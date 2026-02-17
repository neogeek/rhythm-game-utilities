// Rhythm Game Utilities - https://github.com/neogeek/rhythm-game-utilities
//
// ░█▀▄░█░█░█░█░▀█▀░█░█░█▄█░░░█▀▀░█▀█░█▄█░█▀▀░░░█░█░▀█▀░▀█▀░█░░░▀█▀░▀█▀░▀█▀░█▀▀░█▀▀
// ░█▀▄░█▀█░░█░░░█░░█▀█░█░█░░░█░█░█▀█░█░█░█▀▀░░░█░█░░█░░░█░░█░░░░█░░░█░░░█░░█▀▀░▀▀█
// ░▀░▀░▀░▀░░▀░░░▀░░▀░▀░▀░▀░░░▀▀▀░▀░▀░▀░▀░▀▀▀░░░▀▀▀░░▀░░▀▀▀░▀▀▀░▀▀▀░░▀░░▀▀▀░▀▀▀░▀▀▀
//
// Copyright (c) Scott Doxey. All Rights Reserved. Licensed under the MIT
// License. See LICENSE in the project root for license information.

#pragma once

#include <climits>
#include <cmath>
#include <map>
#include <vector>

#include "Enums/Accuracy.hpp"
#include "Enums/Timing.hpp"

#include "Structs/BeatBar.hpp"
#include "Structs/Note.hpp"
#include "Structs/Tempo.hpp"
#include "Structs/TimeSignature.hpp"

#include "Common.hpp"

#ifdef _WIN32
#define PACKAGE_API __declspec(dllexport)
#else
#define PACKAGE_API
#endif

namespace RhythmGameUtilities
{

const float SECONDS_PER_MINUTE = 60.0F;

extern "C"
{
    /**
     * Calculate ticks per second.
     *
     * @param bpm The base BPM for a song.
     * @param resolution The resolution of the song.
     * @public
     */

    PACKAGE_API auto CalculateTicksPerSecond(int bpm, int resolution) -> float
    {
        return resolution * bpm / SECONDS_PER_MINUTE;
    }
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

inline auto ConvertSecondsToTicks(
    float seconds, int resolution, const std::vector<Tempo> &tempoChanges,
    const std::vector<TimeSignature> &timeSignatureChanges) -> int
{
    if (tempoChanges.empty())
    {
        return 0;
    }

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

    adjacentKeyPairs.reserve(keyValuePairs.size() - 1);

    auto current = keyValuePairs.begin();
    auto next = std::next(current);

    while (next != keyValuePairs.end())
    {
        adjacentKeyPairs.emplace_back(current->first, next->first);
        current++;
        next++;
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

inline auto FindNotesNearGivenTick(const std::vector<Note> &notes, int tick,
                                   int delta = 50) -> std::vector<Note>
{
    std::vector<Note> foundNotes;

    auto length = static_cast<int>(notes.size());

    auto left = 0;
    auto right = length - 1;

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
            while (left >= 0 && notes[left].Position + delta >= tick)
            {
                foundNotes.emplace_back(notes[left]);
                left -= 1;
            }

            while (right < length && notes[right].Position - delta <= tick)
            {
                foundNotes.emplace_back(notes[right]);
                right += 1;
            }

            break;
        }
    }

    return foundNotes;
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

    PACKAGE_API auto ConvertTickToPosition(int tick, int resolution) -> float
    {
        return tick / static_cast<float>(resolution);
    }
}
extern "C"
{
    /**
     * Checks to see if the current time of a game or audio file is on the beat.
     *
     * @param bpm The base BPM for a song.
     * @param currentTime A timestamp to compare to the BPM.
     * @param delta The plus/minus delta to test the current time against.
     * @public
     */

    PACKAGE_API auto IsOnTheBeat(int bpm, float currentTime,
                                 float delta = 0.05F) -> bool
    {
        const float beatsElapsed = currentTime * bpm / SECONDS_PER_MINUTE;

        return std::abs(beatsElapsed - std::round(beatsElapsed)) < delta;
    }
}

extern "C"
{
    /**
     * Rounds a value up the nearest multiplier.
     *
     * @param value The value to round.
     * @param multiplier The multiplier to round using.
     * @public
     */

    PACKAGE_API auto RoundUpToTheNearestMultiplier(int value, int multiplier)
        -> int
    {
        return static_cast<int>(
            std::ceil(static_cast<float>(value) / multiplier) * multiplier);
    }
}

extern "C"
{
    /**
     * Calculated the accuracy ratio of the current position against a static
     * position.
     *
     * @param position The position to test against.
     * @param currentPosition The current position.
     * @param delta The plus/minus delta to test the current position against.
     * @public
     */

    PACKAGE_API auto CalculateAccuracyRatio(int position, int currentPosition,
                                            int delta = 50) -> float
    {
        auto diff = position - currentPosition;

        auto ratio = InverseLerpUnclamped(0, delta, diff);

        return ratio;
    }
}

extern "C"
{
    PACKAGE_API auto CalculateAccuracy(int position, int currentPosition,
                                       int delta = 50) -> Accuracy
    {
        auto ratio = CalculateAccuracyRatio(position, currentPosition, delta);

        auto absoluteRatio = std::abs(ratio);

        if (absoluteRatio <= 0.2f)
        {
            return Accuracy::Perfect;
        }

        if (absoluteRatio <= 0.35f)
        {
            return Accuracy::Great;
        }

        if (absoluteRatio <= 0.75f)
        {
            return Accuracy::Good;
        }

        if (absoluteRatio <= 0.85f)
        {
            return Accuracy::Fair;
        }

        if (absoluteRatio <= 1)
        {
            return Accuracy::Poor;
        }

        return Accuracy::Invalid;
    }
}

extern "C"
{
    PACKAGE_API auto CalculateTiming(int position, int currentPosition,
                                     int delta = 50) -> Timing
    {
        auto ratio = CalculateAccuracyRatio(position, currentPosition, delta);

        if (std::abs(ratio) >= 1)
        {
            return Timing::Miss;
        }

        if (ratio >= 0.5f)
        {
            return Timing::Early;
        }

        if (ratio <= -0.5f)
        {
            return Timing::Late;
        }

        return Timing::Hit;
    }
}

} // namespace RhythmGameUtilities
