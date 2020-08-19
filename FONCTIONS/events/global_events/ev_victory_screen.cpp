
#include "ev_victory_screen.h"

#include "../msg_dispatcher.h"
#include "../events.h"
#include "../../UI/console_output/render_list.h"

#include "../../grid/AllGrids.h"
#include "../../lvls/lvl_script.h"
#include "../../structure_manager/structure_manager.h"
#include "../../player/player.h"
#include "ev_to_proceed.h"

static Event ev_VictoryScreen(Ev_Victory_Screen, 5);

static Coord xy;
static Coord ori;		// Coordonnée d'origine, servira de référence pour TOUT les affichages
static Colors fillClr[2];	// Fait flasher le coueur d'une certaine couleur la première est blanche, l'autre représente la couleur du coeur
static const int DFLT_FAST_SPEED[2] = {300000, 100000};	// same logic 
static const int DFLT_SLOW_SPEED[2] = {60000, 42000};	// same logic 

static std::string GG_1 = "- YOU HAVE SURVIVED -";

// Comment faire du ascii art
//static const std::string heart_3[] = {};
//static const std::string heart_2[] = {};
//static const std::string heart_1[] = {};
//static const std::string* allHearts[3] = { heart_1, heart_2, heart_3 };	// all of the hearts

// CHOIX DE DESIGN
// . . .

 void Ev_Victory_Screen()				 // Affiche un écran qui gratifiant		 // Affiche le coueur à ses différents stades
{
	if (!ev_VictoryScreen.Is_Active())
	{
		// La console doit être setté pour utiliser ça
		ori.x = Find_Ctr_X() - 8;		// L'afficahge du coeur se fera à partir d'un point central, situé en plein milieu de la fenêtre windows
		ori.y = linkGrid->link[0][linkGrid->Get_Rows() / 2].Get_XY().y;

		MsgQueue::Register(LOCK_PLAYER);
		ev_VictoryScreen.Activate();
		ev_VictoryScreen.Start(1000);
	}
	else
		while (ev_VictoryScreen.delay.Tick())
		{
			switch (ev_VictoryScreen.Get_Current_Step())
			{
			case 1:
				//ListsOfChainToModify::Annihilate_All_Links();
				//P1.Er_Player(); // efface joueur
				ev_VictoryScreen.Advance(5000);
				break;

			case 2: // tit break
				ev_VictoryScreen.Advance(5000);
				break;

			case 3:
				ConsoleRender::Add_String(GG_1, ori, LIGHT_GREEN, 450);
				ev_VictoryScreen.Advance(200); 
				break;

			case 4:
				Press_X_To_Proceed(0);
				ev_VictoryScreen.Advance(200); 
				break;

			case 5:
				ev_VictoryScreen.Advance(300); 
				break;
			}
		}
}
