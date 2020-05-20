
#include "../bot.h"
#include "../../UI/map.h"

// Intialise les données sur le nombre de step que le bot doit faire pour sortir
// ----------------------------------------------------------------------------

void Bot::Init_Step_Count()																	// La distance qu'il doit parcourir and shit
{
	//	Nb de déplacement total à faire au moment du spawn,

	switch (dir)
	{
	case UP:case DOWN: stepLeftMax = (map.Get_Height() + GAP_BTW_GRID) / speed;		break;	// Ya un tit gap entre la position du spawn et la "box". Le bot spawn donc à l'ext de la box
	case LEFT:	case RIGHT:stepLeftMax = (map.Get_Length() + GAP_BTW_GRID) / speed;
	}

	stepLeft = stepLeftMax;			//	Le nombre de déplacement pour atteindre l'autre decôté de la box, par rapport à sa position actuelle 
}

