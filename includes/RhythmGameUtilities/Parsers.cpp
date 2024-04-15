#pragma once

#include <iterator>
#include <map>
#include <regex>
#include <string.h>
#include <vector>

#include "Parsers.h"
#include "Utilities.h"

std::regex CHART_SECTION_PATTERN("\\[([a-z]+)\\]\\s*\\{([^\\}]+)\\}",
                                 std::regex_constants::icase);

std::regex CHART_SECTION_LINE_PATTERN("([^=]+)\\s*=([^\\r\\n]+)");

ChartSection *ParseSectionsFromChart(const char *contents, int *outSize)
{
    auto matches = FindAllMatches(contents, CHART_SECTION_PATTERN);

    auto sectionsInternal = std::vector<std::vector<std::string>>();

    for (auto i = 0; i < matches.size(); i += 1)
    {
        auto parts = FindMatchGroups(matches[i].c_str(), CHART_SECTION_PATTERN);

        if (parts.size() >= 3)
        {
            sectionsInternal.push_back({parts[1], parts[2]});
        }
    }

    *outSize = sectionsInternal.size();

    auto sections =
        (ChartSection *)malloc(sectionsInternal.size() * sizeof(ChartSection));

    for (auto i = 0; i < sectionsInternal.size(); i += 1)
    {
        sections[i].name =
            (char *)malloc(strlen(sectionsInternal[i][0].c_str()) + 1);
        strcpy(sections[i].name, sectionsInternal[i][0].c_str());

        auto linesInternal = FindAllMatches(sectionsInternal[i][1].c_str(),
                                            CHART_SECTION_LINE_PATTERN);

        sections[i].lines =
            (KeyValuePair *)malloc(linesInternal.size() * sizeof(KeyValuePair));

        sections[i].lineCount = linesInternal.size();

        for (auto j = 0; j < linesInternal.size(); j += 1)
        {
            auto parts = Split(linesInternal[j].c_str(), '=');

            auto key = Trim(parts[0].c_str());
            auto value = Trim(parts[1].c_str());

            sections[i].lines[j].key = (char *)malloc(strlen(key.c_str()) + 1);
            strcpy(sections[i].lines[j].key, key.c_str());

            sections[i].lines[j].value =
                (char *)malloc(strlen(value.c_str()) + 1);
            strcpy(sections[i].lines[j].value, value.c_str());
        }
    }

    return sections;
}
