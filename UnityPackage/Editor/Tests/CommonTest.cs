using NUnit.Framework;

namespace RhythmGameUtilities.Tests
{

    public class CommonTest
    {

        [Test]
        public void TestInverseLerp()
        {
            var value = Common.InverseLerp(0, 10, 5);

            Assert.That(value, Is.EqualTo(0.5f));
        }

        [Test]
        public void TestInverseLerpContinued()
        {
            Assert.That(Common.InverseLerp(0, 10, 0), Is.EqualTo(0));
            Assert.That(Common.InverseLerp(0, 10, 5), Is.EqualTo(0.5f));
            Assert.That(Common.InverseLerp(0, 10, 10), Is.EqualTo(1));
        }

        [Test]
        public void TestLerp()
        {
            var value = Common.Lerp(0, 10, 0.5f);

            Assert.That(value, Is.EqualTo(5));
        }

        [Test]
        public void TestLerpContinued()
        {
            Assert.That(Common.Lerp(0, 10, 0), Is.EqualTo(0));
            Assert.That(Common.Lerp(0, 10, 0.5f), Is.EqualTo(5));
            Assert.That(Common.Lerp(0, 10, 1), Is.EqualTo(10));
        }

    }

}
