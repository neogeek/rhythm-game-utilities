#include <cassert>
#include <cmath>
#include <iostream>
#include <tuple>

#include "RhythmGameUtilities/Utilities.hpp"

using namespace RhythmGameUtilities;

void testConvertTickToPosition()
{
    assert(4 == ConvertTickToPosition(768, 192));

    std::cout << ".";
}

void testConvertSecondsToTicks()
{
    std::map<int, int> bpmChanges = {
        {0, 88000},      {3840, 112000},  {9984, 89600},  {22272, 112000},
        {33792, 111500}, {34560, 112000}, {42240, 111980}};

    assert(1408 == ConvertSecondsToTicks(5, 192, bpmChanges));

    std::cout << ".";
}

void testIsOnTheBeat()
{
    assert(true == IsOnTheBeat(120, 10));
    assert(true == IsOnTheBeat(60, 1));
    assert(false == IsOnTheBeat(60, 1.5f));

    std::cout << ".";
}

void testRoundUpToTheNearestMultiplier()
{
    assert(20 == RoundUpToTheNearestMultiplier(12, 10));

    std::cout << ".";
}

void testGenerateAdjacentKeyPairs()
{
    std::map<int, int> bpmChanges = {
        {0, 88000},      {3840, 112000},  {9984, 89600},  {22272, 112000},
        {33792, 111500}, {34560, 112000}, {42240, 111980}};

    auto adjacentKeyPairs = GenerateAdjacentKeyPairs(bpmChanges);

    assert(adjacentKeyPairs.size() == 6);
    assert(adjacentKeyPairs[0] == std::make_tuple(0, 3840));
    assert(adjacentKeyPairs[1] == std::make_tuple(3840, 9984));

    std::cout << ".";
}

void testCalculateBeatBars()
{
    std::map<int, int> bpmChanges = {
        {0, 88000},      {3840, 112000},  {9984, 89600},  {22272, 112000},
        {33792, 111500}, {34560, 112000}, {42240, 111980}};

    auto beatBars = CalculateBeatBars(bpmChanges, 192, 4, true);

    assert(beatBars.size() == 446);

    std::cout << ".";
}

int main()
{
    testConvertTickToPosition();
    testConvertSecondsToTicks();
    testIsOnTheBeat();
    testRoundUpToTheNearestMultiplier();
    testGenerateAdjacentKeyPairs();
    testCalculateBeatBars();

    return 0;
}
