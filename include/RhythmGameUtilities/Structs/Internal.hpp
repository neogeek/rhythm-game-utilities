#pragma once

#include <cstdlib>

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
    PACKAGE_API void FreeTempoChanges(Tempo *tempoChanges)
    {
        free(tempoChanges);
    }

    PACKAGE_API void
    FreeTimeSignatureChanges(TimeSignature *timeSignatureChanges)
    {
        free(timeSignatureChanges);
    }

    PACKAGE_API void FreeNotes(Note *notes) { free(notes); }
}

} // namespace RhythmGameUtilities
