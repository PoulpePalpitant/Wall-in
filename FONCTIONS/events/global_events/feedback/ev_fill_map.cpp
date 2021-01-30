
#include "ev_fill_map.h"

#include "../../../UI/console_output/render_list.h"
#include "../../../console/sweet_cmd_console.h"
#include "../../../events/events.h"
#include "../../../events/msg_dispatcher.h"
#include "../../../math/manage_interval.h"
#include "../../../UI/map.h"
#include "../../../events/global_events/feedback/ev_draw_map.h"

#include "../../../lvls/lvl_script.h"

static int numChars; // Nombre de char pour fill l'écran
static Event ev_FillMap(Ev_Fill_Map, 8);	// l'event

static Coord crd;	// random crd
static Intervals::ManageIntervalLists charToDr(0, 0, 0);	// Liste de tout les charactères de la console qui n'ont pas été remplis 

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void Set_Screen_Filler()
{
	charToDr.Resize(gConWidth, 0, gConHeight);

	// Fill uniquement la box maintenant
	// Exclut côté gauche
	for (int row = 0; row < map.Get_Box_Limit(LEFT); row++)
		charToDr.Empty_List(row);
	// Exclut côté droit
	for (int row = map.Get_Box_Limit(RIGHT) + 1; row < gConWidth; row++)
		charToDr.Empty_List(row);
	// Exclut côté up
	for (int col = 0; col < map.Get_Box_Limit(UP); col++)
		charToDr.Remove_Value_Everywhere(col);
	// Exclut côté droit
	for (int col = map.Get_Box_Limit(DOWN) + 1; col < gConHeight; col++)
		charToDr.Remove_Value_Everywhere(col);
}

static void Fill_Screen_Randomly(bool erase = false)
{
	charToDr.Pick_From_Lists(crd.x, crd.y, true, true, Intervals::RDM_ALL);	// pogne une coord random

	if (erase)
		ConsoleRender::Add_Char(crd, TXT_CONST.SPACE);	// blakc
	else
		//ConsoleRender::Add_Char(crd, TXT_CONST.SPACE_FILL);	// pour l'instant c'est blanc
		ConsoleRender::Add_Char(crd, COOL_CHARS[rand() % NUM_COOL_CHARS], GRAY);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Ev_Fill_Map()			//  Fill la map de charactère cools, delete ensuite tout 
{
	if (!ev_FillMap.Is_Active())
	{
		numChars = (map.Get_Length()) * (map.Get_Height());	// nombre de char à fill
		ev_FillMap.Activate();
		ev_FillMap.Start(350);
	}
	else
	{
		while (ev_FillMap.delay.Tick())
		{
			switch (ev_FillMap.Get_Current_Step())
			{
			case 1:
				Set_Screen_Filler();	

				if (gCurrentLevel < 3)	// Le lvl 3 est plus fat, donc plus lent à dessiner
				{
					Set_Dr_Map_1(TXT_SPD_FAST * 3, 0);
					ev_FillMap.Advance(2000000, numChars);
				}
				else
				{
					Set_Dr_Map_1(TXT_SPD_FAST * 5, 0);
					ev_FillMap.Advance(7000000, numChars);
				}

			case 2:
				Fill_Screen_Randomly();	// Remplis la console d'un charactère blanc à la fois
				ev_FillMap.Advance(2900);
				break;

			case 3:
				ev_FillMap.Advance(1000);
				break;

			case 4:
				// Pause Pour afficher Le titre
				Set_Screen_Filler();
				if (gCurrentLevel < 3)	// Le lvl 3 est plus fat, donc plus lent à dessiner
					ev_FillMap.Advance(400);
				else
					ev_FillMap.Advance(300);


				break;

			case 5:
				if (gCurrentLevel < 3)
				{
					if (gCurrentLevel == 2)
						Set_Dr_Map_1(TXT_SPD_DR * 8); 

					ev_FillMap.Advance(2000000, numChars * 2);
				}
				else
				{
					Set_Dr_Map_1(TXT_SPD_DR * 12);
					ev_FillMap.Advance(8000000, numChars * 1.4);
				}
				break;

			case 6:
				Fill_Screen_Randomly(true);	// Efface le fill
				ev_FillMap.Advance(0);
				break;

			case 7:
				ev_FillMap.Cancel();
				break;

			}
		}
	}
}

bool Is_Ev_Fill_Map_Active() {
	return ev_FillMap.Is_Active();
}