using System;

namespace RhythmGameUtilities
{

    public static class Audio
    {

        /// <summary>
        /// Converts samples from an audio file into data used to display a waveform.
        /// </summary>
        ///
        /// <param name="samples">Array of sample data from an audio file.</param>
        /// <param name="width">Width of the waveform.</param>
        /// <param name="height">Height of the waveform.</param>
        public static int[][] ConvertSamplesToWaveform(float[] samples, int width, int height)
        {
            var waveform = new int[width][];

            var step = Math.Floor((double)samples.Length / width);
            var amp = height / 2;

            for (var x = 0; x < width; x += 1)
            {
                waveform[x] = new int[height];

                var min = 1.0f;
                var max = -1.0f;

                for (var j = 0; j < step; j += 1)
                {
                    var index = (int)(x * step + j);

                    var datum = samples[index];

                    if (datum < min)
                    {
                        min = datum;
                    }

                    if (datum > max)
                    {
                        max = datum;
                    }
                }

                var minY = (int)((1 + min) * amp);
                var maxY = (int)((1 + max) * amp);

                for (var y = 0; y < height; y += 1)
                {
                    waveform[x][y] = y >= minY && y <= maxY ? 1 : 0;
                }
            }

            return waveform;
        }

    }

}
