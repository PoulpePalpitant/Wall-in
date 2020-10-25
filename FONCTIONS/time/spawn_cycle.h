#pragma once 

#include <time.h>
#include "movement_timer.h"

extern bool gSpawnThisCycle;
extern int gSpawnCycle;							// L'intervalle de spawn cycle. La distance entre le current et le next
extern time_t gCurrentSpawnCycle;	// Le spawn cycle actuel
extern time_t gNextSpawnCycle;		// Le prochain spawn cycle
extern int gSpawnCycleTot;						// Le nombre total de spawn cycle ayant u lieu
extern SpeedTimer gSpwBotTimer;

extern const int CHECKPOINT_DELAY;	// Petit d�lay apr�s chaque checkpoint

void UPD_Spawn_Cycle();			// Refresh Timer des spawns
bool Spawn_Bots_This_Cycle();	// Spawn les bots, ou pas!
void Temporary_Spawn_Speed_Switch(int speed, bool overwritePrev);	// Instaure une nouvelle vitesse de spawn. "Store" la valeur de la vitesse pr�c�dante.
void Restore_Prev_Spw_Speed();	// restaure la vitesse pr�c�dante

void Checkpoint_Delay();	// Ajoute un d�lai apr�s avoir atteint un check point
