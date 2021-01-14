#include "ighoul.h"

typedef struct sharedEdict_s
{
	void *inv; // voided these temporarily
	void *edict; // voided these temporarily
	int		attack;
	int		altattack;
	int		weap3;
	int		weap4;
	int		leanLeft;
	int		leanRight;
	int		cinematicFreeze;
	int		rejectSniper;
	float	*weaponkick_angles;	// Really, a vec3_t.
	float	framescale;
	int		doReload;
} sharedEdict_t;




// Glurk - do something about this mess - it's vile -MW.
class IGhoulObj;
typedef unsigned short int GhoulID;


/*
==============================================================

GHOUL FILESYSTEM STUFF

==============================================================
*/

int FindGSQFile(char *gsqdir, char *gsqfile, void **buffer);
bool ReadGsqEntry(int &filesize, char **tdata, char *seqname);
void	PrecacheGSQFile(char *dirname, char *gsq_file, IGhoulObj *object);
int  RegisterGSQSequences(char *gsqdir, char *subclass, IGhoulObj *object);
void TurnOffPartsFromGSQFile(char *dirname, char *poff_file, IGhoulObj *this_object, IGhoulInst *this_inst);



#define MAX_TEAMNAME_LENGTH			50
#define	MAX_MATERIALNAME_LENGTH		50
#define	MAX_SKINNAME_LENGTH			100
#define	MAX_PARTNAME_LENGTH			50
#define	MAX_MODELINFONAME_LENGTH	100
#define	MAX_GHBNAME_LENGTH			100
#define	MAX_GSQNAME_LENGTH			100
#define	MAX_FACESETNAME_LENGTH		50
#define	MAX_DIRECTORYNAME_LENGTH	100
#define MAX_MENUSTRING_LENGTH		200

//public player-model textfile stuff (sorry, i didn't want to make a GPMFile_public.h):
class TeamInfoC
{
public:
	char name[MAX_TEAMNAME_LENGTH];
};

//i'm not sure how this is going to be handled--a directory should be enough, but in case there's more i'm separating it out now.
class VoiceInfoC
{
public:
	char voiceDir[MAX_DIRECTORYNAME_LENGTH];//injury & death directory
};

class SkinInfoC
{
public:
	char matName[MAX_MATERIALNAME_LENGTH];
	char skinName[MAX_SKINNAME_LENGTH];
	char partName[MAX_PARTNAME_LENGTH];//this may have to be taken out because it could blow texture memory through the ceiling, but it's just too cool for me to leave it off to begin with. i'll demonstrate shortly.
};

//some of the player types require twiddling with a part or two beyond what the typical guy of the same general type would have on/off (e.g. mohawks)
class ExtraPartToggleInfoC
{
public:
	char partName[MAX_PARTNAME_LENGTH];
	bool partState;//true=on;false=off
};

class BoltOnInfoC
{
public:
	float scale;
	char parentBolt[MAX_PARTNAME_LENGTH];//bolts are parts
	char childBolt[MAX_PARTNAME_LENGTH];//bolts are parts
	char childModelInfo[MAX_MODELINFONAME_LENGTH];//this should be the name of a modelinfo file. maybe .gbm instead of .gpm?
};

//Don't ever new one of these!  This is just the interface class to let you call the functions that are available in the class that's really returned by NewPlayerModelInfo.
class IPlayerModelInfoC
{
public:
	//will load the player description textfile, and set all info according to that.  called by constructor, but should be able to recall for a new model.
	virtual	void	Init(char *newFileName){}

	// Returns and sets the object associated with this model
	virtual IGhoulObj	*GetObject(void) const { return(NULL); }
	virtual void		SetObject(IGhoulObj *obj) { }

	//the number of skins that need to be set for this guy
	virtual	int		GetNumSkins(void){return 0;}
	//the number of bolt-ons available for this guy
	virtual	int		GetNumBoltOns(void){return 0;}
	//the number of extra twiddles to part on/off state that need to be done for this guy
	virtual int		GetNumPartToggles(void){return 0;}

	//the ghb's and the gsq's should be in this directory--this is mostly to be game_ghoul-friendly
	virtual	char	*GetGHBDir(void){return "";}
	//this is the ghb the menu can use (if we can get the menu using the game ghb, this is meaningless)
	virtual	char	*GetMenuGHB(void){return "";}
	//this is the ghb the game needs to load (the menu might be able to use it too, but we'll not hold our breath on that)
	virtual	char	*GetGameGHB(void){return "";}

	//this is the gsq file listing the sequences to register--use this to get the _poff .gsq too(game ghb only)
	virtual	char	*GetSeqGSQ(void){return "";}
	//this is the face base, to be used by the body for changing expressions
	virtual	char	*GetFaceSet(void){return "";}

	//these guys return true if they filled the class passed in, false if they failed for some reason
	virtual	bool	GetTheMenuString(char *putstringhere){return false;}
	virtual	bool	GetTeamInfo(TeamInfoC &putteamhere){return false;}
	virtual	bool	GetVoiceInfo(VoiceInfoC &putvoiceinfohere){return false;}
	virtual	bool	GetSkin(int skinnum, SkinInfoC &putskinhere){return false;}
	virtual	bool	GetBoltOn(int boltonnum, BoltOnInfoC &putboltonhere){return false;}
	virtual	bool	GetPartToggle(int togglenum, ExtraPartToggleInfoC &puttogglehere){return false;}

	virtual	bool	IsLoaded(void){return false;}

	virtual	~IPlayerModelInfoC(){}
};


	//if you pass in a NULL pointer to this, it won't set anything up (no file-loading, nothing)
	//so if you want to create one of these guys but don't know the file yet, pass in NULL, don't pass in trash

//urh! you need to delete this when you're done with it!
IPlayerModelInfoC *NewPlayerModelInfo(char *modelname);



//
// These are the functions imported by the player dll module when it is called
// from the client or server.
//

typedef struct
{ 
	// Cvar stuff.

	cvar_t	*(*Cvar_Get)(const char *name, const char *value, int flags, cvarcommand_t command); // 1
	cvar_t	*(*Cvar_Set)(const char *name, const char *value ); // 2
	void	(*Cvar_SetValue)(const char *name, float value ); // 3 

	// Command processing.

	int		(*Cmd_Argc) (void); // 4
	char	*(*Cmd_Argv) (int i); // 5
	char	*(*Cmd_Args) (void); // 6

	// Output to console, etc.

	void	(*Com_Printf) (char *str, ...); // 7
	void	(*Com_Sprintf) (char *dest, int size, char *fmt, ...); // 8
	void 	(*Com_DPrintf) (char *fmt, ...); // 9

	// File handling.

	int		(*FS_LoadFile) (char *name, void **buf, bool OverridePak); // 10
	void	(*FS_FreeFile) (void *buf); // 11
	
	// Misc

	int		(*irand)(int min, int max); // 12

	// Ghoul stuff.

	cvar_t	*ghl_specular; // 13
	IPlayerModelInfoC *(*NewPlayerModelInfo)(char *modelname); // 14
	int		(*FindGSQFile)(char *gsqdir, char *gsqfile, void **buffer); // 15
	bool	(*ReadGsqEntry)(int &filesize, char **tdata, char *seqname); // 16
	void	(*PrecacheGSQFile)(char *dirname, char *gsq_file, IGhoulObj *object); // 17
	int		(*RegisterGSQSequences)(char *gsqdir, char *subclass, IGhoulObj *object); // 18
	void	(*TurnOffPartsFromGSQFile)(char *dirname, char *poff_file, IGhoulObj *this_object, IGhoulInst *this_inst); // 19
} player_com_import_t;

//
// These are the functions imported by the player dll module when it is called
// from the client.
//

typedef struct
{ 
	// So we can grab the Ghoul pointer we need so badly.

	void	*(*GetGhoul)(); // 1

	// Getting level.time for weapon prediction.

	float	*levelTime; // 2

	// Helper functions for weapon firing.

	void	(*FireHelper)(sharedEdict_t &sh, void * ent, void * inven); // 3
	void	(*AltfireHelper)(sharedEdict_t &sh, void * ent, void * inven); // 4
	void	(*WeapSoundHelper)(const void *data); // 5
	void	(*WeapSoundKill)(void); // 6
	void	(*WeaponEffectHelper)(const void *data); // 7

	// Network stuff.

	int		(*ReadByte)(void); // 8
	int		(*ReadShort)(void); // 9
	int		(*ReadLong)(void); // 10
	int		(*ReadByteSizebuf)(sizebuf_t *sz); // 11
	int		(*ReadShortSizebuf)(sizebuf_t *sz); // 12
	int		(*ReadLongSizebuf)(sizebuf_t *sz); // 13
	void	(*ReadDataSizebuf)(sizebuf_t *sz, unsigned char *addr, int len); // 14
	void	(*WriteByteSizebuf)(sizebuf_t *sz,int b); // 15
	void	(*WriteShortSizebuf)(sizebuf_t *sz,int s); // 16
	void	(*WriteLongSizebuf)(sizebuf_t *sz,int i); // 17

	// Sizebuf stuff.

	void	(*SZ_Init)(sizebuf_t *buf, byte *data, int length); // 18
	void	(*SZ_Clear)(sizebuf_t *buf); // 19
	void	(*SZ_Write)(sizebuf_t *buf, const void *data, int length); // 20
} player_cl_import_t;

