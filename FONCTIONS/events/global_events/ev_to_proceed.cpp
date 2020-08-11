#include "ev_to_proceed.h"

#include "../../UI/map.h"
#include "../../UI/console_output/render_list.h"
#include "../../console/sweet_cmd_console.h"
#include "../../inputs/action_input.h"

static std::string proceed = "Press \"Esc\" to Proceed";
static std::string lvl = "Press \"Esc\" to Sart Level";

void Press_X_To_Proceed(bool startLvl)
{
	gProceedTime = true;
	
	if(startLvl)
		ConsoleRender::Add_String(proceed, { Find_Ctr_X((int)std::size(proceed)),gConHeight - 1 } , GRAY); 
	else
		ConsoleRender::Add_String(lvl, { Find_Ctr_X((int)std::size(lvl)),gConHeight - 1 } , GRAY);

}