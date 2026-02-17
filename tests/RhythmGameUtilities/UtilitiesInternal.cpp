#include <cassert>
#include <cmath>
#include <iostream>

#include "RhythmGameUtilities/Structs/Tempo.hpp"
#include "RhythmGameUtilities/Structs/TimeSignature.hpp"

#include "RhythmGameUtilities/UtilitiesInternal.hpp"

using namespace RhythmGameUtilities;

void testCalculateBeatBarsInternal()
{
    std::vector<Tempo> tempoChanges = {
        {0, 88000},      {3840, 112000},  {9984, 89600},  {22272, 112000},
        {33792, 111500}, {34560, 112000}, {42240, 111980}};

    int outSize;

    auto *beatBars = CalculateBeatBarsInternal(
        &tempoChanges[0], tempoChanges.size(), 192, 4, true, &outSize);

    assert(outSize == 440);

    std::cout << ".";
}

void testConvertSecondsToTicksInternal()
{
    std::vector<Tempo> tempoChanges = {
        {0, 88000},      {3840, 112000},  {9984, 89600},  {22272, 112000},
        {33792, 111500}, {34560, 112000}, {42240, 111980}};

    std::vector<TimeSignature> timeSignatureChanges = {{0, 4, 2}};

    assert(1408 == ConvertSecondsToTicksInternal(
                       5, 192, &tempoChanges[0], tempoChanges.size(),
                       &timeSignatureChanges[0], timeSignatureChanges.size()));

    std::cout << ".";
}

auto main() -> int
{
    testCalculateBeatBarsInternal();
    testConvertSecondsToTicksInternal();

    return 0;
}
