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

using Accuracy = enum : uint8_t {
    // Invalid Accuracy
    Invalid,

    // Poor Accuracy
    Poor,

    // Fair Accuracy
    Fair,

    // Good Accuracy
    Good,

    // Great Accuracy
    Great,

    // Perfect Accuracy
    Perfect
};

inline auto ToString(Accuracy accuracy) -> std::string
{
    switch (accuracy)
    {
    case Invalid:
        return "Invalid";
    case Fair:
        return "Fair";
    case Poor:
        return "Poor";
    case Good:
        return "Good";
    case Great:
        return "Great";
    case Perfect:
        return "Perfect";
    default:
        return "Unknown Accuracy";
    }
}

} // namespace RhythmGameUtilities
