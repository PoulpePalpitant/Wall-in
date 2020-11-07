
#include "ev_Ammo_Depleted.h"

#include "../../../UI/map.h"
#include "../../../blast/blast.h"
#include "../../../UI/console_output/render_list.h"
#include "../../events.h"
#include "../../../blast/blast_ammo_animator.h"

using namespace DrawBlastAmmo;


static Event ev_AmmoDepleted(Ev_Ammo_Depleted);
static std::string depleted = "- NO AMMO -";
static Coord crd;


void Ev_Ammo_Depleted()	// Affiche 1 warning que le joueur n'a plus d'ammo
{
	static bool erOrDr;	// erase ou draw

	if (!ev_AmmoDepleted.Is_Active())
	{

		crd = Get_Ori();
		crd.x += barToCount;
		erOrDr = false;
		ConsoleRender::Add_String(depleted, crd, LIGHT_RED);

		ev_AmmoDepleted.Activate();
		ev_AmmoDepleted.Start(0);
		ev_AmmoDepleted.delay.Start_Timer(2000,1,true);
	}
	else
		while (ev_AmmoDepleted.delay.Tick())
		{
			if (blastP1.Get_Ammo_Manager().Get_Nb_Ammo() > 0)	// safety
			{
				Cancel_Ev_Ammo_Depleted();
			}
			else
			{
				ConsoleRender::Add_String(depleted, crd, LIGHT_RED, 0, erOrDr);

				if (erOrDr)
					erOrDr = false;
				else
					erOrDr = true;
			}
		}
}

void Cancel_Ev_Ammo_Depleted()	// permet de cancel cet event for the sake of speed
{
	ConsoleRender::Add_String(depleted, crd, LIGHT_RED, 0, true);
	ev_AmmoDepleted.Cancel();
}