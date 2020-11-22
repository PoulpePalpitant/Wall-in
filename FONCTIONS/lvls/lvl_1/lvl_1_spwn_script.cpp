

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
#include "msg_events/ev_wasd.h"
#include "msg_events/ev_arr_keys.h"



// Cheats! sshhhhs
#include "../../player/player.h"
#include "../../items/item_spw_drawer.h"

// TO REMOVE
#include "../../console/sweet_cmd_console.h"


// GENERAL RULES FOR THIS DUMB BROKEN SHIT: 
// Dépasse jamais le nombre de spawn permis sur une bordure
// AddSpecific(): Ne setup jamais une boxside random avec un spw précis
// CETTE FORMULE CRASH 100% DU TEMPS // Add(1); gBoxSide = LEFT; gSpwNum = spawnGrid->Get_MaxSpwnCrdY() - 1; 
// Combiner BoxSide, Spwnum avec plus qu'un spawn, ça créer des exceptions
// Setup un intervalle de spawn trop petit pour le total va faire crashé le shit Ex : Set_Interval(RIGHT, 10, 13);Add(4); break;

using namespace bots_to_spawn;


// Puzzles du lvl1:
void Puzzle_1_0();
void Puzzle_1_1();
void Puzzle_1_2();
void Puzzle_1_3();
void Puzzle_1_4();
void Puzzle_1_5();	//
void Puzzle_1_6();
void Puzzle_1_7();
void Puzzle_1_8();	// Peut être utilisé, mais va bcp trop vite
void Puzzle_1_9();
void Puzzle_1_10();
void Puzzle_1_11();
void Puzzle_1_12();
void Puzzle_1_13();
void Puzzle_1_14();
void Puzzle_1_15();
void Puzzle_1_16();
void Puzzle_1_17();


// VOICI  l'ordre dans lequel sera joué les puzzles
void (*LVL1_PUZZLES[])() = {	// definition 
Puzzle_1_0,
Puzzle_1_1,
Puzzle_1_2,
Puzzle_1_3,
Puzzle_1_4,
Puzzle_1_5,
Puzzle_1_6,
Puzzle_1_7,
Puzzle_1_8,
Puzzle_1_9,
Puzzle_1_10,
Puzzle_1_11,
Puzzle_1_12,
Puzzle_1_13,
Puzzle_1_14,
Puzzle_1_15,
Puzzle_1_16,
Puzzle_1_17
};		


// stupid stuff that should'nt be here, but the convenience is too great
static int spw;
static int box;
static GrdCoord crd;
static std::string codeRecycling = "(Don't Let The Shapes Reach This Border)";
static bool seenFinalHour = false;
static std::string tip_01 = "Drain Hp For Ammo ->";
static std::string tip_01_1 = "Shoot to drain hp ";
static int skip;

void Lvl_1_Spwn_Script()
{
	if (gSpawnThisCycle)
	{
		int numSpawnWaves = gSpawnCycleTot;	// Pour aller dans la switch et déterminé quel va être le spawn
		skip = 0;						// Représente le nombre de fois qu'on va Skip un cycle de spawn selon l'indice de temps: Delay * Spawn_Cycle
		
		// POUR GET LE MAX
		//	spawnGrid->Get_MaxSpwnCrdX() - 1
		//	spawnGrid->Get_MaxSpwnCrdY() - 1
		//Add(300);
		
		if (numSpawnWaves < 220) // Tout les spawns seront verticaux lors de la moitié du final hour
			gHorizontalBorder = true;
		
		LVL1_PUZZLES[gCurrentPuzzle[gCurrentLevel - 1]]();	// Script du puzzle

		// Ceci ajoute du temps entre le spawn actuel et le prochain
		if (skip)
			gSpwBotTimer.Add_Count(skip);

		gCurrPuzzleStep++;	// Prochain step du puzzle!

			// KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP // KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP // KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP 
			// TELEPORTATION TUTORIAL

			/*
			P1.Move_And_Draw_Player({ 9,14 });	// ouins, last resort
						// Very Temporary! Doit être remove
			ConsoleRender::Add_String("TELEPORTATION SHOT", { (Find_Ctr_X((int)std::size("TELEPORTATION SHOT")) / 2) / 2, (gConHeight / 2) / 2 }, BRIGHT_WHITE, TXT_SPD_DR);
			ConsoleRender::Add_String("(Shoot, then spacebar)", { (Find_Ctr_X((int)std::size("(Shoot , then spacebar)")) / 2) / 2 , (gConHeight / 2) / 2 + 2 }, WHITE, TXT_SPD_DR);

			gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 3, linkGrid->Get_Rows() - 1 }, UP, linkGrid->Get_Rows() - 3);
			gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 3, 2 }, LEFT, linkGrid->Get_Cols() - 5);
			gGrids.Make_Chain_Of_Walls({ 2, 2 }, DOWN, 2);

			gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 4, linkGrid->Get_Rows() - 2 }, LEFT, linkGrid->Get_Cols() - 6);
			gGrids.Make_Chain_Of_Walls({ 2, linkGrid->Get_Rows() - 2 }, UP, 3);
			Add(3); Set_Interval(LEFT, 6, 9);skip = -1;
			skip = 5;
			break;

			Add(1);  gBoxSide = RIGHT; gSpwNum = spawnGrid->Get_MaxSpwnCrdY() - 1;	Set_Custom_Bot(SPWN_DLAY - 15);	break;
			MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE

			ConsoleRender::Add_String("TELEPORTATION SHOT", { (Find_Ctr_X((int)std::size("TELEPORTATION SHOT")) / 2) / 2, (gConHeight / 2) / 2 }, BRIGHT_WHITE, TXT_SPD_DR, 1);
			ConsoleRender::Add_String("(Shoot, then spacebar)", { (Find_Ctr_X((int)std::size("(Shoot , then spacebar)")) / 2) / 2 , (gConHeight / 2) / 2 + 2 }, WHITE, TXT_SPD_DR, 1);break; // breaky break
			*/
			// KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP // KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP // KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP KEEP 



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

	}
}

/* TEMPLATE DE PUZZLE SCRIPT*/



//void Puzzle_1_0(){
/*
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 6,6 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(10);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;
		break;


	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 11:
	case 12:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
*/
//}

//                                DISCLAIMER: l'ordre des définitions de méthodes suivantes ne veut pas dire que ce puzzle sera joué dans cet ordre
// Voici les puzzles du niveau
// da first
void Puzzle_1_0(){
	switch (gCurrPuzzleStep)
	{
	case 0:
		P1.Set_Position({ 6, 5 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(5);// Quantité d'ammo
		gCurrPuzzleStepMax = 11;
		break;


	case 1:	MsgQueue::Register(ENABLE_BLAST);
		Set_Dr_Map_1(TXT_SPD_DR * 4); skip = 6; // Erase la border au cas où le joueur est pas en mode quickstartS
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() / 2 ,linkGrid->Get_Rows() / 2 }, LEFT, 2);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() / 2 ,linkGrid->Get_Rows() / 2 }, RIGHT, 2);

		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() / 2 ,linkGrid->Get_Rows() / 2 }, DOWN, 1);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() / 2 + 1,linkGrid->Get_Rows() / 2 }, DOWN, 1);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() / 2 + 2,linkGrid->Get_Rows() / 2 }, DOWN, 1);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() / 2 - 1,linkGrid->Get_Rows() / 2 }, DOWN, 1);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() / 2 - 2,linkGrid->Get_Rows() / 2 }, DOWN, 1);
		break;

	case 2:
		// Présentation des mécaniques de bases pour le noob qui skip le tutorial
		Set_Flashy_Border(LEFT);
		Ev_Flash_Map_Border();	// Fait flasher la border pour signaler au joueur ou va aller Jerry
		ConsoleRender::Add_String(codeRecycling, { map.Get_Box_Limit(LEFT) - Half_String(codeRecycling) , map.Get_Box_Limit(UP) - 2 }, GRAY, TXT_SPD_DR);
		Add(1); gBoxSide = RIGHT;gSpwNum = spawnGrid->Get_MaxSpwnCrdY() / 2; break;

	case 3: Add(1); gBoxSide = RIGHT;gSpwNum = spawnGrid->Get_MaxSpwnCrdY() / 2; break;
	case 4: Add(1); gBoxSide = RIGHT;gSpwNum = spawnGrid->Get_MaxSpwnCrdY() / 2; break;
	case 5: Add(1); gBoxSide = RIGHT;gSpwNum = spawnGrid->Get_MaxSpwnCrdY() / 2; break;
	case 6: Add(1); gBoxSide = RIGHT;gSpwNum = spawnGrid->Get_MaxSpwnCrdY() / 2; skip = 8; break;
	case 7: Add(1); gBoxSide = RIGHT;gSpwNum = spawnGrid->Get_MaxSpwnCrdY() / 2 - 1; break;
	case 8: Add(1); gBoxSide = RIGHT;gSpwNum = spawnGrid->Get_MaxSpwnCrdY() / 2 - 1; break;
	case 9: Add(1); gBoxSide = RIGHT;gSpwNum = spawnGrid->Get_MaxSpwnCrdY() / 2 - 1; break;
	case 10:Add(1); gBoxSide = RIGHT;gSpwNum = spawnGrid->Get_MaxSpwnCrdY() / 2 - 1; break;
	case 11:Add(1); gBoxSide = RIGHT;gSpwNum = spawnGrid->Get_MaxSpwnCrdY() / 2 - 1; 
		ConsoleRender::Add_String(codeRecycling, { map.Get_Box_Limit(LEFT) - Half_String(codeRecycling) , map.Get_Box_Limit(UP) - 2 }, GRAY, TXT_SPD_DR, true);	// erase le message
		MsgQueue::Register(CHECKPOINT_REACHED);
		break;
	}
}



// Puzzle de ligne verticale à faire en haut
void Puzzle_1_2(){
	switch (gCurrPuzzleStep)
	{
	case 0:
		P1.Set_Position({ 6, 5 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(7);// Quantité d'ammo
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() / 2 - 1,0 }, DOWN, 1);
		gCurrPuzzleStepMax = 9;
		break;


	case 1:
		Just_Dr_Arr_Keys(true);
		Just_Dr_Wasd(true);
		Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() / 2);
		break;

	case 2:Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() / 2 - 1);break;	
	case 3:Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() / 2 - 2);break;	
	case 4:Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() / 2 - 3);break;	
	case 5:Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() / 2 - 4);break;	
	case 6:Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() / 2 - 5);break;	
	case 7:Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() / 2 - 6);break;	
	case 8:Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() / 2 - 7);break;	
	case 9:MsgQueue::Register(CHECKPOINT_REACHED);break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE	break;
	}
}


// MINI puzzle pour montrer que tu peux drain ta vie
void Puzzle_1_1() {
	static int y = Heart_Txt_Crd_Right("  ").y - 2;

	switch (gCurrPuzzleStep)
	{
	case 0:
		P1.Set_Position({ 10,11 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(0);// Quantité d'ammo
		gCurrPuzzleStepMax = 5;

		// Mur en L pour montrer au joueur comment dealer avec
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 1,3 }, LEFT, 1);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 2,3 }, DOWN, 1);
		break;


	case 1:ConsoleRender::Add_String(tip_01, { Heart_Txt_Crd_Left(TXT_CONST.DOTDOTDOT).x + 11 ,y }, WHITE, TXT_SPD_DR); skip = 1; break;
	case 2:ConsoleRender::Add_String(tip_01_1, { Heart_Txt_Crd_Right(tip_01_1).x - 10 ,y + 4 }, WHITE, TXT_SPD_DR); skip = 2; break;
	case 3:Add_Spec(LEFT, 3);Add_Spec(LEFT, 10);break;
	case 4: skip = 10; break;
	case 5:
		ConsoleRender::Add_String(tip_01, { Heart_Txt_Crd_Left(TXT_CONST.DOTDOTDOT).x + 11 ,y }, WHITE, TXT_SPD_DR, 1); skip = 3;
		ConsoleRender::Add_String(tip_01_1, { Heart_Txt_Crd_Right(tip_01_1).x - 10 ,y + 4 }, WHITE, TXT_SPD_DR, 1);
		MsgQueue::Register(CHECKPOINT_REACHED);	
		break;
	}
}


void Puzzle_1_3(){
	switch (gCurrPuzzleStep)
	{
	case 0:
		P1.Set_Position({ 6, 6 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(5);// Quantité d'ammo
		gCurrPuzzleStepMax = 5;
		gGrids.Make_Chain_Of_Walls({ 5, 7 }, DOWN, 3);
		break;

	// Ez one with a lesson: les root meurt quand ils ne sont plus attachés
	case 1:Add(3);Set_Interval(LEFT, 7, 10); skip = 2;break;
	case 3:Add_Spec(LEFT, 6); skip = 9; break;
	case 4:Add(4);Set_Interval(RIGHT, 6, 10);break;
	case 5:MsgQueue::Register(CHECKPOINT_REACHED);break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}


void Puzzle_1_4() {
	switch (gCurrPuzzleStep)
	{
	case 0:
		P1.Set_Position({ 9, 0 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(14);// Quantité d'ammo
		gCurrPuzzleStepMax = 11;
		gGrids.Make_Chain_Of_Walls({ 9,7 }, RIGHT, 1);
		break;

	case 1:	Add(1);gBoxSide = LEFT; gSpwNum = 0;break;
	case 2:	Add(1);gBoxSide = LEFT; gSpwNum = 1;break;
	case 3:	Add(1);gBoxSide = LEFT; gSpwNum = 2;break;
	case 4:	Add(1);gBoxSide = LEFT; gSpwNum = 3;break;
	case 5:	Add(1);gBoxSide = LEFT; gSpwNum = 4;break;
	case 6:	Add(1);gBoxSide = LEFT; gSpwNum = 5;break;
	case 7:	Add(1);gBoxSide = LEFT; gSpwNum = 6; skip = 1; break;
	case 8:	Add(1);gBoxSide = LEFT; gSpwNum = 0;break;
	case 9:Add(1);gBoxSide = LEFT; gSpwNum = 1;break;
	case 10:Add(1);gBoxSide = LEFT; gSpwNum = 2;break;
	case 11:Add(1);gBoxSide = LEFT; gSpwNum = 3;break;
	case 12:Add(1);gBoxSide = LEFT; gSpwNum = 4;break;
	case 13:Add(1);gBoxSide = LEFT; gSpwNum = 5;break;
	case 14:Add(1);gBoxSide = LEFT; gSpwNum = 6; skip = 1;break;
	case 15:
		ConsoleRender::Add_String(tip_01, { (Find_Ctr_X((int)std::size(tip_01)) / 2) / 2, (gConHeight / 2) / 2 }, BRIGHT_WHITE, TXT_SPD_ER, 1);
		ConsoleRender::Add_String(tip_01_1, { (Find_Ctr_X((int)std::size(tip_01_1)) / 2) / 2 + 4, (gConHeight / 2) / 2 + 2 }, WHITE, TXT_SPD_DR, 1);
		MsgQueue::Register(CHECKPOINT_REACHED); // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHEREbreak;
		break;
	}
}

void Puzzle_1_5()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 12,8 });			// Coord de départ du joueur
		blastP1.Get_Ammo_Manager().Set_Ammo(0);// Quantité d'ammo
		gCurrPuzzleStepMax = 13;
		Cancel_Checkpoint_Delay();	// Si le joueur spawn à côté d'un mur, on veut pas effacer le mur, alors on enlève le delay entre la prochaine wave, et on spawn les murs APRÈS l'animation
		break;


	case 1:
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 1,7 }, LEFT, linkGrid->Get_Cols() - 1);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 1,9 }, LEFT, linkGrid->Get_Cols() - 1);

		// Wall du milieu à transfer
		gGrids.Make_Chain_Of_Walls({ 0,8 }, RIGHT, 11);
		break;

	case 2:	  Add_Spec(LEFT, 7);skip = 4;break;
	case 3:	  Add_Spec(LEFT, 8);skip = 1;break;
	case 4:	  Add_Spec(LEFT, 7);skip = 1;break;
	case 5:	  Add_Spec(LEFT, 8);skip = 1;break;
	case 6:	  Add_Spec(LEFT, 7);skip = 1;break;
	case 7:	  Add_Spec(LEFT, 8);skip = 1;break;
	case 8:	  Add_Spec(LEFT, 7);skip = 1;break;
	case 9:	  Add_Spec(LEFT, 8);skip = 1;break;
	case 11:  Add_Spec(LEFT, 7);skip = 1;break;
	case 12:  Add_Spec(LEFT, 8); skip = 1;break;
	case 13:  Add_Spec(LEFT, 7);MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE 
	}
}


void Puzzle_1_6() {
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 1,5 });		   // Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(0);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;
		Cancel_Checkpoint_Delay();
		break;


	case 1:
		gGrids.Make_Chain_Of_Walls({ 3,5 }, LEFT, 1);
		gGrids.Make_Chain_Of_Walls({ 2,6 }, RIGHT, 1);

		gGrids.Make_Chain_Of_Walls({ 5,5 }, LEFT, 1);
		gGrids.Make_Chain_Of_Walls({ 4,6 }, RIGHT, 1);

		gGrids.Make_Chain_Of_Walls({ 8,8 }, LEFT, 1);
		gGrids.Make_Chain_Of_Walls({ 7,7 }, RIGHT, 1);

		gGrids.Make_Chain_Of_Walls({ 10,8 }, LEFT, 1);
		gGrids.Make_Chain_Of_Walls({ 9,7 }, RIGHT, 1);

		// Wall du milieu à transfer
		//gGrids.Make_Chain_Of_Walls({ 4,11 }, LEFT, 1);
		//gGrids.Make_Chain_Of_Walls({ 4,10 }, RIGHT, 1);
		//gGrids.Make_Chain_Of_Walls({ 5,9 }, LEFT, 1);
		//gGrids.Make_Chain_Of_Walls({ 5,8 }, RIGHT, 1);
		//gGrids.Make_Chain_Of_Walls({ 6,7 }, LEFT, 1);
		//gGrids.Make_Chain_Of_Walls({ 6,6 }, RIGHT, 1);
		break;

	case 2:Add_Spec(RIGHT, 0); skip = 2; break;
	case 3:Add_Spec(RIGHT, 0); skip = 2; break;
	case 4:Add_Spec(RIGHT, 0); skip = 2; break;
	case 5:Add_Spec(RIGHT, 0); skip = 2; break;
	case 6:Add_Spec(LEFT, 13); skip = 2; break;
	case 7:Add_Spec(LEFT, 13); skip = 2; break;
	case 8:Add_Spec(LEFT, 13); skip = 2; break;
	case 9:Add_Spec(LEFT, 13); skip = 2; break;
	case 11:
	case 12:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE 
	}
}

// REPRISE: root qui meurt au milieu
void Puzzle_1_7(){
	switch (gCurrPuzzleStep)
	{
	case 0:
		P1.Set_Position({ 4,7 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(12);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;
		gGrids.Make_Chain_Of_Walls({ 6, 7 }, UP, 2);
		gGrids.Make_Chain_Of_Walls({ 6, 7 }, DOWN, 2);
		break;

		// Ez one with a lesson: les root meurt quand ils ne sont plus attachés
	case 1:Add(2);Set_Interval(RIGHT, 7, 9); skip = 2;break;
	case 2:Add(2);Set_Interval(LEFT, 5, 7); skip = 4;break;

	case 3:Add(3);Set_Interval(RIGHT, 7, 10); skip = 4;break;
	case 4:Add_Spec(LEFT, 6); skip = 9; break;

	case 5:Add(3);Set_Interval(RIGHT, 4, 7); skip = 3;break;
	case 6:Add_Spec(RIGHT, 7); skip = 9; break;
	case 7:Add(4);Set_Interval(LEFT, 5, 7);Set_Interval(RIGHT, 7, 9); break;
	case 8:MsgQueue::Register(CHECKPOINT_REACHED);break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}



void Puzzle_1_8(){
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 4,1 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(0);// Quantité d'ammo
		gCurrPuzzleStepMax = 13;

		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 2, 1 }, LEFT, 5);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 2, 1 }, DOWN, 1);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 1, 4 }, LEFT, 1);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 1, 5 }, LEFT, 1);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 1, 6 }, LEFT, 1);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 1, 7 }, LEFT, 1);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 1, 8 }, LEFT, 1);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 1, 9 }, LEFT, 1);
		//gGrids.Make_Chain_Of_Walls({ 5, 12 }, RIGHT, 6);
		break;

	case 1: Add_Spec(RIGHT, 0);break;
	case 2:	Add_Spec(RIGHT, 0);skip = 1;break;
	case 3:	Add_Spec(RIGHT, 0);skip = 1;break;
	case 4:	Add_Spec(RIGHT, 0);skip = 1;break;
	case 5:	Add_Spec(RIGHT, 0);skip = 4;break;
	case 6:Add(1);gBoxSide = LEFT; gSpwNum = 7;break;
	case 7:Add(1);gBoxSide = LEFT; gSpwNum = 6;break;
	case 8:Add(1);gBoxSide = LEFT; gSpwNum = 5;break;
	case 9:Add(1);gBoxSide = LEFT; gSpwNum = 4;break;
	case 10:Add(1);gBoxSide = LEFT; gSpwNum = 3;break;
	case 11:Add(1);gBoxSide = LEFT; gSpwNum = 2;break;
	case 12:Add(1);gBoxSide = LEFT; gSpwNum = 1; skip = 1;break;
		// Pt de trop
	//case 13:Add(1);gBoxSide = LEFT; gSpwNum = 13;break;
	//case 14:Add(1);gBoxSide = LEFT; gSpwNum = 13;break;
	//case 15:Add(1);gBoxSide = LEFT; gSpwNum = 13;break;
	//case 16:Add(1);gBoxSide = LEFT; gSpwNum = 13;break;
	//case 17:Add(1);gBoxSide = LEFT; gSpwNum = 13;break;
	//case 18:Add(1);gBoxSide = LEFT; gSpwNum = 13;break;
	case 13:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE 
	}
}

void Puzzle_1_9()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 11,7 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(18);// Quantité d'ammo
		gCurrPuzzleStepMax = 8;
		break;

	case 1:Add(1); gBoxSide = LEFT; gSpwNum = 9; break;
	case 2:Add(2);Set_Interval(LEFT, 7, 9);	skip = 10;	break;
	case 3:Add(4);Set_Interval(LEFT, 0, 2);Set_Interval(RIGHT, 1, 3); skip = 5;break;
	case 4:Add(2);Set_Interval(LEFT, 3, 5);  skip = 3;break;
	case 5:Add(2);Set_Interval(LEFT, 7, 9);  skip = 3; break;
	case 6:Add(2);Set_Interval(RIGHT, 3, 5); skip = 3;break;
	case 7:Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() - 2);Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() - 1);skip = 2;break;
	case 8:Add(2);Set_Interval(RIGHT, 7, 9);MsgQueue::Register(CHECKPOINT_REACHED); break;// CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}


// SATISFAISANT! Montre les walls transfer...	FUCKING HARD
void Puzzle_1_10() {
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 4,7 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(1);// Quantité d'ammo
		gCurrPuzzleStepMax = 9;

		// Quelque mur en forme de L sur la bordure left
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


	case 1:Add_Spec(LEFT, 6);break;
	case 2:Add_Spec(LEFT, 8);skip = 4;break;
	case 3:Add_Spec(LEFT, 9);skip = 2;break;
	case 4:Add_Spec(LEFT, 9);break;
	case 5:Add_Spec(LEFT, 5);skip = 5;break;
	case 6:Add_Spec(LEFT, 7);skip = 2;break;
	case 7:Add_Spec(LEFT, 9);skip = 3;break;
	case 8:Add_Spec(LEFT, 5);break;
	case 9:MsgQueue::Register(CHECKPOINT_REACHED);			break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}

void Puzzle_1_11()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 6,7 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(10);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 1, 3 }, LEFT, 1);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 2, 3 }, DOWN, 1);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 2, 4 }, LEFT, 5);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 2 - 5, 4 }, DOWN, 1);
		break;

	case 1:	Add(10);Set_Interval(LEFT, 4, 9);Set_Interval(RIGHT, 9, 14); skip = 5;break;
	case 2:	Add_Spec(UP, spawnGrid->Get_MaxSpwnCrdX() - 1);
		instantSpawn = true;
		MsgQueue::Register(CHECKPOINT_REACHED); // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
		break;

	}
}

// EZ Vertical introduction!
void Puzzle_1_12()
{	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 6,7 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(6);// Quantité d'ammo
		gCurrPuzzleStepMax = 7;
		gGrids.Make_Chain_Of_Walls({ 3,6 }, LEFT, 3);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 4,7 }, RIGHT, 3);
		break;

	case 1:Add_Spec(DOWN, spawnGrid->Get_MaxSpwnCrdX() - 1); Add_Spec(DOWN, 2);break;
	case 2:Add_Spec(DOWN, spawnGrid->Get_MaxSpwnCrdX() - 2); Add_Spec(DOWN, 1);break;
	case 3:Add_Spec(DOWN, spawnGrid->Get_MaxSpwnCrdX() - 3); Add_Spec(DOWN, 0);break;
	case 4:Add_Spec(UP, 0); Add_Spec(UP, spawnGrid->Get_MaxSpwnCrdX() - 3);break;
	case 5:Add_Spec(UP, 1); Add_Spec(UP, spawnGrid->Get_MaxSpwnCrdX() - 2);break;
	case 6:Add_Spec(UP, 2); Add_Spec(UP, spawnGrid->Get_MaxSpwnCrdX() - 1);break;
	case 7:MsgQueue::Register(CHECKPOINT_REACHED); break;// CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}

// redirect couloir au milieu
void Puzzle_1_13()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 7,5 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(0);// Quantité d'ammo
		gCurrPuzzleStepMax = 21;
		gGrids.Make_Chain_Of_Walls({ 0,10 }, RIGHT, 9);
		gGrids.Make_Chain_Of_Walls({ 9,10 }, UP, 6);	// max = 9[
		gGrids.Make_Chain_Of_Walls({ 8,10 }, UP, 3);
		gGrids.Make_Chain_Of_Walls({ 7,10 }, UP, 3);
		gGrids.Make_Chain_Of_Walls({ 6,10 }, UP, 4);
		gGrids.Make_Chain_Of_Walls({ 5,10 }, UP, 5);
		gGrids.Make_Chain_Of_Walls({ 4,10 }, UP, 6);
		break;

	case 1:	Add_Spec(UP, 8);break;
	case 2:Add_Spec(UP, 4);skip = 1;break;
	case 3:Add_Spec(UP, 6);skip = 1;break;
	case 4:Add_Spec(UP, 5);skip = 1;break;
	case 5:Add_Spec(LEFT, 4);Add_Spec(RIGHT, 4);skip = 2;break;
	case 6:Add_Spec(UP, 5);skip = 1;break;
	case 7:Add_Spec(UP, 7);skip = 1;break;
	case 8:Add_Spec(UP, 7);skip = 1;break;
	case 9:Add_Spec(UP, 7);skip = 1;break;
	case 10:Add_Spec(LEFT, 5);Add_Spec(RIGHT, 5);skip = 2;break;
	case 11:Add_Spec(UP, 8);skip = 1;break;
	case 12:Add_Spec(UP, 4);skip = 1;break;
	case 13:Add_Spec(UP, 4);skip = 1;break;
	case 14:Add_Spec(UP, 7);skip = 1;break;
	case 15:Add_Spec(LEFT, 6);Add_Spec(RIGHT, 6);skip = 4;break;
	case 16:Add_Spec(UP, 4);skip = 2;break;
	case 17:Add_Spec(LEFT, 7);Add_Spec(UP, 4);skip = 2;break;
	case 18:Add_Spec(UP, 8);skip = 1;break;
	case 19:Add_Spec(LEFT, 9);Add_Spec(RIGHT, 8);Add_Spec(UP, 7);skip = 2;break;
	case 20:Add_Spec(RIGHT, 9);skip = 3;break;
	case 21:Add(9);Set_Interval(DOWN, 0, 9); MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE 
	}
}


// MUST BE REDONE
void Puzzle_1_14()
{	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 10,1 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(19);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;
		break;

		// Challenging teleporting all sides
		case 1:Add_Spec(LEFT, 2); Set_Custom_Bot(SPWN_DLAY / 2);break;
		case 2:Add_Spec(UP, 8); Add_Spec(UP, 9); skip = 4; break;
		case 3:Add_Spec(UP, 1);skip = 1;break;
		case 4:Add_Spec(LEFT, 1); Add_Spec(LEFT, 2); skip = 6;break;
		case 5:Add_Spec(LEFT, 13);skip = 2;break;
		case 6:Add_Spec(DOWN, 1); Add_Spec(DOWN, 2); skip = 4;break;
		case 7:Add_Spec(DOWN, 11);skip = 1;break;
		case 8:Add_Spec(DOWN, 8);Add_Spec(DOWN, 9); Add_Spec(RIGHT, 11);skip = 1;break;
		case 9:Add_Spec(RIGHT, 5); skip = 1; break;
		case 10:Add_Spec(UP, 11);	skip = 1;break;
		case 11:Add_Spec(RIGHT, 3);skip = 4; break;
		case 12:Add_Spec(UP, 11); break;
		case 13:Add_Spec(RIGHT, 1);break;
		case 14:Add_Spec(RIGHT, 0);MsgQueue::Register(CHECKPOINT_REACHED); break;// CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}

// 2 long wall d'obstacle
void Puzzle_1_15()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 12,3 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(37);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;
		gGrids.Make_Chain_Of_Walls({ 3,14 }, UP, 14);
		gGrids.Make_Chain_Of_Walls({ 9,0 }, DOWN, 14);
		break;

	case 1:Add_Spec(RIGHT, 0);Add_Spec(RIGHT, 1);break;
	case 2:Add_Spec(RIGHT, 4);Add_Spec(RIGHT, 5);break;
	case 3:Add_Spec(UP, 9); Add_Spec(UP, 10); skip = 7; break;
	case 4:Add_Spec(RIGHT, 0);Add_Spec(RIGHT, 1); break;
	case 5:Add_Spec(UP, 9);Add_Spec(UP, 10);Add_Spec(UP, 11);skip = 2;break;
	case 6:Add_Spec(RIGHT, 0);skip = 2;break;
	case 7:Add(6);Set_Interval(DOWN, 3, 9); skip = 12;break;
	case 8:Add_Spec(UP, 0);Add_Spec(UP, 1); break;
	case 9:Add_Spec(LEFT, 13);break;
	case 10:Add_Spec(LEFT, 7);Add_Spec(LEFT, 8);skip = 3; break;
	case 11:Add_Spec(UP, 0);Add_Spec(UP, 1);Add_Spec(UP, 2);break;
	case 12:Add_Spec(LEFT, 5);Add_Spec(LEFT, 6);skip = 3;break;
	case 13:Add_Spec(LEFT, 13); skip = 12; break;
	case 14:Add(12);Set_Interval(UP, 0, linkGrid->Get_Cols() - 1); MsgQueue::Register(CHECKPOINT_REACHED); break;// CHECKPOINTHERE C
	}
}

// Super hard: mais différent des autres, juste avant le FINAL HOUR 
// Static shoot dans tout les sens
// 1-12 LEFT/RIGHT
// 1-10	UP/DOWN 
void Puzzle_1_16()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 6,7 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(41);// Quantité d'ammo
		gCurrPuzzleStepMax = 27;

		gGrids.Make_Chain_Of_Walls({ 6,1 }, UP, 1);
		gGrids.Make_Chain_Of_Walls({ 6,13 }, DOWN, 1);
		gGrids.Make_Chain_Of_Walls({ 1,7 }, LEFT, 1);
		gGrids.Make_Chain_Of_Walls({ 11,7 }, RIGHT, 1);
		break;

	case 1:Add_Spec(UP, 10);break;
	case 2:Add_Spec(LEFT, 1);break;
	case 3:Add_Spec(DOWN, 1);break;
	case 4:Add_Spec(RIGHT, 12);skip = 2;break;
	case 5:Add_Spec(UP, 10);break;
	case 6:Add_Spec(LEFT, 1);break;
	case 7:Add_Spec(DOWN, 1);break;
	case 8:Add_Spec(DOWN, 10);skip = 1;break;
	case 9:Add_Spec(RIGHT, 1);break;
	case 11:Add_Spec(UP, 1);break;
	case 12:Add_Spec(RIGHT, 12);break;
	case 13:Add_Spec(UP, 1);break;
	case 14:Add_Spec(UP, 10);break;
	case 15:Add_Spec(LEFT, 1);break;
	case 16:Add_Spec(LEFT, 1);break;
	case 17:Add_Spec(DOWN, 10);break;
	case 18:Add_Spec(LEFT, 12);break;
	case 19:Add_Spec(UP, 1);break;
	case 20:Add_Spec(LEFT, 12); skip = 3;break;
	case 21:Add_Spec(DOWN, 10);break;
	case 22:Add_Spec(RIGHT, 12);break;
	case 23:Add_Spec(LEFT, 2);break;
	case 24:Add_Spec(UP, 9);break;
	case 25:Add_Spec(RIGHT, 11);break;
	case 26:Add_Spec(DOWN, 2);skip = 12; break;
	case 27:Add_Spec(UP, 4);Add_Spec(DOWN, 7);Add_Spec(LEFT, 5);Add_Spec(RIGHT, 8); MsgQueue::Register(CHECKPOINT_REACHED);break;// CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}


// THE FINAL CHALLENGE IS HERE HAHAHAHAHAH
void Puzzle_1_17()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 3,7 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(20);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;

		if (!seenFinalHour)
		{ MsgQueue::Register(LOCK_PLAYER);P1.Er_Player(); }
		break;

	case 1:
		if (!seenFinalHour)
		{
			MsgQueue::Register(FINAL_HOUR);	// montre ça juste une fois, EVER
			seenFinalHour = true;
			skip = 10;
		}
		break;



	case 2:
		if (P1.Cant_Do_Stuff())
			Set_Ev_Spawn_Player(3);

		ItemSpawner::Spawn_This_Item(ItemType::HEALTH, { 6,4 });
		skip = 5;
		break;

	case 3:
		ItemSpawner::Add_To_Pool(ItemType::HEALTH, 700, 0);
		MsgQueue::Register(ENABLE_ITEM_SPAWN);
		skip = 7;
		break;

	case 4:Add(1);skip = 1;break;
	case 5:Add(1);skip = 2;break;
	case 6:Add(1);skip = 2;break;
	case 7:Add(1);skip = 3;break;
	case 8:Add(1);skip = 4;break;
	case 9:Add(1);skip = 1;break;
	case 10:Add(1);skip = 1;break;
	case 11:Add(1);skip = 1;break;
	case 12:Add(1);skip = 1;break;
	case 13:Add(1);skip = 1;break;
	case 14:Add(1);skip = 1;break;
	case 15:Add(1);skip = 4;break;
	case 16:Add(1);skip = 4;break;
	case 17:Add(1);skip = 4;break;
	case 18:Add(1);skip = 4;break;
	case 19:ItemSpawner::Set_Spawner_Timer(ItemType::HEALTH, 1000, 0);break;	// Augmente vitesse des spawnsAdd(1);skip = 3;break;
	case 20:Add(1);skip = 3;break;
	case 21:Add(1);skip = 3;break;
	case 22:Add(1);skip = 3;break;
	case 23:Add(1);skip = 3;break;
	case 24:Add(1);skip = 3;break;
	case 25:Add(1);skip = 3;break;
	case 26:Add(1);skip = 3;break;
	case 27:Add(1);skip = 3;break;
	case 28:Add(1);skip = 3;break;
	case 29:Add(1);skip = 4;break;
	case 30:Add(1);skip = 4;break;
	case 31:Add(1);skip = 4;break;
	case 32:Add(1);skip = 4;break;
	case 33:Add(1);skip = 4;break;
	case 34:Add(1);skip = 4;break;
	case 35:Add(1);skip = 4;break;
	case 36:Add(1);skip = 3;break;
	case 37:Add(1);skip = 3;break;
	case 38:Add(1);skip = 3;break;
	case 39:Add(1);skip = 3;break;
	case 40:Add(1);skip = 3;break;
	case 41:Add(1);skip = 3;break;
	case 42:Add(1);skip = 2;break;
	case 43:Add(1);skip = 2;break;
	case 44:Add(1);skip = 2;break;
	case 45:Add(1);skip = 1;break;
	case 46:Add(1);skip = 1;break;
	case 47:Add(1);skip = 1;break;
	case 48:Add(1);break;
	case 49:
		// VICTORY IS OURS HAHAHAHAHAHAH
		MsgQueue::Register(STOP_BOT_SPAWNS);
		Ev_Wait_For_Victory(); // Wait que le dernier bot meurt pour trigger la victoire
		break;
	}
}
