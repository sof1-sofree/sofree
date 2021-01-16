extern "C" void simpletest(lua_State * L);

void createCommands(void);

void Cmd_SofreeHelp(void);

void sf_sv_lua_func_exec(void);


extern "C" int sf_sv_console_write(lua_State *L);
extern "C" int sf_sv_cmd_list(lua_State * L);
extern "C" int sf_sv_check_reso(lua_State * L); // in:Int(slotid) in:Int(challenge) in:String(cvar) 
extern "C" int sf_sv_save_reso(lua_State * L); // in:Int(slotid) in:Int(X) in:Int(Y)

extern "C" int sf_sv_vector_grow(lua_State * L); //in:Vector(a) in:Float(scale) in:Vector(b) out:Vector(c)
extern "C" int sf_sv_vector_copy(lua_State * L); //out:DstVectorVar in:SrcVectorVar
extern "C" int sf_sv_vector_create(lua_State * L); //in:floatX in:floatY in:floatZ out:DstVectorVar
extern "C" int sf_sv_vector_add(lua_State * L); //in:vectorA in:vectorB out:vectorOut
extern "C" int sf_sv_vector_subtract(lua_State * L); //in:vectorA in:vectorB out:VectorOut
extern "C" int sf_sv_vector_scale(lua_State * L); //in:vectorA in:float(scale) out:Vector
extern "C" int sf_sv_vector_normalize(lua_State * L); //in:vectorA out:vectorOut
extern "C" int sf_sv_vector_length(lua_State * L); // in: vectorA out:Float
extern "C" int sf_sv_vector_dotproduct(lua_State * L); // in:vectorA in:vectorB out:Float

extern "C" int sf_sv_print_cprintf(lua_State * L);// in:entHandle in:String(msg)
extern "C" int sf_sv_print_bprintf(lua_State * L); // in:String(msg)
extern "C" int sf_sv_print_centerprint(lua_State * L); // in:entHandle in:String(msg)
extern "C" int sf_sv_print_cinprintf(lua_State * L); // in:entHandle in:Int(x) in:Int(y) in:Int(speed) in:String(msg)
extern "C" int sf_sv_print_welcomeprint(lua_State * L); // in:entHandle

extern "C" int sf_sv_draw_string(lua_State * L); // in:Int(x) in:Int(y) in:String(msg)
extern "C" int sf_sv_draw_string2(lua_State * L); // in:Int(x) in:Int(y) in:String(msg)
extern "C" int sf_sv_draw_altstring(lua_State * L); // in:Int(x) in:Int(y) in:String(msg)
extern "C" int sf_sv_draw_clear(lua_State * L); //0

extern "C" int sf_sv_spackage_list(lua_State * L); // inOptional:String(substring) out:ListOfStrings
extern "C" int sf_sv_spackage_register(lua_State * L); // in:String(name)
extern "C" int sf_sv_spackage_print_ref(lua_State * L); // in: EntHandle in:String(fileref) in:String(indexref) In:OptionalArgs...printf
extern "C" int sf_sv_spackage_print_id(lua_State * L); // in:entHandle in:Int(idfile) in:Int(index) In:OptionalArgs...printf
extern "C" int sf_sv_spackage_print_obit(lua_State * L); // in:Int(EntHandle) in:Int(shortID)
extern "C" int sf_sv_spackage_print_string(lua_State * L); // in:String(msg) in:Int(BufferSize) in:Int(ID)

extern "C" int Cmd_SP_GetStringText(lua_State * L);// in:Int(ID)

extern "C" int sf_sv_sound_remove(lua_State * L); // in:String(name)
extern "C" int sf_sv_sound_register(lua_State * L); // in:String(name)
extern "C" int sf_sv_sound_play_origin(lua_State * L); // in:String(name) in:Vector(origin) in:Int(channel) in:Float(volume) in:Float(Attenuation) in:Integer(clientNum)
extern "C" int sf_sv_sound_play_ent(lua_State * L); //in:String(name) in:EntHandle in:Int(Channel) in:Float(Volume) in:Float(Attenuation) in:Int(ClientNum)
extern "C" int sf_sv_sound_override(lua_State * L); // in:String(origSound) in:String(newSound) in:Float(newAttenuation)
extern "C" int sf_sv_sound_list(lua_State * L); // in:OptionalString(substring) out:ListOfStrings

extern "C" int sf_sv_script_unload(lua_State * L); // in: scriptHandle
extern "C" int sf_sv_script_run(lua_State * L); // in:String(name)
extern "C" int sf_sv_script_load(lua_State * L); // out:scriptHandle in:String(name) in:OptionalArgsStringsScriptParameters st.

extern "C" int sf_sv_player_pos(lua_State * L); // out:Vector(pos) in:Int(slotid)
extern "C" int sf_sv_player_paint(lua_State * L); // in:Int(slotid) in:Float(r) in:Float(g) in:Float(b) in:Float(a)
extern "C" int sf_sv_player_move(lua_State * L); // in:Int(slotid) in:Vector(pos)
extern "C" int sf_sv_player_gravity(lua_State * L); // in:Int(slotid) in:ShortInt(grav)
extern "C" int sf_sv_player_effect(lua_State * L); // Incomplete.
extern "C" int sf_sv_player_ent(lua_State * L); // in:Int(slotid) out:entHandle
extern "C" int sf_sv_player_collision(lua_State * L); // in:Int(slotid) in:Bool(on/off)
extern "C" int sf_sv_player_anim(lua_State * L); // in:Int(playerslot) in:String(animName) in:Float(startpos) in:Int(interuptCurrent) in:Int(EndCondition) in:Int(resume) in:Int(reverse)
extern "C" int sf_sv_player_allow_attack(lua_State * L); // in:Int(playerslot) in:Bool(y/n)
extern "C" int sf_sv_player_allow_altattack(lua_State * L); // in:Int(playerslot) in:Bool(y/n)
extern "C" int sf_sv_player_allow_walk(lua_State * L); // in:Int(playerslot) in:Bool(y/n)
extern "C" int sf_sv_player_weap_lock(lua_State * L); // in:Int(playerslot) in:Bool(y/n)
extern "C" int sf_sv_player_weap_switch(lua_State * L); // in:Int(playerslot) in:Int(weapId)
extern "C" int sf_sv_player_weap_paint(lua_State * L); // in:Int(playerslot) in:Float(r) in:Float(g) in:Float(b) in:Float(a)
extern "C" int sf_sv_player_weap_current(lua_State * L); // out:Int(weapId) in:Int(slotid)

extern "C" int sf_sv_effect_endpos(lua_State * L); // in:Vector(Endpos)
extern "C" int sf_sv_effect_start(lua_State * L); // in:EffectFile in:Vector(StartPos)
extern "C" int sf_sv_effect_list(lua_State * L); // in:String(optionalSubstring) out:ListOfStrings
extern "C" int sf_sv_effect_register(lua_State * L); // in:String(name)

extern "C" int sf_sv_ent_paint(lua_State * L); // in:entHandle in:Float(r) in:Float(g) in:Float(b) in:Float(a)
extern "C" int sf_sv_ent_vects(lua_State * L); // out:3 Vectors in:entHandle
extern "C" int sf_sv_ent_spawn(lua_State * L); // in:entHandle
extern "C" int sf_sv_ent_remove(lua_State * L); // in:entHandle
extern "C" int sf_sv_ent_find(lua_State * L); // out:ListOfEntIds in:Int(field) in:String(Equal)
extern "C" int sf_sv_ent_create(lua_State * L); // out:entHandle
extern "C" int sf_sv_ent_use(lua_State * L); // in:entHandle
extern "C" int sf_sv_ent_anim(lua_State * L); // in:Int(entHandle) in:String(anim) in:Float(start) in:Int(interuptCurrent) in:Int(EndCondition) in:Int(resume) in:Int(reverse)
extern "C" int sf_sv_ent_model(lua_State * L); // in:Int(entHandle) in:String(dir) in:String(modelname)

extern "C" int sf_sv_ent_bolt(lua_State * L); // in:EntHandle in:Float(scale)
extern "C" int sf_sv_ent_relink(lua_State * L); // in:EntHandle
extern "C" int sf_sv_ent_callback(lua_State * L); // in:EntHandle in:String(type) in:String(funcname)
extern "C" int sf_sv_ent_field_get(lua_State * L); // in:entHandle in:String(fieldname) out:Data?String?Dunno?ManyTypes.
extern "C" int sf_sv_ent_field_set(lua_State * L); // in:entHandle in:String(fieldname) in:Data(newValue)
extern "C" int sf_sv_ent_tint(lua_State * L); // in:entHandle in:Vector(rgb) in: Float(alpha)

extern "C" int sf_sv_image_register(lua_State * L); //in:String(image)
extern "C" int sf_sv_image_list(lua_State * L); // in:String(optionalSubstring) out:ListStrings

extern "C" int sf_sv_ghoul_scale(lua_State * L); // in:entHandle in:Float(scale)
extern "C" int sf_sv_ghoul_translate(lua_State * L); // in:entHandle in:Vector
extern "C" int sf_sv_ghoul_register(lua_State * L); // in:String(nameOfFile)
extern "C" int sf_sv_ghoul_list(lua_State * L); // in:String(optionalSubString) out:ListOfStrings

extern "C" int sf_sv_int_add(lua_State * L); // in:Int(input) in:Int(HowMuch)

extern "C" int sf_sv_mem_read_string(lua_State * L); // in:Int(memAddress) out:String
extern "C" int sf_sv_mem_read_short(lua_State * L); // in:Int(memAddress) out:Int(short)
extern "C" int sf_sv_jmp_at(lua_State * L); // in:Int(From) in:Int(to)
extern "C" int sf_sv_hook_at(lua_State * L); // Undocumented
extern "C" int sf_sv_mem_read_int(lua_State * L); // in:Int(memAddress) out:Int
extern "C" int sf_sv_mem_read_float(lua_State * L); // in:Int(memAddress) out:Float
extern "C" int sf_sv_mem_read_char(lua_State * L); // in:Int(memAddress) out:Char
extern "C" int sf_sv_mem_write_char(lua_State * L); // in:Int(memAddress) in:char
extern "C" int sf_sv_mem_write_short(lua_State * L); // in:Int(memAdderss) in:Int(short)
extern "C" int sf_sv_mem_write_float(lua_State * L); // in:Int(memAddress) in:Float
extern "C" int sf_sv_mem_write_int(lua_State * L); // in:Int(memAddress) in:Int
extern "C" int sf_sv_mem_write_string(lua_State * L); // in:Int(memAddress) in:String

extern "C" int sf_sv_configstring_set(lua_State * L); // in: Int(index) in:String(value)

extern "C" int sf_sv_math_sin(lua_State * L); // in:Float(angle) out:Float(sin)
extern "C" int sf_sv_math_asin(lua_State * L); // in: Float(num) out:Float(angle)
extern "C" int sf_sv_math_cos(lua_State * L); // in:Float(angle) out:Float(cos)
extern "C" int sf_sv_math_acos(lua_State * L); // in: Float(num) out:Float(angle)
extern "C" int sf_sv_math_tan(lua_State * L); // in:Float(angle) out:Float(tan)
extern "C" int sf_sv_math_atan(lua_State * L); // in: Float(num) out:Float(angle)
extern "C" int sf_sv_math_or(lua_State * L); // in:Int(numA) in:Int(numB) out:Int
extern "C" int sf_sv_math_and(lua_State * L);// in:Int(numA) in:Int(numB) out:Int 
extern "C" int sf_sv_math_not(lua_State * L); // in:Int(numA) in:Int(numB) out:Int


void Cmd_Blue_f(void);
void Cmd_Red_f(void);
void Cmd_Swap_f(void);

void goRed(int who);
void goBlue(int who);

void randomBoxCode(void);

void ThinkEventCallback(edict_t * self);
void TouchEventCallback(edict_t *self, edict_t *other, cplane_t *plane, struct mtexinfo_s *surf);
void UseEventCallback(edict_t *self, edict_t *other, edict_t *activator);
void PlUseEventCallback(edict_t *self, edict_t *other, edict_t *activator);
void PainEventCallback(edict_t *self, edict_t *other, float kick, int damage, vec3_t wherehit);
void DieCallback(edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point);

void Cmd_CalcFreeImageSlots(void);
void Cmd_CalcFreeEffectSlots(void);
void Cmd_CalcFreeGhoulSlots(void);
void Cmd_CalcFreeSoundSlots(void);


// effect fields that can be sent
#define EFF_SCALE			0x01
#define EFF_NUMELEMS		0x02
#define EFF_POS2			0x04
#define EFF_DIR				0x08
#define EFF_MIN				0x10
#define EFF_MAX				0x20
#define EFF_LIFETIME		0x40
#define EFF_RADIUS			0x80
							
#define EFAT_POS			0x01
#define EFAT_ENT			0x02
#define EFAT_BOLT			0x04
#define EFAT_BOLTANDINST	0x08	
#define EFAT_POSTOWALL		0x20	// pos2 gets frame updates
#define EFAT_ALTAXIS		0x40	// uses different axis for ghoul stuff
#define EFAT_HASFLAGS		0x80



#define MAX_D_SCRIPTS 64
extern struct d_script_s * dende_scripts[MAX_D_SCRIPTS];
extern int d_script_pointer;
extern float player_tint[32][4];
extern float player_wep_tint[32][4];
extern unsigned int was_ghosted[32];
extern bool player_collision[32];
extern bool new_client[32];
extern short client_gravity[32];

extern bool disable_attack[32];
extern  bool disable_altattack[32];
extern bool disable_walk[32];

extern unsigned int num_sound_overrides;
typedef struct sound_overrides_s {
	char orig_sound[256];
	char new_sound[256];
	int index;
	float atten_mod;
	struct sound_overrides_s * next,*prev;
} sound_overrides_t;
extern sound_overrides_t sound_overrides;

extern unsigned int num_scripts;
typedef struct script_list_s {
	char script_name[64];
	void * runner;
	void * cscript;
	struct script_list_s * next,*prev;
} script_list_t;
extern script_list_t the_scripts;

typedef struct event_think_s {
	edict_t * ent;
	char sofplusfunc[64];
	struct event_think_s * next,*prev;
} event_think_t;
extern event_think_s think_events;

typedef struct event_touch_s {
	edict_t * ent;
	char sofplusfunc[64];
	struct event_touch_s * next,*prev;
} event_touch_t;
extern event_touch_s touch_events;

typedef struct event_use_s {
	edict_t * ent;
	char sofplusfunc[64];
	struct event_use_s * next,*prev;
} event_use_t;
extern event_use_s use_events;

typedef struct event_pluse_s {
	edict_t * ent;
	char sofplusfunc[64];
	struct event_pluse_s * next,*prev;
} event_pluse_t;
extern event_pluse_s pluse_events;

typedef struct event_pain_s {
	edict_t * ent;
	char sofplusfunc[64];
	struct event_pain_s * next,*prev;
} event_pain_t;
extern event_pain_s pain_events;

typedef struct event_die_s {
	edict_t * ent;
	char sofplusfunc[64];
	struct event_die_s * next,*prev;
} event_die_t;
extern event_die_s die_events;

extern int last_created_cscript;

extern void * player_export;

extern int reso2d[16][2];
extern bool show_score[16];
extern void * gametype_self;
extern short prev_sidemove[16];
extern byte prev_buttons[16];

extern char layoutstring[1024];
extern int layoutstring_len;
extern char sofreebuildstring[128];
extern int sofreebuild_len;




extern void * game_clients;
#define MAX_NET_COMMANDS 1024
#define MAX_PACKETS 1024
#define PACKET_MINUS_HEADER 1390 
#define TOTAL_PSIZE MAX_PACKETS * PACKET_MINUS_HEADER
typedef struct networkCommand_s {
	int msgsize;
} networkCommand_t;

extern networkCommand_t net_commands[16][MAX_NET_COMMANDS];
extern int num_net_cmds[16];
extern char unreliableData[16][TOTAL_PSIZE]; //1390 * MAX_PACKETS
extern unsigned int unreliablePointer[16];

extern void Netchan_Transmit_Unreliable(netchan_t *chan, int length, byte *data);


extern char _BUILD_YEAR;
extern char _BUILD_MONTH;
extern char _BUILD_DAY;
extern char _BUILD_NUMBER;

extern sizebuf_t * sv_multicast;

extern bool INSIDE_SPACKAGE_PRINT_ID;
extern void * spackage_items;

extern float ammofix;

#define	FOFS(x) (int)&(((edict_t *)0)->x)

extern int next_available_ID;