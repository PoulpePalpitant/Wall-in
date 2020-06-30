
#include "timerOP.h"
#include "../bots/botmove.h"
#include "bot_move_cycle.h"


bool gMoveBotsThisCycle;	// On bouge les bots durant ce cycle
int gBotMoveCycleTot;		// Le nombre total de botmove cycle ayant u lieu

MovementTimer gBotMoveTimer;	// Pour l'instant, les bots bougent tous à la même vitesse, et sur le même rythme

void UPD_Bot_Move_Cycle()
{
	while (gBotMoveTimer.Tick())
	{
		gMoveBotsThisCycle = true;
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