#pragma once

#include "../grid/grid.h"

// Le teleporteur est une action que le joueur peut faire qui lui permet de se teleporter


class Teleporter
{
	GrdCoord crd;
	bool isActive;

	void Teleport_Player();							//		
	void Set_Teleport_Location(GrdCoord crd);		// 
	void Remove_Teleport_Location();				// 
	void Dr_Teleporter();							// Affiche le teleporter
};


