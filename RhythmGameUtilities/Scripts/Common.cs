using System;

namespace RhythmGameUtilities
{

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
            return (1 - t) * a + b * t;
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
            return Math.Clamp(((v - a) / (b - a)), 0.0f, 1.0f);
        }

    }

}
