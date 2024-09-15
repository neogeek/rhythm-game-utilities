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

        for (auto i = 0; i < internalSections.size(); i += 1)
        {
            auto nameLength = internalSections[i].name.size() + 1;
            sections[i].name = (char *)malloc(nameLength);
            strncpy(sections[i].name, internalSections[i].name.c_str(),
                    nameLength - 1);
            sections[i].name[nameLength - 1] = '\0';

            sections[i].lines = (KeyValuePairInternal *)malloc(
                internalSections[i].lines.size() *
                sizeof(KeyValuePairInternal));

            sections[i].lineCount = internalSections[i].lines.size();

            for (auto j = 0; j < internalSections[i].lines.size(); j += 1)
            {
                auto keyLength = internalSections[i].lines[j].first.size() + 1;
                sections[i].lines[j].key = (char *)malloc(keyLength);
                strncpy(sections[i].lines[j].key,
                        internalSections[i].lines[j].first.c_str(),
                        keyLength - 1);
                sections[i].lines[j].key[keyLength - 1] = '\0';

                auto values = internalSections[i].lines[j].second;

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
        }

        return sections;
    }
}

} // namespace RhythmGameUtilities
