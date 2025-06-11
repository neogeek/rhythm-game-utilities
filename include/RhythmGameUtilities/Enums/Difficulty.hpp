#pragma once

#include <string>

namespace RhythmGameUtilities
{

typedef enum Difficulty
{
    // Easy Difficulty
    Easy,

    // Medium Difficulty
    Medium,

    // Hard Difficulty
    Hard,

    // Expert Difficulty
    Expert
} DifficultyType;

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
