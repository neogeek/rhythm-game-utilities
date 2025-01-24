using System.Runtime.InteropServices;

namespace RhythmGameUtilities
{

    [StructLayout(LayoutKind.Sequential)]
    public struct Tempo
    {

        public int Position;

        public int BPM;

    }

}
