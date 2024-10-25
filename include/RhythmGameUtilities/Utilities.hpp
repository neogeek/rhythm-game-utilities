#pragma once

#include <cmath>
#include <map>
#include <optional>
#include <vector>

#include "Common.hpp"
#include "Structs/BeatBar.h"
#include "Structs/Note.h"

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
 * @public
 */

int ConvertSecondsToTicks(float seconds, int resolution,
                          std::map<int, int> bpmChanges)
{
    auto totalTicks = 0;
    auto remainingSeconds = seconds;
    auto previousTick = 0;
    auto previousBPM = bpmChanges.begin()->second / 1000;

    for (auto const &[currentTick, value] : bpmChanges)
    {
        auto timeForSegment = (currentTick - previousTick) /
                              (resolution * previousBPM / SECONDS_PER_MINUTE);

        if (remainingSeconds <= timeForSegment)
        {
            totalTicks += (int)(remainingSeconds * previousBPM /
                                SECONDS_PER_MINUTE * resolution);

            return totalTicks;
        }

        totalTicks += currentTick - previousTick;
        remainingSeconds -= timeForSegment;
        previousTick = currentTick;
        previousBPM = value / 1000;
    }

    totalTicks +=
        (int)(remainingSeconds * previousBPM / SECONDS_PER_MINUTE * resolution);

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

std::vector<BeatBar> CalculateBeatBars(std::map<int, int> bpmChanges,
                                       int resolution, int ts,
                                       bool includeHalfNotes)
{
    std::vector<BeatBar> beatBars;

    auto keyValuePairs = GenerateAdjacentKeyPairs(bpmChanges);

    for (const auto &keyValuePair : keyValuePairs)
    {
        auto startTick = std::get<0>(keyValuePair);
        auto endTick = std::get<1>(keyValuePair);

        for (auto tick = startTick; tick < endTick; tick += resolution)
        {
            beatBars.push_back({tick, bpmChanges[startTick]});

            if (includeHalfNotes && tick != endTick)
            {
                beatBars.push_back(
                    {tick + resolution / 2, bpmChanges[startTick]});
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
        return tick / (float)resolution;
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
        auto beatInterval = SECONDS_PER_MINUTE / (float)bpm;

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
        return (int)std::ceil((float)value / multiplier) * multiplier;
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
