using System;
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

            Assert.That(MathF.Abs(value), Is.EqualTo(0.36f).Within(double.Epsilon));
        }

        [Test]
        public void TestCalculateAccuracyRatioContinued()
        {
            Assert.That(Utilities.CalculateAccuracyRatio(750, 725), Is.EqualTo(0.5f));
            Assert.That(Utilities.CalculateAccuracyRatio(750, 750), Is.EqualTo(0));
            Assert.That(Utilities.CalculateAccuracyRatio(750, 775), Is.EqualTo(-0.5f));
        }

        [Test]
        public void TestCalculateAccuracy()
        {
            Assert.That(Utilities.CalculateAccuracy(750, 695), Is.EqualTo(Accuracy.Invalid));
            Assert.That(Utilities.CalculateAccuracy(750, 700), Is.EqualTo(Accuracy.Poor));
            Assert.That(Utilities.CalculateAccuracy(750, 710), Is.EqualTo(Accuracy.Fair));
            Assert.That(Utilities.CalculateAccuracy(750, 725), Is.EqualTo(Accuracy.Good));
            Assert.That(Utilities.CalculateAccuracy(750, 735), Is.EqualTo(Accuracy.Great));
            Assert.That(Utilities.CalculateAccuracy(750, 750), Is.EqualTo(Accuracy.Perfect));
            Assert.That(Utilities.CalculateAccuracy(750, 765), Is.EqualTo(Accuracy.Great));
            Assert.That(Utilities.CalculateAccuracy(750, 775), Is.EqualTo(Accuracy.Good));
            Assert.That(Utilities.CalculateAccuracy(750, 790), Is.EqualTo(Accuracy.Fair));
            Assert.That(Utilities.CalculateAccuracy(750, 800), Is.EqualTo(Accuracy.Poor));
            Assert.That(Utilities.CalculateAccuracy(750, 805), Is.EqualTo(Accuracy.Invalid));
        }

        [Test]
        public void TestCalculateTiming()
        {
            Assert.That(Utilities.CalculateTiming(750, 725), Is.EqualTo(Timing.Early));
            Assert.That(Utilities.CalculateTiming(750, 750), Is.EqualTo(Timing.Hit));
            Assert.That(Utilities.CalculateTiming(750, 775), Is.EqualTo(Timing.Late));
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
        public void TestFindNotesNearGivenTick()
        {
            var notes = new Note[]
            {
                new() { Position = 110 }, new() { Position = 120 }, new() { Position = 130 },
                new() { Position = 140 }, new() { Position = 150 }, new() { Position = 160 },
                new() { Position = 170 }, new() { Position = 180 }, new() { Position = 190 },
                new() { Position = 200 }
            };

            var foundNotes = Utilities.FindNotesNearGivenTick(notes, 160, 20);

            Assert.That(foundNotes.Length, Is.EqualTo(5));

            Assert.That(foundNotes[0].Position, Is.EqualTo(140));
            Assert.That(foundNotes[1].Position, Is.EqualTo(150));
            Assert.That(foundNotes[2].Position, Is.EqualTo(160));
            Assert.That(foundNotes[3].Position, Is.EqualTo(170));
            Assert.That(foundNotes[4].Position, Is.EqualTo(180));
        }

        [Test]
        public void TestFindNotesNearGivenTickContinued()
        {
            var notes = new Note[]
            {
                new() { Position = 110 }, new() { Position = 120 }, new() { Position = 130 },
                new() { Position = 140 }, new() { Position = 150 }, new() { Position = 160 },
                new() { Position = 170 }, new() { Position = 180 }, new() { Position = 190 },
                new() { Position = 200 }
            };

            Assert.That(Utilities.FindNotesNearGivenTick(notes, 50, 20), Is.Empty);
            Assert.That(Utilities.FindNotesNearGivenTick(notes, 130, 20)[0].Position, Is.EqualTo(110));
            Assert.That(Utilities.FindNotesNearGivenTick(notes, 190, 20)[0].Position, Is.EqualTo(170));
            Assert.That(Utilities.FindNotesNearGivenTick(notes, 300, 20), Is.Empty);
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
