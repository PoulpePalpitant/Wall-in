

#include "lvl_2_spwn_script.h"
#include "../../time/spawn_cycle.h"
#include "../../grid/managegrids.h"
#include "../../spawns/bots_to_spawn.h"
#include "../../events/msg_dispatcher.h"
#include "../lvl_script.h"

#include "../../player/player.h"

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

static bool seenFinalHour = false;
static int skip;

// Puzzles du lvl1:
void Puzzle_2_0();
void Puzzle_2_1();
void Puzzle_2_2();
void Puzzle_2_3();
void Puzzle_2_4();
void Puzzle_2_5();
void Puzzle_2_6();
void Puzzle_2_7();
void Puzzle_2_8();
void Puzzle_2_9();
void Puzzle_2_10();
void Puzzle_2_11();
void Puzzle_2_12();
void Puzzle_2_13();
void Puzzle_2_14();
void Puzzle_2_15();
void Puzzle_2_16();
void Puzzle_2_17();
void Puzzle_2_18();
void Puzzle_2_19();
void Puzzle_2_FINAL();


// VOICI  l'ordre dans lequel sera joué les puzzles
void (*LVL2_PUZZLES[])() = {	// definition 
Puzzle_2_0,
Puzzle_2_1,
Puzzle_2_2,
Puzzle_2_3,
Puzzle_2_4,
Puzzle_2_5,
Puzzle_2_6,
Puzzle_2_7,
Puzzle_2_8,
Puzzle_2_9,
Puzzle_2_10,
Puzzle_2_11,
Puzzle_2_12,
Puzzle_2_13,
Puzzle_2_14,
Puzzle_2_15,
Puzzle_2_16,
Puzzle_2_17,
Puzzle_2_18,
Puzzle_2_19,
Puzzle_2_FINAL
};





void Lvl_2_Spwn_Script()	// HERE WE GO AGAIN
{
	if (gSpawnThisCycle)
	{
		skip = 0;		

		LVL2_PUZZLES[gCurrentPuzzle[gCurrentLevel - 1]]();	// Script du puzzle
		gCurrPuzzleStep++;	// Prochain step du puzzle!

		if (skip)
			gSpwBotTimer.Add_Count(skip);
	}
}

//void Puzzle_2_0(){
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


// Tuto blocker
void Puzzle_2_0()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 6,6 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(3);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;

		gGrids.Make_Box_Of_Blockers({ 0 + 4 , 0 }, { linkGrid->Get_Cols() - 1 - 4 , linkGrid->Get_Rows() - 1 });
		gGrids.Activate_Blocker({ 6, 2 });
		Set_Dr_Map_1(TXT_SPD_DR * 4);  // Erase la border au cas où le joueur est pas en mode quickstartS

		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 5 , 1 }, false, true);
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 6 , 1 }, false, true);
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 7 , 1 }, false, true);
		break;


	case 1:skip = 8;break;
	case 2:
		Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 1);
		Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 2);
		Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 3);
		break;

	case 3:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}


// Place them correctly you fool!
void Puzzle_2_1()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 5,7 });			// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(6);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;

		gGrids.Make_Box_Of_Blockers({ 3 + 1, 4 }, { linkGrid->Get_Cols() - 4, linkGrid->Get_Rows() - 5 });

		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 6 , 6 }, false);
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 6 ,7 }, false);
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 6, 8 }, false);

		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 7 ,6 }, false);
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 7,7 }, false);
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 7 ,8 }, false);
		break;


	case 1:Add_Spec(RIGHT, 7);skip = 4;break;
	case 2:Add_Spec(RIGHT, 9);skip = 2;break;
	case 3:Add_Spec(UP, 6);skip = 3;break;
	case 4:Add_Spec(UP, 8); skip = 2;break;
	case 5:Add_Spec(DOWN, 6); skip = 1;break;
	case 6:Add_Spec(LEFT, 9);skip = 1;break;
	case 7:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}



// Regular links can be converted to BLOCKER
void Puzzle_2_2()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 6,7 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(6);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;

		// Couloir principal au milieu
		for (int i = 0; i < linkGrid->Get_Cols(); i++)
		{
			gGrids.Activate_Blocker({ i, 6 });

			if (i != 6)
				gGrids.Activate_Blocker({ i, 8 });
		}

		gGrids.Activate_Link({ 0,7 });	// Link ordinaire à gauche
		gGrids.Activate_Blocker({ linkGrid->Get_Cols() - 1, 7 });	// Blocker à droite

		// Couloir vide au milieu
		for (int i = 9; i < 11; i++)
		{
			gGrids.Activate_Blocker({ 5, i });
			gGrids.Activate_Blocker({ 7, i });
		}

		gGrids.Activate_Blocker({ 6, 10 });	// Scelle le couloir


		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 3 ,7 }, false);
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 4 ,7 }, false);

		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 8 ,7 }, false);
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 9 ,7 }, false);
		break;


	case 1:Add_Spec(UP, 1);Add_Spec(UP, 0);skip = 8;break;
	case 2:Add_Spec(DOWN, 10);Add_Spec(DOWN, 11);Add_Spec(LEFT, 8);Add_Spec(LEFT, 9);skip = 5;break;
	case 3:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}



// Labyrinthe à détruire
void Puzzle_2_3()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 2,12 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(5);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;

		gGrids.Make_Chain_Of_Walls({ 10,0 }, DOWN, linkGrid->Get_Rows() - 1);
		gGrids.Make_Chain_Of_Walls({ 10,linkGrid->Get_Rows() - 1 }, RIGHT, 1);
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 0 ,11 }, false);

		gGrids.Make_Chain_Of_Walls({ 0,10 }, RIGHT, 3);
		gGrids.Make_Chain_Of_Walls({ 3,10 }, DOWN, 3);
		gGrids.Make_Chain_Of_Walls({ 3,13 }, LEFT, 3);
		gGrids.Make_Chain_Of_Walls({ 0,13 }, DOWN, 1);
		gGrids.Make_Chain_Of_Walls({ 0,14 }, RIGHT, 3);
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 3 ,9 }, false);

		gGrids.Make_Chain_Of_Walls({ 4,9 }, UP, 1);
		gGrids.Make_Chain_Of_Walls({ 4,8 }, LEFT, 2);
		gGrids.Make_Chain_Of_Walls({ 2,8 }, DOWN, 1);
		gGrids.Make_Chain_Of_Walls({ 2,9 }, LEFT, 2);
		gGrids.Make_Chain_Of_Walls({ 0,9 }, UP, 1);
		gGrids.Make_Chain_Of_Walls({ 0,8 }, RIGHT, 1);
		gGrids.Make_Chain_Of_Walls({ 4,9 }, DOWN, 5);
		gGrids.Make_Chain_Of_Walls({ 4,14 }, RIGHT, 2);
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 5 ,12 }, false);

		gGrids.Make_Chain_Of_Walls({ 5,13 }, RIGHT, 1);
		gGrids.Make_Chain_Of_Walls({ 6,13 }, UP, 4);
		gGrids.Make_Chain_Of_Walls({ 6,9 }, RIGHT, 1);
		gGrids.Make_Chain_Of_Walls({ 7,9 }, DOWN, 5);
		gGrids.Make_Chain_Of_Walls({ 7,14 }, RIGHT, 1);
		gGrids.Make_Chain_Of_Walls({ 8,14 }, UP, 5);
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 9 ,14 }, false);


		gGrids.Make_Chain_Of_Walls({ 5,11 }, UP, 4);
		gGrids.Make_Chain_Of_Walls({ 5,7 }, LEFT, 5);
		gGrids.Make_Chain_Of_Walls({ 0,7 }, UP, 1);
		gGrids.Make_Chain_Of_Walls({ 0,6 }, RIGHT, 5);
		gGrids.Make_Chain_Of_Walls({ 5,6 }, UP, 1);
		gGrids.Make_Chain_Of_Walls({ 5,5 }, LEFT, 5);
		gGrids.Make_Chain_Of_Walls({ 0,5 }, UP, 1);
		gGrids.Make_Chain_Of_Walls({ 0,4 }, RIGHT, 5);
		gGrids.Make_Chain_Of_Walls({ 5,4 }, UP, 1);
		gGrids.Make_Chain_Of_Walls({ 5,3 }, LEFT, 5);
		gGrids.Make_Chain_Of_Walls({ 0,3 }, UP, 1);
		gGrids.Make_Chain_Of_Walls({ 0,2 }, RIGHT, 5);
		gGrids.Make_Chain_Of_Walls({ 5,2 }, UP, 1);
		gGrids.Make_Chain_Of_Walls({ 5,1 }, LEFT, 5);
		gGrids.Make_Chain_Of_Walls({ 0,1 }, UP, 1);
		gGrids.Make_Chain_Of_Walls({ 0,0 }, RIGHT, 4);
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 5 ,0 }, false);
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 6 ,0 }, false);

		gGrids.Make_Chain_Of_Walls({ 7,0 }, DOWN, 1);
		gGrids.Make_Chain_Of_Walls({ 7,1 }, LEFT, 1);
		gGrids.Make_Chain_Of_Walls({ 6,1 }, DOWN, 7);
		gGrids.Make_Chain_Of_Walls({ 6,8 }, RIGHT, 2);


		gGrids.Make_Chain_Of_Walls({ 9,13 }, UP, 6);
		gGrids.Make_Chain_Of_Walls({ 9,7 }, LEFT, 2);
		gGrids.Make_Chain_Of_Walls({ 7,7 }, UP, 5);

		gGrids.Make_Chain_Of_Walls({ 8,0 }, DOWN, 6);
		gGrids.Make_Chain_Of_Walls({ 8,6 }, RIGHT, 1);
		gGrids.Make_Chain_Of_Walls({ 9,6 }, UP, 5);
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 9 ,0 }, false);
		break;


	case 1:skip = 35;break;
	case 2:Add_Spec(UP, 11);break;
	case 3:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}


void Puzzle_2_4()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 6,8 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(10);	// Quantité d'ammo
		gCurrPuzzleStepMax = 12;


		for (int r = 7; r <= linkGrid->Get_Rows() - 6; r++)
			for (int c = 4; c <= linkGrid->Get_Cols() - 5; c++)
			{
				if (!(r < 9 && c == 6))
					ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { c, r }, true);
			}

		gGrids.Make_Box_Of_Blockers({ 3, 6 }, { linkGrid->Get_Cols() - 4, linkGrid->Get_Rows() - 5 });
		gGrids.Activate_Link({ 6, 6 }, Modifier::REGULAR, 1);
		gGrids.Make_Chain_Of_Walls({ 6, 7 }, UP, 7);
		break;

	case 1:Add(2); Set_Interval(RIGHT, 7, 9);skip = 10;break;
	case 2:Add(2); Set_Interval(UP, 4, 6);   skip = 10;break;
	case 3:Add(2); Set_Interval(UP, 6, 8); skip = 4;break;
	case 4:Add(7);Set_Interval(RIGHT, 0, 7); skip = 9;break;
	case 5:Add_Spec(LEFT, 7);/*Add_Spec(RIGHT, 6);*/Add_Spec(DOWN, 5);Add_Spec(UP, 6); skip = 6;break;
	case 6:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}



// Show what the buffer does
void Puzzle_2_5()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 8,1 });				
		blastP1.Get_Ammo_Manager().Set_Ammo(1);	
		gCurrPuzzleStepMax = 12;
		
		gGrids.Make_Box_Of_Blockers({ 3, 0}, { 9, 6 });

		for (int i = 5; i < 9; i++)
			gGrids.Activate_Blocker({ i, 2 });

		for (int i = 4; i < 8; i++)
			gGrids.Activate_Blocker({ i, 4 });

		for (int i = 6; i < linkGrid->Get_Rows(); i++)
			gGrids.Activate_Blocker({ 5, i });

		for (int i = 6; i < linkGrid->Get_Rows() ; i++)
			gGrids.Activate_Blocker({ 7, i });



		//for (int i = 1; i < linkGrid->Get_Rows() - 1; i++)
		//{
		//	gGrids.Activate_Blocker({ 4, i }, 0);
		//	gGrids.Activate_Blocker({ 8, i }, 0);
		//}

		

		gGrids.Activate_Link({ 6,6}, Modifier::REGULAR, true);
		gGrids.Activate_Link({ 9,7 }, Modifier::REGULAR, true);

		gGrids.Make_Chain_Of_Walls({ 6,9 }, DOWN, 5);
		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 6 , 7 });
		break;


	case 1:skip = 20;break;
	case 2:Add(10);Set_Interval(LEFT, 9, 14);
		Set_Interval(RIGHT, 9, 14);	break;
	case 3:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}

// 1st buffer practice
void Puzzle_2_6()
{
	switch (gCurrPuzzleStep)
	{
	case 0:
		P1.Set_Position({ 6, 6 });				// Coord de départ du jouer
		P1.Reset_Hp_And_Heart(3);
		blastP1.Get_Ammo_Manager().Set_Ammo(4);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;

		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 6 , 5 });
		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 6 , 7 });
		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 5 , 6 });
		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 7 , 6 });


		gGrids.Make_Chain_Of_Walls({ 2,3 }, LEFT, 1);
		gGrids.Make_Chain_Of_Walls({ 10,5 }, UP, 1);
		gGrids.Make_Chain_Of_Walls({ 8,9 }, DOWN, 1);
		gGrids.Make_Chain_Of_Walls({ 4,7 }, RIGHT, 1);
		break;


	case 1:skip = 8; break;
	case 2:
		Add_Spec(UP, 1);
		Add_Spec(DOWN, 1);
		Add_Spec(LEFT, 4);
		Add_Spec(RIGHT, 4);
		Add_Spec(UP, 4);
		Add_Spec(DOWN, 4);
		Add_Spec(LEFT, 9);
		Add_Spec(RIGHT, 9);
	case 3:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}

void Puzzle_2_7()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 6,8 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(8);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;

		gGrids.Activate_Link({ 6,6 }, Modifier::BUFFER);
		break;


	case 1:Add_Spec(UP, 0);Add_Spec(UP, spawnGrid->Get_MaxSpwnCrdX() - 1);break;
	case 2:Add_Spec(UP, 0);Add_Spec(UP, spawnGrid->Get_MaxSpwnCrdX() - 1);skip = 4;break;
	case 3:Add_Spec(UP, 0);Add_Spec(UP, spawnGrid->Get_MaxSpwnCrdX() - 1);break;
	case 4:Add_Spec(UP, 0);Add_Spec(UP, spawnGrid->Get_MaxSpwnCrdX() - 1);skip = 3;break;
	case 5:Add_Spec(UP, 0);Add_Spec(UP, spawnGrid->Get_MaxSpwnCrdX() - 1);break;
	case 6:Add_Spec(UP, 0);Add_Spec(UP, spawnGrid->Get_MaxSpwnCrdX() - 1);skip = 1;break;
	case 7:Add_Spec(UP, 0);Add_Spec(UP, spawnGrid->Get_MaxSpwnCrdX() - 1);break;
	case 8:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}

// Show that you can shoot the buffers
void Puzzle_2_8()
{
	GrdCoord crd = P1.Get_Grd_Coord();

	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 6,7 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(8);// Quantité d'ammo
		gCurrPuzzleStepMax = 1;

		//gGrids.Make_Box_Of_Blockers({ 0, 0 }, { linkGrid->Get_Cols() - 1, linkGrid->Get_Rows() - 1 });
		gGrids.Activate_Link({ 5,6 }, Modifier::BUFFER);
		gGrids.Activate_Link({ 7,8 }, Modifier::BUFFER);
		break;


	case 1:
		Add_Spec(UP, 6); Add_Spec(DOWN, 6);	skip = 3;break;
	case 2:Add_Spec(UP, 4); Add_Spec(DOWN, 4);skip = 3;break;
	case 3:Add_Spec(LEFT, 5); Add_Spec(RIGHT, 5);skip = 2;break;
	case 4:Add_Spec(LEFT, 7); Add_Spec(RIGHT, 7);skip = 2;break;
	case 5:Add_Spec(UP, 5); Add_Spec(DOWN, 5);	skip = 2;break;
	case 6:Add_Spec(UP, 7); Add_Spec(DOWN, 7);	skip = 1;break;
	case 7:Add_Spec(LEFT, 8); Add_Spec(RIGHT, 8);skip = 1;break;
	case 8:Add_Spec(LEFT, 6); Add_Spec(RIGHT, 6);skip = 1;break;
	case 9:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}

// Montre qu'on peut grab les items avec transfer. Montre aussi qu'est-ce que ça fait quand on tir sur une border
void Puzzle_2_9()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 0 ,7 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(0);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;

		gGrids.Make_Chain_Of_Walls({ 12,7 }, LEFT, 10);


		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 2 , 3 });
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 2 , linkGrid->Get_Rows() - 4 });


		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 3 , linkGrid->Get_Rows() - 4 });
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 3 , 3 });


		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 4 , 3 });
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 4 , linkGrid->Get_Rows() - 4 });


		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 5 , linkGrid->Get_Rows() - 4 });
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 5 , 3 });


		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 6 , 3 });
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 6 , linkGrid->Get_Rows() - 4 });


		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 7 , linkGrid->Get_Rows() - 4 });
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, {7 , 3 });


		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 8 , 3 });
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 8 , linkGrid->Get_Rows() - 4 });


		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 9 , 3 });
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 9 , linkGrid->Get_Rows() - 4 });


		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 10 , linkGrid->Get_Rows() - 4 });
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 10 , 3 });

		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 11 , linkGrid->Get_Rows() - 4 });
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 11 , 3 });
		break;


	case 1:Add_Spec(LEFT, 0);Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 1);skip = 0;break;
	case 2:Add_Spec(LEFT, 0);Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY()- 1); skip = 0;break;
	case 3:Add_Spec(LEFT, 0);Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY()- 1); skip = 0;break;
	case 4:Add_Spec(LEFT, 0);Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY()- 1); skip = 0;break;
	case 5:Add_Spec(LEFT, 0);Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY()- 1); skip = 0;break;
	case 6:Add_Spec(LEFT, 0);Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY()- 1); skip = 0;break;
	case 7:Add_Spec(LEFT, 0);Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY()- 1); skip = 0;break;
	case 8:Add_Spec(LEFT, 0);Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY()- 1); skip = 0;break;
	case 9:Add_Spec(LEFT, 0);Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY()- 1); skip = 3;break;
	case 11:Add_Spec(RIGHT, 0);Add_Spec(RIGHT,spawnGrid->Get_MaxSpwnCrdY() -1); skip = 0;break;
	case 12:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}

void Puzzle_2_10()
{
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
}

// Alternance entre buff et blocker. Bie regarder la queue à gauche
void Puzzle_2_11()
{
	GrdCoord crd = { 1,1 };

	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position(crd);				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(11);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;

		gGrids.Activate_Blocker({ crd.c- 1,crd.r });

		for (int c = crd.c - 1; c < crd.c + 6; c++)
			gGrids.Activate_Blocker({ c,crd.r - 1 });


		for (int c = crd.c - 1; c < crd.c + 4; c++)
			gGrids.Activate_Blocker({ c,crd.r + 1 });


		for (int r = 0; r < linkGrid->Get_Rows(); r++)
			gGrids.Activate_Blocker({ crd.c + 6 ,r });


		for (int r = 2; r < linkGrid->Get_Rows(); r++)
			gGrids.Activate_Blocker({ crd.c + 4,r });

		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { crd.c + 5 -4,1 });
		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { crd.c + 5 -3,1 });
		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { crd.c + 5 -2,1 });
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { crd.c + 5 -1,1 });
		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, {  crd.c + 5,1 });
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { crd.c + 5,2 });
		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, {  crd.c + 5,3 });
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { crd.c + 5,4 });
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { crd.c + 5,5 });
		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, {  crd.c + 5,6 });

		gGrids.Make_Chain_Of_Walls({ crd.c + 5, 13 }, UP, 3);	// Mur que le joueurs va tirés avec les items
		break;


	case 1:
		Add_Spec(LEFT,  7 + 2);
		Add_Spec(RIGHT, 7 + 2);
		Add_Spec(RIGHT, 8 + 2);
		skip = 7;
		break;

	case 2:
		Add_Spec(LEFT,  8 + 2);
		Add_Spec(RIGHT, 8 + 2);
		Add_Spec(RIGHT, 9 + 2);
		skip = 7;
		break;

	case 4:		
		Add(5);Set_Interval(DOWN, 0, 5);
		skip = 6;
		break;

	case 3:
		Add_Spec(LEFT, 9 + 2);
		Add_Spec(RIGHT, 9 + 2);
		Add_Spec(RIGHT, 10 + 2);
		skip = 4;
		break;

	case 5:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}


// Double STRONG walls transfer!
void Puzzle_2_12()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 11,7 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(0);	// Quantité d'ammo
		gCurrPuzzleStepMax = 12;

		// Couloir principal au milieu
		for (int i = 0; i < 13; i++)
		{
			if (i > 0 && i < 8)
				gGrids.Activate_Link({ i,5 }, Modifier::REGULAR);

			gGrids.Activate_Blocker({ i, 4 });
			gGrids.Activate_Blocker({ i, 8 });
		}

		gGrids.Activate_Blocker({ 0, 5 });
		gGrids.Activate_Blocker({ 12, 5});
		gGrids.Activate_Blocker({ 0, 6 });
		gGrids.Activate_Blocker({ linkGrid->Get_Cols() - 1, 7 });

		gGrids.Activate_Link({ 0,7 }, Modifier::BUFFER);
		gGrids.Make_Chain_Of_Walls({ 0, 7 }, RIGHT, 7, WallStrength::STRONG);
		break;

	case 1:Add_Spec(RIGHT, 5);break;	// Ajoute un skip = 1 ici si c'est trop hard //skip = 1;
	case 2:Add_Spec(RIGHT, 5);break;												 //skip = 1;
	case 3:Add_Spec(RIGHT, 5);break;												 //skip = 1;
	case 4:Add_Spec(RIGHT, 5);break;												 //skip = 1;
	case 5:Add_Spec(RIGHT, 5);break;												 //skip = 1;
	case 6:Add_Spec(RIGHT, 5);break;												 //skip = 1;
	case 7:Add_Spec(RIGHT, 5); skip = 15;break;
	case 8:Add(7); Set_Interval(UP, 5, 12);break;
	case 9:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}

void Puzzle_2_13()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 6,7 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(14);	// Quantité d'ammo
		gCurrPuzzleStepMax = 12;

		// Couloir principal au milieu
		for (int i = 2; i < linkGrid->Get_Cols() - 2; i++)
		{
			if (i != 6)
			{
				gGrids.Activate_Blocker({ i, 6 });
				gGrids.Activate_Blocker({ i, 8 });
			}
		}

		gGrids.Activate_Link({ 3,7 }, Modifier::REGULAR);
		gGrids.Activate_Link({ 2,7 }, Modifier::BLOCKER);
		gGrids.Activate_Link({ linkGrid->Get_Cols() - 4, 7 });
		gGrids.Activate_Link({ linkGrid->Get_Cols() - 3, 7 }, Modifier::BLOCKER);

		// Couloir vide en bas 
		for (int i = 9; i < 14; i++)
		{
			gGrids.Activate_Blocker({ 5, i });
			gGrids.Activate_Blocker({ 7, i });
		}

		gGrids.Activate_Link({ 6, 13 }, Modifier::REGULAR);

		// Couloir vide en haut
		for (int i = 5; i > 1; i--)
		{
			gGrids.Activate_Blocker({ 5, i });
			gGrids.Activate_Blocker({ 7, i });
		}

		gGrids.Activate_Link({ 6, 3 }, Modifier::REGULAR);	// Scelle le couloir
		gGrids.Activate_Link({ 6, 2 }, Modifier::BLOCKER);	// Scelle le couloir
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 6 ,5 }, false);
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 6, 6 }, false);

		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 6, 8 }, false);
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 6, 9 }, false);
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 6, 10 }, false);
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 6, 11 }, false);
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 6, 12 }, false);
		break;


	case 1:skip = 0;break;
	case 2:
		Add(2); Set_Interval(UP, 3, 5);
		Add(2); Set_Interval(DOWN, 7, 9);
		skip = 6;
		break;
	case 3:Add(3); Set_Interval(RIGHT, 3, 6);skip = 6;break;
	case 4:Add_Spec(DOWN, 2);Add_Spec(DOWN, 9);Add_Spec(RIGHT, 2);skip = 8;break;
	case 5:Add(3); Set_Interval(LEFT, 10, 13);skip = 8;break;
	case 6:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}



void Puzzle_2_14()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 6,6 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(16);	// Quantité d'ammo
		gCurrPuzzleStepMax = 12;



		for (int r = 6; r <= linkGrid->Get_Rows() - 5; r++)
			for (int c = 3; c <= linkGrid->Get_Cols() - 4; c++)
			{
				if (!(c == 6 && r == 6))
						if (!(c == 9 && r == 10))
						ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { c, r }, true);
			}
		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 9, 10 });

		for (short i = 0; i < 5; i++)
		{
			gGrids.Activate_Link({ 5, i }, Modifier::BLOCKER);
			gGrids.Activate_Link({ 7, i }, Modifier::BLOCKER);
		}
		gGrids.Activate_Link({ 6, 0 }, Modifier::BLOCKER);



		gGrids.Make_Box_Of_Blockers({ 2, 5 }, { linkGrid->Get_Cols() - 3, linkGrid->Get_Rows() - 4 });
		gGrids.Make_Chain_Of_Walls({ 6, 2 }, UP, 1);
		gGrids.Activate_Link({6, 5 }, Modifier::REGULAR,1);
		break;

	case 1:Add(4);Set_Interval(DOWN, 6, 10);skip = 10;break;
	case 2:Add_Spec(RIGHT, 2);skip = 3;break;
	case 3:Add(4);Set_Interval(DOWN, 2, 6);skip = 5;break;
	case 4:Add_Spec(RIGHT, 2);skip = 3;break;
	case 5:Add(2);Set_Interval(RIGHT, 5, 7);skip = 5;break;
	case 6:Add_Spec(RIGHT, 2);skip = 5;break;
	case 7:Add(3);Set_Interval(DOWN, 2, 5);skip = 5;break;
	case 8:Add_Spec(RIGHT, 2);skip = 5;break;
	case 9:Add_Spec(RIGHT, 1);Add_Spec(LEFT, 1);break;
	case 10:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}

void Puzzle_2_15()
{
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
}
void Puzzle_2_16()
{
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
}
void Puzzle_2_17()
{
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
}
void Puzzle_2_18(){
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
}
void Puzzle_2_19(){
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
}
void Puzzle_2_FINAL()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 6,6 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(10);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;
		for (int i = 0; i < linkGrid->Get_Cols(); i++)
		{
			gGrids.Activate_Blocker({ i, 0 }, 0);
			gGrids.Activate_Blocker({ i, 14 }, 0);
		}

		for (int i = 1; i < linkGrid->Get_Rows() - 1; i++)
		{
			gGrids.Activate_Blocker({ 0, i }, 0);
			gGrids.Activate_Blocker({ linkGrid->Get_Cols() - 1, i }, 0);
		}

		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 6 , 3 });
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 5 , 3 });
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 7 , 3 });
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
}







// Copy-paste that shit when you make lvl 3 :)
//
//void Puzzle_2_2()
//{
//	switch (gCurrPuzzleStep)
//	{
//	case 0:P1.Set_Position({ 6,6 });				// Coord de départ du jouer
//		blastP1.Get_Ammo_Manager().Set_Ammo(10);// Quantité d'ammo
//		gCurrPuzzleStepMax = 12;
//		break;
//
//
//	case 1:
//	case 2:
//	case 3:
//	case 4:
//	case 5:
//	case 6:
//	case 7:
//	case 8:
//	case 9:
//	case 11:
//	case 12:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
//	}
//}
//void Puzzle_2_3()
//{
//	switch (gCurrPuzzleStep)
//	{
//	case 0:P1.Set_Position({ 6,6 });				// Coord de départ du jouer
//		blastP1.Get_Ammo_Manager().Set_Ammo(10);// Quantité d'ammo
//		gCurrPuzzleStepMax = 12;
//		break;
//
//
//	case 1:
//	case 2:
//	case 3:
//	case 4:
//	case 5:
//	case 6:
//	case 7:
//	case 8:
//	case 9:
//	case 11:
//	case 12:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
//	}
//}
//void Puzzle_2_4()
//{
//	switch (gCurrPuzzleStep)
//	{
//	case 0:P1.Set_Position({ 6,6 });				// Coord de départ du jouer
//		blastP1.Get_Ammo_Manager().Set_Ammo(10);// Quantité d'ammo
//		gCurrPuzzleStepMax = 12;
//		break;
//
//
//	case 1:
//	case 2:
//	case 3:
//	case 4:
//	case 5:
//	case 6:
//	case 7:
//	case 8:
//	case 9:
//	case 11:
//	case 12:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
//	}
//}
//void Puzzle_2_5()
//{
//	switch (gCurrPuzzleStep)
//	{
//	case 0:P1.Set_Position({ 6,6 });				// Coord de départ du jouer
//		blastP1.Get_Ammo_Manager().Set_Ammo(10);// Quantité d'ammo
//		gCurrPuzzleStepMax = 12;
//		break;
//
//
//	case 1:
//	case 2:
//	case 3:
//	case 4:
//	case 5:
//	case 6:
//	case 7:
//	case 8:
//	case 9:
//	case 11:
//	case 12:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
//	}
//}
//void Puzzle_2_6()
//{
//	switch (gCurrPuzzleStep)
//	{
//	case 0:P1.Set_Position({ 6,6 });				// Coord de départ du jouer
//		blastP1.Get_Ammo_Manager().Set_Ammo(10);// Quantité d'ammo
//		gCurrPuzzleStepMax = 12;
//		break;
//
//
//	case 1:
//	case 2:
//	case 3:
//	case 4:
//	case 5:
//	case 6:
//	case 7:
//	case 8:
//	case 9:
//	case 11:
//	case 12:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
//	}
//}
//void Puzzle_2_7()
//{
//	switch (gCurrPuzzleStep)
//	{
//	case 0:P1.Set_Position({ 6,6 });				// Coord de départ du jouer
//		blastP1.Get_Ammo_Manager().Set_Ammo(10);// Quantité d'ammo
//		gCurrPuzzleStepMax = 12;
//		break;
//
//
//	case 1:
//	case 2:
//	case 3:
//	case 4:
//	case 5:
//	case 6:
//	case 7:
//	case 8:
//	case 9:
//	case 11:
//	case 12:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
//	}
//}
//void Puzzle_2_8()
//{
//	switch (gCurrPuzzleStep)
//	{
//	case 0:P1.Set_Position({ 6,6 });				// Coord de départ du jouer
//		blastP1.Get_Ammo_Manager().Set_Ammo(10);// Quantité d'ammo
//		gCurrPuzzleStepMax = 12;
//		break;
//
//
//	case 1:
//	case 2:
//	case 3:
//	case 4:
//	case 5:
//	case 6:
//	case 7:
//	case 8:
//	case 9:
//	case 11:
//	case 12:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
//	}
//}
//void Puzzle_2_9()
//{
//	switch (gCurrPuzzleStep)
//	{
//	case 0:P1.Set_Position({ 6,6 });				// Coord de départ du jouer
//		blastP1.Get_Ammo_Manager().Set_Ammo(10);// Quantité d'ammo
//		gCurrPuzzleStepMax = 12;
//		break;
//
//
//	case 1:
//	case 2:
//	case 3:
//	case 4:
//	case 5:
//	case 6:
//	case 7:
//	case 8:
//	case 9:
//	case 11:
//	case 12:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
//	}
//}
//void Puzzle_2_10()
//{
//	switch (gCurrPuzzleStep)
//	{
//	case 0:P1.Set_Position({ 6,6 });				// Coord de départ du jouer
//		blastP1.Get_Ammo_Manager().Set_Ammo(10);// Quantité d'ammo
//		gCurrPuzzleStepMax = 12;
//		break;
//
//
//	case 1:
//	case 2:
//	case 3:
//	case 4:
//	case 5:
//	case 6:
//	case 7:
//	case 8:
//	case 9:
//	case 11:
//	case 12:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
//	}
//}
//void Puzzle_2_11()
//{
//	switch (gCurrPuzzleStep)
//	{
//	case 0:P1.Set_Position({ 6,6 });				// Coord de départ du jouer
//		blastP1.Get_Ammo_Manager().Set_Ammo(10);// Quantité d'ammo
//		gCurrPuzzleStepMax = 12;
//		break;
//
//
//	case 1:
//	case 2:
//	case 3:
//	case 4:
//	case 5:
//	case 6:
//	case 7:
//	case 8:
//	case 9:
//	case 11:
//	case 12:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
//	}
//}
//void Puzzle_2_12()
//{
//	switch (gCurrPuzzleStep)
//	{
//	case 0:P1.Set_Position({ 6,6 });				// Coord de départ du jouer
//		blastP1.Get_Ammo_Manager().Set_Ammo(10);// Quantité d'ammo
//		gCurrPuzzleStepMax = 12;
//		break;
//
//
//	case 1:
//	case 2:
//	case 3:
//	case 4:
//	case 5:
//	case 6:
//	case 7:
//	case 8:
//	case 9:
//	case 11:
//	case 12:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
//	}
//}
//void Puzzle_2_13()
//{
//	switch (gCurrPuzzleStep)
//	{
//	case 0:P1.Set_Position({ 6,6 });				// Coord de départ du jouer
//		blastP1.Get_Ammo_Manager().Set_Ammo(10);// Quantité d'ammo
//		gCurrPuzzleStepMax = 12;
//		break;
//
//
//	case 1:
//	case 2:
//	case 3:
//	case 4:
//	case 5:
//	case 6:
//	case 7:
//	case 8:
//	case 9:
//	case 11:
//	case 12:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
//	}
//}
//void Puzzle_2_14()
//{
//	switch (gCurrPuzzleStep)
//	{
//	case 0:P1.Set_Position({ 6,6 });				// Coord de départ du jouer
//		blastP1.Get_Ammo_Manager().Set_Ammo(10);// Quantité d'ammo
//		gCurrPuzzleStepMax = 12;
//		break;
//
//
//	case 1:
//	case 2:
//	case 3:
//	case 4:
//	case 5:
//	case 6:
//	case 7:
//	case 8:
//	case 9:
//	case 11:
//	case 12:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
//	}
//}
//void Puzzle_2_15()
//{
//	switch (gCurrPuzzleStep)
//	{
//	case 0:P1.Set_Position({ 6,6 });				// Coord de départ du jouer
//		blastP1.Get_Ammo_Manager().Set_Ammo(10);// Quantité d'ammo
//		gCurrPuzzleStepMax = 12;
//		break;
//
//
//	case 1:
//	case 2:
//	case 3:
//	case 4:
//	case 5:
//	case 6:
//	case 7:
//	case 8:
//	case 9:
//	case 11:
//	case 12:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
//	}
//}
//void Puzzle_2_16()
//{
//	switch (gCurrPuzzleStep)
//	{
//	case 0:P1.Set_Position({ 6,6 });				// Coord de départ du jouer
//		blastP1.Get_Ammo_Manager().Set_Ammo(10);// Quantité d'ammo
//		gCurrPuzzleStepMax = 12;
//		break;
//
//
//	case 1:
//	case 2:
//	case 3:
//	case 4:
//	case 5:
//	case 6:
//	case 7:
//	case 8:
//	case 9:
//	case 11:
//	case 12:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
//	}
//}
//void Puzzle_2_17()
//{
//	switch (gCurrPuzzleStep)
//	{
//	case 0:P1.Set_Position({ 6,6 });				// Coord de départ du jouer
//		blastP1.Get_Ammo_Manager().Set_Ammo(10);// Quantité d'ammo
//		gCurrPuzzleStepMax = 12;
//		break;
//
//
//	case 1:
//	case 2:
//	case 3:
//	case 4:
//	case 5:
//	case 6:
//	case 7:
//	case 8:
//	case 9:
//	case 11:
//	case 12:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
//	}
//}
//void Puzzle_2_18() {
//	switch (gCurrPuzzleStep)
//	{
//	case 0:P1.Set_Position({ 6,6 });				// Coord de départ du jouer
//		blastP1.Get_Ammo_Manager().Set_Ammo(10);// Quantité d'ammo
//		gCurrPuzzleStepMax = 12;
//		break;
//
//
//	case 1:
//	case 2:
//	case 3:
//	case 4:
//	case 5:
//	case 6:
//	case 7:
//	case 8:
//	case 9:
//	case 11:
//	case 12:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
//	}
//}
//void Puzzle_2_19() {
//	switch (gCurrPuzzleStep)
//	{
//	case 0:P1.Set_Position({ 6,6 });				// Coord de départ du jouer
//		blastP1.Get_Ammo_Manager().Set_Ammo(10);// Quantité d'ammo
//		gCurrPuzzleStepMax = 12;
//		break;
//
//
//	case 1:
//	case 2:
//	case 3:
//	case 4:
//	case 5:
//	case 6:
//	case 7:
//	case 8:
//	case 9:
//	case 11:
//	case 12:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
//	}
//}
//void Puzzle_2_FINAL()
//{
//	switch (gCurrPuzzleStep)
//	{
//	case 0:P1.Set_Position({ 6,6 });				// Coord de départ du jouer
//		blastP1.Get_Ammo_Manager().Set_Ammo(10);// Quantité d'ammo
//		gCurrPuzzleStepMax = 12;
//		break;
//
//
//	case 1:
//	case 2:
//	case 3:
//	case 4:
//	case 5:
//	case 6:
//	case 7:
//	case 8:
//	case 9:
//	case 11:
//	case 12:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
//	}
//}