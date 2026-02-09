#pragma once

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/variant/dictionary.hpp>

#include <RhythmGameUtilities/Enums/Difficulty.hpp>
#include <RhythmGameUtilities/Enums/NamedSection.hpp>

using namespace godot;

class Song : public Object
{
    GDCLASS(Song, Object)

  protected:
    static void _bind_methods();

  public:
    int resolution;
    Array tempo_changes;
    Array time_signature_changes;
    Array notes;
    Array beat_bars;

    void set_resolution(int value);
    auto get_resolution() -> int;

    void set_tempo_changes(Array value);
    auto get_tempo_changes() -> Array;

    void set_time_signature_changes(Array value);
    auto get_time_signature_changes() -> Array;

    void set_notes(Array value);
    auto get_notes() -> Array;

    void set_beat_bars(Array value);
    auto get_beat_bars() -> Array;

    void load_song_from_chart(const String &contents, const int &difficulty);

    void load_song_from_midi(const Variant &data);
};
