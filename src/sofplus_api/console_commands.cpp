#include <windows.h>
#include "sofheader.h"
#include "engine_features/console/console.h"

void sf_sv_configstring_set(void) {
	int index = atoi(orig_Cmd_Argv(1));
	engine_configstring_set(index, orig_Cmd_Argv(2));
}

