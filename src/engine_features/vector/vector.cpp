#include <windows.h>
#include "sofheader.h"
#include "engine_features/vector/vector.h"

void engine_vector_set(vec3_t out, float x, float y, float z) {
	out[0] = x;
	out[1] = y;
	out[2] = z;
}

void engine_vector_copy(vec3_t out, vec3_t in) {
	VectorCopy(in, out);
}

void engine_vector_add(vec3_t out, vec3_t a, vec3_t b) {
	VectorAdd(a, b, out);
}

void engine_vector_subtract(vec3_t out, vec3_t a, vec3_t b) {
	VectorSubtract(a, b, out);
}

void engine_vector_scale(vec3_t out, vec3_t in, float scale) {
	VectorScale(in, scale, out);
}

void engine_vector_normalize(vec3_t out, vec3_t in) {
	VectorCopy(in, out);
	VectorNormalize(out);
}

float engine_vector_length(vec3_t v) {
	return VectorLength(v);
}

float engine_vector_dotproduct(vec3_t a, vec3_t b) {
	return DotProduct(a, b);
}

void engine_vector_grow(vec3_t out, vec3_t a, float multiplier, vec3_t b) {
	VectorMA(a, multiplier, b, out);
}

