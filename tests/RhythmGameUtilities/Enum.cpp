#include <cassert>
#include <iostream>

#include "RhythmGameUtilities/Enums/Difficulty.hpp"
#include "RhythmGameUtilities/Enums/NamedSection.hpp"
#include "RhythmGameUtilities/Enums/TypeCode.hpp"

using namespace RhythmGameUtilities;

void testDifficulty()
{
    assert(ToString(Difficulty::Easy) == "Easy");
    assert(ToString(Difficulty::Medium) == "Medium");
    assert(ToString(Difficulty::Hard) == "Hard");
    assert(ToString(Difficulty::Expert) == "Expert");

    std::cout << ".";
}

void testNamedSection()
{
    assert(ToString(NamedSection::Song) == "Song");
    assert(ToString(NamedSection::SyncTrack) == "SyncTrack");
    assert(ToString(NamedSection::Events) == "Events");

    std::cout << ".";
}

void testTypeCode()
{
    assert(ToString(TypeCode::BPM_Marker) == "B");
    assert(ToString(TypeCode::TimeSignatureMarker) == "TS");
    assert(ToString(TypeCode::NoteMarker) == "N");
    assert(ToString(TypeCode::EventMarker) == "E");

    std::cout << ".";
}

auto main() -> int
{
    testDifficulty();
    testNamedSection();
    testTypeCode();

    return 0;
}
