using System;
using NUnit.Framework;

namespace RhythmGameUtilities.Tests
{

    public class ParsersTest
    {

        [Test]
        public void TestParseTempoChangesFromChartSection()
        {
            var sections = Parsers.ParseSectionsFromChart(Mocks.SONG_CHART);

            var tempoChanges = Parsers.ParseTempoChangesFromChartSection(sections[NamedSection.SyncTrack]);

            Console.WriteLine(tempoChanges.Length); // 7

            Assert.That(tempoChanges.Length, Is.EqualTo(7));
        }

        [Test]
        public void TestParseLyricsFromChartSection()
        {
            var sections = Parsers.ParseSectionsFromChart(Mocks.SONG_CHART);

            var lyrics = Parsers.ParseLyricsFromChartSection(sections[NamedSection.Events]);

            Console.WriteLine(lyrics.Count); // 12

            Assert.That(lyrics.Count, Is.EqualTo(12));
        }

        [Test]
        public void TestParseMetaDataFromChartSection()
        {
            var sections = Parsers.ParseSectionsFromChart(Mocks.SONG_CHART);

            var metaData = Parsers.ParseMetaDataFromChartSection(sections[NamedSection.Song]);

            Console.WriteLine(metaData["Name"]); // Example Song
            Console.WriteLine(metaData["Resolution"]); // 192
            Console.WriteLine(metaData["MusicStream"]); // Example Song.ogg

            Assert.That(metaData["Name"], Is.EqualTo("Example Song"));
            Assert.That(metaData["Resolution"], Is.EqualTo("192"));
            Assert.That(metaData["MusicStream"], Is.EqualTo("Example Song.ogg"));
        }

        [Test]
        public void TestParseNotesFromChartSection()
        {
            var sections = Parsers.ParseSectionsFromChart(Mocks.SONG_CHART);

            var notes = Parsers.ParseNotesFromChartSection(sections[$"{Difficulty.Expert}Single"]);

            Assert.That(notes.Length, Is.EqualTo(8));
        }

        [Test]
        public void TestParseSectionsFromChart()
        {
            var sections = Parsers.ParseSectionsFromChart(Mocks.SONG_CHART);

            Console.WriteLine(sections.Count); // 4

            Assert.That(sections.Count, Is.EqualTo(4));

            Assert.That(sections.ContainsKey(NamedSection.Song), Is.True);
            Assert.That(sections["Song"].Length, Is.EqualTo(12));
            Assert.That(sections.ContainsKey(NamedSection.SyncTrack), Is.True);
            Assert.That(sections[NamedSection.SyncTrack].Length, Is.EqualTo(11));
            Assert.That(sections.ContainsKey(NamedSection.Events), Is.True);
            Assert.That(sections[NamedSection.Events].Length, Is.EqualTo(16));
            Assert.That(sections.ContainsKey("ExpertSingle"), Is.True);
            Assert.That(sections["ExpertSingle"].Length, Is.EqualTo(11));
        }

        [Test]
        public void TestParseTimeSignatureChangesFromChartSection()
        {
            var sections = Parsers.ParseSectionsFromChart(Mocks.SONG_CHART);

            var timeSignatures = Parsers.ParseTimeSignatureChangesFromChartSection(sections[NamedSection.SyncTrack]);

            Assert.That(timeSignatures.Length, Is.EqualTo(4));
        }

        [Test]
        public void TestParseValuesFromChartSection()
        {
            var sections = Parsers.ParseSectionsFromChart(Mocks.SONG_CHART);

            Assert.That(sections.ContainsKey(NamedSection.Song), Is.True);
            Assert.That(sections[NamedSection.Song][0].Key, Is.EqualTo("Name"));
            Assert.That(sections[NamedSection.Song][0].Value[0], Is.EqualTo("Example Song"));
            Assert.That(sections[NamedSection.Song][6].Key, Is.EqualTo("Resolution"));
            Assert.That(sections[NamedSection.Song][6].Value[0], Is.EqualTo("192"));
            Assert.That(sections[NamedSection.Song][11].Key, Is.EqualTo("MusicStream"));
            Assert.That(sections[NamedSection.Song][11].Value[0], Is.EqualTo("Example Song.ogg"));
        }

    }

}
