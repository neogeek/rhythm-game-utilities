using System;
using System.Runtime.InteropServices;

namespace RhythmGameUtilities
{

    internal static class AudioInternal
    {

        [DllImport("libRhythmGameUtilities", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ConvertSamplesToWaveform(float[] samples, int size, int width, int height);

        [DllImport("libRhythmGameUtilities", CallingConvention = CallingConvention.Cdecl)]
        public static extern void FreeWaveform(IntPtr waveform, int width);

    }

    public static class Audio
    {

        /// <summary>
        ///     Converts samples from an audio file into data used to display a waveform.
        /// </summary>
        /// <param name="samples">Array of sample data from an audio file.</param>
        /// <param name="width">Width of the waveform.</param>
        /// <param name="height">Height of the waveform.</param>
        public static int[][] ConvertSamplesToWaveform(float[] samples, int width, int height)
        {
            var ptr = AudioInternal.ConvertSamplesToWaveform(samples, samples.Length, width, height);

            var waveform = new int[width][];

            for (var x = 0; x < width; x += 1)
            {
                var innerPtr = Marshal.ReadIntPtr(ptr, x * IntPtr.Size);

                waveform[x] = new int[height];

                Marshal.Copy(innerPtr, waveform[x], 0, height);
            }

            AudioInternal.FreeWaveform(ptr, width);

            return waveform;
        }

    }

}
