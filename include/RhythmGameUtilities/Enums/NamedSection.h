#pragma once

#include <string>

namespace RhythmGameUtilities
{

typedef enum NamedSection
{
    /// Song information
    Song,

    /// Track information used for syncing with music and notes like BPM
    SyncTrack,

    /// Track events
    Events
} NamedSectionType;

inline std::string ToString(NamedSection namedSection)
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
