#include "ev_start_bots.h"

#include "../events.h"
#include "../../time/cycles.h"

// Wow, 3 events in one place!!
static Event Ev_StopBotCycles(Ev_Start_Bot_Cycles);
static Event Ev_StopBotMove(Ev_Start_Bot_Move);
static Event Ev_StopBotSpawn(Ev_Start_Bot_Spawn);

void Ev_Start_Bot_Cycles()
{
	stopMoveCycle = false;
	stopSpwCycle = false;
}
void Ev_Start_Bot_Move()
{
	stopMoveCycle = false;
}
void Ev_Start_Bot_Spawn()
{
	stopSpwCycle = false;
}
