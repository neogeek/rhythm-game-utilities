#include <cassert>
#include <cmath>
#include <iostream>
#include <tuple>

#include "RhythmGameUtilities/Structs/Tempo.hpp"
#include "RhythmGameUtilities/Structs/TimeSignature.hpp"

#include "RhythmGameUtilities/UtilitiesInternal.hpp"

using namespace RhythmGameUtilities;

void testCalculateAccuracyRatioInternal()
{
    const int seconds = 2;
    const int resolution = 192;
    const int positionDelta = 50;

    std::vector<Tempo> tempoChanges = {{0, 120000}};
    std::vector<TimeSignature> timeSignatureChanges = {{0, 4}};

    auto note = new Note{750};
    auto currentPosition = ConvertSecondsToTicksInternal(
        seconds, resolution, &tempoChanges[0], tempoChanges.size(),
        &timeSignatureChanges[0], timeSignatureChanges.size());

    auto value = CalculateAccuracyRatioInternal(note->Position, currentPosition,
                                                positionDelta);

    assert(abs(0.64 - value) < 0.01);

    std::cout << ".";
}

void testCalculateBeatBarsInternal()
{
    std::vector<Tempo> tempoChanges = {
        {0, 88000},      {3840, 112000},  {9984, 89600},  {22272, 112000},
        {33792, 111500}, {34560, 112000}, {42240, 111980}};

    int outSize;

    auto beatBars = CalculateBeatBarsInternal(
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

void testConvertTickToPositionInternal()
{
    const int tick = 1056;
    const int resolution = 192;

    auto position = ConvertTickToPositionInternal(tick, resolution);

    assert(abs(5.5 - position) < 0.01);

    std::cout << ".";
}

void testIsOnTheBeatInternal()
{
    const int bpm = 120;
    const float currentTime = 10;
    const float delta = 0.05f;

    auto isOnTheBeat = IsOnTheBeatInternal(bpm, currentTime, delta);

    assert(true == isOnTheBeat);

    std::cout << ".";
}

void testRoundUpToTheNearestMultiplierInternal()
{
    auto value = RoundUpToTheNearestMultiplierInternal(12, 10);

    assert(20 == value);

    std::cout << ".";
}

int main()
{
    testCalculateAccuracyRatioInternal();
    testCalculateBeatBarsInternal();
    testConvertSecondsToTicksInternal();
    testConvertTickToPositionInternal();
    testIsOnTheBeatInternal();
    testRoundUpToTheNearestMultiplierInternal();

    return 0;
}
