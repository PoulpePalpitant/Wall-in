
#include "ev_lvl_start_warning.h"


#include "../../player/player.h"
#include "../msg_dispatcher.h"
#include "../events.h"
#include "../../UI/console_output/render_list.h"
#include "../../grid/AllGrids.h"
#include "../../UI/console_output/dsp_string.h"
#include "ev_update_heart.h"
#include "ev_progress_bar.h"

static Coord crd;
static Coord ori;		// Coordonn�e d'origine, servira de r�f�rence pour TOUT les affichages
static Event ev_LvlStartWarning(Ev_Lvl_Start_Warning, 7);
static std::string ready = "Prepare Yourself";
static std::string inc = "They Are Coming";

static int stringProgress;

void Ev_Lvl_Start_Warning()		 // Affiche le coueur � ses diff�rents stades
{
	if (!ev_LvlStartWarning.Is_Active())
	{
		// initialisation, la console doit �tre sett� pour utiliser �a
		ori.x = Find_Ctr_Grid(ready);		// L'afficahge du coeur se fera � partir d'un point central, situ� en plein milieu de la fen�tre windows
		ori.y = linkGrid->Get_Rows();
		crd = ori;
		stringProgress = 0;

		ev_LvlStartWarning.Activate();
		ev_LvlStartWarning.Start(40000, (int)ready.size());
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
				ev_LvlStartWarning.Advance(1000);
				break;

			case 2:
				MsgQueue::Register(FREE_PLAYER);
				stringProgress = 0;
				crd = ori;
				ev_LvlStartWarning.Advance(30000, (int)inc.size());
				break;

			case 3:
				ConsoleRender::Add_Char({ crd.x , crd.y +2  }, inc[stringProgress]);
				stringProgress++;	// avance d'un char
				crd.x++;	// avance d'un char
				ev_LvlStartWarning.Advance(1000);
				break;

			case 4:
				ev_LvlStartWarning.Advance(500);
				break;

			case 5:
				ConsoleRender::Add_String(ready, ori, WHITE, TXT_SPD_ER, true);
				ConsoleRender::Add_String(inc, { ori.x, ori.y + 2 }, WHITE, TXT_SPD_ER, true);
				ev_LvlStartWarning.Advance(1000);
				break;

			case 6:
				Ev_Progress_Bar();	// Make that progress bar
				ev_LvlStartWarning.Advance(0);
				break;
			
			case 7:
				MsgQueue::Register(STAGE_ADVANCE); // Here they come baby
				ev_LvlStartWarning.Advance(0);
				break;
			}
		}
}