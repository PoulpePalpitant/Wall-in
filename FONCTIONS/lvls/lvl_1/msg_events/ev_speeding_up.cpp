
#include "ev_speeding_up.h"

#include "../../../UI/console_output/render_list.h"
#include "../../../console/sweet_cmd_console.h"
#include "../../../events/events.h"
#include "../../../events/msg_dispatcher.h"

static Event ev_SpeedingUp(Ev_Speeding_Up, 1);	// l'event

static Coord crd;	// random crd
static std::string faster = "- SPAWN SPEED IS INCREASING -";	
static bool Dr_Er;	// draw or erase
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void  Ev_Speeding_Up()			// Les bots spawnent plus vite!
{
	if (!ev_SpeedingUp.Is_Active())
	{
		crd = { ((Find_Ctr_X((int)std::size(faster))) / 2) - 20, (gConHeight / 2) };
		
		ev_SpeedingUp.Activate();
		ev_SpeedingUp.Start(2000, 20);
	}
	else
	{
		while (ev_SpeedingUp.delay.Tick())
		{
			if (Dr_Er)
				Dr_Er = false;
			else
				Dr_Er = true;

			ConsoleRender::Add_String(faster, { Up_Txt_1(faster).x, 1 }, LIGHT_RED, 0, Dr_Er);	// fais clignoter ce titre
			//ConsoleRender::Add_String(faster, crd, LIGHT_RED, 0, Dr_Er);	// fais clignoter ce titre
		}
	}
}

