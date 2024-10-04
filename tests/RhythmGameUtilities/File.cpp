#include <cassert>
#include <iostream>

#include "RhythmGameUtilities/File.hpp"

using namespace RhythmGameUtilities;

void testReadFromFile()
{
    assert(ReadFromFile("./tests/Mocks/test.txt") == "Hello, world!\n");

    std::cout << ".";
}

int main()
{
    testReadFromFile();

    return 0;
}
