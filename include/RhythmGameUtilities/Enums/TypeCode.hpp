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

enum class TypeCode : uint8_t
{
    // BPM Marker
    BPM_Marker,

    // Time Signature Marker
    TimeSignatureMarker,

    // Note Marker
    NoteMarker,

    // Event Marker
    EventMarker
};

inline auto ToString(TypeCode typeCode) -> std::string
{
    switch (typeCode)
    {
    case TypeCode::BPM_Marker:
        return "B";
    case TypeCode::TimeSignatureMarker:
        return "TS";
    case TypeCode::NoteMarker:
        return "N";
    case TypeCode::EventMarker:
        return "E";
    default:
        return "Unknown TypeCode";
    }
}

} // namespace RhythmGameUtilities
