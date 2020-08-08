
#include "ev_lvl_start_warning.h"


#include "../../player/player.h"
#include "../msg_dispatcher.h"
#include "../events.h"
#include "../../UI/console_output/render_list.h"
#include "../../grid/AllGrids.h"
#include "../../UI/console_output/dsp_string.h"
#include "ev_update_heart.h"

static Coord crd;
static Coord ori;		// Coordonnée d'origine, servira de référence pour TOUT les affichages
static Event ev_LvlStartWarning(Ev_Lvl_Start_Warning, 6);
static std::string ready = "Prepare Yourself";
static std::string inc = "They Are Coming";

static int stringProgress;

void Ev_Lvl_Start_Warning()		 // Affiche le coueur à ses différents stades
{
	if (!ev_LvlStartWarning.Is_Active())
	{
		// initialisation, la console doit être setté pour utiliser ça
		ori.x = Find_Ctr_X((int)ready.size());			// L'afficahge du coeur se fera à partir d'un point central, situé en plein milieu de la fenêtre windows
		ori.y = linkGrid->Get_Rows();
		crd = ori;
		stringProgress = 0;

		ev_LvlStartWarning.Activate();
		ev_LvlStartWarning.Start(10000, (int)ready.size());
	}
	else
		while (ev_LvlStartWarning.delay.Tick())
		{
			switch (ev_LvlStartWarning.Get_Current_Step())
			{
			case 1:			
				ConsoleRender::Add_Char(crd, ready[stringProgress]);
				stringProgress++;	// avance d'un char			
				crd.x++;	// avance d'un char
				ev_LvlStartWarning.Advance(500);
				break;

			case 2:
				stringProgress = 0;
				crd = ori;
				ev_LvlStartWarning.Advance(10000, (int)inc.size());
				break;

			case 3:
				ConsoleRender::Add_Char({ crd.x , crd.y +2  }, inc[stringProgress]);
				stringProgress++;	// avance d'un char
				crd.x++;	// avance d'un char
				ev_LvlStartWarning.Advance(600);
				break;

			case 4:
				MsgQueue::Register(SPAWN_PLAYER);
				ev_LvlStartWarning.Advance(600);
				break;

			case 5:
				Ev_Dr_Heart_3();	// affiche le coeur
				ConsoleRender::Add_String(ready, ori, WHITE,50, true);
				ConsoleRender::Add_String(inc, { ori.x, ori.y + 2 }, WHITE,50, true);
				ev_LvlStartWarning.Advance(200);
				break;

			case 6:
				MsgQueue::Register(STAGE_ADVANCE); // Here they come baby
				ev_LvlStartWarning.Advance(0);
				break;
			}
		}
}