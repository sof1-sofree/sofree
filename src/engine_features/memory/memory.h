#pragma once
#include "sofheader.h"

int engine_mem_read_int(unsigned int offset);
unsigned short engine_mem_read_short(unsigned int offset);
unsigned char engine_mem_read_char(unsigned int offset);
float engine_mem_read_float(unsigned int offset);
const char* engine_mem_read_string(unsigned int offset);
void engine_mem_write_int(unsigned int offset, int value);
void engine_mem_write_short(unsigned int offset, unsigned short value);
void engine_mem_write_char(unsigned int offset, unsigned char value);
void engine_mem_write_float(unsigned int offset, float value);
void engine_mem_write_string(unsigned int offset, const char* value);

