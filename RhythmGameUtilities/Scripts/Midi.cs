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
        public static extern IntPtr ReadMidiDataInternal(byte[] bytes, int dataSize, out int size);

#if UNITY_WEBGL && !UNITY_EDITOR
        [DllImport("__Internal")]
#else
        [DllImport("libRhythmGameUtilities", CallingConvention = CallingConvention.Cdecl)]
#endif
        public static extern IntPtr ReadMidiFileInternal(string filename, out int size);

#if UNITY_WEBGL && !UNITY_EDITOR
        [DllImport("__Internal")]
#else
        [DllImport("libRhythmGameUtilities", CallingConvention = CallingConvention.Cdecl)]
#endif
        public static extern void FreeNotes(IntPtr notes);

    }

    public static class Midi
    {

        public static Note[] ReadMidiData(byte[] bytes)
        {
            var notes = new List<Note>();

            var ptrArray = MidiInternal.ReadMidiDataInternal(bytes, bytes.Length, out var size);

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

        public static Note[] ReadMidiFile(string path)
        {
            var notes = new List<Note>();

            var ptrArray = MidiInternal.ReadMidiFileInternal(path, out var size);

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
