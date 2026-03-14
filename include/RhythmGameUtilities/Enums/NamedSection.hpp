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

enum class NamedSection : uint8_t
{
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
    case NamedSection::Song:
        return "Song";
    case NamedSection::SyncTrack:
        return "SyncTrack";
    case NamedSection::Events:
        return "Events";
    default:
        return "Unknown NamedSection";
    }
}

} // namespace RhythmGameUtilities
