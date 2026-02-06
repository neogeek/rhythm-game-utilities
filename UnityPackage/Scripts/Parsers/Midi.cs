using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace RhythmGameUtilities
{

    internal static class MidiInternal
    {

#if UNITY_WEBGL && !UNITY_EDITOR
        [DllImport("__Internal")]
#else
        [DllImport("libRhythmGameUtilities", CallingConvention = CallingConvention.Cdecl)]
#endif
        public static extern int ReadResolutionFromMidiDataInternal(byte[] bytes, int dataSize, out int size);

#if UNITY_WEBGL && !UNITY_EDITOR
        [DllImport("__Internal")]
#else
        [DllImport("libRhythmGameUtilities", CallingConvention = CallingConvention.Cdecl)]
#endif
        public static extern IntPtr ReadTempoChangesFromMidiDataInternal(byte[] bytes, int dataSize, out int size);

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
        public static extern IntPtr ReadTimeSignatureChangesFromMidiDataInternal(byte[] bytes, int dataSize,
            out int size);

#if UNITY_WEBGL && !UNITY_EDITOR
        [DllImport("__Internal")]
#else
        [DllImport("libRhythmGameUtilities", CallingConvention = CallingConvention.Cdecl)]
#endif
        public static extern void FreeTimeSignatureChanges(IntPtr timeSignatureChanges);

#if UNITY_WEBGL && !UNITY_EDITOR
        [DllImport("__Internal")]
#else
        [DllImport("libRhythmGameUtilities", CallingConvention = CallingConvention.Cdecl)]
#endif
        public static extern IntPtr ReadNotesFromMidiDataInternal(byte[] bytes, int dataSize, out int size);

#if UNITY_WEBGL && !UNITY_EDITOR
        [DllImport("__Internal")]
#else
        [DllImport("libRhythmGameUtilities", CallingConvention = CallingConvention.Cdecl)]
#endif
        public static extern void FreeNotes(IntPtr notes);

    }

    public static class Midi
    {

        public static int ReadResolutionFromMidiData(byte[] bytes)
        {
            return MidiInternal.ReadResolutionFromMidiDataInternal(bytes, bytes.Length, out var _);
        }

        public static Tempo[] ReadTempoChangesFromMidiData(byte[] bytes)
        {
            var tempoChanges = new List<Tempo>();

            var ptrArray = MidiInternal.ReadTempoChangesFromMidiDataInternal(bytes, bytes.Length, out var size);

            var tempoSize = Marshal.SizeOf(typeof(Tempo));

            for (var i = 0; i < size; i += 1)
            {
                var noteSizePtr = new IntPtr(ptrArray.ToInt64() + tempoSize * i);
                var tempoChange = Marshal.PtrToStructure<Tempo>(noteSizePtr);

                tempoChanges.Add(tempoChange);
            }

            MidiInternal.FreeTempoChanges(ptrArray);

            return tempoChanges.ToArray();
        }

        public static TimeSignature[] ReadTimeSignatureChangesFromMidiData(byte[] bytes)
        {
            var timeSignatureChanges = new List<TimeSignature>();

            var ptrArray = MidiInternal.ReadTimeSignatureChangesFromMidiDataInternal(bytes, bytes.Length, out var size);

            var timeSignatureSize = Marshal.SizeOf(typeof(TimeSignature));

            for (var i = 0; i < size; i += 1)
            {
                var noteSizePtr = new IntPtr(ptrArray.ToInt64() + timeSignatureSize * i);
                var note = Marshal.PtrToStructure<TimeSignature>(noteSizePtr);

                timeSignatureChanges.Add(note);
            }

            MidiInternal.FreeTimeSignatureChanges(ptrArray);

            return timeSignatureChanges.ToArray();
        }

        public static Note[] ReadNotesFromMidiData(byte[] bytes)
        {
            var notes = new List<Note>();

            var ptrArray = MidiInternal.ReadNotesFromMidiDataInternal(bytes, bytes.Length, out var size);

            var noteSize = Marshal.SizeOf(typeof(Note));

            for (var i = 0; i < size; i += 1)
            {
                var noteSizePtr = new IntPtr(ptrArray.ToInt64() + noteSize * i);
                var note = Marshal.PtrToStructure<Note>(noteSizePtr);

                notes.Add(note);
            }

            MidiInternal.FreeNotes(ptrArray);

            return notes.ToArray();
        }

    }

}
