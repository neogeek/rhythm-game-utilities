#include <cassert>
#include <cstring>
#include <iostream>

#include "RhythmGameUtilities/Enums/Difficulty.hpp"
#include "RhythmGameUtilities/Enums/NamedSection.hpp"
#include "RhythmGameUtilities/Parsers/ChartInternal.hpp"

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

auto FindSection(ChartSectionInternal *sections, int size, std::string name)
    -> ChartSectionInternal *
{
    for (auto i = 0; i < size; i += 1)
    {
        if (sections[i].name == name)
        {
            return &sections[i];
        }
    }

    return nullptr;
}

void testParseSectionsFromChartInternal()
{
    int size = 0;

    auto *sections = ParseSectionsFromChartInternal(contents, &size);

    assert(size == 4);

    auto *song = FindSection(sections, size, ToString(NamedSection::Song));

    auto *syncTrack =
        FindSection(sections, size, ToString(NamedSection::SyncTrack));

    auto *events = FindSection(sections, size, ToString(NamedSection::Events));

    auto *expertSingle =
        FindSection(sections, size, ToString(Difficulty::Expert) + "Single");

    assert(song != nullptr);
    assert(song->lineCount == 12);
    assert(syncTrack != nullptr);
    assert(syncTrack->lineCount == 11);
    assert(events != nullptr);
    assert(events->lineCount == 16);
    assert(expertSingle != nullptr);
    assert(expertSingle->lineCount == 11);

    std::cout << ".";
}

void testParseValuesFromChartSectionInternal()
{
    int size = 0;

    auto *sections = ParseSectionsFromChartInternal(contents, &size);

    assert(size == 4);

    auto *song = FindSection(sections, size, ToString(NamedSection::Song));

    assert(song->lineCount == 12);

    assert(strcmp(song->lines[0].key, "Name") == 0);
    assert(strcmp(song->lines[0].values[0], "Example Song") == 0);

    assert(strcmp(song->lines[6].key, "Resolution") == 0);
    assert(strcmp(song->lines[6].values[0], "192") == 0);

    assert(strcmp(song->lines[11].key, "MusicStream") == 0);
    assert(strcmp(song->lines[11].values[0], "Example Song.ogg") == 0);

    std::cout << ".";
}

auto main() -> int
{
    testParseSectionsFromChartInternal();
    testParseValuesFromChartSectionInternal();

    return 0;
}
