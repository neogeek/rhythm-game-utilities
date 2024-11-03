#include "rhythm_game_utilities.h"

#include <RhythmGameUtilities/Common.hpp>

void rhythm_game_utilities::_bind_methods()
{
    ClassDB::bind_static_method("rhythm_game_utilities",
                                D_METHOD("lerp", "a", "b", "t"),
                                &rhythm_game_utilities::lerp);

    ClassDB::bind_static_method("rhythm_game_utilities",
                                D_METHOD("inverse_lerp", "a", "b", "v"),
                                &rhythm_game_utilities::inverse_lerp);
}

float rhythm_game_utilities::lerp(float a, float b, float t)
{
    return RhythmGameUtilities::Lerp(a, b, t);
}

float rhythm_game_utilities::inverse_lerp(float a, float b, float v)
{
    return RhythmGameUtilities::InverseLerp(a, b, v);
}
