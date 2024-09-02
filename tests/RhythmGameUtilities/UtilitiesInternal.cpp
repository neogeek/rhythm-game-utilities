#include <cassert>
#include <cmath>
#include <iostream>
#include <tuple>

#include "RhythmGameUtilities/UtilitiesInternal.hpp"

using namespace RhythmGameUtilities;

void testConvertSecondsToTicksInternal()
{
    std::map<int, int> bpmChanges = {
        {0, 88000},      {3840, 112000},  {9984, 89600},  {22272, 112000},
        {33792, 111500}, {34560, 112000}, {42240, 111980}};

    std::vector<int> bpmChangesKeys;
    std::vector<int> bpmChangesValues;

    for (const auto &[key, value] : bpmChanges)
    {
        bpmChangesKeys.push_back(key);
        bpmChangesValues.push_back(value);
    }

    assert(1408 == ConvertSecondsToTicksInternal(5, 192, &bpmChangesKeys[0],
                                                 &bpmChangesValues[0],
                                                 size(bpmChanges)));

    std::cout << ".";
}

void testCalculateBeatBarsInternal()
{
    std::map<int, int> bpmChanges = {
        {0, 88000},      {3840, 112000},  {9984, 89600},  {22272, 112000},
        {33792, 111500}, {34560, 112000}, {42240, 111980}};

    std::vector<int> bpmChangesKeys;
    std::vector<int> bpmChangesValues;

    for (const auto &[key, value] : bpmChanges)
    {
        bpmChangesKeys.push_back(key);
        bpmChangesValues.push_back(value);
    }

    int *outSize;

    auto beatBars =
        CalculateBeatBarsInternal(&bpmChangesKeys[0], &bpmChangesValues[0],
                                  size(bpmChanges), 192, 4, true, outSize);

    assert(*outSize == 446);

    std::cout << ".";
}

int main()
{
    testConvertSecondsToTicksInternal();
    testCalculateBeatBarsInternal();

    return 0;
}
