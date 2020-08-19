
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

static Event ev_DefeatScreen(Ev_Defeat_Screen, 4);

static Coord xy;
static Coord ori;		// Coordonnée d'origine, servira de référence pour TOUT les affichages
static Colors fillClr[2];	// Fait flasher le coueur d'une certaine couleur la première est blanche, l'autre représente la couleur du coeur
static const int DFLT_FAST_SPEED[2] = {300000, 100000};	// same logic 
static const int DFLT_SLOW_SPEED[2] = {60000, 42000};	// same logic 

static std::string dead[] = { "YOU HAVE DIED","YOU LOST", "DEFEAT", "NOT VICTORIOUS" };
static std::string retry = "Retry?";

// Comment faire du ascii art
//static const std::string heart_3[] = {};
//static const std::string heart_2[] = {};
//static const std::string heart_1[] = {};
//static const std::string* allHearts[3] = { heart_1, heart_2, heart_3 };	// all of the hearts

// CHOIX DE DESIGN
// . . .

void Ev_Defeat_Screen()				 // Affiche un écran punitif
{
	if (!ev_DefeatScreen.Is_Active())
	{
		// La console doit être setté pour utiliser ça
		ori.x = Find_Ctr_X() - 8;		// L'afficahge du coeur se fera à partir d'un point central, situé en plein milieu de la fenêtre windows
		ori.y = linkGrid->link[0][linkGrid->Get_Rows() / 2].Get_XY().y -6;

		// refresh all
		Clear_All_States();
		ev_DefeatScreen.Activate();
		ev_DefeatScreen.Start(0);
	}
	else
		while (ev_DefeatScreen.delay.Tick())
		{
			switch (ev_DefeatScreen.Get_Current_Step())
			{
			case 1:
				Set_Custom_Glitch_Map_Ev(false, 1900000); // pour remplir l'écran de petits char cool
				Start_Ev_Dr_Heart(0);		 // Setup l'event Précédent
				ev_DefeatScreen.Advance(300);
				break;

			case 2: // tit break
				ConsoleRender::Add_String(dead[0], ori, LIGHT_RED, 400);
				ev_DefeatScreen.Advance(350);
				break;

			case 3:
				ConsoleRender::Add_String(retry, { ori.x + 4, ori.y + 2 }, LIGHT_RED, 400);
				ev_DefeatScreen.Advance(2000);
				break;

			case 4:
				gSkipStory = true;	// we go fast				
				Press_X_To_Proceed(2);	// press x to retry
				ev_DefeatScreen.Advance(1000);
				break;

			}
		}
}
