#include <windows.h>
#include "sofheader.h"
#include "lua_api/generic.h"
#include "engine_features/memory/memory.h"

int sf_sv_mem_read_int(lua_State* L) {
	unsigned int offset = lua_tointeger(L, 1);
	int value = engine_mem_read_int(offset);
	lua_pushinteger(L, value);
	return 1;
}

int sf_sv_mem_read_short(lua_State* L) {
	unsigned int offset = lua_tointeger(L, 1);
	unsigned short value = engine_mem_read_short(offset);
	lua_pushinteger(L, value);
	return 1;
}

int sf_sv_mem_read_char(lua_State* L) {
	unsigned int offset = lua_tointeger(L, 1);
	unsigned char value = engine_mem_read_char(offset);
	lua_pushinteger(L, value);
	return 1;
}

int sf_sv_mem_read_float(lua_State* L) {
	unsigned int offset = lua_tointeger(L, 1);
	float value = engine_mem_read_float(offset);
	lua_pushnumber(L, value);
	return 1;
}

int sf_sv_mem_read_string(lua_State* L) {
	unsigned int offset = lua_tointeger(L, 1);
	const char* value = engine_mem_read_string(offset);
	lua_pushstring(L, value);
	return 1;
}

int sf_sv_mem_write_int(lua_State* L) {
	unsigned int offset = lua_tointeger(L, 1);
	int value = lua_tointeger(L, 2);
	engine_mem_write_int(offset, value);
	return 0;
}

int sf_sv_mem_write_short(lua_State* L) {
	unsigned int offset = lua_tointeger(L, 1);
	unsigned short value = lua_tointeger(L, 2);
	engine_mem_write_short(offset, value);
	return 0;
}

int sf_sv_mem_write_char(lua_State* L) {
	unsigned int offset = lua_tointeger(L, 1);
	unsigned char value = lua_tointeger(L, 2);
	engine_mem_write_char(offset, value);
	return 0;
}

int sf_sv_mem_write_float(lua_State* L) {
	unsigned int offset = lua_tointeger(L, 1);
	float value = lua_tonumber(L, 2);
	engine_mem_write_float(offset, value);
	return 0;
}

int sf_sv_mem_write_string(lua_State* L) {
	unsigned int offset = lua_tointeger(L, 1);
	const char* value = lua_tostring(L, 2);
	engine_mem_write_string(offset, value);
	return 0;
}

