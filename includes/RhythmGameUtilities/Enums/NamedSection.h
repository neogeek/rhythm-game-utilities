#pragma once

#include <string>

namespace RhythmGameUtilities
{

namespace NamedSection
{
typedef std::string Type;

/// <summary>
/// Song information
/// </summary>
Type Song = "Song";

/// <summary>
/// Track information used for syncing with music and notes like BPM
/// </summary>
Type SyncTrack = "SyncTrack";

/// <summary>
/// Track events
/// </summary>
Type Events = "Events";

}; // namespace NamedSection

} // namespace RhythmGameUtilities
