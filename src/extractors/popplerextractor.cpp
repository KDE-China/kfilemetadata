/*
    <one line to give the library's name and an idea of what it does.>
    Copyright (C) 2012  Vishesh Handa <me@vhanda.in>
    Copyright (C) 2012  Jörg Ehrichs <joerg.ehrichs@gmx.de>

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


#include "popplerextractor.h"

#include <QScopedPointer>
#include <QDebug>

using namespace KFileMetaData;

PopplerExtractor::PopplerExtractor(QObject* parent)
    : ExtractorPlugin(parent)
{

}

QStringList PopplerExtractor::mimetypes() const
{
    QStringList list;
    list << QStringLiteral("application/pdf");

    return list;
}


void PopplerExtractor::extract(ExtractionResult* result)
{
    const QString fileUrl = result->inputUrl();
    QScopedPointer<Poppler::Document> pdfDoc(Poppler::Document::load(fileUrl, QByteArray(), QByteArray()));

    if (!pdfDoc || pdfDoc->isLocked()) {
        return;
    }

    result->addType(Type::Document);

    QString title = pdfDoc->info(QStringLiteral("Title")).trimmed();

    if (!title.isEmpty()) {
        result->add(Property::Title, title);
    }

    QString subject = pdfDoc->info(QStringLiteral("Subject"));
    if (!subject.isEmpty()) {
        result->add(Property::Subject, subject);
    }

    QString author = pdfDoc->info(QStringLiteral("Author"));
    if (!author.isEmpty()) {
        result->add(Property::Author, author);
    }

    QString generator = pdfDoc->info(QStringLiteral("Producer"));
    if (!generator.isEmpty()) {
        result->add(Property::Generator, generator);
    }

    QString creationDate = pdfDoc->info(QStringLiteral("CreationDate"));
    if (!creationDate.isEmpty()) {
        QByteArray utf8 = creationDate.toUtf8();
        result->add(Property::CreationDate, Poppler::convertDate(utf8.data()));
    }

    if (!(result->inputFlags() & ExtractionResult::ExtractPlainText)) {
        return;
    }

    for (int i = 0; i < pdfDoc->numPages(); i++) {
        QScopedPointer<Poppler::Page> page(pdfDoc->page(i));
        if (!page) { // broken pdf files do not return a valid page
            qWarning() << "Could not read page content from" << fileUrl;
            break;
        }
        result->append(page->text(QRectF()));
    }
}
