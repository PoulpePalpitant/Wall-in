#pragma once

#include "../UI/txtstyle.h"
#include	"../link/link.h"
#include "../grid/grid.h"

/*
	Le teleporteur est une action que le joueur peut faire qui lui permet de se teleporter
	Le joueur doit sett� le teleporteur en tirant. 
	Un t�l�porteur ne t�l�portera jamais le joueur sur une ROOT. Si le joueur tente de faire �a, il sera t�l�port� juste en face, selon la direction du tir. 
	Si cette nouvelle position est aussi une ROOT, la t�l�portation	�chouera.
	Le joueur peut se t�l�porter sur la m�me position autant de fois qu'il le veut.
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


