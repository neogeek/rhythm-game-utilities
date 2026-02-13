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

    auto *note = new Note{750};
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

void testCalculateTicksPerSecond()
{
    const int bpm = 120;
    const int resolution = 192;

    auto ticks = CalculateTicksPerSecond(bpm, resolution);

    assert(ticks == 384);

    std::cout << ".";
}

void testFindPositionsNearGivenTick()
{
    std::vector<Note> notes = {{768, 0, 0},  {960, 0, 0},  {1152, 0, 0},
                               {1536, 0, 0}, {1728, 0, 0}, {1920, 0, 0},
                               {2304, 0, 0}, {2496, 0, 0}, {2688, 0, 0},
                               {3072, 0, 0}, {3264, 0, 0}};

    auto matchedNotes = FindPositionsNearGivenTick(notes, 750);

    assert(1 == size(matchedNotes));

    assert(768 == matchedNotes[0].Position);

    assert(0 == size(FindPositionsNearGivenTick(notes, 100)));
    assert(768 == FindPositionsNearGivenTick(notes, 750)[0].Position);
    assert(1536 == FindPositionsNearGivenTick(notes, 1500)[0].Position);
    assert(0 == size(FindPositionsNearGivenTick(notes, 3200)));

    std::cout << ".";
}

void testIsOnTheBeat()
{
    const int bpm = 120;
    const float currentTime = 10;
    const float delta = 0.05F;

    auto isOnTheBeat = IsOnTheBeat(bpm, currentTime, delta);

    assert(true == isOnTheBeat);

    std::cout << ".";
}

void testIsOnTheBeatContinued()
{
    assert(IsOnTheBeat(120, 10) == true);
    assert(IsOnTheBeat(60, 1) == true);
    assert(IsOnTheBeat(60, 1.5f) == false);

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

auto main() -> int
{
    testCalculateAccuracyRatio();
    testCalculateBeatBars();
    testConvertSecondsToTicks();
    testConvertTickToPosition();
    testCalculateTicksPerSecond();
    testFindPositionsNearGivenTick();
    testIsOnTheBeat();
    testIsOnTheBeatContinued();
    testRoundUpToTheNearestMultiplier();
    testGenerateAdjacentKeyPairs();

    return 0;
}
