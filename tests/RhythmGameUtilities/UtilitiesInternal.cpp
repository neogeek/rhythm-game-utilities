#include <cassert>
#include <cmath>
#include <iostream>
#include <tuple>

#include "RhythmGameUtilities/Structs/Tempo.h"
#include "RhythmGameUtilities/Structs/TimeSignature.h"

#include "RhythmGameUtilities/UtilitiesInternal.hpp"

using namespace RhythmGameUtilities;

void testConvertSecondsToTicksInternal()
{
    std::vector<Tempo> bpmChanges = {
        {0, 88000},      {3840, 112000},  {9984, 89600},  {22272, 112000},
        {33792, 111500}, {34560, 112000}, {42240, 111980}};

    std::vector<TimeSignature> timeSignatureChanges = {{0, 4, 2}};

    assert(1408 == ConvertSecondsToTicksInternal(
                       5, 192, &bpmChanges[0], bpmChanges.size(),
                       &timeSignatureChanges[0], timeSignatureChanges.size()));

    std::cout << ".";
}

void testCalculateBeatBarsInternal()
{
    std::vector<Tempo> bpmChanges = {
        {0, 88000},      {3840, 112000},  {9984, 89600},  {22272, 112000},
        {33792, 111500}, {34560, 112000}, {42240, 111980}};

    int *outSize;

    auto beatBars = CalculateBeatBarsInternal(&bpmChanges[0], bpmChanges.size(),
                                              192, 4, true, outSize);

    assert(*outSize == 440);

    std::cout << ".";
}

int main()
{
    testConvertSecondsToTicksInternal();
    testCalculateBeatBarsInternal();

    return 0;
}
