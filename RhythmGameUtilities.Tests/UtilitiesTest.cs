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

            Assert.That(
                Utilities.ConvertSecondsToTicks(seconds, resolution,
                    new Dictionary<int, int>
                    {
                        { 0, 88000 },
                        { 3840, 112000 },
                        { 9984, 89600 },
                        { 22272, 112000 },
                        { 33792, 111500 },
                        { 34560, 112000 },
                        { 42240, 111980 }
                    }), Is.EqualTo(1408));
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
