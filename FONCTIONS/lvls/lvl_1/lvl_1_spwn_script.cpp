

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

// Cheats! sshhhhs
#include "../../player/player.h"

// TO REMOVE
#include "../../console/sweet_cmd_console.h"


// GENERAL RULES FOR THIS DUMB BROKEN SHIT: 
// D�passe jamais le nombre de spawn permis sur une bordure
// AddSpecific(): Ne setup jamais une boxside random avec un spw pr�cis
// CETTE FORMULE CRASH 100% DU TEMPS // Add(1); gBoxSide = LEFT; gSpwNum = spawnGrid->Get_MaxSpwnCrdY() - 1; 
// Combiner BoxSide, Spwnum avec plus qu'un spawn, �a cr�er des exceptions
// Setup un intervalle de spawn trop petit pour le total va faire crash� le shit Ex : Set_Interval(RIGHT, 10, 13);Add(4); break;

using namespace bots_to_spawn;

static int spw;
static int box;

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
		
		
		case 20: linkGrid->link[9][7].Activate_Lonely_Link(Modifier::REGULAR); break;// Cr�er une root ici
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
		
			
			// Ez one with a lesson: les root meurt quand ils ne sont plus attach�s
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
			// Very Temporary! Doit �tre remove
			ConsoleRender::Add_String("TELEPORT", { (Find_Ctr_X((int)std::size("TELEPORT")) / 2) / 2, (gConHeight / 2) / 2 }, BRIGHT_WHITE, TXT_SPD_DR);
			ConsoleRender::Add_String("(Shoot , then spacebar)", { (Find_Ctr_X((int)std::size("(Shoot , then spacebar)")) / 2) / 2 - 5, (gConHeight / 2) / 2 + 2 }, WHITE, TXT_SPD_DR);

			gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 3, linkGrid->Get_Rows() - 1 }, UP, linkGrid->Get_Rows() - 3);
			gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 3, 2 }, LEFT, linkGrid->Get_Cols() - 5);
			gGrids.Make_Chain_Of_Walls({ 2, 2 }, DOWN, 2);

			gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 4, linkGrid->Get_Rows() - 2 }, LEFT, linkGrid->Get_Cols() - 6);
			gGrids.Make_Chain_Of_Walls({ 2, linkGrid->Get_Rows() - 2 }, UP, 3);
			break;

		case 54:Add(6); Set_Interval(LEFT, 4, 10);instantSpawn = true;break;
		case 55:Add(1);  gBoxSide = RIGHT; gSpwNum = spawnGrid->Get_MaxSpwnCrdY() - 1;	Set_Custom_Bot(SPWN_DLAY - 15);	MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
		case 56: break; // breaky break


			// EZ ONE FOR PACING AND LESSON - Montre l'utilit� du teleporter
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
		case 110:
		case 111:
		case 112:
		case 113:
		case 114:
		case 115:
		case 116:
		case 117:
		case 118:
		case 119:
		case 120:
		case 121:
			break;



			// KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP // KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP // KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP 

		//	// TROP COMPLIQU� POUR RIEN CELUI AVEC PLEINS DE ROOT PARTOUT
		//	// LIGNe au milieu
		//	gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 1, (linkGrid->Get_Rows() - 1) / 2 }, LEFT, 8);

		//	// Branche 1
		//	gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 3, (linkGrid->Get_Rows() - 1) / 2 }, UP, 1);
		//	gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 3, (linkGrid->Get_Rows() - 1) / 2 }, LEFT, 1);

		//	// Branche 2
		//	gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 4, (linkGrid->Get_Rows() - 1) / 2 }, DOWN, 1);
		//	gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 4, (linkGrid->Get_Rows() - 1) / 2 }, LEFT, 1);


		//	// Active les points strat�giques!
		//	linkGrid->link[4][4].Activate_Lonely_Link();	// Cr�er une root ici
		//	linkGrid->link[5][2].Activate_Lonely_Link();	// Cr�er une root ici
		//	linkGrid->link[6][12].Activate_Lonely_Link();	// Cr�er une root ici
		//	linkGrid->link[7][11].Activate_Lonely_Link();	// Cr�er une root ici
		//	linkGrid->link[8][3].Activate_Lonely_Link();	// Cr�er une root ici
		//	linkGrid->link[11][1].Activate_Lonely_Link();	// Cr�er une root ici
		//	//linkGrid->link[12][12].Activate_Lonely_Link();	// Cr�er une root ici

		//	// bouncys
		//	linkGrid->link[2][8].Activate_Lonely_Link();	// Cr�er une root ici
		//	linkGrid->link[3][10].Activate_Lonely_Link();	// Cr�er une root ici
		//	linkGrid->link[6][2].Activate_Lonely_Link();	// Cr�er une root ici
		//	linkGrid->link[7][5].Activate_Lonely_Link();	// Cr�er une root ici
		//	linkGrid->link[linkGrid->Get_Cols() - 3][1].Activate_Lonely_Link();	// Cr�er une root ici
		//	//linkGrid->link[linkGrid->Get_Cols() - 1][6].Activate_Lonely_Link();	// Cr�er une root ici
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
//linkGrid->link[6][linkGrid->Get_Rows() - 6].Activate_Lonely_Link(Modifier::FORCEFIELD);	// Cr�er une root ici
//linkGrid->link[linkGrid->Get_Cols() / 2][linkGrid->Get_Rows() - 4].Activate_Lonely_Link(Modifier::REGULAR);	// Cr�er une root ici
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
		//Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 3); 			break;// Dessine un pattern de d�part
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

		//case 50:			
		//	ItemSpawner::Spawn_This_Item(ItemType::HEALTH, { 1,1 }); // Spawn de la vie ici?
		//	gNumSpawnTOT = 0; skip = 5;
		//	gSpwBotTimer.Start_Timer(800, 1, true);	// speed is inscreased!!!
		//	break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE break;

		//	// Le joueur va voir la chaine des mur et va tout de suite la renforcer, MAIS! Un bot vertical va venir la d�truire mouhahaha!
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


// VERSION 1: Jug� trop difficile
// Voici les checkpoints dans le lvl script
//const int LVL1_CHECKPOINT[] = { 30, 49, 67, 100 }; 


//case 1: Set_Dr_Map_1(TXT_SPD_DR * 2 + 3);skip = 2; break; // Erase la border seulement si le joueur est en mode quickstartS
//case 2:Add_Spec(RIGHT, 7); /*MsgQueue::Register(START_BOT_SPAWNS); */break;
//case 3:Add_Spec(RIGHT, 5); 			break;// Dessine un pattern de d�part
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
//	// Le checkpoint que le joueur � r�ussie � reach durant le niveau
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

	J'ai abandonn� celle-l�, parce que je trouvais �a franchement lame
*/
