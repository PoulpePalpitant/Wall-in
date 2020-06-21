
#include "timerOP.h"
#include "../bots/botmove.h"
#include "bot_move_cycle.h"


bool gMoveBotsThisCycle;					// On bouge les bots durant ce cycle
int gBotMoveCycle;						// L'intervalle de BotMove cycle. La distance entre le current et le next
time_t gCurrentBotMoveCycle;	// Le BotMove cycle actuel
time_t gNextBotMoveCycle;	// Le prochain BotMove cycle
int gBotMoveCycleTot;							// Le nombre total de botmove cycle ayant u lieu

void UPD_Bot_Move_Cycle()
{
	if (/*gameClockTEST.Get_Time()*/gLvlTime >= gNextBotMoveCycle)
	{
		gMoveBotsThisCycle = true;
		gCurrentBotMoveCycle = gNextBotMoveCycle;	// j'ai pt pas besoin de Current_Spawn_Cycle
		gNextBotMoveCycle += gBotMoveCycle/*+ gLvlTime - gNextBotMoveCycle*/;					// Compenserais pour un excès :O
		gBotMoveCycleTot++;						// Le nombre de cycle de spawn depuis le début de la game
	}
}
bool Move_Bots_This_Cycle()
{
	if (gMoveBotsThisCycle)
	{
		BotMove::Move_Bots();
		gMoveBotsThisCycle = false;
		return true;
	}

	return false;	// no moverino
}