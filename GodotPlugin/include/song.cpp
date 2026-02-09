#include "song.hpp"

#include "rhythm_game_utilities.hpp"

void Song::_bind_methods()
{
    // resolution

    ClassDB::bind_method(D_METHOD("set_resolution", "resolution"),
                         &Song::set_resolution);
    ClassDB::bind_method(D_METHOD("get_resolution"), &Song::get_resolution);

    ADD_PROPERTY(PropertyInfo(Variant::INT, "resolution"), "set_resolution",
                 "get_resolution");

    // tempo_changes

    ClassDB::bind_method(D_METHOD("set_tempo_changes", "tempo_changes"),
                         &Song::set_tempo_changes);
    ClassDB::bind_method(D_METHOD("get_tempo_changes"),
                         &Song::get_tempo_changes);

    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "tempo_changes"),
                 "set_tempo_changes", "get_tempo_changes");

    // time_signature_changes

    ClassDB::bind_method(
        D_METHOD("set_time_signature_changes", "time_signature_changes"),
        &Song::set_time_signature_changes);
    ClassDB::bind_method(D_METHOD("get_time_signature_changes"),
                         &Song::get_time_signature_changes);

    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "time_signature_changes"),
                 "set_time_signature_changes", "get_time_signature_changes");

    // notes

    ClassDB::bind_method(D_METHOD("set_notes", "notes"), &Song::set_notes);
    ClassDB::bind_method(D_METHOD("get_notes"), &Song::get_notes);

    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "notes"), "set_notes",
                 "get_notes");

    // beat_bars

    ClassDB::bind_method(D_METHOD("set_beat_bars", "beat_bars"),
                         &Song::set_beat_bars);
    ClassDB::bind_method(D_METHOD("get_beat_bars"), &Song::get_beat_bars);

    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "beat_bars"), "set_beat_bars",
                 "get_beat_bars");

    ClassDB::bind_method(
        D_METHOD("load_song_from_chart", "contents", "difficulty"),
        &Song::load_song_from_chart);

    ClassDB::bind_method(D_METHOD("load_song_from_midi", "data"),
                         &Song::load_song_from_midi);
}

// resolution

void Song::set_resolution(int value) { resolution = value; }

auto Song::get_resolution() -> int { return resolution; }

// tempo_changes

void Song::set_tempo_changes(Array value) { tempo_changes = value; }

auto Song::get_tempo_changes() -> Array { return tempo_changes; }

// time_signature_changes

void Song::set_time_signature_changes(Array value)
{
    time_signature_changes = value;
}

auto Song::get_time_signature_changes() -> Array
{
    return time_signature_changes;
}

// notes

void Song::set_notes(Array value) { notes = value; }

auto Song::get_notes() -> Array { return notes; }

// beat_bars

void Song::set_beat_bars(Array value) { beat_bars = value; }

auto Song::get_beat_bars() -> Array { return beat_bars; }

// load_song_from_chart

void Song::load_song_from_chart(const String &contents, const int &difficulty)
{
    resolution =
        rhythm_game_utilities::read_resolution_from_chart_data(contents);

    tempo_changes =
        rhythm_game_utilities::read_tempo_changes_from_chart_data(contents);

    time_signature_changes =
        rhythm_game_utilities::read_time_signature_changes_from_chart_data(
            contents);

    notes =
        rhythm_game_utilities::read_notes_from_chart_data(contents, difficulty);

    beat_bars = rhythm_game_utilities::calculate_beat_bars(tempo_changes,
                                                           resolution, 4, true);
}

// load_song_from_midi

void Song::load_song_from_midi(const Variant &data)
{
    resolution = rhythm_game_utilities::read_resolution_from_midi_data(data);

    tempo_changes =
        rhythm_game_utilities::read_tempo_changes_from_midi_data(data);

    time_signature_changes =
        rhythm_game_utilities::read_time_signature_changes_from_midi_data(data);

    notes = rhythm_game_utilities::read_notes_from_midi_data(data);

    beat_bars = rhythm_game_utilities::calculate_beat_bars(tempo_changes,
                                                           resolution, 4, true);
}
