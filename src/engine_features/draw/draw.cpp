#include <windows.h>
#include "sofheader.h"
#include <string.h>
#include <stdlib.h>
#include "engine_features/draw/draw.h"

extern char layoutstring[1024];
extern int layoutstring_len;
extern char sofreebuildstring[128];
extern int sofreebuild_len;

void engine_draw_clear(void) {
	layoutstring_len = 0;
	layoutstring[0] = 0x00;
	sprintf(layoutstring, "xr %i yb -16 altstring \"%s\" ", 0 - (sofreebuild_len * 8 + 8), sofreebuildstring);
}

void engine_draw_string(int offsetx, int offsety, const char* message) {
	int len = strlen(message);
	if (layoutstring_len + len <= 1024) {
		char newstring[256];
		sprintf(newstring, "xv %i yv %i string \"%s\" ", offsetx, offsety, message);
		int newlen = strlen(newstring);
		strcat(layoutstring, newstring);
		layoutstring_len += newlen;
	} else {
		orig_Com_Printf("Cant draw this , run out of space\n");
	}
}

void engine_draw_string2(int offsetx, int offsety, const char* message) {
	int len = strlen(message);
	if (layoutstring_len + len <= 1024) {
		char newstring[256];
		sprintf(newstring, "%s ", message);
		int newlen = strlen(newstring);
		strcat(layoutstring, newstring);
		layoutstring_len += newlen;
	} else {
		orig_Com_Printf("Cant draw this , run out of space\n");
	}
}

void engine_draw_altstring(int offsetx, int offsety, const char* message) {
	int len = strlen(message);
	if (layoutstring_len + len <= 1024) {
		char* msg = (char*)malloc(len + 1);
		strcpy(msg, message);
		for (int i = 0; i < len; i++) {
			*(msg + i) = *(msg + i) | 0x80;
		}
		char newstring[256];
		sprintf(newstring, "xv %i yv %i altstring \"%s\" ", offsetx, offsety, msg);
		int newlen = strlen(newstring);
		strcat(layoutstring, newstring);
		layoutstring_len += newlen;
		free(msg);
	} else {
		orig_Com_Printf("Cant draw this , run out of space\n");
	}
}

