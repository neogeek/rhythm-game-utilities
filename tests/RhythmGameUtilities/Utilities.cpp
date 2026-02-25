#include <cassert>
#include <cmath>
#include <iostream>
#include <tuple>

#include "RhythmGameUtilities/Enums/Accuracy.hpp"
#include "RhythmGameUtilities/Enums/Timing.hpp"
#include "RhythmGameUtilities/Structs/Tempo.hpp"
#include "RhythmGameUtilities/Structs/TimeSignature.hpp"

#include "RhythmGameUtilities/Utilities.hpp"

using namespace RhythmGameUtilities;

void testCalculateAccuracy()
{
    const int positionDelta = 50;

    auto *note = new Note{750};

    assert(CalculateAccuracy(note->Position, 695, positionDelta) ==
           Accuracy::Invalid);

    assert(CalculateAccuracy(note->Position, 700, positionDelta) ==
           Accuracy::Poor);

    assert(CalculateAccuracy(note->Position, 710, positionDelta) ==
           Accuracy::Fair);

    assert(CalculateAccuracy(note->Position, 725, positionDelta) ==
           Accuracy::Good);

    assert(CalculateAccuracy(note->Position, 735, positionDelta) ==
           Accuracy::Great);

    assert(CalculateAccuracy(note->Position, 750, positionDelta) ==
           Accuracy::Perfect);

    assert(CalculateAccuracy(note->Position, 765, positionDelta) ==
           Accuracy::Great);

    assert(CalculateAccuracy(note->Position, 775, positionDelta) ==
           Accuracy::Good);

    assert(CalculateAccuracy(note->Position, 790, positionDelta) ==
           Accuracy::Fair);

    assert(CalculateAccuracy(note->Position, 800, positionDelta) ==
           Accuracy::Poor);

    assert(CalculateAccuracy(note->Position, 805, positionDelta) ==
           Accuracy::Invalid);

    std::cout << ".";
}

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

    assert(abs(0.36 - abs(value)) < 0.01);

    std::cout << ".";
}

void testCalculateTiming()
{
    const int positionDelta = 50;

    auto *note = new Note{750};

    assert(CalculateTiming(note->Position, 725, positionDelta) ==
           Timing::Early);
    assert(CalculateTiming(note->Position, 750, positionDelta) == Timing::Hit);
    assert(CalculateTiming(note->Position, 775, positionDelta) == Timing::Late);

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

void testFindNotesNearGivenTick()
{
    std::vector<Note> notes = {{110}, {120}, {130}, {140}, {150},
                               {160}, {170}, {180}, {190}, {200}};

    auto foundNotes = FindNotesNearGivenTick(notes, 160, 20);

    assert(5 == size(foundNotes));

    assert(140 == foundNotes[0].Position);
    assert(150 == foundNotes[1].Position);
    assert(160 == foundNotes[2].Position);
    assert(170 == foundNotes[3].Position);
    assert(180 == foundNotes[4].Position);

    std::cout << ".";
}

void testFindNotesNearGivenTickContinued()
{
    std::vector<Note> notes = {{110}, {120}, {130}, {140}, {150},
                               {160}, {170}, {180}, {190}, {200}};

    assert(0 == size(FindNotesNearGivenTick(notes, 50, 20)));
    assert(110 == FindNotesNearGivenTick(notes, 130, 20)[0].Position);
    assert(170 == FindNotesNearGivenTick(notes, 190, 20)[0].Position);
    assert(0 == size(FindNotesNearGivenTick(notes, 300, 20)));

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
    testCalculateAccuracy();
    testCalculateAccuracyRatio();
    testCalculateTiming();
    testCalculateBeatBars();
    testConvertSecondsToTicks();
    testConvertTickToPosition();
    testCalculateTicksPerSecond();
    testFindNotesNearGivenTick();
    testFindNotesNearGivenTickContinued();
    testIsOnTheBeat();
    testIsOnTheBeatContinued();
    testRoundUpToTheNearestMultiplier();
    testGenerateAdjacentKeyPairs();

    return 0;
}
