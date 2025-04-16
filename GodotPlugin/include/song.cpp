#include "song.hpp"

#include "rhythm_game_utilities.hpp"

#include <RhythmGameUtilities/Enums/Difficulty.hpp>
#include <RhythmGameUtilities/Enums/NamedSection.hpp>

void Song::_bind_methods()
{
    // sections

    ClassDB::bind_method(D_METHOD("set_sections", "sections"),
                         &Song::set_sections);
    ClassDB::bind_method(D_METHOD("get_sections"), &Song::get_sections);

    ADD_PROPERTY(PropertyInfo(Variant::DICTIONARY, "sections"), "set_sections",
                 "get_sections");

    // meta_data

    ClassDB::bind_method(D_METHOD("set_meta_data", "meta_data"),
                         &Song::set_meta_data);
    ClassDB::bind_method(D_METHOD("get_meta_data"), &Song::get_meta_data);

    ADD_PROPERTY(PropertyInfo(Variant::DICTIONARY, "meta_data"),
                 "set_meta_data", "get_meta_data");

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

    // difficulties

    ClassDB::bind_method(D_METHOD("set_difficulties", "difficulties"),
                         &Song::set_difficulties);
    ClassDB::bind_method(D_METHOD("get_difficulties"), &Song::get_difficulties);

    ADD_PROPERTY(PropertyInfo(Variant::DICTIONARY, "difficulties"),
                 "set_difficulties", "get_difficulties");

    // beat_bars

    ClassDB::bind_method(D_METHOD("set_beat_bars", "beat_bars"),
                         &Song::set_beat_bars);
    ClassDB::bind_method(D_METHOD("get_beat_bars"), &Song::get_beat_bars);

    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "beat_bars"), "set_beat_bars",
                 "get_beat_bars");

    ClassDB::bind_method(D_METHOD("load_song", "contents"), &Song::load_song);
}

// sections

void Song::set_sections(Dictionary value) { sections = value; }

Dictionary Song::get_sections() { return sections; }

// meta_data

void Song::set_meta_data(Dictionary value) { meta_data = value; }

Dictionary Song::get_meta_data() { return meta_data; }

// resolution

void Song::set_resolution(int value) { resolution = value; }

int Song::get_resolution() { return resolution; }

// tempo_changes

void Song::set_tempo_changes(Array value) { tempo_changes = value; }

Array Song::get_tempo_changes() { return tempo_changes; }

// time_signature_changes

void Song::set_time_signature_changes(Array value)
{
    time_signature_changes = value;
}

Array Song::get_time_signature_changes() { return time_signature_changes; }

// difficulties

void Song::set_difficulties(Dictionary value) { difficulties = value; }

Dictionary Song::get_difficulties() { return difficulties; }

// beat_bars

void Song::set_beat_bars(Array value) { beat_bars = value; }

Array Song::get_beat_bars() { return beat_bars; }

void Song::load_song(const String contents)
{
    sections = rhythm_game_utilities::parse_sections_from_chart(contents);

    meta_data = rhythm_game_utilities::parse_meta_data_from_chart_section(
        sections[godot::String(RhythmGameUtilities::ToString(
                                   RhythmGameUtilities::NamedSection::Song)
                                   .c_str())]);

    resolution = int(meta_data["Resolution"]);

    tempo_changes =
        rhythm_game_utilities::parse_tempo_changes_from_chart_section(
            sections[godot::String(
                RhythmGameUtilities::ToString(
                    RhythmGameUtilities::NamedSection::SyncTrack)
                    .c_str())]);

    time_signature_changes =
        rhythm_game_utilities::parse_time_signature_changes_from_chart_section(
            sections[godot::String(
                RhythmGameUtilities::ToString(
                    RhythmGameUtilities::NamedSection::SyncTrack)
                    .c_str())]);

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
            difficulties[godot::String(
                RhythmGameUtilities::ToString(difficulty).c_str())] =
                rhythm_game_utilities::parse_notes_from_chart_section(
                    sections[key]);
        }
    }

    beat_bars = rhythm_game_utilities::calculate_beat_bars(tempo_changes,
                                                           resolution, 4, true);
}
