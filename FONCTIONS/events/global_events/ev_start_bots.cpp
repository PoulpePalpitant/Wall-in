#include "ev_start_bots.h"

#include "../events.h"
#include "../../time/cycles.h"

// Wow, 3 events in one place!!
static Event ev_StartBotCycles(Ev_Start_Bot_Cycles);
static Event ev_StartBotMove(Ev_Start_Bot_Move);
static Event ev_StartBotSpawn(Ev_Start_Bot_Spawn);

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
