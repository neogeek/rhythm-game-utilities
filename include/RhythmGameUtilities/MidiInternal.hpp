#pragma once

#include <map>

#include "Structs/Note.h"

#include "Midi.hpp"

#ifdef _WIN32
#define PACKAGE_API __declspec(dllexport)
#else
#define PACKAGE_API
#endif

namespace RhythmGameUtilities
{

extern "C"
{

    PACKAGE_API Note *ReadMidiDataInternal(const uint8_t *data, int dataSize,
                                           int *outSize)
    {
        std::vector<uint8_t> byteVector(data, data + dataSize);

        auto internalNotes = ReadMidiData(byteVector);

        *outSize = internalNotes.size();

        auto notes = (Note *)malloc(internalNotes.size() * sizeof(Note));

        for (auto i = 0; i < internalNotes.size(); i += 1)
        {
            notes[i] = internalNotes[i];
        }

        return notes;
    }

    PACKAGE_API Note *ReadMidiFileInternal(const std::string &path,
                                           int *outSize)
    {
        auto internalNotes = ReadMidiFile(path);

        *outSize = internalNotes.size();

        auto notes = (Note *)malloc(internalNotes.size() * sizeof(Note));

        for (auto i = 0; i < internalNotes.size(); i += 1)
        {
            notes[i] = internalNotes[i];
        }

        return notes;
    }
}

} // namespace RhythmGameUtilities
