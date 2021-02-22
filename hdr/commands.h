extern "C" void simpletest(lua_State * L);

void createCommands(void);

void Cmd_SofreeHelp(void);

void sf_sv_check_reso(void);
void sf_sv_save_reso(void);

void sf_sv_vector_grow(void);
void sf_sv_vector_copy(void);
void sf_sv_vector_set(void);
void sf_sv_vector_add(void);
void sf_sv_vector_subtract(void);
void sf_sv_vector_scale(void);
void sf_sv_vector_normalize(void);
void sf_sv_vector_length(void);
void sf_sv_vector_dotproduct(void);

void sf_sv_print_cprintf(void);
void sf_sv_print_bprintf(void);
void sf_sv_print_centerprint(void);
void sf_sv_print_cinprintf(void);
void sf_sv_print_welcomeprint(void);
void sf_sv_draw_string(void);
void sf_sv_draw_string2(void);
void sf_sv_draw_altstring(void);
void sf_sv_draw_clear(void);
void sf_sv_spackage_list(void);
void sf_sv_spackage_register(void);
void sf_sv_spackage_print_ref(void);
void sf_sv_spackage_print_id(void);
void sf_sv_spackage_print_obit(void);
void sf_sv_spackage_print_string(void);
void Cmd_SP_GetStringText(void);
void sf_sv_sound_remove(void);
void sf_sv_sound_register(void);
void sf_sv_sound_play_origin(void);
void sf_sv_sound_play_ent(void);
void sf_sv_sound_override(void);
void sf_sv_sound_list(void);
void sf_sv_script_unload(void);
void sf_sv_script_run(void);
void sf_sv_script_load(void);
void sf_sv_player_pos(void);
void sf_sv_player_paint(void);
void sf_sv_player_move(void);
void sf_sv_player_gravity(void);
void sf_sv_player_effect(void);
void sf_sv_player_ent(void);
void sf_sv_player_collision(void);
void sf_sv_player_anim(void);
void sf_sv_player_allow_attack(void);
void sf_sv_player_allow_altattack(void);
void sf_sv_player_allow_walk(void);
void sf_sv_player_weap_lock(void);
void sf_sv_player_weap_switch(void);
void sf_sv_player_weap_paint(void);
void sf_sv_player_weap_current(void);
void sf_sv_effect_endpos(void);
void sf_sv_effect_start(void);
void sf_sv_effect_list(void);
void sf_sv_effect_register(void);
void sf_sv_ent_paint(void);
void sf_sv_ent_vects(void);
void sf_sv_ent_spawn(void);
void sf_sv_ent_remove(void);
void sf_sv_ent_find(void);
void sf_sv_ent_create(void);
void sf_sv_ent_use(void);
void sf_sv_ent_anim(void);
void sf_sv_ent_model(void);

void sf_sv_ent_bolt(void);

void sf_sv_ent_relink(void);
void sf_sv_ent_callback(void);
void sf_sv_ent_field_get(void);
void sf_sv_ent_field_set(void);
void sf_sv_ent_tint(void);
void sf_sv_image_register(void);
void sf_sv_image_list(void);

void sf_sv_ghoul_scale(void);
void sf_sv_ghoul_translate(void);
void sf_sv_ghoul_register(void);
void sf_sv_ghoul_list(void);

void sf_sv_int_add(void);
void sf_sv_mem_read_string(void);
void sf_sv_mem_read_short(void);
void sf_sv_jmp_at(void);
void sf_sv_hook_at(void);
void sf_sv_mem_read_int(void);
void sf_sv_mem_read_float(void);
void sf_sv_mem_read_char(void);
void sf_sv_mem_write_char(void);
void sf_sv_mem_write_short(void);
void sf_sv_mem_write_float(void);
void sf_sv_mem_write_int(void);
void sf_sv_mem_write_string(void);
void sf_sv_configstring_set(void);
void sf_sv_math_sin(void);
void sf_sv_math_asin(void);
void sf_sv_math_cos(void);
void sf_sv_math_acos(void);
void sf_sv_math_tan(void);
void sf_sv_math_atan(void);
void sf_sv_math_or(void);
void sf_sv_math_and(void);
void sf_sv_math_not(void);
void sf_sv_lua_func_exec(void);



void randomBoxCode(void);

void test(void);


void Cmd_Blue_f(void);
void Cmd_Red_f(void);
void Cmd_Swap_f(void);

void goRed(int who);
void goBlue(int who);

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