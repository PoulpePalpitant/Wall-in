

#include "teleporter.h"
#include "../grid/AllGrids.h"
#include "../player/player.h"


const Colors Teleporter::CLR = LIGHT_GREEN/*LIGHT_AQUA*/;
const char Teleporter::SYM = (unsigned char)250;

bool Teleporter::Validate_Position(GrdCoord crd)			// Check si le link d'une position est free et régulier
{
	//return linkGrid->link[crd.c][crd.r].Get_State() == LinkState::FREE && linkGrid->link[crd.c][crd.r].Get_Modifier() == Modifier::REGULAR;
	return true;
}

bool Teleporter::Validate_Position(Link &link)			// Check si le link d'une position est free et régulier
{
	return 	link.Get_Modifier() != Modifier::FORCEFIELD;

}



void Teleporter::Upd_Teleporter_State()					// Devient 
{
	if (isActive)
	{
		// Vérification de si le teleporteur est toujours actif
		if (!Validate_Position(crd))
			Remove_Teleport_Location();
	}
}

bool Teleporter::Teleport_Player()							//		
{
	Upd_Teleporter_State();	// Vérifie si le teleporteur est bien toujours là
	
	if (isActive)
	{
		GrdCoord playerCrd = P1.Get_Grd_Coord();
		if (linkGrid->link[playerCrd.c][playerCrd.r].Get_State() != LinkState::DEAD)
			linkGrid->link[playerCrd.c][playerCrd.r].Dsp_Link();	// EFFACE le joueur, et affiche du même coup le link en dessous
		else
			P1.Er_Player();

		// Déclancherait une animation, mais pour l'instant
		P1.Set_Position(crd);
		P1.Dr_Player();

		// Remove teleporter
		//Remove_Teleport_Location();

		return true;
	}
	else
		return false;
}

bool Teleporter::Set_Teleport_Location(GrdCoord coord)		// Set la position du teleporteur
{
	if (isActive)
	{
		if (linkGrid->link[crd.c][crd.r].Get_State() != LinkState::DEAD)
		{
			linkGrid->link[crd.c][crd.r].Dsp_Link();	// redraw le link
		}
	}
	else
	{

			isActive = true;
	}

	crd = coord;
	//Dr_Teleporter();

	return true;
}


void Teleporter::Remove_Teleport_Location()				// 
{
	crd = { -1,-1 };
	isActive = false; // reset
}

void Teleporter::Dr_Teleporter()							// Affiche le teleporter
{
	if (!Are_Equal(P1.Get_Grd_Coord(), crd))
	{
		Coord xy = linkGrid->link[crd.c][crd.r].Get_XY();
		
		//if(!linkGrid->Is_Link_Alive_Here(crd))
		//	ConsoleRender::Add_Char(xy, SYM, CLR);
	}
}
