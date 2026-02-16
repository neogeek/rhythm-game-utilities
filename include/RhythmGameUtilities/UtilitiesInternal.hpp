// Rhythm Game Utilities - https://github.com/neogeek/rhythm-game-utilities
//
// ░█▀▄░█░█░█░█░▀█▀░█░█░█▄█░░░█▀▀░█▀█░█▄█░█▀▀░░░█░█░▀█▀░▀█▀░█░░░▀█▀░▀█▀░▀█▀░█▀▀░█▀▀
// ░█▀▄░█▀█░░█░░░█░░█▀█░█░█░░░█░█░█▀█░█░█░█▀▀░░░█░█░░█░░░█░░█░░░░█░░░█░░░█░░█▀▀░▀▀█
// ░▀░▀░▀░▀░░▀░░░▀░░▀░▀░▀░▀░░░▀▀▀░▀░▀░▀░▀░▀▀▀░░░▀▀▀░░▀░░▀▀▀░▀▀▀░▀▀▀░░▀░░▀▀▀░▀▀▀░▀▀▀
//
// Copyright (c) Scott Doxey. All Rights Reserved. Licensed under the MIT
// License. See LICENSE in the project root for license information.

#pragma once

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
    PACKAGE_API auto
    ConvertSecondsToTicksInternal(float seconds, int resolution,
                                  Tempo *tempoChanges, int tempoChangesSize,
                                  TimeSignature *timeSignatureChanges,
                                  int timeSignatureChangesSize) -> int
    {
        std::vector<Tempo> tempoChangesVector;

        for (auto i = 0; i < tempoChangesSize; i += 1)
        {
            tempoChangesVector.push_back(tempoChanges[i]);
        }

        std::vector<TimeSignature> timeSignatureChangesVector;

        for (auto i = 0; i < timeSignatureChangesSize; i += 1)
        {
            timeSignatureChangesVector.push_back(timeSignatureChanges[i]);
        }

        return ConvertSecondsToTicks(seconds, resolution, tempoChangesVector,
                                     timeSignatureChangesVector);
    }

    PACKAGE_API auto CalculateBeatBarsInternal(Tempo *tempoChanges,
                                               int tempoChangesSize,
                                               int resolution, int ts,
                                               bool includeHalfNotes,
                                               int *outSize) -> BeatBar *
    {
        std::vector<Tempo> tempoChangesVector;

        for (auto i = 0; i < tempoChangesSize; i += 1)
        {
            tempoChangesVector.push_back(tempoChanges[i]);
        }

        auto internalBeatBars = CalculateBeatBars(
            tempoChangesVector, resolution, ts, includeHalfNotes);

        *outSize = internalBeatBars.size();

        auto *beatBars =
            (BeatBar *)malloc(internalBeatBars.size() * sizeof(BeatBar));

        for (auto i = 0; i < internalBeatBars.size(); i += 1)
        {
            beatBars[i] = internalBeatBars[i];
        }

        return beatBars;
    }

    PACKAGE_API auto FindPositionsNearGivenTickInternal(Note *notes,
                                                        int noteSize, int tick,
                                                        int delta, int *outSize)
        -> Note *
    {
        std::vector<Note> notesVector;

        for (auto i = 0; i < noteSize; i += 1)
        {
            notesVector.push_back(notes[i]);
        }

        auto internalPositions =
            FindPositionsNearGivenTick(notesVector, tick, delta);

        *outSize = internalPositions.size();

        auto *foundPositions =
            (Note *)malloc(internalPositions.size() * sizeof(Note));

        for (auto i = 0; i < internalPositions.size(); i += 1)
        {
            foundPositions[i] = internalPositions[i];
        }

        return foundPositions;
    }

    PACKAGE_API auto ConvertTickToPositionInternal(int tick, int resolution)
        -> float
    {
        return ConvertTickToPosition(tick, resolution);
    }

    PACKAGE_API auto IsOnTheBeatInternal(int bpm, float currentTime,
                                         float delta = 0.05F) -> bool
    {
        return IsOnTheBeat(bpm, currentTime, delta);
    }

    PACKAGE_API auto RoundUpToTheNearestMultiplierInternal(int value,
                                                           int multiplier)
        -> int
    {
        return RoundUpToTheNearestMultiplier(value, multiplier);
    }

    PACKAGE_API auto CalculateAccuracyRatioInternal(int position,
                                                    int currentPosition,
                                                    int delta = 50) -> float
    {
        return CalculateAccuracyRatio(position, currentPosition, delta);
    }
}

} // namespace RhythmGameUtilities
