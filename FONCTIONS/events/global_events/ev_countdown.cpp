#include "ev_countdown.h"

#include "../events.h"
#include "../msg_dispatcher.h"
#include "../../UI/console_output/render_list.h"
#include "../../structure_manager/modify_chain.h"
#include "../../console/sweet_cmd_console.h"

static Event ev_CountDown(Ev_CountDown, 3);
static std::string go = "Go!";
static std::string blast = "(You can shoot \"after\" the countdown)";
static Coord crd;
static Colors clr;
static int clrRatio;		// Change la couleur selon la progression du countdown
static bool blastDisabled = false;

static const int DLFLT_CD = 5;	// La durée du countdown
static int cd = DLFLT_CD;	// La durée du countdown

bool Blast_Disabled_While_CD()
{
	static bool msgShown = false;

	if (ev_CountDown.Is_Active())
	{
		if (blastDisabled)
		{
			if (msgShown)
				return true;
			else
			{
				msgShown = false;
				ConsoleRender::Add_String(blast, { Find_Ctr_X((int)std::size(blast)),gConHeight - 1 }, GRAY); 			// show message
				return true;
			}
		}
	}

	return false;
}

void Set_CountDown(int duration, Coord coord, bool disableBlast)
{
	if (!ev_CountDown.Is_Active())
	{
		cd = duration;
		crd = coord;
		blastDisabled = disableBlast;
	}
	else
		throw "fuckyou";
}
bool CountDown_Cancel() // Permet de savoir quand le contdown est finit
{
	if (ev_CountDown.Is_Active())
	{
		ev_CountDown.Cancel();
		if (blastDisabled)
		{
			MsgQueue::Register(ENABLE_BLAST);
			ConsoleRender::Add_String(blast, { Find_Ctr_X((int)std::size(blast)),gConHeight - 1 },WHITE, TXT_SPD_FAST, true); 			// erase
			 blastDisabled = false;
		}
		return true;
	}
	else
		return false;
}

bool CountDown_Finished() // Permet de savoir quand le contdown est finit
{
	if (!ev_CountDown.Is_Active())
		return true;
	else
		return false;
}

// Affiche un tit countdown au milieu de l'écran
void Ev_CountDown()
{
	static int currCoundown;

	if (!ev_CountDown.Is_Active())
	{
		if (blastDisabled)
			MsgQueue::Register(DISABLE_BLAST);

		if (cd <= 0)
			cd = DLFLT_CD;	 

		ev_CountDown.Activate();
		ev_CountDown.Start(1000, cd );
	}
	else
		while (ev_CountDown.delay.Tick())
		{
			if (cd >= 4)
				clr = LIGHT_GREEN;
			else
				if(cd == 3)
					clr = Colors::LIGHT_YELLOW;
				else
					clr = Colors::LIGHT_RED;

			switch (ev_CountDown.Get_Current_Step())
			{
			case 1:
				if(cd == 9)
					ConsoleRender::Add_String("9 ", crd, clr);	// Pour éffacer la dizaine xD
				else
					ConsoleRender::Add_String(std::to_string(cd), crd, clr);
				cd--;

				ev_CountDown.Advance(1000);
				break;

			case 2:
				ConsoleRender::Add_String(go, { crd.x - 1 , crd.y });//Affiche
				ev_CountDown.Advance(1000);
				break;

			case 3:
				ConsoleRender::Add_String(go, { crd.x - 1 , crd.y }, WHITE, 0, true);//erase
				
				if (blastDisabled)
				{
					ConsoleRender::Add_String(blast, { Find_Ctr_X((int)std::size(blast)),gConHeight - 1 }, WHITE, TXT_SPD_FAST, true); 			// erase
					MsgQueue::Register(ENABLE_BLAST);
					blastDisabled = false;
				}
				ev_CountDown.Advance(1000);
				break;
			}
		}
			

	
}
