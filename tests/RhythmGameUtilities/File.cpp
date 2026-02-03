#include <cassert>
#include <iostream>

#include "RhythmGameUtilities/File.hpp"

using namespace RhythmGameUtilities;

void testReadBytesFromFile()
{
    assert(size(ReadBytesFromFile("./tests/Mocks/test.txt")) == 14);

    std::cout << ".";
}

void testReadStringFromFile()
{
    assert(ReadStringFromFile("./tests/Mocks/test.txt") == "Hello, world!\n");

    std::cout << ".";
}

auto main() -> int
{
    testReadBytesFromFile();
    testReadStringFromFile();

    return 0;
}
