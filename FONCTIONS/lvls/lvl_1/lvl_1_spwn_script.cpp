

#include "../../time/spawn_cycle.h"
#include "../../grid/managegrids.h"
#include "../../spawns/bots_to_spawn.h"
#include "../../events/msg_dispatcher.h"
#include "lvl_1_spwn_script.h"
#include "../lvl_script.h"

//some events Shhh...
#include "../../items/item_spawner.h"
#include "../../events/global_events/ev_warning.h"
#include "../../events/global_events/feedback/ev_draw_map.h"
#include "../../events/global_events/ev_wait_last_bot.h"

// GENERAL RULES FOR THIS DUMB BROKEN SHIT: 
// Dépasse jamais le nombre de spawn permis sur une bordure
// AddSpecific(): Ne setup jamais une boxside random avec un spw précis
// CETTE FORMULE CRASH 100% DU TEMPS // Add(1); gBoxSide = LEFT; gSpwNum = spawnGrid->Get_MaxSpwnCrdY() - 1; 
// Combiner BoxSide, Spwnum avec plus qu'un spawn, ça créer des exceptions
// Setup un intervalle de spawn trop petit pour le total va faire crashé le shit Ex : Set_Interval(RIGHT, 10, 13);Add(4); break;

using namespace bots_to_spawn;

void Lvl_1_Spwn_Script()
{
	if (gSpawnThisCycle)
	{
		int numSpawnWaves = gSpawnCycleTot;	// Pour aller dans la switch et déterminé quel va être le spawn
		int skip = 0;						// Représente le nombre de fois qu'on va Skip un cycle de spawn selon l'indice de temps: Delay * Spawn_Cycle
		
		// POUR GET LE MAX
		//	spawnGrid->Get_MaxSpwnCrdX() - 1
		//	spawnGrid->Get_MaxSpwnCrdY() - 1
		//Add(300);
		
		if (numSpawnWaves < 67) // Tout les spawns seront verticaux jusqu'au final push du level
		{
			gVerticalBorder = true;
		}
		else
		{
			gHorizontalBorder = true;
		}
		
		switch (numSpawnWaves)
		{	


		////PUZZLE START------------------------------------------------------------------
			// Tirer au milieu!
		case 1: Set_Dr_Map_1(TXT_SPD_DR * 4); skip = 2;
			gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() / 2 ,linkGrid->Get_Rows() / 2 }, LEFT, 1);
			gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() / 2 ,linkGrid->Get_Rows() / 2 }, RIGHT, 1);
			break; // Erase la border seulement si le joueur est en mode quickstartS
			    
		case 2: Add(1); gBoxSide = RIGHT;gSpwNum = spawnGrid->Get_MaxSpwnCrdY() / 2; break;
		case 3: Add(1); gBoxSide = RIGHT;gSpwNum = spawnGrid->Get_MaxSpwnCrdY() / 2; break;
		case 4: Add(1); gBoxSide = RIGHT;gSpwNum = spawnGrid->Get_MaxSpwnCrdY() / 2; skip = 1; break;
		case 5: Add(1); gBoxSide = RIGHT;gSpwNum = spawnGrid->Get_MaxSpwnCrdY() / 2; break;
		case 6: Add(1); gBoxSide = RIGHT;gSpwNum = spawnGrid->Get_MaxSpwnCrdY() / 2; break;
		case 7: Add(1); gBoxSide = RIGHT;gSpwNum = spawnGrid->Get_MaxSpwnCrdY() / 2; skip = 1; break;
		case 8: Add(1); gBoxSide = RIGHT;gSpwNum = spawnGrid->Get_MaxSpwnCrdY() / 2; break;
		case 9: Add(1); gBoxSide = RIGHT;gSpwNum = spawnGrid->Get_MaxSpwnCrdY() / 2; break;
		case 10:Add(1); gBoxSide = RIGHT;gSpwNum = spawnGrid->Get_MaxSpwnCrdY() / 2;
			MsgQueue::Register(CHECKPOINT_REACHED);
			break;
			
			
			////PUZZLE START------------------------------------------------------------------
			//Add(1);gBoxSide = RIGHT; gSpwNum = 0;break;
			//Add(1);gBoxSide = RIGHT; gSpwNum = 1; break;
			//Add(1);gBoxSide = RIGHT; gSpwNum = 2; break;
			//Add(1);gBoxSide = RIGHT; gSpwNum = 3; break;
			//Add(1);gBoxSide = RIGHT; gSpwNum = 4; break;
			//Add(1);gBoxSide = RIGHT; gSpwNum = 0; Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() / 2); Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() / 2 + 1); break;		// Add(1); gBoxSide = LEFT; gSpwNum = spawnGrid->Get_MaxSpwnCrdY() - 1; // CETTE FORMULE CRASH 100% DU TEMPS
			//Add(1);gBoxSide = RIGHT; Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() / 2 + 2); break;
			//Add(1);gBoxSide = RIGHT; Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() / 2 + 3);break;
			////puzzle end------------------------------------------------------------------


		
		case 11: /*Set_Custom_Bot(SPWN_DLAY * 1.3f); skip = 3;*/ Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() / 2);  break;
		case 12: Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() / 2 - 1);break;
		case 13: Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() / 2 - 2);break;
		case 14: Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() / 2 - 3);break;
		case 15: Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() / 2 - 4);break;
		case 16: Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() / 2 - 5);break;
		case 17: Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() / 2 - 6);break;
		case 18: Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() / 2 - 7); break;
		case 19: Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() / 2);  break;
		case 20: Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() / 2 + 1);break;
		case 21: Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() / 2 + 2);break;
		case 22: Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() / 2 + 3);break;
		case 23: Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() / 2 + 4);break;
		case 24: Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() / 2 + 5);break;
		case 25: Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() / 2 + 6);
			MsgQueue::Register(CHECKPOINT_REACHED);
			break;

		case 26:Add(1);gBoxSide = RIGHT; gSpwNum = 0; break;			//Add(1);gBoxSide = RIGHT; gSpwNum = 5; break;
		case 27:Add(1);gBoxSide = RIGHT; gSpwNum = 1; break;			//Add(1);gBoxSide = RIGHT; gSpwNum = 4; break;
		case 28:Add(1);gBoxSide = RIGHT; gSpwNum = 2; break;			//Add(1);gBoxSide = RIGHT; gSpwNum = 3; break;
		case 29:Add(1);gBoxSide = RIGHT; gSpwNum = 3; break;			//Add(1);gBoxSide = RIGHT; gSpwNum = 2; break;
		case 30:Add(1);gBoxSide = RIGHT; gSpwNum = 4; break;			//Add(1);gBoxSide = RIGHT; gSpwNum = 1; break;
		case 31:Add(1);gBoxSide = RIGHT; gSpwNum = 5; break;			//Add(1);gBoxSide = RIGHT; gSpwNum = 0; break;
		case 32:Add(1);gBoxSide = RIGHT; gSpwNum = 6; skip = 1; break;
		case 33:Add(1);gBoxSide = RIGHT; gSpwNum = 0; break;
		case 34:Add(1);gBoxSide = RIGHT; gSpwNum = 1; break;
		case 35:Add(1);gBoxSide = RIGHT; gSpwNum = 2; break;
		case 36:Add(1);gBoxSide = RIGHT; gSpwNum = 3; break;
		case 37:Add(1);gBoxSide = RIGHT; gSpwNum = 4; break;
		case 38:Add(1);gBoxSide = RIGHT; gSpwNum = 5; break;
		case 39:Add(1);gBoxSide = RIGHT; gSpwNum = 6; skip = 1; break;
		case 40:gBoxSide = RIGHT; gSpwNum = 0; break;
		case 41:gBoxSide = RIGHT; gSpwNum = 1; break;
		case 42:gBoxSide = RIGHT; gSpwNum = 2; break;
		case 43:gBoxSide = RIGHT; gSpwNum = 3; break;
		case 44:gBoxSide = RIGHT; gSpwNum = 4; break;
		case 45:gBoxSide = RIGHT; gSpwNum = 5; break;
		case 46:gBoxSide = RIGHT; gSpwNum = 6; 
			MsgQueue::Register(CHECKPOINT_REACHED);
			break;
			
			
			
			
			
			
			
			
		


			////PUZZLE START------------------------------------------------------------------	top mid bot, top mid bot
			//gGrids.Make_Chain_Of_Walls({ 2,0 }, DOWN, 2);
			//gGrids.Make_Chain_Of_Walls({ 0, (linkGrid->Get_Rows() - 1) / 2 }, RIGHT, 2);
			//Add(1);gBoxSide = RIGHT; gSpwNum = 0; break;
			//Add(1);gBoxSide = RIGHT; gSpwNum = spawnGrid->Get_MaxSpwnCrdY() - 1; break;
			//Add(1);gBoxSide = RIGHT; gSpwNum = spawnGrid->Get_MaxSpwnCrdY() / 2; break;
			//Add(1);gBoxSide = RIGHT; gSpwNum = 0; break;
			//Add(1);gBoxSide = RIGHT; gSpwNum = spawnGrid->Get_MaxSpwnCrdY() - 1; break;
			//Add(1);gBoxSide = RIGHT; gSpwNum = spawnGrid->Get_MaxSpwnCrdY() / 2; skip = 1; break;	
			//Add(1);gBoxSide = RIGHT; gSpwNum = spawnGrid->Get_MaxSpwnCrdY() - 1;break;			
			//Add(1);gBoxSide = RIGHT; gSpwNum = spawnGrid->Get_MaxSpwnCrdY() / 2; break;			
			//Add(1);gBoxSide = RIGHT; gSpwNum = 0; break;											
			//Add(1);gBoxSide = RIGHT; gSpwNum = spawnGrid->Get_MaxSpwnCrdY() - 1;break;			
			//Add(1);gBoxSide = RIGHT; gSpwNum = spawnGrid->Get_MaxSpwnCrdY() / 2; break;			
			//Add(1);gBoxSide = RIGHT; gSpwNum = 0; skip = 2; break;
			//Add(1);gBoxSide = LEFT; gSpwNum = spawnGrid->Get_MaxSpwnCrdY() - 1;break;
			//Add(1);gBoxSide = LEFT; gSpwNum = spawnGrid->Get_MaxSpwnCrdY() / 2; break;
			//Add(1);gBoxSide = LEFT; gSpwNum = 0;  break;
			//Add(1);gBoxSide = LEFT; gSpwNum = spawnGrid->Get_MaxSpwnCrdY() - 1;break;
			//Add(1);gBoxSide = LEFT; gSpwNum = spawnGrid->Get_MaxSpwnCrdY() / 2; break;
			//Add(1);gBoxSide = LEFT; gSpwNum = 0; skip = 1; break;

			//Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 1);
			//Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() - 1);
			//Add_Spec(LEFT, 0);
			//Add_Spec(RIGHT, 0);
			//MsgQueue::Register(CHECKPOINT_REACHED);
			//break;
			////puzzle end------------------------------------------------------------------

				
				
				
				


		////PUZZLE START------------------------------------------------------------------
		// Doubles spawns left and Right!
		//gGrids.Make_Chain_Of_Walls({ 0, linkGrid->Get_Rows() - 4 }, RIGHT, 8);
		//Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 3); /*MsgQueue::Register(START_BOT_SPAWNS); */break;
		//Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 3); 			break;// Dessine un pattern de départ
		//Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 3);break;
		//Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 3);break;
		//Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 4);break;
		//Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 4);break;
		//Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 4);break;
		//Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 3);break;
		//Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 3); Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 1);break;	// Spawn Left Now
		////puzzle end------------------------------------------------------------------
		

		////PUZZLE START------------------------------------------------------------------
		//case 19:Add(1);gBoxSide = LEFT; break;
		//case 20:Add(1);gBoxSide = RIGHT;skip = 1; break;
		//case 21:Add(1);gBoxSide = LEFT; break;
		//case 22:Add(1);gBoxSide = RIGHT;skip = 1; break;
		//case 23:Add(1);gBoxSide = LEFT; break;
		//case 24:Add(1);gBoxSide = RIGHT; skip = 1;  break;
		//case 25:Add(1);gBoxSide = LEFT; break;
		//case 26:Add(1); gBoxSide = RIGHT;skip = 1; break;
		//case 27:Add(1);gBoxSide = LEFT; break;
		//case 28:Add(1); gBoxSide = RIGHT;skip = 1; break;
		//case 29: gNumSpawnTOT = 0;break;
		////puzzle end------------------------------------------------------------------

		//////PUZZLE START------------------------------------------------------------------
		//Add(1); Set_Interval(RIGHT,5,6);break;
		//Add(1); Set_Interval(RIGHT,5,6);break;
		//Add(1); Set_Interval(RIGHT,5,6);break;
		//Add(1); Set_Interval(RIGHT, 5, 6); skip = 3; break;
		//Add(1); Add_Spec(LEFT, 0); Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() - 1);break;
		//Add_Spec(LEFT, 0); Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() - 1); break; //Set_Interval(RIGHT, 9,10);
		//Add_Spec(LEFT, 0); Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() - 1); break;
		//Add_Spec(LEFT, 0); Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() - 1); break;
		//Add_Spec(LEFT, 0); Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() - 1); skip = 3; break;
			////puzzle end------------------------------------------------------------------

		////PUZZLE START------------------------------------------------------------------
		//Set_Interval(LEFT, 2, 3); Add(2); break;
		//Set_Interval(LEFT, 2,4); Add(2); break;
		//Set_Interval(LEFT, 2,5); Add(2); break;
		//Set_Interval(LEFT, 2,6); Add(2); break;
		//Set_Interval(LEFT, 2, 7); Add(2); skip = 3; break;
		//Set_Interval(RIGHT, spawnGrid->Get_MaxSpwnCrdY() - 3, spawnGrid->Get_MaxSpwnCrdY() - 1);Add(1);break;
		//Set_Interval(RIGHT, spawnGrid->Get_MaxSpwnCrdY() - 4, spawnGrid->Get_MaxSpwnCrdY() - 1);Add(1);break;
		//Set_Interval(RIGHT, spawnGrid->Get_MaxSpwnCrdY() - 5, spawnGrid->Get_MaxSpwnCrdY() - 1);Add(3); break;
		//Set_Interval(RIGHT, spawnGrid->Get_MaxSpwnCrdY() - 6, spawnGrid->Get_MaxSpwnCrdY() - 1);Add(3); break;
		//gNumSpawnTOT = 0; 	MsgQueue::Register(CHECKPOINT_REACHED); break;
		////puzzle end------------------------------------------------------------------

		case 50:			
			ItemSpawner::Spawn_This_Item(ItemType::HEALTH, { 1,1 }); // Spawn de la vie ici?
			gNumSpawnTOT = 0; skip = 5;
			gSpwBotTimer.Start_Timer(800, 1, true);	// speed is inscreased!!!
			break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE break;

			// Le joueur va voir la chaine des mur et va tout de suite la renforcer, MAIS! Un bot vertical va venir la détruire mouhahaha!
			gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 1, 6 }, LEFT, 4);
			Add_Spec(UP, spawnGrid->Get_Cols() - 1);
			Add_Spec(DOWN, spawnGrid->Get_Cols() - 1);

		// Random spawns
		case 51:Add(1);break;
		case 52:Add(1);break;
		case 53:Add(1);break;
		case 54:Add(1);break;
		case 55:Add(1);break;
		case 56:Add(1);break;
		case 57:Add(2);break;
		case 58:Add(1);break;
		case 59:Add(2);break;
		case 60:Add(1);break;
		case 61:Add(2);break;
		case 62:Add(1);break;
		case 63:Add(1); skip = 2; break;
		case 64:Add(3);break;
		case 65:Add(4);break;
		case 66:Add(5);break;
		case 67:gNumSpawnTOT = 0;skip = 7;
			

		
		
			// Start les quad spawns!! too hard poyo
		case 80: Set_Interval(LEFT, 4,6);Add(3); break;
		case 81: Set_Interval(RIGHT, 4,8);Add(3); break;
		case 83: Set_Interval(LEFT, 8,12);Add(3); break;
		case 84: Set_Interval(LEFT, 4,6);Add(3); break;
		case 87: Set_Interval(RIGHT, 4,8);Add(3); break;

			// Biggest rush of all time
		case 88: Set_Interval(LEFT, 8,12);Add(2); break;		
		case 89: Set_Interval(LEFT, 7,12);Add(2); break;
		case 90: Set_Interval(LEFT, 6,12);Add(2); break;
		case 91: Set_Interval(LEFT, 5,12);Add(2); break;
		case 92: Set_Interval(LEFT, 4,12);Add(2); break;
		case 93: Set_Interval(LEFT, 3,12);Add(2); break;
		case 94: Set_Interval(RIGHT, 7,12);Add(2); break;
		case 95: Set_Interval(RIGHT, 6,12);Add(2); break;
		case 96: Set_Interval(RIGHT, 5,12);Add(2); break;
		case 97: Set_Interval(RIGHT, 4,12);Add(2); break;
		case 98: Set_Interval(RIGHT, 3,12);Add(2); break;
		case 99: Add(2); break;

			// FINAL PUSH	
		case 100: 
			gNumSpawnTOT = 0; 	skip = 7;
			gSpwBotTimer.Start_Timer(500, 1, true);	
			
			MsgQueue::Register(CHECKPOINT_REACHED);
			MsgQueue::Register(FINAL_PUSH);
			break;// CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE 

		case 101: skip = 3; break;
		case 102:break;
		case 103:break;
		case 104:break;
		case 105:gBoxSide = LEFT;  Add(1);break;
		case 106:gBoxSide = LEFT;  Add(1);break;
		case 107:break;
		case 108:Add_Spec(LEFT, -1);  break;
		case 109:break;
		case 110:Add_Spec(RIGHT, -1);  Add(1);break;
		case 111:Add_Spec(RIGHT, -1);  Add(1); skip = 1;break;
		case 112:Add_Spec(RIGHT, -1);  Add(1);skip = 1; break;
		case 113:Add_Spec(LEFT, -1);  Add(1);skip = 2; break;
		case 114:Add_Spec(LEFT, -1);  Add(1);skip = 1;break;
		case 115:Add_Spec(LEFT, -1);  Add(1);skip = 2;break;
		case 116:gBoxSide = LEFT;  Add(1);break;
		case 117:  Add(1);break;
		case 118:  Add(1);break;
		case 119:  Add(1);break;
		case 120:  Add(1); break;
		case 121:  Add(1); break;
		case 122:  Add(1); break;
		case 123:  Add(1);
			MsgQueue::Register(STOP_BOT_SPAWNS); 
			Ev_Wait_For_Victory(); // Wait que le dernier bot meurt pour trigger la victoire
			break;
		}

		// Ceci ajoute du temps entre le spawn actuel et le prochain
		if(skip)
			gSpwBotTimer.Add_Count(skip);
	}
}


// VERSION 1: Jugé trop difficile
// Voici les checkpoints dans le lvl script
//const int LVL1_CHECKPOINT[] = { 30, 49, 67, 100 }; 


//case 1: Set_Dr_Map_1(TXT_SPD_DR * 2 + 3);skip = 2; break; // Erase la border seulement si le joueur est en mode quickstartS
//case 2:Add_Spec(RIGHT, 7); /*MsgQueue::Register(START_BOT_SPAWNS); */break;
//case 3:Add_Spec(RIGHT, 5); 			break;// Dessine un pattern de départ
//case 4:Add_Spec(RIGHT, 9);break;
//case 5:Add_Spec(RIGHT, 7);break;
//case 6:Add(1);gBoxSide = RIGHT; break;
//case 7:Add(1);gBoxSide = RIGHT; break;
//case 8:Add(1);gBoxSide = RIGHT; break;
//case 9:Add(1);gBoxSide = RIGHT; break;
//case 10:Add(1); Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 1);break;	// Premier Double. Spawn Left Now
//case 11:Add(1); gBoxSide = LEFT; break;
//case 12:Add(1); gBoxSide = LEFT; gSpwNum = 0; break;
//case 13:gBoxSide = LEFT; gSpwNum = 1; break;
//case 14:Add(1); gBoxSide = LEFT; gSpwNum = 2; break;
//case 15:gBoxSide = LEFT; gSpwNum = 3; break;
//case 16:gBoxSide = LEFT; gSpwNum = 0; Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() / 2); Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 1); break;		// Add(1); gBoxSide = LEFT; gSpwNum = spawnGrid->Get_MaxSpwnCrdY() - 1; // CETTE FORMULE CRASH 100% DU TEMPS
//case 17:gBoxSide = LEFT;Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() / 2); break;
//case 18:gBoxSide = LEFT; Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() / 2);break;
//	// Start les doubles spawns left and Right
//
//case 19:Add(1);gBoxSide = LEFT; break;
//case 20:Add(1);gBoxSide = RIGHT; break;
//case 21:Add(1);gBoxSide = LEFT; break;
//case 22:Add(1);gBoxSide = RIGHT;  break;
//case 23:Add(1);gBoxSide = LEFT; break;
//case 24:Add(1);gBoxSide = RIGHT;  break;
//case 25:Add(1);gBoxSide = LEFT; break;
//case 26:Add(1); gBoxSide = RIGHT; break;
//case 27:Add(1);gBoxSide = LEFT; break;
//case 28:Add(1); gBoxSide = RIGHT; break;
//case 29: gNumSpawnTOT = 0; skip = 1;break;
//case 30: gNumSpawnTOT = 0;skip = 6;
//
//	// Le checkpoint que le joueur à réussie à reach durant le niveau
//	MsgQueue::Register(CHECKPOINT_REACHED);
//
//
//	Ev_MultiColor_Warnings();	// WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
//	gSpwBotTimer.Start_Timer(800, 1, true);	// speed is inscreased!!!
//	break;// CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE 
//
//case 31:Add(1); Set_Interval(RIGHT, 5, 6);break;
//case 32:Add(1); Set_Interval(RIGHT, 5, 6);break;
//case 33:Add(1); Set_Interval(RIGHT, 5, 6);break;
//case 34:Add(1); Set_Interval(RIGHT, 5, 6); break;
//case 35:Add(1); Add_Spec(LEFT, 0); Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() - 1);break;
//case 36:Add_Spec(LEFT, 0); Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() - 1); break; //Set_Interval(RIGHT, 9,10);
//case 37:Add_Spec(LEFT, 0); Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() - 1); break;
//case 38:Add_Spec(LEFT, 0); Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() - 1); break;
//case 39:Add_Spec(LEFT, 0); Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() - 1);  break;
//
//case 40: Set_Interval(LEFT, 2, 3); Add(1); break;
//case 41: Set_Interval(LEFT, 2, 4); Add(1); break;
//case 42: Set_Interval(LEFT, 2, 5); Add(1); break;
//case 43: Set_Interval(LEFT, 2, 6); Add(1); break;
//case 44: Set_Interval(LEFT, 2, 7); Add(1); break;
//case 45: Set_Interval(RIGHT, spawnGrid->Get_MaxSpwnCrdY() - 3, spawnGrid->Get_MaxSpwnCrdY() - 1);Add(1);break;
//case 46: Set_Interval(RIGHT, spawnGrid->Get_MaxSpwnCrdY() - 4, spawnGrid->Get_MaxSpwnCrdY() - 1);Add(1);break;
//case 47: Set_Interval(RIGHT, spawnGrid->Get_MaxSpwnCrdY() - 5, spawnGrid->Get_MaxSpwnCrdY() - 1);Add(3); break;
//case 48: Set_Interval(RIGHT, spawnGrid->Get_MaxSpwnCrdY() - 6, spawnGrid->Get_MaxSpwnCrdY() - 1);Add(3); break;
//case 49: gNumSpawnTOT = 0;skip = 8;
//
//	ItemSpawner::Spawn_This_Item(ItemType::HEALTH, { 1,1 }); // Spawn de la vie ici?
//	MsgQueue::Register(CHECKPOINT_REACHED);
//	break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE 
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
//case 67:gNumSpawnTOT = 0;skip = 7;
//
//	gSpwBotTimer.Start_Timer(900, 1, true);	// speed is inscreased!!!	sSShhhhh
//	MsgQueue::Register(CHECKPOINT_REACHED);
//	break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE 
//
//	// Start les quad spawns!!
//case 80: Set_Interval(LEFT, 4, 6);Add(3); break;
//case 81: Set_Interval(RIGHT, 4, 8);Add(3); break;
//case 83: Set_Interval(LEFT, 8, 12);Add(3); break;
//case 84: Set_Interval(LEFT, 4, 6);Add(3); break;
//case 87: Set_Interval(RIGHT, 4, 8);Add(3); break;
//
//	// Biggest rush of all time
//case 88: Set_Interval(LEFT, 8, 12);Add(2); break;
//case 89: Set_Interval(LEFT, 7, 12);Add(2); break;
//case 90: Set_Interval(LEFT, 6, 12);Add(2); break;
//case 91: Set_Interval(LEFT, 5, 12);Add(2); break;
//case 92: Set_Interval(LEFT, 4, 12);Add(2); break;
//case 93: Set_Interval(LEFT, 3, 12);Add(2); break;
//case 94: Set_Interval(RIGHT, 7, 12);Add(2); break;
//case 95: Set_Interval(RIGHT, 6, 12);Add(2); break;
//case 96: Set_Interval(RIGHT, 5, 12);Add(2); break;
//case 97: Set_Interval(RIGHT, 4, 12);Add(2); break;
//case 98: Set_Interval(RIGHT, 3, 12);Add(2); break;
//case 99: Add(2); break;
//
//	// FINAL PUSH	
//case 100:
//	gNumSpawnTOT = 0; 	skip = 7;
//	gSpwBotTimer.Start_Timer(500, 1, true);
//
//	MsgQueue::Register(CHECKPOINT_REACHED);
//	MsgQueue::Register(FINAL_PUSH);
//	break;// CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE 
//
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
//	MsgQueue::Register(STOP_BOT_SPAWNS);
//	Ev_Wait_For_Victory(); // Wait que le dernier bot meurt pour trigger la victoire
//	break;




/*
	/////////////////////////////////////////////////////////////////////// Version avec 1 checkpoint au milieu

	J'ai abandonné celle-là, parce que je trouvais ça franchement lame
*/
