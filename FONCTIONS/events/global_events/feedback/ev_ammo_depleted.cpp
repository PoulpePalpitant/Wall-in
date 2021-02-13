
#include "ev_Ammo_Depleted.h"

#include "../../../UI/map.h"
#include "../../../blast/blast.h"
#include "../../../UI/console_output/render_list.h"
#include "../../events.h"
#include "../../../blast/blast_ammo_animator.h"
#include "ev_rainbow_borders.h"
#include "../../../events/global_events/feedback/ev_draw_map.h"
#include "../../../blast/mod_queue_animator.h"
#include "../../msg_dispatcher.h"
#include "../../../player/player.h"
#include "../../../blast/blast_ammo_animator.h"

using namespace DrawBlastAmmo;
using namespace DrawModifierQueue;

static Event ev_AmmoDepleted(Ev_Ammo_Depleted);
static std::string depleted = "- NO AMMO -";
static std::string depleted2 = "- NO AMMO FOR SHOT -";
static Coord crd;


void Ev_Ammo_Depleted()	// Affiche 1 warning que le joueur n'a plus d'ammo
{
	static bool erOrDr;	// erase ou draw

	if (!ev_AmmoDepleted.Is_Active())
	{
		crd = Get_Ori();
		crd.x += barToCount;
		erOrDr = false;
		Dr_Ammo_Title(0);
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
				if (DrawModifierQueue::isShown && P1.Get_HP() == 1)
					ConsoleRender::Add_String(depleted2, { realTitleCrd.x - 3,realTitleCrd.y }, LIGHT_RED, 0, erOrDr);

				ConsoleRender::Add_String(depleted, crd, LIGHT_RED, 0, erOrDr);
				//ConsoleRender::Add_String(depleted, { crd.x + 4  ,crd.y + MAX_BAR_SIZE + 1 - 8 },LIGHT_RED,0, erOrDr);	// 

				if (erOrDr)
					erOrDr = false;
				else
					erOrDr = true;
			}
		}
}

void Cancel_Ev_Ammo_Depleted()	// permet de cancel cet event for the sake of speed
{
	ev_AmmoDepleted.Cancel();

	ConsoleRender::Add_String(depleted, crd, LIGHT_RED, 0, true);
	ConsoleRender::Add_String(depleted2, { realTitleCrd.x - 3,realTitleCrd.y }, LIGHT_RED, 0, 1);
	
	if (DrawModifierQueue::isShown)
		MsgQueue::Register(SHOW_MOD_QUEUE);
	
	if(DrawBlastAmmo::isShown)
		DrawBlastAmmo::Dr_Ammo_Title(1);

}

bool Is_Ev_Ammo_Depleted_Active() {
	return ev_AmmoDepleted.Is_Active();
}