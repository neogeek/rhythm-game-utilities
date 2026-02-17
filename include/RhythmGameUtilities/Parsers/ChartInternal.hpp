// Rhythm Game Utilities - https://github.com/neogeek/rhythm-game-utilities
//
// ░█▀▄░█░█░█░█░▀█▀░█░█░█▄█░░░█▀▀░█▀█░█▄█░█▀▀░░░█░█░▀█▀░▀█▀░█░░░▀█▀░▀█▀░▀█▀░█▀▀░█▀▀
// ░█▀▄░█▀█░░█░░░█░░█▀█░█░█░░░█░█░█▀█░█░█░█▀▀░░░█░█░░█░░░█░░█░░░░█░░░█░░░█░░█▀▀░▀▀█
// ░▀░▀░▀░▀░░▀░░░▀░░▀░▀░▀░▀░░░▀▀▀░▀░▀░▀░▀░▀▀▀░░░▀▀▀░░▀░░▀▀▀░▀▀▀░▀▀▀░░▀░░▀▀▀░▀▀▀░▀▀▀
//
// Copyright (c) Scott Doxey. All Rights Reserved. Licensed under the MIT
// License. See LICENSE in the project root for license information.

#pragma once

#include <cstring>

#include "../Enums/Difficulty.hpp"

#include "Chart.hpp"

#ifdef _WIN32
#define PACKAGE_API __declspec(dllexport)
#else
#define PACKAGE_API
#endif

namespace RhythmGameUtilities
{

extern "C"
{
    PACKAGE_API auto ReadTempoChangesFromChartDataInternal(const char *contents,
                                                           int *outSize)
        -> Tempo *
    {
        auto internalTempoChanges = ReadTempoChangesFromChartData(contents);

        *outSize = internalTempoChanges.size();

        auto *tempoChanges =
            (Tempo *)malloc(internalTempoChanges.size() * sizeof(Tempo));

        for (auto i = 0; i < internalTempoChanges.size(); i += 1)
        {
            tempoChanges[i] = internalTempoChanges[i];
        }

        return tempoChanges;
    }

    PACKAGE_API auto ReadTimeSignatureChangesFromChartDataInternal(
        const char *contents, int *outSize) -> TimeSignature *
    {
        auto internalTimeSignatureChanges =
            ReadTimeSignatureChangesFromChartData(contents);

        *outSize = internalTimeSignatureChanges.size();

        auto *timeSignatureChanges = (TimeSignature *)malloc(
            internalTimeSignatureChanges.size() * sizeof(TimeSignature));

        for (auto i = 0; i < internalTimeSignatureChanges.size(); i += 1)
        {
            timeSignatureChanges[i] = internalTimeSignatureChanges[i];
        }

        return timeSignatureChanges;
    }

    PACKAGE_API auto ReadNotesFromChartDataInternal(const char *contents,
                                                    Difficulty difficulty,
                                                    int *outSize) -> Note *
    {
        auto internalNotes = ReadNotesFromChartData(contents, difficulty);

        *outSize = internalNotes.size();

        auto *notes = (Note *)malloc(internalNotes.size() * sizeof(Note));

        for (auto i = 0; i < internalNotes.size(); i += 1)
        {
            notes[i] = internalNotes[i];
        }

        return notes;
    }
}

} // namespace RhythmGameUtilities
