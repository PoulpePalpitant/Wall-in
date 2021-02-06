
#include "timerOP.h"
#include "../bots/botmove.h"
#include "bot_move_cycle.h"


bool gMoveBotsThisCycle;	
int gBotMoveCycleTot;		

SpeedTimer gBotMoveTimer;	// Les bots bougent tous � la m�me vitesse, et sur le m�me rythme
int prevMovSpeed = 4000;	


void UPD_Bot_Move_Cycle()
{
	while (gBotMoveTimer.Tick())
	{
		gMoveBotsThisCycle = true;
		gBotMoveCycleTot++;	
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

	return false;	
}


void Temporary_Bot_Speed_Switch(int speed, bool overwritePrev)
{
	if(overwritePrev)
		prevMovSpeed = gBotMoveTimer.Get_Speed();

	gBotMoveTimer.Start_Timer(speed, 1, true);

}
void Restore_Prev_Bot_Speed()	
{
	gBotMoveTimer.Start_Timer(prevMovSpeed, 1, true);
}