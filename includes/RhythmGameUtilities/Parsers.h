#pragma once

#include <vector>

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

typedef struct
{
    std::string name;
    std::vector<std::pair<std::string, std::vector<std::string>>> lines;
} ChartSection;

std::vector<ChartSection> ParseSectionsFromChart(const char *contents);

extern "C"
{
    PACKAGE_API ChartSectionInternal *
    ParseSectionsFromChartInternal(const char *contents, int *outSize);
}

} // namespace RhythmGameUtilities
