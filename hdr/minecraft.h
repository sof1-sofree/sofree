/*
A module to allow creation of entities with raytracing
*/

class Minecraft {
public:
	static void applyHooks(void);
	static void removeHooks(void);

	static void Minecraft::onDamage(edict_t *targ);
};