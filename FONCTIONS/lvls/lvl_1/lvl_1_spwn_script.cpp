

#include "../../time/spawn_cycle.h"
#include "../../grid/managegrids.h"
#include "../../spawns/bots_to_spawn.h"

#include "lvl_1_spwn_script.h"

using namespace bots_to_spawn;

void Lvl_1_Spwn_Script()
{
	int numSpawnWaves = gSpawnCycleTot;	// Pour aller dans la switch et déterminé quel va être le spawn
	int skip = 0;						// Représente le nombre de fois qu'on va Skip un cycle de spawn selon l'indice de temps: Delay * Spawn_Cycle

	
	//gHorizontalBorder = true;
	//gVerticalBorder = true;
	switch (numSpawnWaves)
	{
	//case 0:Add_Spwns(40); break;
	case 1: break;
	case 2:Add_Specific(LEFT, 1);break;
	case 3:Add_Specific(RIGHT, 1);break;
	case 4:Add_Specific(RIGHT, 1);break;
	case 5:Add_Specific(RIGHT, 1);break;
	case 6:gBoxSide = RIGHT;break;
	case 7:gBoxSide = LEFT;break;
	case 8:gBoxSide = RIGHT;break;
	case 9:gBoxSide = RIGHT;break;

	case 20:Add_Spwns(35); break;
	}


}