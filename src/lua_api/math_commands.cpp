#include <windows.h>
#include "sofheader.h"
#include "lua_api/generic.h"
#include "engine_features/math/math.h"

int sf_sv_math_sin(lua_State* L) {
	float angle = lua_tonumber(L, 1);
	float result = engine_math_sin(angle);
	lua_pushnumber(L, result);
	return 1;
}

int sf_sv_math_asin(lua_State* L) {
	float value = lua_tonumber(L, 1);
	float result = engine_math_asin(value);
	lua_pushnumber(L, result);
	return 1;
}

int sf_sv_math_cos(lua_State* L) {
	float angle = lua_tonumber(L, 1);
	float result = engine_math_cos(angle);
	lua_pushnumber(L, result);
	return 1;
}

int sf_sv_math_acos(lua_State* L) {
	float value = lua_tonumber(L, 1);
	float result = engine_math_acos(value);
	lua_pushnumber(L, result);
	return 1;
}

int sf_sv_math_tan(lua_State* L) {
	float angle = lua_tonumber(L, 1);
	float result = engine_math_tan(angle);
	lua_pushnumber(L, result);
	return 1;
}

int sf_sv_math_atan(lua_State* L) {
	float value = lua_tonumber(L, 1);
	float result = engine_math_atan(value);
	lua_pushnumber(L, result);
	return 1;
}

int sf_sv_math_or(lua_State* L) {
	unsigned int a = lua_tointeger(L, 1);
	unsigned int b = lua_tointeger(L, 2);
	unsigned int result = engine_math_or(a, b);
	lua_pushinteger(L, result);
	return 1;
}

int sf_sv_math_and(lua_State* L) {
	unsigned int a = lua_tointeger(L, 1);
	unsigned int b = lua_tointeger(L, 2);
	unsigned int result = engine_math_and(a, b);
	lua_pushinteger(L, result);
	return 1;
}

int sf_sv_math_not(lua_State* L) {
	unsigned int a = lua_tointeger(L, 1);
	unsigned int result = engine_math_not(a);
	lua_pushinteger(L, result);
	return 1;
}

