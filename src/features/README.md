# Features Directory Structure

This directory contains modular features organized by functionality. Each feature has its own folder with:

- `hooks.cpp` - Function hooks and detours
- `cvars.cpp` - CVar declarations and registration
- `README.md` - Feature documentation

## Current Features

- **vaccine** - Team protection (prevents team switching)
- **movement** - Movement physics (friction, accel, airaccel, runspeed, etc.)
- **grenade** - Grenade impact explosion control
- **q2_mode** - Quake 2 compatibility mode
- **force_sky** - Force sky configstring
- **ghoul_tint** - Ghoul model tinting
- **fx** - Effects/blood system
- **gravity** - Gravity override
- **force_item_respawn** - Force item respawn time

## Adding New Features

1. Create a new folder: `src/features/my_feature/`
2. Add `hooks.cpp` for hook implementations
3. Add `cvars.cpp` for CVar declarations
4. Add `README.md` for documentation
5. Update `makefile` to include the new feature files
6. Update `hdr/features.h` with function declarations

