using System;
using System.Runtime.InteropServices;

namespace RhythmGameUtilities
{

    [StructLayout(LayoutKind.Sequential)]
    public struct Note : IEquatable<Note>
    {

        public int Position;

        public int HandPosition;

        public int Length;

        public override int GetHashCode()
        {
            return (Position, HandPosition, Length).GetHashCode();
        }

        public bool Equals(Note other)
        {
            return Position == other.Position && HandPosition == other.HandPosition && Length == other.Length;
        }

        public override bool Equals(object obj)
        {
            return obj is Note other && Equals(other);
        }

        public static bool operator ==(Note left, Note right)
        {
            return left.Equals(right);
        }

        public static bool operator !=(Note left, Note right)
        {
            return !(left == right);
        }

    }

}
