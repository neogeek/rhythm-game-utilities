#include <cassert>
#include <cmath>
#include <iostream>
#include <tuple>

#include "RhythmGameUtilities/Structs/Tempo.hpp"
#include "RhythmGameUtilities/Structs/TimeSignature.hpp"

#include "RhythmGameUtilities/Utilities.hpp"

using namespace RhythmGameUtilities;

void testCalculateAccuracyRatio()
{
    const int seconds = 2;
    const int resolution = 192;
    const int positionDelta = 50;

    std::vector<Tempo> tempoChanges = {{0, 120000}};
    std::vector<TimeSignature> timeSignatureChanges = {{0, 4}};

    auto note = new Note{750};
    auto currentPosition = ConvertSecondsToTicks(
        seconds, resolution, tempoChanges, timeSignatureChanges);

    auto value =
        CalculateAccuracyRatio(note->Position, currentPosition, positionDelta);

    assert(abs(0.64 - value) < 0.01);

    std::cout << ".";
}

void testCalculateBeatBars()
{
    const int resolution = 192;
    const int timeSignature = 4;

    std::vector<Tempo> tempoChanges = {
        {0, 88000},      {3840, 112000},  {9984, 89600},  {22272, 112000},
        {33792, 111500}, {34560, 112000}, {42240, 111980}};

    auto beatBars =
        CalculateBeatBars(tempoChanges, resolution, timeSignature, true);

    assert(beatBars.size() == 440);

    std::cout << ".";
}

void testConvertSecondsToTicks()
{
    const int seconds = 5;
    const int resolution = 192;

    std::vector<Tempo> tempoChanges = {
        {0, 88000},      {3840, 112000},  {9984, 89600},  {22272, 112000},
        {33792, 111500}, {34560, 112000}, {42240, 111980}};

    std::vector<TimeSignature> timeSignatureChanges = {{0, 4, 2}};

    auto ticks = ConvertSecondsToTicks(seconds, resolution, tempoChanges,
                                       timeSignatureChanges);

    assert(1408 == ticks);

    std::cout << ".";
}

void testConvertTickToPosition()
{
    const int tick = 1056;
    const int resolution = 192;

    auto position = ConvertTickToPosition(tick, resolution);

    assert(abs(5.5 - position) < 0.01);

    std::cout << ".";
}

void testFindPositionNearGivenTick()
{
    std::vector<Note> notes = {{768, 0, 0},  {960, 0, 0},  {1152, 0, 0},
                               {1536, 0, 0}, {1728, 0, 0}, {1920, 0, 0},
                               {2304, 0, 0}, {2496, 0, 0}, {2688, 0, 0},
                               {3072, 0, 0}, {3264, 0, 0}};

    auto note = FindPositionNearGivenTick(notes, 750);

    assert(768 == note->Position);

    assert(std::nullopt == FindPositionNearGivenTick(notes, 100));
    assert(768 == FindPositionNearGivenTick(notes, 750)->Position);
    assert(1536 == FindPositionNearGivenTick(notes, 1500)->Position);
    assert(std::nullopt == FindPositionNearGivenTick(notes, 3200));

    std::cout << ".";
}

void testIsOnTheBeat()
{
    const int bpm = 120;
    const float currentTime = 10;
    const float delta = 0.05f;

    auto isOnTheBeat = IsOnTheBeat(bpm, currentTime, delta);

    assert(true == isOnTheBeat);

    std::cout << ".";
}

void testRoundUpToTheNearestMultiplier()
{
    auto value = RoundUpToTheNearestMultiplier(12, 10);

    assert(20 == value);

    std::cout << ".";
}

void testGenerateAdjacentKeyPairs()
{
    std::map<int, int> tempoChanges = {
        {0, 88000},      {3840, 112000},  {9984, 89600},  {22272, 112000},
        {33792, 111500}, {34560, 112000}, {42240, 111980}};

    auto adjacentKeyPairs = GenerateAdjacentKeyPairs(tempoChanges);

    assert(adjacentKeyPairs.size() == 6);
    assert(adjacentKeyPairs[0] == std::make_tuple(0, 3840));
    assert(adjacentKeyPairs[1] == std::make_tuple(3840, 9984));

    std::cout << ".";
}

int main()
{
    testCalculateAccuracyRatio();
    testCalculateBeatBars();
    testConvertSecondsToTicks();
    testConvertTickToPosition();
    testFindPositionNearGivenTick();
    testIsOnTheBeat();
    testRoundUpToTheNearestMultiplier();
    testGenerateAdjacentKeyPairs();

    return 0;
}
