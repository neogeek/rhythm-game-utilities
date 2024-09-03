#pragma once

#include <map>
#include <string>

#include "RhythmGameUtilities/Enums/Difficulty.h"
#include "RhythmGameUtilities/Structs/BeatBar.h"
#include "RhythmGameUtilities/Structs/Note.h"

namespace RhythmGameUtilities
{

struct Song
{

    // Title of the song.
    std::string Name;

    // Artist(s) or band(s) behind the song.
    std::string Artist;

    // Title of the album the song is featured in.
    std::string Album;

    // Genre of the song.
    std::string Genre;

    // Year of the song’s release.<br />Typically preceded by a comma and space,
    // for example `, 2002`, to make importing into GHTCP quicker.
    std::string Year;

    // Community member who charted the song.
    std::string Charter;

    // (Required) Number of positional ticks between each 1/4th note in the
    // chart.
    int Resolution;

    // Estimated difficulty of the song.
    int Difficulty;

    // Start time of the audio, in seconds.<br />A higher value makes the audio
    // start sooner.
    double Offset;

    // Time of the song, in seconds, where the song preview should start.
    double PreviewStart;

    // Time of the song, in seconds, where the song preview should end.
    double PreviewEnd;

    // The main audio stream.<br />When other audio stems are present, this is
    // background audio not in the other tracks and/or instruments not charted.
    std::string MusicStream;

    std::map<int, std::string> Lyrics;

    std::map<DifficultyType, std::vector<Note>> Difficulties;

    std::map<int, int> BPM;

    std::map<int, std::vector<int>> TimeSignatures;

    std::vector<BeatBar> BeatBars;
};

} // namespace RhythmGameUtilities
