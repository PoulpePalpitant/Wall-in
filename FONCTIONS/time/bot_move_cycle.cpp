
#include "timerOP.h"
#include "../bots/botmove.h"
#include "bot_move_cycle.h"


bool gMoveBotsThisCycle;	// On bouge les bots durant ce cycle
int gBotMoveCycleTot;		// Le nombre total de botmove cycle ayant u lieu

SpeedTimer gBotMoveTimer;	// Pour l'instant, les bots bougent tous � la m�me vitesse, et sur le m�me rythme
int prevMovSPeed = 4000;


void UPD_Bot_Move_Cycle()
{
	while (gBotMoveTimer.Tick())
	{
		gMoveBotsThisCycle = true;
		gBotMoveCycleTot++;						// Le nombre de cycle de spawn depuis le d�but de la game
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


void Temporary_Bot_Speed_Switch(int speed, bool overwritePrev)	// Instaure une vouelle vitesse de bots. "Store" la valeur de la vitesse pr�c�dante.
{
	if(overwritePrev)
		prevMovSPeed = gBotMoveTimer.Get_Speed();

	gBotMoveTimer.Start_Timer(speed, 1, true);

}
void Restore_Prev_Bot_Speed()	// restaure la vitesse pr�c�dante
{
	gBotMoveTimer.Start_Timer(prevMovSPeed, 1, true);
}