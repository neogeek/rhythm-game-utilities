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
