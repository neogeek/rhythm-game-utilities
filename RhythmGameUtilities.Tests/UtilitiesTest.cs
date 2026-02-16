using NUnit.Framework;

namespace RhythmGameUtilities.Tests
{

    public class UtilitiesTest
    {

        [Test]
        public void TestCalculateAccuracyRatio()
        {
            const int seconds = 2;
            const int resolution = 192;
            const int positionDelta = 50;

            var tempoChanges = new Tempo[] { new() { Position = 0, BPM = 120000 } };

            var timeSignatureChanges = new TimeSignature[] { new() { Position = 0, Numerator = 4, Denominator = 2 } };

            var note = new Note { Position = 750 };

            var currentPosition =
                Utilities.ConvertSecondsToTicks(seconds, resolution, tempoChanges, timeSignatureChanges);

            var value = Utilities.CalculateAccuracyRatio(note.Position, currentPosition, positionDelta);

            Assert.That(value, Is.EqualTo(0.64).Within(0.01));
        }

        [Test]
        public void TestCalculateAccuracyRatioContinued()
        {
            Assert.That(Utilities.CalculateAccuracyRatio(750, 100), Is.EqualTo(0));
            Assert.That(Utilities.CalculateAccuracyRatio(750, 750), Is.EqualTo(1));
            Assert.That(Utilities.CalculateAccuracyRatio(750, 725), Is.EqualTo(0.5f));
        }

        [Test]
        public void TestCalculateBeatBars()
        {
            var tempoChanges = new Tempo[]
            {
                new() { Position = 0, BPM = 88000 }, new() { Position = 3840, BPM = 112000 },
                new() { Position = 9984, BPM = 89600 }, new() { Position = 22272, BPM = 112000 },
                new() { Position = 33792, BPM = 111500 }, new() { Position = 34560, BPM = 112000 },
                new() { Position = 42240, BPM = 111980 }
            };

            var beatBars = Utilities.CalculateBeatBars(tempoChanges);

            Assert.That(beatBars.Length, Is.EqualTo(440));
        }

        [Test]
        public void TestConvertSecondsToTicks()
        {
            const int seconds = 5;
            const int resolution = 192;

            var tempoChanges = new Tempo[]
            {
                new() { Position = 0, BPM = 88000 }, new() { Position = 3840, BPM = 112000 },
                new() { Position = 9984, BPM = 89600 }, new() { Position = 22272, BPM = 112000 },
                new() { Position = 33792, BPM = 111500 }, new() { Position = 34560, BPM = 112000 },
                new() { Position = 42240, BPM = 111980 }
            };

            var timeSignatureChanges = new TimeSignature[] { new() { Position = 0, Numerator = 4, Denominator = 2 } };

            var ticks = Utilities.ConvertSecondsToTicks(seconds, resolution, tempoChanges, timeSignatureChanges);

            Assert.That(ticks, Is.EqualTo(1408));
        }

        [Test]
        public void TestConvertTickToPosition()
        {
            const int tick = 1056;
            const int resolution = 192;

            var position = Utilities.ConvertTickToPosition(tick, resolution);

            Assert.That(position, Is.EqualTo(5.5f));
        }

        [Test]
        public void TestFindPositionsNearGivenTick()
        {
            var notes = new Note[]
            {
                new() { Position = 768 }, new() { Position = 960 }, new() { Position = 1152 },
                new() { Position = 1536 }, new() { Position = 1728 }, new() { Position = 1920 },
                new() { Position = 2304 }, new() { Position = 2496 }, new() { Position = 2688 },
                new() { Position = 3072 }, new() { Position = 3264 }
            };

            var foundPositions = Utilities.FindPositionsNearGivenTick(notes, 750);

            Assert.That(foundPositions, Is.Not.Empty);

            Assert.That(foundPositions[0].Position, Is.EqualTo(768));
        }

        [Test]
        public void TestFindPositionsNearGivenTickContinued()
        {
            var notes = new Note[]
            {
                new() { Position = 768 }, new() { Position = 960 }, new() { Position = 1152 },
                new() { Position = 1536 }, new() { Position = 1728 }, new() { Position = 1920 },
                new() { Position = 2304 }, new() { Position = 2496 }, new() { Position = 2688 },
                new() { Position = 3072 }, new() { Position = 3264 }
            };

            Assert.That(Utilities.FindPositionsNearGivenTick(notes, 100), Is.Empty);
            Assert.That(Utilities.FindPositionsNearGivenTick(notes, 750), Is.Not.Empty);
            Assert.That(Utilities.FindPositionsNearGivenTick(notes, 1500), Is.Not.Empty);
            Assert.That(Utilities.FindPositionsNearGivenTick(notes, 3200), Is.Empty);
        }

        [Test]
        public void TestIsOnTheBeat()
        {
            const int bpm = 120;
            const float currentTime = 10f;
            const float delta = 0.05f;

            var isOnTheBeat = Utilities.IsOnTheBeat(bpm, currentTime, delta);

            Assert.That(isOnTheBeat, Is.True);
        }

        [Test]
        public void TestIsOnTheBeatContinued()
        {
            Assert.That(Utilities.IsOnTheBeat(120, 10), Is.True);
            Assert.That(Utilities.IsOnTheBeat(60, 1), Is.True);
            Assert.That(Utilities.IsOnTheBeat(60, 1.5f), Is.False);
        }

        [Test]
        public void TestRoundUpToTheNearestMultiplier()
        {
            var value = Utilities.RoundUpToTheNearestMultiplier(12, 10);

            Assert.That(value, Is.EqualTo(20));
        }

    }

}
