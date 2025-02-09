#pragma once

#include <map>

#include <godot_cpp/variant/dictionary.hpp>

using namespace godot;

std::vector<std::pair<std::string, std::vector<std::string>>>
convert_section_to_section_internal(Array section)
{
    std::vector<std::pair<std::string, std::vector<std::string>>>
        section_internal;

    for (auto i = 0; i < section.size(); i += 1)
    {
        if (section[i].get_type() == Variant::DICTIONARY)
        {
            Dictionary variant = section[i];

            Array keys = variant.keys();

            for (auto j = 0; j < keys.size(); j += 1)
            {
                String key = keys[j];
                Array values = variant[key];

                std::vector<std::string> values_internal;

                for (auto k = 0; k < values.size(); k += 1)
                {
                    if (values[k].get_type() == Variant::Type::STRING)
                    {
                        String value = values[k];

                        values_internal.push_back(value.utf8().get_data());
                    }
                }

                section_internal.push_back(
                    std::make_pair(key.utf8().get_data(), values_internal));
            }
        }
    }

    return section_internal;
}
