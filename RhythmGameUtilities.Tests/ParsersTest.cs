using System.Linq;
using NUnit.Framework;

namespace RhythmGameUtilities.Tests
{

    public class ParsersTest
    {

        [Test]
        public void TestParseSectionsFromChart()
        {
            var sections = Parsers.ParseSectionsFromChart(MockData.MOCK_CHART_CONTENTS)
                .ToDictionary(item => item.Key, x => x.Value);

            Assert.That(sections.ContainsKey(NamedSection.Song), Is.True);
            Assert.That(sections.ContainsKey("ExpertSingle"), Is.True);

            Assert.That(sections["Song"].Count(), Is.EqualTo(12));
            Assert.That(sections["ExpertSingle"].Count(), Is.EqualTo(11));
        }

        [Test]
        public void TestParseBpmFromChartChartSections()
        {
            var sections = Parsers.ParseSectionsFromChart(MockData.MOCK_CHART_CONTENTS);

            var bpm = Parsers.ParseBpmFromChartChartSection(sections[NamedSection.SyncTrack]);

            Assert.That(bpm.Count, Is.EqualTo(7));
        }

        [Test]
        public void TestParseTrackEventsFromChartSections()
        {
            var sections = Parsers.ParseSectionsFromChart(MockData.MOCK_CHART_CONTENTS);

            var trackEvents =
                Parsers.ParseTrackEventsFromChartSection(sections[$"{Difficulty.Expert}Single"], TypeCode.Event);

            Assert.That(trackEvents.Count(), Is.EqualTo(2));
        }

        [Test]
        public void TestParseNotesFromChartSections()
        {
            var sections = Parsers.ParseSectionsFromChart(MockData.MOCK_CHART_CONTENTS);

            var notes = Parsers.ParseNotesFromChartSection(sections[$"{Difficulty.Expert}Single"]);

            Assert.That(notes.Length, Is.EqualTo(8));
        }

        [Test]
        public void TestParseLyricsFromChartSections()
        {
            var sections = Parsers.ParseSectionsFromChart(MockData.MOCK_CHART_CONTENTS);

            var lyrics = Parsers.ParseLyricsFromChartSection(sections[NamedSection.Events]);

            Assert.That(lyrics.Count, Is.EqualTo(12));
        }

    }

}
