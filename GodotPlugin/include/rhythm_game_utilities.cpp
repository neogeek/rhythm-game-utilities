#include "rhythm_game_utilities.h"

#include "utilities.hpp"

#include <RhythmGameUtilities/Common.hpp>
#include <RhythmGameUtilities/Parsers.hpp>
#include <RhythmGameUtilities/Utilities.hpp>

void rhythm_game_utilities::_bind_methods()
{
    // Common

    ClassDB::bind_static_method("rhythm_game_utilities",
                                D_METHOD("inverse_lerp", "a", "b", "v"),
                                &rhythm_game_utilities::inverse_lerp);

    ClassDB::bind_static_method("rhythm_game_utilities",
                                D_METHOD("lerp", "a", "b", "t"),
                                &rhythm_game_utilities::lerp);

    // Parsers

    ClassDB::bind_static_method(
        "rhythm_game_utilities",
        D_METHOD("parse_tempo_changes_from_chart_section", "section"),
        &rhythm_game_utilities::parse_tempo_changes_from_chart_section);

    ClassDB::bind_static_method(
        "rhythm_game_utilities",
        D_METHOD("parse_lyrics_from_chart_section", "section"),
        &rhythm_game_utilities::parse_lyrics_from_chart_section);

    ClassDB::bind_static_method(
        "rhythm_game_utilities",
        D_METHOD("parse_meta_data_from_chart_section", "section"),
        &rhythm_game_utilities::parse_meta_data_from_chart_section);

    ClassDB::bind_static_method(
        "rhythm_game_utilities",
        D_METHOD("parse_notes_from_chart_section", "section"),
        &rhythm_game_utilities::parse_notes_from_chart_section);

    ClassDB::bind_static_method(
        "rhythm_game_utilities",
        D_METHOD("parse_sections_from_chart", "contents"),
        &rhythm_game_utilities::parse_sections_from_chart);

    ClassDB::bind_static_method(
        "rhythm_game_utilities",
        D_METHOD("parse_time_signature_changes_from_chart_section", "section"),
        &rhythm_game_utilities::
            parse_time_signature_changes_from_chart_section);

    // Utilities

    ClassDB::bind_static_method(
        "rhythm_game_utilities",
        D_METHOD("calculate_accuracy_ratio", "position", "current_position",
                 "delta"),
        &rhythm_game_utilities::calculate_accuracy_ratio);

    ClassDB::bind_static_method("rhythm_game_utilities",
                                D_METHOD("calculate_beat_bars", "tempo_changes",
                                         "resolution", "ts",
                                         "include_half_notes"),
                                &rhythm_game_utilities::calculate_beat_bars);

    ClassDB::bind_static_method(
        "rhythm_game_utilities",
        D_METHOD("convert_seconds_to_ticks", "seconds", "resolution",
                 "tempo_changes", "time_signature_changes"),
        &rhythm_game_utilities::convert_seconds_to_ticks);

    ClassDB::bind_static_method(
        "rhythm_game_utilities",
        D_METHOD("convert_tick_to_position", "tick", "resolution"),
        &rhythm_game_utilities::convert_tick_to_position);

    ClassDB::bind_static_method(
        "rhythm_game_utilities",
        D_METHOD("find_position_near_given_tick", "notes", "tick", "delta"),
        &rhythm_game_utilities::find_position_near_given_tick);

    ClassDB::bind_static_method(
        "rhythm_game_utilities",
        D_METHOD("is_on_the_beat", "bpm", "current_time", "delta"),
        &rhythm_game_utilities::is_on_the_beat);

    ClassDB::bind_static_method(
        "rhythm_game_utilities",
        D_METHOD("round_up_to_the_nearest_multiplier", "value", "multiplier"),
        &rhythm_game_utilities::round_up_to_the_nearest_multiplier);
}

// Common

float rhythm_game_utilities::inverse_lerp(float a, float b, float v)
{
    return RhythmGameUtilities::InverseLerp(a, b, v);
}

float rhythm_game_utilities::lerp(float a, float b, float t)
{
    return RhythmGameUtilities::Lerp(a, b, t);
}

// Parsers

Array rhythm_game_utilities::parse_tempo_changes_from_chart_section(
    Array section)
{
    auto tempo_changes_internal =
        RhythmGameUtilities::ParseTempoChangesFromChartSection(
            convert_section_to_section_internal(section));

    Array tempo_changes;

    for (auto &tempo_change_internal : tempo_changes_internal)
    {
        Dictionary tempo_change;

        tempo_change["position"] = tempo_change_internal.Position;
        tempo_change["bpm"] = tempo_change_internal.BPM;

        tempo_changes.append(tempo_change);
    }

    return tempo_changes;
}

Dictionary rhythm_game_utilities::parse_lyrics_from_chart_section(Array section)
{
    auto lyrics_internal = RhythmGameUtilities::ParseLyricsFromChartSection(
        convert_section_to_section_internal(section));

    Dictionary lyrics;

    for (auto const &[key, val] : lyrics_internal)
    {
        lyrics[key] = godot::String(lyrics_internal[key].c_str());
    }

    return lyrics;
}

Dictionary
rhythm_game_utilities::parse_meta_data_from_chart_section(Array section)
{
    auto meta_data_internal =
        RhythmGameUtilities::ParseMetaDataFromChartSection(
            convert_section_to_section_internal(section));

    Dictionary meta_data;

    for (auto const &[key, val] : meta_data_internal)
    {
        meta_data[godot::String(key.c_str())] =
            godot::String(meta_data_internal[key].c_str());
    }

    return meta_data;
}

Array rhythm_game_utilities::parse_notes_from_chart_section(Array section)
{
    auto notes_internal = RhythmGameUtilities::ParseNotesFromChartSection(
        convert_section_to_section_internal(section));

    Array notes;

    for (auto &note_internal : notes_internal)
    {
        Dictionary note;

        note["position"] = note_internal.Position;
        note["hand_position"] = note_internal.HandPosition;
        note["length"] = note_internal.Length;

        notes.append(note);
    }

    return notes;
}

Dictionary rhythm_game_utilities::parse_sections_from_chart(String contents)
{
    Dictionary sections;

    auto sections_internal =
        RhythmGameUtilities::ParseSectionsFromChart(contents.utf8().get_data());

    for (auto section_internal = sections_internal.begin();
         section_internal != sections_internal.end(); section_internal++)
    {
        auto section_key = godot::String(section_internal->first.c_str());

        Array section_items;

        for (auto i = 0; i < section_internal->second.size(); i += 1)
        {
            Dictionary section_item;

            auto temp = section_internal->second[i];

            auto key = godot::Variant(temp.first.c_str());

            Array values;

            for (auto j = 0; j < temp.second.size(); j += 1)
            {
                values.append(godot::Variant(temp.second[j].c_str()));
            }

            section_item[key] = values;

            section_items.append(section_item);
        }

        sections[section_key] = section_items;
    }

    return sections;
}

Array rhythm_game_utilities::parse_time_signature_changes_from_chart_section(
    Array section)
{
    auto time_signature_changes_internal =
        RhythmGameUtilities::ParseTimeSignatureChangesFromChartSection(
            convert_section_to_section_internal(section));

    Array time_signature_changes;

    for (auto &time_signature_change_internal : time_signature_changes_internal)
    {
        Dictionary time_signature_change;

        time_signature_change["position"] =
            time_signature_change_internal.Position;
        time_signature_change["numerator"] =
            time_signature_change_internal.Numerator;
        time_signature_change["denominator"] =
            time_signature_change_internal.Denominator;

        time_signature_changes.append(time_signature_change);
    }

    return time_signature_changes;
}

// Utilities

float rhythm_game_utilities::calculate_accuracy_ratio(int position,
                                                      int current_position,
                                                      int delta)
{
    return RhythmGameUtilities::CalculateAccuracyRatio(position,
                                                       current_position, delta);
}

Array rhythm_game_utilities::calculate_beat_bars(Array tempo_changes,
                                                 int resolution, int ts,
                                                 bool include_half_notes)
{
    std::vector<RhythmGameUtilities::Tempo> tempo_changes_internal;
    tempo_changes_internal.reserve(tempo_changes.size());

    for (auto i = 0; i < tempo_changes.size(); i += 1)
    {
        RhythmGameUtilities::Tempo tempo_change_internal;

        if (tempo_changes[i].get_type() == Variant::DICTIONARY)
        {
            Dictionary variant = tempo_changes[i];

            tempo_change_internal.Position = variant["position"];
            tempo_change_internal.BPM = variant["bpm"];
        }

        tempo_changes_internal.push_back(tempo_change_internal);
    }

    auto beat_bars_internal = RhythmGameUtilities::CalculateBeatBars(
        tempo_changes_internal, resolution, ts, include_half_notes);

    Array beat_bars_dictionary_array;

    for (auto &beat_bar_internal : beat_bars_internal)
    {
        Dictionary beat_bar_dictionary;

        beat_bar_dictionary["position"] = beat_bar_internal.Position;
        beat_bar_dictionary["bpm"] = beat_bar_internal.BPM;

        beat_bars_dictionary_array.append(beat_bar_dictionary);
    }

    return beat_bars_dictionary_array;
}

int rhythm_game_utilities::convert_seconds_to_ticks(
    float seconds, int resolution, Array tempo_changes,
    Array time_signature_changes)
{
    std::vector<RhythmGameUtilities::Tempo> tempo_changes_internal;
    tempo_changes_internal.reserve(tempo_changes.size());

    for (auto i = 0; i < tempo_changes.size(); i += 1)
    {
        RhythmGameUtilities::Tempo tempo_change_internal;

        if (tempo_changes[i].get_type() == Variant::DICTIONARY)
        {
            Dictionary variant = tempo_changes[i];

            tempo_change_internal.Position = variant["position"];
            tempo_change_internal.BPM = variant["bpm"];
        }

        tempo_changes_internal.push_back(tempo_change_internal);
    }

    std::vector<RhythmGameUtilities::TimeSignature>
        time_signature_changes_internal;
    time_signature_changes_internal.reserve(time_signature_changes.size());

    for (auto i = 0; i < time_signature_changes.size(); i += 1)
    {
        RhythmGameUtilities::TimeSignature time_signature_internal;

        if (time_signature_changes[i].get_type() == Variant::DICTIONARY)
        {
            Dictionary variant = time_signature_changes[i];

            time_signature_internal.Position = variant["position"];
            time_signature_internal.Numerator = variant["numerator"];
            time_signature_internal.Denominator = variant["denominator"];
        }

        time_signature_changes_internal.push_back(time_signature_internal);
    }

    return RhythmGameUtilities::ConvertSecondsToTicks(
        seconds, resolution, tempo_changes_internal,
        time_signature_changes_internal);
}

float rhythm_game_utilities::convert_tick_to_position(int tick, int resolution)
{
    return RhythmGameUtilities::ConvertTickToPosition(tick, resolution);
}

Dictionary rhythm_game_utilities::find_position_near_given_tick(Array notes,
                                                                int tick,
                                                                int delta)
{
    std::vector<RhythmGameUtilities::Note> notes_internal;
    notes_internal.reserve(notes.size());

    for (auto i = 0; i < notes.size(); i += 1)
    {
        RhythmGameUtilities::Note note_internal;

        if (notes[i].get_type() == Variant::DICTIONARY)
        {
            Dictionary variant = notes[i];

            note_internal.Position = variant["position"];
            note_internal.HandPosition = variant["hand_position"];
            note_internal.Length = variant["length"];
        }

        notes_internal.push_back(note_internal);
    }

    auto note_internal = RhythmGameUtilities::FindPositionNearGivenTick(
        notes_internal, tick, delta);

    Dictionary note;

    if (note_internal)
    {
        note["position"] = note_internal->Position;
        note["hand_position"] = note_internal->HandPosition;
        note["length"] = note_internal->Length;
    }

    return note;
}

bool rhythm_game_utilities::is_on_the_beat(int bpm, float current_time,
                                           float delta)
{
    return RhythmGameUtilities::IsOnTheBeat(bpm, current_time, delta);
}

int rhythm_game_utilities::round_up_to_the_nearest_multiplier(int value,
                                                              int multiplier)
{
    return RhythmGameUtilities::RoundUpToTheNearestMultiplier(value,
                                                              multiplier);
}
