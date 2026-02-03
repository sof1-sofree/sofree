#include <windows.h>
#include "sofheader.h"
#include "engine_features/print/print.h"

void engine_print_cprintf(edict_t* ent, const char* text) {
	orig_cprintf(ent, PRINT_HIGH, (char*)text);
}

void engine_print_bprintf(const char* text) {
	orig_bprintf(PRINT_HIGH, (char*)text);
}

void engine_print_centerprint(edict_t* ent, const char* text) {
	orig_centerprintf(ent, (char*)text);
}

void engine_print_welcomeprint(edict_t* ent) {
	orig_welcomeprint(ent);
}

void engine_print_cinprintf(edict_t* ent, int x, int y, int speed, const char* text) {
	orig_cinprintf(ent, x, y, speed, (char*)text);
}

