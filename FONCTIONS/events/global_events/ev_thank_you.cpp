
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



static Event ev_ThksForPlaying(Ev_Thks_For_Playing,2000);

static int y;

static std::string grats = "You are a true Winner! ";

static std::string paragraph[] = 
{ "You saved the universe,",
"became king of the world,",
"and achieved eternal happiness n'shit.",
 "You are a true Winner!"
 };
static std::string ty = "Thank you so much for playing!";

static std::string tyTesters = "Un \202nomre MERCI \205 mes testeurs, je vous dois tous une bi\212re :P ";
static std::string testersName[] = 
{ "Charles Paris\202",
"\220tienne Montreuil",
"Marc-Andr\202 de Launi\212re",
"\220mile Laforce"};
void Ev_Thks_For_Playing()	
{
	if (!ev_ThksForPlaying.Is_Active())
	{
		y = 33;
		clrscr();
		Event::Cancel_All();		// Tout les events
		
		Ev_GG();		

		ev_ThksForPlaying.Activate();
		ev_ThksForPlaying.Start(500);
	}
	else
		while (ev_ThksForPlaying.delay.Tick())
		{
			switch (ev_ThksForPlaying.Get_Current_Step())
			{
			case 1:
				ConsoleRender::Add_String(paragraph[0], { Find_Ctr_String_X(paragraph[0]),y }, BRIGHT_WHITE, TXT_SPD_DR * .75);
				ev_ThksForPlaying.Advance(500);
				break;

			case 2:
				ConsoleRender::Add_String(paragraph[1], { Find_Ctr_String_X(paragraph[1]),y + 1 }, BRIGHT_WHITE, TXT_SPD_DR * .75);
				ev_ThksForPlaying.Advance(500);
				break;

			case 3:
				ConsoleRender::Add_String(paragraph[2], { Find_Ctr_String_X(paragraph[2]),y + 2 }, BRIGHT_WHITE, TXT_SPD_DR * .75);
				ev_ThksForPlaying.Advance(400);
				break;

			case 4:
				ConsoleRender::Add_String(paragraph[3], { Find_Ctr_String_X(paragraph[3]),y + 5 }, LIGHT_GREEN, TXT_SPD_DR * .75);
				ev_ThksForPlaying.Advance(300);
				break;

			case 5:
				ConsoleRender::Add_String(tyTesters, { Find_Ctr_String_X(tyTesters),y + 8 }, LIGHT_YELLOW, TXT_SPD_DR * .75);
				ev_ThksForPlaying.Advance(300);
				break;
				
			case 6:
				ConsoleRender::Add_String(testersName[0], { Find_Ctr_String_X(testersName[0]) ,y + 11}, BRIGHT_WHITE, TXT_SPD_DR * .75);
				ConsoleRender::Add_String(testersName[1], { Find_Ctr_String_X(testersName[1]) ,y + 13 }, BRIGHT_WHITE, TXT_SPD_DR * .75);
				ConsoleRender::Add_String(testersName[2], { Find_Ctr_String_X(testersName[2]) ,y + 15 }, BRIGHT_WHITE, TXT_SPD_DR * .75);
				ConsoleRender::Add_String(testersName[3], { Find_Ctr_String_X(testersName[3]) ,y + 17 }, BRIGHT_WHITE, TXT_SPD_DR * .75);
				ev_ThksForPlaying.Advance(300);
				break;

			case 7:
				gCurrentStage++;
				Press_X_To_Proceed();


				ConsoleRender::Add_String(ty, { Find_Ctr_String_X(ty),y + 24 }, LIGHT_AQUA, TXT_SPD_DR * .75);
				ev_ThksForPlaying.Advance(500);
				break;

			}
		}
}
