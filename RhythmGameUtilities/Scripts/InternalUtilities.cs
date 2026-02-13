using System;
using System.Runtime.InteropServices;

namespace RhythmGameUtilities
{

    public static class InternalUtilities
    {

        public static T[] CaptureArrayFromInternalMethod<T>(IntPtr ptrArray, int size)
        {
            var array = new T[size];

            var structSize = Marshal.SizeOf(typeof(T));

            for (var i = 0; i < size; i += 1)
            {
                var structSizePtr = new IntPtr(ptrArray.ToInt64() + structSize * i);

                array[i] = Marshal.PtrToStructure<T>(structSizePtr);
            }

            return array;
        }

    }

}
