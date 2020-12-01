#include "ev_to_proceed.h"

#include "../../UI/map.h"
#include "../../UI/console_output/render_list.h"
#include "../../console/sweet_cmd_console.h"
#include "../../inputs/action_input.h"
#include "../../lvls/lvl_script.h"


static std::string proceed[5] = { "Press 'Enter' to Continue", "Press 'Enter' to Start Level", "Press 'Enter' to Start Over","Press 'Enter' To Proceed To The Next Step ",
"Press 'Enter' To Skip Chit Chat" };
static std::string refresh[] = { "Press 'R' To Refresh Stage", "Press 'R' To Retry From CheckPoint" };

void Press_X_To_Proceed(int action, bool cancel)	// Active ou désactive le proceed time
{
	if (cancel)
	{
		gProceedTime = false;	// prend le plus long text à effacer
		ConsoleRender::Add_String(proceed[0], { Find_Ctr_Grid(proceed[action]),gConHeight - 1 }, WHITE, true);
	}
	else
	{
		gProceedTime = true;
		ConsoleRender::Add_String(proceed[action], { Find_Ctr_Grid(proceed[action]),gConHeight - 1 }, GRAY);
	}
}

void Press_R_To_Refresh(int action, bool cancel)	// Active ou désactive le refresher
{
	if (cancel)
	{
		ConsoleRender::Add_String(refresh[action], { Find_Ctr_Grid(refresh[action]),gConHeight - 2 }, WHITE, true);
	}
	else
	{
		ConsoleRender::Add_String(refresh[action], { Find_Ctr_Grid(refresh[action]),gConHeight - 2 }, GREEN);
	}
}


void Press_R_To_Retry_On_Pause(int action, bool cancel)	// Active ou désactive le refresher
{
	if (cancel)
	{
		ConsoleRender::Add_String(refresh[action], { Find_Ctr_X((int)refresh[action].size()) - 1,gConHeight - 1 }, WHITE,0, true);
	}
	else
	{
		ConsoleRender::Add_String(refresh[action], { Find_Ctr_X((int)refresh[action].size()) - 1,gConHeight - 1 }, GREEN);
	}
}