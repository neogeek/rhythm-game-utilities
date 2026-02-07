#pragma once

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/variant/dictionary.hpp>

using namespace godot;

class Song : public Object
{
    GDCLASS(Song, Object)

  protected:
    static void _bind_methods();

  public:
    Dictionary sections;
    Dictionary meta_data;
    int resolution;
    Array tempo_changes;
    Array time_signature_changes;
    Dictionary difficulties;
    Array beat_bars;

    void set_sections(Dictionary value);
    auto get_sections() -> Dictionary;

    void set_meta_data(Dictionary value);
    auto get_meta_data() -> Dictionary;

    void set_resolution(int value);
    auto get_resolution() -> int;

    void set_tempo_changes(Array value);
    auto get_tempo_changes() -> Array;

    void set_time_signature_changes(Array value);
    auto get_time_signature_changes() -> Array;

    void set_difficulties(Dictionary value);
    auto get_difficulties() -> Dictionary;

    void set_beat_bars(Array value);
    auto get_beat_bars() -> Array;

    void load_song(String contents);
};
