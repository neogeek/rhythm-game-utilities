#pragma once

#include <cstdint>
#include <string>

namespace RhythmGameUtilities
{

using Difficulty = enum : uint8_t {
    // Easy Difficulty
    Easy,

    // Medium Difficulty
    Medium,

    // Hard Difficulty
    Hard,

    // Expert Difficulty
    Expert
};

inline auto ToString(Difficulty difficulty) -> std::string
{
    switch (difficulty)
    {
    case Easy:
        return "Easy";
    case Medium:
        return "Medium";
    case Hard:
        return "Hard";
    case Expert:
        return "Expert";
    default:
        return "Unknown Difficulty";
    }
}

} // namespace RhythmGameUtilities
