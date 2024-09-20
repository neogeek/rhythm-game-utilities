using NUnit.Framework;

namespace RhythmGameUtilities.Tests
{

    public class CommonTest
    {

        [Test]
        public void TestLerp()
        {
            Assert.That(Common.Lerp(0, 10, 0), Is.EqualTo(0));
            Assert.That(Common.Lerp(0, 10, 0.5f), Is.EqualTo(5));
            Assert.That(Common.Lerp(0, 10, 1), Is.EqualTo(10));
        }

        [Test]
        public void TestInverseLerp()
        {
            Assert.That(Common.InverseLerp(0, 10, 0), Is.EqualTo(0));
            Assert.That(Common.InverseLerp(0, 10, 5), Is.EqualTo(0.5f));
            Assert.That(Common.InverseLerp(0, 10, 10), Is.EqualTo(1));
        }

    }

}
