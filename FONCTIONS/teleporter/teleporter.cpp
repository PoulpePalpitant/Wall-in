

#include "teleporter.h"
#include "../grid/AllGrids.h"
#include "../player/player.h"
#include "../events/global_events/feedback/ev_tp_animation.h"



bool Teleporter::Validate_Position(Link &link)	
{
	return 	link.Get_Modifier() != Modifier::FORCEFIELD;
}

bool Teleporter::Teleport_Player()							
{
	if (isActive)
	{
		GrdCoord playerCrd = P1.Get_Grd_Coord();
		if (linkGrid->link[playerCrd.c][playerCrd.r].Get_State() != LinkState::DEAD)
			linkGrid->link[playerCrd.c][playerCrd.r].Dsp_Link();	// EFFACE le joueur, et affiche du même coup le link en dessous
		else
			P1.Er_Player();

		P1.Set_Position(crd);
		P1.Dr_Player();

		Add_Tp_Animation();
		return true;
	}
	else
		return false;
}

bool Teleporter::Set_Teleport_Location(GrdCoord coord)		
{
	if (isActive)
	{
		if (linkGrid->link[crd.c][crd.r].Get_State() != LinkState::DEAD)
			linkGrid->link[crd.c][crd.r].Dsp_Link();	
	}
	else
	{
		isActive = true;
	}

	crd = coord;
	return true;
}


void Teleporter::Remove_Teleport_Location()			
{
	crd = { -1,-1 };
	isActive = false; 
}

void Teleporter::Dr_Teleporter()							
{
	if (!Are_Equal(P1.Get_Grd_Coord(), crd))
		Coord xy = linkGrid->link[crd.c][crd.r].Get_XY();
}
