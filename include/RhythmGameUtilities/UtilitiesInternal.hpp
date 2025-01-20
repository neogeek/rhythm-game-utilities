#pragma once

#include <map>

#include "Structs/BeatBar.h"
#include "Structs/TimeSignature.h"

#include "Utilities.hpp"

#ifdef _WIN32
#define PACKAGE_API __declspec(dllexport)
#else
#define PACKAGE_API
#endif

namespace RhythmGameUtilities
{

extern "C"
{
    PACKAGE_API int ConvertSecondsToTicksInternal(float seconds, int resolution,
                                                  int *bpmChangesKeys,
                                                  int *bpmChangesValues,
                                                  int bpmChangesSize,
                                                  TimeSignature *timeSignatures,
                                                  int timeSignaturesSize)
    {
        std::map<int, int> bpmChanges;

        for (auto i = 0; i < bpmChangesSize; i += 1)
        {
            bpmChanges[bpmChangesKeys[i]] = bpmChangesValues[i];
        }

        std::vector<TimeSignature> timeSignatureChanges;

        for (auto i = 0; i < timeSignaturesSize; i += 1)
        {
            timeSignatureChanges.push_back(timeSignatures[i]);
        }

        return ConvertSecondsToTicks(seconds, resolution, bpmChanges,
                                     timeSignatureChanges);
    }

    PACKAGE_API BeatBar *
    CalculateBeatBarsInternal(int *bpmChangesKeys, int *bpmChangesValues,
                              int bpmChangesSize, int resolution, int ts,
                              bool includeHalfNotes, int *outSize)
    {
        auto bpmChanges = std::map<int, int>();

        for (auto i = 0; i < bpmChangesSize; i += 1)
        {
            bpmChanges[bpmChangesKeys[i]] = bpmChangesValues[i];
        }

        auto internalBeatBars =
            CalculateBeatBars(bpmChanges, resolution, ts, includeHalfNotes);

        *outSize = internalBeatBars.size();

        auto beatBars =
            (BeatBar *)malloc(internalBeatBars.size() * sizeof(BeatBar));

        for (auto i = 0; i < internalBeatBars.size(); i += 1)
        {
            beatBars[i] = internalBeatBars[i];
        }

        return beatBars;
    }
}

} // namespace RhythmGameUtilities
