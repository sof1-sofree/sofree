#include <windows.h>
#include "sofheader.h"
#include <stdlib.h>
#include <string.h>
#include "engine_features/script/script.h"

extern script_list_t the_scripts;
extern int last_created_cscript;

edict_t* engine_script_load(const char* scriptName, const char** params, int paramCount) {
	script_list_t* z = (script_list_t*)malloc(sizeof(script_list_t));
	z->next = the_scripts.next;
	z->prev = &the_scripts;
	the_scripts.next->prev = z;
	the_scripts.next = z;
	char* blehparms[16] = { 0 };
	for (int i = 0; i < paramCount && i < 16; i++) {
		int len = strlen(params[i]) + 1;
		char* lul = (char*)malloc(len);
		strncpy(lul, params[i], len);
		lul[len - 1] = 0x00;
		*(unsigned int*)(0x5015CC34 + 4 * i) = (unsigned int)lul;
		blehparms[i] = lul;
	}
	strcpy(z->script_name, scriptName);
	edict_t* newrunner = orig_G_Spawn();
	newrunner->classname = "script_runner";
	*(unsigned int*)0x5015CC30 = (unsigned int)&z->script_name;
	orig_SP_script_runner(newrunner);
	z->cscript = last_created_cscript;
	for (int j = 0; j < 16; j++) {
		if (blehparms[j])
			free(blehparms[j]);
	}
	z->next = NULL;
	z->runner = newrunner;
	return newrunner;
}

void engine_script_unload(edict_t* runner) {
	if (!runner || !runner->inuse) return;
	script_list_t* z, * next;
	for (z = the_scripts.next; z != &the_scripts; z = next) {
		next = z->next;
		if (z->runner == runner) {
			z->prev->next = z->next;
			z->next->prev = z->prev;
			stset(z->cscript, CSCRIPT_SCRIPTCONDITION, COND_COMPLETED);
			orig_G_FreeEdict(z->runner);
			free(z);
			break;
		}
	}
}

void engine_script_run(edict_t* runner) {
	if (!runner || !runner->inuse) return;
	orig_script_use(runner, runner, runner);
}

