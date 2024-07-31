using System.Runtime.InteropServices;

namespace RhythmGameUtilities
{

    [StructLayout(LayoutKind.Sequential)]
    public struct TrackEvent
    {

        public int Position;

        public string TypeCode;

        public string[] Values;

    }

}
