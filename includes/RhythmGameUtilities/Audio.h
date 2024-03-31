#ifndef AUDIO_H
#define AUDIO_H

#ifdef _WIN32
#define PACKAGE_API __declspec(dllexport)
#else
#define PACKAGE_API
#endif

extern "C"
{
    PACKAGE_API int **ConvertSamplesToWaveform(float *samples, int size,
                                               int width, int height);
}

#endif
