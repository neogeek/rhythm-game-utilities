using NUnit.Framework;

namespace RhythmGameUtilities.Tests
{

    public class SongTest
    {

        [Test]
        public void TestSongFromChartFile()
        {
            var song = Song.FromChartFile(MockData.MOCK_CHART_CONTENTS);

            Assert.That(song.Name, Is.EqualTo("Example Song"));
        }

        [Test]
        public void TestSongToJSON()
        {
            var song = Song.FromChartFile(MockData.MOCK_CHART_CONTENTS);

            Assert.That(song.ToJSON(), Is.EqualTo(MockData.MOCK_JSON_CONTENTS));
        }

        [Test]
        public void TestSongFromJSON()
        {
            var song = Song.FromJSON(MockData.MOCK_JSON_CONTENTS);

            Assert.That(song.Name, Is.EqualTo("Example Song"));
        }

    }

}
