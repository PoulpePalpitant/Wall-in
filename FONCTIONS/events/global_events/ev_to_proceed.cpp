#include "ev_to_proceed.h"

#include "../../UI/map.h"
#include "../../UI/console_output/render_list.h"
#include "../../console/sweet_cmd_console.h"
#include "../../inputs/action_input.h"

static std::string proceed[3] = { "Press \"Enter\" to Proceed","Press \"Enter\" to Start Level", "Press \"Enter\" to Retry" };

void Press_X_To_Proceed(int action, bool cancel)	// Active ou désactive le proceed time
{
	if (cancel)
	{
		gProceedTime = false;	// prend le plus long text à effacer
		ConsoleRender::Add_String(proceed[1], { Find_Ctr_X((int)std::size(proceed[action])),gConHeight - 1 }, WHITE, true);
	}
	else
	{
		gProceedTime = true;
		ConsoleRender::Add_String(proceed[action], { Find_Ctr_X((int)std::size(proceed[action])),gConHeight - 1 }, GRAY);
	}
}