extern char countryCode[16][64];

class Scoreboard {
public:
	static const char * geoSaveFile;
	static bool isMenuOn[16];
	static map<string,bool> geoMap;

	static void applyHooks(void);
	static void removeHooks(void);

	static void saveNewFlagToFile(char * newflag);
	static bool isFlagNew(char * c);

	static void adjustPulseRate(unsigned char newpulse);
	static void toggleMenu(edict_t * ent);

	static void onMapBegin(void);
	static void clientConnect(edict_t *ent);
	static void clientRespawn(edict_t *ent);
	static void drawMe (edict_t *ent, edict_t *killer, qboolean log_file);

	static void drawCreditImage(edict_t * ent);
	static void hideCreditImage(edict_t * ent);

};