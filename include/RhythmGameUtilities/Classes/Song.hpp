// Rhythm Game Utilities -
// https://github.com/rhythm-game-utilities/rhythm-game-utilities
//
// ░█▀▄░█░█░█░█░▀█▀░█░█░█▄█░░░█▀▀░█▀█░█▄█░█▀▀░░░█░█░▀█▀░▀█▀░█░░░▀█▀░▀█▀░▀█▀░█▀▀░█▀▀
// ░█▀▄░█▀█░░█░░░█░░█▀█░█░█░░░█░█░█▀█░█░█░█▀▀░░░█░█░░█░░░█░░█░░░░█░░░█░░░█░░█▀▀░▀▀█
// ░▀░▀░▀░▀░░▀░░░▀░░▀░▀░▀░▀░░░▀▀▀░▀░▀░▀░▀░▀▀▀░░░▀▀▀░░▀░░▀▀▀░▀▀▀░▀▀▀░░▀░░▀▀▀░▀▀▀░▀▀▀
//
// Copyright (c) Scott Doxey. All Rights Reserved. Licensed under the MIT
// License. See LICENSE in the project root for license information.

#pragma once

#include <vector>

#include "../Enums/Difficulty.hpp"

#include "../Parsers/Chart.hpp"
#include "../Parsers/Midi.hpp"

#include "../Structs/BeatBar.hpp"
#include "../Structs/Note.hpp"
#include "../Structs/Tempo.hpp"
#include "../Structs/TimeSignature.hpp"

#include "../Utilities.hpp"

namespace RhythmGameUtilities
{

class Song
{
  public:
    int resolution;

    std::vector<Tempo> tempoChanges;

    std::vector<TimeSignature> timeSignatureChanges;

    std::vector<Note> notes;

    std::vector<BeatBar> beatBars;

    explicit Song() = default;
    explicit Song(int resolution, const std::vector<Tempo> &tempoChanges,
                  const std::vector<TimeSignature> &timeSignatureChanges,
                  const std::vector<Note> &notes,
                  const std::vector<BeatBar> &beatBars)
    {
        this->resolution = resolution;
        this->tempoChanges = tempoChanges;
        this->timeSignatureChanges = timeSignatureChanges;
        this->notes = notes;
        this->beatBars = beatBars;
    }

    auto static FromChartData(const std::string &contents,
                              Difficulty difficulty) -> Song
    {
        Song song;

        song.resolution = ReadResolutionFromChartData(contents.c_str());
        song.tempoChanges = ReadTempoChangesFromChartData(contents.c_str());
        song.timeSignatureChanges =
            ReadTimeSignatureChangesFromChartData(contents.c_str());
        song.notes = ReadNotesFromChartData(contents.c_str(), difficulty);
        song.beatBars =
            CalculateBeatBars(song.tempoChanges, song.timeSignatureChanges,
                              song.resolution, true);

        return song;
    }

    auto static FromMidiData(const std::vector<uint8_t> &bytes) -> Song
    {
        Song song;

        song.resolution = ReadResolutionFromMidiData(bytes);
        song.tempoChanges = ReadTempoChangesFromMidiData(bytes);
        song.timeSignatureChanges = ReadTimeSignatureChangesFromMidiData(bytes);
        song.notes = ReadNotesFromMidiData(bytes);
        song.beatBars =
            CalculateBeatBars(song.tempoChanges, song.timeSignatureChanges,
                              song.resolution, true);

        return song;
    }
};

} // namespace RhythmGameUtilities
