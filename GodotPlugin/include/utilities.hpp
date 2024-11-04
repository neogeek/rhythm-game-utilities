#pragma once

#include <map>

#include <godot_cpp/variant/dictionary.hpp>

using namespace godot;

template <typename T1, typename T2>
std::map<T1, T2> convert_dictionary_to_map(Dictionary input)
{
    std::map<T1, T2> output;

    auto keys = input.keys();

    for (auto i = 0; i < keys.size(); i += 1)
    {
        auto key = keys[i];
        output[key] = input[key];
    }

    return output;
}
