

#include "lvl_2_spwn_script.h"
#include "../../time/spawn_cycle.h"
#include "../../grid/managegrids.h"
#include "../../spawns/bots_to_spawn.h"
#include "../../events/msg_dispatcher.h"

//some events Shhh...
#include "../../items/item_spawner.h"
#include "../../events/global_events/ev_warning.h"
#include "../../events/global_events/feedback/ev_draw_map.h"

// GENERAL RULES FOR THIS DUMB BROKEN SHIT: 
// D�passe jamais le nombre de spawn permis sur une bordure
// AddSpecific(): Ne setup jamais une boxside random avec un spw pr�cis
// CETTE FORMULE CRASH 100% DU TEMPS // Add(1); gBoxSide = LEFT; gSpwNum = spawnGrid->Get_MaxSpwnCrdY() - 1; 
// Combiner BoxSide, Spwnum avec plus qu'un spawn, �a cr�er des exceptions
// Setup un intervalle de spawn trop petit pour le total va faire crash� le shit Ex : Set_Interval(RIGHT, 10, 13);Add(4); break;

using namespace bots_to_spawn;

void Lvl_2_Spwn_Script()
{
	if (gSpawnThisCycle)
	{
		int numSpawnWaves = gSpawnCycleTot;	// Pour aller dans la switch et d�termin� quel va �tre le spawn
		int skip = 0;						// Repr�sente le nombre de fois qu'on va Skip un cycle de spawn selon l'indice de temps: Delay * Spawn_Cycle
		
		// POUR GET LE MAX
		//	spawnGrid->Get_MaxSpwnCrdX() - 1
		//	spawnGrid->Get_MaxSpwnCrdY() - 1
		//Add(300);
		
		// Toujours un bot par d�faut � chaque wave
		Add(1);
		
		switch (numSpawnWaves)
		{
		case 1: 
			gNumSpawnTOT = 0; Erase_Map_Borders_1(84); skip = 4; break; // Erase la border juste si le joueur est pas en mode quickstartS
		case 2:MsgQueue::Register(ENABLE_ITEM_SPAWN); gBoxSide = DOWN; break;
		case 3: gBoxSide = DOWN;break;
		case 4:break;	// it's all random wut? It is
		case 5:break;
		case 6:break;
		case 7:break;
		case 8:break;
		case 9:break;
		case 10:break;	
		case 11:break;
		case 12:break;
		case 13:break;
		case 14:break;
		case 15:break;
		case 16:break;		// Add(1); gBoxSide = LEFT; gSpwNum = spawnGrid->Get_MaxSpwnCrdY() - 1; // CETTE FORMULE CRASH 100% DU TEMPS
		case 17:break;
		case 18:break;
		case 19:break;
		case 20:				
			// ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS 
			gNumSpawnTOT = 0;skip = 6;
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
		case 31:Add(1); Set_Interval(UP,5,9);break;
		case 32:Add(1); Set_Interval(DOWN,5,9);break;
		case 33:Add(1); Set_Interval(UP,5,9);break;
		case 34:Add(1); Set_Interval(DOWN,5,9); break;
		case 35:skip = 1; break;
		case 36:Add(1);Set_Interval(LEFT, 5, 9);break;
		case 37:Add(1);Set_Interval(RIGHT, 5, 9);break;
		case 38:Add(1);Set_Interval(LEFT, 5, 9);break;
		case 39:Add(1);Set_Interval(RIGHT, 5, 9); break;
		case 40: 
			Ev_MultiColor_Warnings();// WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNINGbreak;
			gSpwBotTimer.Start_Timer(475, 1, true);	// speed is inscreased!!!

			// ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS 
			gNumSpawnTOT = 0;skip = 8;
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
		case 51:Add(2);break;
		case 52:Add(1);break;
		case 53:Add(2);break;
		case 54:Add(1);break;
		case 55:Add(1);break;
		case 56:Add(1);break;
		case 57:Add(2);break;
		case 58:Add(1);break;
		case 59:Add(2);break;
		case 60:Add(1);break;
		case 61:Add(1);break;
		case 62:Add(2);break;
		case 63:Add(2);break;
		case 64:Add(2);break;
		case 65:Add(1);break;
		case 66:Add(1);break;
		case 67:
			
			gNumSpawnTOT = 0; skip = 1;


			break;

		case 68:break;
		case 69:Add(1);break;
		case 70:break;
		case 71:Add(1);break;
		case 72:break;
		case 73:Add(1);break;
		case 74:break;
		case 75:Add(1);break;
		case 76:break;
		case 77:Add(1);break;
		case 78:break;
		case 79:Set_Interval(LEFT, 4, 6);Add(3);break;
		case 80:  
			// TOOLS SPAWN SPEED INCREASED!
			Ev_MultiColor_Warnings();// WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNINGbreak;
			// ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS  ITEMS 
			
			skip = 7;
			break; //BREAKHERERHERHERHEHREHRHERHEHRHERBREAKHERERHERHERHEHREHRHERHEHRHERBREAKHERERHERHERHEHREHRHERHEHRHER
		
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

			// FINAL PUSH	

		case 100: 
			for (int c = 0; c < linkGrid->Get_Cols(); c++)	// Soit �a, ou un gros X en plein milieu
			{
				ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { c,4 }, false);
				ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { c,10 }, false);
			}


			gNumSpawnTOT = 0; MsgQueue::Register(FINAL_PUSH); 
			gSpwBotTimer.Start_Timer(500, 1, true);	
			skip = 7;	break;
		case 101: skip = 3; break;
		case 102:break;
		case 103:break;
		case 104:break;
		case 105:gBoxSide = LEFT;  Add(1);break;
		case 106:gBoxSide = LEFT;  Add(1);break;
		case 107:break;
		case 108:Add_Specific(LEFT, -1);  break;
		case 109:break;
		case 110:Add_Specific(RIGHT, -1);  Add(1);break;
		case 111:Add_Specific(RIGHT, -1);  Add(1); skip = 1;break;
		case 112:Add_Specific(RIGHT, -1);  Add(1);skip = 1; break;
		case 113:Add_Specific(LEFT, -1);  Add(1);skip = 2; break;
		case 114:Add_Specific(LEFT, -1);  Add(1);skip = 1;break;
		case 115:Add_Specific(LEFT, -1);  Add(1);skip = 2;break;
		case 116:gBoxSide = LEFT;  Add(1);break;
		case 117:  Add(1);break;
		case 118:  Add(1);break;
		case 119:  Add(1);break;
		case 120:  Add(1); break;
		case 121:  Add(1); break;
		case 122:  Add(1); break;
		case 123:  Add(1);
			MsgQueue::Register(STOP_BOT_SPAWNS); 
			MsgQueue::Register(WAIT_LAST_BOT); break;
		}

		// Ceci ajoute du temps entre le spawn actuel et le prochain
		if(skip)
			gSpwBotTimer.Add_Count(skip);
	}
}
//	// V1
//case 1: skip = 6; break; // test
//case 2:Add_Specific(RIGHT, 0);Add_Specific(RIGHT, 1); Add_Specific(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 1);Add_Specific(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 2);Add_Specific(LEFT, 6);  skip = 2; break;
//case 3:Add_Specific(RIGHT, 5); break;// Dessine un pattern de d�part
//case 4:Add_Specific(RIGHT, 9);break;
//case 5:Add_Specific(RIGHT, 7);break;
//case 6:Add(1);gBoxSide = RIGHT; break;
//case 7:Add(1);gBoxSide = RIGHT; break;
//case 8:Add(1);gBoxSide = RIGHT; break;
//case 9:Add(1);gBoxSide = RIGHT; break;
//case 10:Add(1); Add_Specific(RIGHT, spawnGrid->Get_MaxSpwnCrdY() - 1);break;	// Premier Double
//case 11:Add(1); break;
//case 12:Add(1); gBoxSide = LEFT; gSpwNum = 0; break;
//case 13:gBoxSide = LEFT; gSpwNum = 1; break;
//case 14:Add(1); gBoxSide = LEFT; gSpwNum = 2; break;
//case 15:gBoxSide = LEFT; gSpwNum = 3; break;
//case 16:Add(1); gBoxSide = LEFT; Add_Specific(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 1); break;		// Add(1); gBoxSide = LEFT; gSpwNum = spawnGrid->Get_MaxSpwnCrdY() - 1; // CETTE FORMULE CRASH 100% DU TEMPS
//case 17:gBoxSide = RIGHT;Add_Specific(RIGHT, spawnGrid->Get_MaxSpwnCrdY() / 2); break;
//case 18:gBoxSide = LEFT; Add_Specific(LEFT, spawnGrid->Get_MaxSpwnCrdY() / 2);break;
//case 19:Add(1); break;
//case 20:Add(1); break;
//case 21:Add(1); break;
//case 22:Add(1); break;
//case 23:Add(1); break;
//case 24:Add(1); break;
//case 25:Add(1); break;
//case 26:Add(1); break;
//case 27:Add(1); break;
//case 28:Add(1); break;
//case 29:Add(1); break;
//	// Start les doubles spawns
//case 30: skip = 7;break;//BREAKHERERHERHERHEHREHRHERHEHRHERBREAKHERERHERHERHEHREHRHERHEHRHERBREAKHERERHERHERHEHREHRHERHEHRHER
//case 31:Add(1); Set_Interval(RIGHT, 5, 6);break;
//case 32:Add(1); Set_Interval(RIGHT, 5, 6);break;
//case 33:Add(1); Set_Interval(RIGHT, 5, 6);break;
//case 34:Add(1); Set_Interval(RIGHT, 5, 6); break;
//case 35:Add(1); Add_Specific(LEFT, 0); Add_Specific(RIGHT, spawnGrid->Get_MaxSpwnCrdY() - 1);break;
//case 36:Add_Specific(LEFT, 0); Add_Specific(RIGHT, spawnGrid->Get_MaxSpwnCrdY() - 1); break; //Set_Interval(RIGHT, 9,10);
//case 37:Add_Specific(LEFT, 0); Add_Specific(RIGHT, spawnGrid->Get_MaxSpwnCrdY() - 1); break;
//case 38:Add_Specific(LEFT, 0); Add_Specific(RIGHT, spawnGrid->Get_MaxSpwnCrdY() - 1); break;
//case 39:Add_Specific(LEFT, 0); Add_Specific(RIGHT, spawnGrid->Get_MaxSpwnCrdY() - 1);  break;
//
//case 40: Set_Interval(LEFT, 2, 3); Add(1); break;
//case 41: Set_Interval(LEFT, 2, 3); Add(1); break;
//case 42: Set_Interval(LEFT, 2, 3); Add(1); break;
//case 43: Set_Interval(LEFT, 2, 3); Add(1); break;
//case 44: Set_Interval(LEFT, 2, 3); Add(1); break;
//case 45: Set_Interval(RIGHT, 11, 12);  Add(1);break;
//case 46: Set_Interval(RIGHT, 11, 12);  Add(1);break;
//case 47: Set_Interval(RIGHT, 10, 12);Add(3); break;
//case 48: Set_Interval(RIGHT, 10, 13);Add(3); break;
//case 49: skip = 8;
//	ItemSpawner::Spawn_This_Item(ItemType::HEALTH, { 1,1 }); // Spawn de la vie ici?
//	break; //BREAKHERERHERHERHEHREHRHERHEHRHERBREAKHERERHERHERHEHREHRHERHEHRHERBREAKHERERHERHERHEHREHRHERHEHRHER
//
//	// Random spawns
//case 50:Add(1);break;
//case 51:Add(2);break;
//case 52:Add(1);break;
//case 53:Add(2);break;
//case 54:Add(1);break;
//case 55:Add(2);break;
//case 56:Add(1);break;
//case 57:Add(2);break;
//case 58:Add(1);break;
//case 59:Add(2);break;
//case 60:Add(1);break;
//case 61:Add(1);break;
//case 62:Add(3);break;
//case 63:Add(4);break;
//case 64:Add(5);break;
//case 65:Add(1);break;
//case 66:Add(1);break;
//case 67:
//	Ev_MultiColor_Warnings();	// WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
//	gSpwBotTimer.Start_Timer(800, 1, true);	// speed is inscreased!!!
//	skip = 7;break; //BREAKHERERHERHERHEHREHRHERHEHRHERBREAKHERERHERHERHEHREHRHERHEHRHERBREAKHERERHERHERHEHREHRHERHEHRHER
//
//	// Start les triples spawns!!
//case 80: Set_Interval(LEFT, 0, 4);Add(2); break;
//case 81: Set_Interval(RIGHT, 4, 8);Add(2); break;
//case 83: Set_Interval(LEFT, 8, 12);Add(2); break;
//case 84: Set_Interval(LEFT, 0, 4);Add(2); break;
//case 87: Set_Interval(RIGHT, 4, 8);Add(2); break;
//case 88: Set_Interval(LEFT, 8, 12);Add(2); break;
//case 99: Add(2); break;
//
//	// FINAL PUSH	
//
//case 100:
//	gNumSpawnTOT = 0; MsgQueue::Register(FINAL_PUSH);
//	gSpwBotTimer.Start_Timer(600, 1, true);	// speed is decreased
//	skip = 5;	break;
//case 101: skip = 3; break;
//case 102:break;
//case 103:break;
//case 104:break;
//case 105:gBoxSide = LEFT;  Add(1);break;
//case 106:gBoxSide = LEFT;  Add(1);break;
//case 107:break;
//case 108:Add_Specific(LEFT, -1);  break;
//case 109:break;
//case 110:Add_Specific(RIGHT, -1);  Add(1);break;
//case 111:Add_Specific(RIGHT, -1);  Add(1); skip = 1;break;
//case 112:Add_Specific(RIGHT, -1);  Add(1);skip = 1; break;
//case 113:Add_Specific(LEFT, -1);  Add(1);skip = 2; break;
//case 114:Add_Specific(LEFT, -1);  Add(1);skip = 1;break;
//case 115:Add_Specific(LEFT, -1);  Add(1);skip = 2;break;
//case 116:gBoxSide = LEFT;  Add(1);break;
//case 117:  Add(1);break;
//case 118:  Add(1);break;
//case 119:  Add(1);break;
//case 120:  Add(1); break;
//case 121:  Add(1); break;
//case 122:  Add(1); break;
//case 123:  Add(1);
//	MsgQueue::Register(STOP_BOT_SPAWNS);
//	MsgQueue::Register(WAIT_LAST_BOT); break;