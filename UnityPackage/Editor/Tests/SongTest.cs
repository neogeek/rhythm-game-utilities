using NUnit.Framework;

namespace RhythmGameUtilities.Tests
{

    public class SongTest
    {

        [Test]
        public void TestSongFromChartFile()
        {
            var song = Song.FromChartFile(Mocks.SONG_CHART);

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
        }

        [Test]
        public void TestSongToJSON()
        {
            var song = Song.FromChartFile(Mocks.SONG_CHART);

            Assert.That(song.ToJSON(), Is.EqualTo(Mocks.SONG_JSON));
        }

        [Test]
        public void TestSongFromJSON()
        {
            var song = Song.FromJSON(Mocks.SONG_JSON);

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
        }

        [Test]
        public void TestCurrentBPM()
        {
            var song = Song.FromChartFile(Mocks.SONG_CHART);

            Assert.That(song.GetCurrentBPM(), Is.EqualTo(88));
            Assert.That(song.GetCurrentBPM(new Note { Position = 0 }), Is.EqualTo(88));
            Assert.That(song.GetCurrentBPM(new Note { Position = 3840 }), Is.EqualTo(112));
            Assert.That(song.GetCurrentBPM(new Note { Position = 9984 }), Is.EqualTo(89));
            Assert.That(song.GetCurrentBPM(new Note { Position = 22272 }), Is.EqualTo(112));
            Assert.That(song.GetCurrentBPM(new Note { Position = 33792 }), Is.EqualTo(111));
            Assert.That(song.GetCurrentBPM(new Note { Position = 34560 }), Is.EqualTo(112));
        }

        [Test]
        public void TestCurrentTimeStamps()
        {
            var song = Song.FromChartFile(Mocks.SONG_CHART);

            Assert.That(song.GetCurrentTimeSignature(), Is.EqualTo(new[] { 4 }));

            Assert.That(song.GetCurrentTimeSignature(new Note { Position = 9984 }),
                Is.EqualTo(new[] { 2, 1 }));
        }

    }

}
