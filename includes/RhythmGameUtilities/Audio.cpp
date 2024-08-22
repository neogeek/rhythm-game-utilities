#include <stdlib.h>

#include <cmath>

#include "Audio.h"

namespace RhythmGameUtilities
{

int **ConvertSamplesToWaveform(float *samples, int size, int width, int height)
{
    auto waveform = new int *[width];

    auto step = floor(size / width);
    auto amp = height / 2;

    for (auto x = 0; x < width; x += 1)
    {
        waveform[x] = new int[height];

        auto min = 1.0f;
        auto max = -1.0f;

        for (auto j = 0; j < step; j += 1)
        {
            auto index = (int)(x * step + j);

            auto datum = samples[index];

            if (datum < min)
            {
                min = datum;
            }

            if (datum > max)
            {
                max = datum;
            }
        }

        auto minY = (int)((1 + min) * amp);
        auto maxY = (int)((1 + max) * amp);

        for (auto y = 0; y < height; y += 1)
        {
            waveform[x][y] = y >= minY && y <= maxY ? 1 : 0;
        }
    }

    return waveform;
}

} // namespace RhythmGameUtilities
