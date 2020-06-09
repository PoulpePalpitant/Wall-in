#pragma once

#include "spawn.h"
#include "../grid/linkgrid.h"
#include "../UI/direction.h"

class SpawnBorder {
private:
	int numSpawns;			// Le nombre de spawns que possède la bordure
	Distance btwSpw;		// Soit DELTA_X OU DELTA_Y, la distance séparant chacun des spawn sur la bordure
public:
	BotSpawner *spawn;			// L'array contenant tous les spawns sur sa bordure
	void Create_Border(LinkGrid &linkGrid, Direction border);	// Créer une Bordure de spawn selon les dimensions du Link Grid et un côté. Assigne également une valeur X et y à chacun des spawns :)
	int Get_Num_Spawns() { return this->numSpawns; }				// Accès au nombre de spawns sur la bordure
};

