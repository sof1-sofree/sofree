#include <windows.h>
#include "sofheader.h"
#include "engine_features/memory/memory.h"

int engine_mem_read_int(unsigned int offset) {
	if (offset) {
		return stget(offset, 0);
	}
	return 0;
}

unsigned short engine_mem_read_short(unsigned int offset) {
	if (offset) {
		return (unsigned short)stget(offset, 0);
	}
	return 0;
}

unsigned char engine_mem_read_char(unsigned int offset) {
	if (offset) {
		return (unsigned char)stget(offset, 0);
	}
	return 0;
}

float engine_mem_read_float(unsigned int offset) {
	if (offset) {
		return *(float*)(offset);
	}
	return 0.0f;
}

const char* engine_mem_read_string(unsigned int offset) {
	if (offset) {
		return (const char*)(offset);
	}
	return "";
}

void engine_mem_write_int(unsigned int offset, int value) {
	if (offset) {
		*(int*)offset = value;
	}
}

void engine_mem_write_short(unsigned int offset, unsigned short value) {
	if (offset) {
		*(short int*)offset = value & 0xFFFF;
	}
}

void engine_mem_write_char(unsigned int offset, unsigned char value) {
	if (offset) {
		*(char*)offset = value;
	}
}

void engine_mem_write_float(unsigned int offset, float value) {
	if (offset) {
		*(float*)offset = value;
	}
}

void engine_mem_write_string(unsigned int offset, const char* value) {
	if (offset && value) {
		strcpy((char*)offset, value);
	}
}

