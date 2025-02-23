#include <cassert>
#include <cmath>
#include <iostream>
#include <tuple>

#include "RhythmGameUtilities/CommonInternal.hpp"

using namespace RhythmGameUtilities;

void testInverseLerpInternal()
{
    auto value = InverseLerpInternal(0, 10, 5);

    assert(abs(0.5 - value) < 0.01);

    std::cout << ".";
}

void testLerpInternal()
{
    auto value = LerpInternal(0, 10, 0.5f);

    assert(5 == value);

    std::cout << ".";
}

int main()
{
    testInverseLerpInternal();
    testLerpInternal();

    return 0;
}
