#pragma once

#include <climits>
#include <cmath>
#include <map>
#include <optional>
#include <vector>

#include "Structs/BeatBar.hpp"
#include "Structs/Note.hpp"
#include "Structs/Tempo.hpp"
#include "Structs/TimeSignature.hpp"

#include "Common.hpp"

namespace RhythmGameUtilities
{

const float SECONDS_PER_MINUTE = 60.0F;

/**
 * Calculate ticks per second.
 *
 * @param bpm The base BPM for a song.
 * @param resolution The resolution of the song.
 * @public
 */

inline auto CalculateTicksPerSecond(int bpm, int resolution) -> float
{
    return resolution * bpm / SECONDS_PER_MINUTE;
}

/**
 * Convert seconds to ticks.
 *
 * @param seconds The seconds to generate ticks with.
 * @param resolution The resolution of the song.
 * @param tempoChanges All tempo changes within the song.
 * @param timeSignatureChanges All time signature changes within the song.
 * @public
 */

inline auto
ConvertSecondsToTicks(float seconds, int resolution,
                      std::vector<Tempo> tempoChanges,
                      std::vector<TimeSignature> timeSignatureChanges) -> int
{
    auto tempoChangesIterator = tempoChanges.begin();
    auto timeSignatureIterator = timeSignatureChanges.begin();

    auto totalTicks = 0;
    auto remainingSeconds = seconds;
    auto previousTick = 0;
    auto previousBPM = tempoChangesIterator->BPM / 1000.0;

    while (remainingSeconds > 0)
    {
        int nextTempoChange = tempoChangesIterator != tempoChanges.end()
                                  ? tempoChangesIterator->Position
                                  : INT_MAX;

        int nextTimeSignatureChange =
            timeSignatureIterator != timeSignatureChanges.end()
                ? timeSignatureIterator->Position
                : INT_MAX;

        int nextChangeTick = std::min(nextTempoChange, nextTimeSignatureChange);

        float ticksPerSecond = CalculateTicksPerSecond(previousBPM, resolution);
        float timeForSegment = (nextChangeTick - previousTick) / ticksPerSecond;

        if (remainingSeconds <= timeForSegment)
        {
            totalTicks += static_cast<int>(remainingSeconds * ticksPerSecond);

            return totalTicks;
        }

        totalTicks += nextChangeTick - previousTick;
        remainingSeconds -= timeForSegment;
        previousTick = nextChangeTick;

        if (nextChangeTick == nextTempoChange)
        {
            previousBPM = tempoChangesIterator->BPM / 1000.0;
            ++tempoChangesIterator;
        }

        if (nextChangeTick == nextTimeSignatureChange)
        {
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

inline auto GenerateAdjacentKeyPairs(const std::map<int, int> &keyValuePairs)
    -> std::vector<std::tuple<int, int>>
{
    auto adjacentKeyPairs = std::vector<std::tuple<int, int>>();

    std::vector<int> keys;

    keys.reserve(keyValuePairs.size());

    for (auto item : keyValuePairs)
    {
        keys.push_back(item.first);
    }

    std::vector<int> sortedKeys(keys.begin(), keys.end());

    for (auto i = 0; i < sortedKeys.size() - 1; i += 1)
    {
        adjacentKeyPairs.emplace_back(sortedKeys[i], sortedKeys[i + 1]);
    }

    return adjacentKeyPairs;
}

inline auto CalculateBeatBars(const std::vector<Tempo> &tempoChanges,
                              int resolution, int ts, bool includeHalfNotes)
    -> std::vector<BeatBar>
{
    std::vector<BeatBar> beatBars;

    std::map<int, int> tempoChangePositions;

    for (const auto &tempoChange : tempoChanges)
    {
        tempoChangePositions[tempoChange.Position] = tempoChange.BPM;
    }

    auto keyValuePairs = GenerateAdjacentKeyPairs(tempoChangePositions);

    for (const auto &keyValuePair : keyValuePairs)
    {
        auto startTick = std::get<0>(keyValuePair);
        auto endTick = std::get<1>(keyValuePair);

        for (auto tick = startTick; tick < endTick; tick += resolution)
        {

            auto bpm = tempoChangePositions[startTick];

            beatBars.push_back({tick, bpm});

            if (includeHalfNotes && tick != endTick)
            {
                beatBars.push_back({tick + (resolution / 2), bpm});
            }
        }
    }

    return beatBars;
}

inline auto FindPositionNearGivenTick(std::vector<Note> notes, int tick,
                                      int delta = 50) -> std::optional<Note>
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

/**
 * Convert a tick to a 2D/3D position.
 *
 * @param tick The tick.
 * @param resolution The resolution of the song.
 * @public
 */

inline auto ConvertTickToPosition(int tick, int resolution) -> float
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

inline auto IsOnTheBeat(int bpm, float currentTime, float delta = 0.05F) -> bool
{
    const float beatsElapsed = currentTime * bpm / SECONDS_PER_MINUTE;

    return std::abs(beatsElapsed - std::round(beatsElapsed)) < delta;
}

/**
 * Rounds a value up the nearest multiplier.
 *
 * @param value The value to round.
 * @param multiplier The multiplier to round using.
 * @public
 */

inline auto RoundUpToTheNearestMultiplier(int value, int multiplier) -> int
{
    return static_cast<int>(std::ceil(static_cast<float>(value) / multiplier) *
                            multiplier);
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

inline auto CalculateAccuracyRatio(int position, int currentPosition,
                                   int delta = 50) -> float
{
    auto diff = position - currentPosition;

    auto ratio = InverseLerp(delta, 0, std::abs(diff));

    return ratio;
}

} // namespace RhythmGameUtilities
