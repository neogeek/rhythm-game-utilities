using System;
using System.Collections.Generic;
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
            var tempoChanges = new List<Tempo>();

            var ptrArray = ChartInternal.ReadTempoChangesFromChartDataInternal(contents, out var size);

            var tempoSize = Marshal.SizeOf(typeof(Tempo));

            for (var i = 0; i < size; i += 1)
            {
                var noteSizePtr = new IntPtr(ptrArray.ToInt64() + tempoSize * i);
                var tempoChange = Marshal.PtrToStructure<Tempo>(noteSizePtr);

                tempoChanges.Add(tempoChange);
            }

            ChartInternal.FreeTempoChanges(ptrArray);

            return tempoChanges.ToArray();
        }

        public static TimeSignature[] ReadTimeSignatureChangesFromChartData(string contents)
        {
            var timeSignatureChanges = new List<TimeSignature>();

            var ptrArray =
                ChartInternal.ReadTimeSignatureChangesFromChartDataInternal(contents, out var size);

            var timeSignatureSize = Marshal.SizeOf(typeof(TimeSignature));

            for (var i = 0; i < size; i += 1)
            {
                var noteSizePtr = new IntPtr(ptrArray.ToInt64() + timeSignatureSize * i);
                var note = Marshal.PtrToStructure<TimeSignature>(noteSizePtr);

                timeSignatureChanges.Add(note);
            }

            ChartInternal.FreeTimeSignatureChanges(ptrArray);

            return timeSignatureChanges.ToArray();
        }

        public static Note[] ReadNotesFromChartData(string contents, Difficulty difficulty)
        {
            var notes = new List<Note>();

            var ptrArray = ChartInternal.ReadNotesFromChartDataInternal(contents, difficulty, out var size);

            var noteSize = Marshal.SizeOf(typeof(Note));

            for (var i = 0; i < size; i += 1)
            {
                var noteSizePtr = new IntPtr(ptrArray.ToInt64() + noteSize * i);
                var note = Marshal.PtrToStructure<Note>(noteSizePtr);

                notes.Add(note);
            }

            ChartInternal.FreeNotes(ptrArray);

            return notes.ToArray();
        }

    }

}
