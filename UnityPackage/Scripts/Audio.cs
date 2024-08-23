using System;
using System.Runtime.InteropServices;

namespace RhythmGameUtilities
{

    internal static class AudioInternal
    {

#if WINDOWS_BUILD || UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN
        [DllImport("libRhythmGameUtilities.dll", CallingConvention = CallingConvention.Cdecl)]
#elif MACOS_BUILD || UNITY_EDITOR_OSX || UNITY_STANDALONE_OSX
        [DllImport("libRhythmGameUtilities.dylib", CallingConvention = CallingConvention.Cdecl)]
#elif LINUX_BUILD || UNITY_EDITOR_LINUX || UNITY_STANDALONE_LINUX
        [DllImport("libRhythmGameUtilities.so", CallingConvention = CallingConvention.Cdecl)]
#endif
        public static extern IntPtr ConvertSamplesToWaveform(float[] samples, int size, int width, int height);

#if WINDOWS_BUILD || UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN
        [DllImport("libRhythmGameUtilities.dll", CallingConvention = CallingConvention.Cdecl)]
#elif MACOS_BUILD || UNITY_EDITOR_OSX || UNITY_STANDALONE_OSX
        [DllImport("libRhythmGameUtilities.dylib", CallingConvention = CallingConvention.Cdecl)]
#elif LINUX_BUILD || UNITY_EDITOR_LINUX || UNITY_STANDALONE_LINUX
        [DllImport("libRhythmGameUtilities.so", CallingConvention = CallingConvention.Cdecl)]
#endif
        public static extern void FreeWaveform(IntPtr waveform, int width);

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

            AudioInternal.FreeWaveform(ptr, width);

            return waveform;
        }

    }

}
