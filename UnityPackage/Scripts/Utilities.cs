using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;

namespace RhythmGameUtilities
{

    internal static class UtilitiesInternal
    {

        [DllImport("libRhythmGameUtilities", CallingConvention = CallingConvention.Cdecl)]
        public static extern float ConvertTickToPosition(int tick, int resolution);

        [DllImport("libRhythmGameUtilities", CallingConvention = CallingConvention.Cdecl)]
        public static extern int ConvertSecondsToTicksInternal(float seconds, int resolution, int[] bpmChangesKeys,
            int[] bpmChangesValues, int bpmChangesSize, TimeSignature[] timeSignatures, int timeSignaturesSize);

        [DllImport("libRhythmGameUtilities", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool IsOnTheBeat(int bpm, float currentTime, float delta);

        [DllImport("libRhythmGameUtilities", CallingConvention = CallingConvention.Cdecl)]
        public static extern int RoundUpToTheNearestMultiplier(int value, int multiplier);

        [DllImport("libRhythmGameUtilities", CallingConvention = CallingConvention.Cdecl)]
        public static extern float CalculateAccuracyRatio(int position, int currentPosition, int delta);

        [DllImport("libRhythmGameUtilities", CallingConvention = CallingConvention.Cdecl)]
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
        public static float ConvertTickToPosition(int tick, int resolution)
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
        /// <param name="timeSignatureChanges">All time signature changes within the song.</param>
        public static int ConvertSecondsToTicks(float seconds, int resolution, Dictionary<int, int> bpmChanges,
            TimeSignature[] timeSignatureChanges)
        {
            return UtilitiesInternal.ConvertSecondsToTicksInternal(seconds, resolution, bpmChanges.Keys.ToArray(),
                bpmChanges.Values.ToArray(), bpmChanges.Count, timeSignatureChanges, timeSignatureChanges.Length);
        }

        /// <summary>
        /// Checks to see if the current time of a game or audio file is on the beat.
        /// </summary>
        ///
        /// <param name="bpm">The base BPM for a song.</param>
        /// <param name="currentTime">A timestamp to compare to the BPM.</param>
        /// <param name="delta">The plus/minus delta to test the current time against.</param>
        public static bool IsOnTheBeat(int bpm, float currentTime, float delta = 0.05f)
        {
            return UtilitiesInternal.IsOnTheBeat(bpm, currentTime, delta);
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

        public static BeatBar[] CalculateBeatBars(Dictionary<int, int> bpmChanges, int resolution = 192, int ts = 4,
            bool includeHalfNotes = true)
        {

            var ptrArray = UtilitiesInternal.CalculateBeatBarsInternal(bpmChanges.Keys.ToArray(),
                bpmChanges.Values.ToArray(), bpmChanges.Count, resolution, ts, includeHalfNotes,
                out var size);

            var beatBarSize = Marshal.SizeOf(typeof(BeatBar));

            var beatBars = new BeatBar[size];

            for (var i = 0; i < size; i += 1)
            {
                var beatBarSizePtr = new IntPtr(ptrArray.ToInt64() + beatBarSize * i);
                var beatBar = Marshal.PtrToStructure<BeatBar>(beatBarSizePtr);

                beatBars[i] = beatBar;
            }

            Marshal.FreeHGlobal(ptrArray);

            return beatBars;
        }

        public static Note? FindPositionNearGivenTick(Note[] notes, int tick, int delta = 50)
        {
            var left = 0;
            var right = notes.Length - 1;

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
