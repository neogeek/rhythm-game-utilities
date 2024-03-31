using System.Runtime.InteropServices;

namespace RhythmGameUtilities
{

    internal static class UtilitiesInternal
    {

#if WINDOWS_BUILD || UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN
        [DllImport("libRhythmGameUtilities.dll", CallingConvention = CallingConvention.Cdecl)]
#else
        [DllImport("libRhythmGameUtilities.dylib", CallingConvention = CallingConvention.Cdecl)]
#endif
        public static extern float ConvertTicksToSeconds(float tick, int resolution, int bpm);

#if WINDOWS_BUILD || UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN
        [DllImport("libRhythmGameUtilities.dll", CallingConvention = CallingConvention.Cdecl)]
#else
        [DllImport("libRhythmGameUtilities.dylib", CallingConvention = CallingConvention.Cdecl)]
#endif
        public static extern int ConvertSecondsToTicks(double seconds, int resolution, int bpm);

#if WINDOWS_BUILD || UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN
        [DllImport("libRhythmGameUtilities.dll", CallingConvention = CallingConvention.Cdecl)]
#else
        [DllImport("libRhythmGameUtilities.dylib", CallingConvention = CallingConvention.Cdecl)]
#endif
        public static extern float CalculateNoteHitAccuracy(ref Note note, float buffer, int currentTick);

#if WINDOWS_BUILD || UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN
        [DllImport("libRhythmGameUtilities.dll", CallingConvention = CallingConvention.Cdecl)]
#else
        [DllImport("libRhythmGameUtilities.dylib", CallingConvention = CallingConvention.Cdecl)]
#endif
        public static extern float CalculateScale(float baseBpm, float actualBpm, float speed);

#if WINDOWS_BUILD || UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN
        [DllImport("libRhythmGameUtilities.dll", CallingConvention = CallingConvention.Cdecl)]
#else
        [DllImport("libRhythmGameUtilities.dylib", CallingConvention = CallingConvention.Cdecl)]
#endif
        public static extern float Lerp(float a, float b, float t);

#if WINDOWS_BUILD || UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN
        [DllImport("libRhythmGameUtilities.dll", CallingConvention = CallingConvention.Cdecl)]
#else
        [DllImport("libRhythmGameUtilities.dylib", CallingConvention = CallingConvention.Cdecl)]
#endif
        public static extern float InverseLerp(float a, float b, float v);

    }

    public static class Utilities
    {

        public static float ConvertTicksToSeconds(float tick, int resolution, int bpm)
        {
            return UtilitiesInternal.ConvertTicksToSeconds(tick, resolution, bpm);
        }

        public static int ConvertSecondsToTicks(double seconds, int resolution, int bpm)
        {
            return UtilitiesInternal.ConvertSecondsToTicks(seconds, resolution, bpm);
        }

        public static float CalculateNoteHitAccuracy(ref Note note, float buffer, int currentTick)
        {
            return UtilitiesInternal.CalculateNoteHitAccuracy(ref note, buffer, currentTick);
        }

        public static float CalculateScale(float baseBpm, float actualBpm, float speed)
        {
            return UtilitiesInternal.CalculateScale(baseBpm, actualBpm, speed);
        }

        public static float Lerp(float a, float b, float t)
        {
            return UtilitiesInternal.Lerp(a, b, t);
        }

        public static float InverseLerp(float a, float b, float v)
        {
            return UtilitiesInternal.InverseLerp(a, b, v);
        }

    }

}
