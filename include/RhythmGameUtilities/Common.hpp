// Rhythm Game Utilities - https://github.com/neogeek/rhythm-game-utilities
//
// ░█▀▄░█░█░█░█░▀█▀░█░█░█▄█░░░█▀▀░█▀█░█▄█░█▀▀░░░█░█░▀█▀░▀█▀░█░░░▀█▀░▀█▀░▀█▀░█▀▀░█▀▀
// ░█▀▄░█▀█░░█░░░█░░█▀█░█░█░░░█░█░█▀█░█░█░█▀▀░░░█░█░░█░░░█░░█░░░░█░░░█░░░█░░█▀▀░▀▀█
// ░▀░▀░▀░▀░░▀░░░▀░░▀░▀░▀░▀░░░▀▀▀░▀░▀░▀░▀░▀▀▀░░░▀▀▀░░▀░░▀▀▀░▀▀▀░▀▀▀░░▀░░▀▀▀░▀▀▀░▀▀▀
//
// Copyright (c) Scott Doxey. All Rights Reserved. Licensed under the MIT
// License. See LICENSE in the project root for license information.

#pragma once

#include <cstring>
#include <regex>
#include <sstream>

#ifdef _WIN32
#define PACKAGE_API __declspec(dllexport)
#else
#define PACKAGE_API
#endif

namespace RhythmGameUtilities
{

extern "C"
{
    /**
     * Calculates the linear interpolation between two values.
     *
     * @param a The start value.
     * @param b The end value.
     * @param t The value used for interpolation.
     * @public
     */

    PACKAGE_API auto Lerp(float a, float b, float t) -> float
    {
        return ((1 - t) * a) + (b * t);
    }

    /**
     * Calculates the fraction, based on a value between two values.
     *
     * @param a The start value.
     * @param b The end value.
     * @param v The value in the middle.
     * @public
     */

    PACKAGE_API auto InverseLerp(float a, float b, float v) -> float
    {
        return std::clamp((v - a) / (b - a), 0.0F, 1.0F);
    }
}

/**
 * Trims a string value.
 *
 * @param contents The string to trim.
 * @private
 */

inline auto Trim(const char *contents) -> std::string
{
    return std::regex_replace(contents, std::regex("^\\s+|\\s+$"), "");
}

/**
 * Splits a string into an array based on a delimiter.
 *
 * @param contents The string to split.
 * @param delimiter The delimiter to split on.
 * @private
 */

inline auto Split(const char *contents, const char delimiter)
    -> std::vector<std::string>
{
    auto parts = std::vector<std::string>();

    std::stringstream input(contents);

    std::string str;

    while (std::getline(input, str, delimiter))
    {
        parts.push_back(str);
    }

    return parts;
}

inline auto FindAllMatches(const char *contents, const std::regex &pattern)
    -> std::vector<std::string>
{
    auto matches = std::vector<std::string>();

    auto begin =
        std::cregex_iterator(contents, contents + strlen(contents), pattern);

    auto end = std::cregex_iterator();

    for (auto iterator = begin; iterator != end; iterator++)
    {
        matches.push_back(iterator->str(0));
    }

    return matches;
}

inline auto FindMatchGroups(const char *contents, const std::regex &pattern)
    -> std::vector<std::string>
{
    auto matches = std::vector<std::string>();

    auto iterator =
        std::cregex_iterator(contents, contents + strlen(contents), pattern);

    if (iterator == std::cregex_iterator())
    {
        return matches;
    }

    const auto &match = *iterator;

    for (auto i = 0; i < match.size(); i += 1)
    {
        matches.push_back(match.str(i));
    }

    return matches;
}

} // namespace RhythmGameUtilities
