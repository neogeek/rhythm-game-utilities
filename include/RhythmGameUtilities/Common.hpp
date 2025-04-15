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

    PACKAGE_API float Lerp(float a, float b, float t)
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

    PACKAGE_API float InverseLerp(float a, float b, float v)
    {
        return std::clamp(((v - a) / (b - a)), 0.0F, 1.0F);
    }
}

/**
 * Trims a string value.
 *
 * @param contents The string to trim.
 * @private
 */

inline std::string Trim(const char *contents)
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

inline std::vector<std::string> Split(const char *contents,
                                      const char delimiter)
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

inline std::vector<std::string> FindAllMatches(const char *contents,
                                               const std::regex &pattern)
{
    auto currentMatch =
        std::cregex_iterator(contents, contents + strlen(contents), pattern);
    auto lastMatch = std::cregex_iterator();

    auto matches = std::vector<std::string>();

    while (currentMatch != lastMatch)
    {
        auto match = *currentMatch;

        matches.push_back(match.str(0));

        currentMatch++;
    }

    return matches;
}

inline std::vector<std::string> FindMatchGroups(const char *contents,
                                                const std::regex &pattern)
{
    auto currentMatch =
        std::cregex_iterator(contents, contents + strlen(contents), pattern);

    auto matches = std::vector<std::string>();

    const auto &match = *currentMatch;

    for (auto i = 0; i < match.size(); i += 1)
    {
        matches.push_back(match.str(i));
    }

    return matches;
}

} // namespace RhythmGameUtilities
