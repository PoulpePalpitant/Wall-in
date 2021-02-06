#pragma once

#include "../UI/txtstyle.h"
#include	"../link/link.h"
#include "../grid/grid.h"

/*
	Le teleporteur est une action que le joueur peut faire qui lui permet de se teleporter
	Le joueur doit setté le teleporteur en tirant. 
	Un téléporteur ne téléportera jamais le joueur sur une ROOT. Si le joueur tente de faire ça, il sera téléporté juste en face, selon la direction du tir. 
	Si cette nouvelle position est aussi une ROOT, la téléportation	échouera.
	Le joueur peut se téléporter sur la même position autant de fois qu'il le veut.
*/

class Teleporter
{
	GrdCoord crd;
	bool isActive;
	
	void Dr_Teleporter();							
public:
	void Remove_Teleport_Location();				
	bool Teleport_Player();							
	bool Validate_Position(Link &link);				
	bool Set_Teleport_Location(GrdCoord coord);		
	GrdCoord Get_Coord() { return crd; }

	~Teleporter() {}
};


