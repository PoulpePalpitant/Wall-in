
#include "ev_wrong_action.h"

#include "../../../UI/console_output/render_list.h"
#include "../../events.h"
#include "../../../player/player.h"

void Ev_Wrong_Action(); // Fait flasher le joueur en rose quand il fait dequoi de pas correct. Ex: tirer quand il peut pas, se déplacer à un endroit blocké ()
static Event ev_WrongAction(Ev_Wrong_Action,2); // Def //


void Ev_Wrong_Action() // Fait flasher le joueur en rose quand il fait dequoi de pas correct. Ex: tirer quand il peut pas, se déplacer à un endroit blocké ()
{
	if (!ev_WrongAction.Is_Active())
	{
		ConsoleRender::Add_Char(P1.Get_XY(), P1.Get_Sym(), LIGHT_PURPLE);
		ev_WrongAction.Activate();
		ev_WrongAction.Start(12000);	
	}
	else
	{
		while (ev_WrongAction.delay.Tick())
		{
			P1.Dr_Player();
			ev_WrongAction.Cancel();
		}
	}
}

void Ev_Wrong_Action_Add()	// Cancel et et réinitialise l'event() s'il est actif
{
	if (ev_WrongAction.Is_Active())
		ev_WrongAction.Cancel();
	Ev_Wrong_Action();	// Refait l'event
}