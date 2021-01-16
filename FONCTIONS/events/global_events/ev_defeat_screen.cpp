
#include "ev_defeat_screen.h"

#include "../msg_dispatcher.h"
#include "../events.h"
#include "../../UI/console_output/render_list.h"

#include "../../grid/AllGrids.h"
#include "../../lvls/lvl_script.h"
#include "../../structure_manager/structure_manager.h"
#include "../../player/player.h"
#include "ev_to_proceed.h"
#include "feedback/ev_glitch_screen.h"
#include "../../bots/botlist.h"
#include "clear_all_states.h"
#include "ev_update_heart.h"

static Event ev_SlowDefeatScreen(Ev_Slow_Defeat_Screen, 4);
static Event ev_FastDefeatScreen(Ev_Fast_Defeat_Screen, 4);

static Coord xy;
static Coord ori;		// Coordonnée d'origine, servira de référence pour TOUT les affichages
static Colors fillClr[2];	// Fait flasher le coueur d'une certaine couleur la première est blanche, l'autre représente la couleur du coeur
static const int DFLT_FAST_SPEED[2] = {300000, 100000};	// same logic 
static const int DFLT_SLOW_SPEED[2] = {60000, 42000};	// same logic 
static std::string tip = "Tip: ";
static std::string tips[] = { "Never Stop Building", "Speed Is Key", "Shooting From Afar Is Slower", "" };

static std::string dead[] = { "EMPLOYEE TERMINATED","YOU LOST", "DEFEAT", "NOT VICTORIOUS", "OVERWHELMED" };
static std::string retry = "Be Replaced?";
static std::string retry2 = "(Press 'R' To Retry, Anytime)";

const int NUM_RESTART_STR = 17;
static std::string restart[NUM_RESTART_STR] = { " - I CAN DO BETTER -", "- A MINOR SETBACK -", "- I KNOW WHAT DO TO -", "- THIS IS NOT THE END -", "- LET'S GO -", "- JUST A MISTAKE -",
"- I WAS ALMOST THERE! -","- I CAN DO THIS -", "- I SLIPPED -", "- THAT WON'T STOP ME -", "- FAILURE IS A LESSON -","- I WON'T GIVE UP -", "- AND SO I LEARNED, I THINK... -",
"- LET'S RETRY -", "- I MUST TRY HARDER -", "- GETTING BETTER -", "- I WON'T BE DEFEATED -"};

// Comment faire du ascii art
//static const std::string heart_3[] = {};
//static const std::string heart_2[] = {};
//static const std::string heart_1[] = {};
//static const std::string* allHearts[3] = { heart_1, heart_2, heart_3 };	// all of the hearts

// CHOIX DE DESIGN
// . . .

void Ev_Slow_Defeat_Screen()				 // Affiche un écran punitif
{
	if (!ev_SlowDefeatScreen.Is_Active())
	{
		// La console doit être setté pour utiliser ça
		ori.x = Find_Ctr_Grid(dead[0]);
		ori.y = linkGrid->link[0][linkGrid->Get_Rows() / 2].Get_XY().y -6;

		// refresh all
		Clear_All_States();
		gSkipStory = gDayStarted = true;	// Devient faux dans clr state :(
		ev_SlowDefeatScreen.Activate();
		ev_SlowDefeatScreen.Start(0);
	}
	else
		while (ev_SlowDefeatScreen.delay.Tick())
		{
			switch (ev_SlowDefeatScreen.Get_Current_Step())
			{
			case 1:
					Set_Custom_Glitch_Map_Ev(false, 1900000); // pour remplir l'écran de petits char cool

				Start_Ev_Dr_Heart(0);		 // Setup l'event Précédent
				ev_SlowDefeatScreen.Advance(500);
				break;

			case 2: // tit break
				ConsoleRender::Add_String(dead[0], ori, LIGHT_RED);
				ev_SlowDefeatScreen.Advance(700);
				break;

			case 3:
				ConsoleRender::Add_String(retry, { Find_Ctr_Grid(retry), ori.y + 2 }, LIGHT_RED, TXT_SPD_DR / 3);
				ev_SlowDefeatScreen.Advance(2000);
				break;

			case 4:
				gSkipStory = true;	// we go fast				
				Press_X_To_Proceed(2);	// press x to retry
				Press_R_To_Refresh(1);	// press x to retry
				gRetryCheckpoint = true;
				ev_SlowDefeatScreen.Advance(1000);
				break;

			}
		}
}


void Ev_Fast_Defeat_Screen()				 // Prompt le joueur à restart!
{
	static int restartString;	// L'index correspondant au string dans l'array restart[] 

	if (!ev_FastDefeatScreen.Is_Active())
	{
		// La console doit être setté pour utiliser ça
		restartString = rand() % NUM_RESTART_STR;
		ori.x = Find_Ctr_Grid(restart[restartString]);
		ori.y = linkGrid->link[0][linkGrid->Get_Rows() / 2].Get_XY().y - 6;

		// refresh all
		Clear_All_States();
		gSkipStory = gDayStarted = true;	// Devient faux dans clr state :(
		ev_FastDefeatScreen.Activate();
		ev_FastDefeatScreen.Start(0);
	}
	else
		while (ev_FastDefeatScreen.delay.Tick())
		{
			switch (ev_FastDefeatScreen.Get_Current_Step())
			{
			case 1:
				if(gCurrentLevel == 3)
					Set_Custom_Glitch_Map_Ev(false, 30000000); // pour remplir l'écran de petits char cool
				else
					Set_Custom_Glitch_Map_Ev(false, 3000000); // pour remplir l'écran de petits char cool

				Start_Ev_Dr_Heart(0);		 // Setup l'event Précédent
				ev_FastDefeatScreen.Advance(0);
				ev_FastDefeatScreen.delay.Start_Timer(10000, 1, true);
				break;

			case 2: // tit break
				if (Is_Done_Ev_Glitch_Map_Retry())
				{
					ev_FastDefeatScreen.delay.Stop();
					ev_FastDefeatScreen.Advance(1200);
				}
				break;

			case 3:
				ConsoleRender::Add_String(restart[restartString], { Find_Ctr_Grid(restart[restartString]), ori.y }, LIGHT_GREEN, TXT_SPD_FAST / 2);
				ev_FastDefeatScreen.Advance(700);
				break;

			case 4:
				gSkipStory = true;	// we go fast				
				//ConsoleRender::Add_String(retry2, { Find_Ctr_Grid(retry2), ori.y + 1 }, GREEN, TXT_SPD_DR,true);	// erase en haut
				ConsoleRender::Add_String(retry2, { Find_Ctr_Grid(retry2), ori.y + 2 }, GREEN);
				//ConsoleRender::Add_String(retry2, { Find_Ctr_Grid(retry2), ori.y + 3 }, GREEN, TXT_SPD_FAST,true);	// erase en bas, pour rendre le txt plus lisible

				//Press_X_To_Proceed(2);	// press x to go back to menu
				gRetryCheckpoint = true;
				ev_FastDefeatScreen.Advance(1000);
				break;

			}
		}
}
