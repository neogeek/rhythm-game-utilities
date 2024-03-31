using System.Linq;
using NUnit.Framework;

namespace RhythmGameUtilities.Tests
{

    public class ParsersTest
    {

        private const string MOCK_CHART_CONTENTS = @"[Song]
{
  Name = ""Example Song""
  Artist = ""Example Artist""
  Album = ""Example Album""
  Genre = ""Example Genre""
  Year = "", 2021""
  Charter = ""Example Charter""
  Resolution = 192
  Difficulty = 4
  Offset = 0.56
  PreviewStart = 45.28
  PreviewEnd = 75.28
  MusicStream = ""Example Song.ogg""
}
[SyncTrack]
{
  0 = TS 4
  0 = B 88000
  3840 = B 112000
  9984 = TS 2 1
  9984 = B 89600
  22272 = TS 4
  22272 = B 112000
  33792 = B 111500
  34560 = B 112000
  42240 = B 111980
  69120 = TS 2 1
}
[Events]
{
  768 = E ""section Intro""
  9984 = E ""phrase_start""
  9984 = E ""section Verse 1""
  10080 = E ""lyric Stand""
  10208 = E ""lyric in""
  10344 = E ""lyric line""
  10496 = E ""lyric as""
  10608 = E ""lyric we""
  10736 = E ""lyric march""
  10896 = E ""lyric to""
  11008 = E ""lyric the""
  11112 = E ""lyric drums""
  11268 = E ""lyric of""
  11400 = E ""lyric the""
  11520 = E ""lyric east""
  11904 = E ""phrase_end""
}
[ExpertSingle]
{
  768 = N 0 0
  768 = S 64 768
  864 = N 1 0
  864 = N 5 0
  960 = N 2 0
  960 = N 6 0
  1056 = N 3 0
  1056 = E solo
  1152 = N 4 0
  1248 = N 7 0
  1248 = E soloend
}";

        [Test]
        public void TestParseSectionsFromChart()
        {
            var sections = Parsers.ParseSectionsFromChart(MOCK_CHART_CONTENTS)
                .ToDictionary(item => item.Key, x => x.Value);

            Assert.That(sections.ContainsKey(NamedSection.Song), Is.True);
            Assert.That(sections.ContainsKey("ExpertSingle"), Is.True);

            Assert.That(sections["Song"].Count(), Is.EqualTo(12));
            Assert.That(sections["ExpertSingle"].Count(), Is.EqualTo(11));
        }

        [Test]
        public void TestParseBpmFromChartChartSections()
        {
            var sections = Parsers.ParseSectionsFromChart(MOCK_CHART_CONTENTS);

            var bpm = Parsers.ParseBpmFromChartChartSection(sections[NamedSection.SyncTrack]);

            Assert.That(bpm.Count, Is.EqualTo(7));
        }

        [Test]
        public void TestParseTrackEventsFromChartSections()
        {
            var sections = Parsers.ParseSectionsFromChart(MOCK_CHART_CONTENTS);

            var trackEvents =
                Parsers.ParseTrackEventsFromChartSection(sections[$"{Difficulty.Expert}Single"], TypeCode.Event);

            Assert.That(trackEvents.Count(), Is.EqualTo(2));
        }

        [Test]
        public void TestParseNotesFromChartSections()
        {
            var sections = Parsers.ParseSectionsFromChart(MOCK_CHART_CONTENTS);

            var notes = Parsers.ParseNotesFromChartSection(sections[$"{Difficulty.Expert}Single"]);

            Assert.That(notes.Length, Is.EqualTo(8));
        }

        [Test]
        public void TestParseLyricsFromChartSections()
        {
            var sections = Parsers.ParseSectionsFromChart(MOCK_CHART_CONTENTS);

            var lyrics = Parsers.ParseLyricsFromChartSection(sections[NamedSection.Events]);

            Assert.That(lyrics.Count, Is.EqualTo(12));
        }

    }

}
