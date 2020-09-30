
#include "ev_speeding_up.h"

#include "../../../UI/console_output/render_list.h"
#include "../../../console/sweet_cmd_console.h"
#include "../../../events/events.h"
#include "../../../events/msg_dispatcher.h"
#include "../../../UI/map.h"

static Event ev_SpeedingUp(Ev_Speeding_Up, 1);	// l'event

static Coord crd;	// random crd
static std::string faster = "- SPAWN SPEED IS INCREASING -";	
static std::string faster_2 = "- TOOLS SPAWN SPEED IS INCREASING -";	
static std::string* increase = &faster;	// le titre sélectionné
static Colors clr = LIGHT_RED;	// Couleur sélectionné
static bool Dr_Er;	// draw or erase
static const int GAP_GRID = 12;	// distance entre texte et grid sur les côtés

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Set_Event_String(int string)
{
	if (string == 1)
	{
		increase = &faster;
		clr = LIGHT_RED;
	}
	if (string == 2)
	{
		increase = &faster_2;
		clr = LIGHT_YELLOW;
	}
}

void  Ev_Speeding_Up()			// Les bots spawnent plus vite!
{
	if (!ev_SpeedingUp.Is_Active())
	{
		crd = { ((Find_Ctr_X((int)std::size(*increase))) / 2) - 20, (gConHeight / 2) };
		
		ev_SpeedingUp.Activate();
		ev_SpeedingUp.Start(1000, 13);
	}
	else
	{
		while (ev_SpeedingUp.delay.Tick())
		{
			if (Dr_Er)
				Dr_Er = false;
			else
				Dr_Er = true;

			//ConsoleRender::Add_String(*increase, { Up_Txt_1(*increase).x,  Up_Txt_1(*increase).y - 1 }, clr, 0, Dr_Er);	// fais clignoter ce titre
			ConsoleRender::Add_String(*increase , { map.Get_Box_Limit(LEFT) - (int)(*increase).size() - GAP_GRID,/* gConHeight / 2*/(map.Get_Box_Limit(DOWN)) / 2 }, clr, 0, Dr_Er);	// fais clignoter ce titre
			ConsoleRender::Add_String(*increase, { map.Get_Box_Limit(RIGHT) + (int)(*increase).size() - GAP_GRID, (map.Get_Box_Limit(DOWN) ) / 2  }, clr, 0, Dr_Er);	// fais clignoter ce titre
			
		}
	}
}

