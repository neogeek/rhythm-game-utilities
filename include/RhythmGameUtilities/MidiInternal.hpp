#pragma once

#include "Structs/Note.hpp"

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

    PACKAGE_API auto ReadMidiDataInternal(const uint8_t *data, int dataSize,
                                          int *outSize) -> Note *
    {
        std::vector<uint8_t> byteVector(data, data + dataSize);

        auto internalNotes = ReadMidiData(byteVector);

        *outSize = internalNotes.size();

        auto *notes = (Note *)malloc(internalNotes.size() * sizeof(Note));

        for (auto i = 0; i < internalNotes.size(); i += 1)
        {
            notes[i] = internalNotes[i];
        }

        return notes;
    }

    PACKAGE_API void FreeNotes(Note *notes) { free(notes); }
}

} // namespace RhythmGameUtilities
