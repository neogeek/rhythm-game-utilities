#include <cassert>
#include <cstring>
#include <iostream>

#include "RhythmGameUtilities/File.hpp"
#include "RhythmGameUtilities/Parsers/Stepfile.hpp"

using namespace RhythmGameUtilities;

void testParseSectionsFromStepfile()
{
    auto contents = ReadStringFromFile("./tests/Mocks/stepfile.ssc");

    ParseSectionsFromStepfile(contents.c_str());

    std::cout << ".";
}

auto main() -> int
{
    testParseSectionsFromStepfile();

    return 0;
}
