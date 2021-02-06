

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
#include "../../spawns/valid_spwn_intervals.h"
#include "../../console/sweet_cmd_console.h"


// GENERAL RULES FOR THIS DUMB BROKEN SHIT: 
// D�passe jamais le nombre de spawn permis sur une bordure
// AddSpecific(): Ne setup jamais une boxside random avec un spw pr�cis
// CETTE FORMULE CRASH 100% DU TEMPS // Add(1); gBoxSide = LEFT; gSpwNum = spawnGrid->Get_MaxSpwnCrdY() - 1; 
// Combiner BoxSide, Spwnum avec plus qu'un spawn, �a cr�er des exceptions
// Setup un intervalle de spawn trop petit pour le total va faire crash� le shit Ex : Set_Interval(RIGHT, 10, 13);Add(4); break;

using namespace bots_to_spawn;


// Puzzles du lvl1:
void Puzzle_1_0();
void Puzzle_1_1();
void Puzzle_1_2();
void Puzzle_1_3();
void Puzzle_1_4();
void Puzzle_1_5();	
void Puzzle_1_6();
void Puzzle_1_7();
void Puzzle_1_8();	
void Puzzle_1_9();
void Puzzle_1_10();
void Puzzle_1_11();
void Puzzle_1_12();
void Puzzle_1_13();
void Puzzle_1_14();
void Puzzle_1_15();
void Puzzle_1_16();
void Puzzle_1_17();


// VOICI  l'ordre dans lequel sera jou� les puzzles
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
static std::string codeRecycling = "(Don't let the shapes reach this border)";
static std::string tip_01 = "Health Is Ammo ->";
static std::string tip_01_1 = "Shoot to drain hp ";
static bool seenFinalHour = false;
static int skip;

void Lvl_1_Spwn_Script()
{
	if (gSpawnThisCycle)
	{
		skip = 0;	// Repr�sente le nombre de fois qu'on va Skip un cycle de spawn selon l'indice de temps: Delay * Spawn_Cycle

		LVL1_PUZZLES[gCurrentPuzzle[gCurrentLevel - 1]]();	// Script du puzzle

		// Ceci ajoute du temps entre le spawn actuel et le prochain
		if (skip)
			gSpwBotTimer.Add_Count(skip);

		gCurrPuzzleStep++;	// Prochain step du puzzle!
	}
}

// Voici les puzzles du niveau
void Puzzle_1_0(){
	switch (gCurrPuzzleStep)
	{
	case 0:
		P1.Set_Position({ 6, 5 });				// Coord de d�part du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(5);// Quantit� d'ammo
		gCurrPuzzleStepMax = 11;


		// reset cette variable ici
		seenFinalHour = false;
		break;


	case 1:	MsgQueue::Register(ENABLE_BLAST);

		Set_Dr_Map_1(TXT_SPD_DR * 4); skip = 6; 
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() / 2 ,linkGrid->Get_Rows() / 2 }, LEFT, 2);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() / 2 ,linkGrid->Get_Rows() / 2 }, RIGHT, 2);

		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() / 2 ,linkGrid->Get_Rows() / 2 }, DOWN, 1);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() / 2 + 1,linkGrid->Get_Rows() / 2 }, DOWN, 1);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() / 2 + 2,linkGrid->Get_Rows() / 2 }, DOWN, 1);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() / 2 - 1,linkGrid->Get_Rows() / 2 }, DOWN, 1);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() / 2 - 2,linkGrid->Get_Rows() / 2 }, DOWN, 1);
		break;

	case 2:
		// Pr�sentation des m�caniques de bases pour le noob qui skip le tutorial
		Set_Flashy_Border(LEFT);
		Ev_Flash_Map_Border();	// Fait flasher la border pour signaler au joueur ou va aller les bots
		ConsoleRender::Add_String(codeRecycling, { map.Get_Limit(LEFT) - Half_String(codeRecycling) , map.Get_Limit(UP) - 2 }, GRAY, TXT_SPD_DR);
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
		ConsoleRender::Add_String(codeRecycling, { map.Get_Limit(LEFT) - Half_String(codeRecycling) , map.Get_Limit(UP) - 2 }, GRAY, TXT_SPD_DR, true);	// erase le message
		MsgQueue::Register(CHECKPOINT_REACHED);
		break;
	}
}



// Puzzle de ligne verticale � faire en haut
void Puzzle_1_1(){
	switch (gCurrPuzzleStep)
	{
	case 0:
		P1.Set_Position({ 6, 5 });				// Coord de d�part du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(7);// Quantit� d'ammo
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() / 2 - 1,0 }, DOWN, 1);
		gCurrPuzzleStepMax = 9;

		Ev_Er_Arr_Keys();
		Ev_Er_Wasd();
		break;


	case 1:

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
void Puzzle_1_2() {

	switch (gCurrPuzzleStep)
	{
	case 0:
		P1.Set_Position({ 6,6 });				// Coord de d�part du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(2);// Quantit� d'ammo
		gCurrPuzzleStepMax = 5;

		// Mur en L pour montrer au joueur comment dealer avec
		gGrids.Make_Chain_Of_Walls({ 0,3 }, RIGHT, 1);
		gGrids.Make_Chain_Of_Walls({ 12,11 }, LEFT, 1);
		gGrids.Make_Chain_Of_Walls({ 1,3 }, DOWN, 1);
		break;


	case 1:Add_Spec(RIGHT, 3);skip = 2; break;
	case 2:Add_Spec(LEFT, 10);
		Add_Spec(LEFT, 9);
		break;

	case 3:
		MsgQueue::Register(CHECKPOINT_REACHED);	
		break;
	}
}


void Puzzle_1_3(){
	switch (gCurrPuzzleStep)
	{
	case 0:
		P1.Set_Position({ 5, 5 });				// Coord de d�part du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(5);// Quantit� d'ammo
		gCurrPuzzleStepMax = 5;
		gGrids.Make_Chain_Of_Walls({ 5, 7 }, DOWN, 3);
		break;

	// Ez one with a lesson: les root meurt quand ils ne sont plus attach�s
	case 1:Add(3);Set_Interval(LEFT, 7, 10); skip = 2;break;
	case 3:Add_Spec(LEFT, 6); skip = 5; break;
	case 4:Add(4);Set_Interval(RIGHT, 6, 10);break;
	case 5:MsgQueue::Register(CHECKPOINT_REACHED);break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}


void Puzzle_1_4() {
	switch (gCurrPuzzleStep)
	{
	case 0:
		P1.Set_Position({ 9, 3 });				// Coord de d�part du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(13);// Quantit� d'ammo
		gCurrPuzzleStepMax = 11;
		gGrids.Make_Chain_Of_Walls({ 9,7 }, RIGHT, 1);
		gGrids.Make_Chain_Of_Walls({ 9,7 }, UP, 1);
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
	case 0:P1.Set_Position({ 12,8 });			// Coord de d�part du joueur
		blastP1.Get_Ammo_Manager().Set_Ammo(0);// Quantit� d'ammo
		gCurrPuzzleStepMax = 13;
		Cancel_Checkpoint_Delay();	// Si le joueur spawn � c�t� d'un mur, on veut pas effacer le mur, alors on enl�ve le delay entre la prochaine wave, et on spawn les murs APR�S l'animation
		Set_Ev_Spawn_Player(3, true);
		break;

	case 1:

		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 1,7 }, LEFT, linkGrid->Get_Cols() - 1);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 1,9 }, LEFT, linkGrid->Get_Cols() - 1);
		gGrids.Make_Chain_Of_Walls({ 0,8 }, RIGHT, 11); // Wall du milieu � transfer
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
	case 0:P1.Set_Position({ 1,5 });		   // Coord de d�part du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(0);// Quantit� d'ammo
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
		P1.Set_Position({ 4,7 });				// Coord de d�part du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(12);// Quantit� d'ammo
		gCurrPuzzleStepMax = 12;
		gGrids.Make_Chain_Of_Walls({ 6, 7 }, UP, 2);
		gGrids.Make_Chain_Of_Walls({ 6, 7 }, DOWN, 2);
		break;

		// Ez one with a lesson: les root meurt quand ils ne sont plus attach�s
	case 1:Add(2);Set_Interval(RIGHT, 7, 9); skip = 2;break;
	case 2:Add(2);Set_Interval(LEFT, 5, 7); skip = 4;break;

	case 3:Add(3);Set_Interval(RIGHT, 7, 10); skip = 4;break;
	case 4:Add_Spec(LEFT, 6); skip = 7; break;

	case 5:Add(3);Set_Interval(RIGHT, 4, 7); skip = 3;break;
	case 6:Add_Spec(RIGHT, 7); skip = 9; break;
	case 7:Add(4);Set_Interval(LEFT, 5, 7);Set_Interval(RIGHT, 7, 9); break;
	case 8:MsgQueue::Register(CHECKPOINT_REACHED);break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}



void Puzzle_1_8(){
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 4,1 });				// Coord de d�part du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(0);// Quantit� d'ammo
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
	case 13:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE 
	}
}

void Puzzle_1_9()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 11,7 });				// Coord de d�part du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(18);// Quantit� d'ammo
		gCurrPuzzleStepMax = 8;
		break;

	case 1:Add(1); gBoxSide = LEFT; gSpwNum = 9; break;
	case 2:Add(2);Set_Interval(LEFT, 7, 9);	skip = 10;	break;
	case 3:Add(2);Set_Interval(LEFT, 0, 2);	skip = 1; break;
	case 4:Add(2);Set_Interval(RIGHT, 1, 3); skip = 5;break;
	case 5:Add(2);Set_Interval(LEFT, 3, 5);  skip = 3;break;
	case 6:Add(2);Set_Interval(RIGHT, 3, 5); skip = 5;break;
	case 7:Add(2);Set_Interval(LEFT, 7, 9);  skip = 3; break;
	case 8:Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() - 2);Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() - 1);break;
	case 9:Add(2);Set_Interval(RIGHT, 7, 9);MsgQueue::Register(CHECKPOINT_REACHED); break;// CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}


// SATISFAISANT! Montre les walls transfer...	FUCKING HARD
void Puzzle_1_10() {
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 4,7 });				// Coord de d�part du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(0);// Quantit� d'ammo
		gCurrPuzzleStepMax = 9;

		// Quelque mur en forme de L sur la bordure left
		gGrids.Make_Chain_Of_Walls({ 0, 8 }, RIGHT, 1);
		gGrids.Make_Chain_Of_Walls({ 1, 8 }, DOWN, 1);

		gGrids.Make_Chain_Of_Walls({ 0, 10 }, RIGHT, 1);
		gGrids.Make_Chain_Of_Walls({ 1, 10 }, DOWN, 1);

		gGrids.Make_Chain_Of_Walls({ 0, 13 }, RIGHT, 1);
		gGrids.Make_Chain_Of_Walls({ 1, 13 }, UP, 1);

		// Quelques lignes sur la bordure right
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 1, 2 }, LEFT, 1);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 1, 3 }, LEFT, 1);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 1, 5 }, LEFT, 1);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 1, 6 }, LEFT, 1);
		break;


	case 1:Add_Spec(LEFT, 6 + 3);break;
	case 2:Add_Spec(LEFT, 8 + 3);skip = 4;break;
	case 3:Add_Spec(LEFT, 7 + 3);skip = 2;break;
	case 4:Add_Spec(LEFT, 6 + 3);skip = 3;break;
	case 5:Add_Spec(LEFT, 7 + 3);skip = 3;break;
	case 6:Add_Spec(LEFT, 6);skip = 3;break;
	case 7:Add_Spec(LEFT, 5);skip = 3;break;
	case 8:Add_Spec(LEFT, 3);skip = 1;break;
	case 9:Add_Spec(LEFT, 2);break;
	case 10:MsgQueue::Register(CHECKPOINT_REACHED);			break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}

void Puzzle_1_11()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 6,7 });				// Coord de d�part du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(10);// Quantit� d'ammo
		gCurrPuzzleStepMax = 12;
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 1, 3 }, LEFT, 1);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 2, 3 }, DOWN, 1);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 2, 4 }, LEFT, 5);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 2 - 5, 4 }, DOWN, 1);
		break;

	case 1:skip = 2; break;
	case 2:Add(10);Set_Interval(LEFT, 4, 9);Set_Interval(RIGHT, 9, 14); skip = 5;break;
	case 3:Add_Spec(UP, spawnGrid->Get_MaxSpwnCrdX() - 1);
		instantSpawn = true;
		MsgQueue::Register(CHECKPOINT_REACHED); // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
		break;

	}
}

// EZ Vertical introduction!
void Puzzle_1_12()
{	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 6,7 });				// Coord de d�part du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(6);// Quantit� d'ammo
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
	case 0:P1.Set_Position({ 7,5 });				// Coord de d�part du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(1);// Quantit� d'ammo
		gCurrPuzzleStepMax = 21;
		gGrids.Make_Chain_Of_Walls({ 0,10 }, RIGHT, 9);
		gGrids.Make_Chain_Of_Walls({ 9,10 }, UP, 7);	// max = 9[
		gGrids.Make_Chain_Of_Walls({ 8,10 }, UP, 3);
		gGrids.Make_Chain_Of_Walls({ 7,10 }, UP, 3);
		gGrids.Make_Chain_Of_Walls({ 6,10 }, UP, 4);
		gGrids.Make_Chain_Of_Walls({ 5,10 }, UP, 5);
		gGrids.Make_Chain_Of_Walls({ 4,10 }, UP, 7);
		break;

	case 1:Add_Spec(RIGHT, 3);Add_Spec(LEFT, 3);break;
	case 2: Add_Spec(UP, 4);skip = 1;break;
	case 3: Add_Spec(UP, 6);skip = 2;break;
	case 4: Add_Spec(UP, 5);skip = 3;break;
	case 5: Add_Spec(LEFT, 4);Add_Spec(RIGHT, 4);skip = 6;break;
	case 6: Add_Spec(UP, 5);skip = 1;break;
	case 7: Add_Spec(UP, 7);skip = 2;break;
	case 8: Add_Spec(UP, 7);skip = 1;break;
	case 9: Add_Spec(UP, 7);skip = 1;break;
	case 10:Add_Spec(LEFT, 5);Add_Spec(RIGHT, 5);skip = 6;break;
	case 11:Add_Spec(UP, 8);skip = 1;break;
	case 12:Add_Spec(UP, 4);skip = 2;break;
	case 13:Add_Spec(UP, 4);skip = 3;break;
	case 14:Add_Spec(UP, 7);skip = 1;break;
	case 15:Add_Spec(LEFT, 6);Add_Spec(RIGHT, 6);skip = 6;break;
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
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 6,6 });				// Coord de d�part du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(12);// Quantit� d'ammo
		gCurrPuzzleStepMax = 12;
		gGrids.Make_Chain_Of_Walls({ 3,7 }, LEFT, 3);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 4,6 },RIGHT , 3);
		gGrids.Make_Chain_Of_Walls({ 4,3 }, UP, 3);
		gGrids.Make_Chain_Of_Walls({ 7,linkGrid->Get_Rows() - 4 }, DOWN, 3);
		break;

	case 1:Add_Spec(LEFT, 2); Add_Spec(RIGHT, 0);break;
	case 2:Add_Spec(LEFT, 1); Add_Spec(RIGHT, 1);break;
	case 3:Add_Spec(LEFT, 0); Add_Spec(RIGHT, 2);skip = 4;break;
	case 4:Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 1); Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() - 3);break;
	case 5:Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 2); Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() - 2);break;
	case 6:Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 3); Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() - 1);skip = 4;break;

	case 7:Add_Spec(DOWN, spawnGrid->Get_MaxSpwnCrdX() - 1); Add_Spec(DOWN, 2);break;
	case 8:Add_Spec(DOWN, spawnGrid->Get_MaxSpwnCrdX() - 2); Add_Spec(DOWN, 1);break;
	case 9:Add_Spec(DOWN, spawnGrid->Get_MaxSpwnCrdX() - 3); Add_Spec(DOWN, 0);break;
	case 10:Add_Spec(UP, 0); Add_Spec(UP, spawnGrid->Get_MaxSpwnCrdX() - 3);break;
	case 11:Add_Spec(UP, 1); Add_Spec(UP, spawnGrid->Get_MaxSpwnCrdX() - 2);break;
	case 12:Add_Spec(UP, 2); Add_Spec(UP, spawnGrid->Get_MaxSpwnCrdX() - 1);break;
	case 13:MsgQueue::Register(CHECKPOINT_REACHED); break;// CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}

// 2 long wall d'obstacle
void Puzzle_1_15()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 12,3 });				// Coord de d�part du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(33);// Quantit� d'ammo
		gCurrPuzzleStepMax = 12;
		gGrids.Make_Chain_Of_Walls({ 3,14 }, UP, 14);
		gGrids.Make_Chain_Of_Walls({ 9,0 }, DOWN, 14);
		gGrids.Make_Chain_Of_Walls({ 9,linkGrid->Get_Rows() - 1 }, LEFT,1);
		break;

	case 1:Add_Spec(RIGHT, 0);Add_Spec(RIGHT, 1); skip = 5;break;
	case 2:Add_Spec(RIGHT, 4);Add_Spec(RIGHT, 5);break;
	case 3:Add_Spec(UP, 9); Add_Spec(UP, 10); skip = 7; break;
	case 4:Add_Spec(RIGHT, 0);Add_Spec(RIGHT, 1); break;
	case 5:Add_Spec(UP, 9);Add_Spec(UP, 10);Add_Spec(UP, 11);skip = 2;break;
	case 6:Add_Spec(RIGHT, 0);skip = 2;break;
	case 7:Add(4);Set_Interval(DOWN, 4, 8); skip = 12;break;
	case 8:Add_Spec(UP, 0);Add_Spec(UP, 1); skip = 3;break;
	case 9:Add_Spec(LEFT, 13); skip = 4; break;
	case 10:Add_Spec(LEFT, 7);Add_Spec(LEFT, 8);skip = 6; break;
	case 11:Add_Spec(UP, 0);Add_Spec(UP, 1);Add_Spec(UP, 2);skip = 6;break;
	case 12:Add_Spec(LEFT, 13); skip = 12; break;
	case 13:Add(12);Set_Interval(UP, 0, linkGrid->Get_Cols() - 1); MsgQueue::Register(CHECKPOINT_REACHED); break;// CHECKPOINTHERE C
	}
}

// Super hard: mais diff�rent des autres, juste avant le FINAL HOUR 
// Static shoot dans tout les sens
// 1-12 LEFT/RIGHT
// 1-10	UP/DOWN 
void Puzzle_1_16()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 6,7 });				// Coord de d�part du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(42);	// Quantit� d'ammo
		gCurrPuzzleStepMax = 27;

		gGrids.Make_Chain_Of_Walls({ 6,1 }, UP, 1);
		gGrids.Make_Chain_Of_Walls({ 6,13 }, DOWN, 1);
		gGrids.Make_Chain_Of_Walls({ 1,7 }, LEFT, 1);
		gGrids.Make_Chain_Of_Walls({ 11,7 }, RIGHT, 1);
		break;

	case 1:Add_Spec(UP, 10);break;
	case 2:Add_Spec(LEFT, 1);break;
	case 3:Add_Spec(DOWN, 1);break;
	case 4:Add_Spec(RIGHT, 12);skip = 3;break;
	case 5:Add_Spec(UP, 10);break;
	case 6:Add_Spec(LEFT, 1);break;
	case 7:Add_Spec(DOWN, 1);break;
	case 8:Add_Spec(DOWN, 10);break;
	case 9:Add_Spec(RIGHT, 1);skip = 6;break;
	case 11:Add_Spec(UP, 1);break;
	case 12:Add_Spec(RIGHT, 12);break;
	case 13:Add_Spec(UP, 1);break;
	case 14:Add_Spec(UP, 10);break;
	case 15:Add_Spec(LEFT, 1);break;
	case 16:Add_Spec(LEFT, 1);skip = 6;break;
	case 17:Add_Spec(DOWN, 10);break;
	case 18:Add_Spec(LEFT, 12);break;
	case 19:Add_Spec(UP, 1);break;
	case 20:Add_Spec(LEFT, 12);break;
	case 21:Add_Spec(DOWN, 10);break;
	case 22:Add_Spec(RIGHT, 12);skip = 5; break;
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
	static std::string _1 = "- SURVIVE -";
	static std::string _2 = "Waves Remaining :";

	static Coord crd;
	static int y = 5; 

	const int SHAPES_TO_KILL = 40;
	static int shapesRemaining;

	if (gCurrPuzzleStep < 19) // Tout les spawns seront verticaux lors de la moiti� du final hour
		gHorizontalSpawns = true;

	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 6,7 });				// Coord de d�part du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(0);		// Quantit� d'ammo
		gCurrPuzzleStepMax = 12;
		shapesRemaining = SHAPES_TO_KILL;

		crd = { Find_Ctr_String_X(_1) - 1, 6 };

		if (!seenFinalHour)
		{
			MsgQueue::Register(LOCK_PLAYER);P1.Er_Player();
		}
		else
			Cancel_Checkpoint_Delay();
		break;

	case 1:
		if (!seenFinalHour)
		{
			MsgQueue::Register(FINAL_HOUR);	// montre �a juste une fois, EVER
			skip = 10;
		}
		break;



	case 2:

		if (P1.Cant_Do_Stuff())
			Set_Ev_Spawn_Player(3);

		gGrids.Make_Chain_Of_Walls({ 4,0 }, DOWN, linkGrid->Get_Rows() - 1);
		gGrids.Make_Chain_Of_Walls({ 8,0 }, DOWN, linkGrid->Get_Rows() - 1);
		gGrids.Make_Chain_Of_Walls({ 4,linkGrid->Get_Rows() - 1 }, LEFT, 1);	/*1*/
		gGrids.Make_Chain_Of_Walls({ 8,linkGrid->Get_Rows() - 1 }, RIGHT, 1);

		gGrids.Make_Chain_Of_Walls({ 3,1 }, DOWN, linkGrid->Get_Rows() - 3);
		gGrids.Make_Chain_Of_Walls({ 9,1 }, DOWN, linkGrid->Get_Rows() - 3);
		gGrids.Make_Chain_Of_Walls({ 3,linkGrid->Get_Rows() - 2 }, LEFT, 1);
		gGrids.Make_Chain_Of_Walls({ 9,linkGrid->Get_Rows() - 2 }, RIGHT, 1);

		gGrids.Make_Chain_Of_Walls({ 3,0 }, LEFT, 3);
		gGrids.Make_Chain_Of_Walls({ 0,1 }, RIGHT,  2);
		gGrids.Make_Chain_Of_Walls({ 0,2 }, RIGHT,  2);
		gGrids.Make_Chain_Of_Walls({ 0,3 }, RIGHT,  2);
		gGrids.Make_Chain_Of_Walls({ 0,4 }, RIGHT,  2);
		gGrids.Make_Chain_Of_Walls({ 0,4 }, RIGHT,  2);
		gGrids.Make_Chain_Of_Walls({ 0,5 }, RIGHT,  2);
		gGrids.Make_Chain_Of_Walls({ 0,6 }, RIGHT,  2);
		gGrids.Make_Chain_Of_Walls({ 0,7 }, RIGHT,  2);
		gGrids.Make_Chain_Of_Walls({ 0,8 }, RIGHT,  2);
		gGrids.Make_Chain_Of_Walls({ 0,9 }, RIGHT,  2);
		gGrids.Make_Chain_Of_Walls({ 0,10 }, RIGHT, 2);
		gGrids.Make_Chain_Of_Walls({ 0,11 }, RIGHT, 2);
		gGrids.Make_Chain_Of_Walls({ 0,12 }, RIGHT, 2);
		gGrids.Make_Chain_Of_Walls({ 1,13 }, LEFT, 1);
		gGrids.Make_Chain_Of_Walls({ 2,14 }, LEFT, 2);

		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 4,0 }, RIGHT,  3);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 1,1 }, LEFT,  2);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 1,2 }, LEFT,  2);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 1,3 }, LEFT,  2);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 1,4 }, LEFT,  2);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 1,4 }, LEFT,  2);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 1,5 }, LEFT,  2);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 1,6 }, LEFT,  2);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 1,7 }, LEFT,  2);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 1,8 }, LEFT,  2);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 1,9 }, LEFT,  2);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 1,10 }, LEFT, 2);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 1,11 }, LEFT, 2);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 1,12 }, LEFT, 2);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 2,13 }, RIGHT, 1);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 3,14 }, RIGHT, 2);



		ItemSpawner::Spawn_This_Item(ItemType::AMMO, { 6,3 });
		ItemSpawner::Spawn_This_Item(ItemType::AMMO, { 7,4 });
		ItemSpawner::Spawn_This_Item(ItemType::AMMO, { 5,4 });

		ItemSpawner::Spawn_This_Item(ItemType::AMMO, { 6,12 });
		ItemSpawner::Spawn_This_Item(ItemType::AMMO, { 5,11 });
		ItemSpawner::Spawn_This_Item(ItemType::AMMO, { 7,11 });

		if (!seenFinalHour)
		{
			seenFinalHour = true;
			skip = 10;
		}

		break;

	case 3:
		ConsoleRender::Add_String(_1, crd, BRIGHT_WHITE, TXT_SPD_DR);
		ConsoleRender::Add_String(_2, { crd.x - 5, crd.y + 1 }, WHITE, TXT_SPD_DR);
		ItemSpawner::Add_To_Pool(ItemType::AMMO, 200, 0);
		MsgQueue::Register(ENABLE_ITEM_SPAWN);
		skip = 8;
		break;

	case 4:Add(1);skip = 5;break;
	case 5:Add(1);skip = 5;break;
	case 6:Add(1);skip = 5;break;
	case 7:Add(1);skip = 5;break;
	case 8:Add(1);skip = 5;break;
	case 9:Add(1);skip = 5;break;
	case 10:Add(1);skip = 8;
		ItemSpawner::Spawn_This_Item(ItemType::AMMO, { 6,3 });
		ItemSpawner::Spawn_This_Item(ItemType::AMMO, { 7,4 });
		ItemSpawner::Spawn_This_Item(ItemType::AMMO, { 5,4 });

		ItemSpawner::Spawn_This_Item(ItemType::AMMO, { 6,12 });
		ItemSpawner::Spawn_This_Item(ItemType::AMMO, { 5,11 });
		ItemSpawner::Spawn_This_Item(ItemType::AMMO, { 7,11 });
		break;

	case 11:Add(1);skip = 2;break;
	case 12:Add(1);skip = 2;break;
	case 13:Add(1);skip = 2;break;
	case 14:Add(1);skip = 2;break;
	case 15:Add(1);skip = 1;break;
	case 16:Add(1);skip = 1;break;
	case 17:Add(1);skip = 1;break;
	case 18:Add(1);skip = 1;break;
	case 19:Add_Spec(LEFT, 0);Add_Spec(RIGHT, 0),

		skip = 16;break;
	case 20:
		for (int r = 0; r < 5; r++)
		{
			for (int c = 0; c < 5; c++)
			{
				ItemSpawner::Spawn_This_Item(ItemType::AMMO, { 4 + c, 9 + r });
			}
		}
		skip = 16;
		break;

	case 21:Add(1);skip = 5;break;
	case 22:Add(1);skip = 5;break;
	case 23:Add(1);skip = 5;break;
	case 24:Add(1);skip = 3;break;
	case 25:Add(1);skip = 2;break;
	case 26:Add(1);skip = 2;break;
	case 27:Add(1);skip = 2;break;
	case 28:Add(1);skip = 2;break;
	case 29:Add(1);skip = 2;break;
	case 30:Add(1);skip = 2;break;
	case 31:Add(1);skip = 7;break;
	case 32:Add(1);skip = 3;break;
	case 33:Add(1);skip = 3;break;
	case 34:Add(1);skip = 3;break;
	case 35:Add(1);skip = 3;break;
	case 36:Add(1);skip = 3;break;
	case 37:Add(1);skip = 3;break;
	case 38:Add(1);skip = 2;break;
	case 39:Add(1);skip = 2;break;
	case 40:Add(1);skip = 0;break;
	case 41:Add(1);skip = 0;break;
	case 42:Add(1);skip = 0;break;
	case 43:
		// VICTORY IS OURS HAHAHAHAHAHAH
		MsgQueue::Register(STOP_BOT_SPAWNS);
		Ev_Wait_For_Victory(); 
		break;
	}

	if (gCurrPuzzleStep > 2)
	{
		if (shapesRemaining == 9)
			ConsoleRender::Add_String(TXT_CONST.SPACE_STRING, { crd.x + 14,crd.y + 1 }, LIGHT_AQUA, TXT_SPD_DR);

		ConsoleRender::Add_String(std::to_string(shapesRemaining), { crd.x + 13,crd.y + 1 }, LIGHT_AQUA, TXT_SPD_DR);
		shapesRemaining--;

		if (gCurrPuzzleStep < 19)
		{
			Set_Interval(UP, 4, 8);
		}
		else
			Set_Interval(UP, 3, 9);
	}
}
