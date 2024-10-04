#pragma once

#include "Parsers.hpp"
#include "Utilities.hpp"

#ifdef _WIN32
#define PACKAGE_API __declspec(dllexport)
#else
#define PACKAGE_API
#endif

namespace RhythmGameUtilities
{

extern "C"
{
    PACKAGE_API
    ChartSectionInternal *ParseSectionsFromChartInternal(const char *contents,
                                                         int *outSize)
    {
        auto internalSections = ParseSectionsFromChart(contents);

        *outSize = internalSections.size();

        auto sections = (ChartSectionInternal *)malloc(
            internalSections.size() * sizeof(ChartSectionInternal));

        int i = 0;

        for (auto section = internalSections.begin();
             section != internalSections.end(); section++)
        {
            auto nameLength = section->first.size() + 1;
            sections[i].name = (char *)malloc(nameLength);
            strncpy(sections[i].name, section->first.c_str(), nameLength - 1);
            sections[i].name[nameLength - 1] = '\0';

            sections[i].lines = (KeyValuePairInternal *)malloc(
                section->second.size() * sizeof(KeyValuePairInternal));

            sections[i].lineCount = section->second.size();

            for (auto j = 0; j < section->second.size(); j += 1)
            {
                auto keyLength = section->second[j].first.size() + 1;
                sections[i].lines[j].key = (char *)malloc(keyLength);
                strncpy(sections[i].lines[j].key,
                        section->second[j].first.c_str(), keyLength - 1);
                sections[i].lines[j].key[keyLength - 1] = '\0';

                auto values = section->second[j].second;

                for (auto k = 0; k < values.size(); k += 1)
                {
                    auto valueLength = values[k].size() + 1;
                    sections[i].lines[j].values[k] =
                        (char *)malloc(valueLength);
                    strncpy(sections[i].lines[j].values[k], values[k].c_str(),
                            values[k].size());
                    sections[i].lines[j].values[k][valueLength - 1] = '\0';
                }

                sections[i].lines[j].valueCount = values.size();
            }

            i += 1;
        }

        return sections;
    }
}

} // namespace RhythmGameUtilities
