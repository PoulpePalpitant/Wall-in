
#include "timerOP.h"
#include "../spawns/spawn_bot.h"

#include "spawn_cycle.h"


bool gSpawnThisCycle;
int gSpawnCycleTot;						
SpeedTimer gSpwBotTimer;
int prevSpwSpeed = 0;

const int CHECKPOINT_DELAY = 5;


void Reset_Spw_Cycle()				
{
	gSpawnCycleTot = 0;
}

void UPD_Spawn_Cycle()			
{
	while (gSpwBotTimer.Tick())
	{
		gSpawnThisCycle = true;
		gSpawnCycleTot++;		
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

	return false;	
}

void Temporary_Spawn_Speed_Switch(int speed, bool overwritePrev)	
{
	if (overwritePrev)
		prevSpwSpeed = gSpwBotTimer.Get_Speed();

	gSpwBotTimer.Start_Timer(speed, 1, true);
}

void Restore_Prev_Spw_Speed()	
{
	gSpwBotTimer.Start_Timer(prevSpwSpeed, 1, true);
	prevSpwSpeed = 0;
}

void Checkpoint_Delay()	// Délay après chaque checkpoint
{
	gSpwBotTimer.Add_Count(CHECKPOINT_DELAY);
}

void Cancel_Checkpoint_Delay()	
{
	gSpwBotTimer.Add_Count(-CHECKPOINT_DELAY);
}