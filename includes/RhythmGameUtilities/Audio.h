#pragma once

#ifdef _WIN32
#define PACKAGE_API __declspec(dllexport)
#else
#define PACKAGE_API
#endif

namespace RhythmGameUtilities
{

extern "C"
{
    PACKAGE_API int **ConvertSamplesToWaveform(float *samples, int size,
                                               int width, int height);
}

} // namespace RhythmGameUtilities
