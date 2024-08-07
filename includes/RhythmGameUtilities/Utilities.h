#pragma once

#include <map>
#include <regex>
#include <string>
#include <vector>

#include "Structs/Note.h"

#ifdef _WIN32
#define PACKAGE_API __declspec(dllexport)
#else
#define PACKAGE_API
#endif

extern "C"
{
    PACKAGE_API float ConvertTickToPosition(float tick, int resolution);

    PACKAGE_API int ConvertSecondsToTicksInternal(float seconds, int resolution,
                                                  int *bpmChangesKeys,
                                                  int *bpmChangesValues,
                                                  int bpmChangesSize);

    PACKAGE_API bool IsOnTheBeat(float bpm, float currentTime);

    PACKAGE_API int RoundUpToTheNearestMultiplier(int value, int multiplier);

    PACKAGE_API float Lerp(float a, float b, float t);

    PACKAGE_API float InverseLerp(float a, float b, float v);
}

int ConvertSecondsToTicks(float seconds, int resolution,
                          std::map<int, int> bpmChanges);

std::string Trim(const char *contents);

std::vector<std::string> Split(const char *contents, const char delimiter);

std::vector<std::string> FindAllMatches(const char *contents,
                                        std::regex pattern);

std::vector<std::string> FindMatchGroups(const char *contents,
                                         std::regex pattern);
