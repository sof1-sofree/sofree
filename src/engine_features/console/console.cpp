#include <windows.h>
#include "sofheader.h"
#include "engine_features/console/console.h"

void engine_console_write(const char* text) {
	orig_Com_Printf("%s", text);
}

void engine_configstring_set(int index, const char* string) {
	orig_PF_Configstring(index, (char*)string);
}

