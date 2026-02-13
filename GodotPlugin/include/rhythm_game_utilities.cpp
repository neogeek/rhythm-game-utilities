#include "godot_cpp/variant/variant.hpp"

#include "rhythm_game_utilities.hpp"

#include <RhythmGameUtilities/Common.hpp>
#include <RhythmGameUtilities/Enums/Difficulty.hpp>
#include <RhythmGameUtilities/Parsers/Chart.hpp>
#include <RhythmGameUtilities/Parsers/Midi.hpp>
#include <RhythmGameUtilities/Utilities.hpp>

void rhythm_game_utilities::_bind_methods()
{
    // Enums

    BIND_ENUM_CONSTANT(Easy);
    BIND_ENUM_CONSTANT(Medium);
    BIND_ENUM_CONSTANT(Hard);
    BIND_ENUM_CONSTANT(Expert);

    // Common

    ClassDB::bind_static_method("rhythm_game_utilities",
                                D_METHOD("inverse_lerp", "a", "b", "v"),
                                &rhythm_game_utilities::inverse_lerp);

    ClassDB::bind_static_method("rhythm_game_utilities",
                                D_METHOD("lerp", "a", "b", "t"),
                                &rhythm_game_utilities::lerp);

    // Parsers (Chart)

    ClassDB::bind_static_method(
        "rhythm_game_utilities",
        D_METHOD("read_resolution_from_chart_data", "contents"),
        &rhythm_game_utilities::read_resolution_from_chart_data);

    ClassDB::bind_static_method(
        "rhythm_game_utilities",
        D_METHOD("read_tempo_changes_from_chart_data", "contents"),
        &rhythm_game_utilities::read_tempo_changes_from_chart_data);

    ClassDB::bind_static_method(
        "rhythm_game_utilities",
        D_METHOD("read_time_signature_changes_from_chart_data", "contents"),
        &rhythm_game_utilities::read_time_signature_changes_from_chart_data);

    ClassDB::bind_static_method(
        "rhythm_game_utilities",
        D_METHOD("read_notes_from_chart_data", "contents", "difficulty"),
        &rhythm_game_utilities::read_notes_from_chart_data);

    // Parsers (Midi)

    ClassDB::bind_static_method(
        "rhythm_game_utilities",
        D_METHOD("read_resolution_from_midi_data", "data"),
        &rhythm_game_utilities::read_resolution_from_midi_data);

    ClassDB::bind_static_method(
        "rhythm_game_utilities",
        D_METHOD("read_tempo_changes_from_midi_data", "data"),
        &rhythm_game_utilities::read_tempo_changes_from_midi_data);

    ClassDB::bind_static_method(
        "rhythm_game_utilities",
        D_METHOD("read_time_signature_changes_from_midi_data", "data"),
        &rhythm_game_utilities::read_time_signature_changes_from_midi_data);

    ClassDB::bind_static_method(
        "rhythm_game_utilities", D_METHOD("read_notes_from_midi_data", "data"),
        &rhythm_game_utilities::read_notes_from_midi_data);

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
        D_METHOD("find_positions_near_given_tick", "notes", "tick", "delta"),
        &rhythm_game_utilities::find_positions_near_given_tick);

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

auto rhythm_game_utilities::inverse_lerp(float a, float b, float v) -> float
{
    return RhythmGameUtilities::InverseLerp(a, b, v);
}

auto rhythm_game_utilities::lerp(float a, float b, float t) -> float
{
    return RhythmGameUtilities::Lerp(a, b, t);
}

// Parsers (Chart)

auto rhythm_game_utilities::read_resolution_from_chart_data(
    const String &contents) -> int
{
    auto resolution = RhythmGameUtilities::ReadResolutionFromChartData(
        contents.utf8().get_data());

    return resolution;
}

auto rhythm_game_utilities::read_tempo_changes_from_chart_data(
    const String &contents) -> Array
{
    auto tempo_changes_internal =
        RhythmGameUtilities::ReadTempoChangesFromChartData(
            contents.utf8().get_data());

    Array tempo_changes;

    for (const auto &tempo_change_internal : tempo_changes_internal)
    {
        Dictionary tempo_change;

        tempo_change["position"] = tempo_change_internal.Position;
        tempo_change["bpm"] = tempo_change_internal.BPM;

        tempo_changes.append(tempo_change);
    }

    return tempo_changes;
}

auto rhythm_game_utilities::read_time_signature_changes_from_chart_data(
    const String &contents) -> Array
{
    auto time_signature_changes_internal =
        RhythmGameUtilities::ReadTimeSignatureChangesFromChartData(
            contents.utf8().get_data());

    Array time_signature_changes;

    for (const auto &time_signature_change_internal :
         time_signature_changes_internal)
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

auto rhythm_game_utilities::read_notes_from_chart_data(const String &contents,
                                                       int difficulty) -> Array
{
    auto notes_internal = RhythmGameUtilities::ReadNotesFromChartData(
        contents.utf8().get_data(),
        static_cast<RhythmGameUtilities::Difficulty>(difficulty));

    Array notes;

    for (const auto &note_internal : notes_internal)
    {
        Dictionary note;

        note["position"] = note_internal.Position;
        note["hand_position"] = note_internal.HandPosition;
        note["length"] = note_internal.Length;

        notes.append(note);
    }

    return notes;
}

// Parsers (Midi)

auto rhythm_game_utilities::read_resolution_from_midi_data(const Variant &data)
    -> int
{
    std::vector<uint8_t> buffer;

    if (data.get_type() == Variant::PACKED_BYTE_ARRAY)
    {
        PackedByteArray bytes = data;

        buffer.resize(bytes.size());

        std::copy(bytes.ptr(), bytes.ptr() + bytes.size(), buffer.begin());
    }

    return RhythmGameUtilities::ReadResolutionFromMidiData(buffer);
}

auto rhythm_game_utilities::read_tempo_changes_from_midi_data(
    const Variant &data) -> Array
{

    std::vector<uint8_t> buffer;

    if (data.get_type() == Variant::PACKED_BYTE_ARRAY)
    {
        PackedByteArray bytes = data;

        buffer.resize(bytes.size());

        std::copy(bytes.ptr(), bytes.ptr() + bytes.size(), buffer.begin());
    }

    auto tempo_changes_internal =
        RhythmGameUtilities::ReadTempoChangesFromMidiData(buffer);

    Array tempo_changes;

    for (const auto &tempo_change_internal : tempo_changes_internal)
    {
        Dictionary tempo_change;

        tempo_change["position"] = tempo_change_internal.Position;
        tempo_change["bpm"] = tempo_change_internal.BPM;

        tempo_changes.append(tempo_change);
    }

    return tempo_changes;
}

auto rhythm_game_utilities::read_time_signature_changes_from_midi_data(
    const Variant &data) -> Array
{
    std::vector<uint8_t> buffer;

    if (data.get_type() == Variant::PACKED_BYTE_ARRAY)
    {
        PackedByteArray bytes = data;

        buffer.resize(bytes.size());

        std::copy(bytes.ptr(), bytes.ptr() + bytes.size(), buffer.begin());
    }

    auto time_signature_changes_internal =
        RhythmGameUtilities::ReadTimeSignatureChangesFromMidiData(buffer);

    Array time_signature_changes;

    for (const auto &time_signature_change_internal :
         time_signature_changes_internal)
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

auto rhythm_game_utilities::read_notes_from_midi_data(const Variant &data)
    -> Array
{
    std::vector<uint8_t> buffer;

    if (data.get_type() == Variant::PACKED_BYTE_ARRAY)
    {
        PackedByteArray bytes = data;

        buffer.resize(bytes.size());

        std::copy(bytes.ptr(), bytes.ptr() + bytes.size(), buffer.begin());
    }

    auto notes_internal = RhythmGameUtilities::ReadNotesFromMidiData(buffer);

    Array notes;

    for (const auto &note_internal : notes_internal)
    {
        Dictionary note;

        note["position"] = note_internal.Position;
        note["hand_position"] = note_internal.HandPosition;
        note["length"] = note_internal.Length;

        notes.append(note);
    }

    return notes;
}

// Utilities

auto rhythm_game_utilities::calculate_accuracy_ratio(int position,
                                                     int current_position,
                                                     int delta) -> float
{
    return RhythmGameUtilities::CalculateAccuracyRatio(position,
                                                       current_position, delta);
}

auto rhythm_game_utilities::calculate_beat_bars(Array tempo_changes,
                                                int resolution, int ts,
                                                bool include_half_notes)
    -> Array
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

    for (const auto &beat_bar_internal : beat_bars_internal)
    {
        Dictionary beat_bar_dictionary;

        beat_bar_dictionary["position"] = beat_bar_internal.Position;
        beat_bar_dictionary["bpm"] = beat_bar_internal.BPM;

        beat_bars_dictionary_array.append(beat_bar_dictionary);
    }

    return beat_bars_dictionary_array;
}

auto rhythm_game_utilities::convert_seconds_to_ticks(
    float seconds, int resolution, Array tempo_changes,
    Array time_signature_changes) -> int
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

auto rhythm_game_utilities::convert_tick_to_position(int tick, int resolution)
    -> float
{
    return RhythmGameUtilities::ConvertTickToPosition(tick, resolution);
}

auto rhythm_game_utilities::find_positions_near_given_tick(Array notes,
                                                           int tick, int delta)
    -> Array
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

    auto matched_notes_internal =
        RhythmGameUtilities::FindPositionsNearGivenTick(notes_internal, tick,
                                                        delta);

    Array matched_notes_dictionary_array;

    for (const auto &matched_note_internal : matched_notes_internal)
    {
        Dictionary matched_note_dictionary;

        matched_note_dictionary["position"] = matched_note_internal.Position;
        matched_note_dictionary["hand_position"] =
            matched_note_internal.HandPosition;
        matched_note_dictionary["length"] = matched_note_internal.Length;

        matched_notes_dictionary_array.append(matched_note_dictionary);
    }

    return matched_notes_dictionary_array;
}

auto rhythm_game_utilities::is_on_the_beat(int bpm, float current_time,
                                           float delta) -> bool
{
    return RhythmGameUtilities::IsOnTheBeat(bpm, current_time, delta);
}

auto rhythm_game_utilities::round_up_to_the_nearest_multiplier(int value,
                                                               int multiplier)
    -> int
{
    return RhythmGameUtilities::RoundUpToTheNearestMultiplier(value,
                                                              multiplier);
}
