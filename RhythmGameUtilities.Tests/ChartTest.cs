using NUnit.Framework;

namespace RhythmGameUtilities.Tests
{

    public class ChartTest
    {

        [Test]
        public void TestReadResolutionFromChartData()
        {
            var resolution = Chart.ReadResolutionFromChartData(Mocks.SONG_CHART);

            Assert.That(resolution, Is.EqualTo(192));
        }

        [Test]
        public void TestReadTempoChangesFromChartData()
        {
            var tempoChanges = Chart.ReadTempoChangesFromChartData(Mocks.SONG_CHART);

            Assert.That(tempoChanges.Length, Is.EqualTo(7));
        }

        [Test]
        public void TestReadTimeSignatureChangesFromChartData()
        {
            var timeSignatureChanges = Chart.ReadTimeSignatureChangesFromChartData(Mocks.SONG_CHART);

            Assert.That(timeSignatureChanges.Length, Is.EqualTo(4));
        }

        [Test]
        public void TestReadNotesFromChartData()
        {
            var notes = Chart.ReadNotesFromChartData(Mocks.SONG_CHART, Difficulty.Expert);

            Assert.That(notes.Length, Is.EqualTo(8));
        }

    }

}
