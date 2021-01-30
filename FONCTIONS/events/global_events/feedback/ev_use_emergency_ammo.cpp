
#include "ev_use_emergency_ammo.h"

#include "../../../UI/map.h"
#include "../../../blast/blast.h"
#include "../../../UI/console_output/render_list.h"
#include "../../events.h"
#include "../../../UI/console_output/draw_queue.h"
#include "../../../blast/blast_ammo_animator.h"
#include "../../../player/player.h"

using namespace DrawBlastAmmo;

static Event ev_UseEmergencyAmmo(Ev_Use_Emergency_Ammo); // Def //
static Event ev_NoAmmoMsg(Ev_No_Ammo_Msg,2); // Def //
DrawerQueue Q_ev_UseEmergencyAmmo(8, 9);		

static unsigned char dr = 179;
static unsigned char er = TXT_CONST.SPACE;



static std::string eraser = "                                     ";

struct odds { std::string msg; unsigned int odd; };

// Une phrase différente à chaque fois, ou presque
static odds emptyMsg[12] = {
	{" NO EXTRA AMMO ",43},
	
	{" THERE IS NO AMMO  ",8},
	{" NOTHING HERE ",8},
	{" EMPTY ",8},
	{" CANNOT SHOOT ", 8},
	{" AMMO'S GONE  ",8},
	{" YOU CAN'T  ",8},

	{" OH... ",2},
	{" TRY AGAIN LATER  ",2},
	{" THAT'S NOT HOW IT WORKS ",2},
	{" STOP TRYING ! ",2},
	{" YOU'RE SCREWED !  ",1},
};



void Ev_Use_Emergency_Ammo()
{
	//static unsigned char dr = TXT_CONST.SPACE_FILL;
	static Coord crd; 
	static int y; 
	static int step;
	
	if (!ev_UseEmergencyAmmo.Is_Active())
	{
		if (ev_NoAmmoMsg.Is_Active()) {
			ev_NoAmmoMsg.Cancel();
		}

		ev_UseEmergencyAmmo.Activate();
		ev_UseEmergencyAmmo.Start(0);	// On ne tick pas ce timer
	}
	else
	{
		for (int i = 0; i < Q_ev_UseEmergencyAmmo.Get_Total(); i++)
		{
			while (Q_ev_UseEmergencyAmmo.queue[i].timer.Tick())
			{

				step = Q_ev_UseEmergencyAmmo.queue[i].currStep;
				crd = Q_ev_UseEmergencyAmmo.queue[i].XY;
				y = crd.y;				// ne changera pas


				if (step < MAX_BAR_SIZE + 1)
				{
					ConsoleRender::Add_Char({ crd.x,crd.y + step }, er);

					if (step < MAX_BAR_SIZE / 2)
						Q_ev_UseEmergencyAmmo.Step(i, 55000);
					else
						Q_ev_UseEmergencyAmmo.Step(i, 25000);
				}
				else
				{
					Q_ev_UseEmergencyAmmo.Remove(i);
				}
			}
		}

		if (!Q_ev_UseEmergencyAmmo.Get_Total())
			ev_UseEmergencyAmmo.Cancel();

	}
}

void Add_Ev_Use_Emergency_Ammo()	
{
	static Coord crd;
	crd = Get_Ori();

	// Je veux juste une animation de ça à la fois finalement
	if (ev_UseEmergencyAmmo.Is_Active())
	{
		ev_UseEmergencyAmmo.Cancel();
		Q_ev_UseEmergencyAmmo.Remove(0);
		Stop_Ev_No_Ammo_Msg();
	}

	Q_ev_UseEmergencyAmmo.Add(crd);

	for (int i = 1; i < MAX_BAR_SIZE; i++)
		ConsoleRender::Add_Char({ crd.x,crd.y + i }, dr, LIGHT_RED);

	Ev_Use_Emergency_Ammo();  
}

void Ev_No_Ammo_Msg()
{
	static Colors clr;
	static Coord crd;
	static int y = Heart_Txt_Crd_Left("").y;
	static std::string msg;
	if (!ev_NoAmmoMsg.Is_Active())
	{
		clr = LIGHT_YELLOW;
		crd = Get_Ori();
		crd.x += 5;
		crd.y += MAX_BAR_SIZE + 1 - 9;

		int diceRoll = rand() % 100 + 1;
		int actualOdd = 0;

		msg = emptyMsg[1].msg;	//default
		
		for (int i = 0; i < 12; i++) {
			actualOdd += emptyMsg[i].odd;
			if (diceRoll <= actualOdd) {
				msg = emptyMsg[i].msg;
				break;
			}
		}

		ConsoleRender::Add_String(msg, crd, clr);
		ev_NoAmmoMsg.Activate();
		ev_NoAmmoMsg.Start(700);
	}
	else
		while (ev_NoAmmoMsg.delay.Tick())
		{

			ConsoleRender::Add_String(eraser, crd, clr ,0,1);
			ConsoleRender::Add_String(eraser, crd, clr,0,1);
			Dr_Emergency_Ammo(0);

			ev_NoAmmoMsg.Cancel();
		}
}

void Stop_Ev_Use_Emergency_Ammo() {		// This will fix a visual glitch
	if (ev_UseEmergencyAmmo.Is_Active())
	{
		ev_UseEmergencyAmmo.Cancel();
		Dr_Or_Er_Bar(MAX_BAR_SIZE,WHITE,true);
		Dr_Bar_Tip(1);
		Q_ev_UseEmergencyAmmo.Remove(0);
	}
}


void Stop_Ev_No_Ammo_Msg()		
{
	Coord crd = Get_Ori();
	crd.x += 5;
	crd.y += MAX_BAR_SIZE + 1 - 9;	 // ouech

	ConsoleRender::Add_String(eraser, crd, WHITE, 0, 1);
	ConsoleRender::Add_String(eraser, crd, WHITE, 0, 1);
	Dr_Emergency_Ammo(0);
	
	ev_NoAmmoMsg.Cancel();
}