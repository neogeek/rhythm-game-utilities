using System.Collections.Generic;
using NUnit.Framework;

namespace RhythmGameUtilities.Tests
{

    public class UtilitiesTest
    {

        [Test]
        public void TestConvertTickToPosition()
        {
            const int tick = 1056;
            const int resolution = 192;

            Assert.That(Utilities.ConvertTickToPosition(tick, resolution), Is.EqualTo(5.5f));
        }

        [Test]
        public void TestConvertSecondsToTicks()
        {
            const int seconds = 5;
            const int resolution = 192;

            var bpmChanges = new Dictionary<int, int>
            {
                { 0, 88000 },
                { 3840, 112000 },
                { 9984, 89600 },
                { 22272, 112000 },
                { 33792, 111500 },
                { 34560, 112000 },
                { 42240, 111980 }
            };

            Assert.That(
                Utilities.ConvertSecondsToTicks(seconds, resolution, bpmChanges), Is.EqualTo(1408));
        }

        [Test]
        public void TestIsOnTheBeat()
        {
            Assert.That(Utilities.IsOnTheBeat(120, 10), Is.True);
            Assert.That(Utilities.IsOnTheBeat(60, 1), Is.True);
            Assert.That(Utilities.IsOnTheBeat(60, 1.5f), Is.False);
        }

        [Test]
        public void TestRoundUpToTheNearestMultiplier()
        {
            Assert.That(Utilities.RoundUpToTheNearestMultiplier(12, 10), Is.EqualTo(20));
        }

        [Test]
        public void TestCalculateBeatBars()
        {
            const int resolution = 192;
            const int timeSignature = 4;

            var bpmChanges = new Dictionary<int, int>
            {
                { 0, 88000 },
                { 3840, 112000 },
                { 9984, 89600 },
                { 22272, 112000 },
                { 33792, 111500 },
                { 34560, 112000 },
                { 42240, 111980 }
            };

            var beatBars = Utilities.CalculateBeatBars(bpmChanges, resolution, timeSignature, true);

            Assert.That(beatBars.Count, Is.EqualTo(440));
        }

    }

}
