/*
 * TagLibExtractor tests.
 *
 * Copyright (C) 2015  Juan Palacios <jpalaciosdev@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include "taglibextractortest.h"
#include "simpleextractionresult.h"
#include "propertyinfo.h"
//TODO: use QTESTFINDDATA and remove this
#include "indexerextractortestsconfig.h"
#include "extractors/taglibextractor.h"

#include <QDebug>
#include <QTest>
#include <QDir>

Q_DECLARE_METATYPE(KFileMetaData::Property::Property)

using namespace KFileMetaData;

QString TagLibExtractorTest::testFilePath(const QString& fileName) const
{
    return QLatin1String(INDEXER_TESTS_SAMPLE_FILES_PATH) + QDir::separator() + fileName;
}

const QStringList TagLibExtractorTest::propertyEnumNames(const QList<KFileMetaData::Property::Property>& keys) const
{
    QStringList result;
    for (auto key : keys) {
        result.append(PropertyInfo(key).name());
    }
    return result;
}

void TagLibExtractorTest::testOpus()
{
    TagLibExtractor plugin{this};

    SimpleExtractionResult resultOpus(testFilePath("test.opus"), "audio/opus");
    plugin.extract(&resultOpus);

    QCOMPARE(resultOpus.types().size(), 1);
    QCOMPARE(resultOpus.types().constFirst(), Type::Audio);

    QCOMPARE(resultOpus.properties().value(Property::Title), QVariant(QStringLiteral("Title")));
    QCOMPARE(resultOpus.properties().value(Property::Artist), QVariant(QStringLiteral("Artist")));
    QCOMPARE(resultOpus.properties().value(Property::Album), QVariant(QStringLiteral("Album")));
    QCOMPARE(resultOpus.properties().value(Property::AlbumArtist), QVariant(QStringLiteral("Album Artist")));
    QCOMPARE(resultOpus.properties().value(Property::Genre), QVariant(QStringLiteral("Genre")));
    QCOMPARE(resultOpus.properties().value(Property::Comment), QVariant(QStringLiteral("Comment")));
    QCOMPARE(resultOpus.properties().value(Property::Composer), QVariant(QStringLiteral("Composer")));
    QCOMPARE(resultOpus.properties().value(Property::Lyricist), QVariant(QStringLiteral("Lyricist")));
    QCOMPARE(resultOpus.properties().value(Property::Conductor), QVariant(QStringLiteral("Conductor")));
    QCOMPARE(resultOpus.properties().value(Property::Arranger), QVariant(QStringLiteral("Arranger")));
    QCOMPARE(resultOpus.properties().value(Property::Ensemble), QVariant(QStringLiteral("Ensemble")));
    QCOMPARE(resultOpus.properties().value(Property::Location), QVariant(QStringLiteral("Location")));
    QCOMPARE(resultOpus.properties().value(Property::Performer), QVariant(QStringLiteral("Performer")));
    QCOMPARE(resultOpus.properties().value(Property::Language), QVariant(QStringLiteral("Language")));
    QCOMPARE(resultOpus.properties().value(Property::Publisher), QVariant(QStringLiteral("Publisher")));
    QCOMPARE(resultOpus.properties().value(Property::Label), QVariant(QStringLiteral("Label")));
    QCOMPARE(resultOpus.properties().value(Property::Author), QVariant(QStringLiteral("Author")));
    QCOMPARE(resultOpus.properties().value(Property::Copyright), QVariant(QStringLiteral("Copyright")));
    QCOMPARE(resultOpus.properties().value(Property::Compilation), QVariant(QStringLiteral("Compilation")));
    QCOMPARE(resultOpus.properties().value(Property::License), QVariant(QStringLiteral("License")));
    QCOMPARE(resultOpus.properties().value(Property::Lyrics), QVariant(QStringLiteral("Lyrics")));
    QCOMPARE(resultOpus.properties().value(Property::Opus).toInt(), 1);
    QCOMPARE(resultOpus.properties().value(Property::TrackNumber).toInt(), 1);
    QCOMPARE(resultOpus.properties().value(Property::ReleaseYear).toInt(), 2015);
    QCOMPARE(resultOpus.properties().value(Property::Channels).toInt(), 1);
    QCOMPARE(resultOpus.properties().value(Property::DiscNumber).toInt(), 1);
    QCOMPARE(resultOpus.properties().value(Property::Rating).toInt(), 1);
}

void TagLibExtractorTest::testFlac()
{
    TagLibExtractor plugin{this};
    SimpleExtractionResult resultFlac(testFilePath("test.flac"), "audio/flac");
    plugin.extract(&resultFlac);

    QCOMPARE(resultFlac.types().size(), 1);
    QCOMPARE(resultFlac.types().constFirst(), Type::Audio);

    QCOMPARE(resultFlac.properties().value(Property::Title), QVariant(QStringLiteral("Title")));
    QCOMPARE(resultFlac.properties().value(Property::Artist), QVariant(QStringLiteral("Artist")));
    QCOMPARE(resultFlac.properties().value(Property::Album), QVariant(QStringLiteral("Album")));
    QCOMPARE(resultFlac.properties().value(Property::AlbumArtist), QVariant(QStringLiteral("Album Artist")));
    QCOMPARE(resultFlac.properties().value(Property::Genre), QVariant(QStringLiteral("Genre")));
    QCOMPARE(resultFlac.properties().value(Property::Comment), QVariant(QStringLiteral("Comment")));
    QCOMPARE(resultFlac.properties().value(Property::Composer), QVariant(QStringLiteral("Composer")));
    QCOMPARE(resultFlac.properties().value(Property::Lyricist), QVariant(QStringLiteral("Lyricist")));
    QCOMPARE(resultFlac.properties().value(Property::Conductor), QVariant(QStringLiteral("Conductor")));
    QCOMPARE(resultFlac.properties().value(Property::Arranger), QVariant(QStringLiteral("Arranger")));
    QCOMPARE(resultFlac.properties().value(Property::Ensemble), QVariant(QStringLiteral("Ensemble")));
    QCOMPARE(resultFlac.properties().value(Property::Location), QVariant(QStringLiteral("Location")));
    QCOMPARE(resultFlac.properties().value(Property::Performer), QVariant(QStringLiteral("Performer")));
    QCOMPARE(resultFlac.properties().value(Property::Language), QVariant(QStringLiteral("Language")));
    QCOMPARE(resultFlac.properties().value(Property::Publisher), QVariant(QStringLiteral("Publisher")));
    QCOMPARE(resultFlac.properties().value(Property::Label), QVariant(QStringLiteral("Label")));
    QCOMPARE(resultFlac.properties().value(Property::Author), QVariant(QStringLiteral("Author")));
    QCOMPARE(resultFlac.properties().value(Property::Copyright), QVariant(QStringLiteral("Copyright")));
    QCOMPARE(resultFlac.properties().value(Property::Compilation), QVariant(QStringLiteral("Compilation")));
    QCOMPARE(resultFlac.properties().value(Property::License), QVariant(QStringLiteral("License")));
    QCOMPARE(resultFlac.properties().value(Property::Lyrics), QVariant(QStringLiteral("Lyrics")));
    QCOMPARE(resultFlac.properties().value(Property::Opus).toInt(), 1);
    QCOMPARE(resultFlac.properties().value(Property::TrackNumber).toInt(), 1);
    QCOMPARE(resultFlac.properties().value(Property::ReleaseYear).toInt(), 2015);
    QCOMPARE(resultFlac.properties().value(Property::Channels).toInt(), 1);
    QCOMPARE(resultFlac.properties().value(Property::DiscNumber).toInt(), 1);
    QCOMPARE(resultFlac.properties().value(Property::Rating).toInt(), 10);
}

void TagLibExtractorTest::testOgg()
{
    TagLibExtractor plugin{this};
    SimpleExtractionResult resultOgg(testFilePath("test.ogg"), "audio/ogg");
    plugin.extract(&resultOgg);

    QCOMPARE(resultOgg.types().size(), 1);
    QCOMPARE(resultOgg.types().constFirst(), Type::Audio);

    QCOMPARE(resultOgg.properties().value(Property::Title), QVariant(QStringLiteral("Title")));
    QCOMPARE(resultOgg.properties().value(Property::Artist), QVariant(QStringLiteral("Artist")));
    QCOMPARE(resultOgg.properties().value(Property::Album), QVariant(QStringLiteral("Album")));
    QCOMPARE(resultOgg.properties().value(Property::AlbumArtist), QVariant(QStringLiteral("Album Artist")));
    QCOMPARE(resultOgg.properties().value(Property::Genre), QVariant(QStringLiteral("Genre")));
    QCOMPARE(resultOgg.properties().value(Property::Comment), QVariant(QStringLiteral("Comment")));
    QCOMPARE(resultOgg.properties().value(Property::Composer), QVariant(QStringLiteral("Composer")));
    QCOMPARE(resultOgg.properties().value(Property::Lyricist), QVariant(QStringLiteral("Lyricist")));
    QCOMPARE(resultOgg.properties().value(Property::Conductor), QVariant(QStringLiteral("Conductor")));
    QCOMPARE(resultOgg.properties().value(Property::Arranger), QVariant(QStringLiteral("Arranger")));
    QCOMPARE(resultOgg.properties().value(Property::Ensemble), QVariant(QStringLiteral("Ensemble")));
    QCOMPARE(resultOgg.properties().value(Property::Location), QVariant(QStringLiteral("Location")));
    QCOMPARE(resultOgg.properties().value(Property::Performer), QVariant(QStringLiteral("Performer")));
    QCOMPARE(resultOgg.properties().value(Property::Language), QVariant(QStringLiteral("Language")));
    QCOMPARE(resultOgg.properties().value(Property::Publisher), QVariant(QStringLiteral("Publisher")));
    QCOMPARE(resultOgg.properties().value(Property::Label), QVariant(QStringLiteral("Label")));
    QCOMPARE(resultOgg.properties().value(Property::Author), QVariant(QStringLiteral("Author")));
    QCOMPARE(resultOgg.properties().value(Property::Copyright), QVariant(QStringLiteral("Copyright")));
    QCOMPARE(resultOgg.properties().value(Property::Compilation), QVariant(QStringLiteral("Compilation")));
    QCOMPARE(resultOgg.properties().value(Property::License), QVariant(QStringLiteral("License")));
    QCOMPARE(resultOgg.properties().value(Property::Lyrics), QVariant(QStringLiteral("Lyrics")));
    QCOMPARE(resultOgg.properties().value(Property::Opus).toInt(), 1);
    QCOMPARE(resultOgg.properties().value(Property::TrackNumber).toInt(), 1);
    QCOMPARE(resultOgg.properties().value(Property::ReleaseYear).toInt(), 2015);
    QCOMPARE(resultOgg.properties().value(Property::Channels).toInt(), 1);
    QCOMPARE(resultOgg.properties().value(Property::DiscNumber).toInt(), 1);
    QCOMPARE(resultOgg.properties().value(Property::Rating).toInt(), 5);
}

void TagLibExtractorTest::testMp3()
{
    TagLibExtractor plugin{this};
    SimpleExtractionResult resultMp3(testFilePath("test.mp3"), "audio/mpeg");
    plugin.extract(&resultMp3);

    QCOMPARE(resultMp3.types().size(), 1);
    QCOMPARE(resultMp3.types().constFirst(), Type::Audio);
    QCOMPARE(resultMp3.properties().value(Property::Title), QVariant(QStringLiteral("Title")));
    QCOMPARE(resultMp3.properties().value(Property::Artist), QVariant(QStringLiteral("Artist")));
    QCOMPARE(resultMp3.properties().value(Property::Album), QVariant(QStringLiteral("Album")));
    QCOMPARE(resultMp3.properties().value(Property::AlbumArtist), QVariant(QStringLiteral("Album Artist")));
    QCOMPARE(resultMp3.properties().value(Property::Genre), QVariant(QStringLiteral("Genre")));
    QCOMPARE(resultMp3.properties().value(Property::Comment), QVariant(QStringLiteral("Comment")));
    QCOMPARE(resultMp3.properties().value(Property::Composer), QVariant(QStringLiteral("Composer")));
    QCOMPARE(resultMp3.properties().value(Property::Lyricist), QVariant(QStringLiteral("Lyricist")));
    QCOMPARE(resultMp3.properties().value(Property::Conductor), QVariant(QStringLiteral("Conductor")));
    QCOMPARE(resultMp3.properties().value(Property::Publisher), QVariant(QStringLiteral("Publisher")));
    QCOMPARE(resultMp3.properties().value(Property::Language), QVariant(QStringLiteral("Language")));
    QCOMPARE(resultMp3.properties().value(Property::Compilation), QVariant(QStringLiteral("Compilation")));
    QCOMPARE(resultMp3.properties().value(Property::Lyrics), QVariant(QStringLiteral("Lyrics")));
    QCOMPARE(resultMp3.properties().value(Property::TrackNumber).toInt(), 1);
    QCOMPARE(resultMp3.properties().value(Property::ReleaseYear).toInt(), 2015);
    QCOMPARE(resultMp3.properties().value(Property::Channels).toInt(), 1);
    QCOMPARE(resultMp3.properties().value(Property::DiscNumber).toInt(), 1);
    QCOMPARE(resultMp3.properties().value(Property::Rating).toInt(), 10);
}

void TagLibExtractorTest::testMpc()
{
    TagLibExtractor plugin{this};
    SimpleExtractionResult resultMpc(testFilePath("test.mpc"), "audio/x-musepack");
    plugin.extract(&resultMpc);

    QCOMPARE(resultMpc.types().size(), 1);
    QCOMPARE(resultMpc.types().constFirst(), Type::Audio);

    QCOMPARE(resultMpc.properties().value(Property::Title), QVariant(QStringLiteral("Title")));
    QCOMPARE(resultMpc.properties().value(Property::Artist), QVariant(QStringLiteral("Artist")));
    QCOMPARE(resultMpc.properties().value(Property::Album), QVariant(QStringLiteral("Album")));
    QCOMPARE(resultMpc.properties().value(Property::AlbumArtist), QVariant(QStringLiteral("Album Artist")));
    QCOMPARE(resultMpc.properties().value(Property::Genre), QVariant(QStringLiteral("Genre")));
    QCOMPARE(resultMpc.properties().value(Property::Comment), QVariant(QStringLiteral("Comment")));
    QCOMPARE(resultMpc.properties().value(Property::Composer), QVariant(QStringLiteral("Composer")));
    QCOMPARE(resultMpc.properties().value(Property::Conductor), QVariant(QStringLiteral("Conductor")));
    QCOMPARE(resultMpc.properties().value(Property::Arranger), QVariant(QStringLiteral("Arranger")));
    QCOMPARE(resultMpc.properties().value(Property::Ensemble), QVariant(QStringLiteral("Ensemble")));
    QCOMPARE(resultMpc.properties().value(Property::Location), QVariant(QStringLiteral("Location")));
    QCOMPARE(resultMpc.properties().value(Property::Performer), QVariant(QStringLiteral("Performer")));
    QCOMPARE(resultMpc.properties().value(Property::Language), QVariant(QStringLiteral("Language")));
    QCOMPARE(resultMpc.properties().value(Property::Publisher), QVariant(QStringLiteral("Publisher")));
    QCOMPARE(resultMpc.properties().value(Property::Label), QVariant(QStringLiteral("Label")));
    QCOMPARE(resultMpc.properties().value(Property::Author), QVariant(QStringLiteral("Author")));
    QCOMPARE(resultMpc.properties().value(Property::Copyright), QVariant(QStringLiteral("Copyright")));
    QCOMPARE(resultMpc.properties().value(Property::Compilation), QVariant(QStringLiteral("Compilation")));
    QCOMPARE(resultMpc.properties().value(Property::License), QVariant(QStringLiteral("License")));
    QCOMPARE(resultMpc.properties().value(Property::Lyrics), QVariant(QStringLiteral("Lyrics")));
    QCOMPARE(resultMpc.properties().value(Property::TrackNumber).toInt(), 1);
    QCOMPARE(resultMpc.properties().value(Property::ReleaseYear).toInt(), 2015);
    QCOMPARE(resultMpc.properties().value(Property::Channels).toInt(), 1);
    QCOMPARE(resultMpc.properties().value(Property::DiscNumber).isValid(), false);
    QCOMPARE(resultMpc.properties().value(Property::Rating).toInt(), 4);
}

void TagLibExtractorTest::testMp4()
{
    TagLibExtractor plugin{this};
    SimpleExtractionResult resultMp4(testFilePath("test.m4a"), "audio/mp4");
    plugin.extract(&resultMp4);

    QCOMPARE(resultMp4.types().size(), 1);
    QCOMPARE(resultMp4.types().constFirst(), Type::Audio);

    QCOMPARE(resultMp4.properties().value(Property::Title), QVariant(QStringLiteral("Title")));
    QCOMPARE(resultMp4.properties().value(Property::Artist), QVariant(QStringLiteral("Artist")));
    QCOMPARE(resultMp4.properties().value(Property::Album), QVariant(QStringLiteral("Album")));
    QCOMPARE(resultMp4.properties().value(Property::AlbumArtist), QVariant(QStringLiteral("Album Artist")));
    QCOMPARE(resultMp4.properties().value(Property::Genre), QVariant(QStringLiteral("Genre")));
    QCOMPARE(resultMp4.properties().value(Property::Comment), QVariant(QStringLiteral("Comment")));
    QCOMPARE(resultMp4.properties().value(Property::Composer), QVariant(QStringLiteral("Composer")));
    QCOMPARE(resultMp4.properties().value(Property::Copyright), QVariant(QStringLiteral("Copyright")));
    QCOMPARE(resultMp4.properties().value(Property::Lyrics), QVariant(QStringLiteral("Lyrics")));
    QCOMPARE(resultMp4.properties().value(Property::TrackNumber).toInt(), 1);
    QCOMPARE(resultMp4.properties().value(Property::ReleaseYear).toInt(), 2015);
    QCOMPARE(resultMp4.properties().value(Property::Channels).toInt(), 2);
    QCOMPARE(resultMp4.properties().value(Property::DiscNumber).toInt(), 1);
    QCOMPARE(resultMp4.properties().value(Property::Rating).toInt(), 8);
}

void TagLibExtractorTest::testMP3Rating_data()
{
    QTest::addColumn<QString>("path");
    QTest::addColumn<int>("expectedRating");

#if QT_VERSION >= 0x050900
    QTest::addRow("WMP")
        << QFINDTESTDATA("samplefiles/mp3_rating/testWMP.mp3")
        << 0 ;
    QTest::addRow("WMP1")
        << QFINDTESTDATA("samplefiles/mp3_rating/testWMP1.mp3")
        << 2 ;
    QTest::addRow("WMP2")
        << QFINDTESTDATA("samplefiles/mp3_rating/testWMP2.mp3")
        << 4 ;
    QTest::addRow("WMP3")
        << QFINDTESTDATA("samplefiles/mp3_rating/testWMP3.mp3")
        << 6 ;
    QTest::addRow("WMP4")
        << QFINDTESTDATA("samplefiles/mp3_rating/testWMP4.mp3")
        << 8 ;
    QTest::addRow("WMP5")
        << QFINDTESTDATA("samplefiles/mp3_rating/testWMP5.mp3")
        << 10 ;
    QTest::addRow("MM")
        << QFINDTESTDATA("samplefiles/mp3_rating/testMM.mp3")
        << 0 ;
    QTest::addRow("MM1")
        << QFINDTESTDATA("samplefiles/mp3_rating/testMM1.mp3")
        << 1 ;
    QTest::addRow("MM2")
        << QFINDTESTDATA("samplefiles/mp3_rating/testMM2.mp3")
        << 2 ;
    QTest::addRow("MM3")
        << QFINDTESTDATA("samplefiles/mp3_rating/testMM3.mp3")
        << 3 ;
    QTest::addRow("MM4")
        << QFINDTESTDATA("samplefiles/mp3_rating/testMM4.mp3")
        << 4 ;
    QTest::addRow("MM5")
        << QFINDTESTDATA("samplefiles/mp3_rating/testMM5.mp3")
        << 5 ;
    QTest::addRow("MM6")
        << QFINDTESTDATA("samplefiles/mp3_rating/testMM6.mp3")
        << 6 ;
    QTest::addRow("MM7")
        << QFINDTESTDATA("samplefiles/mp3_rating/testMM7.mp3")
        << 7 ;
    QTest::addRow("MM8")
        << QFINDTESTDATA("samplefiles/mp3_rating/testMM8.mp3")
        << 8 ;
    QTest::addRow("MM9")
        << QFINDTESTDATA("samplefiles/mp3_rating/testMM9.mp3")
        << 9 ;
    QTest::addRow("MM10")
        << QFINDTESTDATA("samplefiles/mp3_rating/testMM10.mp3")
        << 10 ;
#else
    // FIXME: Unimplemented
#endif
}

void TagLibExtractorTest::testMP3Rating()
{
    QFETCH(QString, path);
    QFETCH(int, expectedRating);

    TagLibExtractor plugin{this};
    SimpleExtractionResult resultMp3(path, "audio/mpeg");
    plugin.extract(&resultMp3);

    QCOMPARE(resultMp3.properties().value(Property::Rating).toInt(), expectedRating);
}

void TagLibExtractorTest::testNoMetadata_data()
{
    const auto expectedKeys = QList<Property::Property>{
        Property::BitRate,
        Property::Channels,
        Property::Duration,
        Property::SampleRate,
    };

    QTest::addColumn<QString>("path");
    QTest::addColumn<QString>("mimeType");
    QTest::addColumn<QList<Property::Property>>("expectedKeys");
    QTest::addColumn<QString>("failMessage");

#if QT_VERSION >= 0x050900
    QTest::addRow("mp3")
        << QFINDTESTDATA("samplefiles/no-meta/test.mp3")
        << QStringLiteral("audio/mp3")
        << expectedKeys << QString()
        ;

    QTest::addRow("m4a")
        << QFINDTESTDATA("samplefiles/no-meta/test.m4a")
        << QStringLiteral("audio/mp4")
        << expectedKeys << QString()
        ;

    QTest::addRow("flac")
        << QFINDTESTDATA("samplefiles/no-meta/test.flac")
        << QStringLiteral("audio/flac")
        << expectedKeys << QString()
        ;

    QTest::addRow("opus")
        << QFINDTESTDATA("samplefiles/no-meta/test.opus")
        << QStringLiteral("audio/opus")
        << expectedKeys << QString()
        ;

    QTest::addRow("ogg")
        << QFINDTESTDATA("samplefiles/no-meta/test.ogg")
        << QStringLiteral("audio/ogg")
        << expectedKeys << QString()
        ;

    QTest::addRow("mpc")
        << QFINDTESTDATA("samplefiles/no-meta/test.mpc")
        << QStringLiteral("audio/x-musepack")
        << expectedKeys << QString()
        ;
#else
    // FIXME: Unimplemented
#endif

}

void  TagLibExtractorTest::testNoMetadata()
{
    QFETCH(QString, path);
    QFETCH(QString, mimeType);
    QFETCH(QList<Property::Property>, expectedKeys);
    QFETCH(QString, failMessage);

    TagLibExtractor plugin{this};
    SimpleExtractionResult extracted(path, mimeType);
    plugin.extract(&extracted);

    const auto resultList = extracted.properties();
    const auto resultKeys = resultList.uniqueKeys();

    const auto excessKeys = resultKeys.toSet() - expectedKeys.toSet();
    const auto missingKeys = expectedKeys.toSet() - resultKeys.toSet();
    if (excessKeys.size()) {
        const auto propNames =  propertyEnumNames(excessKeys.toList()).join(QLatin1String(", "));
        if (failMessage.isEmpty()) {
            const auto message = QStringLiteral("Excess properties: %1").arg(propNames);
            QWARN(qPrintable(message));
        } else {
            QEXPECT_FAIL("", qPrintable(QStringLiteral("%1: %2").arg(failMessage).arg(propNames)), Continue);
        }
    } else if (missingKeys.size()) {
        const auto message = QStringLiteral("Missing properties: %1")
            .arg(propertyEnumNames(missingKeys.toList()).join(QLatin1String(", ")));
        QWARN(qPrintable(message));
    }
    QCOMPARE(resultKeys, expectedKeys);
    if (!failMessage.isEmpty()) {
        auto excessKeys = resultKeys.toSet() - expectedKeys.toSet();
        const auto message = QStringLiteral("%1: %2")
            .arg(failMessage)
            .arg(propertyEnumNames(excessKeys.toList()).join(QLatin1String(", ")));
        QEXPECT_FAIL("", qPrintable(message), Continue);
    }
    QCOMPARE(resultKeys, expectedKeys);
}

QTEST_GUILESS_MAIN(TagLibExtractorTest)
