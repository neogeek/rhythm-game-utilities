#pragma once

#include <string>

namespace TypeCode
{
typedef std::string Type;

/// <summary>
/// BPM Marker
/// </summary>
Type BPM = "B";

/// <summary>
/// Time Signature Marker
/// </summary>
Type TimeSignature = "TS";

/// <summary>
/// Note Marker
/// </summary>
Type Note = "N";

/// <summary>
/// Event Marker
/// </summary>
Type Event = "E";

} // namespace TypeCode
