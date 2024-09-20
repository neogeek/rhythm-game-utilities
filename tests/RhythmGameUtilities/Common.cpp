#include <cassert>
#include <cmath>
#include <iostream>
#include <tuple>

#include "RhythmGameUtilities/Common.hpp"

using namespace RhythmGameUtilities;

void testTrim()
{
    assert(Trim(" test ") == "test");

    std::cout << ".";
}

void testSplit()
{
    auto parts = Split("key=value", '=');

    assert(parts.size() == 2);
    assert(parts[0] == "key");
    assert(parts[1] == "value");

    std::cout << ".";
}

void testFindAllMatches()
{
    std::regex pattern("\\w+");

    auto sections = FindAllMatches("this is a test", pattern);

    assert(sections.size() == 4);

    std::cout << ".";
}

void testFindMatchGroups()
{
    std::regex pattern("(\\w+)\\s+(\\w+)\\s+(\\w+)\\s+(\\w+)");

    auto sections = FindMatchGroups("this is a test", pattern);

    assert(sections.size() == 5);

    std::cout << ".";
}

int main()
{
    testTrim();
    testSplit();
    testFindAllMatches();
    testFindMatchGroups();

    return 0;
}
