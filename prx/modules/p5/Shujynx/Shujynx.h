#ifdef GAME_P5
#ifndef SHUJYNX_H
#define SHUJYNX_H

void ShujynxInit( void );
void ShujynxShutdown( void );


// PS3 system includes
#include "lib/common.h"
#include "lib/shk.h"

#include "modules/p5/p5.h"

typedef struct{
    int flags;
    short Field02;
    short Field04;
    short EnemyID[5];
    short FldMajorID;
    short FldMinorID;
    short MusicID;
} EncounterStruct;

#endif
#endif