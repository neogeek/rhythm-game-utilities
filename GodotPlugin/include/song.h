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
    Dictionary get_sections();

    void set_meta_data(Dictionary value);
    Dictionary get_meta_data();

    void set_resolution(int value);
    int get_resolution();

    void set_tempo_changes(Array value);
    Array get_tempo_changes();

    void set_time_signature_changes(Array value);
    Array get_time_signature_changes();

    void set_difficulties(Dictionary value);
    Dictionary get_difficulties();

    void set_beat_bars(Array value);
    Array get_beat_bars();

    void load_song(const String contents);
};
