#pragma once

#include "../UI/axis.h"
#include "../UI/coord.h"

class BotSpawner
{
public:
	void Set_XY(Coord Coord) { coord = Coord; }	// Initialise le x et y du Spawn (Ne doit pas �tre utilis� directement, se r�f�rer au Grid de Spawn : SpawnGrid)
	Coord Get_XY() { return coord;}	
private:
	Coord coord;
};

