// Rhythm Game Utilities - https://github.com/neogeek/rhythm-game-utilities
//
// ░█▀▄░█░█░█░█░▀█▀░█░█░█▄█░░░█▀▀░█▀█░█▄█░█▀▀░░░█░█░▀█▀░▀█▀░█░░░▀█▀░▀█▀░▀█▀░█▀▀░█▀▀
// ░█▀▄░█▀█░░█░░░█░░█▀█░█░█░░░█░█░█▀█░█░█░█▀▀░░░█░█░░█░░░█░░█░░░░█░░░█░░░█░░█▀▀░▀▀█
// ░▀░▀░▀░▀░░▀░░░▀░░▀░▀░▀░▀░░░▀▀▀░▀░▀░▀░▀░▀▀▀░░░▀▀▀░░▀░░▀▀▀░▀▀▀░▀▀▀░░▀░░▀▀▀░▀▀▀░▀▀▀
//
// Copyright (c) Scott Doxey. All Rights Reserved. Licensed under the MIT
// License. See LICENSE in the project root for license information.

#pragma once

#include "../Structs/Note.hpp"
#include "../Structs/Tempo.hpp"
#include "../Structs/TimeSignature.hpp"

#include "./Midi.hpp"

#ifdef _WIN32
#define PACKAGE_API __declspec(dllexport)
#else
#define PACKAGE_API
#endif

namespace RhythmGameUtilities
{

extern "C"
{
    PACKAGE_API auto ReadResolutionFromMidiDataInternal(const uint8_t *data,
                                                        int dataSize,
                                                        int *outSize)
        -> uint16_t
    {
        std::vector<uint8_t> byteVector(data, data + dataSize);

        return ReadResolutionFromMidiData(byteVector);
    }

    PACKAGE_API auto ReadTempoChangesFromMidiDataInternal(const uint8_t *data,
                                                          int dataSize,
                                                          int *outSize)
        -> Tempo *
    {
        std::vector<uint8_t> byteVector(data, data + dataSize);

        auto internalTempoChanges = ReadTempoChangesFromMidiData(byteVector);

        *outSize = internalTempoChanges.size();

        auto *tempoChanges =
            (Tempo *)malloc(internalTempoChanges.size() * sizeof(Tempo));

        for (auto i = 0; i < internalTempoChanges.size(); i += 1)
        {
            tempoChanges[i] = internalTempoChanges[i];
        }

        return tempoChanges;
    }

    PACKAGE_API auto ReadTimeSignatureChangesFromMidiDataInternal(
        const uint8_t *data, int dataSize, int *outSize) -> TimeSignature *
    {
        std::vector<uint8_t> byteVector(data, data + dataSize);

        auto internalTimeSignatureChanges =
            ReadTimeSignatureChangesFromMidiData(byteVector);

        *outSize = internalTimeSignatureChanges.size();

        auto *timeSignatureChanges = (TimeSignature *)malloc(
            internalTimeSignatureChanges.size() * sizeof(TimeSignature));

        for (auto i = 0; i < internalTimeSignatureChanges.size(); i += 1)
        {
            timeSignatureChanges[i] = internalTimeSignatureChanges[i];
        }

        return timeSignatureChanges;
    }

    PACKAGE_API auto ReadNotesFromMidiDataInternal(const uint8_t *data,
                                                   int dataSize, int *outSize)
        -> Note *
    {
        std::vector<uint8_t> byteVector(data, data + dataSize);

        auto internalNotes = ReadNotesFromMidiData(byteVector);

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
