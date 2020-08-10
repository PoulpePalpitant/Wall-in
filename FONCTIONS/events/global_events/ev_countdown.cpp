#include "ev_countdown.h"

#include "../events.h"
#include "../msg_dispatcher.h"
#include "../../UI/console_output/render_list.h"
#include "../../structure_manager/modify_chain.h"
#include "../../grid/AllGrids.h"

static Event ev_CountDown(Ev_CountDown, 3);
static std::string go = "Go!";
static Coord crd;
static Colors clr;
static int clrRatio;		// Change la couleur selon la progression du countdown


static const int DLFLT_CD = 5;	// La durée du countdown
static int cd = DLFLT_CD;	// La durée du countdown

void Set_CoundDown_Dur(int duration)
{
	if (!ev_CountDown.Is_Active())
		cd = duration;
	else
		throw "fuckyou";
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
		// initialisation
		//crd.x = linkGrid->link[(linkGrid->Get_Cols() / 2)][0].Get_XY().x;		// Translation: 1 case en dessous de l'élément au milieu du grid
		crd.x = Find_Ctr_X();
		crd.y = linkGrid->link[0][(linkGrid->Get_Rows() / 2)].Get_XY().y + 1;		// Translation: 1 case en dessous de l'élément au milieu du grid

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
				ev_CountDown.Advance(1000);
				break;
			}
		}
			

	
}
