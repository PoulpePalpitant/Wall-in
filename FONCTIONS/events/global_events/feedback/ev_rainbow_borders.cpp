
#include "ev_rainbow_borders.h"

#include "../../../UI/console_output/render_list.h"
#include "../../../console/sweet_cmd_console.h"
#include "../../../events/events.h"
#include "../../../events/msg_dispatcher.h"
#include "../../../math/manage_interval.h"
#include "../../../UI/map.h"
#include "../../../events/global_events/feedback/ev_draw_map.h"


const int NUM_COLOR = 6;	// nombre de couleurs
const int NUM_COLOR_EXTRA = 8;	// nombre de couleurs
static Colors clr;	// Pour colorier chaque bordures

static Event ev_RainbowBorders(Ev_Rainbow_Borders, NUM_COLOR * 4);	// l'event. Fait flasher un certain nombre de fois tout les couleur du pattern ci-dessous
static Event ev_RainbowBordersExtra(Ev_Rainbow_Borders_Extra, NUM_COLOR_EXTRA * 5);	//	EXTRA! OUAIS!

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
	static int eventSpeed = 8200;

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


void Ev_Rainbow_Borders_Extra()
{
	static int eventSpeed = 10200;

	if (!ev_RainbowBordersExtra.Is_Active())
	{
		ev_RainbowBordersExtra.Activate();
		ev_RainbowBordersExtra.Start(eventSpeed);
	}
	else
	{
		while (ev_RainbowBordersExtra.delay.Tick())
		{
			switch (ev_RainbowBordersExtra.Get_Current_Step() % NUM_COLOR)
			{
			case 0:	clr = LIGHT_RED;	 break;
			case 1:	clr = LIGHT_YELLOW;  break;
			case 2:	clr = LIGHT_GREEN;	 break;
			case 3:	clr = LIGHT_PURPLE;  break;
			case 4:	clr = LIGHT_BLUE;    break;
			case 5:	clr = LIGHT_AQUA;    break;
			case 6:	clr = BRIGHT_WHITE;    break;
			case 7:	clr = BG_WH_LIGHT_GREEN;  break;
			default: clr = BRIGHT_WHITE;
			}

			Just_Dr_Map_Borders(clr);
			ev_RainbowBordersExtra.Advance(eventSpeed);

			if (!ev_RainbowBordersExtra.Is_Active())
				Set_Dr_Map_1(0, true);	// Efface la map

		}
	}
}
