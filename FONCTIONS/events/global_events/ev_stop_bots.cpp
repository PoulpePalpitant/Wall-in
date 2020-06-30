#include "ev_stop_bots.h"

#include "../events.h"
#include "../../time/cycles.h"

// Wow, 3 events in one place!!
static Event ev_StopBotCycles(Ev_Stop_Bot_Cycles);
static Event ev_StopBotMove(Ev_Stop_Bot_Move);
static Event ev_StopBotSpawn(Ev_Stop_Bot_Spawn);



void Ev_Stop_Bot_Cycles()
{
	stopMoveCycle = true;
	stopSpwCycle = true;
}
void Ev_Stop_Bot_Move()
{
	stopMoveCycle = true;
}
void Ev_Stop_Bot_Spawn()
{
	stopSpwCycle = true;
}
