#pragma once

#include <map>
#include <regex>
#include <string>
#include <vector>

#include "Enums/TypeCode.hpp"

#include "Structs/Note.hpp"
#include "Structs/Tempo.hpp"
#include "Structs/TimeSignature.hpp"

#include "Common.hpp"

namespace RhythmGameUtilities
{

using KeyValuePairInternal = struct
{
    char *key;
    char *values[10];
    int valueCount;
};

using ChartSectionInternal = struct
{
    char *name;
    KeyValuePairInternal *lines;
    int lineCount;
};

std::regex CHART_SECTION_PATTERN(R"(\[([a-z]+)\]\s*\{([^\}]+)\})",
                                 std::regex_constants::icase);

std::regex CHART_SECTION_LINE_PATTERN(R"(([^=]+)\s*=([^\r\n]+))");

std::regex JSON_VALUE_PATTERN(R"(("[^"]+"|\S+))");

inline auto ParseSectionsFromChart(const char *contents)
    -> std::map<std::string,
                std::vector<std::pair<std::string, std::vector<std::string>>>>
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

            items.emplace_back(key, values);
        }

        sections.insert({parts[1].c_str(), items});
    }

    return sections;
}

inline auto ParseMetaDataFromChartSection(
    std::vector<std::pair<std::string, std::vector<std::string>>> section)
    -> std::map<std::string, std::string>
{
    auto data = std::map<std::string, std::string>();

    for (auto &line : section)
    {
        data.insert({line.first, line.second.front()});
    }

    return data;
}

inline auto ParseTimeSignatureChangesFromChartSection(
    std::vector<std::pair<std::string, std::vector<std::string>>> section)
    -> std::vector<TimeSignature>
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

inline auto ParseTempoChangesFromChartSection(
    std::vector<std::pair<std::string, std::vector<std::string>>> section)
    -> std::vector<Tempo>
{
    auto tempoChanges = std::vector<Tempo>();

    for (auto &line : section)
    {
        if (line.second.front() == ToString(TypeCode::BPM_Marker))
        {
            auto position = std::stoi(line.first);
            auto bpm = std::stoi(line.second.at(1));

            tempoChanges.push_back({position, bpm});
        }
    }

    return tempoChanges;
}

inline auto ParseNotesFromChartSection(
    std::vector<std::pair<std::string, std::vector<std::string>>> section)
    -> std::vector<Note>
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

inline auto ParseLyricsFromChartSection(
    std::vector<std::pair<std::string, std::vector<std::string>>> section)
    -> std::map<int, std::string>
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
