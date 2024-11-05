#pragma once

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/variant/dictionary.hpp>
#include <godot_cpp/variant/string.hpp>

using namespace godot;

class rhythm_game_utilities : public Object
{
    GDCLASS(rhythm_game_utilities, Object)

  protected:
    static void _bind_methods();

  public:
    // Common

    static float lerp(float a, float b, float t);

    static float inverse_lerp(float a, float b, float v);

    // Parsers

    static Dictionary parse_sections_from_chart(String contents);

    // Utilities

    static int convert_seconds_to_ticks(float seconds, int resolution,
                                        Dictionary bpmChanges);

    static float convert_tick_to_position(int tick, int resolution);

    static bool is_on_the_beat(int bpm, float currentTime, float delta = 0.05f);

    static int round_up_to_the_nearest_multiplier(int value, int multiplier);

    static float calculate_accuracy_ratio(int position, int currentPosition,
                                          int delta = 50);

    static Array calculate_beat_bars(Dictionary bpmChanges, int resolution,
                                     int ts, bool includeHalfNotes);
};
