#include <cassert>
#include <cmath>
#include <iostream>

#include "RhythmGameUtilities/Utilities.h"

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

void testLerp()
{
    assert(0 == Lerp(0, 10, 0));
    assert(5 == Lerp(0, 10, 0.5f));
    assert(10 == Lerp(0, 10, 1));

    std::cout << ".";
}

void testInverseLerp()
{
    assert(0 == InverseLerp(0, 10, 0));
    assert(0.5f == InverseLerp(0, 10, 5));
    assert(1 == InverseLerp(0, 10, 10));

    std::cout << ".";
}

void testRoundUpToTheNearestMultiplier()
{
    assert(20 == RoundUpToTheNearestMultiplier(12, 10));

    std::cout << ".";
}

void testTrim()
{
    assert(Trim(" test ") == "test");

    std::cout << ".";
}

void testSplit()
{
    auto parts = Split("key=value", '=');

    assert(parts.size() == 2);
    assert(parts[0] == "key");
    assert(parts[1] == "value");

    std::cout << ".";
}

void testFindAllMatches()
{
    std::regex pattern("\\w+");

    auto sections = FindAllMatches("this is a test", pattern);

    assert(sections.size() == 4);

    std::cout << ".";
}

void testFindMatchGroups()
{
    std::regex pattern("(\\w+)\\s+(\\w+)\\s+(\\w+)\\s+(\\w+)");

    auto sections = FindMatchGroups("this is a test", pattern);

    assert(sections.size() == 5);

    std::cout << ".";
}

int main()
{
    testConvertTickToPosition();
    testConvertSecondsToTicks();
    testIsOnTheBeat();
    testLerp();
    testInverseLerp();
    testRoundUpToTheNearestMultiplier();

    testTrim();
    testSplit();
    testFindAllMatches();
    testFindMatchGroups();

    return 0;
}
