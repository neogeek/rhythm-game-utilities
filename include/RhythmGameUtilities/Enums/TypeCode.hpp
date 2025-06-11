#pragma once

#include <cstdint>
#include <string>

namespace RhythmGameUtilities
{

using TypeCode = enum : uint8_t {
    /// BPM Marker
    BPM_Marker,

    /// Time Signature Marker
    TimeSignatureMarker,

    /// Note Marker
    NoteMarker,

    /// Event Marker
    EventMarker
};

inline auto ToString(TypeCode typeCode) -> std::string
{
    switch (typeCode)
    {
    case BPM_Marker:
        return "B";
    case TimeSignatureMarker:
        return "TS";
    case NoteMarker:
        return "N";
    case EventMarker:
        return "E";
    default:
        return "Unknown TypeCode";
    }
}

} // namespace RhythmGameUtilities
