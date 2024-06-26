using NUnit.Framework;

namespace RhythmGameUtilities.Tests
{

    public class ParsersTest
    {

        [Test]
        public void TestParseSectionsFromChart()
        {
            var sections = Parsers.ParseSectionsFromChart(Mocks.SONG_CHART);

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
        public void TestParseValuesFromChartSections()
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

        [Test]
        public void TestParseBpmFromChartSections()
        {
            var sections = Parsers.ParseSectionsFromChart(Mocks.SONG_CHART);

            var bpm = Parsers.ParseBpmFromChartSection(sections[NamedSection.SyncTrack]);

            Assert.That(bpm.Count, Is.EqualTo(7));
        }

        [Test]
        public void TestParseNotesFromChartSections()
        {
            var sections = Parsers.ParseSectionsFromChart(Mocks.SONG_CHART);

            var notes = Parsers.ParseNotesFromChartSection(sections[$"{Difficulty.Expert}Single"]);

            Assert.That(notes.Length, Is.EqualTo(8));
        }

        [Test]
        public void TestParseLyricsFromChartSections()
        {
            var sections = Parsers.ParseSectionsFromChart(Mocks.SONG_CHART);

            var lyrics = Parsers.ParseLyricsFromChartSection(sections[NamedSection.Events]);

            Assert.That(lyrics.Count, Is.EqualTo(12));
        }

    }

}
