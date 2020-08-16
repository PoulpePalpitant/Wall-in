
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
#include "../lvls/lvl_1/msg_events/ev_stop_Jerry_1.h"

static Event ev_SpawnJerry(Ev_Spawn_Jerry, 2);

static Direction side;
static bool verti = false;
static int spw;
static int limit;		// Nombre de Jerry Max que Le joueur peut summon
static std::string howTo = "(Press Enter To Summon Jerry Again)";

bool jerryTime = false;		// Si On a des Jerry qui spawnenT
int jerCount;				// Nombre de fois que le joueur doit stopper Jerry
int deadJerrys;		// Le nombre de Jerry qui sont dead pendant un Jerry time


static bool spwThisFrame = false;
static int prevSpd;

void Add_Jerrys_To_Stop(int toAdd)
{
	jerCount += toAdd;
}

void Set_Jerry_Time(int JerryToStop)
{
	if (!jerryTime)
	{
		jerCount = JerryToStop;
		deadJerrys = 0;
		jerryTime = true;
	}
	else
		throw " fuck you ";
}

void Update_Dead_Jerrys()							// Nombre de Jerry à buter pendant un Jerry time
{
	deadJerrys++;

	if (deadJerrys == jerCount)
	{
		jerryTime = false;
	}
}
void Make_It_Vertical_Only()
{
	verti = true;
}

void Set_Jerry(Direction boxSide, int spwNum, int moveSpeed)	// Set Jerry pour les prochains spawn de Jerry
{
	side = boxSide;
	spw = spwNum;
	prevSpd = gBotMoveTimer.Get_Speed();
	gBotMoveTimer.Start_Timer(moveSpeed, 1, true);	// tu va devoir rétablir la vitesse précédante après ton Jerry spawn
}

void Ev_Stop_Spawn_Jerry()	// Stop l'event de spawn Jerry!
{
	verti = false;
	ev_SpawnJerry.Cancel();
	spwThisFrame = false;
	ConsoleRender::Add_String(howTo, { Find_Ctr_X((int)howTo.size()) , gConHeight - 14 }, GRAY, 0, true); // efface ce titre
	
	if (prevSpd == 0)
		prevSpd = prevMovSpeed;

	gBotMoveTimer.Start_Timer(prevSpd, 1, true);	// tu va devoir rétablir la vitesse précédante après ton Jerry spawn
	MsgQueue::Register(STOP_BOT_MOVE);
}

void Spawn_A_Jerry(Direction boxSide, int spwNum, int delay)	// Permet de spawn un Jerry
{
	gCustomBot.is = true;
	gCustomBot.fixedColor = true;
	gCustomBot.clr = gJerClr;
	gCustomBot.warningDelay = delay;	
	
	if (verti) // random border basically
		bots_to_spawn::gVerticalBorder = true;
	
	Spawn_A_Bot(boxSide, spwNum);		// Off he goes!
}

void Ev_Spawn_Jerry()
{
	if (!ev_SpawnJerry.Is_Active())
	{
		// initialisationa
		ConsoleRender::Add_String(howTo, { Find_Ctr_X((int)howTo.size()) , gConHeight - 14 }, GRAY, 150); // affiche ce titre
		gBotMoveTimer.Start_Timer(prevSpd, 1, true);
		//Set_Jerry_Time(0);
		//Ev_Dr_Stop_Jerry();
		spwThisFrame = false;
		ev_SpawnJerry.Activate();
		ev_SpawnJerry.Start(0);
		ev_SpawnJerry.delay.Start_Timer(10000, 1, true);
	}
	else
	{
		while (ev_SpawnJerry.delay.Tick())
		{

			if (!spwThisFrame && lastKey == KeyPressed::ENTER)	// WE SPAWN JERRY
			{
				Spawn_A_Jerry(side, spw, 5);
				lastKey = KeyPressed::NONE;
				//Add_Jerrys_To_Stop(1);
				/*spwThisFrame = true;*/
			}

		}

		
		/*spwThisFrame = false;*/
		// Cet Event Doit être cancel manuellement
	}
}

