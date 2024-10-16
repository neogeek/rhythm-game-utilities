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

std::string ToString(Difficulty difficulty)
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
        throw std::invalid_argument("Unknown Difficulty");
    }
}

} // namespace RhythmGameUtilities
