

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
#include "../../events/global_events/ev_spwn_player.h"
#include "../../console/sweet_cmd_console.h"

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
void Puzzle_2_20();
void Puzzle_2_21();
void Puzzle_2_22();
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
Puzzle_2_20,
Puzzle_2_21,
Puzzle_2_22,
Puzzle_2_FINAL
};





void Lvl_2_Spwn_Script()	
{
	if (gSpawnThisCycle)
	{
		skip = 0;		

		LVL2_PUZZLES[gCurrentPuzzle[gCurrentLevel - 1]]();
		gCurrPuzzleStep++;	

		if (skip)
			gSpwBotTimer.Add_Count(skip);
	}
}


// Tuto blocker
void Puzzle_2_0()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 6,3 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(4);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;

		gGrids.Make_Box_Of_Blockers({ 0 + 4 , 0 }, { linkGrid->Get_Cols() - 1 - 4 , linkGrid->Get_Rows() - 1 });
		gGrids.Activate_Link({ 6,11 });	// Link ordinaire à gauche

		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 6 , 10 }, false, true);
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 5 , 6 }, false, true);
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 6 , 6 }, false, true);
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 7 , 6 }, false, true);

		// reset cette variable ici
		seenFinalHour = false;
		break;


	case 1:skip = 8;break;
	case 2:
		Add_Spec(LEFT, 10);
		Add_Spec(LEFT, 9);
		Add_Spec(LEFT, 8);
		skip = 10;
		break;

		break;

	case 4:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}

// Regular links can be converted to BLOCKER
void Puzzle_2_1()
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


	case 1:Add_Spec(DOWN, 10);Add_Spec(DOWN, 11);skip = 6;break;
	case 2:Add_Spec(LEFT, 8);Add_Spec(LEFT, 9);break;
	case 3:Add_Spec(UP, 1);Add_Spec(UP, 0);break;
	case 4:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}


// Place them correctly you fool!
void Puzzle_2_2()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 5,7 });			// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(6);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;

		gGrids.Make_Box_Of_Blockers({ 3 + 1, 4 }, { linkGrid->Get_Cols() - 4, linkGrid->Get_Rows() - 5 });

		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 6 ,5 }, false);
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 6 ,6 }, false);
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 7 ,5 }, false);
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 7, 6 }, false);

		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 6, 8 }, false);
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 6, 9 }, false);
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 7 ,8 }, false);
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 7 ,9 }, false);
		break;


	case 1:Add_Spec(LEFT, 7);skip = 4;break;
	case 2:Add_Spec(RIGHT, 9);skip = 2;break;
	case 3:Add_Spec(UP, 6);skip = 3;break;
	case 4:Add_Spec(UP, 8); skip = 2;break;
	case 5:Add_Spec(DOWN, 6); skip = 1;break;
	case 6:Add_Spec(LEFT, 9);skip = 1;break;
	case 7:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
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

		for (int r = 0; r < 15; r++)
		{
			gGrids.Activate_Link({ 12,r }, Modifier::REGULAR);
		}

		gGrids.Make_Chain_Of_Walls({ 10,0 }, DOWN, linkGrid->Get_Rows() - 1);
		linkGrid->link[10][linkGrid->Get_Rows() - 1].Convert_Modifier(Modifier::BLOCKER);

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

		gGrids.Make_Chain_Of_Walls({ 8,1 }, UP, 1);
		gGrids.Make_Chain_Of_Walls({ 8,1 }, DOWN, 5);
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
	case 0:P1.Set_Position({ 6,9 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(10);	// Quantité d'ammo
		gCurrPuzzleStepMax = 12;

		for (int r = 0; r <= linkGrid->Get_Rows() - 1; r++)
			for (int c = 0; c <= linkGrid->Get_Cols() - 1; c++)
			{
				if (!(r < 15 && c == 6))
					ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { c, r }, 0,1);
			}

		gGrids.Activate_Link({ 6, 5 }, Modifier::REGULAR, 1);

		gGrids.Make_Chain_Of_Walls({ 6, 6 }, UP, 6);
		gGrids.Make_Chain_Of_Walls({ 6, 6 }, DOWN, 1);
		linkGrid->link[6][7].Convert_Modifier(Modifier::BLOCKER);


		//ItemsOnGrid::Remove({6,7});
		//ItemsOnGrid::Remove({ 7,8 });
		break;

	case 1:Add(2); Set_Interval(RIGHT, 7, 9);skip = 10;break;
	case 2:Add(2); Set_Interval(UP, 4, 6);   skip = 7;break;
	case 3:Add(2); Set_Interval(UP, 6, 8); skip = 6;break;
	case 4:
		Add_Spec(LEFT, 6);
		skip = 12;
		break;

	case 5:
		Add(6); Set_Interval(LEFT, 0, 6);
		Add(4); Set_Interval(RIGHT, 6, 10);
		skip = 6;
		break;

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



		//for (int r = 1; r < linkGrid->Get_Rows() - 1; r++)
		//{
		//	gGrids.Activate_Blocker({ 4, r }, 0);
		//	gGrids.Activate_Blocker({ 8, r }, 0);
		//}

		

		gGrids.Activate_Link({ 6,6}, Modifier::REGULAR, true);
		gGrids.Activate_Link({ 9,7 }, Modifier::REGULAR, true);

		gGrids.Make_Chain_Of_Walls({ 6,9 }, DOWN, 5);
		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 6 , 7 });
		break;


	case 1:skip = 15;break;
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
		P1.Set_Hp(1);

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


	case 1:skip = 7; break;
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
	case 6:Add_Spec(UP, 0);Add_Spec(UP, spawnGrid->Get_MaxSpwnCrdX() - 1);skip = 3;break;
	case 7:Add_Spec(UP, 0);Add_Spec(UP, spawnGrid->Get_MaxSpwnCrdX() - 1);break;
	case 8:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}


// Montre qu'on peut grab les items avec transfer. Montre aussi qu'est-ce que ça fait quand on tir sur une border
void Puzzle_2_8()
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
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 7 , 3 });


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
	case 2:Add_Spec(LEFT, 0);Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 1); skip = 0;break;
	case 3:Add_Spec(LEFT, 0);Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 1); skip = 0;break;
	case 4:Add_Spec(LEFT, 0);Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 1); skip = 0;break;
	case 5:Add_Spec(LEFT, 0);Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 1); skip = 0;break;
	case 6:Add_Spec(LEFT, 0);Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 1); skip = 0;break;
	case 7:Add_Spec(LEFT, 0);Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 1); skip = 0;break;
	case 8:Add_Spec(LEFT, 0);Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 1); skip = 0;break;
	case 9:Add_Spec(LEFT, 0);Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 1); skip = 3;break;
	case 11:Add_Spec(RIGHT, 0);Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() - 1); skip = 0;break;
	case 12:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}

void Puzzle_2_9()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 6,4 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(7);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;

		// First
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 4, 3 });

		gGrids.Make_Chain_Of_Walls({ 0, 4 }, DOWN, 4);
		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 2, 4 });
		gGrids.Make_Chain_Of_Walls({ 3 , 3 }, DOWN, 2);
		gGrids.Make_Chain_Of_Walls({ 3 , 5 }, LEFT, 2);
		gGrids.Make_Chain_Of_Walls({ 1 , 5 }, UP, 2);
		gGrids.Make_Chain_Of_Walls({ 1 , 3 }, RIGHT, 1);
		linkGrid->link[2][3].Convert_Modifier(Modifier::BLOCKER);

		// scnd
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 8, 3 });

		gGrids.Make_Chain_Of_Walls({ 12, 4 }, DOWN, 4);
		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 10, 4 });
		gGrids.Make_Chain_Of_Walls({ 9 ,3 }, DOWN, 2);
		gGrids.Make_Chain_Of_Walls({ 9 , 5 }, RIGHT, 2);
		gGrids.Make_Chain_Of_Walls({ 11 , 5 }, UP, 2);
		gGrids.Make_Chain_Of_Walls({ 11 , 3 }, LEFT, 1);
		linkGrid->link[10][5].Convert_Modifier(Modifier::BLOCKER);


		// third
		gGrids.Make_Chain_Of_Walls({ 1 , 9 }, DOWN, 5);
		gGrids.Make_Chain_Of_Walls({ 11, 9 }, DOWN, 5);
		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 5, 9 });
		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 7, 9 });


		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 6, 7 });
		gGrids.Make_Chain_Of_Walls({ 6 , 8 }, LEFT, 2);
		gGrids.Make_Chain_Of_Walls({ 6 , 8 }, RIGHT, 2);
		gGrids.Make_Chain_Of_Walls({ 8 , 8 }, DOWN, 1);
		gGrids.Make_Chain_Of_Walls({ 4 , 8 }, DOWN, 1);

		linkGrid->link[4][8].Convert_Modifier(Modifier::BLOCKER);
		linkGrid->link[8][8].Convert_Modifier(Modifier::BLOCKER);
		linkGrid->link[4][9].Convert_Modifier(Modifier::BLOCKER);
		linkGrid->link[8][9].Convert_Modifier(Modifier::BLOCKER);

		for (int r = 8; r <  15; r++)
		{
			gGrids.Activate_Link({ 4,r }, Modifier::BLOCKER);
			gGrids.Activate_Link({ 8,r }, Modifier::BLOCKER);
		}
		break;

	case 1: skip = 1; break;
	case 2:
		Add(4); Set_Interval(RIGHT, 4, 8);
		Add(4); Set_Interval(LEFT, 4, 8);
		skip = 10;
		break;		

	case 3:
		Add(4); Set_Interval(RIGHT, 4, 8);
		Add(4); Set_Interval(LEFT, 4, 8);
		break;

	case 4:
		Add(5); Set_Interval(RIGHT, 9, 14);
		Add(5); Set_Interval(LEFT, 9, 14);
		break;
	
	case 5:
		Add(5); Set_Interval(RIGHT, 9, 14);
		Add(5); Set_Interval(LEFT, 9, 14);
		break;

	
	case 6:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}


// Buffer transfer tuto
void Puzzle_2_10()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 10,2 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(1);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;

		gGrids.Make_Chain_Of_Walls({ 10, 10 }, LEFT, 1);
		gGrids.Make_Chain_Of_Walls({ 10 - 1, 10 }, UP, 8);
		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 10, 7 });
		break;


	case 1:Add(8);Set_Interval(LEFT, 2, 10); skip = 12;break;
	case 2:Add_Spec(UP, 0); skip = 1;break;
	case 3:Add_Spec(UP, 0); skip = 1;break;
	case 4:Add_Spec(UP, 0); skip = 1;break;
	case 5:Add_Spec(UP, 0); skip = 1;break;
	case 6:Add_Spec(UP, 0); skip = 1;break;
	case 7:Add_Spec(UP, 0); skip = 1;break;
	case 8:Add_Spec(UP, 0); skip = 1;break;
	case 9:Add_Spec(UP, 0); skip = 1;break;
	case 11:Add_Spec(UP, 0);skip = 2; break;
	case 12:Add_Spec(DOWN, 0);break;
	case 13:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}




// une tit ligne au milieu, again
void Puzzle_2_11() {
	switch (gCurrPuzzleStep)
	{
	case 0:
		P1.Set_Position({ 6,10 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(8);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;


		gGrids.Make_Chain_Of_Walls({ 6, 7 }, UP, 2);
		gGrids.Activate_Link({ 6,8 });
		gGrids.Activate_Link({ 5,7 }, Modifier::BLOCKER);
		gGrids.Activate_Link({ 7,7 }, Modifier::BLOCKER);

		gGrids.Activate_Link({ 5,8 }, Modifier::BLOCKER);
		gGrids.Activate_Link({ 7,8 }, Modifier::BLOCKER);

		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 5, 9 });
		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 7, 9 });
		break;

	case 1:Add(2);Set_Interval(RIGHT, 8, 10); skip = 5;break;
	case 2:Add_Spec(RIGHT, 7); Add_Spec(LEFT, 7); skip = 5;break;
	case 3:Add(2);Set_Interval(LEFT, 5, 7);Add(2);Set_Interval(RIGHT, 5, 7); skip = 10;break;
	case 4:Add(2);Set_Interval(LEFT, 7, 9); Add(4);Set_Interval(RIGHT, 7, 11);skip = 4;break;
	case 5:break;
	case 6:MsgQueue::Register(CHECKPOINT_REACHED);break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}




void Puzzle_2_12()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 6,7 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(9);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;

		// Couloir principal au milieu
		for (int i = 0; i < linkGrid->Get_Cols(); i++)
		{
			gGrids.Activate_Blocker({ i, 6 });
			gGrids.Activate_Blocker({ i, 8 });
		}

		gGrids.Activate_Link({ 0,7 }, Modifier::BUFFER);	
		gGrids.Activate_Link({ linkGrid->Get_Cols() - 1, 7 }, Modifier::BUFFER);	
		gGrids.Activate_Link({ 6, 0 }, Modifier::BLOCKER);	

		// Couloir vide au milieu
		for (int i = 5; i >= 0; i--)
		{
			gGrids.Activate_Blocker({ 5, i });
			gGrids.Activate_Blocker({ 7, i });
		}

		gGrids.Activate_Link({ 6, 6 },Modifier::REGULAR,1);

		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 3 ,7 }, false);
		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 4 ,7 }, false);

		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 8 ,7 }, false);
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 9 ,7 }, false);

		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 6 ,3 }, false);
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 6 ,4 }, false);
		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 6 ,5 }, false);
		break;


	case 1:Add_Spec(UP, 1);Add_Spec(UP, 0);skip = 7;break;
	case 2:Add_Spec(DOWN, 10);Add_Spec(DOWN, 11);skip = 8;break;
	case 3:Add_Spec(UP, 9);Add_Spec(UP, 2); skip = 5; break;
	case 4:Add_Spec(LEFT, 0);Add_Spec(LEFT, 1);Add_Spec(LEFT, 2);break;
	case 5:Add_Spec(DOWN, 0);Add_Spec(DOWN, 1);	Add_Spec(DOWN, 10);Add_Spec(DOWN, 11);
		Add_Spec(DOWN, 9);Add_Spec(DOWN, 2);break;
	case 6:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}

void Puzzle_2_13()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 6,8 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(7);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;

		gGrids.Make_Box_Of_Blockers({ 3, 4 }, { linkGrid->Get_Cols() - 4, linkGrid->Get_Rows() - 5 });
		gGrids.Make_Chain_Of_Walls({ 6, 4 }, DOWN, 2);
		linkGrid->link[6][5].Convert_Modifier(Modifier::BLOCKER);
		linkGrid->link[6][6].Convert_Modifier(Modifier::BLOCKER);

		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 5 ,7 }, false);
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 5 ,8 }, false);
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 5, 9 }, false);

		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 6 ,7 }, false);
		//ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 6 ,7 }, false);
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 6 ,9 }, false);

		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 7 ,7 }, false);
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 7 ,8 }, false);
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 7 ,9 }, false);
		break;


	case 1:Add_Spec(DOWN, 5);skip = 4;break;
	case 2:Add_Spec(LEFT, 9);skip = 3;break;
	case 3:Add_Spec(UP, 6);skip = 2;break;
	case 4:Add_Spec(RIGHT, 8); skip = 2;break;
	case 5:Add_Spec(DOWN, 8); skip = 1;break;
	case 6:Add_Spec(LEFT, 6);skip = 4;break;
	case 7:Add_Spec(RIGHT, 5);skip = 1;break;
	case 8:Add_Spec(UP, 5);skip = 1;break;
	case 9:Add_Spec(LEFT, 4);skip = 1;break;
	case 10:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}

// Alternance entre buff et blocker. Bie regarder la queue à gauche
void Puzzle_2_14()
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
		skip = 10;
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


// Show that you can shoot the buffers
void Puzzle_2_15()
{
	GrdCoord crd = P1.Get_Grd_Coord();

	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 5,8 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(8);// Quantité d'ammo
		gCurrPuzzleStepMax = 1;

		//gGrids.Make_Box_Of_Blockers({ 0, 0 }, { linkGrid->Get_Cols() - 1, linkGrid->Get_Rows() - 1 });
		gGrids.Activate_Link({ 5,6 }, Modifier::BUFFER);
		gGrids.Activate_Link({ 7,8 }, Modifier::BUFFER);
		break;


	case 1:Add_Spec(LEFT, 6); Add_Spec(RIGHT, 6);skip = 1;break;
	case 2:Add_Spec(LEFT, 8); Add_Spec(RIGHT, 8);skip = 1;break;
	case 3:Add_Spec(UP, 7); Add_Spec(DOWN, 7);	skip = 1;break;
	case 4:Add_Spec(UP, 5); Add_Spec(DOWN, 5);	skip = 2;break;
	case 5:Add_Spec(LEFT, 7); Add_Spec(RIGHT, 7);skip = 2;break;
	case 6:Add_Spec(LEFT, 5); Add_Spec(RIGHT, 5);skip = 2;break;
	case 7:Add_Spec(UP, 4); Add_Spec(DOWN, 4);skip = 3;break;
	case 8:Add_Spec(UP, 6); Add_Spec(DOWN, 6);	skip = 3;break;
	case 9:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}

// Double STRONG walls transfer!
void Puzzle_2_16()
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
				gGrids.Make_Chain_Of_Walls({ i,5 }, DOWN, 1,WallType::STRONG, Modifier::REGULAR);

			gGrids.Activate_Blocker({ i, 4 });
			gGrids.Activate_Blocker({ i, 8 });
		}

		gGrids.Activate_Blocker({ 0, 5 });
		gGrids.Activate_Blocker({ 12, 5});
		gGrids.Activate_Blocker({ 0, 6 });
		gGrids.Activate_Blocker({ 0, 7 });

		gGrids.Activate_Blocker({ linkGrid->Get_Cols() - 1, 7 });

		/*gGrids.Activate_Link({ 0,7 }, Modifier::BUFFER);
		gGrids.Make_Chain_Of_Walls({ 0, 7 }, RIGHT, 7, WallType::STRONG);*/
		break;

	case 1:Add_Spec(RIGHT, 5);skip = 1; break;	// Ajoute un skip = 1 ici si c'est trop hard //skip = 1;
	case 2:Add_Spec(RIGHT, 5);skip = 1; break;												 //skip = 1;
	case 3:Add_Spec(RIGHT, 5);skip = 1; break;												 //skip = 1;
	case 4:Add_Spec(RIGHT, 5);skip = 1; break;												 //skip = 1;
	case 5:Add_Spec(RIGHT, 5);skip = 1; break;												 //skip = 1;
	case 6:Add_Spec(RIGHT, 5);skip = 1; break;												 //skip = 1;
	case 7:Add_Spec(RIGHT, 5); skip = 15;break;
	case 8:Add(7); Set_Interval(UP, 5, 12);break;
	case 9:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}


// Buffer transfer v2
void Puzzle_2_17()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 7, 11 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(2);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;

		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 2, 9 }, DOWN, 1);

		gGrids.Make_Chain_Of_Walls({ 3, 11 }, UP, 1,WallType::STRONG,Modifier::REGULAR);
		gGrids.Make_Chain_Of_Walls({ 3, 11 - 1 }, RIGHT, 3, WallType::STRONG);

		gGrids.Make_Chain_Of_Walls({ 6, 3 }, RIGHT, 1);
		gGrids.Make_Chain_Of_Walls({ 7, 3 }, DOWN, 3);

		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { linkGrid->Get_Cols() - 2,8 });
		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 6, 4 });
		//ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 4, 11 });
		break;


	case 1:skip = 1;break;
	case 2:Add(4);Set_Interval(DOWN, 7, 11);skip = 3;break;
	case 3:Add(3);Set_Interval(RIGHT, 3, 6); skip = 16;break;
	case 4:
		Add(4);Set_Interval(UP, 7, 11); Add(4);Set_Interval(LEFT, 6, 10);
		break;
	case 5:Add(4);Set_Interval(LEFT, 6, 10); skip = 0;break;
	case 6:Add(4);Set_Interval(UP, 7, 11); 		break;
	case 7:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}

void Puzzle_2_18()
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


// blocker transfer
void Puzzle_2_19()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 1,7 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(3);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;
		
		
		// Couloir principal au milieu
		for (int i = 0; i < linkGrid->Get_Cols() - 1; i++)
		{
				gGrids.Activate_Blocker({ i, 6 });
				gGrids.Activate_Blocker({ i, 8 });
		}

		
		for (int i = 3; i < 12; i++)
		{
			if(i != 7)
				gGrids.Activate_Blocker({ 11, i });

		}

		gGrids.Activate_Link({ 0, 7 }, Modifier::REGULAR);
		gGrids.Activate_Link({ 12, 3 }, Modifier::BLOCKER);
		gGrids.Activate_Link({ 12, 11 }, Modifier::REGULAR);


		gGrids.Make_Chain_Of_Walls({ 5, 7 }, LEFT, 1);
		gGrids.Make_Chain_Of_Walls({ 7, 7 }, LEFT, 1);
		gGrids.Make_Chain_Of_Walls({ 9, 7 }, LEFT, 1);
		gGrids.Make_Chain_Of_Walls({ 11, 7 }, LEFT, 1);


		gGrids.Make_Chain_Of_Walls({ 12, 4 }, DOWN, 2);
		gGrids.Make_Chain_Of_Walls({ 12, 10 }, UP, 1);


		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 2, 7 });
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 3, 7 });
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 12, 7 });

		break;


	case 1:Add(4);Set_Interval(UP, 0, 4);skip = 10;	break;
	case 2:
		Add_Spec(LEFT, 3);Add_Spec(LEFT, 4);Add_Spec(LEFT, 5);
		Add_Spec(LEFT, 8);Add_Spec(LEFT, 9);Add_Spec(LEFT, 10);
		break;
	case 3:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}


void Puzzle_2_20() {
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 10, 0 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(2);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;

		gGrids.Make_Chain_Of_Walls({ 0,linkGrid->Get_Rows() - 1 }, UP, linkGrid->Get_Rows() - 1);
		gGrids.Make_Chain_Of_Walls({ 2,linkGrid->Get_Rows() - 1 }, UP, 2);
		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 1, linkGrid->Get_Rows() - 1 });

		for (int r = 0; r < linkGrid->Get_Rows(); r++)
			for (int c = 1; c < linkGrid->Get_Cols(); c++)
				if (!(c == 10 && r == 1))
					ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { c,r }, 1, 1);


		// Voici le chemin que le joueur doit suivre
		ItemsOnGrid::Remove({ 10,2 - 2 });
		ItemsOnGrid::Remove({ 10,3 - 2 });
		ItemsOnGrid::Remove({ 10,4 - 2 });
		ItemsOnGrid::Remove({ 10,5 - 2 });

		ItemsOnGrid::Remove({ 9,5 - 2 });
		ItemsOnGrid::Remove({ 8,5 - 2 });
		ItemsOnGrid::Remove({ 7,5 - 2 });
		ItemsOnGrid::Remove({ 6,5 - 2 });
		ItemsOnGrid::Remove({ 5,5 - 2 });
		ItemsOnGrid::Remove({ 4,5 - 2 });
		ItemsOnGrid::Remove({ 3,5 - 2 });
		ItemsOnGrid::Remove({ 2,5 - 2 });

		ItemsOnGrid::Remove({ 2,6 - 2 });

		ItemsOnGrid::Remove({ 2,7 - 2 });
		ItemsOnGrid::Remove({ 3,7 - 2 });
		ItemsOnGrid::Remove({ 4,7 - 2 });
		ItemsOnGrid::Remove({ 5,7 - 2 });

		ItemsOnGrid::Remove({ 5,8 - 2 });

		ItemsOnGrid::Remove({ 5,9 - 2 });
		ItemsOnGrid::Remove({ 5,10 - 2 });
		ItemsOnGrid::Remove({ 4,10 - 2 });

		ItemsOnGrid::Remove({ 4,11 - 2 });

		ItemsOnGrid::Remove({ 4,12 - 2 });
		ItemsOnGrid::Remove({ 5,12 - 2 });
		ItemsOnGrid::Remove({ 6,12 - 2 });
		ItemsOnGrid::Remove({ 7,12 - 2 });
		ItemsOnGrid::Remove({ 8,12 - 2 });


		ItemsOnGrid::Remove({ 8,11 - 2 });
		ItemsOnGrid::Remove({ 8,10 - 2 });
		ItemsOnGrid::Remove({ 8,9 - 2 });
		ItemsOnGrid::Remove({ 8,8 - 2 });

		ItemsOnGrid::Remove({ 9, 8 - 2 });
		ItemsOnGrid::Remove({ 10,8 - 2 });

		ItemsOnGrid::Remove({ 10,7 - 2 });
		ItemsOnGrid::Remove({ 11,7 - 2 });
		ItemsOnGrid::Remove({ 12,7 - 2 });
		ItemsOnGrid::Remove({ 12,8 - 2 });
		ItemsOnGrid::Remove({ 12,9 - 2 });
		ItemsOnGrid::Remove({ 12,10 - 2 });
		ItemsOnGrid::Remove({ 11,10 - 2 });
		ItemsOnGrid::Remove({ 11,11 - 2 });
		ItemsOnGrid::Remove({ 11,12 - 2 });
		ItemsOnGrid::Remove({ 10,12 - 2 });
		ItemsOnGrid::Remove({ 10,13 - 2 });
		ItemsOnGrid::Remove({ 10,14 - 2 });

		ItemsOnGrid::Remove({ 10,14 - 1 });
		ItemsOnGrid::Remove({ 9,14 - 1 });
		ItemsOnGrid::Remove({ 8,14 - 1 });
		ItemsOnGrid::Remove({ 7,14 - 1 });
		ItemsOnGrid::Remove({ 6,14 - 1 });
		ItemsOnGrid::Remove({ 5,14 - 1 });
		ItemsOnGrid::Remove({ 4,14 - 1 });
		ItemsOnGrid::Remove({ 3,14 - 1 });
		ItemsOnGrid::Remove({ 2,14 - 1 });

		ItemsOnGrid::Remove({ 1,13 });
		ItemsOnGrid::Remove({ 3,14 });
		break;


	case 1:skip = 20;break;
	case 2:Add(spawnGrid->Get_MaxSpwnCrdY());Set_Interval(LEFT, 0, spawnGrid->Get_MaxSpwnCrdY()); break;
	case 3:Add(spawnGrid->Get_MaxSpwnCrdY());Set_Interval(LEFT, 0, spawnGrid->Get_MaxSpwnCrdY());break;
	case 4:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}



void Puzzle_2_21()
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
		gGrids.Activate_Link({ 6, 5 }, Modifier::REGULAR, 1);
		break;

	case 1:Add(4);Set_Interval(DOWN, 6, 10);skip = 10;break;
	case 2:Add_Spec(RIGHT, 2);skip = 3;break;
	case 3:Add(4);Set_Interval(DOWN, 2, 6);skip = 7;break;
	case 4:Add_Spec(RIGHT, 2);skip = 5;break;
	case 5:Add(2);Set_Interval(RIGHT, 5, 7);skip = 9;break;
	case 6:Add_Spec(RIGHT, 2);skip = 5;break;
	case 7:Add(3);Set_Interval(DOWN, 2, 5);skip = 5;break;
	case 8:Add_Spec(RIGHT, 2);skip = 5;break;
	case 9:Add_Spec(RIGHT, 1);Add_Spec(LEFT, 1);break;
	case 10:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}


void Puzzle_2_22()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 6,7 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(10);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;

		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 6,1 });
		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 6,2 });
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 6,3 });
		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 6,4 });

		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 11,7 });
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 10,7 });
		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 9,7 });

		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 3,7 });
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 2,7 });
		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 1,7 });



		gGrids.Make_Chain_Of_Walls({ 6, 0 }, LEFT, 6);
		gGrids.Make_Chain_Of_Walls({ 6, 0 }, RIGHT, 6);


		// Vertical sur les côtés
		gGrids.Make_Chain_Of_Walls({ 0, 7 }, UP, 6);
		gGrids.Make_Chain_Of_Walls({ 12, 7 }, UP, 6);


		gGrids.Make_Chain_Of_Walls({ 2 + 2, 7 + 1 }, RIGHT, 4);
		gGrids.Make_Chain_Of_Walls({ 3 + 2, 8 + 1 }, RIGHT, 3);
		gGrids.Make_Chain_Of_Walls({ 3 + 2, 8 + 1 }, LEFT, 1);
		gGrids.Make_Chain_Of_Walls({ 4 + 2, 9 + 1 }, RIGHT, 2);
		gGrids.Make_Chain_Of_Walls({ 4 + 2, 9 + 1 }, LEFT, 2);
		gGrids.Make_Chain_Of_Walls({ 6 + 2, 10 + 1 }, LEFT, 4);
		gGrids.Make_Chain_Of_Walls({ 3 + 2, 11 + 1 }, RIGHT, 3);
		gGrids.Make_Chain_Of_Walls({ 3 + 2, 11 + 1 }, LEFT, 1);


		gGrids.Make_Chain_Of_Walls({ 5 + 2, 12 + 1 }, LEFT, 3);
		gGrids.Make_Chain_Of_Walls({ 5 + 2, 12 + 1 }, RIGHT, 1);

		for (short r = 0; r < 6; r++)
		{
			if (r != 0)
				linkGrid->link[2 + 2][8 + r].Convert_Modifier(Modifier::BLOCKER);

			if (r != 3)
				linkGrid->link[2 + 2 + 4][8 + r].Convert_Modifier(Modifier::BLOCKER);
		}


		gGrids.Activate_Link({ 9, 8 }, Modifier::BLOCKER);
		gGrids.Activate_Link({ 9, 9 }, Modifier::BLOCKER);
		gGrids.Activate_Link({ 9, 10 }, Modifier::BLOCKER);
		gGrids.Activate_Link({ 9, 11 }, Modifier::BLOCKER);
		gGrids.Activate_Link({ 9, 12 }, Modifier::BLOCKER);
		gGrids.Activate_Link({ 9, 13 }, Modifier::BLOCKER);

		gGrids.Activate_Link({ 1 + 2, 8 }, Modifier::BLOCKER);
		gGrids.Activate_Link({ 1 + 2, 9 }, Modifier::BLOCKER);
		gGrids.Activate_Link({ 1 + 2, 10 }, Modifier::BLOCKER);
		gGrids.Activate_Link({ 1 + 2, 11 }, Modifier::BLOCKER);
		gGrids.Activate_Link({ 1 + 2, 12 }, Modifier::BLOCKER);
		gGrids.Activate_Link({ 1 + 2, 13 }, Modifier::BLOCKER);

		gGrids.Activate_Link({ 0, 8 }, Modifier::BLOCKER);
		gGrids.Activate_Link({ 1, 8 }, Modifier::BLOCKER);
		gGrids.Activate_Link({ 2, 8 }, Modifier::BLOCKER);

		gGrids.Activate_Link({ 10, 8 }, Modifier::BLOCKER);
		gGrids.Activate_Link({ 11, 8 }, Modifier::BLOCKER);
		gGrids.Activate_Link({ 12, 8 }, Modifier::BLOCKER);

		gGrids.Make_Chain_Of_Walls({ 6, 14 }, LEFT, 6);
		gGrids.Make_Chain_Of_Walls({ 6, 14 }, RIGHT, 6);
		gGrids.Make_Chain_Of_Walls({ 0, 14 }, UP, 5);
		gGrids.Make_Chain_Of_Walls({ 12, 14 }, UP, 5);
		skip = 3000;
		break;


	case 1:skip = 15;break;
	case 2:
		Add(6); Set_Interval(LEFT, 1, 7);
		Add(6); Set_Interval(RIGHT, 1, 7);
		Add(12); Set_Interval(UP, 0, 12);
		skip = 5;
		break;

	case 3:
		Add(6); Set_Interval(LEFT, 1, 7);
		Add(6); Set_Interval(RIGHT, 1, 7);
		Add(12); Set_Interval(UP, 0, 12);
		skip = 5;
		break;

	case 4:
		Add(5); Set_Interval(LEFT, 9, 14);
		Add(5); Set_Interval(RIGHT, 9, 14);
		Add(12); Set_Interval(DOWN, 0, 12);
		break;

	case 5:
		Add(5); Set_Interval(LEFT, 9, 14);
		Add(5); Set_Interval(RIGHT, 9, 14);
		Add(12); Set_Interval(DOWN, 0, 12);
		break;

	case 6:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}




void Puzzle_2_FINAL()
{
	static bool upOrDown = false;
	static Direction leftOrRight = LEFT;

	static std::string _1 = "- SURVIVE -";
	static std::string _2 = "Waves Remaining :";

	static Coord crd;
	const int SHAPES_TO_KILL = 15;
	static int shapesRemaining;

	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 6,7 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(18);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;
		
		upOrDown = false;
		leftOrRight = LEFT;
		shapesRemaining = SHAPES_TO_KILL;
		crd = { Find_Ctr_String_X(_1) - 1, 6 };

		//seenFinalHour = 1;	// debug

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
			MsgQueue::Register(FINAL_HOUR);	// montre ça juste une fois, EVER
			seenFinalHour = true;
			skip = 10;
		}
		else
			skip = -1;
		break;

	case 2:

		if (P1.Cant_Do_Stuff())
			Set_Ev_Spawn_Player(3);

		//box regular au milieu
		for (int i = 3; i < linkGrid->Get_Cols() -3; i++)
		{
			if (i != 6)
			{
				gGrids.Activate_Link({ i, 5 }, Modifier::REGULAR);
				gGrids.Activate_Link({ i, 9 }, Modifier::REGULAR);
			}
		}
	
		// Lignes verticales
		for (int i = 0; i < linkGrid->Get_Rows(); i++)
		{
			gGrids.Activate_Link({ 0,i }, Modifier::BLOCKER);
			gGrids.Activate_Link({ 1,i }, Modifier::BLOCKER);
			gGrids.Activate_Link({ 2,i }, Modifier::BLOCKER);
			gGrids.Activate_Link({ 3,i }, Modifier::BLOCKER);

			gGrids.Activate_Link({ 12,i }, Modifier::BLOCKER);
			gGrids.Activate_Link({ 11,i }, Modifier::BLOCKER);
			gGrids.Activate_Link({ 10,i }, Modifier::BLOCKER);
			gGrids.Activate_Link({ 9,i }, Modifier::BLOCKER);
		}

		// Lignes horizontales
		for (int i = 0; i < linkGrid->Get_Cols(); i++)
		{
			if (i != 6)
			{
				gGrids.Activate_Link({ i,0 }, Modifier::BLOCKER);
				gGrids.Activate_Link({ i,1 }, Modifier::BLOCKER);
				gGrids.Activate_Link({ i,2 }, Modifier::BLOCKER);
				gGrids.Activate_Link({ i,3 }, Modifier::BLOCKER);
				gGrids.Activate_Link({ i,4 }, Modifier::BLOCKER);
				gGrids.Activate_Link({ i,10 }, Modifier::BLOCKER);
				gGrids.Activate_Link({ i,11 }, Modifier::BLOCKER);
				gGrids.Activate_Link({ i,12 }, Modifier::BLOCKER);
				gGrids.Activate_Link({ i,13 }, Modifier::BLOCKER);
				gGrids.Activate_Link({ i,14 }, Modifier::BLOCKER);
			}
		}

		//tips
		gGrids.Make_Chain_Of_Walls({ 6,0 }, DOWN, 4, WallType::STRONG, Modifier::BUFFER);
		gGrids.Make_Chain_Of_Walls({ 6,14 }, UP, 4, WallType::REGULAR, Modifier::BLOCKER);

		ItemSpawner::Spawn_This_Item(ItemType::AMMO, { 4, 7 });
		ItemSpawner::Spawn_This_Item(ItemType::AMMO, { 8, 7 });
		break;

	case 3:
		ConsoleRender::Add_String(std::to_string(shapesRemaining), { crd.x + 13,crd.y + 1 }, LIGHT_AQUA, TXT_SPD_DR);
		ConsoleRender::Add_String(_1, crd, BRIGHT_WHITE, TXT_SPD_DR);
		ConsoleRender::Add_String(_2, { crd.x - 5, crd.y + 1 }, WHITE, TXT_SPD_DR);

		Set_Interval(LEFT, 0, 4);
		Set_Interval(RIGHT, 0, 4);
		Add(8);
		Add_Spec(LEFT, 10);Add_Spec(LEFT, 11);Add_Spec(RIGHT, 12);Add_Spec(RIGHT, 13);
		skip = 12;
		break;

	case 4:
		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 6, 1 });
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 6, 13 });
		MsgQueue::Register(ENABLE_ITEM_SPAWN);
		Add_Spec(LEFT, 8);
		skip = 5;
		break;

	case 5:Add_Spec(RIGHT, 5);skip = 5;break;
	case 6:Add(1);skip = 5;break;
	case 7:Add(1);skip = 5;break;
	case 8:
		Add_Spec(LEFT, 5);skip = 5;
		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 6, 2 });
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 6, 12 });
		break;

	case 9:Add_Spec(RIGHT, 8);skip = 8;break;
	case 10:
		Hide_Cursor();
		Add(1);
		skip = 2;
		ItemSpawner::Spawn_This_Item(ItemType::AMMO, { 4, 7 });
		ItemSpawner::Spawn_This_Item(ItemType::AMMO, { 8, 7 });
		break;

	case 11:Add(1);skip = 2;break;
	case 12:Add_Spec(LEFT, 8);skip = 2;break;
	case 13:Add_Spec(RIGHT, 5);skip = 5;break;
	case 14:
		Add(1);skip = 9;
		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 6, 3 });
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 6, 11 });
		break;

	case 15:Add(1);	skip = 5;break;
	case 16:Add_Spec(LEFT, 8);skip = 5;
		ItemSpawner::Spawn_This_Item(ItemType::AMMO, { 4, 7 });
		ItemSpawner::Spawn_This_Item(ItemType::AMMO, { 8, 7 });
		break;

	case 17:Add_Spec(RIGHT, 5);skip = 5;break;
	case 18:
		Set_Interval(LEFT, 0, 4);
		Set_Interval(RIGHT, 0, 4);
		Add(8);
		Add_Spec(LEFT, 10);Add_Spec(LEFT, 11);Add_Spec(RIGHT, 12);Add_Spec(RIGHT, 13);
		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 6, 4 });
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 6, 10 });

		// VICTORY IS OURS HAHAHAHAHAHAH
		MsgQueue::Register(STOP_BOT_SPAWNS);
		Ev_Wait_For_Victory(); // Wait que le dernier bot meurt pour trigger la victoire
		break;
	}

	if (gCurrPuzzleStep % 2 == 0)
		Set_Interval(LEFT, 6, 7);
	else
		Set_Interval(RIGHT, 6, 7);

	if (gCurrPuzzleStep > 3)
	{
		if (shapesRemaining == 9)
			ConsoleRender::Add_String(TXT_CONST.SPACE_STRING, { crd.x + 14,crd.y + 1 }, LIGHT_AQUA, TXT_SPD_DR);

		ConsoleRender::Add_String(std::to_string(shapesRemaining), { crd.x + 13,crd.y + 1 }, LIGHT_AQUA, TXT_SPD_DR);

		shapesRemaining--;
	}


}





