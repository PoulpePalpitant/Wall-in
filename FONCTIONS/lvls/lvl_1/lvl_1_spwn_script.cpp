

#include "../../time/spawn_cycle.h"
#include "../../grid/managegrids.h"
#include "../../spawns/bots_to_spawn.h"

#include "lvl_1_spwn_script.h"

using namespace bots_to_spawn;

void Lvl_1_Spwn_Script()
{
	int numSpawnWaves = gSpawnCycleTot;	// Pour aller dans la switch et déterminé quel va être le spawn
	int skip = 0;						// Représente le nombre de fois qu'on va Skip un cycle de spawn selon l'indice de temps: Delay * Spawn_Cycle

	
	gHorizontalBorder = true;

	switch (numSpawnWaves)
	{



	}
}