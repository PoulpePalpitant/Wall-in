
#include "ev_glitch_screen.h"

#include "../../../UI/console_output/render_list.h"
#include "../../../console/sweet_cmd_console.h"
#include "../../../events/events.h"
#include "../../../events/msg_dispatcher.h"
#include "../../../math/manage_interval.h"
#include "../../../UI/map.h"
#include "../../../events/global_events/feedback/ev_draw_map.h"

static int numChars; // Nombre de char pour fill l'écran

static Event ev_GlitchMap(Ev_Glitch_Map_Retry, 4);	// l'event
static Intervals::ManageIntervalLists charToDr(0, 0, 0);	// Liste de tout les charactères de la console qui n'ont pas été remplis 
static Intervals::ManageIntervalLists charToEr(0, 0, 0);	// Liste de tout les charactères de la console qui n'ont pas été remplis 
static int speedDr, speedEr;
static std::string retry = "[- Retry -]";
static Coord crd;	// random crd
static Colors clr;

void Ev_Dr_Glitch_Map();			//  Remplis la screen de char cool pendant un bref instant
void Ev_Er_Glitch_Map();			//  Remplis la screen de char cool pendant un bref instant

// Ne pas bouger lol
static Event ev_Dr_GlitchMap(Ev_Dr_Glitch_Map);	// l'event
static Event ev_Er_GlitchMap(Ev_Er_Glitch_Map);	// l'event

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Set_Screen_Filler(bool erase, int speed, Colors color)
{
	Intervals::ManageIntervalLists* list;

	if (erase)
	{
		list = &charToEr;
		speedEr = speed;
	}
	else
	{
		list = &charToDr;
		speedDr = speed;
		clr = color;
	}

		list->Resize(gConWidth, 0, gConHeight);

	// Fill uniquement la box maintenant
	// Exclut côté gauche
	for (int row = 0; row < map.Get_Box_Limit(LEFT); row++)
		list->Empty_List(row);
	// Exclut côté droit
	for (int row = map.Get_Box_Limit(RIGHT) + 1; row < gConWidth; row++)
		list->Empty_List(row);
	// Exclut côté up
	for (int col = 0; col < map.Get_Box_Limit(UP); col++)
		list->Remove_Value_Everywhere(col);
	// Exclut côté droit
	for (int col = map.Get_Box_Limit(DOWN) + 1; col < gConHeight; col++)
		list->Remove_Value_Everywhere(col);
}
//
// void Fill_Screen_Randomly(int amount)
//{
//	static Colors clr;
//
//	Set_Screen_Filler();
//
//	for (int i = 0; i < amount; i++)
//	{
//		//switch (i % 7)
//		//{
//		//case 0:	clr = WHITE; break;
//		//case 1:	clr = GRAY; break;
//		//case 2:	clr = RED; break;
//		//case 3:	clr = LIGHT_RED; break;
//		//case 4:	clr = LIGHT_RED; break;
//		//case 5:	clr = YELLOW; break;
//		//case 6:	clr = LIGHT_YELLOW; break;
//		//}
//		charToDr.Pick_From_Lists(crd.x, crd.y, true, true, Intervals::RDM_ALL);	// pogne une coord random
//		ConsoleRender::Add_Char(crd, COOL_CHARS[rand() % NUM_COOL_CHARS], clr);
//	}
//}

 void Fill(bool erase)
 {
	 if (erase)
	 {
		 charToEr.Pick_From_Lists(crd.x, crd.y, true, true, Intervals::RDM_ALL);	// pogne une coord random
		ConsoleRender::Add_Char(crd, TXT_CONST.SPACE);	// efface

	 }
	 else
	 {
		 charToDr.Pick_From_Lists(crd.x, crd.y, true, true, Intervals::RDM_ALL);	// pogne une coord random
		 ConsoleRender::Add_Char(crd, COOL_CHARS[rand() % NUM_COOL_CHARS], clr); // affiche
	 }
 }


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///  V2 - Je vais séparer le erase du draw, et crisse ça dans un event périodique
void Ev_Dr_Glitch_Map()			//  Remplis la screen de char cool pendant un bref instant
{
	if (!ev_Dr_GlitchMap.Is_Active())
	{
		ev_Dr_GlitchMap.Activate();
		ev_Dr_GlitchMap.Start(0);
		ev_Dr_GlitchMap.delay.Start_Timer(speedDr, 1 , true);
	}
	else
	{
		while (ev_Dr_GlitchMap.delay.Tick())
		{
			if (!charToDr.Is_All_Empty())
				Fill(false);
			else
				ev_Dr_GlitchMap.Cancel();
		}
	}
}

// ERASE
void Ev_Er_Glitch_Map()			//  R//  Erase la map rapidement
{
	if (!ev_Er_GlitchMap.Is_Active())
	{
		//Set_Screen_Filler(true);
		ev_Er_GlitchMap.Activate();
		ev_Er_GlitchMap.Start(0);
		ev_Er_GlitchMap.delay.Start_Timer(speedEr, 1, true);
	}
	else
	{
		while (ev_Er_GlitchMap.delay.Tick())
		{
			if (!charToEr.Is_All_Empty())
				Fill(true);
			else
				ev_Er_GlitchMap.Cancel();
		}
	}
}


void Set_Custom_Glitch_Map_Ev(bool erase, int speed, Colors clr) // Est utilisé pour setté un des event de glitch map
{
	Set_Screen_Filler(erase, speed, clr);	// Il fuadra utilisé qu'une seul itération de ces deux events à la fois, je crois

	if (erase)
		Ev_Er_Glitch_Map();
	else
		Ev_Dr_Glitch_Map();
}


void Ev_Glitch_Map_Retry()			//  Remplis la screen de char cool pendant un bref instant
{
	if (!ev_GlitchMap.Is_Active())
	{
		Set_Custom_Glitch_Map_Ev(false);	// nombre de char à fill);		// Fait glitché l'écran rapidement
		ev_GlitchMap.Activate();
		ev_GlitchMap.Start(0);
		ev_GlitchMap.delay.Start_Timer(10000, 1, true);
	}
	else
	{
		while (ev_GlitchMap.delay.Tick())
		{
			switch (ev_GlitchMap.Get_Current_Step())
			{
			case 1:
				if (!ev_Dr_GlitchMap.Is_Active())
				{
					ConsoleRender::Add_String(retry, { map.Get_Box_Limit(LEFT) + map.Get_Length() / 2 - (int)retry.size() / 2 , map.Get_Box_Limit(UP) + map.Get_Height() / 2 }, LIGHT_RED, 400);
					ev_GlitchMap.delay.Stop();
					ev_GlitchMap.Advance(500);
				}
				break;

			case 2:
				Set_Custom_Glitch_Map_Ev(true);	// Efface l'écran
				ev_GlitchMap.Advance(0);
				ev_GlitchMap.delay.Start_Timer(10000, 1, true);
				break;

			case 3:
				if (!ev_Er_GlitchMap.Is_Active())
				{
					ev_GlitchMap.delay.Stop();
					ev_GlitchMap.Advance(2000);
				}
				break;

			case 4:
				clrscr();					// Clear l'écran au grand complet
				ev_GlitchMap.Advance(1000);	// Tu vas devoir réaffiché tout ce qui était affiché avant cette fonction
				break;
			}
		}
	}
}
