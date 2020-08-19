#include "ev_back_to_menu.h"

#include "../../UI/map.h"
#include "../../UI/console_output/render_list.h"
#include "../events.h"
#include "../msg_dispatcher.h"
#include "../../lvls/lvl_script.h"
#include "../../inputs/action_input.h"
#include "clear_all_states.h"
#include "../../time/timerOP.h"

void Go_Back_To_Menu()	// Stop la game et on va au main menu
{
	// Reset all
	Clear_All_States();
	gCurrentLevel = 0;
	gCurrentStage = 0;
	gMenuInputs = true;
	clrscr();
	MsgQueue::Register(PLS_INTIALIZE_LVL);	// here we go
}