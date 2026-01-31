#include "RhythmGameUtilities/Common.hpp"
#include "RhythmGameUtilities/Utilities.hpp"

#include <lua/lua.hpp>

// Common

static auto lua_inverse_lerp(lua_State *L) -> int
{
    float a = luaL_checknumber(L, 1);
    float b = luaL_checknumber(L, 2);
    float v = luaL_checknumber(L, 3);

    float result = RhythmGameUtilities::InverseLerp(a, b, v);

    lua_pushnumber(L, result);

    return 1;
}

static auto lua_lerp(lua_State *L) -> int
{
    float a = luaL_checknumber(L, 1);
    float b = luaL_checknumber(L, 2);
    float t = luaL_checknumber(L, 3);

    float result = RhythmGameUtilities::Lerp(a, b, t);

    lua_pushnumber(L, result);

    return 1;
}

// Utilities

static auto lua_calculate_accuracy_ratio(lua_State *L) -> int
{
    int position = luaL_checknumber(L, 1);
    int current_position = luaL_checknumber(L, 2);
    int delta = luaL_checknumber(L, 3);

    float result = RhythmGameUtilities::CalculateAccuracyRatio(
        position, current_position, delta);

    lua_pushnumber(L, result);

    return 1;
}

static auto lua_convert_tick_to_position(lua_State *L) -> int
{
    int tick = luaL_checknumber(L, 1);
    int resolution = luaL_checknumber(L, 2);

    float result = RhythmGameUtilities::ConvertTickToPosition(tick, resolution);

    lua_pushnumber(L, result);

    return 1;
}

static auto lua_is_on_the_beat(lua_State *L) -> int
{
    int bpm = luaL_checknumber(L, 1);
    float current_time = luaL_checknumber(L, 2);
    float delta = luaL_checknumber(L, 3);

    bool result = RhythmGameUtilities::IsOnTheBeat(bpm, current_time, delta);

    lua_pushboolean(L, result);

    return 1;
}

static auto lua_round_up_to_the_nearest_multiplier(lua_State *L) -> int
{
    int value = luaL_checknumber(L, 1);
    int multiplier = luaL_checknumber(L, 2);

    int result =
        RhythmGameUtilities::RoundUpToTheNearestMultiplier(value, multiplier);

    lua_pushnumber(L, result);

    return 1;
}

static const luaL_Reg rhythmgameutilities_functions[] = {
    {"inverse_lerp", lua_inverse_lerp},
    {"lerp", lua_lerp},
    {"calculate_accuracy_ratio", lua_calculate_accuracy_ratio},
    {"convert_tick_to_position", lua_convert_tick_to_position},
    {"is_on_the_beat", lua_is_on_the_beat},
    {"round_up_to_the_nearest_multiplier",
     lua_round_up_to_the_nearest_multiplier}};

extern "C" auto luaopen_rhythmgameutilities(lua_State *L) -> int
{
    luaL_newlib(L, rhythmgameutilities_functions);
    return 1;
}
