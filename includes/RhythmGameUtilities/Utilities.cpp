#include <algorithm>
#include <cmath>
#include <map>
#include <regex>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

#include "Utilities.h"

#include "Structs/BeatBar.h"
#include "Structs/Note.h"

const float SECONDS_PER_MINUTE = 60.0f;

float ConvertTickToPosition(float tick, int resolution)
{
    return tick / resolution;
}

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

int ConvertSecondsToTicksInternal(float seconds, int resolution,
                                  int *bpmChangesKeys, int *bpmChangesValues,
                                  int bpmChangesSize)
{
    std::map<int, int> bpmChanges;

    for (auto i = 0; i < bpmChangesSize; i += 1)
    {
        bpmChanges[bpmChangesKeys[i]] = bpmChangesValues[i];
    }

    return ConvertSecondsToTicks(seconds, resolution, bpmChanges);
}

bool IsOnTheBeat(float bpm, float currentTime)
{
    auto beatInterval = SECONDS_PER_MINUTE / bpm;

    auto beatFraction = currentTime / beatInterval;

    auto difference = std::abs(beatFraction - std::round(beatFraction));

    auto result = difference < 0.05f;

    return result;
}

int RoundUpToTheNearestMultiplier(int value, int multiplier)
{
    return (int)ceil((float)value / multiplier) * multiplier;
}

float Lerp(float a, float b, float t) { return (1 - t) * a + b * t; }

float InverseLerp(float a, float b, float v)
{
    return std::clamp(((v - a) / (b - a)), 0.0f, 1.0f);
}

std::string Trim(const char *contents)
{
    return std::regex_replace(contents, std::regex("^\\s+|\\s+$"), "");
}

std::vector<std::string> Split(const char *contents, const char delimiter)
{
    auto parts = std::vector<std::string>();

    std::stringstream input(contents);

    std::string str;

    while (std::getline(input, str, delimiter))
    {
        parts.push_back(str);
    }

    return parts;
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

        for (auto tick = startTick; tick <= endTick; tick += resolution)
        {
            beatBars.push_back(
                {.Position = tick, .BPM = bpmChanges[startTick]});

            if (includeHalfNotes && tick != endTick)
            {
                beatBars.push_back({.Position = tick + resolution / 2,
                                    .BPM = bpmChanges[startTick]});
            }
        }
    }

    return beatBars;
}

BeatBar *CalculateBeatBarsInternal(int *bpmChangesKeys, int *bpmChangesValues,
                                   int bpmChangesSize, int resolution, int ts,
                                   bool includeHalfNotes, int *outSize)
{
    auto bpmChanges = std::map<int, int>();

    for (auto i = 0; i < bpmChangesSize; i += 1)
    {
        bpmChanges[bpmChangesKeys[i]] = bpmChangesValues[i];
    }

    auto internalBeatBars =
        CalculateBeatBars(bpmChanges, resolution, ts, includeHalfNotes);

    *outSize = internalBeatBars.size();

    auto beatBars =
        (BeatBar *)malloc(internalBeatBars.size() * sizeof(BeatBar));

    for (auto i = 0; i < internalBeatBars.size(); i += 1)
    {
        beatBars[i] = internalBeatBars[i];
    }

    return beatBars;
}

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

    for (auto i = 0; i < size(sortedKeys) - 1; i += 1)
    {
        adjacentKeyPairs.push_back(
            std::make_tuple(sortedKeys[i], sortedKeys[i + 1]));
    }

    return adjacentKeyPairs;
}

std::vector<std::string> FindAllMatches(const char *contents,
                                        std::regex pattern)
{
    auto currentMatch =
        std::cregex_iterator(contents, contents + strlen(contents), pattern);
    auto lastMatch = std::cregex_iterator();

    auto matches = std::vector<std::string>();

    while (currentMatch != lastMatch)
    {
        auto match = *currentMatch;

        matches.push_back(match.str(0));

        currentMatch++;
    }

    return matches;
}

std::vector<std::string> FindMatchGroups(const char *contents,
                                         std::regex pattern)
{
    auto currentMatch =
        std::cregex_iterator(contents, contents + strlen(contents), pattern);

    auto matches = std::vector<std::string>();

    auto match = *currentMatch;

    for (auto i = 0; i < match.size(); i += 1)
    {
        matches.push_back(match.str(i));
    }

    return matches;
}
