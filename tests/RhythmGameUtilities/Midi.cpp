#include <cassert>
#include <iostream>

#include "RhythmGameUtilities/File.hpp"
#include "RhythmGameUtilities/Parsers/Midi.hpp"

using namespace RhythmGameUtilities;

void testReadResolutionFromMidiData()
{
    auto bytes = ReadBytesFromFile("./tests/Mocks/song.mid");

    auto resolution = ReadResolutionFromMidiData(bytes);

    assert(resolution == 480);

    std::cout << ".";
}

void testReadTempoChangesFromMidiData()
{
    auto bytes = ReadBytesFromFile("./tests/Mocks/song.mid");

    auto tempChanges = ReadTempoChangesFromMidiData(bytes);

    assert(size(tempChanges) == 1);
    assert(tempChanges[0].Position == 0);
    assert(tempChanges[0].BPM == 120000);

    std::cout << ".";
}
void testReadTimeSignatureChangesFromMidiData()
{
    auto bytes = ReadBytesFromFile("./tests/Mocks/song.mid");

    auto timeSignatureChanges = ReadTimeSignatureChangesFromMidiData(bytes);

    assert(size(timeSignatureChanges) == 1);

    assert(timeSignatureChanges[0].Position == 0);
    assert(timeSignatureChanges[0].Numerator == 4);
    assert(timeSignatureChanges[0].Denominator == 4);

    std::cout << ".";
}

void testReadNotesFromMidiData()
{
    auto bytes = ReadBytesFromFile("./tests/Mocks/song.mid");

    auto notes = ReadNotesFromMidiData(bytes);

    assert(size(notes) == 10);

    assert(notes[0].Position == 0);
    assert(notes[0].HandPosition == 48);

    assert(notes[1].Position == 480);
    assert(notes[1].HandPosition == 50);

    assert(notes[2].Position == 960);
    assert(notes[2].HandPosition == 52);

    assert(notes[3].Position == 1440);
    assert(notes[3].HandPosition == 54);

    assert(notes[4].Position == 1920);
    assert(notes[4].HandPosition == 56);

    assert(notes[5].Position == 2400);
    assert(notes[5].HandPosition == 48);

    assert(notes[6].Position == 2400);
    assert(notes[6].HandPosition == 50);

    assert(notes[7].Position == 2400);
    assert(notes[7].HandPosition == 52);

    assert(notes[8].Position == 2400);
    assert(notes[8].HandPosition == 54);

    assert(notes[9].Position == 2400);
    assert(notes[9].HandPosition == 56);

    std::cout << ".";
}

auto main() -> int
{
    testReadResolutionFromMidiData();
    testReadTempoChangesFromMidiData();
    testReadTimeSignatureChangesFromMidiData();
    testReadNotesFromMidiData();

    return 0;
}
