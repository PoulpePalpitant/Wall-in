#pragma once

#include "../UI/txtstyle.h"
#include	"../link/link.h"
#include "../grid/grid.h"

/*
	Le teleporteur est une action que le joueur peut faire qui lui permet de se teleporter
	Le joueur peut lui même setté le teleporteur en tirant. 
	Un téléporteur ne téléportera jamais le joueur sur une ROOT. Si le joueur tente de faire ça, il sera téléporté juste en face, selon la direction du tir. Si cette nouvelle position est aussi une ROOT, la téléportation
	échouera. Le joueur peut se téléporter sur la même position autant de fois qu'il le veut.
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
	GrdCoord Get_Coord() { return crd; }

	~Teleporter() {}
};


