#pragma once

#include <string>

namespace RhythmGameUtilities
{

typedef enum TypeCode
{

    /// BPM Marker
    BPM,

    /// Time Signature Marker
    TimeSignature,

    /// Note Marker
    Note,

    /// Event Marker
    Event

} TypeCodeType;

std::string ToString(TypeCode typeCode)
{
    switch (typeCode)
    {
    case BPM:
        return "B";
    case TimeSignature:
        return "TS";
    case Note:
        return "N";
    case Event:
        return "E";
    }
}

} // namespace RhythmGameUtilities
