#include <cassert>
#include <cstring>
#include <iostream>

#include "RhythmGameUtilities/Parsers.h"

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

void testParseSectionsFromChart()
{
    auto sections = ParseSectionsFromChart(contents);

    assert(sections.size() == 4);

    assert(sections.at(0).name == "Song");
    assert(sections.at(1).name == "SyncTrack");
    assert(sections.at(2).name == "Events");
    assert(sections.at(3).name == "ExpertSingle");

    std::cout << ".";
}

void testParseValuesFromChartSections()
{
    auto sections = ParseSectionsFromChart(contents);

    assert(sections.size() == 4);

    assert(sections.at(0).name == "Song");
    assert(sections.at(0).lines.size() == 12);

    assert(sections.at(0).lines[0].first == "Name");
    assert(sections.at(0).lines[0].second[0] == "Example Song");

    assert(sections.at(0).lines[6].first == "Resolution");
    assert(sections.at(0).lines[6].second[0] == "192");

    assert(sections.at(0).lines[11].first == "MusicStream");
    assert(sections.at(0).lines[11].second[0] == "Example Song.ogg");

    std::cout << ".";
}

void testParseSectionsFromChartInternal()
{
    int size = 0;

    auto sections = ParseSectionsFromChartInternal(contents, &size);

    assert(size == 4);

    assert(strcmp(sections[0].name, "Song") == 0);
    assert(sections[0].lineCount == 12);
    assert(strcmp(sections[1].name, "SyncTrack") == 0);
    assert(sections[1].lineCount == 11);
    assert(strcmp(sections[2].name, "Events") == 0);
    assert(sections[2].lineCount == 16);
    assert(strcmp(sections[3].name, "ExpertSingle") == 0);
    assert(sections[3].lineCount == 11);

    std::cout << ".";
}

void testParseValuesFromChartSectionsInternal()
{
    int size = 0;

    auto sections = ParseSectionsFromChartInternal(contents, &size);

    assert(size == 4);

    assert(sections[0].lineCount == 12);

    assert(strcmp(sections[0].lines[0].key, "Name") == 0);
    assert(strcmp(sections[0].lines[0].values[0], "Example Song") == 0);

    assert(strcmp(sections[0].lines[6].key, "Resolution") == 0);
    assert(strcmp(sections[0].lines[6].values[0], "192") == 0);

    assert(strcmp(sections[0].lines[11].key, "MusicStream") == 0);
    assert(strcmp(sections[0].lines[11].values[0], "Example Song.ogg") == 0);

    std::cout << ".";
}

int main()
{
    testParseSectionsFromChart();
    testParseValuesFromChartSections();
    testParseSectionsFromChartInternal();
    testParseValuesFromChartSectionsInternal();

    return 0;
}
