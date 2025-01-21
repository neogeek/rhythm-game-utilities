#pragma once

#include <map>

#include "Structs/BeatBar.h"
#include "Structs/Tempo.h"
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
    PACKAGE_API int ConvertSecondsToTicksInternal(
        float seconds, int resolution, Tempo *bpmChanges, int bpmChangesSize,
        TimeSignature *timeSignaturesChanges, int timeSignaturesChangesSize)
    {
        std::vector<Tempo> bpmChangesVector;

        for (auto i = 0; i < bpmChangesSize; i += 1)
        {
            bpmChangesVector.push_back(bpmChanges[i]);
        }

        std::vector<TimeSignature> timeSignatureChangesVector;

        for (auto i = 0; i < timeSignaturesChangesSize; i += 1)
        {
            timeSignatureChangesVector.push_back(timeSignaturesChanges[i]);
        }

        return ConvertSecondsToTicks(seconds, resolution, bpmChangesVector,
                                     timeSignatureChangesVector);
    }

    PACKAGE_API BeatBar *CalculateBeatBarsInternal(Tempo *bpmChanges,
                                                   int bpmChangesSize,
                                                   int resolution, int ts,
                                                   bool includeHalfNotes,
                                                   int *outSize)
    {
        std::vector<Tempo> bpmChangesVector;

        for (auto i = 0; i < bpmChangesSize; i += 1)
        {
            bpmChangesVector.push_back(bpmChanges[i]);
        }

        auto internalBeatBars = CalculateBeatBars(bpmChangesVector, resolution,
                                                  ts, includeHalfNotes);

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
