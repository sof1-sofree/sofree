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