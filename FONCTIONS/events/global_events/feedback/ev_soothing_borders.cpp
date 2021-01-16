
#include "ev_soothing_borders.h"

#include "../../../UI/console_output/render_list.h"
#include "../../../console/sweet_cmd_console.h"
#include "../../../events/events.h"
#include "../../../events/msg_dispatcher.h"
#include "../../../math/manage_interval.h"
#include "../../../UI/map.h"
#include "../../../events/global_events/feedback/ev_draw_map.h"


const int NUM_COLOR = 18;	// nombre de couleurs
static Colors clr;	// Pour colorier chaque bordures
static Colors newClr;	// Pour colorier chaque bordures

static int eventSpeed = 16000;
static int numCycles = 50;
static Event ev_SoothingBorders(Ev_Soothing_Borders,2);	// l'event. Fait flasher un certain nombre de fois tout les couleur du pattern ci-dessous
static bool infinite;


void Ev_Soothing_Borders()
{
	static int cycles;
	static bool pauseCycle;

	if (!ev_SoothingBorders.Is_Active())
	{
		cycles = 0;
		pauseCycle = false;

		ev_SoothingBorders.Activate();
		ev_SoothingBorders.Start(0);
		ev_SoothingBorders.delay.Start_Timer(eventSpeed, 1, 1);
	}
	else
	{
		while (ev_SoothingBorders.delay.Tick())
		{
			if (pauseCycle)
			{
				if (cycles % (NUM_COLOR * (int)2) == 0)
					pauseCycle = false;
			}
			else {
				switch (cycles % NUM_COLOR)
				{
				case 0:	newClr = GRAY;	 break;
				case 1:	newClr = GRAY; break;
				case 2:	newClr = WHITE; break;
				case 3:	newClr = WHITE; break;
				case 4:	newClr = BRIGHT_WHITE;break;
				case 5:	newClr = BRIGHT_WHITE;break;
				case 6:	newClr = BRIGHT_WHITE;break;
				case 7:	newClr = BRIGHT_WHITE; break;
				case 8: newClr = BRIGHT_WHITE;break;
				case 9:	newClr = BRIGHT_WHITE;	break;
				case 10:newClr = WHITE; break;
				case 11:newClr = WHITE;break;
				case 12:newClr = WHITE;break;
				case 13:newClr = GRAY;  break;
				case 14:newClr = GRAY;    break;
				case 15:newClr = GRAY;    break;
				case 16:newClr = GRAY;    break;
				case 17: newClr = GRAY;	pauseCycle = true;	break;
				}

				if (newClr != clr)
				{
					clr = newClr;
					Just_Dr_Map_Borders(clr);
				}
			}

			cycles++;

			if (cycles == numCycles * NUM_COLOR && !infinite )
			{
				Cancel_Ev_Soothing_Borders();
			}
		}
	}
}

void Set_Ev_Soothing_Borders(bool infinity, int duration)
{
	numCycles = duration;
	infinite = infinity;

	if (ev_SoothingBorders.Is_Active())
	{
		Cancel_Ev_Soothing_Borders();
	}
		
	Ev_Soothing_Borders();
}


void Cancel_Ev_Soothing_Borders() {
	ev_SoothingBorders.Cancel();
	Set_Dr_Map_1(0, true);
}


// Version #1, couleur blanche
//
//speed= 16000
//if (pauseCycle)
//{
//	if (cycles % (NUM_COLOR * (int)2) == 0)
//		pauseCycle = false;
//}
//else {
//	switch (cycles % NUM_COLOR)
//	{
//	case 0:	newClr = GRAY;	 break;
//	case 1:	newClr = GRAY; break;
//	case 2:	newClr = GREEN; break;
//	case 3:	newClr = GREEN; break;
//	case 4:	newClr = BRIGHT_WHITE;break;
//	case 5:	newClr = BRIGHT_WHITE;break;
//	case 6:	newClr = BRIGHT_WHITE;break;
//	case 7:	newClr = BRIGHT_WHITE; break;
//	case 8: newClr = BRIGHT_WHITE;break;
//	case 9:	newClr = BRIGHT_WHITE;	break;
//	case 10:newClr = WHITE; break;
//	case 11:newClr = WHITE;break;
//	case 12:newClr = WHITE;break;
//	case 13:newClr = GRAY;  break;
//	case 14:newClr = GRAY;    break;
//	case 15:newClr = GRAY;    break;
//	case 16:newClr = GRAY;    break;
//	case 17: newClr = GRAY;	pauseCycle = true;	break;
//	}