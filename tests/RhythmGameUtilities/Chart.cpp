#include <cassert>
#include <cstring>
#include <iostream>

#include "RhythmGameUtilities/Enums/Difficulty.hpp"
#include "RhythmGameUtilities/Parsers/Chart.hpp"

using namespace RhythmGameUtilities;

auto contents = R"([Song]
{
  Name = "Example Song"
  Artist = "Example Artist"
  Album = "Example Album"
  Genre = "Example Genre"
  Year = ", 2021"
  Charter = "Example Charter"
  Resolution = 192
  Difficulty = 4
  Offset = 0.56
  PreviewStart = 45.28
  PreviewEnd = 75.28
  MusicStream = "Example Song.ogg"
}
[SyncTrack]
{
  0 = TS 4
  0 = B 88000
  3840 = B 112000
  9984 = TS 2 1
  9984 = B 89600
  22272 = TS 4
  22272 = B 112000
  33792 = B 111500
  34560 = B 112000
  42240 = B 111980
  69120 = TS 2 1
}
[Events]
{
  768 = E "section Intro"
  9984 = E "phrase_start"
  9984 = E "section Verse 1"
  10080 = E "lyric Stand"
  10208 = E "lyric in"
  10344 = E "lyric line"
  10496 = E "lyric as"
  10608 = E "lyric we"
  10736 = E "lyric march"
  10896 = E "lyric to"
  11008 = E "lyric the"
  11112 = E "lyric drums"
  11268 = E "lyric of"
  11400 = E "lyric the"
  11520 = E "lyric east"
  11904 = E "phrase_end"
}
[ExpertSingle]
{
  768 = N 0 0
  768 = S 64 768
  864 = N 1 0
  864 = N 5 0
  960 = N 2 0
  960 = N 6 0
  1056 = N 3 0
  1056 = E solo
  1152 = N 4 0
  1248 = N 7 0
  1248 = E soloend
})";

void testReadResolutionFromChartData()
{
    auto resolution = ReadResolutionFromChartData(contents);

    assert(resolution == 192);

    std::cout << ".";
}

void testReadTempoChangesFromChartData()
{
    auto tempoChanges = ReadTempoChangesFromChartData(contents);

    assert(tempoChanges.size() == 7);

    std::cout << ".";
}

void testReadTimeSignatureChangesFromChartData()
{
    auto timeSignatureChanges = ReadTimeSignatureChangesFromChartData(contents);

    assert(timeSignatureChanges.size() == 4);

    std::cout << ".";
}

void testReadNotesFromChartData()
{
    auto notes = ReadNotesFromChartData(contents, Difficulty::Expert);

    assert(notes.size() == 8);

    std::cout << ".";
}

void testReadLyricsFromChartData()
{
    auto lyrics = ReadLyricsFromChartData(contents);

    assert(lyrics.size() == 12);

    std::cout << ".";
}

auto main() -> int
{
    testReadResolutionFromChartData();
    testReadTempoChangesFromChartData();
    testReadTimeSignatureChangesFromChartData();
    testReadNotesFromChartData();
    testReadLyricsFromChartData();

    return 0;
}
