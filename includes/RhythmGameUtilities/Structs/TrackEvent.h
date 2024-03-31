#pragma once

#include <string>

struct TrackEvent
{

    int Position;

    std::string TypeCode;

    std::vector<std::string> *Values;
};
