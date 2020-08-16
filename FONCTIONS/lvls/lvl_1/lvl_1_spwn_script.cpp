

#include "../../time/spawn_cycle.h"
#include "../../grid/managegrids.h"
#include "../../spawns/bots_to_spawn.h"
#include "../../events/msg_dispatcher.h"

#include "events/ev_build_start_walls.h"
#include "lvl_1_spwn_script.h"

using namespace bots_to_spawn;

void Lvl_1_Spwn_Script()
{
	if (gSpawnThisCycle)
	{
		int numSpawnWaves = gSpawnCycleTot;	// Pour aller dans la switch et d�termin� quel va �tre le spawn
		int skip = 0;						// Repr�sente le nombre de fois qu'on va Skip un cycle de spawn selon l'indice de temps: Delay * Spawn_Cycle
		
		// POUR GET LE MAX
		//	spawnGrid->Get_MaxSpwnCrdX() - 1
		//	spawnGrid->Get_MaxSpwnCrdY() - 1
		//Add(300);
		

		if(numSpawnWaves > 20)	// Les 20 premier spawns seront manuel
			Add(1);
		
		if (numSpawnWaves < 100) // Tout les spawns seront verticaux jusqu'au final push du level
		{
			gVerticalBorder = true;
		}
		else
		{
			gHorizontalBorder = true;

		}

		switch (numSpawnWaves)
		{
		case 1:Add_Specific(RIGHT, 0); Add_Specific(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 1); skip = 4; break;
		case 2:Add_Specific(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 1); break;
		case 3:Add_Specific(RIGHT, 5); break;// Dessine un pattern de d�part
		case 4: Add_Specific(RIGHT, 9);break;
		case 5:Add_Specific(RIGHT, spawnGrid->Get_MaxSpwnCrdY() - 1);break;
		case 6:Add(1);gBoxSide = RIGHT;break;
		case 7:Add(1);gBoxSide = LEFT;break;
		case 8:Add(1);gBoxSide = RIGHT;break;
		case 9:Add(1);gBoxSide = RIGHT; skip = 1; break;
		case 10:Add(1); Add_Specific(RIGHT, spawnGrid->Get_MaxSpwnCrdY() - 1);break;	// Premier Double
		case 11:Add(1); break;
		case 12:Add(1); gBoxSide = LEFT; gSpwNum = 0; break;
		case 13:Add(1); gBoxSide = LEFT; gSpwNum = 1; break;
		case 14:Add(1); gBoxSide = LEFT; gSpwNum = 2; break;
		case 15:Add(1); gBoxSide = LEFT; gSpwNum = 3; break;
		case 16:Add(1); gBoxSide = LEFT;gSpwNum = spawnGrid->Get_MaxSpwnCrdY() - 1; break;
		case 17:Add(1); gBoxSide = RIGHT;gSpwNum = spawnGrid->Get_MaxSpwnCrdY() / 2; break;
		case 18:Add(1); gBoxSide = LEFT; gSpwNum = spawnGrid->Get_MaxSpwnCrdY() / 2;break;
		case 19:Add(1); break;
		case 20:Add(1); break;
		case 21:Add(1); break;
		case 22:Add(1); break;
		case 23:Add(1); break;
		case 24:Add(1); break;
		case 25:Add(1); break;
		case 26:Add(1); break;
		case 27:Add(1); break;
		case 28:Add(1); break;
		case 29:Add(1); break;
		// Start les doubles spawns
		case 30:Add(1); Set_Interval(RIGHT, 5, 6);break;
		case 31:Add(1); Set_Interval(RIGHT,5,6);break;
		case 32:Add(1); Set_Interval(RIGHT,5,6);break;
		case 33:Add(1); Set_Interval(RIGHT,5,6);break;
		case 34:Add(1); Set_Interval(RIGHT,5,6); skip = 8; break;
		case 35:Add(1); Set_Interval(RIGHT, 9,10);break;
		case 36:Add(1); Set_Interval(RIGHT, 9,10);break;
		case 37:Add(1); Set_Interval(RIGHT, 9,10);break;
		case 38:Add(1); Set_Interval(RIGHT, 9,10);break;
		case 39:Add(1); Set_Interval(RIGHT, 9,10); skip = 8; break;

		case 40: Set_Interval(LEFT, 2,3); Add(1); break;
		case 41: Set_Interval(LEFT, 2,3); Add(1); break;
		case 42: Set_Interval(LEFT, 2,3); Add(1); break;
		case 43: Set_Interval(LEFT, 2,3); Add(1); break;
		case 44: Set_Interval(LEFT, 2,3); Add(1);  skip = 5; break;
		case 45: Set_Interval(RIGHT, 11, 12);  Add(1);break;
		case 46: Set_Interval(RIGHT, 11, 12);  Add(1);break;
		case 47: Set_Interval(RIGHT, 11, 12);  Add(1);break;
		case 48: Set_Interval(RIGHT, 11, 12);  Add(1);break;
		case 49: Set_Interval(RIGHT, 11, 12);  Add(1); skip = 5; break;

			// Random spawns
		case 50:break;
		case 51:break;
		case 52:break;
		case 53:break;
		case 54:break;
		case 55:break;
		case 56:break;
		case 57:break;
		case 58:break;
		case 59:break;
		case 60:break;
		case 61:break;
		case 62:break;
		case 63:break;
		case 64:break;
		case 65:break;
		case 66:break;
		case 67:break;
		
			// Start les triples spawns!!
		case 80: Set_Interval(LEFT, 0,4);Add(2); break;
		case 81: Set_Interval(RIGHT, 4,8);Add(2); break;
		case 83: Set_Interval(LEFT, 8,12);Add(2); break;
		case 84: Set_Interval(LEFT, 0,4);Add(2); break;
		case 87: Set_Interval(RIGHT, 4,8);Add(2); break;
		case 88: Set_Interval(LEFT, 8,12);Add(2); break;
		case 99: Add(2); break;

			// FINAL PUSH	
		case 100: MsgQueue::Register(FINAL_PUSH);	break;
		case 101:  Add(1);break;
		case 102:  Add(1);break;
		case 103:  Add(1);break;
		case 104:  Add(1);break;
		case 105:gBoxSide = LEFT;  Add(1);break;
		case 106:gBoxSide = LEFT;  Add(1);break;
		case 107:  Add(1);break;
		case 108:  Add(1);break;
		case 109:  Add(1);break;
		case 110:Add_Specific(RIGHT, -1);  Add(1);break;
		case 111:Add_Specific(RIGHT, -1);  Add(1);break;
		case 112:Add_Specific(RIGHT, -1);  Add(1);break;
		case 113:Add_Specific(LEFT, -1);  Add(1);break;
		case 114:Add_Specific(LEFT, -1);  Add(1);break;
		case 115:Add_Specific(LEFT, -1);  Add(1);break;
		case 116:  Add(1);break;
		case 117:  Add(1);break;
		case 118:  Add(1);break;
		case 119:  Add(1);break;
		case 120:  Add(1);break;
		}

		// Ceci ajoute du temps entre le spawn actuel et le prochain
		if(skip)
			gSpwBotTimer.Add_Count(skip);
	}
}