using System.Runtime.InteropServices;

namespace RhythmGameUtilities
{

    [StructLayout(LayoutKind.Sequential)]
    public struct Note
    {

        public int Position;

        public int HandPosition;

        public int Length;

    }

}
