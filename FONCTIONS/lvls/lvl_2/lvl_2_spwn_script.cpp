

#include "lvl_2_spwn_script.h"
#include "../../time/spawn_cycle.h"
#include "../../grid/managegrids.h"
#include "../../spawns/bots_to_spawn.h"
#include "../../events/msg_dispatcher.h"
#include "../lvl_script.h"

//some events Shhh...
#include "../../events/global_events/ev_wait_last_bot.h"
#include "../../items/item_spawner.h"
#include "../../events/global_events/ev_warning.h"
#include "../../events/global_events/feedback/ev_draw_map.h"
#include "../lvl_1/msg_events/ev_speeding_up.h"		// hérésie!
#include "lvl_2_initializer.h"

// GENERAL RULES FOR THIS DUMB BROKEN SHIT: 
// Dépasse jamais le nombre de spawn permis sur une bordure
// AddSpecific(): Ne setup jamais une boxside random avec un spw précis
// CETTE FORMULE CRASH 100% DU TEMPS // Add(1); gBoxSide = LEFT; gSpwNum = spawnGrid->Get_MaxSpwnCrdY() - 1; 
// Combiner BoxSide, Spwnum avec plus qu'un spawn, ça créer des exceptions
// Setup un intervalle de spawn trop petit pour le total va faire crashé le shit Ex : Set_Interval(RIGHT, 10, 13);Add(4); break;

using namespace bots_to_spawn;

void Lvl_2_Spwn_Script()
{
	if (gSpawnThisCycle)
	{
		int numSpawnWaves = gSpawnCycleTot;	// Pour aller dans la switch et déterminé quel va être le spawn
		int skip = 0;						// Représente le nombre de fois qu'on va Skip un cycle de spawn selon l'indice de temps: Delay * Spawn_Cycle
		
		// POUR GET LE MAX
		//	spawnGrid->Get_MaxSpwnCrdX() - 1
		//	spawnGrid->Get_MaxSpwnCrdY() - 1
		//Add(300);
		
		// Toujours un bot par défaut à chaque wave
		Add(1);
		
		switch (numSpawnWaves)
		{
		case 1: 
			gNumSpawnTOT = 0; Set_Dr_Map_1(TXT_SPD_DR * 4); skip = 3; break; // Erase la border juste si le joueur est pas en mode quickstartS
		case 2:	gBoxSide = DOWN; break;
		case 3: gBoxSide = DOWN;
			MsgQueue::Register(ENABLE_ITEM_SPAWN);	// Start les spawns là
			break;
		case 4:gVerticalBorder = true; break;	// it's all random wut? It is!
		case 5:gHorizontalBorder = true; Add(1);break;
		case 6:gVerticalBorder = true;break;
		case 7:gHorizontalBorder = true;break;
		case 8:gVerticalBorder = true;break;
		case 9:gVerticalBorder = true;break;
		case 10:Add(2);break;
		case 11:gHorizontalBorder = true;break;
		case 12:gVerticalBorder = true;break;
		case 13:gVerticalBorder = true;break;
		case 14:gHorizontalBorder = true;break;
		case 15:Add(2);break;
		case 16:gVerticalBorder = true;break;		// Add(1); gBoxSide = LEFT; gSpwNum = spawnGrid->Get_MaxSpwnCrdY() - 1; // CETTE FORMULE CRASH 100% DU TEMPS
		case 17:gHorizontalBorder = true;break;
		case 18:gVerticalBorder = true;break;
		case 19:Add(3);break;
		case 20:				
			// ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS 
			gNumSpawnTOT = 0;skip = 5;
			MsgQueue::Register(CHECKPOINT_REACHED);
			break;//BREAKHERERHERHERHEHREHRHERHEHRHERBREAKHERERHERHERHEHREHRHERHEHRHERBREAKHERERHERHERHEHREHRHERHEHRHER

			
			// Les items sont aussi importants que les bots pour ce niveau?

		// Start les doubles spawns
		case 21:Add(1);break;
		case 22:Add(1); break;
		case 23:Add(1);break;
		case 24:Add(1); break;
		case 25:Add(1);break;
		case 26:Add(1);break;
		case 27:Add(1);break;
		case 28:Add(1);break;
		case 29:Add(1);break;
		case 30:Add(1);break;
		case 31:Add(2); Set_Interval(UP,5,9);break;
		case 32:Add(1); Set_Interval(DOWN,5,9);break;
		case 33:Add(1); Set_Interval(UP,5,9);break;
		case 34:Add(2); Set_Interval(DOWN,5,9); break;
		case 35:skip = 1; break;
		case 36:Add(2);Set_Interval(LEFT, 5, 9);break;
		case 37:Add(1);Set_Interval(RIGHT, 5, 9);break;
		case 38:Add(1);Set_Interval(LEFT, 5, 9);break;
		case 39:Add(2);Set_Interval(RIGHT, 5, 9); break;
		case 40: 

			gNumSpawnTOT = 0;skip = 8;
			Set_Event_String(1);	
			Ev_MultiColor_Warnings();// WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNINGbreak;
			gSpwBotTimer.Start_Timer(SPW_BOT_SPD_LVL2 + 150, 1, true);	// speed is inscreased!!!
			ItemSpawner::Add_To_Pool(ItemType::BUFFER, BUFFER_SPEED_LVL2 + 15, 4);
			ItemSpawner::Add_To_Pool(ItemType::BLOCKER, BLOCKER_SPEED_LVL2 + 150, 3);	// woah :O
			MsgQueue::Register(CHECKPOINT_REACHED);

			// ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS 
			break; //BREAKHERERHERHERHEHREHRHERHEHRHERBREAKHERERHERHERHEHREHRHERHEHRHERBREAKHERERHERHERHEHREHRHERHEHRHER

		case 41: break;
		case 42: break;
		case 43: break;
		case 44: break;
		case 45: break;
		case 46: break;
		case 47: break;
		case 48: break;
		case 49: break;

			// Random spawns
		case 50:Add(1);break;
		case 51:Add(1);break;
		case 52:Add(1);break;
		case 53:Add(1);break;
		case 54:Add(1);break;
		case 55:Add(1);break;
		case 56:Add(2);break;
		case 57:Add(1);break;
		case 58:Add(2);break;
		case 59:Add(1);break;
		case 60:Add(2);break;
		case 61:Add(1);break;
		case 62:Add(2);break;
		case 63:Add(1);break;
		case 64:Add(2);break;
		case 65:Add(1);break;
		case 66:Add(4);break;
		case 67:
			// TOOLS SPAWN SPEED INCREASED!
		//	Ev_MultiColor_Warnings();// WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNINGbreak;
			// ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS 

			gNumSpawnTOT = 0;
			skip = 7;
			MsgQueue::Register(CHECKPOINT_REACHED);
			break; //BREAKHERERHERHERHEHREHRHERHEHRHERBREAKHERERHERHERHEHREHRHERHEHRHERBREAKHERERHERHERHEHREHRHERHEHRHER

		case 68:break;
		case 69:Add(2);break;
		case 70:break;
		case 71:Add(2);break;
		case 72:break;
		case 73:Add(2);break;
		case 74:break;
		case 75:Add(2);break;
		case 76:break;
		case 77:Add(2);break;
		case 78:Set_Interval(LEFT, 4, 6);Add(3);break;
		case 79:skip = 3;break;
		case 80:  

			// FINAL PUSH	
			// Remplie la console au complet de blockers :O		
			for (int c = 0; c < MAX_ITEMS; c++)
				ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 0,0 });
			// Remplie la console au complet de blockers :O

			gNumSpawnTOT = 0; 
			skip = 7;	
			gCurrentCheckPoints[gCurrentLevel + 1]++;
			gSpwBotTimer.Start_Timer(500, 1, true);
			MsgQueue::Register(FINAL_PUSH);
			MsgQueue::Register(CHECKPOINT_REACHED);

			break;
		
			// Start les quad spawns!!
		case 81:gVerticalBorder = true; Add(3); break;
		case 83:gHorizontalBorder = true; Add(3); break;
		case 84:gHorizontalBorder = true; Add(3); break;
		case 87:gVerticalBorder = true; Add(3); break;

			// Biggest rush of all time
		case 88: gVerticalBorder = true; Add(1); break;		
		case 89: gHorizontalBorder = true; Add(1); break;
		case 90: gVerticalBorder = true; Add(1); break;
		case 91: gHorizontalBorder = true;  Add(1); break;
		case 92: gVerticalBorder = true; Add(1); break;
		case 93: gHorizontalBorder = true; Add(1); break;
		case 94: gVerticalBorder = true; Add(1); break;
		case 95: gHorizontalBorder = true; Add(1); break;
		case 96: gVerticalBorder = true; Add(1); break;
		case 97: gHorizontalBorder = true;Add(1); break;
		case 98: gVerticalBorder = true; Add(1); break;
		case 99: Add(2); break;


		case 100: 		
			MsgQueue::Register(STOP_BOT_SPAWNS);
			Ev_Wait_For_Victory(); // Wait que le dernier bot meurt pour trigger la victoire
			break;

		//case 101: skip = 3; break;
		//case 102:break;
		//case 103:break;
		//case 104:break;
		//case 105:gBoxSide = LEFT;  Add(1);break;
		//case 106:gBoxSide = LEFT;  Add(1);break;
		//case 107:break;
		//case 108:Add_Spec(LEFT, -1);  break;
		//case 109:break;
		//case 110:Add_Spec(RIGHT, -1);  Add(1);break;
		//case 111:Add_Spec(RIGHT, -1);  Add(1); skip = 1;break;
		//case 112:Add_Spec(RIGHT, -1);  Add(1);skip = 1; break;
		//case 113:Add_Spec(LEFT, -1);  Add(1);skip = 2; break;
		//case 114:Add_Spec(LEFT, -1);  Add(1);skip = 1;break;
		//case 115:Add_Spec(LEFT, -1);  Add(1);skip = 2;break;
		//case 116:gBoxSide = LEFT;  Add(1);break;
		//case 117:  Add(1);break;
		//case 118:  Add(1);break;
		//case 119:  Add(1);break;
		//case 120:  Add(1); break;
		//case 121:  Add(1); break;
		//case 122:  Add(1); break;
		//case 123:  Add(1);

		}

		// Ceci ajoute du temps entre le spawn actuel et le prochain
		if(skip)
			gSpwBotTimer.Add_Count(skip);
	}
}
