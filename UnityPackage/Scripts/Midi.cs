using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace RhythmGameUtilities
{

    internal static class MidiInternal
    {

        [DllImport("libRhythmGameUtilities", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ReadMidiDataInternal(byte[] bytes, int dataSize, out int size);

        [DllImport("libRhythmGameUtilities", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ReadMidiFileInternal(string filename, out int size);

    }

    public static class Midi
    {

        public static List<Note> ReadMidiData(byte[] bytes)
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

            Marshal.FreeHGlobal(ptrArray);

            return notes;
        }

        public static List<Note> ReadMidiFile(string path)
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

            Marshal.FreeHGlobal(ptrArray);

            return notes;
        }

    }

}
