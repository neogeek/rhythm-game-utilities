#include <cassert>
#include <cmath>
#include <iostream>

#include "RhythmGameUtilities/Utilities.h"

void testConvertTicksToSeconds()
{
    const int tick = 2784;
    const int resolution = 192;
    const int bpm = 124;

    float seconds = ConvertTicksToSeconds(tick, resolution, bpm);

    assert(fabs(7.01f - seconds) < 0.01f);

    std::cout << ".";
}

void testConvertSecondsToTicks()
{
    const float seconds = 7.01f;
    const int resolution = 192;
    const int bpm = 124;

    assert(2781 == ConvertSecondsToTicks(seconds, resolution, bpm));

    std::cout << ".";
}

void testCalculateScale()
{
    const int baseBpm = 160;
    const float speed = 5;

    assert(5.0f == CalculateScale(baseBpm, 160, speed));
    assert(3.75f == CalculateScale(baseBpm, 120, speed));

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

void testCalculateNoteHitAccuracy()
{
    auto *note = new Note();

    note->Position = 2884;

    const int buffer = 60;

    assert(1 == CalculateNoteHitAccuracy(note, buffer, note->Position));
    assert(0 ==
           CalculateNoteHitAccuracy(note, buffer, note->Position - buffer));
    assert(0.5f ==
           CalculateNoteHitAccuracy(note, buffer, note->Position - buffer / 2));
    assert(0 ==
           CalculateNoteHitAccuracy(note, buffer, note->Position + buffer));
    assert(0.5f ==
           CalculateNoteHitAccuracy(note, buffer, note->Position + buffer / 2));

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
    testConvertTicksToSeconds();
    testConvertSecondsToTicks();
    testCalculateScale();
    testLerp();
    testInverseLerp();
    testCalculateNoteHitAccuracy();

    testTrim();
    testSplit();
    testFindAllMatches();
    testFindMatchGroups();

    return 0;
}
