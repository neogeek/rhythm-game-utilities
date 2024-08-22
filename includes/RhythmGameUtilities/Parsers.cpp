#include <iterator>
#include <map>
#include <regex>
#include <string.h>
#include <vector>

#include "Parsers.h"
#include "Utilities.h"
#include <iostream>

namespace RhythmGameUtilities
{

std::regex CHART_SECTION_PATTERN("\\[([a-z]+)\\]\\s*\\{([^\\}]+)\\}",
                                 std::regex_constants::icase);

std::regex CHART_SECTION_LINE_PATTERN("([^=]+)\\s*=([^\\r\\n]+)");

std::regex JSON_VALUE_PATTERN("(\"[^\"]+\"|\\S+)");

std::vector<ChartSection> ParseSectionsFromChart(const char *contents)
{
    auto matches = FindAllMatches(contents, CHART_SECTION_PATTERN);

    auto sections = std::vector<ChartSection>();

    for (auto i = 0; i < matches.size(); i += 1)
    {
        auto parts = FindMatchGroups(matches[i].c_str(), CHART_SECTION_PATTERN);

        if (parts.size() < 3)
        {
            continue;
        }

        ChartSection section;

        section.name = parts[1].c_str();

        auto lines =
            FindAllMatches(parts[2].c_str(), CHART_SECTION_LINE_PATTERN);

        section.lines =
            std::vector<std::pair<std::string, std::vector<std::string>>>();

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

            section.lines.push_back(std::make_pair(key, values));
        }

        sections.push_back(section);
    }

    return sections;
}

ChartSectionInternal *ParseSectionsFromChartInternal(const char *contents,
                                                     int *outSize)
{
    auto internalSections = ParseSectionsFromChart(contents);

    *outSize = internalSections.size();

    auto sections = (ChartSectionInternal *)malloc(
        internalSections.size() * sizeof(ChartSectionInternal));

    for (auto i = 0; i < internalSections.size(); i += 1)
    {
        sections[i].name =
            (char *)malloc(strlen(internalSections[i].name.c_str()) + 1);
        strcpy(sections[i].name, internalSections[i].name.c_str());

        sections[i].lines = (KeyValuePairInternal *)malloc(
            internalSections[i].lines.size() * sizeof(KeyValuePairInternal));

        sections[i].lineCount = internalSections[i].lines.size();

        for (auto j = 0; j < internalSections[i].lines.size(); j += 1)
        {
            sections[i].lines[j].key = (char *)malloc(
                strlen(internalSections[i].lines[j].first.c_str()) + 1);
            strcpy(sections[i].lines[j].key,
                   internalSections[i].lines[j].first.c_str());

            auto values = internalSections[i].lines[j].second;

            for (auto k = 0; k < values.size(); k += 1)
            {
                sections[i].lines[j].values[k] =
                    (char *)malloc(strlen(values[k].c_str()) + 1);
                strcpy(sections[i].lines[j].values[k], values[k].c_str());
            }

            sections[i].lines[j].valueCount = values.size();
        }
    }

    return sections;
}

} // namespace RhythmGameUtilities
