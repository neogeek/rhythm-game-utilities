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
            var ptrArray = MidiInternal.ReadTempoChangesFromMidiDataInternal(bytes, bytes.Length, out var size);

            var tempoChanges = InternalUtilities.CaptureArrayFromInternalMethod<Tempo>(ptrArray, size);

            MidiInternal.FreeTempoChanges(ptrArray);

            return tempoChanges;
        }

        public static TimeSignature[] ReadTimeSignatureChangesFromMidiData(byte[] bytes)
        {
            var ptrArray = MidiInternal.ReadTimeSignatureChangesFromMidiDataInternal(bytes, bytes.Length, out var size);

            var timeSignatureChanges = InternalUtilities.CaptureArrayFromInternalMethod<TimeSignature>(ptrArray, size);

            MidiInternal.FreeTimeSignatureChanges(ptrArray);

            return timeSignatureChanges;
        }

        public static Note[] ReadNotesFromMidiData(byte[] bytes)
        {
            var ptrArray = MidiInternal.ReadNotesFromMidiDataInternal(bytes, bytes.Length, out var size);

            var notes = InternalUtilities.CaptureArrayFromInternalMethod<Note>(ptrArray, size);

            MidiInternal.FreeNotes(ptrArray);

            return notes;
        }

    }

}
