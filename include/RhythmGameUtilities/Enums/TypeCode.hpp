#pragma once

#include <string>

namespace RhythmGameUtilities
{

typedef enum TypeCode
{
    /// BPM Marker
    BPM_Marker,

    /// Time Signature Marker
    TimeSignatureMarker,

    /// Note Marker
    NoteMarker,

    /// Event Marker
    EventMarker
} TypeCodeType;

inline std::string ToString(TypeCode typeCode)
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
