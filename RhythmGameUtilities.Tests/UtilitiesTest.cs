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

            var bpmChanges = new[]
            {
                new Tempo { Position = 0, BPM = 88000 }, new Tempo { Position = 3840, BPM = 112000 },
                new Tempo { Position = 9984, BPM = 89600 }, new Tempo { Position = 22272, BPM = 112000 },
                new Tempo { Position = 33792, BPM = 111500 }, new Tempo { Position = 34560, BPM = 112000 },
                new Tempo { Position = 42240, BPM = 111980 }
            };

            var timeSignatureChanges = new[] { new TimeSignature { Position = 0, Numerator = 4, Denominator = 2 } };

            Assert.That(
                Utilities.ConvertSecondsToTicks(seconds, resolution, bpmChanges, timeSignatureChanges),
                Is.EqualTo(1408));
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

            var bpmChanges = new Tempo[]
            {
                new() { Position = 0, BPM = 88000 }, new() { Position = 3840, BPM = 112000 },
                new() { Position = 9984, BPM = 89600 }, new() { Position = 22272, BPM = 112000 },
                new() { Position = 33792, BPM = 111500 }, new() { Position = 34560, BPM = 112000 },
                new() { Position = 42240, BPM = 111980 }
            };

            var beatBars = Utilities.CalculateBeatBars(bpmChanges, resolution, timeSignature, true);

            Assert.That(beatBars.Length, Is.EqualTo(440));
        }

        [Test]
        public void TestFindPositionNearGivenTick()
        {
            var notes = new Note[]
            {
                new() { Position = 768 }, new() { Position = 960 }, new() { Position = 1152 },
                new() { Position = 1536 }, new() { Position = 1728 }, new() { Position = 1920 },
                new() { Position = 2304 }, new() { Position = 2496 }, new() { Position = 2688 },
                new() { Position = 3072 }, new() { Position = 3264 },
            };

            Assert.That(Utilities.FindPositionNearGivenTick(notes, 100), Is.Null);
            Assert.That(Utilities.FindPositionNearGivenTick(notes, 750), Is.Not.Null);
            Assert.That(Utilities.FindPositionNearGivenTick(notes, 1500), Is.Not.Null);
            Assert.That(Utilities.FindPositionNearGivenTick(notes, 3200), Is.Null);
        }

        [Test]
        public void TestCalculateAccuracyRatio()
        {
            Assert.That(Utilities.CalculateAccuracyRatio(750, 100), Is.EqualTo(0));
            Assert.That(Utilities.CalculateAccuracyRatio(750, 750), Is.EqualTo(1));
            Assert.That(Utilities.CalculateAccuracyRatio(750, 725), Is.EqualTo(0.5f));
        }

    }

}
