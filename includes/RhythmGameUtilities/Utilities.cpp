#include <algorithm>
#include <cmath>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

#include "Utilities.h"

#include "Structs/Note.h"

float ConvertTicksToSeconds(float tick, int resolution, int bpm)
{
    return tick / (resolution * bpm) * 60.0f;
}

int ConvertSecondsToTicks(double seconds, int resolution, int bpm)
{
    return (int)(seconds / 60.0f * (resolution * bpm));
}

float CalculateScale(float baseBpm, float actualBpm, float speed)
{
    return actualBpm / baseBpm * speed;
}

bool IsOnTheBeat(float bpm, float currentTime)
{
    auto beatInterval = 60.0f / bpm;

    auto beatFraction = currentTime / beatInterval;

    auto difference = std::abs(beatFraction - std::round(beatFraction));

    return difference < 0.05f;
}

float Lerp(float a, float b, float t) { return (1 - t) * a + b * t; }

float InverseLerp(float a, float b, float v)
{
    return std::clamp(((v - a) / (b - a)), 0.0f, 1.0f);
}

float CalculateNoteHitAccuracy(Note *note, float buffer, int currentTick)
{
    auto hit = InverseLerp(note->Position - buffer, note->Position + buffer,
                           (float)currentTick);

    auto accuracy = InverseLerp(0.5f, 0.0f, fabs(hit - 0.5f));

    return accuracy;
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
