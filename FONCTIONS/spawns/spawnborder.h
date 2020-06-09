#pragma once

#include "spawn.h"
#include "../grid/linkgrid.h"
#include "../UI/direction.h"

class SpawnBorder {
private:
	int numSpawns;			// Le nombre de spawns que poss�de la bordure
	Distance btwSpw;		// Soit DELTA_X OU DELTA_Y, la distance s�parant chacun des spawn sur la bordure
public:
	BotSpawner *spawn;			// L'array contenant tous les spawns sur sa bordure
	void Create_Border(LinkGrid &linkGrid, Direction border);	// Cr�er une Bordure de spawn selon les dimensions du Link Grid et un c�t�. Assigne �galement une valeur X et y � chacun des spawns :)
	int Get_Num_Spawns() { return this->numSpawns; }				// Acc�s au nombre de spawns sur la bordure
};

