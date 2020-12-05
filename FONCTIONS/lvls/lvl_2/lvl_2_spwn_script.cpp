

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

void Puzzle_2_0()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 6,1 });				
		blastP1.Get_Ammo_Manager().Set_Ammo(10);	
		gCurrPuzzleStepMax = 12;
		
		gGrids.Activate_Blocker({ linkGrid->Get_Cols() / 2 - 3, 11 }, 0);	
		gGrids.Activate_Blocker({ linkGrid->Get_Cols() / 2 , 11    }, 0);
		gGrids.Activate_Blocker({ linkGrid->Get_Cols() / 2 + 3, 11 }, 0);


		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 6 , 3 });
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 5 , 3 });
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 7 , 3 });
		break;


	case 1:skip = 10;break;
	case 2:Add(1);break;
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
void Puzzle_2_1()
{
	switch (gCurrPuzzleStep)
	{
	case 0:
		P1.Set_Position({ linkGrid->Get_Cols() - 5, 2 });				// Coord de départ du jouer
		P1.Reset_Hp_And_Heart(1);
		blastP1.Get_Ammo_Manager().Set_Ammo(20);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;

		for (int r = 1; r < 5; r += 2)	// 2 couloirs
		{
			for (int c = 0; c < linkGrid->Get_Cols() - 3; c++)
				gGrids.Activate_Blocker({ c ,r });	// 1 couloir de la mort!!!			
		}
		gGrids.Activate_Blocker({ 0,1 }, 0);	// ferme le corridor
		gGrids.Activate_Blocker({ 0,2 }, 0);	// ferme le corridor
		gGrids.Activate_Blocker({ 0,3 }, 0);	// ferme le corridor
		gGrids.Activate_Blocker({ linkGrid->Get_Cols() - 3,0 }, 0);
		gGrids.Activate_Blocker({ linkGrid->Get_Cols() - 3,4 }, 0);

		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { linkGrid->Get_Cols() - 1,1 }, 0, 1);
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { linkGrid->Get_Cols() - 2,1 }, 0, 1);
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { linkGrid->Get_Cols() - 3,1 }, 0, 1);
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { linkGrid->Get_Cols() - 1,3 }, 0, 1);
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { linkGrid->Get_Cols() - 2,3 }, 0, 1);
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { linkGrid->Get_Cols() - 3,3 }, 0, 1);
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { linkGrid->Get_Cols() - 2,2 });	// un derrière le joueur
		break;


	case 1: Add_Spec(UP, 0);skip = 10; break;
	case 2:
		Add_Spec(DOWN, 0);
		Add_Spec(UP, 1);
		Add_Spec(DOWN, 2);
		Add_Spec(UP, 3);
		Add_Spec(DOWN, 4);
		Add_Spec(UP, 5);
		break;
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

void Puzzle_2_2()
{
	GrdCoord crd = P1.Get_Grd_Coord();

	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 2,2 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(10);// Quantité d'ammo
		gCurrPuzzleStepMax = 1;


		for (int c = -1; c < 2; c++)
			for (int r = -1; r < 2; r++)
			{
				if (!(c == 0 && r == 0))
					gGrids.Activate_Blocker({ crd.c + c,crd.r + r });
			}

		gGrids.Make_Chain_Of_Walls({ 12,2 }, RIGHT, wallGridHor->Get_Cols() - 13);	// Mur que le joueurs va tirés avec les items
		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 11,2 });
		break;


	case 1:			
		Add_Spec(UP, 12);
		Add_Spec(UP, 14);
		Add_Spec(UP, 13);
		skip = 15;
		break;

	case 2:
		Add_Spec(DOWN, 12);
		Add_Spec(DOWN, 14);
		Add_Spec(DOWN, 13);

		for (int c = -1; c < 2; c++)
			for (int r = -1; r < 2; r++)
			{
				if (!(c == 0 && r == 0))
					gGrids.Activate_Blocker({ crd.c + c,crd.r + r },true);
			}
		break;

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

void Puzzle_2_3()
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

void Puzzle_2_4()
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
void Puzzle_2_5()
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
void Puzzle_2_6()
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
void Puzzle_2_7()
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
void Puzzle_2_8()
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
void Puzzle_2_9()
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
void Puzzle_2_11()
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
void Puzzle_2_12()
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
void Puzzle_2_13()
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
void Puzzle_2_14()
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