#include <windows.h>
#include "sofheader.h"
float * level_time = (float*)0x5015CCDC;
float * level_intermissiontime = (float*)0x5015D1C8;
int * level_framenum = (int*)0x5015CCD8;
int * maxclientss = (int*)0x5015D8C8;
void ** g_edictss = (void**)0x5015CCA0;

PickupList * pickList = 0x5015C7B8;

pmove_t ** pm = (pmove_t**)(0x20390290);
float * pml_origin = 0x20390220;
float * pml_previous_origin = 0x2039027C;
float * pml_velocity = 0x2039022C;
float * pml_frametime = 0x2039025C;
float * pml_forward = 0x20390238;
float * pml_right = 0x20390244;
float * pml_up = 0x20390250;
float * pm_duckspeed = 0x201375F8;
float * pm_runspeed = 0x201375F4;
int * pml_ladder = 0x20390288;

float * pm_accelerate = 0x201375FC;

vec3_t vec3_origin = {0,0,0};

struct d_script_s * dende_scripts[MAX_D_SCRIPTS];
int d_script_pointer = 0;
float player_tint[32][4];
float player_wep_tint[32][4];
unsigned int was_ghosted[32];
bool player_collision[32];
bool new_client[32];
short client_gravity[32];

bool disable_attack[32];
bool disable_altattack[32];
bool disable_walk[32];

unsigned int num_sound_overrides = 0;
sound_overrides_t sound_overrides;

unsigned int num_scripts = 0;
script_list_t the_scripts;

event_think_s think_events;
event_touch_s touch_events;
event_use_s use_events;
event_pluse_s pluse_events;
event_pain_s pain_events;
event_die_s die_events;

char layoutstring[1024];
int layoutstring_len = 0;
bool INSIDE_SPACKAGE_PRINT_ID = false;
int next_available_ID = 0;