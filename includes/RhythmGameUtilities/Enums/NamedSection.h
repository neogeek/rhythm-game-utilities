#pragma once

#include <string>

namespace RhythmGameUtilities
{

enum NamedSection
{
    /// Song information
    Song,

    /// Track information used for syncing with music and notes like BPM
    SyncTrack,

    /// Track events
    Events
};

std::string ToString(NamedSection namedSection)
{
    switch (namedSection)
    {
    case Song:
        return "Song";
    case SyncTrack:
        return "SyncTrack";
    case Events:
        return "Events";
    }
}

} // namespace RhythmGameUtilities
