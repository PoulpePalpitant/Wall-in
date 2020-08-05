
#include "ev_fill_map.h"

#include "../../../UI/console_output/render_list.h"
#include "../../../console/sweet_cmd_console.h"
#include "../../../events/events.h"
#include "../../../events/msg_dispatcher.h"
#include "../../../math/manage_interval.h"
#include "../../../UI/map.h"
#include "../../../events/global_events/feedback/ev_draw_map.h"


const int NUM_COOL_CHARS = 23;
const int NUM_RECT_CHARS = 7;
const int COOL_CHARS[NUM_COOL_CHARS] = { 170,193,196,197,194,191,192,195,213,217,218,201,204,200,203,206,205,202,187,186,240,238,242 };
const int RECT_CHARS[NUM_RECT_CHARS] = { 176,178,177,220,219,223,254 };
static int numChars; // Nombre de char pour fill l'�cran

static Event ev_FillMap(Ev_Fill_Map, 8);	// l'event

static Coord crd;	// random crd
static Intervals::ManageIntervalLists charToFill(0, 0, 0);	// Liste de tout les charact�res de la console qui n'ont pas �t� remplis 

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void Set_Screen_Filler()
{
	charToFill.Resize(gConWidth, 0, gConHeight);

	// Fill uniquement la box maintenant
	// Exclut c�t� gauche
	for (int row = 0; row < map.Get_Box_Limit(LEFT); row++)
		charToFill.Empty_List(row);
	// Exclut c�t� droit
	for (int row = map.Get_Box_Limit(RIGHT) + 1; row < gConWidth; row++)
		charToFill.Empty_List(row);
	// Exclut c�t� up
	for (int col = 0; col < map.Get_Box_Limit(UP); col++)
		charToFill.Remove_Value_Everywhere(col);
	// Exclut c�t� droit
	for (int col = map.Get_Box_Limit(DOWN) + 1; col < gConHeight; col++)
		charToFill.Remove_Value_Everywhere(col);
}

static void Fill_Screen_Randomly(bool erase = false)
{
	charToFill.Pick_From_Lists(crd.x, crd.y, true, true, Intervals::RDM_ALL);	// pogne une coord random

	if (erase)
		ConsoleRender::Add_Char(crd, TXT_CONST.SPACE);	// blakc
	else
		//ConsoleRender::Add_Char(crd, TXT_CONST.SPACE_FILL);	// pour l'instant c'est blanc
		ConsoleRender::Add_Char(crd, COOL_CHARS[rand() % NUM_COOL_CHARS], GRAY);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Ev_Fill_Map()			//  Fill la map de charact�re cools, delete ensuite tout 
{
	if (!ev_FillMap.Is_Active())
	{
		numChars = (map.Get_Length()) * (map.Get_Height());	// nombre de char � fill
		ev_FillMap.Activate();
		ev_FillMap.Start(200);
	}
	else
	{
		while (ev_FillMap.delay.Tick())
		{
			switch (ev_FillMap.Get_Current_Step())
			{
			case 1:
				Set_Screen_Filler();	// test le screen fill
				ev_FillMap.Advance(50000000, numChars);

			case 2:
				Fill_Screen_Randomly();	// Remplis la console d'un charact�re blanc � la fois
				ev_FillMap.Advance(2000);
				break;

			case 3:
				Just_Dr_Map_Borders();
				ev_FillMap.Advance(1000);
				break;

			case 4:
				// Pause Pour afficher Le titre
				Set_Screen_Filler();
				ev_FillMap.Advance(300);
				break;

			case 5:
				ev_FillMap.Advance(10000000, numChars * 2);
				break;

			case 6:
				Fill_Screen_Randomly(true);	// Efface le fill
				ev_FillMap.Advance(600);
				break;

			case 7:
				clrscr();
				ev_FillMap.Advance(300);
				break;

			case 8:
				ev_FillMap.Advance(0);
				break;
			}
		}
	}
}

