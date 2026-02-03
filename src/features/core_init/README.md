# Core Init Feature

Handles essential initialization hooks that are required for SoFree to function.

## Functions

- `core_init_applyHooks()` - Applies core initialization detours

## Hooks

- `Sys_GetGameApi` - Main game API hook
- `Sys_GetPlayerAPI` - Player API hook  
- `SV_InitGameProgs` - Game progs initialization hook
- `Qcommon_Init` - Common initialization hook

## Dependencies

- Requires `detourSysShutDown()` from server_begin.cpp

