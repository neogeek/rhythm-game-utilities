using System.Runtime.InteropServices;

namespace RhythmGameUtilities
{

    [StructLayout(LayoutKind.Sequential)]
    public struct TimeSignature
    {

        public int Position;

        public int Numerator;

        public int Denominator;

    }

}
