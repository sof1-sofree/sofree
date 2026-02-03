#include <windows.h>
#include "sofheader.h"
#include "engine_features/sound/sound.h"

extern sound_overrides_t sound_overrides;

void Cmd_CalcFreeSoundSlots(void) {
	int freeslots = engine_sound_calc_free_slots();
	cvar_t* thecvar = findCvar("_sf_sv_sound_info_slots");
	setCvarUnsignedInt(thecvar, freeslots);
}

void sf_sv_sound_register(void) {
	int c = orig_Cmd_Argc() - 1;
	char* one = orig_Cmd_Argv(1);
	if (!strcmp(one, "-h")) {
		orig_Com_Printf(
			"Registers a new soundfile\n"
			"Sound files live in your %%User%%/sound directory\n"
			"See _sf_sv_sound_info_slots for how many sounds slots you have free\n"
			"----------------------------\n"
			"arg1 -> name of soundfile eg. misc/talk.wav\n"
		);
		return;
	}
	if (c != 1) {
		orig_Com_Printf("sf_sv_sound_register -h\n");
		return;
	}
	engine_sound_register(one);
	Cmd_CalcFreeSoundSlots();
}

void sf_sv_sound_remove(void) {
	int c = orig_Cmd_Argc() - 1;
	char* one = orig_Cmd_Argv(1);
	if (!strcmp(one, "-h")) {
		orig_Com_Printf(
			"Unregisters a soundfile that is already registered\n"
			"Sound files live in your %%User%%/sound directory\n"
			"See _sf_sv_sound_info_slots for how many sounds slots you have free\n"
			"----------------------------\n"
			"arg1 -> name of soundfile eg. misc/talk.wav\n"
		);
		return;
	}
	if (c != 1) {
		orig_Com_Printf("sf_sv_sound_remove -h\n");
		return;
	}
	engine_sound_remove(one);
	Cmd_CalcFreeSoundSlots();
}

void sf_sv_sound_list(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Lists all registered sounds\n"
			"See _sf_sv_sound_info_slots for how many sounds slots you have free\n"
			"----------------------------\n"
			"takes optional argument as a search for substring\n"
			"fills _sf_sv_sound_X with the results\n"
		);
		return;
	}
	if (c > 1) {
		orig_Com_Printf("sf_sv_sound_list -h\n");
		return;
	}
	const char* search = (c == 1) ? orig_Cmd_Argv(1) : NULL;
	int results[256 * 65];
	int count = engine_sound_list(search, results, 256);
	for (int i = 0; i < count; i++) {
		const char* line = (const char*)(results + i * 65);
		if (_sf_sv_sofree_debug->value) {
			orig_Com_Printf("%s\n", line);
		}
		char tmpname[64];
		sprintf(tmpname, "%s%i", "_sf_sv_sound_", i + 1);
		cvar_t* savecvar = orig_Cvar_Get(tmpname, "", 0, NULL);
		setCvarString(savecvar, line);
	}
	cvar_t* finalcount = orig_Cvar_Get("_sf_sv_sound_0", "", 0, NULL);
	setCvarInt(finalcount, count);
}

void sf_sv_sound_play_ent(void) {
	int c = orig_Cmd_Argc() - 1;
	char* one = orig_Cmd_Argv(1);
	if (!strcmp(one, "-h")) {
		orig_Com_Printf(
			"Plays a soundfile that has already been registered\n"
			"----------------------------\n"
			"arg1 -> name of soundfile eg. misc/talk.wav\n"
			"arg2 -> ent to attach the sound to\n"
			"arg3 -> channel 0->6 to play the sound on, 0 = auto\n"
			"arg4 -> volume\n"
			"arg5 -> attenuation [0 full volume everywhere, 3-diminish volume rapidly with distance]\n"
			"arg6 -> client_only bool\n"
		);
		return;
	}
	if (c != 6) {
		orig_Com_Printf("sf_sv_sound_play_ent -h\n");
		return;
	}
	edict_t* ent = (edict_t*)atoi(orig_Cmd_Argv(2));
	int chan = atoi(orig_Cmd_Argv(3));
	float volume = atof(orig_Cmd_Argv(4));
	float atten = atof(orig_Cmd_Argv(5));
	int global = atoi(orig_Cmd_Argv(6));
	if (!engine_sound_play_ent(one, ent, chan, volume, atten, global)) {
		orig_Com_Printf("Sound is not registered.\n");
	}
}

void sf_sv_sound_play_origin(void) {
	int c = orig_Cmd_Argc() - 1;
	char* one = orig_Cmd_Argv(1);
	if (!strcmp(one, "-h")) {
		orig_Com_Printf(
			"Plays a soundfile that has already been registered\n"
			"----------------------------\n"
			"arg1 -> name of soundfile eg. misc/talk.wav\n"
			"arg2 -> name of cvar that holds origin vector\n"
			"arg3 -> channel 0->6 to play the sound on, 0 = auto\n"
			"arg4 -> volume\n"
			"arg5 -> attenuation\n"
			"arg6 -> client_only bool\n"
		);
		return;
	}
	if (c != 6) {
		orig_Com_Printf("sf_sv_sound_play_origin -h\n");
		return;
	}
	char* origin = orig_Cmd_Argv(2);
	int chan = atoi(orig_Cmd_Argv(3));
	float volume = atof(orig_Cmd_Argv(4));
	float atten = atof(orig_Cmd_Argv(5));
	int global = atoi(orig_Cmd_Argv(6));
	vec3_t vorigin;
	readCvarAsVector(origin, vorigin);
	if (!engine_sound_play_origin(one, vorigin, chan, volume, atten, global)) {
		orig_Com_Printf("Sound is not registered.\n");
	}
}

void sf_sv_sound_override(void) {
	int c = orig_Cmd_Argc() - 1;
	char* one = orig_Cmd_Argv(1);
	if (!strcmp(one, "-h")) {
		orig_Com_Printf(
			"Plays a specific sound in place of a previous one\n"
			"----------------------------\n"
			"arg1 -> the known original sound - can end with a * to target many sounds\n"
			"arg2 -> your new sound - can be empty then will play no sound\n"
			"arg3 -> altered attenuation value - \"\" empty string does not alter\n"
		);
		return;
	}
	if (c != 3) {
		orig_Com_Printf("sf_sv_sound_override -h\n");
		return;
	}
	const char* origSound = orig_Cmd_Argv(1);
	const char* newSound = orig_Cmd_Argv(2);
	const char* attenStr = orig_Cmd_Argv(3);
	if (!engine_sound_override(origSound, newSound, attenStr)) {
		orig_Com_Printf("This sound is already overriden, sorry\n");
	}
}

