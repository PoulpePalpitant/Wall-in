#pragma once

#include "../UI/txtstyle.h"
#include	"../link/link.h"
#include "../grid/grid.h"

// Le teleporteur est une action que le joueur peut faire qui lui permet de se teleporter
/*
	Le joueur peut lui m�me sett� le teleporteur en tirant. La logique va comme suis

	Un t�l�porteur peut uniquement �tre situ�:

	- Sur un Link de state FREE
	- Sur un Link de modifier REGULAR

	Cela implique donc, que toute tentative de cr�er un teleporteur ou le joueur tir un blast qui ne produit pas un link FREE et RGULAR �chouera

*/

class Teleporter
{
	GrdCoord crd;
	bool isActive;
	
	// UI
	static const Colors CLR;
	static const char SYM;

	void Dr_Teleporter();							// Affiche le teleporter
public:
	void Remove_Teleport_Location();				// 
	bool Teleport_Player();							//	Changela position du joueur pour celle du teleporteur. Animation ensues
	void Upd_Teleporter_State();					// Si le state ou le modifier du link surlequeul se trouve change, il se peut que le teleporteur soit d�truit
	bool Validate_Position(Link &link);				// Check si le link d'une position est free et r�gulier
	bool Validate_Position(GrdCoord crd);			// Check si le link d'une position est free et r�gulier
	bool Set_Teleport_Location(GrdCoord coord);		// Set une position de t�l�portation. Fais la validation en m�me temps

	//Teleporter() {}
	~Teleporter() {}

};


