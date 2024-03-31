#pragma once

#include <vector>

#ifdef _WIN32
#define PACKAGE_API __declspec(dllexport)
#else
#define PACKAGE_API
#endif

typedef struct
{
    char *key;
    char *value;
} KeyValuePair;

typedef struct
{
    char *name;
    KeyValuePair *lines;
    int lineCount;
} ChartSection;

extern "C"
{
    PACKAGE_API ChartSection *ParseSectionsFromChart(const char *contents,
                                                     int *outSize);
}
