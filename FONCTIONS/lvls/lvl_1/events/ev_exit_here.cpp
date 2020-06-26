

#include "ev_exit_here.h"

#include "../../lvl_script.h"
#include "../../../events/events.h"
#include "../../../grid/AllGrids.h"
#include "../../../UI/console_output/render_list.h"

static CDTimer timer;	// Pour délay l'event and shit
static Event Ev_BaitToExit(Ev_Bait_To_Exit);

void Ev_Bait_To_Exit()// Trace un chemin vers une fausse porte de sortie
{
	if (!Ev_BaitToExit.Is_Active())
	{
		if (gCurrentStage == 1)
		{
			Ev_BaitToExit.Activate();
			timer.Set_Cd_Duration(2000);
		}
	}
	else	// doin stuff 
	{
		if (timer.Get_Time_Left() <= 0)
		{
			if (!Ev_BaitToExit.Get_Current_Step())	// STEP 0
			{
				GrdCoord start;
				Coord pos;			// position en xy

				start = { linkGrid->Get_Cols() / 2 + 2,linkGrid->Get_Rows() / 2 };	// Position dans le grid du premier point
				pos = linkGrid->link[start.c][start.r].Get_XY();					// premier point

				ConsoleRender::Create_Queue(50);

				for (int i = 0; i < 10; i++)
				{
					ConsoleRender::Add_Char_To_Render_List(pos, 250);
					pos.x += DELTA_X;	// Fait un bond sur le grid :)
				}

				pos.y -= DELTA_Y;
				ConsoleRender::Add_Char_To_Render_List(pos, 250);	// remonte
				pos.y -= 2;
				ConsoleRender::Add_Char_To_Render_List(pos, 127, BRIGHT_WHITE);	// EXIT symbole
				ConsoleRender::Stop_Queue();
				pos.y -= 2;
				ConsoleRender::Add_String_To_Render_List("Exit", pos, LIGHT_YELLOW, 70);

				Ev_BaitToExit.Advance();
				timer.Set_Cd_Duration(1000);	// Délay séparant le prochain step
			}
			else
				if (Ev_BaitToExit.Get_Current_Step() == 1)
				{

					/* stuff à faire durant la deuxième étape*/

				}
		}
		else
			timer.Tick_Timer();

		// Reveal that there is no exit
		if(Ev_BaitToExit.Stop_If_No_More_Steps())
			Ev_BaitToExit.Deactivate();
	}
}

