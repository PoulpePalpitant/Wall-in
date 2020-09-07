
#include "ev_warning.h"

#include "../../UI/console_output/render_list.h"
#include "../../console/sweet_cmd_console.h"
#include "../../events/events.h"
#include "../../events/msg_dispatcher.h"
#include "../../UI/map.h"
#include "../../lvls/lvl_1/msg_events/ev_speeding_up.h"

int WarningDrawerList::animationSteps = 1;							// Nombre de steps dans cet animation
WarningDrawer  WarningDrawerList::drawer[MAX_WAR_DRAWERS] = {};		// why not 20?
int WarningDrawerList::total;

static Event ev_DrawWarnings(Ev_Draw_Warnings);	// qui va draw!
static Event ev_MultiColorWarnings(Ev_MultiColor_Warnings, 4);
//static Event ev_Dr_Warning(Ev_Dr_Warning);	// draw désuet*
//static Event ev_Er_Warning(Ev_Er_Warning);	// draw	désuet*

static Coord ori;	// Origine du titre, coin gauche up
static Distance YBtw = 7;
static int numWarnings = 6;

//static std::string day_1 = " DAY 1";
const std::string T_WARNING[] =	// Le titre principal	font = slant
{
" _       _____    ____  _   _______   ________ ",
"| |     / /   |  / __ \\/ | / /  _/ | / / ____/",
"| | /| / / /| | / /_/ /  |/ // //  |/ / / __   ",
"| |/ |/ / ___ |/ _, _/ /|  // // /|  / /_/ /   ",
"|__/|__/_/  |_/_/ |_/_/ |_/___/_/ |_/\\____/   "
};

const std::string T_WARNING_2[] =	// Le titre principal	font = small slant
{
 " _      _____   ___  _  _______  _______",
 "| | /| / / _ | / _ \\/ |/ /  _/ |/ / ___/",
 "| |/ |/ / __ |/ , _/    // //    / (_ / ",
 "|__/|__/_/ |_/_/|_/_/|_/___/_/|_/\\___/  "
};

const std::string T_WARNING_3[] =	// Le titre principal	font = small
{ 
 "__      ___   ___ _  _ ___ _  _  ___ "
 "\\ \\    / /_\\ | _ \\ \\| |_ _| \\| |/ __|"
 " \\ \\/\\/ / _ \\|   / .` || || .` | (_ |"
 "  \\_/\\_/_/ \\_\\_|_\\_|\\_|___|_|\\_|\\___|"
};
                                       

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


static void Dr_Warning(Colors clr = WHITE, bool erase = false)		
{
	int size = (int)T_WARNING_2[0].length();
	char symbol = 0;
	
	static Coord crd;
	for (int line = 0; line < 4; line++)	// nombre de lignes
	{
		crd = ori;// neccessary

		for (int sym = 0; sym < size; sym++, crd.x++)
		{

			if(erase)
				ConsoleRender::Add_Char({ crd.x, crd.y + line }, TXT_CONST.SPACE);
			else
			{
				if (T_WARNING_2[line][sym] == TXT_CONST.SPACE)
					continue;//symbol = 250;			
				else
					symbol = T_WARNING_2[line][sym];

				ConsoleRender::Add_Char({ crd.x, crd.y + line }, symbol, clr);
			}
		}
	}
}

static void Set_Ori_X(bool leftRight)	// just le X
{
	if (leftRight)
		ori.x = ((Find_Ctr_X((int)std::size(T_WARNING_2[0]))) / 2) - 20;
	else
		ori.x = ((Find_Ctr_X((int)std::size(T_WARNING_2[0]))) / 2) * 3 + 21;
}

static void Set_Ori_Y(bool topBot)	// just le Y
{
	if (topBot)
		ori.y = (gConHeight / 2) - 20;
	else
		ori.y = (gConHeight / 2) + 14;
}

static void Set_Ori(bool leftRight, bool topBot)	// true = left, top, false = right, bot
{
	Set_Ori_X(leftRight);
	Set_Ori_Y(leftRight);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Ev_Draw_Warnings()			// Voici le multiple drawer
{
	static WarningDrawer* pencil;	/// my pencil	

	if (!ev_DrawWarnings.Is_Active())
	{
		ev_DrawWarnings.Activate();
		ev_DrawWarnings.Start(0);
		ev_DrawWarnings.delay.Start_Timer(10000, 1, true);
	}
	else
	{
		for (int index = 0; index < WarningDrawerList::total; index++)
		{
			pencil = &WarningDrawerList::drawer[index];

			while (pencil->timer.Tick())
			{
				if (pencil->dr_Er)	// DRAW
				{
					Set_Ori(true, true);
					ori.y = ori.y + (pencil->currStep * YBtw);	// ceci va faire starter en haut
					Dr_Warning(pencil->clr);

					Set_Ori(false, false);
					ori.y -= (pencil->currStep * YBtw);	// ceci va faire starter en bas
					Dr_Warning(pencil->clr);
					pencil->currStep++;
				}
				else	//ERASE
				{
					Set_Ori(true, false);
					ori.y += (pencil->currStep * YBtw);	// ceci va faire starter en bas a gauche
					Dr_Warning(WHITE, true);

					Set_Ori(false, true);
					ori.y -= (pencil->currStep * YBtw);	// ceci va faire starter en haut a droite
					Dr_Warning(WHITE, true);
					pencil->currStep++;
					ev_DrawWarnings.Advance(0);
				}
			}
			
			if(!pencil->timer.Is_On())
				WarningDrawerList::Remove(index);	// we done here

		}
	}
}

void Ev_MultiColor_Warnings() // voici un event custom
{
	static Colors clr;
	static int modulo;

	if (!ev_MultiColorWarnings.Is_Active())
	{
		ev_MultiColorWarnings.Activate();
		ev_MultiColorWarnings.Start(4000, 9);
	}
	else
		while (ev_MultiColorWarnings.delay.Tick())
		{
			switch (ev_MultiColorWarnings.Get_Current_Step())
			{
			case 1: 
				modulo = ev_MultiColorWarnings.delay.Get_Moves_Left() % 2;
				
				// V1
				//if (modulo == 3)
				//	clr = LIGHT_YELLOW;
				//else
				//	if(modulo == 2)
				//		clr = LIGHT_PURPLE;
				//	else
				//		if(modulo == 1)
				//			clr = LIGHT_RED;
				//		else
				//			if (modulo == 0)
				//				clr = LIGHT_GREEN;
				//v2 
				if(modulo == 1)
					clr = LIGHT_YELLOW;
				else
					clr = LIGHT_RED;


				WarningDrawerList::Add(true, clr);
				ev_MultiColorWarnings.Advance(4000); break;	// all the colors

			case 2:
				Ev_Speeding_Up();
				WarningDrawerList::Add(false, WHITE);
				WarningDrawerList::Add(false, WHITE);
				ev_MultiColorWarnings.Cancel();
				break;
			}
		}
}

void WarningDrawerList::Remove_All()
{
	for (int i = 0; i < MAX_WAR_DRAWERS; i++)		// ALL SHALL BE DELETED
		drawer[i] = {};
	total = 0;
}


void WarningDrawerList::Remove(int index)	// On delete rien au final
{
	for (int i = index; i < total; i++)		// Décale tout
		drawer[i] = drawer[i + 1];

	if (!--total)
		ev_DrawWarnings.Cancel();
}

bool WarningDrawerList::Add(bool dr_Er, Colors clr, int speed)		// Ajoute un drawer à la liste
{
	static WarningDrawer tempDrawer = {};

	if (total < MAX_WAR_DRAWERS)
	{
		tempDrawer.dr_Er = dr_Er;
		tempDrawer.clr = clr;
		tempDrawer.timer.Start_Timer(speed, numWarnings);		// First step de l'animation

		drawer[total] = tempDrawer;
		total++;

		if (!ev_DrawWarnings.Is_Active())	// start l'event qui draw
			Ev_Draw_Warnings();

		return true;
	}
	else
		return false;
}



//
//
//void Ev_Dr_Warning()			// DRAW
//{
//	static int step;
//	static Colors clr = WHITE;
//	if (!ev_Dr_Warning.Is_Active())
//	{
//
//		step = 0;
//		ev_Dr_Warning.Activate();
//		ev_Dr_Warning.Start(10000, numWarnings);
//	}
//	else
//	{
//		while (ev_Dr_Warning.delay.Tick())
//		{
//			Set_Ori(true, true);
//			ori.y = ori.y + (step * YBtw);	// ceci va faire starter en haut
//			Dr_Warning(clr);
//
//			Set_Ori(false, false);
//			ori.y -= (step * YBtw);	// ceci va faire starter en bas
//			Dr_Warning(clr);
//			step++;
//			ev_Dr_Warning.Advance(0);
//		}
//	}
//}
//
//
//void Ev_Er_Warning()			// ERASE
//{
//	static int step;
//	static Colors clr = WHITE;
//	if (!ev_Er_Warning.Is_Active())
//	{
//		step = 0;
//		ev_Er_Warning.Activate();
//		ev_Er_Warning.Start(10000, numWarnings);
//	}
//	else
//	{
//		while (ev_Er_Warning.delay.Tick())
//		{
//			Set_Ori(true, true);
//			ori.y = ori.y + (step * YBtw);	// ceci va faire starter en haut
//			Dr_Warning(clr);
//
//			Set_Ori(false, false);
//			ori.y -= (step * YBtw);	// ceci va faire starter en bas
//			Dr_Warning(clr);
//			step++;
//			ev_Er_Warning.Advance(0);
//		}
//	}
//
//}