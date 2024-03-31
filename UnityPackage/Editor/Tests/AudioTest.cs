using NUnit.Framework;

namespace RhythmGameUtilities.Tests
{

    public class AudioTest
    {

        [Test]
        public void TestConvertTicksToSeconds()
        {
            var samples = new float[] { 1, 2, 3, 4, 5 };
            const int width = 100;
            const int height = 100;

            var waveform = Audio.ConvertSamplesToWaveform(samples, width, height);

            Assert.That(waveform.Length, Is.EqualTo(width));
            Assert.That(waveform[0].Length, Is.EqualTo(height));
        }

    }

}
