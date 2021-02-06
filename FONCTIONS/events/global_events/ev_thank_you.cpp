
#include "ev_thank_you.h"

#include "../msg_dispatcher.h"
#include "../events.h"
#include "../../UI/console_output/render_list.h"

#include "../../grid/AllGrids.h"
#include "../../lvls/lvl_script.h"
#include "../../math/manage_interval.h" 
#include "../../structure_manager/structure_manager.h"
#include "../../player/player.h"
#include "ev_to_proceed.h"
#include "../global_events/clear_all_states.h"
#include "../../time/timerOP.h"
#include "ev_back_to_menu.h"
#include "ev_to_proceed.h"
#include "../../events/global_events/ev_spwn_player.h"
#include "feedback/ev_good_job.h"



static Event ev_ThksForPlaying(Ev_Thks_For_Playing, 5);

static int y;

static std::string grats = "You are a true Winner! ";
static std::string ty = "Thank you so much for playing!";

void Ev_Thks_For_Playing()	
{
	if (!ev_ThksForPlaying.Is_Active())
	{
		y = 33;
		clrscr();
		Event::Cancel_All();		// Tout les events
		ConsoleRender::Add_String(grats, { Find_Ctr_String_X(grats),y}, BRIGHT_WHITE, TXT_SPD_DR * .75);
		Ev_GG();		

		ev_ThksForPlaying.Activate();
		ev_ThksForPlaying.Start(300);
	}
	else
		while (ev_ThksForPlaying.delay.Tick())
		{
			switch (ev_ThksForPlaying.Get_Current_Step())
			{
			case 1:
				ConsoleRender::Add_String(ty, { Find_Ctr_String_X(ty), y + 2 }, BRIGHT_WHITE, TXT_SPD_DR);
				ev_ThksForPlaying.Advance(500);
				break;

			case 2:
				ev_ThksForPlaying.Advance(1000);
				break;

			case 3:
				gCurrentStage++;
				Press_X_To_Proceed();
			}
		}
}
