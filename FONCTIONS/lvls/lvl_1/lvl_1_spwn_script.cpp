

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
#include "../../events/global_events/ev_spwn_player.h"

// Cheats! sshhhhs
#include "../../player/player.h"

// TO REMOVE
#include "../../console/sweet_cmd_console.h"


// GENERAL RULES FOR THIS DUMB BROKEN SHIT: 
// Dépasse jamais le nombre de spawn permis sur une bordure
// AddSpecific(): Ne setup jamais une boxside random avec un spw précis
// CETTE FORMULE CRASH 100% DU TEMPS // Add(1); gBoxSide = LEFT; gSpwNum = spawnGrid->Get_MaxSpwnCrdY() - 1; 
// Combiner BoxSide, Spwnum avec plus qu'un spawn, ça créer des exceptions
// Setup un intervalle de spawn trop petit pour le total va faire crashé le shit Ex : Set_Interval(RIGHT, 10, 13);Add(4); break;

using namespace bots_to_spawn;

static int spw;
static int box;

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
		case 1: Set_Dr_Map_1(TXT_SPD_DR * 4); skip = 2; // Erase la border seulement si le joueur est en mode quickstartS
			gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() / 2 ,linkGrid->Get_Rows() / 2 }, LEFT, 3);
			gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() / 2 ,linkGrid->Get_Rows() / 2 }, RIGHT, 3);
			break; 
			    
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
		
		case 11: /*Set_Custom_Bot(SPWN_DLAY * 1.3f); skip = 3;*/ 
			gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() / 2  - 1,0 }, DOWN, 1);
			Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() / 2);  
			break;

		case 12: Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() / 2 - 1);break;
		case 13: Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() / 2 - 2);break;
		case 14: Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() / 2 - 3);break;
		case 15: Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() / 2 - 4);break;
		case 16: Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() / 2 - 5);break;
		case 17: Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() / 2 - 6);break;
		case 18: Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() / 2 - 7);break;
		case 19: MsgQueue::Register(CHECKPOINT_REACHED);break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
		
		
		case 20: linkGrid->link[9][7].Activate_Lonely_Link(Modifier::REGULAR); break;// Créer une root ici
		case 21:Add(1);gBoxSide = LEFT; gSpwNum = 0;break;			
		case 22:Add(1);gBoxSide = LEFT; gSpwNum = 1; break;			
		case 23:Add(1);gBoxSide = LEFT; gSpwNum = 2; break;			
		case 24:Add(1);gBoxSide = LEFT; gSpwNum = 3; break;			
		case 25:Add(1);gBoxSide = LEFT; gSpwNum = 4; break;			
		case 26:Add(1);gBoxSide = LEFT; gSpwNum = 5; break;			
		case 27:Add(1);gBoxSide = LEFT; gSpwNum = 6; skip = 1; break;
		case 28:Add(1);gBoxSide = LEFT; gSpwNum = 0; break;
		case 29:Add(1);gBoxSide = LEFT; gSpwNum = 1; break;
		case 30:Add(1);gBoxSide = LEFT; gSpwNum = 2; break;
		case 31:Add(1);gBoxSide = LEFT; gSpwNum = 3; break;
		case 32:Add(1);gBoxSide = LEFT; gSpwNum = 4; break;
		case 33:Add(1);gBoxSide = LEFT; gSpwNum = 5; break;
		case 34:Add(1);gBoxSide = LEFT; gSpwNum = 6; skip = 1; break;
		case 35: MsgQueue::Register(CHECKPOINT_REACHED);break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
		
			
			// Ez one with a lesson: les root meurt quand ils ne sont plus attachés
		case 36:gGrids.Make_Chain_Of_Walls({ 3, 4 }, DOWN, 3);Add(3);Set_Interval(LEFT, 4, 7);skip = 2;break;
		case 37:Add(2);Add_Spec(LEFT, 3);Set_Interval(RIGHT, 0, 2);break;
		case 38:Add(2);Set_Interval(RIGHT, 12, 14);	break;
		case 39:Add(4);Set_Interval(RIGHT, 3, 7);break;
		case 40:MsgQueue::Register(CHECKPOINT_REACHED);break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
			

		// Easy one for pacing
		case 41:gGrids.Make_Chain_Of_Walls({ 0, 8 }, RIGHT, 1);	gGrids.Make_Chain_Of_Walls({ 0, 5 }, RIGHT, 1);	gGrids.Make_Chain_Of_Walls({ 0, 2 }, RIGHT, 1);	break;
		case 42:Add(1);gBoxSide = RIGHT; gSpwNum = 7; skip = 2;break;
		case 43:Add(1);gBoxSide = RIGHT; gSpwNum = 4; skip = 2;break;
		case 44:Add(1);gBoxSide = RIGHT; gSpwNum = 1; skip = 2;break;
		case 45:Add(1);gBoxSide = RIGHT; gSpwNum = 2; skip = 1;break;
		case 46:Add(1);gBoxSide = RIGHT; gSpwNum = 5; skip = 1; break;
		case 47:Add_Spec(RIGHT, 8); skip = 1; break;
		case 48:Add_Spec(RIGHT, 11);skip = 4;break;
		case 49:Add_Spec(RIGHT, 10);break;
		case 50:Add_Spec(RIGHT, 7);break;
		case 51:Add_Spec(RIGHT, 4);break;
		case 52:Add_Spec(RIGHT, 1);	MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHEREbreak;
		
		
		case 53: 		// TELEPORTATION TUTORIAL!
			// Very Temporary! Doit être remove
			ConsoleRender::Add_String("TELEPORT", { (Find_Ctr_X((int)std::size("TELEPORT")) / 2) / 2, (gConHeight / 2) / 2 }, BRIGHT_WHITE, TXT_SPD_DR);
			ConsoleRender::Add_String("(Shoot , then spacebar)", { (Find_Ctr_X((int)std::size("(Shoot , then spacebar)")) / 2) / 2 - 5, (gConHeight / 2) / 2 + 2 }, WHITE, TXT_SPD_DR);

			gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 3, linkGrid->Get_Rows() - 1 }, UP, linkGrid->Get_Rows() - 3);
			gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 3, 2 }, LEFT, linkGrid->Get_Cols() - 5);
			gGrids.Make_Chain_Of_Walls({ 2, 2 }, DOWN, 2);

			gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 4, linkGrid->Get_Rows() - 2 }, LEFT, linkGrid->Get_Cols() - 6);
			gGrids.Make_Chain_Of_Walls({ 2, linkGrid->Get_Rows() - 2 }, UP, 3);
			Add(6); Set_Interval(LEFT, 4, 10);instantSpawn = true;
			break;

		case 54:Add(1);  gBoxSide = RIGHT; gSpwNum = spawnGrid->Get_MaxSpwnCrdY() - 1;	Set_Custom_Bot(SPWN_DLAY - 15);	break;
		case 55:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
		case 56: break; // breaky break


			// EZ ONE FOR PACING AND LESSON - Montre l'utilité du teleporter
		case 57:Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 1);Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() - 1);	instantSpawn = true;break;
		case 58:Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 1);	break;
		case 59:Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() - 1);	break;
		case 60:Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 1);Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() - 1);	break;
		case 61:Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 1);Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() - 1);instantSpawn = true;break;
		case 62:Add_Spec(RIGHT, 0);	Add_Spec(LEFT, 0);	break;
		case 63:Add_Spec(RIGHT, 0);Add_Spec(LEFT, 0);instantSpawn = true;break;
		case 64:Add_Spec(LEFT, 0);	break;
		case 65:Add_Spec(RIGHT, 0);Add_Spec(LEFT, 0);	break;
		case 66:Add_Spec(LEFT, 0);	break;
		case 67:Add_Spec(RIGHT, 0);	break;
		case 68:Add_Spec(RIGHT, 0); MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE


			// SATISFAISANT! Montre les walls transfer
		case 69:// Quelque mur en forme de L sur la bordure left
			gGrids.Make_Chain_Of_Walls({ 0, 5 }, RIGHT, 1);
			gGrids.Make_Chain_Of_Walls({ 1, 5 }, DOWN, 1);

			gGrids.Make_Chain_Of_Walls({ 0, 7 }, RIGHT, 1);
			gGrids.Make_Chain_Of_Walls({ 1, 7 }, DOWN, 1);

			gGrids.Make_Chain_Of_Walls({ 0, 10 }, RIGHT, 1);
			gGrids.Make_Chain_Of_Walls({ 1, 10 }, UP, 1);

			// Quelques lignes sur la bordure right
			gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 1, 6 }, LEFT, 1);
			gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 1, 8 }, LEFT, 1);
			gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 1, 9 }, LEFT, 1);
			break;

		case 70:Add_Spec(LEFT, 6);	break;
		case 71:Add_Spec(LEFT, 8);break;
		case 72:Add_Spec(LEFT, 9);skip = 2;break;
		case 73:Add_Spec(LEFT, 9);break;
		case 74:Add_Spec(LEFT, 5);break;
		case 75:Add_Spec(LEFT, 7);skip = 2;break;
		case 76:Add_Spec(LEFT, 9);skip = 3;break;
		case 77:Add_Spec(LEFT, 5);break;
		case 78:MsgQueue::Register(CHECKPOINT_REACHED);			break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE


			// SATISFAISANT! EXPAND les walls transfer
		case 79:break; // small pause
		case 80:
			gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 1, 1 }, LEFT, 6);
			gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 1, 9 }, LEFT, 1);
			gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 1, 10 }, LEFT, 1);
			gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 1, 11 }, LEFT, 1);
			gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 1, 12 }, LEFT, 1);
			gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 1, 13 }, LEFT, 1);
			gGrids.Make_Chain_Of_Walls({ 6, 13 }, RIGHT, 4);
			break;

		case 81:Add(1);gBoxSide = LEFT; gSpwNum = 6; Add_Spec(RIGHT, 0);break;			
		case 82:Add(1);gBoxSide = LEFT; gSpwNum = 5;Add_Spec(RIGHT, 0);break;
		case 83:Add(1);gBoxSide = LEFT; gSpwNum = 4;Add_Spec(RIGHT, 0);break;
		case 84:Add(1);gBoxSide = LEFT; gSpwNum = 3;Add_Spec(RIGHT, 0);break;
		case 85:Add(1);gBoxSide = LEFT; gSpwNum = 2;Add_Spec(RIGHT, 0);break;
		case 86:Add(1);gBoxSide = LEFT; gSpwNum = 1; skip = 1;break;
		case 87:Add_Spec(RIGHT, 0); skip = 10;break;
		case 88:Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() / 2 );Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 1);break;
		case 89:Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() / 2 + 1);Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 1);break;
		case 90:Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() / 2 + 2);Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 1);break;
		case 91:Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() / 2 + 3);Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 1);break;
		case 92:Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() / 2 + 4);Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 1);break;
		case 93:Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() / 2 + 5);skip = 1; Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 1);break;
		case 94:Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 1);break;
		case 95:MsgQueue::Register(CHECKPOINT_REACHED); break;// CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
		case 96:break;
		
		
			// COOL ONE AT THE END OF FIRST HALF
		case 97: Add(1); gBoxSide = RIGHT; gSpwNum = 9; break;
		case 98: Add(4); Set_Interval(LEFT, 0, 2);  Set_Interval(RIGHT, 7, 9);	skip = 3;	break;
		case 99: Add(2);Set_Interval(RIGHT, 1, 3); skip = 1;break;
		case 100:Add(2);Set_Interval(LEFT, 3, 5);  skip = 3;break;
		case 101:Add(2);Set_Interval(LEFT, 7, 9);  skip = 3; break;
		case 103:Add(2);Set_Interval(RIGHT, 3, 5); skip = 3;break;
		case 104:Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() - 2);Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() - 1);skip = 2;break;
		case 105:Add(2);Set_Interval(RIGHT, 7, 9);MsgQueue::Register(CHECKPOINT_REACHED); break;// CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
			// COOL ONE AT THE END OF FIRST HALF

		
			// VERTICAL SPAWN BEGINS!
		case 106:
			gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 1, 3 }, LEFT, 1);
			gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 2, 3 }, DOWN, 1);
			gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 2, 4 }, LEFT, 5);
			gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 2 - 5, 4 }, DOWN, 1);
			break;

		case 107:
			Add(10);
			Set_Interval(LEFT, 4, 9); 
			Set_Interval(RIGHT, 9, 14); skip = 5;
			break;

		case 108:
			Add_Spec(UP, spawnGrid->Get_MaxSpwnCrdX() - 1);
			instantSpawn = true;
			MsgQueue::Register(CHECKPOINT_REACHED); // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
			break;

		case 109:
			gGrids.Make_Chain_Of_Walls({ 3,7 }, LEFT, 3);
			gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 4,7 }, RIGHT, 3);
			break;

			// EZ Vertical introduction!
		case 110:Add_Spec(DOWN, spawnGrid->Get_MaxSpwnCrdX() - 1); Add_Spec(DOWN, 2);break;
		case 111:Add_Spec(DOWN, spawnGrid->Get_MaxSpwnCrdX() - 2); Add_Spec(DOWN, 1);break;
		case 112:Add_Spec(DOWN, spawnGrid->Get_MaxSpwnCrdX() - 3); Add_Spec(DOWN, 0);break;
		case 113:Add_Spec(UP, 0); Add_Spec(UP, spawnGrid->Get_MaxSpwnCrdX() - 3);break;
		case 114:Add_Spec(UP, 1); Add_Spec(UP, spawnGrid->Get_MaxSpwnCrdX() - 2);break;
		case 115:Add_Spec(UP, 2); Add_Spec(UP, spawnGrid->Get_MaxSpwnCrdX() - 1);break;
		case 116:MsgQueue::Register(CHECKPOINT_REACHED); break;// CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
		case 117:break; 
		

			// redirect couloir au milieu
		case 118:
			gGrids.Make_Chain_Of_Walls({ 0,10 }, RIGHT, 9);
			gGrids.Make_Chain_Of_Walls({ 9,10 }, UP, 6);	// max = 9[
			gGrids.Make_Chain_Of_Walls({ 8,10 }, UP, 3);
			gGrids.Make_Chain_Of_Walls({ 7,10 }, UP, 2);
			gGrids.Make_Chain_Of_Walls({ 6,10 }, UP, 4);
			gGrids.Make_Chain_Of_Walls({ 5,10 }, UP, 5);
			gGrids.Make_Chain_Of_Walls({ 4,10 }, UP, 6);
			break;
		case 119:Add_Spec(UP, 8);break;
		case 120:Add_Spec(UP, 4);skip = 1;break;
		case 121:Add_Spec(UP, 6);skip = 1;break;
		case 122:Add_Spec(UP, 5);skip = 1;break;
		case 123:Add_Spec(LEFT, 4);Add_Spec(RIGHT, 4);skip = 2;break;
		case 124:Add_Spec(UP, 5);skip = 1;break;
		case 125:Add_Spec(UP, 7);skip = 1;break;
		case 126:Add_Spec(UP, 7);skip = 1;break;
		case 127:Add_Spec(UP, 7);skip = 1;break;
		case 128:Add_Spec(LEFT, 5);Add_Spec(RIGHT, 5);skip = 2;break;
		case 129:Add_Spec(UP, 8);skip = 1;break;
		case 130:Add_Spec(UP, 4);skip = 1;break;
		case 131:Add_Spec(UP, 4);skip = 1;break;
		case 132:Add_Spec(UP, 7);skip = 1;break;
		case 133:Add_Spec(LEFT, 6);Add_Spec(RIGHT, 6);skip = 4;break;
		case 134:Add_Spec(UP, 4);skip = 2;break;
		case 135:Add_Spec(LEFT, 7);Add_Spec(UP, 4);skip = 2;break;
		case 136:Add_Spec(UP, 8);skip = 1;break;
		case 137:Add_Spec(LEFT, 9);Add_Spec(RIGHT, 8);Add_Spec(UP, 7);skip = 2;break;
		case 138:Add_Spec(RIGHT, 9);skip = 3;break;
		case 139:Add(9);Set_Interval(DOWN, 0, 9); MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE 
		case 140:break;


			// Challenging teleporting all sides
		case 141:Add_Spec(LEFT, 2); Set_Custom_Bot(SPWN_DLAY / 2);break;
		case 142:Add_Spec(UP, 8); Add_Spec(UP, 9); skip = 1; break;
		case 143:Add_Spec(UP, 1);skip = 1;break;
		case 144:Add_Spec(LEFT, 1); Add_Spec(LEFT, 2); skip = 4;break;
		case 145:Add_Spec(LEFT, 13);skip = 1;break;
		case 146:Add_Spec(DOWN, 1); Add_Spec(DOWN, 2); skip = 4;break;
		case 147:Add_Spec(DOWN, 11);skip = 2;break;
		case 148:Add_Spec(DOWN, 8);Add_Spec(DOWN, 9); Add_Spec(RIGHT, 11);skip = 5;break;
		case 149:Add_Spec(RIGHT, 5); skip = 1; break;
		case 150:Add_Spec(UP, 11);	skip = 1;break;
		case 151:Add_Spec(RIGHT, 3);skip = 4; break;
		case 152:Add_Spec(UP, 11); break;
		case 153:Add_Spec(RIGHT, 1);break;
		case 154:Add_Spec(RIGHT, 0);MsgQueue::Register(CHECKPOINT_REACHED); break;// CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
		case 155:break;


			// 2 long wall d'obstacle
		case 156:
			gGrids.Make_Chain_Of_Walls({ 3,14 }, UP, 14);
			gGrids.Make_Chain_Of_Walls({ 9,0 }, DOWN, 14);	
			break;

		case 157:Add_Spec(RIGHT, 0);Add_Spec(RIGHT, 1);break;
		case 158:Add_Spec(RIGHT, 4);Add_Spec(RIGHT, 5);break;
		case 159:Add_Spec(UP, 9); Add_Spec(UP, 10); skip = 2; break;
		case 160:Add_Spec(RIGHT, 0);Add_Spec(RIGHT, 1);skip = 2; break;
		case 161:Add_Spec(UP, 9);Add_Spec(UP, 10);Add_Spec(UP, 11);break;
		case 162:Add_Spec(RIGHT, 0);skip = 2;;break;
		case 163:Add(6);Set_Interval(DOWN, 3, 9); skip = 12;break;
		case 164:Add_Spec(UP, 0);Add_Spec(UP, 1); break;
		case 165:Add_Spec(LEFT, 13);break;
		case 166:Add_Spec(LEFT, 10);Add_Spec(LEFT, 9);skip = 3; break;
		case 167:Add_Spec(UP, 0);Add_Spec(UP, 1);Add_Spec(UP, 2);break;
		case 168:Add_Spec(LEFT, 8);Add_Spec(LEFT, 7);skip = 3;break;
		case 169:Add_Spec(LEFT, 13); skip = 12; break;
		case 170:Add(12);Set_Interval(UP, 0, linkGrid->Get_Cols() - 1); MsgQueue::Register(CHECKPOINT_REACHED); break;// CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
		case 171:break;


			// Super hard: mais différent des autres, juste avant le FINAL HOUR 
			// Static shoot dans tout les sens
			// 1-12 LEFT/RIGHT
			// 1-10	UP/DOWN 
		case 172:
			gGrids.Make_Chain_Of_Walls({ 6,1 }, UP, 1);
			gGrids.Make_Chain_Of_Walls({ 6,13 }, DOWN, 1);
			gGrids.Make_Chain_Of_Walls({ 1,7 }, LEFT, 1);
			gGrids.Make_Chain_Of_Walls({ 11,7 }, RIGHT, 1);
			break;
		case 173:Add_Spec(UP, 10);break;
		case 174:Add_Spec(LEFT, 1);break;
		case 175:Add_Spec(DOWN, 1);break;
		case 176:Add_Spec(RIGHT, 12);skip = 2;break;
		case 177:Add_Spec(UP, 10);break;
		case 178:Add_Spec(LEFT, 1);break;
		case 179:Add_Spec(DOWN, 1);break;
		case 180:Add_Spec(DOWN, 10);skip = 1;break;
		case 181:Add_Spec(RIGHT, 1);break;
		case 182:Add_Spec(UP, 1);break;
		case 183:Add_Spec(RIGHT, 12);break;
		case 184:Add_Spec(UP, 1);break;
		case 185:Add_Spec(UP, 10);break;
		case 186:Add_Spec(LEFT, 1);break;
		case 187:Add_Spec(LEFT, 1);break;
		case 188:Add_Spec(DOWN, 10);break;
		case 189:Add_Spec(LEFT, 12);break;
		case 190:Add_Spec(UP, 1);break;
		case 191:Add_Spec(LEFT, 12); skip = 3;break;
		case 192:Add_Spec(DOWN, 10);break;
		case 193:Add_Spec(RIGHT, 12);break;
		case 194:Add_Spec(LEFT, 2);break;
		case 195:Add_Spec(UP, 9);break;
		case 196:Add_Spec(RIGHT, 11);break;
		case 197:Add_Spec(DOWN, 2);skip = 12; break;
		case 198:Add_Spec(UP, 4);Add_Spec(DOWN, 7);Add_Spec(LEFT, 5);Add_Spec(RIGHT, 8); MsgQueue::Register(CHECKPOINT_REACHED); break;// CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
		case 199://MsgQueue::Register(FINAL_PUSH); skip = 10;break;
		case 200:
			MsgQueue::Register(LOCK_PLAYER);
			P1.Er_Player();
			break;	// THE FINAL CHALLENGE IS HERE HAHAHAHAHAH
			
			// Mur de forcefield
		case 201:
			Set_Ev_Spawn_Player(3);
			for (int r = 0; r < linkGrid->Get_Rows(); r++)
				linkGrid->link[6][r].Activate_Lonely_Link(Modifier::FORCEFIELD);	// Créer une root ici

			skip = 15;
			break;


		case 202:Add(1);skip = 4;break;
		case 203:Add(1);skip = 4;break;
		case 204:Add(1);skip = 4;break;
		case 205:Add(1);skip = 4;break;
		case 206:Add(1);skip = 4;break;
		case 207:Add(1);skip = 4;break;
		case 208:Add(1);skip = 4;break;
		case 209:Add(1);skip = 4;break;
		case 210:Add(1);skip = 4;break;
		case 211:Add(1);skip = 4;break;
		case 212:Add(1);skip = 4;break;
		case 213:Add(1);skip = 4;break;
		case 214:Add(1);skip = 4;break;
		case 215:Add(1);skip = 4;break;
		case 216:Add(1);skip = 4;break;
		case 217:Add(1);skip = 4;break;
		case 218:Add(1);skip = 4;break;
		case 219:Add(1);skip = 4;break;
		case 220:Add(1);skip = 4;break;
		case 221:Add(1);skip = 4;break;
		case 222:Add(1);skip = 4;break;
		case 223:Add(1);skip = 4;break;
		case 224:Add(1);skip = 4;break;
		case 225:Add(1);skip = 4;break;
		case 226:Add(1);skip = 4;break;
		case 227:Add(1);skip = 4;break;
		case 228:Add(1);skip = 4;break;
		case 229:Add(1);skip = 4;break;
		case 230:Add(1);skip = 4;break;
		case 231:Add(1);skip = 4;break;
		case 232:Add(1);skip = 4;break;
		case 233:Add(1);skip = 4;break;
		case 234:Add(1);skip = 4;break;
		case 235:Add(1);skip = 4;break;
		case 236:Add(1);skip = 4;break;
		case 237:Add(1);skip = 4;break;
		case 238:Add(1);skip = 4;break;
		case 239:Add(1);skip = 4;break;
		case 240:Add(1);skip = 4;break;
		case 241:Add(1);skip = 4;break;
		case 242:Add(1);skip = 4;break;
		case 243:Add(1);skip = 4;break;
		case 244:Add(1);skip = 4;break;
		case 245:Add(1);skip = 4;break;
		case 246:Add(1);skip = 4;break;
		case 247:Add(1);skip = 4;break;
		case 248:Add(1);skip = 4;break;
		case 249:Add(1);skip = 4;break;
		case 250:	// VICTORY IS OURS HAHAHAHAHAHAH
			MsgQueue::Register(STOP_BOT_SPAWNS); 
			Ev_Wait_For_Victory(); // Wait que le dernier bot meurt pour trigger la victoire
			break;
																													  
																													  
			
			// KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP // KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP // KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP 




			
			
			
			
			
			
			
			
			
			
			
			
			
			
			

















			// mix et teleporter
			// Mix égal entre vertical et horizontal ez
			// Mix égal entre vertical et horizontal HARD
			//#2 Pleins de ligne verticales, tu dois redirect pour protéger la base horizontale
			// 1 autre redirect mais plus hard



		





















			// KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP // KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP // KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP 

		//	// TROP COMPLIQUÉ POUR RIEN CELUI AVEC PLEINS DE ROOT PARTOUT
		//	// LIGNe au milieu
		//	gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 1, (linkGrid->Get_Rows() - 1) / 2 }, LEFT, 8);

		//	// Branche 1
		//	gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 3, (linkGrid->Get_Rows() - 1) / 2 }, UP, 1);
		//	gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 3, (linkGrid->Get_Rows() - 1) / 2 }, LEFT, 1);

		//	// Branche 2
		//	gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 4, (linkGrid->Get_Rows() - 1) / 2 }, DOWN, 1);
		//	gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 4, (linkGrid->Get_Rows() - 1) / 2 }, LEFT, 1);


		//	// Active les points stratégiques!
		//	linkGrid->link[4][4].Activate_Lonely_Link();	// Créer une root ici
		//	linkGrid->link[5][2].Activate_Lonely_Link();	// Créer une root ici
		//	linkGrid->link[6][12].Activate_Lonely_Link();	// Créer une root ici
		//	linkGrid->link[7][11].Activate_Lonely_Link();	// Créer une root ici
		//	linkGrid->link[8][3].Activate_Lonely_Link();	// Créer une root ici
		//	linkGrid->link[11][1].Activate_Lonely_Link();	// Créer une root ici
		//	//linkGrid->link[12][12].Activate_Lonely_Link();	// Créer une root ici

		//	// bouncys
		//	linkGrid->link[2][8].Activate_Lonely_Link();	// Créer une root ici
		//	linkGrid->link[3][10].Activate_Lonely_Link();	// Créer une root ici
		//	linkGrid->link[6][2].Activate_Lonely_Link();	// Créer une root ici
		//	linkGrid->link[7][5].Activate_Lonely_Link();	// Créer une root ici
		//	linkGrid->link[linkGrid->Get_Cols() - 3][1].Activate_Lonely_Link();	// Créer une root ici
		//	//linkGrid->link[linkGrid->Get_Cols() - 1][6].Activate_Lonely_Link();	// Créer une root ici
		//	break;

		//case 102:
		//	Add_Spec(LEFT, 4);
		//	break;

		//case 103:
		//	Add_Spec(LEFT, 2);
		//	break;

		//case 104:
		//	Add_Spec(LEFT, 11);
		//	break;

		//case 105:
		//	Add_Spec(LEFT, 10);
		//	break;

		//case 106:
		//	Add_Spec(LEFT, 3);
		//	break;

		//case 107:
		//	Add_Spec(RIGHT, 9); skip = 2;
		//	break;

		//case 108:
		//	Add_Spec(LEFT, 0); skip = 4;
		//	break;

		//case 109:
		//	break;

		//case 110:
		//	Add_Spec(RIGHT, 4); skip = 2;
		//	break;

		//case 111:
		//	Add_Spec(LEFT, 1);
		//	break;

		//case 112:
		//	Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 1);
		//	MsgQueue::Register(CHECKPOINT_REACHED); // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
		//	break;
			// KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP // KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP // KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP 


			// KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP // KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP // KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP 
//// FORCEFIELD INTRODUCTION
//linkGrid->link[6][linkGrid->Get_Rows() - 6].Activate_Lonely_Link(Modifier::FORCEFIELD);	// Créer une root ici
//linkGrid->link[linkGrid->Get_Cols() / 2][linkGrid->Get_Rows() - 4].Activate_Lonely_Link(Modifier::REGULAR);	// Créer une root ici
//gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() / 2, linkGrid->Get_Rows() - 2 }, LEFT, 2 );
//gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() / 2, linkGrid->Get_Rows() - 2 }, RIGHT, 2);
//gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() / 2 + 1, linkGrid->Get_Rows() - 6 }, UP, 2);
//gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() / 2 - 1, linkGrid->Get_Rows() - 6} , UP, 2);
//gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() / 2 + 1, linkGrid->Get_Rows() - 6 }, RIGHT,  5);
//gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() / 2 - 1, linkGrid->Get_Rows() - 6 }, LEFT, 5);
//gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 1, linkGrid->Get_Rows() - 6 }, DOWN, 1 );
//gGrids.Make_Chain_Of_Walls({ 0, linkGrid->Get_Rows() - 6 }, DOWN, 1 );
//Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 2);
//Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() - 2);
//break;
// KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP // KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP // KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP 









			//////PUZZLE START------------------------------------------------------------------	 Ligne blockante en bas
			//spw = spawnGrid->Get_MaxSpwnCrdY() - 2;
			//gGrids.Make_Chain_Of_Walls({ 0,linkGrid->Get_Rows() - 3 }, RIGHT, 12);
			//break;
			//Add(1); gBoxSide = LEFT; gSpwNum = spw; break;
			//Add(1); gBoxSide = LEFT; gSpwNum = spw; break;
			//Add(1); gBoxSide = LEFT; gSpwNum = spw; break;
			//Add(1); gBoxSide = LEFT; gSpwNum = spw; break;
			//Add(1); gBoxSide = LEFT; gSpwNum = spw; break;
			//Add(1); gBoxSide = LEFT; gSpwNum = spw; break;
			//Add(1); gBoxSide = LEFT; gSpwNum = spw; break;
			//Add(1); gBoxSide = LEFT; gSpwNum = spw; break;
			//Add(1); gBoxSide = LEFT; gSpwNum = spw; break;
			//Add(1); gBoxSide = LEFT; gSpwNum = spw; break;
			//Add(1); gBoxSide = RIGHT; gSpwNum = spw; break;
			//Add(1); gBoxSide = LEFT; gSpwNum = spw; break;
			//Add(1); gBoxSide = RIGHT; gSpwNum = spw; break;
			//Add(1); gBoxSide = LEFT; gSpwNum = spw; break;
			//Add(1); gBoxSide = RIGHT; gSpwNum = spw; break;
			//Add(1); gBoxSide = LEFT; gSpwNum = spw; break;
			//Add(1); gBoxSide = RIGHT; gSpwNum = spw; break;
			//Add(1); gBoxSide = RIGHT; gSpwNum = spw - 1; break;
			//Add(1); gBoxSide = RIGHT; gSpwNum = spw - 1; break;
			//Add(1); gBoxSide = RIGHT; gSpwNum = spw - 1; break;
			//Add(1); gBoxSide = RIGHT; gSpwNum = spw - 1; break;
			//Add(1); gBoxSide = RIGHT; gSpwNum = spw - 1; break;
			//Add(1); gBoxSide = RIGHT; gSpwNum = spw - 1; break;
			//Add(1);gBoxSide = RIGHT; gSpwNum = spw - 1; break;
			//Add(1);gBoxSide = RIGHT; gSpwNum = spw - 1; break;
			//Add(1);gBoxSide = RIGHT; gSpwNum = spw - 1; break;
			//gNumSpawnTOT = 0;skip = 7;
			//////puzzle end------------------------------------------------------------------

			//
			
		


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
		

		//case 50:			
		//	ItemSpawner::Spawn_This_Item(ItemType::HEALTH, { 1,1 }); // Spawn de la vie ici?
		//	gNumSpawnTOT = 0; skip = 5;
		//	gSpwBotTimer.Start_Timer(800, 1, true);	// speed is inscreased!!!
		//	break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE break;

		//	// Le joueur va voir la chaine des mur et va tout de suite la renforcer, MAIS! Un bot vertical va venir la détruire mouhahaha!
		//	gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 1, 6 }, LEFT, 4);
		//	Add_Spec(UP, spawnGrid->Get_Cols() - 1);
		//	Add_Spec(DOWN, spawnGrid->Get_Cols() - 1);

		//// Random spawns
		//case 51:Add(1);break;
		//case 52:Add(1);break;
		//case 53:Add(1);break;
		//case 54:Add(1);break;
		//case 55:Add(1);break;
		//case 56:Add(1);break;
		//case 57:Add(2);break;
		//case 58:Add(1);break;
		//case 59:Add(2);break;
		//case 60:Add(1);break;
		//case 61:Add(2);break;
		//case 62:Add(1);break;
		//case 63:Add(1); skip = 2; break;
		//case 64:Add(3);break;
		//case 65:Add(4);break;
		//case 66:Add(5);break;
		//case 67:gNumSpawnTOT = 0;skip = 7;
		//	

		//
		

		//	// FINAL PUSH	
		//case 100: 
		//	gNumSpawnTOT = 0; 	skip = 7;
		//	gSpwBotTimer.Start_Timer(500, 1, true);	
		//	
		//	MsgQueue::Register(CHECKPOINT_REACHED);
		//	//MsgQueue::Register(FINAL_PUSH);
		//	break;// CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE 

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
