#include <cassert>
#include <iostream>

#include "RhythmGameUtilities/Enums/Difficulty.h"
#include "RhythmGameUtilities/Enums/NamedSection.h"
#include "RhythmGameUtilities/Enums/TypeCode.h"

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
    assert(ToString(TypeCode::BPM) == "B");
    assert(ToString(TypeCode::TimeSignature) == "TS");
    assert(ToString(TypeCode::Note) == "N");
    assert(ToString(TypeCode::Event) == "E");

    std::cout << ".";
}

int main()
{
    testDifficulty();
    testNamedSection();
    testTypeCode();

    return 0;
}
