
#include "ev_spawn_Jerry.h"

#include "bots_to_spawn.h"
#include "../bots/botmeta.h"
#include "../events/msg_dispatcher.h"
#include "../events/events.h"
#include "../inputs/action_input.h"
#include "../time/bot_move_cycle.h"
#include "../console/sweet_cmd_console.h"
#include "../UI/console_output/render_list.h"
#include "spawn_bot.h"

static Event ev_SpawnJerry(Ev_Spawn_Jerry, 1);


static Direction side;
static int spw;
static std::string howTo = "(Press Enter To Summon Jerry Again)";
static bool jerryAlive;

static int prevSpd;

void Set_Jerry(Direction boxSide, int spwNum, int moveSpeed)	// Set Jerry pour les prochains spawn de Jerry
{
	side = boxSide;
	spw = spwNum;
	prevSpd = gBotMoveTimer.Get_Speed();
	gBotMoveTimer.Start_Timer(moveSpeed, 1, true);	// tu va devoir rétablir la vitesse précédante après ton Jerry spawn
}

void Ev_Stop_Spawn_Jerry()	// Stop l'event de spawn Jerry!
{
	ev_SpawnJerry.Cancel();
	jerryAlive = false;
	ConsoleRender::Add_String(howTo, { Find_Ctr_X((int)howTo.size()) , gConHeight - 15 }, GRAY, 0, true); // efface ce titre
	gBotMoveTimer.Start_Timer(prevSpd, 1, true);	// tu va devoir rétablir la vitesse précédante après ton Jerry spawn
	MsgQueue::Register(STOP_BOT_MOVE);

}

void Ev_Spawn_Jerry()
{
	if (!ev_SpawnJerry.Is_Active())
	{
		// initialisationa
		ConsoleRender::Add_String(howTo, { Find_Ctr_X((int)howTo.size()) , gConHeight - 15 }, GRAY, 150); // affiche ce titre
		jerryAlive = false;
		ev_SpawnJerry.Activate();
		ev_SpawnJerry.Start(0);
	}
	else
	{
			if (!jerryAlive)
			{
				if (!gAllBotMeta.alive && lastKey == KeyPressed::ENTER)	// WE SPAWN JERRY
				{
					gCustomBot.clr = LIGHT_GREEN;
					gCustomBot.warningDelay = 10;	// Jerry laisse plus de temps avant de spawner
					Spawn_A_Bot(side, spw);			// Off he goes!
					jerryAlive = true;
				}
			}
			else
			{
				if (!gAllBotMeta.alive)			
					jerryAlive = false;
				
			}
	}
}

