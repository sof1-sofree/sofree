#include <windows.h>
#include "sofheader.h"
#include "lua_api/generic.h"
#include "engine_features/vector/vector.h"
#include "util_funcs.h"

int sf_sv_vector_create(lua_State* L) {
	float x = lua_tonumber(L, 1);
	float y = lua_tonumber(L, 2);
	float z = lua_tonumber(L, 3);
	vec3_t outVec;
	engine_vector_set(outVec, x, y, z);
	luaPushVectorAsTable(outVec);
	return 1;
}

int sf_sv_vector_copy(lua_State* L) {
	vec3_t src;
	luaReadTableAsVector(1, src);
	vec3_t dest;
	engine_vector_copy(dest, src);
	luaPushVectorAsTable(dest);
	return 1;
}

int sf_sv_vector_add(lua_State* L) {
	vec3_t vecA, vecB, outVec;
	luaReadTableAsVector(1, vecA);
	luaReadTableAsVector(2, vecB);
	engine_vector_add(outVec, vecA, vecB);
	luaPushVectorAsTable(outVec);
	return 1;
}

int sf_sv_vector_subtract(lua_State* L) {
	vec3_t vecA, vecB, outVec;
	luaReadTableAsVector(1, vecA);
	luaReadTableAsVector(2, vecB);
	engine_vector_subtract(outVec, vecA, vecB);
	luaPushVectorAsTable(outVec);
	return 1;
}

int sf_sv_vector_scale(lua_State* L) {
	vec3_t inVec, outVec;
	luaReadTableAsVector(1, inVec);
	float scale = lua_tonumber(L, 2);
	engine_vector_scale(outVec, inVec, scale);
	luaPushVectorAsTable(outVec);
	return 1;
}

int sf_sv_vector_normalize(lua_State* L) {
	vec3_t inVec, outVec;
	luaReadTableAsVector(1, inVec);
	engine_vector_normalize(outVec, inVec);
	luaPushVectorAsTable(outVec);
	return 1;
}

int sf_sv_vector_length(lua_State* L) {
	vec3_t inVec;
	luaReadTableAsVector(1, inVec);
	float length = engine_vector_length(inVec);
	lua_pushnumber(L, length);
	return 1;
}

int sf_sv_vector_dotproduct(lua_State* L) {
	vec3_t vecA, vecB;
	luaReadTableAsVector(1, vecA);
	luaReadTableAsVector(2, vecB);
	float dot = engine_vector_dotproduct(vecA, vecB);
	lua_pushnumber(L, dot);
	return 1;
}

int sf_sv_vector_grow(lua_State* L) {
	vec3_t vecA, vecB, outVec;
	luaReadTableAsVector(1, vecA);
	float multiplier = lua_tonumber(L, 2);
	luaReadTableAsVector(3, vecB);
	engine_vector_grow(outVec, vecA, multiplier, vecB);
	luaPushVectorAsTable(outVec);
	return 1;
}
