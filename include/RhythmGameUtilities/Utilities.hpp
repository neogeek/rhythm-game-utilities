#pragma once

#include <climits>
#include <cmath>
#include <map>
#include <optional>
#include <vector>

#include "Structs/BeatBar.h"
#include "Structs/Note.h"
#include "Structs/Tempo.h"
#include "Structs/TimeSignature.h"

#include "Common.hpp"

#ifdef _WIN32
#define PACKAGE_API __declspec(dllexport)
#else
#define PACKAGE_API
#endif

namespace RhythmGameUtilities
{

const float SECONDS_PER_MINUTE = 60.0f;

/**
 * Convert seconds to ticks.
 *
 * @param seconds The seconds to generate ticks with.
 * @param resolution The resolution of the song.
 * @param bpmChanges All BPM changes within the song.
 * @param timeSignatureChanges All time signature changes within the song.
 * @public
 */

int ConvertSecondsToTicks(float seconds, int resolution,
                          std::vector<Tempo> bpmChanges,
                          std::vector<TimeSignature> timeSignatureChanges)
{
    auto bpmIterator = bpmChanges.begin();
    auto timeSignatureIterator = timeSignatureChanges.begin();

    auto totalTicks = 0;
    auto remainingSeconds = seconds;
    auto previousTick = 0;
    auto previousBPM = bpmIterator->BPM / 1000.0;
    auto previousTimeSignature = timeSignatureIterator->Numerator;

    while (remainingSeconds > 0)
    {
        int nextBPMChange =
            bpmIterator != bpmChanges.end() ? bpmIterator->Position : INT_MAX;

        int nextTimeSignatureChange =
            timeSignatureIterator != timeSignatureChanges.end()
                ? timeSignatureIterator->Position
                : INT_MAX;

        int nextChangeTick = std::min(nextBPMChange, nextTimeSignatureChange);

        float ticksPerSecond = resolution * previousBPM / SECONDS_PER_MINUTE;
        float timeForSegment = (nextChangeTick - previousTick) / ticksPerSecond;

        if (remainingSeconds <= timeForSegment)
        {
            totalTicks += static_cast<int>(remainingSeconds * ticksPerSecond);

            return totalTicks;
        }

        totalTicks += nextChangeTick - previousTick;
        remainingSeconds -= timeForSegment;
        previousTick = nextChangeTick;

        if (nextChangeTick == nextBPMChange)
        {
            previousBPM = bpmIterator->BPM / 1000.0;
            ++bpmIterator;
        }

        if (nextChangeTick == nextTimeSignatureChange)
        {
            previousTimeSignature = timeSignatureIterator->Numerator;
            ++timeSignatureIterator;
        }
    }

    float ticksPerSecond = resolution * previousBPM / SECONDS_PER_MINUTE;

    totalTicks += static_cast<int>(remainingSeconds * ticksPerSecond);

    return totalTicks;
}

/**
 * Takes a map of key/value pairs and returns a list of adjacent key pairs.
 *
 * @param keyValuePairs Key/value pairs map.
 * @public
 */

std::vector<std::tuple<int, int>>
GenerateAdjacentKeyPairs(std::map<int, int> keyValuePairs)
{
    auto adjacentKeyPairs = std::vector<std::tuple<int, int>>();

    std::vector<int> keys;

    for (auto item : keyValuePairs)
    {
        keys.push_back(item.first);
    }

    std::vector<int> sortedKeys(keys.begin(), keys.end());

    for (auto i = 0; i < sortedKeys.size() - 1; i += 1)
    {
        adjacentKeyPairs.push_back(
            std::make_tuple(sortedKeys[i], sortedKeys[i + 1]));
    }

    return adjacentKeyPairs;
}

std::vector<BeatBar> CalculateBeatBars(std::vector<Tempo> bpmChanges,
                                       int resolution, int ts,
                                       bool includeHalfNotes)
{
    std::vector<BeatBar> beatBars;

    std::map<int, int> bpmChangePositions;

    for (const auto &bpmChange : bpmChanges)
    {
        bpmChangePositions[bpmChange.Position] = bpmChange.BPM;
    }

    auto keyValuePairs = GenerateAdjacentKeyPairs(bpmChangePositions);

    for (const auto &keyValuePair : keyValuePairs)
    {
        auto startTick = std::get<0>(keyValuePair);
        auto endTick = std::get<1>(keyValuePair);

        for (auto tick = startTick; tick < endTick; tick += resolution)
        {

            auto position = tick;
            auto bpm = bpmChangePositions[startTick];

            beatBars.push_back({tick, bpm});

            if (includeHalfNotes && tick != endTick)
            {
                beatBars.push_back({tick + resolution / 2, bpm});
            }
        }
    }

    return beatBars;
}

std::optional<Note> FindPositionNearGivenTick(std::vector<Note> notes, int tick,
                                              int delta = 50)
{
    auto left = 0;
    auto right = static_cast<int>(notes.size()) - 1;

    while (left <= right)
    {
        auto mid = (left + right) / 2;

        auto currentPosition = notes[mid].Position;

        if (currentPosition + delta < tick)
        {
            left = mid + 1;
        }
        else if (currentPosition - delta > tick)
        {
            right = mid - 1;
        }
        else
        {
            return notes[mid];
        }
    }

    return std::nullopt;
}

extern "C"
{
    /**
     * Convert a tick to a 2D/3D position.
     *
     * @param tick The tick.
     * @param resolution The resolution of the song.
     * @public
     */

    PACKAGE_API float ConvertTickToPosition(int tick, int resolution)
    {
        return tick / static_cast<float>(resolution);
    }

    /**
     * Checks to see if the current time of a game or audio file is on the beat.
     *
     * @param bpm The base BPM for a song.
     * @param currentTime A timestamp to compare to the BPM.
     * @param delta The plus/minus delta to test the current time against.
     * @public
     */

    PACKAGE_API bool IsOnTheBeat(int bpm, float currentTime,
                                 float delta = 0.05f)
    {
        auto beatInterval = SECONDS_PER_MINUTE / static_cast<float>(bpm);

        auto beatFraction = currentTime / beatInterval;

        auto difference = std::abs(beatFraction - std::round(beatFraction));

        auto result = difference < delta;

        return result;
    }

    /**
     * Rounds a value up the nearest multiplier.
     *
     * @param value The value to round.
     * @param multiplier The multiplier to round using.
     * @public
     */

    PACKAGE_API int RoundUpToTheNearestMultiplier(int value, int multiplier)
    {
        return static_cast<int>(
            std::ceil(static_cast<float>(value) / multiplier) * multiplier);
    }

    /**
     * Calculated the accuracy ratio of the current position against a static
     * position.
     *
     * @param position The position to test against.
     * @param currentPosition The current position.
     * @param delta The plus/minus delta to test the current position against.
     * @public
     */

    PACKAGE_API float CalculateAccuracyRatio(int position, int currentPosition,
                                             int delta = 50)
    {
        auto diff = position - currentPosition;

        auto ratio = InverseLerp(delta, 0, std::abs(diff));

        return ratio;
    }
}

} // namespace RhythmGameUtilities
