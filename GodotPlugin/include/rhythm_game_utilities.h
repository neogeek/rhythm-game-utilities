#pragma once

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/string.hpp>

using namespace godot;

class rhythm_game_utilities : public Object
{
    GDCLASS(rhythm_game_utilities, Object)

  protected:
    static void _bind_methods();

  public:
    static float lerp(float a, float b, float t);

    static float inverse_lerp(float a, float b, float v);
};
