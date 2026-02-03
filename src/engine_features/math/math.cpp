#include <windows.h>
#include "engine_features/math/math.h"

float engine_math_sin(float angle) {
	return sinf(M_PI * angle / 180.0f);
}

float engine_math_asin(float value) {
	return (180.0f / M_PI) * asinf(value);
}

float engine_math_cos(float angle) {
	return cosf(M_PI * angle / 180.0f);
}

float engine_math_acos(float value) {
	return (180.0f / M_PI) * acosf(value);
}

float engine_math_tan(float angle) {
	return tanf(M_PI * angle / 180.0f);
}

float engine_math_atan(float value) {
	return (180.0f / M_PI) * atanf(value);
}

unsigned int engine_math_or(unsigned int a, unsigned int b) {
	return a | b;
}

unsigned int engine_math_and(unsigned int a, unsigned int b) {
	return a & b;
}

unsigned int engine_math_not(unsigned int a) {
	return ~a;
}

