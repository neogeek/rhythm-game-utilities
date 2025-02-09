#include <cassert>
#include <cstring>
#include <iostream>

#include "RhythmGameUtilities/Parsers.hpp"

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

void testParseBpmFromChartSection()
{
    auto sections = ParseSectionsFromChart(contents);

    auto bpm = ParseBpmFromChartSection(
        sections.at(ToString(NamedSection::SyncTrack)));

    assert(bpm.size() == 7);

    std::cout << ".";
}

void testParseLyricsFromChartSection()
{
    auto sections = ParseSectionsFromChart(contents);

    auto lyrics = ParseLyricsFromChartSection(
        sections.at(ToString(NamedSection::Events)));

    assert(lyrics.size() == 12);

    std::cout << ".";
}

void testParseMetaDataFromChartSection()
{
    auto sections = ParseSectionsFromChart(contents);

    auto metaData = ParseMetaDataFromChartSection(
        sections.at(ToString(NamedSection::Song)));

    assert(metaData.size() == 12);

    assert(metaData.at("Name") == "Example Song");
    assert(metaData.at("Resolution") == "192");
    assert(metaData.at("MusicStream") == "Example Song.ogg");

    std::cout << ".";
}

void testParseNotesFromChartSection()
{
    auto sections = ParseSectionsFromChart(contents);

    auto notes = ParseNotesFromChartSection(
        sections.at(ToString(Difficulty::Expert) + "Single"));

    assert(notes.size() == 8);

    std::cout << ".";
}

void testParseSectionsFromChart()
{
    auto sections = ParseSectionsFromChart(contents);

    assert(sections.size() == 4);

    assert(sections.find(ToString(NamedSection::Song)) != sections.end());
    assert(sections.find(ToString(NamedSection::SyncTrack)) != sections.end());
    assert(sections.find(ToString(Difficulty::Expert) + "Single") !=
           sections.end());

    std::cout << ".";
}

void testParseTimeSignaturesFromChartSection()
{
    auto sections = ParseSectionsFromChart(contents);

    auto timeSignatures = ParseTimeSignaturesFromChartSection(
        sections.at(ToString(NamedSection::SyncTrack)));

    assert(timeSignatures.size() == 4);

    std::cout << ".";
}

void testParseValuesFromChartSection()
{
    auto sections = ParseSectionsFromChart(contents);

    assert(sections.size() == 4);

    auto values = sections.at(ToString(NamedSection::Song));

    assert(values.size() == 12);

    assert(values[0].first == "Name");
    assert(values[0].second[0] == "Example Song");

    assert(values[6].first == "Resolution");
    assert(values[6].second[0] == "192");

    assert(values[11].first == "MusicStream");
    assert(values[11].second[0] == "Example Song.ogg");

    std::cout << ".";
}

int main()
{
    testParseBpmFromChartSection();
    testParseLyricsFromChartSection();
    testParseMetaDataFromChartSection();
    testParseNotesFromChartSection();
    testParseSectionsFromChart();
    testParseTimeSignaturesFromChartSection();

    testParseValuesFromChartSection();

    return 0;
}
