

#include "../../time/spawn_cycle.h"
#include "../../grid/managegrids.h"
#include "../../spawns/bots_to_spawn.h"

#include "lvl_1_spwn_script.h"

using namespace bots_to_spawn;

void Lvl_1_Spwn_Script()
{
	if (gSpawnThisCycle)
	{
		int numSpawnWaves = gSpawnCycleTot;	// Pour aller dans la switch et déterminé quel va être le spawn
		int skip = 0;						// Représente le nombre de fois qu'on va Skip un cycle de spawn selon l'indice de temps: Delay * Spawn_Cycle
		
		// POUR GET LE MAX
		//	spawnGrid->Get_MaxSpwnCrdX()
		//	spawnGrid->Get_MaxSpwnCrdY()
		//Add(1);
		//gHorizontalBorder = true;
		//gVerticalBorder = true;
		switch (numSpawnWaves)
		{
		case 1: Add(300);
			/*Set_Interval(LEFT,0, spawnGrid->Get_MaxSpwnCrdY() -1 );
			Set_Interval(RIGHT, 0,spawnGrid->Get_MaxSpwnCrdY() - 1);
			Set_Interval(UP,0, spawnGrid->Get_MaxSpwnCrdX() - 1);
			Set_Interval(DOWN,0, spawnGrid->Get_MaxSpwnCrdX() - 1);
			*/break;
		/*case 2:Add_Specific(LEFT, 1); break;
		case 3:Add_Specific(RIGHT, 1);break;
		case 4:Add_Specific(RIGHT, 1);break;
		case 5:Add_Specific(RIGHT, 1);break;
		case 6:gBoxSide = RIGHT;break;
		case 7:gBoxSide = LEFT;break;
		case 8:gBoxSide = RIGHT;break;
		case 9:gBoxSide = RIGHT;break;*/

		case 20:break;
		}

	}
}