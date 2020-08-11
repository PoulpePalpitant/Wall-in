
#include "ev_glitch_screen.h"

#include "../../../UI/console_output/render_list.h"
#include "../../../console/sweet_cmd_console.h"
#include "../../../events/events.h"
#include "../../../events/msg_dispatcher.h"
#include "../../../math/manage_interval.h"
#include "../../../UI/map.h"
#include "../../../events/global_events/feedback/ev_draw_map.h"

static int numChars; // Nombre de char pour fill l'écran

static Event ev_GlitchScreen(Ev_Glitch_Screen, 4);	// l'event
static Coord crd;	// random crd
static Intervals::ManageIntervalLists charToFill(0, 0, 0);	// Liste de tout les charactères de la console qui n'ont pas été remplis 

static std::string retry = "[- Retry -]";
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void Set_Screen_Filler()
{
	charToFill.Resize(gConWidth, 0, gConHeight);

	// Fill uniquement la box maintenant
	// Exclut côté gauche
	for (int row = 0; row < map.Get_Box_Limit(LEFT); row++)
		charToFill.Empty_List(row);
	// Exclut côté droit
	for (int row = map.Get_Box_Limit(RIGHT) + 1; row < gConWidth; row++)
		charToFill.Empty_List(row);
	// Exclut côté up
	for (int col = 0; col < map.Get_Box_Limit(UP); col++)
		charToFill.Remove_Value_Everywhere(col);
	// Exclut côté droit
	for (int col = map.Get_Box_Limit(DOWN) + 1; col < gConHeight; col++)
		charToFill.Remove_Value_Everywhere(col);
}

static void Fill_Screen_Randomly(int amount)
{
	static Colors clr;
	for (int i = 0; i < amount; i++)
	{
		//switch (i % 7)
		//{
		//case 0:	clr = WHITE; break;
		//case 1:	clr = GRAY; break;
		//case 2:	clr = RED; break;
		//case 3:	clr = LIGHT_RED; break;
		//case 4:	clr = LIGHT_RED; break;
		//case 5:	clr = YELLOW; break;
		//case 6:	clr = LIGHT_YELLOW; break;
		//}
		charToFill.Pick_From_Lists(crd.x, crd.y, true, true, Intervals::RDM_ALL);	// pogne une coord random
		ConsoleRender::Add_Char(crd, COOL_CHARS[rand() % NUM_COOL_CHARS], GRAY);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Ev_Glitch_Screen()			//  Remplis la screen de char cool pendant un bref instant
{
	if (!ev_GlitchScreen.Is_Active())
	{
		charToFill.Resize(gConWidth, 0, gConHeight);
		Set_Screen_Filler();
		ev_GlitchScreen.Activate();
		ev_GlitchScreen.Start(0);
	}
	else
	{
		while (ev_GlitchScreen.delay.Tick())
		{
			switch (ev_GlitchScreen.Get_Current_Step())
			{
			case 1:
				Fill_Screen_Randomly(map.Get_Length() * map.Get_Height());	// nombre de char à fill);		// Fait glitché l'écran rapidement
				ev_GlitchScreen.Advance(0);
				break;

			case 2:
				ConsoleRender::Add_String(retry,  { map.Get_Box_Limit(LEFT) + map.Get_Length() / 2 - (int)retry.size()/ 2 , map.Get_Box_Limit(UP) + map.Get_Height() / 2}, LIGHT_RED, 400);
				ev_GlitchScreen.Advance(500);
				break;
				
			case 3:
				Set_Screen_Filler();
				Fill_Screen_Randomly(map.Get_Length() * map.Get_Height());	// nombre de char à fill);		// Fait glitché l'écran rapidement
				ev_GlitchScreen.Advance(0);
				break;

			case 4:
				clrscr();					// Clear l'écran au grand complet
				ev_GlitchScreen.Advance(0);	// Tu vas devoir réaffiché tout ce qui était affiché avant cette fonction
				break;
			}
		}
	}
}

