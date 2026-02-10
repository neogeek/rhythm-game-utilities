#include <cassert>
#include <cstring>
#include <iostream>

#include "RhythmGameUtilities/File.hpp"
#include "RhythmGameUtilities/Parsers/Chart.hpp"

using namespace RhythmGameUtilities;

void testReadResolutionFromChartData()
{
    auto contents = ReadStringFromFile("./tests/Mocks/song.chart");

    auto resolution = ReadResolutionFromChartData(contents.c_str());

    assert(resolution == 192);

    std::cout << ".";
}

void testReadTempoChangesFromChartData()
{
    auto contents = ReadStringFromFile("./tests/Mocks/song.chart");

    auto tempoChanges = ReadTempoChangesFromChartData(contents.c_str());

    assert(tempoChanges.size() == 7);

    std::cout << ".";
}

void testReadTimeSignatureChangesFromChartData()
{
    auto contents = ReadStringFromFile("./tests/Mocks/song.chart");

    auto timeSignatureChanges =
        ReadTimeSignatureChangesFromChartData(contents.c_str());

    assert(timeSignatureChanges.size() == 4);

    std::cout << ".";
}

void testReadNotesFromChartData()
{
    auto contents = ReadStringFromFile("./tests/Mocks/song.chart");

    auto notes = ReadNotesFromChartData(contents.c_str(), Difficulty::Expert);

    assert(notes.size() == 8);

    std::cout << ".";
}

void testReadLyricsFromChartData()
{
    auto contents = ReadStringFromFile("./tests/Mocks/song.chart");

    auto lyrics = ReadLyricsFromChartData(contents.c_str());

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
