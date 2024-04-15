#pragma once

#include <iterator>
#include <map>
#include <regex>
#include <string.h>
#include <vector>

#include "Parsers.h"
#include "Utilities.h"
#include <iostream>

std::regex CHART_SECTION_PATTERN("\\[([a-z]+)\\]\\s*\\{([^\\}]+)\\}",
                                 std::regex_constants::icase);

std::regex CHART_SECTION_LINE_PATTERN("([^=]+)\\s*=([^\\r\\n]+)");

std::regex JSON_VALUE_PATTERN("(\"[^\"]+\"|\\S+)");

ChartSection *ParseSectionsFromChart(const char *contents, int *outSize)
{
    auto matches = FindAllMatches(contents, CHART_SECTION_PATTERN);

    *outSize = matches.size();

    auto sections =
        (ChartSection *)malloc(matches.size() * sizeof(ChartSection));

    for (auto i = 0; i < matches.size(); i += 1)
    {
        auto parts = FindMatchGroups(matches[i].c_str(), CHART_SECTION_PATTERN);

        if (parts.size() < 3)
        {
            continue;
        }

        sections[i].name = (char *)malloc(strlen(parts[1].c_str()) + 1);
        strcpy(sections[i].name, parts[1].c_str());

        auto lines =
            FindAllMatches(parts[2].c_str(), CHART_SECTION_LINE_PATTERN);

        sections[i].lines =
            (KeyValuePair *)malloc(lines.size() * sizeof(KeyValuePair));

        sections[i].lineCount = lines.size();

        for (auto j = 0; j < lines.size(); j += 1)
        {
            auto parts = Split(lines[j].c_str(), '=');

            auto key = Trim(parts[0].c_str());
            auto value = Trim(parts[1].c_str());

            sections[i].lines[j].key = (char *)malloc(strlen(key.c_str()) + 1);
            strcpy(sections[i].lines[j].key, key.c_str());

            auto values = FindAllMatches(value.c_str(), JSON_VALUE_PATTERN);

            for (auto k = 0; k < values.size(); k += 1)
            {
                auto valuePart =
                    std::regex_replace(values[k], std::regex("^\"|\"$"), "");

                sections[i].lines[j].values[k] =
                    (char *)malloc(strlen(valuePart.c_str()) + 1);
                strcpy(sections[i].lines[j].values[k], valuePart.c_str());
            }

            sections[i].lines[j].valueCount = values.size();
        }
    }

    return sections;
}
