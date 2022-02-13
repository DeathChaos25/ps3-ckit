#ifdef GAME_P5
// PS3 system includes
#include <sys/prx.h>
#include <sys/tty.h>
#include <sys/syscall.h>
// Pre-prepared libraries exist in lib
// Common includes things like printf for printing, strlen, etc.
// PRX dont have access to the usual C libraries, so any functionality that you need from it
// will have to be reimplemented in there.
#include "lib/common.h"

// SHK (Static Hook library)
#include "lib/shk.h"

// Include this to use config variables
#include "lib/config.h"

#include "modules/p5/p5.h"
#include "Shujynx.h"

#define DEBUG_LOG( msg, ... ) \
  if ( CONFIG_ENABLED( debug ) ) printf( "DEBUG: " msg, ##__VA_ARGS__ )


// You need to declare hooks with SHK_HOOK before you can use them.
// The start function of the PRX. This gets executed when the loader loads the PRX at boot.
SHK_HOOK(void, GetFieldIDsFromEncountTBL, int param_1, u32 param_2, short *param_3, short *param_4);
// This means game data is not initialized yet! If you want to modify anything that is initialized after boot,
// hook a function that is called after initialisation.

void GetFieldIDsFromEncountTBLHook(int param_1, u32 param_2, short *param_3, short *param_4)
{
  SHK_CALL_HOOK(GetFieldIDsFromEncountTBL, param_1, param_2, param_3, param_4);
  if (CONFIG_ENABLED( alwaysLoadSpecificBattleField ))
  {
    *param_3 = CONFIG_INT( forcedFieldMajorID );
    *param_4 = CONFIG_INT( forcedFieldMinorID );
  }
}

void ShujynxInit( void )
{
  // Hooks must be 'bound' to a handler like this in the start function.
  // If you don't do this, the game will crash.
  SHK_BIND_HOOK(GetFieldIDsFromEncountTBL, GetFieldIDsFromEncountTBLHook);
}

void ShujynxShutdown( void )
{
  // Executed when the PRX module is unloaded.    
}
#endif