#include "RhythmGameUtilities/Common.hpp"

#include <lua/lua.hpp>

static auto lua_Lerp(lua_State *L) -> int
{
    float a = luaL_checknumber(L, 1);
    float b = luaL_checknumber(L, 2);
    float t = luaL_checknumber(L, 3);

    float result = RhythmGameUtilities::Lerp(a, b, t);

    lua_pushnumber(L, result);

    return 1;
}

static auto lua_InverseLerp(lua_State *L) -> int
{
    float a = luaL_checknumber(L, 1);
    float b = luaL_checknumber(L, 2);
    float v = luaL_checknumber(L, 3);

    float result = RhythmGameUtilities::InverseLerp(a, b, v);

    lua_pushnumber(L, result);

    return 1;
}

static const luaL_Reg rhythmgameutilities_functions[] = {
    {"lerp", lua_Lerp}, {"inverse_lerp", lua_InverseLerp}};

extern "C" int luaopen_rhythmgameutilities(lua_State *L)
{
    luaL_newlib(L, rhythmgameutilities_functions);
    return 1;
}
