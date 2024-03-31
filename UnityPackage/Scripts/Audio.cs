using System;
using System.Runtime.InteropServices;

namespace RhythmGameUtilities
{

    internal static class AudioInternal
    {

#if WINDOWS_BUILD || UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN
        [DllImport("libRhythmGameUtilities.dll", CallingConvention = CallingConvention.Cdecl)]
#else
        [DllImport("libRhythmGameUtilities.dylib", CallingConvention = CallingConvention.Cdecl)]
#endif
        public static extern IntPtr ConvertSamplesToWaveform(float[] samples, int size, int width, int height);

    }

    public static class Audio
    {

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

            return waveform;
        }

    }

}
