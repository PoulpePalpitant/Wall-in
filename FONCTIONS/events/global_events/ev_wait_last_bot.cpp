#include "ev_wait_last_bot.h"

#include "../events.h"
#include "../msg_dispatcher.h"

#include "../../bots/botmeta.h"
#include "../../player/player.h"

static Event ev_WaitForLastBot(Ev_Wait_For_Victory, 1); // L'event
static Event ev_WaitForBotDeaths(Ev_Wait_For_Bot_Deaths, 1); // L'event

void Ev_Wait_For_Victory() 	// Attend que le dernier bot du niveau meurt(bool startLvl)
{

	if (!ev_WaitForLastBot.Is_Active())
	{
		
		ev_WaitForLastBot.Activate(); // initialisation
		ev_WaitForLastBot.Start(0);
		ev_WaitForLastBot.delay.Start_Timer(10000, 1, true);
	}
	else
		while (ev_WaitForLastBot.delay.Tick())
		{
			if (!gAllBotMeta.alive && P1.Get_HP())	
			{
				MsgQueue::Register(VICTORY);
				ev_WaitForLastBot.Cancel();
			}
		}
}

void Ev_Wait_For_Bot_Deaths() 	// Attend que tout les bot soient mort
{

	if (!ev_WaitForBotDeaths.Is_Active())
	{
		ev_WaitForBotDeaths.Activate(); // initialisation
		ev_WaitForBotDeaths.Start(0);
		ev_WaitForBotDeaths.delay.Start_Timer(10000, 1, true);
	}
	else
		while (ev_WaitForBotDeaths.delay.Tick())
		{
			if (!gAllBotMeta.alive && P1.Get_HP())
			{
				MsgQueue::Register(NO_BOTS_ALIVE);
				ev_WaitForBotDeaths.Cancel();
			}

		}
}