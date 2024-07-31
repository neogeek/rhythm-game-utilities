using System.Runtime.InteropServices;

namespace RhythmGameUtilities
{

    [StructLayout(LayoutKind.Sequential)]
    public struct BeatBar
    {

        public int Position;

        public int BPM;

        public int[] TimeSignature;

    }

}
