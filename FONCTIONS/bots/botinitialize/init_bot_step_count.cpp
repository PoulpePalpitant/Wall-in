
#include "../bot.h"
#include "../../UI/map.h"

// Intialise les donn�es sur le nombre de step que le bot doit faire pour sortir
// ----------------------------------------------------------------------------

void Bot::Init_Step_Count()																	// La distance qu'il doit parcourir and shit
{
	//	Nb de d�placement total � faire au moment du spawn,

	switch (dir)
	{
	case UP:case DOWN: stepLeftMax = (map.Get_Height() + GAP_BTW_GRID) / speed;		break;	// Ya un tit gap entre la position du spawn et la "box". Le bot spawn donc � l'ext de la box
	case LEFT:	case RIGHT:stepLeftMax = (map.Get_Length() + GAP_BTW_GRID) / speed;
	}

	stepLeft = stepLeftMax;			//	Le nombre de d�placement pour atteindre l'autre dec�t� de la box, par rapport � sa position actuelle 
}

