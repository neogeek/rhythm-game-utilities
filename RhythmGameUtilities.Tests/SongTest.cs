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
            Assert.That(song.Artist, Is.EqualTo("Example Artist"));
            Assert.That(song.Album, Is.EqualTo("Example Album"));
            Assert.That(song.Genre, Is.EqualTo("Example Genre"));
            Assert.That(song.Year, Is.EqualTo(", 2021"));
            Assert.That(song.Charter, Is.EqualTo("Example Charter"));
            Assert.That(song.Resolution, Is.EqualTo(192));
            Assert.That(song.Difficulty, Is.EqualTo(4));
            Assert.That(song.Offset, Is.EqualTo(0.56));
            Assert.That(song.PreviewStart, Is.EqualTo(45.28));
            Assert.That(song.PreviewEnd, Is.EqualTo(75.28));
            Assert.That(song.MusicStream, Is.EqualTo("Example Song.ogg"));
            Assert.That(song.Difficulties.Count, Is.EqualTo(1));
            Assert.That(song.Difficulties.ContainsKey(Difficulty.Expert), Is.True);
            Assert.That(song.Difficulties[Difficulty.Expert].Length, Is.EqualTo(8));
            Assert.That(song.BPM.Count, Is.EqualTo(7));
            Assert.That(song.BaseBPM, Is.EqualTo(88));
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
            Assert.That(song.Artist, Is.EqualTo("Example Artist"));
            Assert.That(song.Album, Is.EqualTo("Example Album"));
            Assert.That(song.Genre, Is.EqualTo("Example Genre"));
            Assert.That(song.Year, Is.EqualTo(", 2021"));
            Assert.That(song.Charter, Is.EqualTo("Example Charter"));
            Assert.That(song.Resolution, Is.EqualTo(192));
            Assert.That(song.Difficulty, Is.EqualTo(4));
            Assert.That(song.Offset, Is.EqualTo(0.56));
            Assert.That(song.PreviewStart, Is.EqualTo(45.28));
            Assert.That(song.PreviewEnd, Is.EqualTo(75.28));
            Assert.That(song.MusicStream, Is.EqualTo("Example Song.ogg"));
            Assert.That(song.Difficulties.Count, Is.EqualTo(1));
            Assert.That(song.Difficulties.ContainsKey(Difficulty.Expert), Is.True);
            Assert.That(song.Difficulties[Difficulty.Expert].Length, Is.EqualTo(8));
            Assert.That(song.BPM.Count, Is.EqualTo(7));
            Assert.That(song.BaseBPM, Is.EqualTo(88));
        }

    }

}
