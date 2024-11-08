#include "rhythm_game_utilities.h"

#include "utilities.hpp"

#include <RhythmGameUtilities/Common.hpp>
#include <RhythmGameUtilities/Parsers.hpp>
#include <RhythmGameUtilities/Utilities.hpp>

void rhythm_game_utilities::_bind_methods()
{
    // Common

    ClassDB::bind_static_method("rhythm_game_utilities",
                                D_METHOD("lerp", "a", "b", "t"),
                                &rhythm_game_utilities::lerp);

    ClassDB::bind_static_method("rhythm_game_utilities",
                                D_METHOD("inverse_lerp", "a", "b", "v"),
                                &rhythm_game_utilities::inverse_lerp);

    // Parsers

    ClassDB::bind_static_method(
        "rhythm_game_utilities",
        D_METHOD("parse_sections_from_chart", "contents"),
        &rhythm_game_utilities::parse_sections_from_chart);

    ClassDB::bind_static_method(
        "rhythm_game_utilities",
        D_METHOD("parse_bpm_from_chart_section", "section"),
        &rhythm_game_utilities::parse_bpm_from_chart_section);

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
        D_METHOD("parse_time_signatures_from_chart_section", "section"),
        &rhythm_game_utilities::parse_time_signatures_from_chart_section);

    // Utilities

    ClassDB::bind_static_method(
        "rhythm_game_utilities",
        D_METHOD("convert_seconds_to_ticks", "seconds", "resolution",
                 "bpm_changes"),
        &rhythm_game_utilities::convert_seconds_to_ticks);

    ClassDB::bind_static_method(
        "rhythm_game_utilities",
        D_METHOD("convert_tick_to_position", "tick", "resolution"),
        &rhythm_game_utilities::convert_tick_to_position);

    ClassDB::bind_static_method(
        "rhythm_game_utilities",
        D_METHOD("is_on_the_beat", "bpm", "current_time", "delta"),
        &rhythm_game_utilities::is_on_the_beat);

    ClassDB::bind_static_method(
        "rhythm_game_utilities",
        D_METHOD("round_up_to_the_nearest_multiplier", "value", "multiplier"),
        &rhythm_game_utilities::round_up_to_the_nearest_multiplier);

    ClassDB::bind_static_method(
        "rhythm_game_utilities",
        D_METHOD("calculate_accuracy_ratio", "position", "current_position",
                 "delta"),
        &rhythm_game_utilities::calculate_accuracy_ratio);

    ClassDB::bind_static_method("rhythm_game_utilities",
                                D_METHOD("calculate_beat_bars", "bpm_changes",
                                         "resolution", "ts",
                                         "include_half_notes"),
                                &rhythm_game_utilities::calculate_beat_bars);
}

// Common

float rhythm_game_utilities::lerp(float a, float b, float t)
{
    return RhythmGameUtilities::Lerp(a, b, t);
}

float rhythm_game_utilities::inverse_lerp(float a, float b, float v)
{
    return RhythmGameUtilities::InverseLerp(a, b, v);
}

// Parsers

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

Dictionary rhythm_game_utilities::parse_bpm_from_chart_section(Array section)
{
    auto bpm_internal = RhythmGameUtilities::ParseBpmFromChartSection(
        convert_section_to_section_internal(section));

    Dictionary bpm;

    for (auto const &[key, val] : bpm_internal)
    {
        bpm[key] = bpm_internal[key];
    }

    return bpm;
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

        note["hand_position"] = note_internal.HandPosition;
        note["length"] = note_internal.Length;
        note["position"] = note_internal.Position;

        notes.append(note);
    }

    return notes;
}

Dictionary
rhythm_game_utilities::parse_time_signatures_from_chart_section(Array section)
{
    auto time_signatures_internal =
        RhythmGameUtilities::ParseTimeSignaturesFromChartSection(
            convert_section_to_section_internal(section));

    Dictionary time_signatures;

    for (auto const &[key, val] : time_signatures_internal)
    {
        time_signatures[key] = time_signatures_internal[key];
    }

    return time_signatures;
}

// Utilities

int rhythm_game_utilities::convert_seconds_to_ticks(float seconds,
                                                    int resolution,
                                                    Dictionary bpm_changes)
{
    return RhythmGameUtilities::ConvertSecondsToTicks(
        seconds, resolution, convert_dictionary_to_map<int, int>(bpm_changes));
}

float rhythm_game_utilities::convert_tick_to_position(int tick, int resolution)
{
    return RhythmGameUtilities::ConvertTickToPosition(tick, resolution);
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

float rhythm_game_utilities::calculate_accuracy_ratio(int position,
                                                      int current_position,
                                                      int delta)
{
    return RhythmGameUtilities::CalculateAccuracyRatio(position,
                                                       current_position, delta);
}

Array rhythm_game_utilities::calculate_beat_bars(Dictionary bpm_changes,
                                                 int resolution, int ts,
                                                 bool include_half_notes)
{
    auto beat_bars = RhythmGameUtilities::CalculateBeatBars(
        convert_dictionary_to_map<int, int>(bpm_changes), resolution, ts,
        include_half_notes);

    Array beat_bars_dictionary_array;

    for (auto &beat_bar : beat_bars)
    {
        Dictionary beat_bar_dictionary;

        beat_bar_dictionary["bpm"] = beat_bar.BPM;
        beat_bar_dictionary["position"] = beat_bar.Position;

        beat_bars_dictionary_array.append(beat_bar_dictionary);
    }

    return beat_bars_dictionary_array;
}
