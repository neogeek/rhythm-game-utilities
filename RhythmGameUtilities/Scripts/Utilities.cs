using System;
using System.Runtime.InteropServices;

namespace RhythmGameUtilities
{

    internal static class UtilitiesInternal
    {

#if UNITY_WEBGL && !UNITY_EDITOR
        [DllImport("__Internal")]
#else
        [DllImport("libRhythmGameUtilities", CallingConvention = CallingConvention.Cdecl)]
#endif
        public static extern float ConvertTickToPosition(int tick, int resolution);

#if UNITY_WEBGL && !UNITY_EDITOR
        [DllImport("__Internal")]
#else
        [DllImport("libRhythmGameUtilities", CallingConvention = CallingConvention.Cdecl)]
#endif
        public static extern int ConvertSecondsToTicksInternal(float seconds, int resolution, Tempo[] tempoChanges,
            int tempoChangesSize, TimeSignature[] timeSignatures, int timeSignaturesSize);

#if UNITY_WEBGL && !UNITY_EDITOR
        [DllImport("__Internal")]
#else
        [DllImport("libRhythmGameUtilities", CallingConvention = CallingConvention.Cdecl)]
#endif
        [return : MarshalAs(UnmanagedType.I1)]
        public static extern bool IsOnTheBeat(int bpm, float currentTime, float delta);

#if UNITY_WEBGL && !UNITY_EDITOR
        [DllImport("__Internal")]
#else
        [DllImport("libRhythmGameUtilities", CallingConvention = CallingConvention.Cdecl)]
#endif
        public static extern int RoundUpToTheNearestMultiplier(int value, int multiplier);

#if UNITY_WEBGL && !UNITY_EDITOR
        [DllImport("__Internal")]
#else
        [DllImport("libRhythmGameUtilities", CallingConvention = CallingConvention.Cdecl)]
#endif
        public static extern float CalculateAccuracyRatio(int position, int currentPosition, int delta);

#if UNITY_WEBGL && !UNITY_EDITOR
        [DllImport("__Internal")]
#else
        [DllImport("libRhythmGameUtilities", CallingConvention = CallingConvention.Cdecl)]
#endif
        public static extern IntPtr CalculateBeatBarsInternal(Tempo[] tempoChanges, int tempoChangesSize,
            int resolution,
            int ts,
            bool includeHalfNotes, out int size);

#if UNITY_WEBGL && !UNITY_EDITOR
        [DllImport("__Internal")]
#else
        [DllImport("libRhythmGameUtilities", CallingConvention = CallingConvention.Cdecl)]
#endif
        public static extern IntPtr FindPositionsNearGivenTickInternal(Note[] notes, int notesSize,
            int tick,
            int delta,
            out int size);

    }

    public static class Utilities
    {

        public const float SECONDS_PER_MINUTE = 60.0f;

        /// <summary>
        ///     Convert a tick to a 2D/3D position.
        /// </summary>
        /// <param name="tick">The tick.</param>
        /// <param name="resolution">The resolution of the song.</param>
        public static float ConvertTickToPosition(int tick, int resolution)
        {
            return UtilitiesInternal.ConvertTickToPosition(tick, resolution);
        }

        /// <summary>
        ///     Convert seconds to ticks.
        /// </summary>
        /// <param name="seconds">The seconds to generate ticks with.</param>
        /// <param name="resolution">The resolution of the song.</param>
        /// <param name="tempoChanges">All tempo changes within the song.</param>
        /// <param name="timeSignatureChanges">All time signature changes within the song.</param>
        public static int ConvertSecondsToTicks(float seconds, int resolution, Tempo[] tempoChanges,
            TimeSignature[] timeSignatureChanges)
        {
            return UtilitiesInternal.ConvertSecondsToTicksInternal(seconds, resolution, tempoChanges,
                tempoChanges.Length,
                timeSignatureChanges, timeSignatureChanges.Length);
        }

        /// <summary>
        ///     Checks to see if the current time of a game or audio file is on the beat.
        /// </summary>
        /// <param name="bpm">The base BPM for a song.</param>
        /// <param name="currentTime">A timestamp to compare to the BPM.</param>
        /// <param name="delta">The plus/minus delta to test the current time against.</param>
        public static bool IsOnTheBeat(int bpm, float currentTime, float delta = 0.05f)
        {
            return UtilitiesInternal.IsOnTheBeat(bpm, currentTime, delta);
        }

        /// <summary>
        ///     Rounds a value up the nearest multiplier.
        /// </summary>
        /// <param name="value">The value to round.</param>
        /// <param name="multiplier">The multiplier to round using.</param>
        public static int RoundUpToTheNearestMultiplier(int value, int multiplier)
        {
            return UtilitiesInternal.RoundUpToTheNearestMultiplier(value, multiplier);
        }

        public static BeatBar[] CalculateBeatBars(Tempo[] tempoChanges, int resolution = 192, int ts = 4,
            bool includeHalfNotes = true)
        {
            var ptrArray = UtilitiesInternal.CalculateBeatBarsInternal(tempoChanges, tempoChanges.Length, resolution,
                ts,
                includeHalfNotes,
                out var size);

            var beatBars = InternalUtilities.CaptureArrayFromInternalMethod<BeatBar>(ptrArray, size);

            InternalUtilities.FreeBeatBars(ptrArray);

            return beatBars;
        }

        public static Note[] FindPositionsNearGivenTick(Note[] notes, int tick, int delta = 50)
        {
            var ptrArray = UtilitiesInternal.FindPositionsNearGivenTickInternal(notes, notes.Length, tick,
                delta,
                out var size);

            var foundPositions = InternalUtilities.CaptureArrayFromInternalMethod<Note>(ptrArray, size);

            InternalUtilities.FreeNotes(ptrArray);

            return foundPositions;
        }

        /// <summary>
        ///     Calculated the accuracy ratio of the current position against a static position.
        /// </summary>
        /// <param name="position">The position to test against.</param>
        /// <param name="currentPosition">The current position.</param>
        /// <param name="delta">The plus/minus delta to test the current position against.</param>
        public static float CalculateAccuracyRatio(int position, int currentPosition, int delta = 50)
        {
            return UtilitiesInternal.CalculateAccuracyRatio(position, currentPosition, delta);
        }

    }

}
