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

            var keyValuePairs = GenerateAdjacentKeyPairs(bpmChanges);

            foreach (var (startTick, endTick) in keyValuePairs)
            {
                for (var tick = startTick; tick <= endTick; tick += resolution)
                {
                    beatBars.Add(new BeatBar
                    {
                        Position = tick, BPM = bpmChanges[startTick], TimeSignature = new[] { ts }
                    });

                    if (includeHalfNotes && tick != endTick)
                    {
                        beatBars.Add(new BeatBar
                        {
                            Position = tick + resolution / 2,
                            BPM = bpmChanges[startTick],
                            TimeSignature = new[] { ts }
                        });
                    }
                }
            }

            return beatBars;
        }

        public static List<Tuple<T, T>> GenerateAdjacentKeyPairs<T>(Dictionary<T, T> dictionary)
        {
            var keys = dictionary.Keys.ToList();

            keys.Sort();

            var adjacentKeyPairs = new List<Tuple<T, T>>();

            for (var i = 0; i < keys.Count - 1; i += 1)
            {
                adjacentKeyPairs.Add(new Tuple<T, T>(keys[i], keys[i + 1]));
            }

            return adjacentKeyPairs;
        }

    }

}
