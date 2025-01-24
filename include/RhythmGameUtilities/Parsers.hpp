#pragma once

#include <map>
#include <regex>
#include <string>
#include <vector>

#include "Enums/Difficulty.h"
#include "Enums/NamedSection.h"
#include "Enums/TypeCode.h"

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

typedef struct
{
    char *key;
    char *values[10];
    int valueCount;
} KeyValuePairInternal;

typedef struct
{
    char *name;
    KeyValuePairInternal *lines;
    int lineCount;
} ChartSectionInternal;

std::regex CHART_SECTION_PATTERN("\\[([a-z]+)\\]\\s*\\{([^\\}]+)\\}",
                                 std::regex_constants::icase);

std::regex CHART_SECTION_LINE_PATTERN("([^=]+)\\s*=([^\\r\\n]+)");

std::regex JSON_VALUE_PATTERN("(\"[^\"]+\"|\\S+)");

std::map<std::string,
         std::vector<std::pair<std::string, std::vector<std::string>>>>
ParseSectionsFromChart(const char *contents)
{
    auto matches = FindAllMatches(contents, CHART_SECTION_PATTERN);

    std::map<std::string,
             std::vector<std::pair<std::string, std::vector<std::string>>>>
        sections;

    for (auto i = 0; i < matches.size(); i += 1)
    {
        auto parts = FindMatchGroups(matches[i].c_str(), CHART_SECTION_PATTERN);

        if (parts.size() < 3)
        {
            continue;
        }

        auto lines =
            FindAllMatches(parts[2].c_str(), CHART_SECTION_LINE_PATTERN);

        std::vector<std::pair<std::string, std::vector<std::string>>> items;

        for (auto j = 0; j < lines.size(); j += 1)
        {
            auto parts = Split(lines[j].c_str(), '=');

            auto key = Trim(parts[0].c_str());
            auto value = Trim(parts[1].c_str());

            auto values = FindAllMatches(value.c_str(), JSON_VALUE_PATTERN);

            for (auto k = 0; k < values.size(); k += 1)
            {
                values[k] =
                    std::regex_replace(values[k], std::regex("^\"|\"$"), "");
            }

            items.push_back(std::make_pair(key, values));
        }

        sections.insert({parts[1].c_str(), items});
    }

    return sections;
}

std::map<std::string, std::string> ParseMetaDataFromChartSection(
    std::vector<std::pair<std::string, std::vector<std::string>>> section)
{
    auto data = std::map<std::string, std::string>();

    for (auto &line : section)
    {
        data.insert({line.first, line.second.front()});
    }

    return data;
}

std::vector<TimeSignature> ParseTimeSignaturesFromChartSection(
    std::vector<std::pair<std::string, std::vector<std::string>>> section)
{
    auto timeSignaturesChanges = std::vector<TimeSignature>();

    for (auto &line : section)
    {
        if (line.second.front() == ToString(TypeCode::TimeSignatureMarker))
        {
            auto position = std::stoi(line.first);
            auto numerator = std::stoi(line.second.at(1));
            auto denominator =
                line.second.size() > 2 ? std::stoi(line.second.at(2)) : 2;

            timeSignaturesChanges.push_back({position, numerator, denominator});
        }
    }

    return timeSignaturesChanges;
}

std::vector<Tempo> ParseBpmFromChartSection(
    std::vector<std::pair<std::string, std::vector<std::string>>> section)
{
    auto bpmChanges = std::vector<Tempo>();

    for (auto &line : section)
    {
        if (line.second.front() == ToString(TypeCode::BPM_Marker))
        {
            auto position = std::stoi(line.first);
            auto bpm = std::stoi(line.second.at(1));

            bpmChanges.push_back({position, bpm});
        }
    }

    return bpmChanges;
}

std::vector<Note> ParseNotesFromChartSection(
    std::vector<std::pair<std::string, std::vector<std::string>>> section)
{
    auto notes = std::vector<Note>();

    for (auto &line : section)
    {
        if (line.second.front() == ToString(TypeCode::NoteMarker))
        {
            notes.push_back({std::stoi(line.first),
                             std::stoi(line.second.at(1)),
                             std::stoi(line.second.at(2))});
        }
    }

    return notes;
}

std::map<int, std::string> ParseLyricsFromChartSection(
    std::vector<std::pair<std::string, std::vector<std::string>>> section)
{
    auto lyrics = std::map<int, std::string>();

    for (auto &line : section)
    {
        if (line.second.back().rfind("lyric", 0) == 0)
        {
            lyrics.insert({std::stoi(line.first), line.second.at(1)});
        }
    }

    return lyrics;
}

} // namespace RhythmGameUtilities
