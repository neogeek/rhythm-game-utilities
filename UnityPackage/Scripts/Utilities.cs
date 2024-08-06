using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;

namespace RhythmGameUtilities
{

    internal static class UtilitiesInternal
    {

#if WINDOWS_BUILD || UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN
        [DllImport("libRhythmGameUtilities.dll", CallingConvention = CallingConvention.Cdecl)]
#elif MACOS_BUILD || UNITY_EDITOR_OSX || UNITY_STANDALONE_OSX
        [DllImport("libRhythmGameUtilities.dylib", CallingConvention = CallingConvention.Cdecl)]
#elif LINUX_BUILD || UNITY_EDITOR_LINUX || UNITY_STANDALONE_LINUX
        [DllImport("libRhythmGameUtilities.so", CallingConvention = CallingConvention.Cdecl)]
#endif
        public static extern float ConvertTickToPosition(float tick, int resolution);

#if WINDOWS_BUILD || UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN
        [DllImport("libRhythmGameUtilities.dll", CallingConvention = CallingConvention.Cdecl)]
#elif MACOS_BUILD || UNITY_EDITOR_OSX || UNITY_STANDALONE_OSX
        [DllImport("libRhythmGameUtilities.dylib", CallingConvention = CallingConvention.Cdecl)]
#elif LINUX_BUILD || UNITY_EDITOR_LINUX || UNITY_STANDALONE_LINUX
        [DllImport("libRhythmGameUtilities.so", CallingConvention = CallingConvention.Cdecl)]
#endif
        public static extern int ConvertSecondsToTicksInternal(float seconds, int resolution, int[] bpmChangesKeys,
            int[] bpmChangesValues, int bpmChangesSize);

#if WINDOWS_BUILD || UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN
        [DllImport("libRhythmGameUtilities.dll", CallingConvention = CallingConvention.Cdecl)]
#elif MACOS_BUILD || UNITY_EDITOR_OSX || UNITY_STANDALONE_OSX
        [DllImport("libRhythmGameUtilities.dylib", CallingConvention = CallingConvention.Cdecl)]
#elif LINUX_BUILD || UNITY_EDITOR_LINUX || UNITY_STANDALONE_LINUX
        [DllImport("libRhythmGameUtilities.so", CallingConvention = CallingConvention.Cdecl)]
#endif
        public static extern bool IsOnTheBeat(float bpm, float currentTime);

#if WINDOWS_BUILD || UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN
        [DllImport("libRhythmGameUtilities.dll", CallingConvention = CallingConvention.Cdecl)]
#elif MACOS_BUILD || UNITY_EDITOR_OSX || UNITY_STANDALONE_OSX
        [DllImport("libRhythmGameUtilities.dylib", CallingConvention = CallingConvention.Cdecl)]
#elif LINUX_BUILD || UNITY_EDITOR_LINUX || UNITY_STANDALONE_LINUX
        [DllImport("libRhythmGameUtilities.so", CallingConvention = CallingConvention.Cdecl)]
#endif
        public static extern int RoundUpToTheNearestMultiplier(int value, int multiplier);

#if WINDOWS_BUILD || UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN
        [DllImport("libRhythmGameUtilities.dll", CallingConvention = CallingConvention.Cdecl)]
#elif MACOS_BUILD || UNITY_EDITOR_OSX || UNITY_STANDALONE_OSX
        [DllImport("libRhythmGameUtilities.dylib", CallingConvention = CallingConvention.Cdecl)]
#elif LINUX_BUILD || UNITY_EDITOR_LINUX || UNITY_STANDALONE_LINUX
        [DllImport("libRhythmGameUtilities.so", CallingConvention = CallingConvention.Cdecl)]
#endif
        public static extern float Lerp(float a, float b, float t);

#if WINDOWS_BUILD || UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN
        [DllImport("libRhythmGameUtilities.dll", CallingConvention = CallingConvention.Cdecl)]
#elif MACOS_BUILD || UNITY_EDITOR_OSX || UNITY_STANDALONE_OSX
        [DllImport("libRhythmGameUtilities.dylib", CallingConvention = CallingConvention.Cdecl)]
#elif LINUX_BUILD || UNITY_EDITOR_LINUX || UNITY_STANDALONE_LINUX
        [DllImport("libRhythmGameUtilities.so", CallingConvention = CallingConvention.Cdecl)]
#endif
        public static extern float InverseLerp(float a, float b, float v);

#if WINDOWS_BUILD || UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN
        [DllImport("libRhythmGameUtilities.dll", CallingConvention = CallingConvention.Cdecl)]
#elif MACOS_BUILD || UNITY_EDITOR_OSX || UNITY_STANDALONE_OSX
        [DllImport("libRhythmGameUtilities.dylib", CallingConvention = CallingConvention.Cdecl)]
#elif LINUX_BUILD || UNITY_EDITOR_LINUX || UNITY_STANDALONE_LINUX
        [DllImport("libRhythmGameUtilities.so", CallingConvention = CallingConvention.Cdecl)]
#endif
        public static extern IntPtr CalculateBeatBarsInternal(int[] bpmChangesKeys,
            int[] bpmChangesValues, int bpmChangesSize, int resolution, int ts,
            bool includeHalfNotes, out int size);

    }

    public static class Utilities
    {

        public const float SECONDS_PER_MINUTE = 60.0f;

        public static float ConvertTickToPosition(float tick, int resolution)
        {
            return UtilitiesInternal.ConvertTickToPosition(tick, resolution);
        }

        public static int ConvertSecondsToTicks(float seconds, int resolution, Dictionary<int, int> bpmChanges)
        {
            return UtilitiesInternal.ConvertSecondsToTicksInternal(seconds, resolution, bpmChanges.Keys.ToArray(),
                bpmChanges.Values.ToArray(), bpmChanges.Count);
        }

        public static bool IsOnTheBeat(float bpm, float currentTime)
        {
            return UtilitiesInternal.IsOnTheBeat(bpm, currentTime);
        }

        public static int RoundUpToTheNearestMultiplier(int value, int multiplier)
        {
            return UtilitiesInternal.RoundUpToTheNearestMultiplier(value, multiplier);
        }

        public static float Lerp(float a, float b, float t)
        {
            return UtilitiesInternal.Lerp(a, b, t);
        }

        public static float InverseLerp(float a, float b, float v)
        {
            return UtilitiesInternal.InverseLerp(a, b, v);
        }

        public static List<BeatBar> CalculateBeatBars(Dictionary<int, int> bpmChanges, int resolution = 192, int ts = 4,
            bool includeHalfNotes = true)
        {
            var beatBars = new List<BeatBar>();

            var ptrArray = UtilitiesInternal.CalculateBeatBarsInternal(bpmChanges.Keys.ToArray(),
                bpmChanges.Values.ToArray(), bpmChanges.Count, resolution, ts, includeHalfNotes,
                out var size);

            var beatBarSize = Marshal.SizeOf(typeof(BeatBar));

            for (var i = 0; i < size; i += 1)
            {
                var beatBarSizePtr = new IntPtr(ptrArray.ToInt64() + beatBarSize * i);
                var beatBar = Marshal.PtrToStructure<BeatBar>(beatBarSizePtr);

                beatBars.Add(beatBar);
            }

            return beatBars;
        }

    }

}
