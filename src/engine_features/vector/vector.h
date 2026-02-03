#pragma once
#include "sofheader.h"

void engine_vector_set(vec3_t out, float x, float y, float z);
void engine_vector_copy(vec3_t out, vec3_t in);
void engine_vector_add(vec3_t out, vec3_t a, vec3_t b);
void engine_vector_subtract(vec3_t out, vec3_t a, vec3_t b);
void engine_vector_scale(vec3_t out, vec3_t in, float scale);
void engine_vector_normalize(vec3_t out, vec3_t in);
float engine_vector_length(vec3_t v);
float engine_vector_dotproduct(vec3_t a, vec3_t b);
void engine_vector_grow(vec3_t out, vec3_t a, float multiplier, vec3_t b);

