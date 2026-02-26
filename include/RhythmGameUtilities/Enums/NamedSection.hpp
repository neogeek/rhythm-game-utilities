// Rhythm Game Utilities -
// https://github.com/rhythm-game-utilities/rhythm-game-utilities
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

using NamedSection = enum : uint8_t {
    // Song information
    Song,

    // Track information used for syncing with music and notes like BPM
    SyncTrack,

    // Track events
    Events
};

inline auto ToString(NamedSection namedSection) -> std::string
{
    switch (namedSection)
    {
    case Song:
        return "Song";
    case SyncTrack:
        return "SyncTrack";
    case Events:
        return "Events";
    default:
        return "Unknown NamedSection";
    }
}

} // namespace RhythmGameUtilities
