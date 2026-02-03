#include <cassert>
#include <iostream>

#include "RhythmGameUtilities/Audio.hpp"

using namespace RhythmGameUtilities;

void testConvertSamplesToWaveform()
{
    const int size = 5;
    auto *samples = new float[size]{0, 1, 2, 3, 4};
    const int width = 100;
    const int height = 100;

    auto *waveform = ConvertSamplesToWaveform(samples, size, width, height);

    std::cout << ".";
}

auto main() -> int
{
    testConvertSamplesToWaveform();

    return 0;
}
