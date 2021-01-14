/*
 * hook-glx.h
 *
 *  Created on: 31 Jan 2011
 *      Author: graham
 */

/*typedef char bool;
#define false 0x00
#define true 0x01
*/
#pragma once
#include "var_addrs.h"
#include "sof_snd.h"

#define stget(e,x) *(unsigned int*)(e+x)
#define stset(e,x,v) *(unsigned int*)(e+x) = v


#define SV_CONFIGSTRINGS 0x203A2374

#define CLIENT_BASE 0x20396EEC
#define SIZE_OF_CLIENT 0xd2ac
#define CLIENT_USERINFO 0x04
#define CLIENT_ENT 0x298
#define CLIENT_NETMESSAGE 0x52b5
#define CLIENT_NETCHAN 0x526C
#define CLIENT_NETCHAN_IP 0x5284

#define STUFFTEXT 0xD

#define GCLIENT_BASE 0x5015D6C4
#define SIZE_OF_GCLIENT 0x600
#define GCLIENT_PS_BOD 0x7C
#define GCLIENT_TEAM 0x324
#define GCLIENT_INV 0x34C
#define GCLIENT_BODY 0x354
#define GCLIENT_GHOSTED 0x554
#define GCLIENT_PERS_SPECTATOR 0x2DC
#define GCLIENT_PERS_NETNAME 0x2CC
#define GCLIENT_PERS_CONNECTED 0x2F8
#define GCLIENT_RESP_SPECTATOR 0x320
#define GCLIENT_RESP_SCORE 0x308
#define GCLINT_RESP_ENTERFRAME 0x304
#define GCLIENT_PING 0xC8
#define GCLIENT_SHOWSCORES 0x470


#define SIZE_OF_EDICT 0x464
#define EDICT_BASE 0x5015CCA0

#define EDICT_GCLIENT 0x74
#define EDICT_HEALTH 0x2EC
#define EDICT_SOLID 0x158
#define EDICT_CLASSNAME 0x1B4
#define EDICT_TARGETNAME 0x1C8
#define EDICT_SCRIPT 0x454
#define EDICT_S_ORIGIN 0x4
#define EDICT_S_ANGLES 0x10
#define EDICT_INUSE 0x78
#define EDICT_GHOULINST 0x164
#define EDICT_PS_GUN 0x6C
#define EDICT_CLIPMASK 0x15C
#define EDICT_MINS 0x11C
#define EDICT_MAXS 0x128
#define EDICT_MODEL 0x1A4
#define EDICT_S_SKINNUM 0x2C
#define EDICT_ENEMY 0x3240
#define EDICT_CTFFLAGS 0x3CC
#define EDICT_SURFACETYPE 0x3C0
#define EDICT_MATERIAL 0x31C
#define EDICT_TOUCH 0x2C0
#define EDICT_USE 0x2C4
#define EDICT_PLUSE 0x2C8
#define EDICT_PAIN 0x2CC
#define EDICT_DIE 0x2D0
#define EDICT_THINK 0x2B8
#define EDICT_NEXTTHINK 0x2B4
#define EDICT_FLAGS 0x1A0


#define CSCRIPT_SCRIPTCONDITION 0x108

// memory tags to allow dynamic memory to be cleaned up
#define	TAG_TEMP				764			// temporary storage while loading
#define	TAG_GAME				765			// clear when unloading the dll
#define	TAG_LEVEL				766			// clear when loading a new level
#define	TAG_MAP					767			// clear when loading a new level
#define TAG_SOFREE				800




typedef void gclient_t;
typedef void edict_t;
typedef void client_t;
typedef void netchan_t;


typedef enum {
	NOTEAM,
	TEAM_BLUE,
	TEAM_RED
} team_t;


typedef enum
{
SOLID_NOT,			// no interaction with other objects
SOLID_TRIGGER,		// only touch when inside, after moving
SOLID_BBOX,			// touch on edge
SOLID_BSP,			// bsp clip, touch on edge
SOLID_GHOUL,		// use ghoul BoxTrace
SOLID_CORPSE,		// solid type for humanoid corpses only
//
SOLID_NOMATCH = -1	// special value initial ent prev-solid field to ensure non-match, DO NOT USE ELSEWHERE!!!!
} solid_t;

typedef struct modelSpawnData_s
{
	char		*dir;
	char		*file;
	int			surfaceType;
	int			material;
	int			health;
	solid_t		solid;
	char		*materialfile;
	int			debrisCnt;			// Amount of debris to throw
	float		debrisScale;		// Size of debris to throw
	void	*objBreakData;		// Pointer to objBreak array member
} modelSpawnData_t;



typedef enum
{
MOVETYPE_NONE,			// never moves
MOVETYPE_NOCLIP,		// origin and angles change with no interaction
MOVETYPE_PUSH,			// no clip to world, push on box contact
MOVETYPE_STOP,			// no clip to world, stops on box contact
MOVETYPE_WALK,			// gravity
MOVETYPE_STEP,			// gravity, special edge handling
MOVETYPE_FLY,
MOVETYPE_TOSS,			// gravity
MOVETYPE_FLYMISSILE,	// extra size to monsters
MOVETYPE_BOUNCE,
MOVETYPE_DAN,
MOVETYPE_TOUCHNOTSOLID,	// For rockets, uses "Dan" movement, but a SOLID_NOT entity still will use its touch function.
MOVETYPE_SPECTATOR,		// player ONLY - origin and angles change with no interaction except BSP stuff
} movetype_t;



enum ScriptConditionT
{ 
	COND_READY,
	COND_COMPLETED, 
	COND_SUSPENDED, 
	COND_WAIT_ALL, 
	COND_WAIT_ANY,
	COND_WAIT_TIME,
};

typedef enum
{
	SFW_EMPTYSLOT = 0,
	SFW_KNIFE,
	SFW_PISTOL2,
	SFW_PISTOL1,
	SFW_MACHINEPISTOL,
	SFW_ASSAULTRIFLE,
	SFW_SNIPER,
	SFW_AUTOSHOTGUN,
	SFW_SHOTGUN,
	SFW_MACHINEGUN,
	SFW_ROCKET,
	SFW_MICROWAVEPULSE,
	SFW_FLAMEGUN,
	SFW_HURTHAND,
	SFW_THROWHAND,
	SFW_NUM_WEAPONS
} weapons_t;

#define	MAX_STRING_CHARS	1024	// max length of a string passed to Cmd_TokenizeString
#define	MAX_STRING_TOKENS	80		// max tokens resulting from Cmd_TokenizeString
#define	MAX_TOKEN_CHARS		256		// max length of an individual token

#define	MAX_QPATH			64		// max length of a quake game pathname
#define	MAX_OSPATH			128		// max length of a filesystem pathname
#define MAX_PATH			260		// Windows max filename length

#define	MAXLIGHTMAPS		4
//
// per-level limits
//
#define	MAX_CLIENTS			32		// absolute limit
#define	MAX_EDICTS			1024	// must change protocol to increase more
#define	MAX_LIGHTSTYLES		256
#define	MAX_MODELS			256		// these are sent over the net as bytes
#define	MAX_SOUNDS			356		//    (sounds can be sent over as a word index now)
#define MAX_EFPACKS			256		// so they cannot be blindly increased
#define	MAX_IMAGES			256		// 
#define MAX_STRING_PACKAGES	30
#define MAX_PLAYERICONS		16
#define MAX_GHOULFILES		2048	// just to be sure.

#define	CS_NAME				0
#define	CS_CDTRACK			1
#define	CS_SKY				2
#define	CS_SKYAXIS			3		// %f %f %f format
#define	CS_SKYROTATE		4
#define CS_SKYCOLOR			5
#define	CS_MAPCHECKSUM		6		// checksum string

#define CS_CTF_BLUE_STAT	8
#define CS_CTF_RED_STAT		9
#define CS_CTF_BLUE_TEAM   	10
#define CS_CTF_RED_TEAM	   	11
#define CS_AMBSET			12
#define CS_MUSICSET			13
#define CS_TERRAINNAME		14
#define CS_SCREENEFFECT		15
#define CS_DEBRISPRECACHE	16

#define	CS_MAXCLIENTS		31

#define	CS_SHOWNAMES		32
#define	CS_SHOWTEAMS		33
#define	CS_SHOWINFOINDARK	34

#define	CS_MODELS			35

//1497
#define	CS_SOUNDS			(CS_MODELS+MAX_MODELS)
#define CS_EFFECTS			(CS_SOUNDS+MAX_SOUNDS)
#define	CS_IMAGES			(CS_EFFECTS+MAX_EFPACKS)
#define	CS_LIGHTS			(CS_IMAGES+MAX_IMAGES)
#define	CS_PLAYERSKINS		(CS_LIGHTS+MAX_LIGHTSTYLES)
#define	CS_PLAYERICONS		(CS_PLAYERSKINS+MAX_CLIENTS)
#define CS_STRING_PACKAGES	(CS_PLAYERICONS+MAX_PLAYERICONS)
#define CS_WELCOME			(CS_STRING_PACKAGES+MAX_STRING_PACKAGES)
#define CS_GHOULFILES		(CS_WELCOME + 4)
#define CS_CONTROL_FLAGS	(CS_GHOULFILES+MAX_GHOULFILES)
#define	MAX_CONFIGSTRINGS	(CS_CONTROL_FLAGS+10)

//#include "mathlib.h"

typedef int qboolean;
typedef unsigned char byte;
//typedef void modelSpawnData_t;

typedef enum
{
	cs_free,		// can be reused for a new connection
	cs_zombie,		// client has been disconnected, but don't reuse
					// connection for a couple seconds
	cs_connected,	// has been assigned to a client_t, but not in game yet
	cs_spawned		// client is fully in game
} client_state_t;


// Available materials to throw when an object dies.
enum
{
	MAT_NONE = -1,
	MAT_DEFAULT = 0,

	MAT_BRICK_BROWN,
	MAT_BRICK_DBROWN,
	MAT_BRICK_LBROWN,
	MAT_BRICK_LGREY,
	MAT_BRICK_DGREY,
	MAT_BRICK_RED,

	MAT_GLASS,

	MAT_METAL_LGREY,
	MAT_METAL_DGREY,
	MAT_METAL_RUSTY,
	MAT_METAL_SHINY,

	MAT_ROCK_BROWN,
	MAT_ROCK_LBROWN,
	MAT_ROCK_DBROWN,
	MAT_ROCK_LGREY,
	MAT_ROCK_DGREY,

	MAT_WOOD_LBROWN,
	MAT_WOOD_DBROWN,
	MAT_WOOD_DGREY,
	MAT_WOOD_LGREY,

	MAT_WALL_BLACK,
	MAT_WALL_BROWN,
	MAT_WALL_DARKBROWN,
	MAT_WALL_LIGHTBROWN,
	MAT_WALL_GREY,
	MAT_WALL_DARKGREY,
	MAT_WALL_LIGHTGREY,
	MAT_WALL_GREEN,
	MAT_WALL_ORANGE,
	MAT_WALL_RED,
	MAT_WALL_WHITE,
	MAT_ROCK_FLESH,
	MAT_WALL_STRAW,
	MAT_ROCK_SNOW,

	MATERIAL_NUM
};

// Possible marks weapons can make
enum 
{
	DEBRIS_NONE = 0,
	DEBRIS_SM,
	DEBRIS_MED,
	DEBRIS_LRG,
	DEBRIS_TINY,
};


// Possible marks weapons can make
enum 
{
	WMRK_NONE = 0,
	WMRK_BULLETHOLE,
	WMRK_SLASH,
};
// For use on FX_MakeDecalBelow
enum
{
	FXDECAL_BLOODPOOL = 0,
	FXDECAL_SCORCHMARK,
	FXDECAL_OOZE,
	FXDECAL_PIPELEFT,
	FXDECAL_PUDDLE,
	FXDECAL_WHITESCORCH,
	FXDECAL_SINKPIPE,
	FXDECAL_MAX,
};
// If this list is updated, be sure to update bin_nt/sof.mat
enum
{
	SURF_NONE = -1,
	SURF_DEFAULT = 0,
	SURF_METAL_ALSO,					// 2/10/00 kef -- rick wants METAL and METAL_STEAM switched
	SURF_SAND_YELLOW,
	SURF_SAND_WHITE,
	SURF_SAND_LBROWN,
	SURF_SAND_DBROWN,		// 5

	SURF_GRAVEL_GREY,
	SURF_GRAVEL_DBROWN,
	SURF_GRAVEL_LBROWN,

	SURF_SNOW,

	SURF_LIQUID_BLUE,		// 10
	SURF_LIQUID_GREEN,
	SURF_LIQUID_ORANGE,
	SURF_LIQUID_BROWN,

	SURF_WOOD_LBROWN,
	SURF_WOOD_DBROWN,		// 15
	SURF_WOOD_LGREY,

	SURF_STONE_LGREY,			// chunks.tga
	SURF_STONE_DGREY,	// chunksdrkclgry.tga
	SURF_STONE_LBROWN,		// chunksbrwn.tga
	SURF_STONE_DBROWN,		// 20                chunksbrwn.tga
	SURF_STONE_WHITE,		// chunkswht.tga
	SURF_STONE_GREEN,		// chunkgreen.tga
	SURF_STONE_RED,			// chunkred.tga
	SURF_STONE_BLACK,		// chunkblk.tga

	SURF_GRASS_GREEN,		// 25
	SURF_GRASS_BROWN,

	SURF_LIQUID_RED,

	SURF_METAL,							// 2/10/00 kef -- rick wants METAL and METAL_STEAM switched
	SURF_METAL_WATERJET,
	SURF_METAL_OILSPURT,	// 30
	SURF_METAL_CHEMSPURT,
	SURF_METAL_COMPUTERS,

	SURF_SNOW_LBROWN,
	SURF_SNOW_GREY,
	SURF_BLOOD,				// 35
	SURF_LIQUID_BLACK,
	SURF_GLASS,
	SURF_GLASS_COMPUTER,
	SURF_SODAMACHINE,
	SURF_PAPERWALL,			// 40
	SURF_NEWSPAPER_DAMAGE,
	SURF_METAL_STEAM,

	SURF_NUM
};
#define	SURF_LIGHT				0x00000001		// value will hold the light strength
#define	SURF_SLICK				0x00000002		// effects game physics
#define	SURF_SKY				0x00000004		// don't draw, but add to skybox
#define	SURF_WARP				0x00000008		// turbulent water warp
#define	SURF_TRANS33_DEPREC		0x00000010		// Used to clarify view in the editor - not used in game
#define	SURF_TRANS66_DEPREC		0x00000020		// Deprecated - recycle
#define	SURF_FLOWING			0x00000040		// scroll towards angle
#define	SURF_NODRAW				0x00000080		// don't bother referencing the texture
#define	SURF_NO_DETAIL			0x00000400	// face doesn't draw the detail texture normally assigned to it
#define	SURF_ALPHA_TEXTURE		0x00000800		// texture has alpha in it, and should show through in bsp process
#define	SURF_ANIMSPEED			0x00001000		// value will hold the anim speed in fps
#define SURF_UNDULATE			0x00002000		// rock surface up and down...
#define SURF_SKYREFLECT			0x00004000		// liquid will somewhat reflect the sky - not quite finished....
#define SURF_MAP				0x00008000		// used for the auto-map
#define SURF_REGION				0x00010000
#define SURF_SIMPLE_SPHERICAL	0x00020000

#define PACKAGE_DM_GENERIC		0x00

enum
{
	DM_GENERIC_TEXT_DROPPED_WEAPON = 0x0000,
	DM_GENERIC_TEXT_OBT_MOD_WATER = 0x0001,
	DM_GENERIC_TEXT_OBT_MOD_SLIME = 0x0002,
	DM_GENERIC_TEXT_OBT_MOD_CRUSH = 0x0003,
	DM_GENERIC_TEXT_OBT_MOD_FALLING = 0x0004,
	DM_GENERIC_TEXT_OBT_MOD_SUICIDE = 0x0005,
	DM_GENERIC_TEXT_OBT_MOD_EXPLOSIVE = 0x0006,
	DM_GENERIC_TEXT_OBT_MOD_FIRE = 0x0007,
	DM_GENERIC_TEXT_OBT_MOD_LAVA = 0x0008,
	DM_GENERIC_TEXT_OBT_MOD_EXIT = 0x0009,
	DM_GENERIC_TEXT_OBT_MOD_BARBWIRE = 0x000a,
	DM_GENERIC_TEXT_OBT_MOD_DOGBITE = 0x000b,
	DM_GENERIC_TEXT_OBT_MOD_PHOS_GRENADE = 0x000c,
	DM_GENERIC_TEXT_OBT_MOD_ROCKET_SPLASH_F = 0x000d,
	DM_GENERIC_TEXT_OBT_MOD_ROCKET_SPLASH_M = 0x000e,
	DM_GENERIC_TEXT_OBT_MOD_C4_F = 0x000f,
	DM_GENERIC_TEXT_OBT_MOD_C4_M = 0x0010,
	DM_GENERIC_TEXT_OBT_MOD_CLAYMORE = 0x0011,
	DM_GENERIC_TEXT_OBT_MOD_NEURAL_GRENADE_F = 0x0012,
	DM_GENERIC_TEXT_OBT_MOD_NEURAL_GRENADE_M = 0x0013,
	DM_GENERIC_TEXT_OBT_F = 0x0014,
	DM_GENERIC_TEXT_OBT_M = 0x0015,
	DM_GENERIC_TEXT_OBT_MOD_KNIFE_SLASH = 0x0016,
	DM_GENERIC_TEXT_OBT_MOD_KNIFE_THROWN = 0x0017,
	DM_GENERIC_TEXT_OBT_MOD_PISTOL1 = 0x0018,
	DM_GENERIC_TEXT_OBT_MOD_PISTOL2 = 0x0019,
	DM_GENERIC_TEXT_OBT_MOD_MPISTOL = 0x001a,
	DM_GENERIC_TEXT_OBT_MOD_ASSAULTRIFLE = 0x001b,
	DM_GENERIC_TEXT_OBT_MOD_SNIPERRIFLE = 0x001c,
	DM_GENERIC_TEXT_OBT_MOD_AUTOSHOTGUN = 0x001d,
	DM_GENERIC_TEXT_OBT_MOD_SHOTGUN = 0x001e,
	DM_GENERIC_TEXT_OBT_MOD_MACHINEGUN = 0x001f,
	DM_GENERIC_TEXT_OBT_MOD_PHOS_GRENADE_2 = 0x0020,
	DM_GENERIC_TEXT_OBT_MOD_ROCKET = 0x0021,
	DM_GENERIC_TEXT_OBT_MOD_ROCKET_SPLASH = 0x0022,
	DM_GENERIC_TEXT_OBT_MOD_MPG = 0x0023,
	DM_GENERIC_TEXT_OBT_MOD_FLAMEGUN = 0x0024,
	DM_GENERIC_TEXT_OBT_MOD_FLAMEGUN_NAPALM = 0x0025,
	DM_GENERIC_TEXT_OBT_MOD_C4 = 0x0026,
	DM_GENERIC_TEXT_OBT_MOD_CLAYMORE_2 = 0x0027,
	DM_GENERIC_TEXT_OBT_MOD_NEURAL_GRENADE = 0x0028,
	DM_GENERIC_TEXT_OBT_MOD_TELEFRAG = 0x0029,
	DM_GENERIC_TEXT_OBT_DIED = 0x002a,
	DM_GENERIC_LAYOUT_RESET = 0x002b,
	DM_GENERIC_LAYOUT_SCOREBAORD_CLIENT = 0x002c,
	DM_GENERIC_LAYOUT_SCOREBOARD_TEAM = 0x002d,
	DM_GENERIC_TEXT_OBT_MOD_GRENADE_M = 0x002e,
	DM_GENERIC_TEXT_OBT_MOD_GRENADE_F = 0x002f,
	DM_GENERIC_TEXT_OBT_MOD_GRENADE_2 = 0x0030,
	DM_GENERIC_TEXT_SPECTATOR_BAD_PWD = 0x0031,
	DM_GENERIC_TEXT_SPECTATOR_LIMIT_FULL = 0x0032,
	DM_GENERIC_TEXT_BAD_PWD = 0x0033,
	DM_GENERIC_TEXT_SPECTATOR_TO_SIDELINES = 0x0034,
	DM_GENERIC_TEXT_SPECTATOR_TO_GAME = 0x0035,
	DM_GENERIC_TEXT_NO_MORE_CHASE = 0x0036,
	DM_GENERIC_LAYOUT_SCOREBAORD_SPECTATOR = 0x0037,
	DM_GENERIC_TEXT_OBT_MOD_CONC_GRENADE = 0x0038,
	DM_GENERIC_LAYOUT_CTF_CLIENT = 0x0039,
	DM_GENERIC_FRAGS = 0x003a,
	DM_GENERIC_FRAG_LIMIT_HIT = 0x003b,
	DM_GENERIC_TIME_LIMIT_HIT = 0x003c,
	DM_GENERIC_ENTERED = 0x003d,
	DM_GENERIC_TEXT_SCORE = 0x003e,
	DM_GENERIC_TEXT_PING = 0x003f,
	DM_GENERIC_TEXT_TIME = 0x0040,
	DM_GENERIC_TEXT_SPECTATOR = 0x0041,
	DM_GENERIC_TEXT_FLAG_CAPTURES = 0x0042,
	DM_GENERIC_TEXT_CONTROL_POINTS = 0x0043,
	DM_GENERIC_CONTROL_TEAM_RED_SCORE = 0x0044,
	DM_GENERIC_CONTROL_TEAM_BLUE_SCORE = 0x0045,
	DM_GENERIC_CONTROL_TEAM_SCORE = 0x0046
};

// temp entity events
//
// Temp entity events are for things that happen
// at a location seperate from any existing entity.
// Temporary entity messages are explicitly constructed
// and broadcast.
typedef enum
{
	TE_ORANGE_SPARKS,
	TE_DUST_PUFF,
	TE_EXTINGUISHER_EXPLODE,
	TE_BLOODSPRAY,
	TE_BLOODPOOL,
	TE_EXPLODE,
	TE_WALLDAMAGE,
	TE_WALLSEVEREDAMAGE,
	TE_ELECTRIC_ARC,
	TE_WHIZBULLET,
	TE_BLUE_SPARKS,
	TE_WATER_GLOB,
	TE_WATER_SHOCK,
	TE_BARREL_EXPLODE,
	TE_BARREL_SPARKS,
	TE_SCORCHMARK,
	TE_SKY_LIGHTNING,
	TE_OOZE,
	TE_DEBRIS,
	TE_C4EXPLODE,
	TE_FLASHPACK,
	TE_NEURALPULSE,
	TE_AUTOGUNMUZZLEFLASH,
	TE_WALLSTRIKE,
	TE_SHOTGUN,
	TE_UNDERWATER_BULLET,
	TE_SMOKE_BURST,
	TE_TEST_LINE,
	TE_PIPELEFT,
	TE_WHITESCORCH,
	TE_SINKPIPE,
	TE_GUMBALLS,
	TE_WALLSPARKS,
	TE_SHOTGUNMINE,
	TE_SPAS,
	TE_BLOODSQUIRT,
	TE_HELIGUN,
	TE_WHITEBURN,
	TE_WHITEBLAST,
	TE_MINIMISMOKE,
	TE_EXPLOSION,
	TE_BLOODCLOUD,
	TE_HEADEXPLOSION,
	TE_BLOODJET,
	TE_VEHICLEEXPLOSION,
	TE_SMOKE_PUFF,
	TE_LITTLEEXPLOSION,
	TE_MAKERING,
	TE_PAPERCLOUD,
	TE_COINS,
	TE_SODACANS,
	TE_FLOORSPACE,
	TE_DUSTBITS,
	TE_PUDDLE,
	TE_RICOCHET,
	TE_MEDIUMEXPLOSION,
	TE_LARGEEXPLOSION,
	TE_TRACER,
	TE_PHONEHIT,
	TE_TRASHCANHIT,
	TE_DMSHOT,
	TE_DMSHOTHIT,
	TE_DMSHOTBIGHIT,
	TE_DMMUZZLEFLASH,
	TE_TESTBOX,
	TE_NUM
} temp_event_t;

// destination class for gi.multicast()
typedef enum
{
	MULTICAST_ALL,
	MULTICAST_PHS,
	MULTICAST_PVS,
	MULTICAST_ALL_R,
	MULTICAST_PHS_R,
	MULTICAST_PVS_R
} multicast_t;

typedef struct paletteRGB_s
{
	struct
	{
		byte r,g,b;
	};
} paletteRGB_t;

typedef struct paletteRGBA_s
{
	union
	{
		struct
		{
			byte r,g,b,a;
		};
		unsigned c;
		byte c_array[4];
	};
} paletteRGBA_t;

typedef struct cvar_s cvar_t;
typedef void (*cvarcommand_t) (cvar_t *cvar);
typedef struct cvar_s
{
	char			*name;
	char			*string;
	char			*latched_string; // for CVAR_LATCH vars
	int				flags;
	cvarcommand_t	command;
	qboolean		modified; // set each time the cvar is changed
	float			value;
	struct cvar_s *	next;
} cvar_t;


typedef struct sizebuf_s
{
	bool	allowoverflow;
	bool	overflowed;
	byte	*data;
	int		maxsize;
	int		cursize;
	int		readcount;
} sizebuf_t;

#include "../src/Game/player/player.h" // ->ighoul->matrix4,packet->vect3,math,memory,vector,string

// SoF Typedefs:
typedef float vec_t;
typedef vec_t vec3_t[3];
typedef vec_t vec5_t[5];


// SoF Enums:
typedef enum pmtype_s
{
	PM_NORMAL,
	PM_NOCLIP,
	PM_SPECTATOR,
	PM_DEAD,
	PM_GIB,
	PM_FREEZE,
	PM_CAMERA_FREEZE,
	PM_SPECTATOR_FREEZE,
} pmtype_t;

typedef enum
{
	ca_uninitialized,
	ca_disconnected=1,
	ca_connecting=7,
	ca_connected,
	ca_active=8
} connstate_t;


// SoF Definitions:
#define PITCH   0 // up / down
#define YAW     1 // left / right
#define ROLL    2 // fall over

#define	CVAR_ARCHIVE	0x00000001	// set to cause it to be saved to vars.rc
#define	CVAR_USERINFO	0x00000002	// added to userinfo  when changed
#define	CVAR_SERVERINFO	0x00000004	// added to serverinfo when changed
#define	CVAR_NOSET		0x00000008	// don't allow change from console at all,
									// but can be set from the command line
#define	CVAR_LATCH		0x00000010	// save changes until server restart
#define	CVAR_INT		0x00000020	// value is locked to integral
#define CVAR_PLAIN		0x00000040	// can't increment, decrement, or toggle this guy
#define CVAR_INTERNAL	0x00000080	// can only be set internally by the code, never by the user in any way directly

#define CVAR_WEAPON		0x00000100	// this cvar defines possession of a weapon
#define CVAR_ITEM		0x00000200	//  "	  "	   "		  "     "  " item
#define CVAR_AMMO		0x00000400	//  "	  "	   "		  "     "  " quantity of ammo
#define CVAR_MISC		0x00000800
#define CVAR_PARENTAL	0x00001000	// this cvar is stored in the registry through special means

#define P_WHITE		"\001"
#define P_RED  		"\002"
#define P_GREEN		"\003"
#define P_YELLOW	"\004"
#define P_BLUE		"\005"
#define P_PURPLE	"\006"
#define P_CYAN		"\007"
#define P_BLACK		"\010"
#define P_HWHITE  	"\011"
#define P_DONT_USE1	"\012"
#define P_HRED    	"\013"
#define P_HGREEN  	"\014"
#define P_DONT_USE2	"\015"
#define P_HYELLOW	"\016"
#define P_HBLUE		"\017"
#define P_CAMOBROWN	"\020"
#define P_CAMOGREEN	"\021"
#define P_SEAGREEN 	"\022"
#define P_SEABLUE  	"\023"
#define P_METAL    	"\024"
#define P_DBLUE    	"\025"
#define P_DPURPLE  	"\026"
#define P_DGREY    	"\027"
#define P_PINK	  	"\030"
#define P_BLOODRED 	"\031"
#define P_RUSSET   	"\032"
#define P_BROWN    	"\033"
#define P_TEXT     	"\034"
#define P_BAIGE    	"\035"
#define P_LBROWN   	"\036"
#define P_ORANGE   	"\037"

#define	EF_ROTATE			0x00000001		// object (inc. boltons) roates with specifed ang velocities.
#define	EF_ANIM01			0x00000008		// automatically cycle between frames 0 and 1 at 2 hz
#define	EF_ANIM23			0x00000010		// automatically cycle between frames 2 and 3 at 2 hz
#define EF_ANIM_ALL			0x00000020		// automatically cycle through all frames at 2hz
#define EF_ANIM_ALLFAST		0x00000040		// automatically cycle through all frames at 10hz
#define	EF_TELEPORTER		0x00000080		// particle fountain
#define EF_AMB_SOUND_SET	0x00000100		// this object has an ambient sound set attached to it.
#define EF_NO_BULLET		0x00000200		// bmodel leaves no bullet hole
#define EF_EXPLODING		0x00000400		// obj is exploding
#define EF_INVIS_PULSE		0x00000800		// For invulnerability
#define EF_NOTQUAD			0x00001000		// 2 frame buttons rather than the default 4
#define EF_SIMPLEROTATE		0x00002000		// For simple objects that rotate about Z with const. ang. vel.
#define EF_KILL_EFT			0x00004000		// Signal Nathan's effect system to kill all effects on this entity.
#define EF_FADE				0x00008000		// For corpse fading

#define	RF_MINLIGHT			0x00000001		// allways have some light (viewmodel)
#define	RF_VIEWERMODEL		0x00000002		// don't draw through eyes, only mirrors
#define	RF_WEAPONMODEL		0x00000004		// only draw through eyes
#define	RF_FULLBRIGHT		0x00000008		// allways draw full intensity
#define	RF_DEPTHHACK		0x00000010		// for view weapon Z crunching
#define	RF_TRANSLUCENT		0x00000020
#define	RF_FRAMELERP		0x00000040
#define RF_SOUNDONLY		0x00000080		// don't draw this - sent to the client solely for sound purposes
#define	RF_CUSTOMSKIN		0x00000100		// skin is an index in image_precache
#define	RF_GLOW				0x00000200		// pulse lighting for bonus items
#define RF_BMODEL			0x00000400		// Set if this is a bmodel
#define RF_ALPHA_BMODEL		0x00000800		// Set if bmodel has alpha textures
#define RF_GHOUL_SHADOW		0x00001000		// This ghoul model should always have a shadow associated with it
#define RF_GHOUL			0x00400000		// Ghoul model
#define RF_STATICLIT		0x01000000		// world light doesn't need to be re-calced...
#define RF_LIGHTONCE		0x04000000		// New lighting options for speed reasons...
#define RF_NO_DYNA			0x08000000		// ""
#define RF_LIGHT_FASTEST	0x10000000		// ""
#define RF_LIGHT_BEST		0x20000000		// ""
#define RF_LIGHT_FROM_TINT	0x40000000		// ""
#define RF_TRANS_ANY		(RF_TRANSLUCENT | RF_ALPHA_BMODEL)

#define NUM_EFFECTS				4
#define	MAX_STATS 				16
#define MAX_CLIENTWEAPONMODELS	20
#define	MAX_QPATH				64
#define	MAX_MAP_AREAS			256
#define MAX_PARSE_ENTITIES		1024

#ifndef M_PI
#define M_PI				3.14159265358979323846	// matches value in gcc v2 math.h
#endif

#define FLOAT_ZERO_EPSILON	0.0005f
#define DEGTORAD			0.01745329252
#define RADTODEG			57.295779513
#define	ANGLE2SHORT(x)		((int)((x) * 65536 / 360) & 65535)
#define	SHORT2ANGLE(x)		((x) * (360.0 / 65536))



// SoF Structs:



typedef struct pmove_state_s
{
	pmtype_t	pm_type;

	short		origin[3];
	short		velocity[3];
	byte		pm_flags;
	byte		pm_time;
	short		gravity;
	short		delta_angles[3];
	byte		moveScale;
} pmove_state_t; // dunno, compile wax hax wihthout the code tomorrow, im gonna sleep, send me the code via email please, ok , i will be online tomorrow ok

typedef struct player_state_s
{
	pmove_state_t	pmove;

	vec3_t		viewangles;
	vec3_t		viewoffset;
	vec3_t		kick_angles;
	vec3_t		weaponkick_angles;

	vec3_t		remote_vieworigin,
				remote_viewangles;
	int			remote_id;
	byte		remote_type;

	IGhoulInst	*gun;
	short		gunUUID;
	short		gunType;
	short		gunClip;
	short		gunAmmo;
	byte		gunReload;
	byte		restart_count;
	byte		buttons_inhibit;

	IGhoulInst	*bod;
	short		bodUUID;

	float		blend[4];
	float		fov;
	int			rdflags;

	short		soundID;
	byte		musicID;

	short		damageLoc;
	short		damageDir;
	short		stats[MAX_STATS];
	byte		dmRank;
	byte		dmRankedPlyrs;
	byte		spectatorId;

	byte		cinematicfreeze;
} player_state_t; // this is different

/*
typedef struct
{
	pmove_state_t	pmove;		// for prediction

	// these fields do not need to be communicated bit-precise

	vec3_t		viewangles;		// for fixed views
	vec3_t		viewoffset;		// add to pmovestate->origin
	vec3_t		kick_angles;	// add to view direction to get render angles
								// set by weapon kicks, pain effects, etc

	vec3_t		gunangles;
	vec3_t		gunoffset;
	int			gunindex;
	int			gunframe;

	float		blend[4];		// rgba full screen effect

	float		fov;			// horizontal field of view

	int			rdflags;		// refdef flags

	short		stats[MAX_STATS];		// fast status bar updates
} player_state_t; // yes ok try with this one
*/
typedef struct frame_s
{
	bool				valid;
	int				serverframe;
	int				servertime;
	int				deltaframe;
	byte			areabits[MAX_MAP_AREAS/8];
	player_state_t	playerstate;
	int				num_entities;
	int				parse_entities;
} frame_t;


typedef struct
{
	char name[64];
	char teamname[64]; //140 256 + 64 = 320
	char skin[64]; // 192
	char portrait[64]; // 256
	char portrait2[64]; // 320
	vec3_t some_origin;
	char team[1];
	//char unknown2[15];
	vec3_t origin;
} clientinfo_t;

typedef struct aEffectInfo_s
{
	short	effectId;
	short	bolt;
	short	size;
}aEffectInfo_t;

typedef struct entity_state_s
{
	int			number;	//4

	vec3_t		origin;
	vec3_t		angles;
	vec_t		angle_diff; //32
	int			modelindex; //36
	int			renderindex; // 40
	int			frame; // 44
	int			skinnum; //48
	int			effects; // 52
	int			renderfx; //56
	int			solid; //60
	int			sound; //64
	int			sound_data;//68
	int			event;
	int			event2;
	int			event3;
	int			data;
	int			data2;
	int			data3;

	aEffectInfo_t	effectData[NUM_EFFECTS];
} entity_state_t;



typedef struct
{
	entity_state_t	baseline;
	entity_state_t	current;
	entity_state_t	prev;

	int			serverframe;

	int			trailcount;
	vec3_t		lerp_origin;

	int			fly_stoptime;
} centity_t;

typedef struct entity_s
{
	int	*model;
	float	angles[3];	
	float	origin[3];
	int		frame;

	float	oldorigin[3];
	int		oldframe;

	float	backlerp;
	int		skinnum;

	int		lightstyle;
	float	alpha;

	int	*skin;
	int		flags;
	int dontknow1;
	int dontknow2;
	int dontknow3;
} entity_t; // should be 0xDC big - 220

typedef enum
{
	it_skin,
	it_sprite,
	it_wall,
	it_pic,
	it_sky
} imagetype_t; //f7lol :D


typedef struct image_s
{
	char	name[MAX_QPATH];			// game path, including extension
	imagetype_t	type;
	int		width, height;				// source image
	int		upload_width, upload_height;	// after power of two and picmip
	int		registration_sequence;		// 0 = free
	struct msurface_s	*texturechain;	// for sort-by-texture world drawing
	int		texnum;						// gl texture binding
	float	sl, tl, sh, th;				// 0,0 - 1,1 unless part of the scrap
	qboolean	scrap;
	qboolean	has_alpha;

	qboolean paletted;
} image_t; // f7

typedef struct cplane_s
{
	vec3_t	normal;
	float	dist;
	byte	type;			// for fast side tests
	byte	signbits;		// signx + (signy<<1) + (signz<<1)
} cplane_t;

typedef struct mtexinfo_s
{
	float		vecs[2][4];
	int			flags;
	int			numframes;
	struct mtexinfo_s	*next;		// animation chain
	image_t		*image;
} mtexinfo_t; // lol :D it goes on for a while ^^^^ ye

typedef struct
{
	bool				allsolid;	// if true, plane is not valid
	bool				startsolid;	// if true, the initial point was in a solid area
	float				fraction;	// time completed, 1.0 = didn't hit anything
	vec3_t				endpos;		// final position
	cplane_t			plane;		// surface normal at impact
	struct mtexinfo_s	*surface;	// surface hit
	int					contents;	// contents on other side of surface hit
	struct edict_s		*ent;		// not set by CM_*() functions
	int					leaf_num;	// leaf the hit took place in
} trace_t;

typedef struct
{
	int			down[2];
	unsigned int downtime;
	unsigned int msec;
	int			state;
} kbutton_t; // i forgot how to do that? , we need the address of the attack state structure r? i sent you the address ah

#define	BUTTON_ATTACK		1
#define	BUTTON_USE			2
#define BUTTON_ALTATTACK	4
#define BUTTON_WEAP3		8
#define BUTTON_WEAP4		16
#define BUTTON_RUN			32
#define BUTTON_ACTION		64
#define	BUTTON_ANY			128			// any key whatsoever

#define MAX_TARGETS 33

#define	CONTENTS_SOLID			1		// an eye is never valid in a solid
#define	CONTENTS_WINDOW			2		// translucent, but not watery
#define	CONTENTS_AUX			4
#define	CONTENTS_LAVA			8
#define	CONTENTS_SLIME			16
#define	CONTENTS_WATER			32
#define	CONTENTS_MIST			64
#define	LAST_VISIBLE_CONTENTS	64

// remaining contents are non-visible, and don't eat brushes

#define	CONTENTS_AREAPORTAL		0x8000

#define	CONTENTS_PLAYERCLIP		0x10000
#define	CONTENTS_MONSTERCLIP	0x20000

// currents can be added to any other contents, and may be mixed
#define	CONTENTS_CURRENT_0		0x40000
#define	CONTENTS_CURRENT_90		0x80000
#define	CONTENTS_CURRENT_180	0x100000
#define	CONTENTS_CURRENT_270	0x200000
#define	CONTENTS_CURRENT_UP		0x400000
#define	CONTENTS_CURRENT_DOWN	0x800000

#define	CONTENTS_ORIGIN			0x1000000	// removed before bsping an entity

#define	CONTENTS_MONSTER		0x2000000	// should never be on a brush, only in game
#define	CONTENTS_DEADMONSTER	0x4000000
#define	CONTENTS_DETAIL			0x8000000	// brushes to be added after vis leafs
#define	CONTENTS_TRANSLUCENT	0x10000000	// auto set if any surface has trans
#define	CONTENTS_LADDER			0x20000000
#define	LAST_VISIBLE_CONTENTS	64
#define	CONTENTS_AREAPORTAL		0x8000
#define	CONTENTS_PLAYERCLIP		0x10000
#define	CONTENTS_MONSTERCLIP	0x20000

#define	MASK_ALL				(-1)
#define	MASK_SOLID				(CONTENTS_SOLID|CONTENTS_WINDOW)
#define	MASK_PLAYERSOLID		(CONTENTS_SOLID|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER)
#define	MASK_DEADSOLID			(CONTENTS_SOLID|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW)
#define	MASK_MONSTERSOLID		(CONTENTS_SOLID|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER)
#define	MASK_WATER				(CONTENTS_WATER|CONTENTS_LAVA|CONTENTS_SLIME)
#define	MASK_OPAQUE				(CONTENTS_SOLID|CONTENTS_SLIME|CONTENTS_LAVA)
#define	MASK_SHOT				(CONTENTS_SOLID|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEADMONSTER)
#define MASK_CURRENT			(CONTENTS_CURRENT_0|CONTENTS_CURRENT_90|CONTENTS_CURRENT_180|CONTENTS_CURRENT_270|CONTENTS_CURRENT_UP|CONTENTS_CURRENT_DOWN


//
// server to client
//
enum svc_ops_e
{
	svc_bad,

	// these ops are known to the game dll
	svc_temp_entity,
	svc_layout,
	svc_UNUSED,
	svc_sound_info,
	svc_effect,
	svc_equip,					// buying, equipping items messages

	// the rest are private to the client and server
	svc_nop,
	svc_disconnect,
	svc_reconnect,
	svc_sound,					// <see code>
	svc_print,					// [byte] id [string] null terminated string
	svc_nameprint,				// [byte] client num, [byte] team num, [string] null terminated string
	svc_stufftext,				// [string] stuffed into client's console buffer, should be \n terminated
	svc_serverdata,				// [long] protocol ...
	svc_configstring,			// [short] [string]
	svc_spawnbaseline,
	svc_centerprint,			// [string] to put in center of the screen
	svc_captionprint,			// line number of [string] in strings.txt file -- ACTUALLY, JUST THE STRING
	svc_download,				// [short] size [size bytes]
	svc_playerinfo,				// variable
	svc_packetentities,			// [...]
	svc_deltapacketentities,	// [...]
	svc_frame,
	svc_culledEvent,
	svc_damagetexture,			// [short] surface index [byte] level
	svc_ghoulreliable,			// [short] size [size bytes]
	svc_ghoulunreliable,		// [short] size [size bytes]
	svc_ric,					// [byte] num of RICs [...] the actual RICs
	svc_restart_predn,			// [byte] restarts prediction
	svc_rebuild_pred_inv,		// [byte] [inven_c] syncs client inven to server one
	svc_countdown,				// [byte] time to countdown
	svc_cinprint,				//
	svc_playernamecols,			// [byte] num of bytes [string] array of (client,color) pairs
	svc_sp_print,				// [short] string index [color]
	svc_removeconfigstring,		// [short]
	svc_sp_print_data_1,		// [short] string index [byte] count of data bytes [data bytes] [color]
	svc_sp_print_data_2,		// [short] string index [short] count of data bytes [data bytes] [color]
	svc_welcomeprint,			// sent down so welcome message is displayed at entry to a deathmatch server
	svc_sp_print_obit,			// send down the obituaries. Same format as svc_sp_print_data_1, but needs to be different packet type for client filter
	svc_force_con_notify,		// force a console clear - required for CTF when the game is over
};


//==============================================

//
// client to server
//
enum clc_ops_e
{
	clc_bad,
	clc_nop,
	clc_move,				// [[usercmd_t]
	clc_userinfo,			// [[userinfo string]
	clc_stringcmd,			// [string] message
};

typedef struct
{
	void (*afunction1)(void);
	void (*afunction2)(void);
	void (*afunction3)(void);
	void (*afunction4)(void);
	void (*afunction5)(void);
	void (*afunction6)(void);
	void (*afunction7)(void);
	void (*afunction8)(void);
	void (*afunction9)(void);
	void (*afunctiona)(void);
	void (*afunctionb)(void);
	void (*afunctionc)(void);
	void (*afunctiond)(void);
	void (*afunctione)(void);
	void (*afunctionf)(void);
	void (*afunctiong)(void);
	void (*afunctionh)(void);
	void (*afunctioni)(void);
	void (*afunctionj)(void);
	void (*afunctionk)(void);
	void (*afunctionl)(void);
	void (*afunctionm)(void);
	void (*afunctionn)(void);
	void (*afunctiono)(void);
	void (*afunctionp)(void);
	void (*afunctionq)(void);
	void (*afunctionq1)(void);
	void (*afunctionq2)(void);
	void (*afunctionq3)(void);
	void (*afunctionq4)(void);
	void (*afunctionq5)(void);
	void (*afunctionq6)(void);
	void (*afunctionq7)(void);
	void (*afunctionq8)(void);
	void (*afunctionq9)(void);
	void (*afunctionq10)(void);
	void (*afunctionqa)(void);
	void (*afunctionqb)(void);
	void (*afunctionqc)(void);

}refimport_t;
typedef struct
{
	void (*afunction1)(void);
	void (*afunction2)(void);
	void (*afunction3)(void);
	void (*afunction4)(void);
	void (*afunction5)(void);
	void (*afunction6)(void);
	void (*afunction7)(void);
	void (*afunction8)(void);
	void (*afunction9)(void);
	void (*afunctiona)(void);
	void (*afunctionb)(void);
	void (*afunctionc)(void);
	void (*afunctiond)(void);
	void (*afunctione)(void);
	void (*afunctionf)(void);
	void (*afunctiong)(void);
	void (*afunctionh)(void);
	void (*afunctioni)(void);
	void (*afunctionj)(void);
	void (*afunctionk)(void);
	void (*afunctionl)(void);
	void (*afunctionm)(void);
	void (*afunctionn)(void);
	void (*afunctiono)(void);
	void (*afunctionp)(void);
	void (*afunctionq)(void);
	void (*afunctionq1)(void);
	void (*afunctionq2)(void);
	void (*afunctionq3)(void);
	void (*afunctionq4)(void);
	void (*afunctionq5)(void);
	void (*afunctionq6)(void);
	void (*afunctionq7)(void);
	void (*afunctionq8)(void);
	void (*afunctionq9)(void);
	void (*afunctionq10)(void);
	void (*afunctionqa)(void);
	void (*afunctionqb)(void);
	void (*afunctionqc)(void);
}refexport_t;

// usercmd_t is sent to the server each client frame
typedef struct usercmd_s
{
	byte	msec;
	byte	buttons;
	byte	lightlevel;		// light level the player is standing on
	char	lean;			// -1 or 1
	short	angles[3];
	short	forwardmove;
	short	sidemove;
	short	upmove;
	float	fireEvent;
	float	altfireEvent;
} usercmd_t;

#include "cvars.h"
#include "commands.h"
#include "func_defs.h"
#include "sp_detours.h"
#include "util_funcs.h"
#include "client_begin.h"
#include "server_begin.h"
#include "scoreboard.h"
#include "deathmatch.h"
#include "vaccine.h"


