using System;
using System.Runtime.InteropServices;

namespace RhythmGameUtilities
{

    internal static class ChartInternal
    {

#if UNITY_WEBGL && !UNITY_EDITOR
        [DllImport("__Internal")]
#else
        [DllImport("libRhythmGameUtilities", CallingConvention = CallingConvention.Cdecl)]
#endif
        public static extern int ReadResolutionFromChartDataInternal(string contents, out int _);

#if UNITY_WEBGL && !UNITY_EDITOR
        [DllImport("__Internal")]
#else
        [DllImport("libRhythmGameUtilities", CallingConvention = CallingConvention.Cdecl)]
#endif
        public static extern IntPtr ReadTempoChangesFromChartDataInternal(string contents, out int _);

#if UNITY_WEBGL && !UNITY_EDITOR
        [DllImport("__Internal")]
#else
        [DllImport("libRhythmGameUtilities", CallingConvention = CallingConvention.Cdecl)]
#endif
        public static extern void FreeTempoChanges(IntPtr tempoChanges);

#if UNITY_WEBGL && !UNITY_EDITOR
        [DllImport("__Internal")]
#else
        [DllImport("libRhythmGameUtilities", CallingConvention = CallingConvention.Cdecl)]
#endif
        public static extern IntPtr ReadTimeSignatureChangesFromChartDataInternal(string contents, out int _);

#if UNITY_WEBGL && !UNITY_EDITOR
        [DllImport("__Internal")]
#else
        [DllImport("libRhythmGameUtilities", CallingConvention = CallingConvention.Cdecl)]
#endif
        public static extern void FreeTimeSignatureChanges(IntPtr tempoChanges);

#if UNITY_WEBGL && !UNITY_EDITOR
        [DllImport("__Internal")]
#else
        [DllImport("libRhythmGameUtilities", CallingConvention = CallingConvention.Cdecl)]
#endif
        public static extern IntPtr ReadNotesFromChartDataInternal(string contents, Difficulty difficulty, out int _);

#if UNITY_WEBGL && !UNITY_EDITOR
        [DllImport("__Internal")]
#else
        [DllImport("libRhythmGameUtilities", CallingConvention = CallingConvention.Cdecl)]
#endif
        public static extern void FreeNotes(IntPtr tempoChanges);

    }

    public static class Chart
    {

        public static int ReadResolutionFromChartData(string contents)
        {
            return ChartInternal.ReadResolutionFromChartDataInternal(contents, out var _);
        }

        public static Tempo[] ReadTempoChangesFromChartData(string contents)
        {
            var ptrArray = ChartInternal.ReadTempoChangesFromChartDataInternal(contents, out var size);

            var tempoChanges = InternalUtilities.CaptureArrayFromInternalMethod<Tempo>(ptrArray, size);

            ChartInternal.FreeTempoChanges(ptrArray);

            return tempoChanges;
        }

        public static TimeSignature[] ReadTimeSignatureChangesFromChartData(string contents)
        {
            var ptrArray =
                ChartInternal.ReadTimeSignatureChangesFromChartDataInternal(contents, out var size);

            var timeSignatureChanges = InternalUtilities.CaptureArrayFromInternalMethod<TimeSignature>(ptrArray, size);

            ChartInternal.FreeTimeSignatureChanges(ptrArray);

            return timeSignatureChanges;
        }

        public static Note[] ReadNotesFromChartData(string contents, Difficulty difficulty)
        {
            var ptrArray = ChartInternal.ReadNotesFromChartDataInternal(contents, difficulty, out var size);

            var notes = InternalUtilities.CaptureArrayFromInternalMethod<Note>(ptrArray, size);

            ChartInternal.FreeNotes(ptrArray);

            return notes;
        }

    }

}
