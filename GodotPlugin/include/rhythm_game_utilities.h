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

    static float inverse_lerp(float a, float b, float v);

    static float lerp(float a, float b, float t);

    // Parsers

    static Array parse_bpm_from_chart_section(Array section);

    static Dictionary parse_lyrics_from_chart_section(Array section);

    static Dictionary parse_meta_data_from_chart_section(Array section);

    static Array parse_notes_from_chart_section(Array section);

    static Dictionary parse_sections_from_chart(String contents);

    static Array parse_time_signatures_from_chart_section(Array section);

    // Utilities

    static float calculate_accuracy_ratio(int position, int current_position,
                                          int delta = 50);

    static Array calculate_beat_bars(Array bpm_changes, int resolution, int ts,
                                     bool include_half_notes);

    static int convert_seconds_to_ticks(float seconds, int resolution,
                                        Array bpm_changes,
                                        Array time_signature_changes);

    static float convert_tick_to_position(int tick, int resolution);

    static Dictionary find_position_near_given_tick(Array notes, int tick,
                                                    int delta = 50);

    static bool is_on_the_beat(int bpm, float current_time,
                               float delta = 0.05f);

    static int round_up_to_the_nearest_multiplier(int value, int multiplier);
};
