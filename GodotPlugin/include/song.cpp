#include "song.h"

#include "rhythm_game_utilities.h"

#include <RhythmGameUtilities/Enums/Difficulty.h>

void song::_bind_methods()
{
    // sections

    ClassDB::bind_method(D_METHOD("set_sections", "sections"),
                         &song::set_sections);
    ClassDB::bind_method(D_METHOD("get_sections"), &song::get_sections);

    ADD_PROPERTY(PropertyInfo(Variant::DICTIONARY, "sections"), "set_sections",
                 "get_sections");

    // meta_data

    ClassDB::bind_method(D_METHOD("set_meta_data", "meta_data"),
                         &song::set_meta_data);
    ClassDB::bind_method(D_METHOD("get_meta_data"), &song::get_meta_data);

    ADD_PROPERTY(PropertyInfo(Variant::DICTIONARY, "meta_data"),
                 "set_meta_data", "get_meta_data");

    // resolution

    ClassDB::bind_method(D_METHOD("set_resolution", "resolution"),
                         &song::set_resolution);
    ClassDB::bind_method(D_METHOD("get_resolution"), &song::get_resolution);

    ADD_PROPERTY(PropertyInfo(Variant::INT, "resolution"), "set_resolution",
                 "get_resolution");

    // tempo_changes

    ClassDB::bind_method(D_METHOD("set_tempo_changes", "tempo_changes"),
                         &song::set_tempo_changes);
    ClassDB::bind_method(D_METHOD("get_tempo_changes"),
                         &song::get_tempo_changes);

    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "tempo_changes"),
                 "set_tempo_changes", "get_tempo_changes");

    // time_signature_changes

    ClassDB::bind_method(
        D_METHOD("set_time_signature_changes", "time_signature_changes"),
        &song::set_time_signature_changes);
    ClassDB::bind_method(D_METHOD("get_time_signature_changes"),
                         &song::get_time_signature_changes);

    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "time_signature_changes"),
                 "set_time_signature_changes", "get_time_signature_changes");

    // difficulties

    ClassDB::bind_method(D_METHOD("set_difficulties", "difficulties"),
                         &song::set_difficulties);
    ClassDB::bind_method(D_METHOD("get_difficulties"), &song::get_difficulties);

    ADD_PROPERTY(PropertyInfo(Variant::DICTIONARY, "difficulties"),
                 "set_difficulties", "get_difficulties");

    // beat_bars

    ClassDB::bind_method(D_METHOD("set_beat_bars", "beat_bars"),
                         &song::set_beat_bars);
    ClassDB::bind_method(D_METHOD("get_beat_bars"), &song::get_beat_bars);

    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "beat_bars"), "set_beat_bars",
                 "get_beat_bars");

    ClassDB::bind_method(D_METHOD("load_song", "contents"), &song::load_song);
}

// sections

void song::set_sections(Dictionary value) { sections = value; }

Dictionary song::get_sections() { return sections; }

// meta_data

void song::set_meta_data(Dictionary value) { meta_data = value; }

Dictionary song::get_meta_data() { return meta_data; }

// resolution

void song::set_resolution(int value) { resolution = value; }

int song::get_resolution() { return resolution; }

// tempo_changes

void song::set_tempo_changes(Array value) { tempo_changes = value; }

Array song::get_tempo_changes() { return tempo_changes; }

// time_signature_changes

void song::set_time_signature_changes(Array value)
{
    time_signature_changes = value;
}

Array song::get_time_signature_changes() { return time_signature_changes; }

// difficulties

void song::set_difficulties(Dictionary value) { difficulties = value; }

Dictionary song::get_difficulties() { return difficulties; }

// beat_bars

void song::set_beat_bars(Array value) { beat_bars = value; }

Array song::get_beat_bars() { return beat_bars; }

void song::load_song(const String contents)
{
    sections = rhythm_game_utilities::parse_sections_from_chart(contents);

    meta_data = rhythm_game_utilities::parse_meta_data_from_chart_section(
        sections["Song"]);

    resolution = int(meta_data["Resolution"]);

    tempo_changes =
        rhythm_game_utilities::parse_tempo_changes_from_chart_section(
            sections["SyncTrack"]);

    time_signature_changes =
        rhythm_game_utilities::parse_time_signature_changes_from_chart_section(
            sections["SyncTrack"]);

    for (int difficultyInt = RhythmGameUtilities::Difficulty::Easy;
         difficultyInt <= RhythmGameUtilities::Difficulty::Expert;
         difficultyInt += 1)
    {
        auto difficulty =
            static_cast<RhythmGameUtilities::Difficulty>(difficultyInt);

        auto key = godot::String(
            RhythmGameUtilities::ToString(difficulty).append("Single").c_str());

        if (sections.has(key))
        {
            difficulties[difficulty] =
                rhythm_game_utilities::parse_notes_from_chart_section(
                    sections[key]);
        }
    }

    beat_bars = rhythm_game_utilities::calculate_beat_bars(tempo_changes,
                                                           resolution, 4, true);
}
