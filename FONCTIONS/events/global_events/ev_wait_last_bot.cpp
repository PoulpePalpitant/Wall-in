#include "ev_wait_last_bot.h"

#include "../events.h"
#include "../msg_dispatcher.h"

#include "../../bots/botmeta.h"
#include "../../player/player.h"

static Event ev_WaitForLastBot(Ev_Wait_For_Last_Bot, 1); // L'event

void Ev_Wait_For_Last_Bot() 	// Attend que le dernier bot du niveau meurt(bool startLvl)
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