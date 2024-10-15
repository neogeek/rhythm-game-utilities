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
        public static extern float CalculateAccuracyRatio(int position, int currentPosition, int delta);

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

        /// <summary>
        /// Convert a tick to a 2D/3D position.
        /// </summary>
        ///
        /// <param name="tick">The tick.</param>
        /// <param name="resolution">The resolution of the song.</param>
        public static float ConvertTickToPosition(float tick, int resolution)
        {
            return UtilitiesInternal.ConvertTickToPosition(tick, resolution);
        }

        /// <summary>
        /// Convert seconds to ticks.
        /// </summary>
        ///
        /// <param name="seconds">The seconds to generate ticks with.</param>
        /// <param name="resolution">The resolution of the song.</param>
        /// <param name="bpmChanges">All BPM changes within the song.</param>
        public static int ConvertSecondsToTicks(float seconds, int resolution, Dictionary<int, int> bpmChanges)
        {
            return UtilitiesInternal.ConvertSecondsToTicksInternal(seconds, resolution, bpmChanges.Keys.ToArray(),
                bpmChanges.Values.ToArray(), bpmChanges.Count);
        }

        /// <summary>
        /// Checks to see if the current time of a game or audio file is on the beat.
        /// </summary>
        ///
        /// <param name="bpm">The base BPM for a song.</param>
        /// <param name="currentTime">A timestamp to compare to the BPM.</param>
        public static bool IsOnTheBeat(float bpm, float currentTime)
        {
            return UtilitiesInternal.IsOnTheBeat(bpm, currentTime);
        }

        /// <summary>
        /// Rounds a value up the nearest multiplier.
        /// </summary>
        ///
        /// <param name="value">The value to round.</param>
        /// <param name="multiplier">The multiplier to round using.</param>
        public static int RoundUpToTheNearestMultiplier(int value, int multiplier)
        {
            return UtilitiesInternal.RoundUpToTheNearestMultiplier(value, multiplier);
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

            Marshal.FreeHGlobal(ptrArray);

            return beatBars;
        }

        public static Note? FindPositionNearGivenTick(List<Note> notes, int tick, int delta = 50)
        {
            var left = 0;
            var right = notes.Count - 1;

            while (left <= right)
            {
                var mid = (left + right) / 2;

                var currentPosition = notes[mid].Position;

                if (currentPosition + delta < tick)
                {
                    left = mid + 1;
                }
                else if (currentPosition - delta > tick)
                {
                    right = mid - 1;
                }
                else
                {
                    return notes[mid];
                }
            }

            return null;
        }

        /// <summary>
        /// Calculated the accuracy ratio of the current position against a static position.
        /// </summary>
        ///
        /// <param name="position">The position to test against.</param>
        /// <param name="currentPosition">The current position.</param>
        /// <param name="delta">The plus/minus delta to test the current position against.</param>
        public static float CalculateAccuracyRatio(int position, int currentPosition, int delta = 50)
        {
            return UtilitiesInternal.CalculateAccuracyRatio(position, currentPosition, delta);
        }

    }

}
