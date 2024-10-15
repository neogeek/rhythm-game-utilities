using System.Runtime.InteropServices;

namespace RhythmGameUtilities
{

    public static class CommonInternal
    {

#if WINDOWS_BUILD || UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN
        [DllImport("libRhythmGameUtilities.dll", CallingConvention = CallingConvention.Cdecl)]
#elif MACOS_BUILD || UNITY_EDITOR_OSX || UNITY_STANDALONE_OSX
        [DllImport("libRhythmGameUtilities.dylib", CallingConvention = CallingConvention.Cdecl)]
#elif LINUX_BUILD || UNITY_EDITOR_LINUX || UNITY_STANDALONE_LINUX
        [DllImport("libRhythmGameUtilities.so", CallingConvention = CallingConvention.Cdecl)]
#endif
        public static extern float Lerp(float a, float b, float t);

#if WINDOWS_BUILD || UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN
        [DllImport("libRhythmGameUtilities.dll", CallingConvention = CallingConvention.Cdecl)]
#elif MACOS_BUILD || UNITY_EDITOR_OSX || UNITY_STANDALONE_OSX
        [DllImport("libRhythmGameUtilities.dylib", CallingConvention = CallingConvention.Cdecl)]
#elif LINUX_BUILD || UNITY_EDITOR_LINUX || UNITY_STANDALONE_LINUX
        [DllImport("libRhythmGameUtilities.so", CallingConvention = CallingConvention.Cdecl)]
#endif
        public static extern float InverseLerp(float a, float b, float v);

    }

    public static class Common
    {

        /// <summary>
        /// Calculates the linear interpolation between two values.
        /// </summary>
        ///
        /// <param name="a">The start value.</param>
        /// <param name="b">The end value.</param>
        /// <param name="t">The value used for interpolation.</param>
        public static float Lerp(float a, float b, float t)
        {
            return CommonInternal.Lerp(a, b, t);
        }

        /// <summary>
        /// Calculates the fraction, based on a value between two values.
        /// </summary>
        ///
        /// <param name="a">The start value.</param>
        /// <param name="b">The end value.</param>
        /// <param name="v">The value in the middle.</param>
        public static float InverseLerp(float a, float b, float v)
        {
            return CommonInternal.InverseLerp(a, b, v);
        }

    }

}
