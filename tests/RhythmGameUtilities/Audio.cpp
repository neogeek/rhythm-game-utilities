#include <cassert>
#include <iostream>

#include "RhythmGameUtilities/Audio.h"

using namespace RhythmGameUtilities;

void testConvertSamplesToWaveform()
{
    int size = 5;
    float *samples = new float[size]{0, 1, 2, 3, 4};
    const int width = 100;
    const int height = 100;

    auto waveform = ConvertSamplesToWaveform(samples, size, width, height);

    std::cout << ".";
}

int main()
{
    testConvertSamplesToWaveform();

    return 0;
}
