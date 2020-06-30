
#include "ev_change_window.h"

#include "../../../console/sweet_cmd_console.h"



void OBS_Change_Window()
{

	ev_ChangeWindow.Activate();

}

static void EV_Change_Window()	// da event
{

	//Center_WND();
	//EV_ChangeWindow.Deactivate();
}


Event ev_ChangeWindow(EV_Change_Window);