// Rhythm Game Utilities -
// https://github.com/rhythm-game-utilities/rhythm-game-utilities
//
// ░█▀▄░█░█░█░█░▀█▀░█░█░█▄█░░░█▀▀░█▀█░█▄█░█▀▀░░░█░█░▀█▀░▀█▀░█░░░▀█▀░▀█▀░▀█▀░█▀▀░█▀▀
// ░█▀▄░█▀█░░█░░░█░░█▀█░█░█░░░█░█░█▀█░█░█░█▀▀░░░█░█░░█░░░█░░█░░░░█░░░█░░░█░░█▀▀░▀▀█
// ░▀░▀░▀░▀░░▀░░░▀░░▀░▀░▀░▀░░░▀▀▀░▀░▀░▀░▀░▀▀▀░░░▀▀▀░░▀░░▀▀▀░▀▀▀░▀▀▀░░▀░░▀▀▀░▀▀▀░▀▀▀
//
// Copyright (c) Scott Doxey. All Rights Reserved. Licensed under the MIT
// License. See LICENSE in the project root for license information.

#pragma once

#include <cstdlib>

#include "./BeatBar.hpp"
#include "./Note.hpp"
#include "./Tempo.hpp"
#include "./TimeSignature.hpp"

#ifdef _WIN32
#define PACKAGE_API __declspec(dllexport)
#else
#define PACKAGE_API
#endif

namespace RhythmGameUtilities
{

extern "C"
{
    PACKAGE_API void FreeBeatBars(BeatBar *beatBars) { free(beatBars); }

    PACKAGE_API void FreeTempoChanges(Tempo *tempoChanges)
    {
        std::free(tempoChanges);
    }

    PACKAGE_API void
    FreeTimeSignatureChanges(TimeSignature *timeSignatureChanges)
    {
        std::free(timeSignatureChanges);
    }

    PACKAGE_API void FreeNotes(Note *notes) { std::free(notes); }
}

} // namespace RhythmGameUtilities
