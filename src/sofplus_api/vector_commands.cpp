#include <windows.h>
#include "sofheader.h"
#include "engine_features/vector/vector.h"
#include "util_funcs.h"

void sf_sv_vector_set(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Create a vector\n"
			"----------------------------\n"
			"arg1 -> cvarname for output vector\n"
			"arg2 -> first dimension value of vector to set\n"
			"arg3 -> second dimension value of vector to set\n"
			"arg4 -> third dimension value of vector to set\n"
		);
		return;
	}
	if (c != 4) {
		orig_Com_Printf("sf_sv_vector_set -h\n");
		return;
	}
	char* outname = orig_Cmd_Argv(1);
	vec3_t storethis;
	engine_vector_set(storethis, atof(orig_Cmd_Argv(2)), atof(orig_Cmd_Argv(3)), atof(orig_Cmd_Argv(4)));
	writeCvarAsVector(storethis, outname);
}

void sf_sv_vector_copy(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Copy a vector\n"
			"----------------------------\n"
			"arg1 -> cvarname for output vector\n"
			"arg2 -> cvarname vector to copy\n"
		);
		return;
	}
	if (c != 2) {
		orig_Com_Printf("sf_sv_vector_copy -h\n");
		return;
	}
	char* outname = orig_Cmd_Argv(1);
	char* copyname = orig_Cmd_Argv(2);
	vec3_t src, dest;
	readCvarAsVector(copyname, src);
	engine_vector_copy(dest, src);
	writeCvarAsVector(dest, outname);
}

void sf_sv_vector_add(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Add 2 vectors: vectorA + vectorB\n"
			"----------------------------\n"
			"arg1 -> cvarname for output vector\n"
			"arg2 -> cvarname vectorA\n"
			"arg3 -> cvarname vectorB\n"
		);
		return;
	}
	if (c != 3) {
		orig_Com_Printf("sf_sv_vector_add -h\n");
		return;
	}
	char* outname = orig_Cmd_Argv(1);
	char* vec1name = orig_Cmd_Argv(2);
	char* vec2name = orig_Cmd_Argv(3);
	vec3_t vecA, vecB, vecC;
	readCvarAsVector(vec1name, vecA);
	readCvarAsVector(vec2name, vecB);
	engine_vector_add(vecC, vecA, vecB);
	writeCvarAsVector(vecC, outname);
}

void sf_sv_vector_subtract(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Subtract 2 vectors: vectorA - vectorB\n"
			"----------------------------\n"
			"arg1 -> cvarname for output vector\n"
			"arg2 -> cvarname vectorA\n"
			"arg3 -> cvarname vectorB\n"
		);
		return;
	}
	if (c != 3) {
		orig_Com_Printf("sf_sv_vector_subtract -h\n");
		return;
	}
	char* outname = orig_Cmd_Argv(1);
	char* vec1name = orig_Cmd_Argv(2);
	char* vec2name = orig_Cmd_Argv(3);
	vec3_t vecA, vecB, vecC;
	readCvarAsVector(vec1name, vecA);
	readCvarAsVector(vec2name, vecB);
	engine_vector_subtract(vecC, vecA, vecB);
	writeCvarAsVector(vecC, outname);
}

void sf_sv_vector_scale(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Scale a vector by a number\n"
			"----------------------------\n"
			"arg1 -> cvarname for output vector\n"
			"arg2 -> cvarname for input vector\n"
			"arg3 -> scale Factor\n"
		);
		return;
	}
	if (c != 3) {
		orig_Com_Printf("sf_sv_vector_scale -h\n");
		return;
	}
	char* outname = orig_Cmd_Argv(1);
	char* vec1name = orig_Cmd_Argv(2);
	char* scalename = orig_Cmd_Argv(3);
	vec3_t vecA, vecC;
	readCvarAsVector(vec1name, vecA);
	float scale = atof(scalename);
	engine_vector_scale(vecC, vecA, scale);
	writeCvarAsVector(vecC, outname);
}

void sf_sv_vector_normalize(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Normalize a vector\n"
			"Useful for making a vector become a directional vector\n"
			"Compresses values to be between 0.0 and 1.0\n"
			"----------------------------\n"
			"arg1 -> cvarname for output vector\n"
			"arg2 -> cvarname for input Vector\n"
		);
		return;
	}
	if (c != 2) {
		orig_Com_Printf("sf_sv_vector_normalize -h\n");
		return;
	}
	char* outname = orig_Cmd_Argv(1);
	char* vec1name = orig_Cmd_Argv(2);
	vec3_t vecA, outVec;
	readCvarAsVector(vec1name, vecA);
	engine_vector_normalize(outVec, vecA);
	VectorCopy(vecA, outVec);
	writeCvarAsVector(vecA, outname);
}

void sf_sv_vector_length(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Get the length of a vector\n"
			"----------------------------\n"
			"arg1 -> cvarname for output length\n"
			"arg2 -> cvarname for input Vector\n"
		);
		return;
	}
	if (c != 2) {
		orig_Com_Printf("sf_sv_vector_length -h\n");
		return;
	}
	char* outname = orig_Cmd_Argv(1);
	char* vec1name = orig_Cmd_Argv(2);
	vec3_t vecA;
	readCvarAsVector(vec1name, vecA);
	float length = engine_vector_length(vecA);
	setCvarFloat(orig_Cvar_Get(outname, "", 0, NULL), length);
}

void sf_sv_vector_dotproduct(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Calculates the dot product of 2 vectors\n"
			"vectorA . vectorB\n"
			"----------------------------\n"
			"arg1 -> cvarname for output length\n"
			"arg2 -> cvarname for input vectorA\n"
			"arg3 -> cvarname for input vectorB\n"
		);
		return;
	}
	if (c != 3) {
		orig_Com_Printf("sf_sv_vector_dotproduct -h\n");
		return;
	}
	char* outname = orig_Cmd_Argv(1);
	char* vec1name = orig_Cmd_Argv(2);
	char* vec2name = orig_Cmd_Argv(3);
	vec3_t vecA, vecB;
	readCvarAsVector(vec1name, vecA);
	readCvarAsVector(vec2name, vecB);
	float length = engine_vector_dotproduct(vecA, vecB);
	setCvarFloat(orig_Cvar_Get(outname, "", 0, NULL), length);
}

void sf_sv_vector_grow(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Scales a vector with formula\n"
			"newVector = VectorA + Multiplier*VectorB"
			"----------------------------\n"
			"arg1 -> cvarname prefix for resulting cvar\n"
			"arg2 -> VectorA\n"
			"arg3 -> Multiplier\n"
			"arg4 -> VectorB\n"
		);
		return;
	}
	if (c != 4) {
		orig_Com_Printf("sf_sv_vector_grow -h\n");
		return;
	}
	char* out = orig_Cmd_Argv(1);
	char* vectA = orig_Cmd_Argv(2);
	float multiplier = atof(orig_Cmd_Argv(3));
	char* vectB = orig_Cmd_Argv(4);
	vec3_t in_vecA, in_vecB, vout;
	readCvarAsVector(vectA, in_vecA);
	readCvarAsVector(vectB, in_vecB);
	engine_vector_grow(vout, in_vecA, multiplier, in_vecB);
	writeCvarAsVector(vout, out);
}
