// Rhythm Game Utilities - https://github.com/neogeek/rhythm-game-utilities
//
// ░█▀▄░█░█░█░█░▀█▀░█░█░█▄█░░░█▀▀░█▀█░█▄█░█▀▀░░░█░█░▀█▀░▀█▀░█░░░▀█▀░▀█▀░▀█▀░█▀▀░█▀▀
// ░█▀▄░█▀█░░█░░░█░░█▀█░█░█░░░█░█░█▀█░█░█░█▀▀░░░█░█░░█░░░█░░█░░░░█░░░█░░░█░░█▀▀░▀▀█
// ░▀░▀░▀░▀░░▀░░░▀░░▀░▀░▀░▀░░░▀▀▀░▀░▀░▀░▀░▀▀▀░░░▀▀▀░░▀░░▀▀▀░▀▀▀░▀▀▀░░▀░░▀▀▀░▀▀▀░▀▀▀
//
// Copyright (c) Scott Doxey. All Rights Reserved. Licensed under the MIT
// License. See LICENSE in the project root for license information.

#pragma once

#include <cstdint>
#include <string>

namespace RhythmGameUtilities
{

using Timing = enum : uint8_t {
    // Miss Timing
    Miss,

    // Hit Timing
    Hit,

    // Early Timing
    Early,

    // Late Timing
    Late
};

inline auto ToString(Timing timing) -> std::string
{
    switch (timing)
    {
    case Miss:
        return "Miss";
    case Hit:
        return "Hit";
    case Early:
        return "Early";
    case Late:
        return "Late";
    default:
        return "Unknown Timing";
    }
}

} // namespace RhythmGameUtilities
