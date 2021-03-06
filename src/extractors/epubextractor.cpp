/*
    Copyright (C) 2013  Vishesh Handa <me@vhanda.in>
    Copyright (C) 2016  Christoph Cullmann <cullmann@kde.org>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/


#include "epubextractor.h"

#include <epub.h>

#include <QDateTime>
#include <QRegularExpression>
#include <QDebug>

using namespace KFileMetaData;

EPubExtractor::EPubExtractor(QObject* parent)
    : ExtractorPlugin(parent)
{

}

QStringList EPubExtractor::mimetypes() const
{
    QStringList types;
    types << QStringLiteral("application/epub+zip");

    return types;
}

namespace
{
QString fetchMetadata(struct epub* e, const epub_metadata& type)
{
    int size = 0;
    unsigned char** data = epub_get_metadata(e, type, &size);
    if (data) {
        QStringList strList;
        for (int i = 0; i < size; i++) {
            // skip nullptr entries, can happen for broken xml files
            if (!data[i])
                continue;

            strList << QString::fromUtf8((char*)data[i]);
            free(data[i]);
        }
        free(data);

        return strList.join(QLatin1String(", "));
    }
    return QString();
}
}


void EPubExtractor::extract(ExtractionResult* result)
{
    // open epub, return on exit, file will be closed again at end of function
    auto ePubDoc = epub_open(result->inputUrl().toUtf8().constData(), 1);
    if (!ePubDoc) {
        qWarning() << "Invalid document";
        return;
    }

    result->addType(Type::Document);

    QString value = fetchMetadata(ePubDoc, EPUB_TITLE);
    if (!value.isEmpty()) {
        result->add(Property::Title, value);
    }

    value = fetchMetadata(ePubDoc, EPUB_SUBJECT);
    if (!value.isEmpty()) {
        result->add(Property::Subject, value);
    }

    value = fetchMetadata(ePubDoc, EPUB_CREATOR);
    if (!value.isEmpty()) {
        if (value.startsWith(QLatin1String("aut:"), Qt::CaseInsensitive)) {
            value = value.mid(4).simplified();
        } else if (value.startsWith(QLatin1String("author:"), Qt::CaseInsensitive)) {
            value = value.mid(7).simplified();
        }

        // A lot of authors have their name written in () again. We discard that part
        int index = value.indexOf(QLatin1Char('('));
        if (index)
            value = value.mid(0, index);

        result->add(Property::Author, value);
    }

    // The Contributor just seems to be mostly Calibre aka the Generator
    /*
    value = fetchMetadata(ePubDoc, EPUB_CONTRIB);
    if( !value.isEmpty() ) {
        SimpleResource con;
        con.addType( NCO::Contact() );
        con.addProperty( NCO::fullname(), value );

        fileRes.addProperty( NCO::contributor(), con );
        graph << con;
    }*/

    value = fetchMetadata(ePubDoc, EPUB_PUBLISHER);
    if (!value.isEmpty()) {
        result->add(Property::Publisher, value);
    }

    value = fetchMetadata(ePubDoc, EPUB_DESCRIPTION);
    if (!value.isEmpty()) {
        result->add(Property::Comment, value);
    }

    value = fetchMetadata(ePubDoc, EPUB_DATE);
    if (!value.isEmpty()) {
        if (value.startsWith(QLatin1String("Unspecified:"), Qt::CaseInsensitive)) {
            value = value.mid(QByteArray("Unspecified:").size()).simplified();
        }
        int ind = value.indexOf(QLatin1String("publication:"), Qt::CaseInsensitive);
        if (ind != -1) {
            value = value.mid(ind + QByteArray("publication:").size()).simplified();
        }
        QDateTime dt = ExtractorPlugin::dateTimeFromString(value);
        if (!dt.isNull())
            result->add(Property::CreationDate, dt);
    }

    //
    // Plain Text
    //
    if (result->inputFlags() & ExtractionResult::ExtractPlainText) {
        if (auto iter = epub_get_iterator(ePubDoc, EITERATOR_SPINE, 0)) {
            do {
                char* curr = epub_it_get_curr(iter);
                if (!curr)
                    continue;

                QString html = QString::fromUtf8(curr);
                html.remove(QRegularExpression(QStringLiteral("<[^>]*>")));
                result->append(html);
            } while (epub_it_get_next(iter));

            epub_free_iterator(iter);
        }

        auto tit = epub_get_titerator(ePubDoc, TITERATOR_NAVMAP, 0);
        if (!tit) {
            tit = epub_get_titerator(ePubDoc, TITERATOR_GUIDE, 0);
        }
        if (tit) {
            if (epub_tit_curr_valid(tit)) {
                do {
                    // get link, iterator handles freeing of it
                    char* clink = epub_tit_get_curr_link(tit);

                    // epub_get_data returns -1 on failure
                    char* data = nullptr;
                    const int size = epub_get_data(ePubDoc, clink, &data);
                    if (size >= 0 && data) {
                        QString html = QString::fromUtf8(data, size);
                        // strip html tags
                        html.remove(QRegularExpression(QStringLiteral("<[^>]*>")));

                        result->append(html);
                        free(data);
                    }
                } while (epub_tit_next(tit));
            }
            epub_free_titerator(tit);
        }
    }

    // close epub file again
    epub_close(ePubDoc);
}
