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

void testFindPositionNearGivenTick()
{
    std::vector<Note> notes = {{768, 0, 0},  {960, 0, 0},  {1152, 0, 0},
                               {1536, 0, 0}, {1728, 0, 0}, {1920, 0, 0},
                               {2304, 0, 0}, {2496, 0, 0}, {2688, 0, 0},
                               {3072, 0, 0}, {3264, 0, 0}};

    assert(std::nullopt == FindPositionNearGivenTick(notes, 100));
    assert(768 == FindPositionNearGivenTick(notes, 750)->Position);
    assert(1536 == FindPositionNearGivenTick(notes, 1500)->Position);
    assert(std::nullopt == FindPositionNearGivenTick(notes, 3200));

    std::cout << ".";
}

void testCalculateAccuracyRatio()
{
    assert(0 == CalculateAccuracyRatio(750, 100));
    assert(1 == CalculateAccuracyRatio(750, 750));
    assert(0.5f == CalculateAccuracyRatio(750, 725));

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

    assert(beatBars.size() == 440);

    std::cout << ".";
}

int main()
{
    testConvertTickToPosition();
    testConvertSecondsToTicks();
    testIsOnTheBeat();
    testFindPositionNearGivenTick();
    testCalculateAccuracyRatio();
    testRoundUpToTheNearestMultiplier();
    testGenerateAdjacentKeyPairs();
    testCalculateBeatBars();

    return 0;
}
