# Memory Patches Feature

Applies various memory patches using VirtualProtect to modify game behavior.

## Functions

- `memory_patches_applyPatches()` - Applies all memory patches

## Patches

- **Gravity disable** - Disables gravity setting from SV_GRAVITY CVAR
- **Scoreboard patches** - Prevents scoreboard clearing in CTF/DM, faster scoreboard
- **Network overflow patches** - Removes overflow warnings and rate drop logic
- **Ammo fix** - Fixes bbox offset for sp_ammo_slug and sp_ammo_shotgun
- **Score command** - Prevents Cmd_Score_f from being called in player_die

## Dependencies

- Requires `ammofix` variable from hooks.cpp

