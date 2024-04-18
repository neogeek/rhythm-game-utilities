using NUnit.Framework;

namespace RhythmGameUtilities.Tests
{

    public class UtilitiesTest
    {

        [Test]
        public void TestConvertTicksToSeconds()
        {
            const int tick = 2784;
            const int resolution = 192;
            const int bpm = 124;

            Assert.That(Utilities.ConvertTicksToSeconds(tick, resolution, bpm), Is.EqualTo(7.01f).Within(0.01f));
        }

        [Test]
        public void TestConvertSecondsToTicks()
        {
            const float seconds = 7.01f;
            const int resolution = 192;
            const int bpm = 124;

            Assert.That(Utilities.ConvertSecondsToTicks(seconds, resolution, bpm), Is.EqualTo(2781));
        }

        [Test]
        public void TestCalculateNoteHitAccuracy()
        {
            var note = new Note { Position = 2884 };

            const int buffer = 60;

            Assert.That(Utilities.CalculateNoteHitAccuracy(ref note, buffer, note.Position - buffer),
                Is.EqualTo(0));

            Assert.That(Utilities.CalculateNoteHitAccuracy(ref note, buffer, note.Position - buffer / 2),
                Is.EqualTo(0.5f));

            Assert.That(Utilities.CalculateNoteHitAccuracy(ref note, buffer, note.Position + buffer),
                Is.EqualTo(0));

            Assert.That(Utilities.CalculateNoteHitAccuracy(ref note, buffer, note.Position + buffer / 2),
                Is.EqualTo(0.5f));

            Assert.That(Utilities.CalculateNoteHitAccuracy(ref note, buffer, note.Position), Is.EqualTo(1));
        }

        [Test]
        public void TestCalculateScale()
        {
            const int baseBpm = 160;
            const float speed = 5;

            Assert.That(Utilities.CalculateScale(baseBpm, 160, speed), Is.EqualTo(5.0f));
            Assert.That(Utilities.CalculateScale(baseBpm, 120, speed), Is.EqualTo(3.75f));
        }

        [Test]
        public void TestIsOnTheBeat()
        {
            Assert.That(Utilities.IsOnTheBeat(120, 10), Is.True);
            Assert.That(Utilities.IsOnTheBeat(60, 1), Is.True);
            Assert.That(Utilities.IsOnTheBeat(60, 1.5f), Is.False);
        }

        [Test]
        public void TestLerp()
        {
            Assert.That(Utilities.Lerp(0, 10, 0), Is.EqualTo(0));
            Assert.That(Utilities.Lerp(0, 10, 0.5f), Is.EqualTo(5));
            Assert.That(Utilities.Lerp(0, 10, 1), Is.EqualTo(10));
        }

        [Test]
        public void TestInverseLerp()
        {
            Assert.That(Utilities.InverseLerp(0, 10, 0), Is.EqualTo(0));
            Assert.That(Utilities.InverseLerp(0, 10, 5), Is.EqualTo(0.5f));
            Assert.That(Utilities.InverseLerp(0, 10, 10), Is.EqualTo(1));
        }

    }

}
