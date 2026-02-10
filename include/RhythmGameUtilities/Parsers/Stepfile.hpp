#pragma once

#include <iostream>
#include <regex>
#include <vector>

#include "../Common.hpp"

namespace RhythmGameUtilities
{

inline std::regex STEPFILE_SECTION_PATTERN(R"(#([a-z]+):([^;]*);)",
                                           std::regex_constants::icase);

inline auto ParseSectionsFromStepfile(const char *contents) -> void
{
    auto matches = FindAllMatches(contents, STEPFILE_SECTION_PATTERN);

    for (auto i = 0; i < matches.size(); i += 1)
    {
        auto parts =
            FindMatchGroups(matches[i].c_str(), STEPFILE_SECTION_PATTERN);

        if (parts.size() < 2)
        {
            continue;
        }

        std::cout << parts[1].c_str() << "\n";
    }

    std::cout << matches.size() << "\n";
}

} // namespace RhythmGameUtilities
