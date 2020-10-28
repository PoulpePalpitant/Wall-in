
#include "timerOP.h"
#include "../spawns/spawn_bot.h"

#include "spawn_cycle.h"


bool gSpawnThisCycle;
int gSpawnCycleTot;						// Le nombre total de spawn cycle ayant u lieu
SpeedTimer gSpwBotTimer;
int prevSpwSpeed = 0;

const int CHECKPOINT_DELAY = 1;


void Reset_Spw_Cycle()				// Reset le nombre de spw cycle à 0
{
	gSpawnCycleTot = 0;
}

void UPD_Spawn_Cycle()			// Refresh Timer des spawns
{
	while (gSpwBotTimer.Tick())
	{
		gSpawnThisCycle = true;
		gSpawnCycleTot++;						// Le nombre de cycle de spawn depuis le début de la game
	}
}

bool Spawn_Bots_This_Cycle()
{
	if (gSpawnThisCycle)
	{
		Spawn_Bots();
		gSpawnThisCycle = false;
		return true;
	}

	return false;	// no spawnerino
}

void Temporary_Spawn_Speed_Switch(int speed, bool overwritePrev)	// Instaure une vouelle vitesse de bots. "Store" la valeur de la vitesse original.
{
	if (overwritePrev)
		prevSpwSpeed = gSpwBotTimer.Get_Speed();

	gSpwBotTimer.Start_Timer(speed, 1, true);
}

void Restore_Prev_Spw_Speed()	// restaure la vitesse précédante
{
	gSpwBotTimer.Start_Timer(prevSpwSpeed, 1, true);
	prevSpwSpeed = 0;
}

void Checkpoint_Delay()	// Délay après chaque checkpoint
{
	gSpwBotTimer.Add_Count(CHECKPOINT_DELAY);
}