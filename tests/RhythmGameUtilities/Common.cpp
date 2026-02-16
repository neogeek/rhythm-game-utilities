#include <cassert>
#include <cmath>
#include <iostream>

#include "RhythmGameUtilities/Common.hpp"

using namespace RhythmGameUtilities;

void testInverseLerpUnclamped()
{
    auto value = InverseLerpUnclamped(0, 10, 11);

    assert(abs(1.1 - value) < 0.01);

    std::cout << ".";
}

void testInverseLerp()
{
    auto value = InverseLerp(0, 10, 5);

    assert(abs(0.5 - value) < 0.01);

    std::cout << ".";
}

void testLerp()
{
    auto value = Lerp(0, 10, 0.5f);

    assert(5 == value);

    std::cout << ".";
}

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
    std::regex pattern(R"((\w+)\s+(\w+)\s+(\w+)\s+(\w+))");

    auto sections = FindMatchGroups("this is a test", pattern);

    assert(sections.size() == 5);

    std::cout << ".";
}

auto main() -> int
{
    testInverseLerpUnclamped();
    testInverseLerp();
    testLerp();
    testTrim();
    testSplit();
    testFindAllMatches();
    testFindMatchGroups();

    return 0;
}
