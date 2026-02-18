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
    // Enums

    enum Difficulty
    {
        Easy,
        Medium,
        Hard,
        Expert
    };

    // Common

    static auto inverse_lerp_unclamped(float a, float b, float v) -> float;

    static auto inverse_lerp(float a, float b, float v) -> float;

    static auto lerp(float a, float b, float t) -> float;

    // Parsers (Chart)

    static auto read_resolution_from_chart_data(const String &contents) -> int;

    static auto read_tempo_changes_from_chart_data(const String &contents)
        -> Array;

    static auto
    read_time_signature_changes_from_chart_data(const String &contents)
        -> Array;

    static auto read_notes_from_chart_data(const String &contents,
                                           int difficulty) -> Array;

    // Parsers (Midi)

    static auto read_resolution_from_midi_data(const Variant &data) -> int;

    static auto read_tempo_changes_from_midi_data(const Variant &data) -> Array;

    static auto read_time_signature_changes_from_midi_data(const Variant &data)
        -> Array;

    static auto read_notes_from_midi_data(const Variant &data) -> Array;

    // Utilities

    static auto calculate_accuracy_ratio(int position, int current_position,
                                         int delta = 50) -> float;

    static auto calculate_beat_bars(Array tempo_changes, int resolution, int ts,
                                    bool include_half_notes) -> Array;

    static auto convert_seconds_to_ticks(float seconds, int resolution,
                                         Array tempo_changes,
                                         Array time_signature_changes) -> int;

    static auto convert_tick_to_position(int tick, int resolution) -> float;

    static auto find_notes_near_given_tick(Array notes, int tick,
                                           int delta = 50) -> Array;

    static auto is_on_the_beat(int bpm, float current_time, float delta = 0.05F)
        -> bool;

    static auto round_up_to_the_nearest_multiplier(int value, int multiplier)
        -> int;
};

VARIANT_ENUM_CAST(rhythm_game_utilities::Difficulty);
