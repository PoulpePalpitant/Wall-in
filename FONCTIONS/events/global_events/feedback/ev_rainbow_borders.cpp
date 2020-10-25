
#include "ev_rainbow_borders.h"

#include "../../../UI/console_output/render_list.h"
#include "../../../console/sweet_cmd_console.h"
#include "../../../events/events.h"
#include "../../../events/msg_dispatcher.h"
#include "../../../math/manage_interval.h"
#include "../../../UI/map.h"
#include "../../../events/global_events/feedback/ev_draw_map.h"


const int NUM_COLOR = 6;	// nombre de couleurs
static Colors clr;	// Pour colorier chaque bordures
static int eventSpeed = 8200;

static Event ev_RainbowBorders(Ev_Rainbow_Borders, NUM_COLOR * 3);	// l'event. Fait flasher un certain nombre de fois tout les couleur du pattern ci-dessous

/*
		RAINBOW PATTERN
	LIGHT_RED
	LIGHT_YELLOW
	LIGHT_GREEN
	LIGHT_PURPLE
	LIGHT_BLUE
	LIGHT_AQUA

*/


void Ev_Rainbow_Borders()
{
	if (!ev_RainbowBorders.Is_Active())
	{
		ev_RainbowBorders.Activate();
		ev_RainbowBorders.Start(eventSpeed);
	}
	else
	{
		while (ev_RainbowBorders.delay.Tick())
		{
			switch (ev_RainbowBorders.Get_Current_Step() % NUM_COLOR)
			{
			case 0:	clr = RED;	 break;
			case 1:	clr = YELLOW;  break;
			case 2:	clr = GREEN;	 break;
			case 3:	clr = PURPLE;  break;
			case 4:	clr = BLUE;    break;
			case 5:	clr = AQUA;    break;
			default: clr = BRIGHT_WHITE;
			}
			
			Just_Dr_Map_Borders(clr);
			ev_RainbowBorders.Advance(eventSpeed);

			if (!ev_RainbowBorders.Is_Active())
				Set_Dr_Map_1(0, true);	// Efface la map

		}
	}
}

