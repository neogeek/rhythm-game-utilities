#pragma once

#include <map>

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
