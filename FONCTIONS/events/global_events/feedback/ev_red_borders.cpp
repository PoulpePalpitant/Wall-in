
#include "ev_red_borders.h"

#include "../../../UI/console_output/render_list.h"
#include "../../../console/sweet_cmd_console.h"
#include "../../../events/events.h"
#include "../../../events/msg_dispatcher.h"
#include "../../../math/manage_interval.h"
#include "../../../UI/map.h"
#include "../../../events/global_events/feedback/ev_draw_map.h"


const int NUM_COLOR = 4;	// nombre de couleurs
static Colors clr;	// Pour colorier chaque bordures
static int eventSpeed = 90200;

static Event ev_RedBorders(Ev_Red_Borders, NUM_COLOR * 50);	// l'event. Fait flasher un certain nombre de fois tout les couleur du pattern ci-dessous

/*
		RAINBOW PATTERN
	LIGHT_RED
	LIGHT_YELLOW
	LIGHT_GREEN
	LIGHT_PURPLE
	LIGHT_BLUE
	LIGHT_AQUA

*/


void Ev_Red_Borders()
{
	if (!ev_RedBorders.Is_Active())
	{
		ev_RedBorders.Activate();
		ev_RedBorders.Start(eventSpeed);
	}
	else
	{
		while (ev_RedBorders.delay.Tick())
		{
			switch (ev_RedBorders.Get_Current_Step() % NUM_COLOR)
			{
			case 0:	clr = RED;	  break;
			case 1:	clr = GRAY; break;
			case 2:	clr = LIGHT_RED;	 break;
			case 3:	clr = WHITE;  break;
			case 4:	clr = LIGHT_RED;    break;
			default: clr = BRIGHT_WHITE;
			}
			
			Just_Dr_Map_Borders(clr);
			ev_RedBorders.Advance(eventSpeed);

			if (!ev_RedBorders.Is_Active())
				Set_Dr_Map_1(0, true);	// Efface la map

		}
	}
}

