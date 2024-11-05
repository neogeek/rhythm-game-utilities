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

    // Utilities

    ClassDB::bind_static_method(
        "rhythm_game_utilities",
        D_METHOD("convert_seconds_to_ticks", "seconds", "resolution",
                 "bpmChanges"),
        &rhythm_game_utilities::convert_seconds_to_ticks);

    ClassDB::bind_static_method(
        "rhythm_game_utilities",
        D_METHOD("convert_tick_to_position", "tick", "resolution"),
        &rhythm_game_utilities::convert_tick_to_position);

    ClassDB::bind_static_method(
        "rhythm_game_utilities",
        D_METHOD("is_on_the_beat", "bpm", "currentTime", "delta"),
        &rhythm_game_utilities::is_on_the_beat);

    ClassDB::bind_static_method(
        "rhythm_game_utilities",
        D_METHOD("round_up_to_the_nearest_multiplier", "value", "multiplier"),
        &rhythm_game_utilities::round_up_to_the_nearest_multiplier);

    ClassDB::bind_static_method(
        "rhythm_game_utilities",
        D_METHOD("calculate_accuracy_ratio", "position", "currentPosition",
                 "delta"),
        &rhythm_game_utilities::calculate_accuracy_ratio);

    ClassDB::bind_static_method("rhythm_game_utilities",
                                D_METHOD("calculate_beat_bars", "bpmChanges",
                                         "resolution", "ts",
                                         "includeHalfNotes"),
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

    auto sectionsInternal =
        RhythmGameUtilities::ParseSectionsFromChart(contents.utf8().get_data());

    for (auto sectionInternal = sectionsInternal.begin();
         sectionInternal != sectionsInternal.end(); sectionInternal++)
    {
        auto sectionKey = godot::String(sectionInternal->first.c_str());

        Dictionary section;

        for (auto i = 0; i < sectionInternal->second.size(); i += 1)
        {
            auto temp = sectionInternal->second[i];

            auto key = godot::Variant(temp.first.c_str());

            Array values;

            for (auto j = 0; j < temp.second.size(); j += 1)
            {
                values.append(godot::Variant(temp.second[j].c_str()));
            }

            section[key] = values;
        }

        sections[sectionKey] = section;
    }

    return sections;
}

// Utilities

int rhythm_game_utilities::convert_seconds_to_ticks(float seconds,
                                                    int resolution,
                                                    Dictionary bpmChanges)
{
    return RhythmGameUtilities::ConvertSecondsToTicks(
        seconds, resolution, convert_dictionary_to_map<int, int>(bpmChanges));
}

float rhythm_game_utilities::convert_tick_to_position(int tick, int resolution)
{
    return RhythmGameUtilities::ConvertTickToPosition(tick, resolution);
}

bool rhythm_game_utilities::is_on_the_beat(int bpm, float currentTime,
                                           float delta)
{
    return RhythmGameUtilities::IsOnTheBeat(bpm, currentTime, delta);
}

int rhythm_game_utilities::round_up_to_the_nearest_multiplier(int value,
                                                              int multiplier)
{
    return RhythmGameUtilities::RoundUpToTheNearestMultiplier(value,
                                                              multiplier);
}

float rhythm_game_utilities::calculate_accuracy_ratio(int position,
                                                      int currentPosition,
                                                      int delta)
{
    return RhythmGameUtilities::CalculateAccuracyRatio(position,
                                                       currentPosition, delta);
}

Array rhythm_game_utilities::calculate_beat_bars(Dictionary bpmChanges,
                                                 int resolution, int ts,
                                                 bool includeHalfNotes)
{
    auto beatBars = RhythmGameUtilities::CalculateBeatBars(
        convert_dictionary_to_map<int, int>(bpmChanges), resolution, ts,
        includeHalfNotes);

    Array beatBarsDictionaryArray;

    for (auto &beatBar : beatBars)
    {
        Dictionary beatBarDictionary;

        beatBarDictionary["bpm"] = beatBar.BPM;
        beatBarDictionary["position"] = beatBar.Position;

        beatBarsDictionaryArray.append(beatBarDictionary);
    }

    return beatBarsDictionaryArray;
}
