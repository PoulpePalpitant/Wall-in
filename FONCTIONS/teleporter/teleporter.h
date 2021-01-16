#pragma once

#include "../UI/txtstyle.h"
#include	"../link/link.h"
#include "../grid/grid.h"

// Le teleporteur est une action que le joueur peut faire qui lui permet de se teleporter
/*
	Le joueur peut lui même setté le teleporteur en tirant. La logique va comme suis

	Un téléporteur peut uniquement être situé:

	- Sur un Link de state FREE
	- Sur un Link de modifier REGULAR

	Cela implique donc, que toute tentative de créer un teleporteur ou le joueur tir un blast qui ne produit pas un link FREE et RGULAR échouera

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
	void Upd_Teleporter_State();					// Si le state ou le modifier du link surlequeul se trouve change, il se peut que le teleporteur soit détruit
	bool Validate_Position(Link &link);				// Check si le link d'une position est free et régulier
	bool Validate_Position(GrdCoord crd);			// Check si le link d'une position est free et régulier
	bool Set_Teleport_Location(GrdCoord coord);		// Set une position de téléportation. Fais la validation en même temps

	//Teleporter() {}
	~Teleporter() {}

};


