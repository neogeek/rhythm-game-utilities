#pragma once

#include <string>
#include <vector>

namespace RhythmGameUtilities
{

struct TrackEvent
{
    int Position;

    std::string TypeCode;

    std::vector<std::string> *Values;
};

} // namespace RhythmGameUtilities
