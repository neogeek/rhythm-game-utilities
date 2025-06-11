#pragma once

#include <cstdint>
#include <string>

namespace RhythmGameUtilities
{

using NamedSection = enum : uint8_t {
    /// Song information
    Song,

    /// Track information used for syncing with music and notes like BPM
    SyncTrack,

    /// Track events
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
