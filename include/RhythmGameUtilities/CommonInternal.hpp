#pragma once

#include "Common.hpp"

#ifdef _WIN32
#define PACKAGE_API __declspec(dllexport)
#else
#define PACKAGE_API
#endif

namespace RhythmGameUtilities
{

extern "C"
{
    PACKAGE_API float LerpInternal(float a, float b, float t)
    {
        return Lerp(a, b, t);
    }

    PACKAGE_API float InverseLerpInternal(float a, float b, float v)
    {
        return InverseLerp(a, b, v);
    }
}

} // namespace RhythmGameUtilities
