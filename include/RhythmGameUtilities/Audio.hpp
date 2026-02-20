// Rhythm Game Utilities - https://github.com/neogeek/rhythm-game-utilities
//
// ░█▀▄░█░█░█░█░▀█▀░█░█░█▄█░░░█▀▀░█▀█░█▄█░█▀▀░░░█░█░▀█▀░▀█▀░█░░░▀█▀░▀█▀░▀█▀░█▀▀░█▀▀
// ░█▀▄░█▀█░░█░░░█░░█▀█░█░█░░░█░█░█▀█░█░█░█▀▀░░░█░█░░█░░░█░░█░░░░█░░░█░░░█░░█▀▀░▀▀█
// ░▀░▀░▀░▀░░▀░░░▀░░▀░▀░▀░▀░░░▀▀▀░▀░▀░▀░▀░▀▀▀░░░▀▀▀░░▀░░▀▀▀░▀▀▀░▀▀▀░░▀░░▀▀▀░▀▀▀░▀▀▀
//
// Copyright (c) Scott Doxey. All Rights Reserved. Licensed under the MIT
// License. See LICENSE in the project root for license information.

#pragma once

#include <algorithm>
#include <cmath>
#include <cstdlib>

#ifdef _WIN32
#define PACKAGE_API __declspec(dllexport)
#else
#define PACKAGE_API
#endif

namespace RhythmGameUtilities
{

extern "C"
{
    /**
     * Converts samples from an audio file into data used to display a waveform.
     *
     * @param samples Array of sample data from an audio file.
     * @param size Length of the array.
     * @param width Width of the waveform.
     * @param height Height of the waveform.
     * @public
     */

    PACKAGE_API auto ConvertSamplesToWaveform(const float *samples, int size,
                                              int width, int height) -> int **
    {
        auto *waveform =
            static_cast<int **>(std::malloc(width * sizeof(int *)));

        auto step = std::floor(size / width);
        auto amp = height / 2;

        for (auto x = 0; x < width; x += 1)
        {
            waveform[x] = static_cast<int *>(std::malloc(height * sizeof(int)));

            auto min = 1.0F;
            auto max = -1.0F;

            for (auto j = 0; j < step; j += 1)
            {
                auto index = static_cast<int>((x * step) + j);

                auto datum = samples[index];

                min = std::min(datum, min);
                max = std::max(datum, max);
            }

            auto minY = static_cast<int>((1 + min) * amp);
            auto maxY = static_cast<int>((1 + max) * amp);

            for (auto y = 0; y < height; y += 1)
            {
                waveform[x][y] = y >= minY && y <= maxY ? 1 : 0;
            }
        }

        return waveform;
    }

    /**
     * Free data returned from the ConvertSamplesToWaveform function.
     *
     * @param waveform Waveform multidimensional array.
     * @param width Width of the waveform.
     * @public
     */

    PACKAGE_API void FreeWaveform(int **waveform, int width)
    {
        if (waveform != nullptr)
        {
            for (auto x = 0; x < width; x += 1)
            {
                std::free(waveform[x]);
            }

            std::free(waveform);
        }
    }
}

} // namespace RhythmGameUtilities
