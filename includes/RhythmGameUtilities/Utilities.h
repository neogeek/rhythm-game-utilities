#pragma once

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

    PACKAGE_API bool IsOnTheBeat(float bpm, float currentTime);

    PACKAGE_API int RoundUpToTheNearestMultiplier(int value, int multiplier);

    PACKAGE_API float Lerp(float a, float b, float t);

    PACKAGE_API float InverseLerp(float a, float b, float v);
}

std::string Trim(const char *contents);

std::vector<std::string> Split(const char *contents, const char delimiter);

std::vector<std::string> FindAllMatches(const char *contents,
                                        std::regex pattern);

std::vector<std::string> FindMatchGroups(const char *contents,
                                         std::regex pattern);
