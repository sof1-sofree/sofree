#pragma once

/*
    Compile-time Feature Configuration
    
    Auto-generated from features/FEATURES.txt
    Enable/disable features by commenting/uncommenting lines in features/FEATURES.txt
    
    Format in features/FEATURES.txt:
    - feature_name     (enabled)
    - // feature_name  (disabled)
*/

#define FEATURE_CORE_INIT 1  // enabled
#define FEATURE_MEMORY_PATCHES 1  // enabled
#define FEATURE_VACCINE 1  // enabled
#define FEATURE_MOVEMENT 1  // enabled
#define FEATURE_GRAVITY 1  // enabled
#define FEATURE_GRENADE 1  // enabled
#define FEATURE_Q2_MODE 1  // enabled
#define FEATURE_FORCE_ITEM_RESPAWN 1  // enabled
#define FEATURE_FORCE_SKY 1  // enabled
#define FEATURE_GHOUL_TINT 1  // enabled
#define FEATURE_FX 1  // enabled

/*
    Usage in feature files:
    
    #include "../../../hdr/feature_config.h"
    
    #if FEATURE_MY_FEATURE
    // ... feature implementation
    #endif
*/
