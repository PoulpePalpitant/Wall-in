#pragma once 

#include "movement_timer.h"

extern bool gSpawnThisCycle;
extern int gSpawnCycle;				
extern time_t gCurrentSpawnCycle;	
extern time_t gNextSpawnCycle;		
extern int gSpawnCycleTot;			
extern SpeedTimer gSpwBotTimer;

extern const int CHECKPOINT_DELAY;	

void UPD_Spawn_Cycle();			
bool Spawn_Bots_This_Cycle();	
void Temporary_Spawn_Speed_Switch(int speed, bool overwritePrev);	
void Restore_Prev_Spw_Speed();	

void Checkpoint_Delay();	    
void Cancel_Checkpoint_Delay();	// C'est pour fixe l'animation de spawn du player qui efface des links.
