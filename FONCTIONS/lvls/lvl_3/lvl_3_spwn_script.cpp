

#include "lvl_3_spwn_script.h"
#include "../../time/spawn_cycle.h"
#include "../../grid/managegrids.h"
#include "../../spawns/bots_to_spawn.h"
#include "../../events/msg_dispatcher.h"
#include "../lvl_script.h"
#include "../../console/sweet_cmd_console.h"
#include "../../player/player.h"

//some events Shhh...
#include "../../events/global_events/ev_wait_last_bot.h"
#include "../../items/item_spawner.h"
#include "../../events/global_events/ev_warning.h"
#include "../../events/global_events/feedback/ev_draw_map.h"
#include "lvl_3_initializer.h"
#include "../../events/global_events/ev_spwn_player.h"
#include "../../events/global_events/feedback/ev_take_your_time.h"


using namespace bots_to_spawn;

static bool seenFinalHour = false;
static int skip;

// Puzzles du lvl1:
void Puzzle_3_0();
void Puzzle_3_1();
void Puzzle_3_2();
void Puzzle_3_3();
void Puzzle_3_4();
void Puzzle_3_5();
void Puzzle_3_6();
void Puzzle_3_7();
void Puzzle_3_8();
void Puzzle_3_9();
void Puzzle_3_10();
void Puzzle_3_11();
void Puzzle_3_12();
void Puzzle_3_13();
void Puzzle_3_14();
void Puzzle_3_15();
void Puzzle_3_16();
void Puzzle_3_17();
void Puzzle_3_18();
void Puzzle_3_19();
void Puzzle_3_20();
void Puzzle_3_21();
void Puzzle_3_22();
void Puzzle_3_FINAL();


// VOICI  l'ordre dans lequel sera joué les puzzles
void (*LVL3_PUZZLES[])() = {	// definition 
Puzzle_3_0,
Puzzle_3_1,
Puzzle_3_2,
Puzzle_3_3,
Puzzle_3_4,
Puzzle_3_5,
Puzzle_3_6,
Puzzle_3_7,
Puzzle_3_8,
Puzzle_3_9,
Puzzle_3_10,
Puzzle_3_11,
Puzzle_3_12,
Puzzle_3_13,
Puzzle_3_14,
Puzzle_3_15,
Puzzle_3_16,
Puzzle_3_17,
Puzzle_3_18,
Puzzle_3_19,
Puzzle_3_20,
Puzzle_3_21,
Puzzle_3_22,
Puzzle_3_FINAL
};





void Lvl_3_Spwn_Script()	// HERE WE GO AGAIN
{
	if (gSpawnThisCycle)
	{
		skip = 0;		

		LVL3_PUZZLES[gCurrentPuzzle[gCurrentLevel - 1]]();	// Script du puzzle
		gCurrPuzzleStep++;	// Prochain step du puzzle!

		if (skip)
			gSpwBotTimer.Add_Count(skip);
	}
}


// Forcefield intro #1
void Puzzle_3_0()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ linkGrid->Get_Cols() / 2 , 11 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(10);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;

		//Set_Dr_Map_1(TXT_SPD_DR * 4);  
		Set_Dr_Map_1(0,1);  

		for (int r = 1; r < 14; r++)
		{
			for (int c = 0; c < 9; c++)
			{
				if (c < 3 || c > 5)
					gGrids.Activate_Link({ linkGrid->Get_Cols() / 2 - 4 + c,r }, Modifier::FORCEFIELD);
			}
		}

		gGrids.Make_Box_Around({ linkGrid->Get_Cols() / 2,7 }, 7);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() / 2 , 3 }, DOWN, 7, WallType::ENERGIZED, Modifier::REGULAR);
		break;


	case 1:skip = 8;break;
	case 2:Add_Spec(UP, 6);Add_Spec(UP, 11);skip = 5;break;
	case 3:Add_Spec(UP, 14);Add_Spec(UP, 19);skip = 3;break;
	case 4:Add_Spec(UP, 6);Add_Spec(UP, 11); skip = 5;break;
	case 5:Add_Spec(UP, 14);Add_Spec(UP, 19);skip = 3;break;
	case 6:Add_Spec(UP, 6);Add_Spec(UP, 11); skip = 5;break;
	case 7:Add_Spec(UP, 14);Add_Spec(UP, 19);skip = 3;break;
	case 8:Add_Spec(UP, 6);Add_Spec(UP, 11); break;

	case 9:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}


// Forcefield intro #2
void Puzzle_3_1()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ linkGrid->Get_Cols() / 2, 9 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(12);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;

		gGrids.Make_Box_Around({ linkGrid->Get_Cols() / 2, 7 }, 3, Modifier::FORCEFIELD);
		gGrids.Activate_Link({ linkGrid->Get_Cols() / 2, 7 }, Modifier::ENERGIZER);
		break;


	case 1:skip = 5;break;
	case 2:Add_Spec(UP, spawnGrid->Get_MaxSpwnCrdX() - 1);Add_Spec(DOWN, 0);	break;
	case 3:Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 1);Add_Spec(RIGHT, 0); skip = 2;	break;
	case 4:Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() - 1);skip = 2;	break;
	case 5:Add_Spec(UP, spawnGrid->Get_MaxSpwnCrdX() - 1);skip = 2;	break;
	case 6:Add_Spec(DOWN, 0);skip = 2;	break;
	case 7:Add_Spec(LEFT, 0);break;
	case 8:Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() - 1);	break;
	case 9:Add_Spec(UP, spawnGrid->Get_MaxSpwnCrdX() - 1);break;
	case 10:Add_Spec(DOWN, 0);	break;
	case 11:Add_Spec(LEFT, 0);	break;
	case 12:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}


// TELEPORTATION TUTORIAL
void Puzzle_3_2()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ linkGrid->Get_Cols() - 1, 14 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(1);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;

		// Very Temporary! Doit être remove
		ConsoleRender::Add_String("TELEPORTATION SHOT", { (Find_Ctr_X((int)std::size("TELEPORTATION SHOT")) / 2) / 2, (gConHeight / 2) / 2 }, BRIGHT_WHITE, TXT_SPD_DR);
		ConsoleRender::Add_String("(Shoot, then spacebar)", { (Find_Ctr_X((int)std::size("(Shoot , then spacebar)")) / 2) / 2 , (gConHeight / 2) / 2 + 2 }, WHITE, TXT_SPD_DR);

		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 2, linkGrid->Get_Rows() - 1 }, UP, linkGrid->Get_Rows() - 3);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 2, 2 }, LEFT,  5);

		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 2, linkGrid->Get_Rows() - 3 }, LEFT, linkGrid->Get_Cols() - 4);
		gGrids.Make_Chain_Of_Walls({ 2, linkGrid->Get_Rows() - 3 }, UP, 10);
		gGrids.Make_Chain_Of_Walls({ 2, 2 }, RIGHT, 5);
		break;
		
	case 1:
		skip = 3;
		break;



	case 2:
		Add(13); Set_Interval(UP, 7, 20);
		Add_Spec(DOWN, spawnGrid->Get_MaxSpwnCrdX() - 2);
		MsgQueue::Register(CHECKPOINT_REACHED); 
		break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE

	}
}

//// FORCEFIELD TELEPORT ENERGIZED
void Puzzle_3_3()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ linkGrid->Get_Cols() / 2,3 });
		blastP1.Get_Ammo_Manager().Set_Ammo(0);
		gCurrPuzzleStepMax = 12;

		ConsoleRender::Add_String("TELEPORTATION SHOT", { (Find_Ctr_X((int)std::size("TELEPORTATION SHOT")) / 2) / 2, (gConHeight / 2) / 2 }, BRIGHT_WHITE, TXT_SPD_DR, 1);
		ConsoleRender::Add_String("(Shoot, then spacebar)", { (Find_Ctr_X((int)std::size("(Shoot , then spacebar)")) / 2) / 2 , (gConHeight / 2) / 2 + 2 }, WHITE, TXT_SPD_DR, 1);
		
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() / 2,0 }, DOWN, 1, WallType::ENERGIZED);

		linkGrid->link[linkGrid->Get_Cols() / 2][linkGrid->Get_Rows() - 6 - 1].Activate_Lonely_Link(Modifier::FORCEFIELD);
		linkGrid->link[linkGrid->Get_Cols() / 2][linkGrid->Get_Rows() - 5].Activate_Lonely_Link(Modifier::REGULAR);
		linkGrid->link[linkGrid->Get_Cols() / 2][linkGrid->Get_Rows() - 4].Activate_Lonely_Link(Modifier::REGULAR);
		linkGrid->link[linkGrid->Get_Cols() / 2][linkGrid->Get_Rows() - 3].Activate_Lonely_Link(Modifier::REGULAR);

		gGrids.Activate_Link({ linkGrid->Get_Cols() / 2 , linkGrid->Get_Rows() - 2 }, Modifier::BUFFER);

		for (short r = 0; r < 6; r++)
		{
			gGrids.Activate_Link({ linkGrid->Get_Cols() / 2 - 1 , linkGrid->Get_Rows() - 1 - r }, Modifier::BLOCKER);
			gGrids.Activate_Link({ linkGrid->Get_Cols() / 2 + 1 , linkGrid->Get_Rows() - 1 - r }, Modifier::BLOCKER);
		}



		for (short c = 3; c < 4; c++)
		{
			gGrids.Activate_Link({ linkGrid->Get_Cols() / 2 - 1 + c, linkGrid->Get_Rows() - 6 - 1 }, Modifier::BLOCKER);
			gGrids.Activate_Link({ linkGrid->Get_Cols() / 2 + 1 - c, linkGrid->Get_Rows() - 6 - 1 }, Modifier::BLOCKER);
		}
		break;


	case 1:
		Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 2);
		Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() - 2);
		break;

	case 2:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}

// Respostionnement avec les forcefield. Forcefield transfer #1
void Puzzle_3_4()
{
	int start = 4;
	int numWalls = 6;

	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ start + numWalls + 1,7 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(0);		// Quantité d'ammo
		gCurrPuzzleStepMax = 12;


		for (short c = 0; c < linkGrid->Get_Cols(); c++)
		{
			gGrids.Activate_Link({ c, 5 }, Modifier::BLOCKER);
			gGrids.Activate_Link({ c, 9 }, Modifier::BLOCKER);
		}

		gGrids.Activate_Link({ linkGrid->Get_Cols() - 1, 8 }, Modifier::BLOCKER); // tip
		gGrids.Activate_Link({ linkGrid->Get_Cols() - 1, 7 }, Modifier::BLOCKER); // tip
		gGrids.Activate_Link({ linkGrid->Get_Cols() - 1, 6 }, Modifier::BLOCKER); // tip
		gGrids.Activate_Link({ 0, 6 }, Modifier::BLOCKER); // tip
		gGrids.Activate_Link({ 0, 8 }, Modifier::BLOCKER); // tip

		/*linkGrid->link[linkGrid->Get_Cols() / 2][linkGrid->Get_Rows() / 2 - 1].Activate_Lonely_Link(Modifier::FORCEFIELD);
		linkGrid->link[linkGrid->Get_Cols() / 2][linkGrid->Get_Rows() / 2].Activate_Lonely_Link(Modifier::FORCEFIELD);
		linkGrid->link[linkGrid->Get_Cols() / 2][linkGrid->Get_Rows() / 2 + 1].Activate_Lonely_Link(Modifier::FORCEFIELD);*/


		gGrids.Make_Chain_Of_Walls({ start , linkGrid->Get_Rows() / 2 }, RIGHT, numWalls, WallType::REGULAR, Modifier::REGULAR);
		linkGrid->link[linkGrid->Get_Cols() / 2 + numWalls][linkGrid->Get_Rows() / 2].Activate_Lonely_Link(Modifier::BUFFER);
		break;


	case 1:Add_Spec(UP, start + numWalls - 1 - 1); skip = 3; break;
	case 2:
		Add_Spec(UP, start + numWalls - 1 - 1);
		Add_Spec(DOWN, start + numWalls - 1 - 1);
		skip = 2; break;

	case 3:Add_Spec(UP, start + numWalls - 3 - 1); skip = 3;break;
	case 4:
		Add_Spec(UP, start + numWalls - 3 - 1);
		Add_Spec(DOWN, start + numWalls - 3 - 1);
		skip = 3; break;

	case 5:Add_Spec(UP, start + numWalls - 5 - 1); skip = 2; break;
	case 6:
		Add_Spec(UP, 0);
		Add_Spec(DOWN, 0);
		break;

	case 8:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}

// Teleporting madness, Super fast
void Puzzle_3_5()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 1,2 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(0);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;
		Cancel_Checkpoint_Delay();

		for (short r = 0; r < 13; r++)
		{
			gGrids.Activate_Link({ 3,r }, Modifier::BLOCKER);
		}

		for (short r = 14; r > 1; r--)
		{
			gGrids.Activate_Link({ 8,r }, Modifier::BLOCKER);
		}

		for (short r = 0; r < 13; r++)
		{
			gGrids.Activate_Link({ 13,r }, Modifier::BLOCKER);
		}

		for (short r = 14; r > 1; r--)
		{
			gGrids.Activate_Link({ 18,r }, Modifier::BLOCKER);
		}

		for (short r = 0; r < 6; r++)
		{
			gGrids.Activate_Link({ 22,r }, Modifier::BLOCKER);
			gGrids.Activate_Link({ 23,r }, Modifier::BLOCKER);
			gGrids.Activate_Link({ 24,r }, Modifier::BLOCKER);

			gGrids.Activate_Link({ 22,14 - r }, Modifier::BLOCKER);
			gGrids.Activate_Link({ 23,14 - r }, Modifier::BLOCKER);
			gGrids.Activate_Link({ 24,14 - r }, Modifier::BLOCKER);
		}

		gGrids.Activate_Link({ 1,14 }, Modifier::REGULAR);
		gGrids.Activate_Link({ 6,13 }, Modifier::REGULAR);
		gGrids.Activate_Link({ 5,0 }, Modifier::REGULAR);
		gGrids.Activate_Link({ 11,1 }, Modifier::REGULAR);
		gGrids.Activate_Link({ 10,14 }, Modifier::REGULAR);
		gGrids.Activate_Link({ 16,13 }, Modifier::REGULAR);
		gGrids.Activate_Link({ 15,0 }, Modifier::REGULAR);
		gGrids.Activate_Link({ 21,1 }, Modifier::REGULAR);
		gGrids.Activate_Link({ 20,8 }, Modifier::REGULAR);
		gGrids.Activate_Link({ 26,7 }, Modifier::REGULAR);

		for (short i = 0; i < 2; i++)
		{


			linkGrid->link[3][13 + i].Activate_Lonely_Link(Modifier::FORCEFIELD);
			linkGrid->link[8][0 + i].Activate_Lonely_Link(Modifier::FORCEFIELD);
			linkGrid->link[13][13 + i].Activate_Lonely_Link(Modifier::FORCEFIELD);
			linkGrid->link[18][0 + i].Activate_Lonely_Link(Modifier::FORCEFIELD);
			linkGrid->link[23][6 + i].Activate_Lonely_Link(Modifier::FORCEFIELD);
		}
		linkGrid->link[23][8].Activate_Lonely_Link(Modifier::FORCEFIELD);


		gGrids.Activate_Link({ 10, 1 }, Modifier::REGULAR, 1);
		gGrids.Activate_Link({ 10, 13 }, Modifier::REGULAR, 1);
		gGrids.Activate_Link({ 5, 13 }, Modifier::REGULAR, 1);
		gGrids.Activate_Link({ 5, 1 }, Modifier::REGULAR, 1);
		gGrids.Activate_Link({ 1, 13 }, Modifier::REGULAR, 1);
		gGrids.Activate_Link({ 15, 13 }, Modifier::REGULAR, 1);
		gGrids.Activate_Link({ 15, 1 }, Modifier::REGULAR, 1);
		gGrids.Activate_Link({ 20, 1 }, Modifier::REGULAR, 1);
		gGrids.Activate_Link({ 20, 7 }, Modifier::REGULAR, 1);
		gGrids.Activate_Link({ 25, 7 }, Modifier::REGULAR, 1);


		gGrids.Make_Chain_Of_Walls({ 1,0 }, DOWN, 1, WallType::ENERGIZED);


		MsgQueue::Register(ENABLE_BLAST);
		break;


	case 1:skip = 8;break;
	case 2:Add_Spec(UP, 25); instantSpawn = true; break;
	case 3:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}


// Place walls correctly #1
void Puzzle_3_6()
{

	static GrdCoord center = { linkGrid->Get_Cols() / 2, 7 };
	static int distance = 2;
	static bool puzzleSolved;
	static int wallsToConvert;
	static int wallsPlacedIncorrectly;

	static GrdCoord coorectWallPlacement[] = {
		center.c,center.r - distance,
		center.c ,center.r + distance,
		center.c - distance , center.r + 1,
		center.c - distance,center.r - 1,
	};

	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ center.c ,center.r - 1 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(0);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;

		Ev_Take_Your_Time();

		gGrids.Activate_Link(center, Modifier::FORCEFIELD);
		gGrids.Activate_Link({ center.c - 1,center.r }, Modifier::FORCEFIELD);
		gGrids.Activate_Link({ center.c + 1,center.r }, Modifier::FORCEFIELD);

		//up 
		for (int c = center.c - distance; c < center.c + distance + 1; c++)
		{
			for (GrdCoord coord : coorectWallPlacement)
			{
				if (Are_Equal({ c, center.r - distance }, coord))
				{
					gGrids.Make_Chain_Of_Walls({ c, center.r - distance }, UP, 1, WallType::ENERGIZED);
					break;
				}
			}

			gGrids.Make_Chain_Of_Walls({ c, center.r - distance }, UP, 1, WallType::WEAK);
		}

		//down
		for (int c = center.c - distance; c < center.c + distance + 1; c++)
		{
			for (GrdCoord coord : coorectWallPlacement)
			{
				if (Are_Equal({ c, center.r + distance }, coord))
				{
					gGrids.Make_Chain_Of_Walls({ c, center.r + distance }, DOWN, 1, WallType::ENERGIZED);
					break;
				}
			}

			gGrids.Make_Chain_Of_Walls({ c, center.r + distance }, DOWN, 1, WallType::WEAK);
		}

		// Left 
		for (int r = center.r - distance; r < center.r + distance + 1; r++)
		{
			for (GrdCoord coord : coorectWallPlacement)
			{
				if (Are_Equal({ center.c - distance, r }, coord))
				{
					gGrids.Make_Chain_Of_Walls({ center.c - distance, r }, LEFT, 1, WallType::ENERGIZED);
					break;
				}
			}

			gGrids.Make_Chain_Of_Walls({ center.c - distance, r }, LEFT, 1, WallType::WEAK);
		}

		// right
		for (int r = center.r - distance; r < center.r + distance + 1; r++)
		{

			for (GrdCoord coord : coorectWallPlacement)
			{
				if (Are_Equal({ center.c + distance, r }, coord))
				{
					gGrids.Make_Chain_Of_Walls({ center.c + distance, r }, RIGHT, 1, WallType::ENERGIZED);
					break;
				}
			}

			gGrids.Make_Chain_Of_Walls({ center.c + distance, r }, RIGHT, 1, WallType::WEAK);
		}

		gGrids.Make_Chain_Of_Walls({ center.c - 1, center.r + distance }, UP, 1, WallType::ENERGIZED);
		gGrids.Make_Chain_Of_Walls({ center.c - 1, center.r - distance }, DOWN, 1, WallType::ENERGIZED);
		gGrids.Make_Chain_Of_Walls({ center.c + 1,	  center.r - distance }, DOWN, 1, WallType::ENERGIZED);
		gGrids.Make_Chain_Of_Walls({ center.c + distance, center.r + 1 }, LEFT, 1, WallType::ENERGIZED);

		puzzleSolved = false;
		P1.Reset_Hp_And_Heart(1);
		break;


	case 1:skip = 10;break;
	case 2:

		wallsToConvert = 0;
		wallsPlacedIncorrectly = 0;

		// Complete old garbage 		
		for (GrdCoord coord : coorectWallPlacement)
		{
			if (linkGrid->link[coord.c][coord.r].Get_Num_Child() < 2) //Check si les murs convert sont bien placés
				wallsPlacedIncorrectly++;
			else
				if (linkGrid->link[coord.c][coord.r].Get_Child(0)->Get_Type() == WallType::WEAK || linkGrid->link[coord.c][coord.r].Get_Child(1)->Get_Type() == WallType::WEAK)
					wallsToConvert++; //Check si les murs sont bien convert
		}


		if (!wallsToConvert && !wallsPlacedIncorrectly && !blastP1.Is_Active())
		{
			puzzleSolved = true;
			Cancel_Ev_Take_Your_Time();
		}
		else
			gCurrPuzzleStep--;
		break;

	case 3:
		Add_Spec(RIGHT, 5);
		Add_Spec(UP, 11);
		Add_Spec(DOWN, 11);
		Add_Spec(LEFT, 8);
		break;

	case 4:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}
// Initialisation au weak walls
void Puzzle_3_7()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 6,7 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(0);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;


		for (short r = 0; r < linkGrid->Get_Rows(); r++)
			gGrids.Activate_Link({ linkGrid->Get_Cols() / 2, r }, Modifier::FORCEFIELD);


		gGrids.Make_Chain_Of_Walls({ 0, 5 }, RIGHT, 3, WallType::WEAK);
		gGrids.Make_Chain_Of_Walls({ 0, 11 }, RIGHT, 3, WallType::REGULAR);
		gGrids.Activate_Link({ linkGrid->Get_Cols() - 1, 5 });
		break;

	case 1:	skip = 3; break;
	case 2:	Add(3);Set_Interval(UP, 0, 3); skip = 15;break;
	case 3:	Add(3);Set_Interval(DOWN, linkGrid->Get_Cols() - 4, linkGrid->Get_Cols() - 1);break;
	case 4:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}

//// FORCEFIELD TELEPORT WEAK WALLs
void Puzzle_3_8()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ linkGrid->Get_Cols() / 2 - 1,5 });
		blastP1.Get_Ammo_Manager().Set_Ammo(1);
		gCurrPuzzleStepMax = 12;


		linkGrid->link[linkGrid->Get_Cols() / 2][linkGrid->Get_Rows() - 6].Activate_Lonely_Link(Modifier::FORCEFIELD);
		linkGrid->link[linkGrid->Get_Cols() / 2][linkGrid->Get_Rows() - 4].Activate_Lonely_Link(Modifier::REGULAR);

		gGrids.Activate_Link({ linkGrid->Get_Cols() / 2 , linkGrid->Get_Rows() - 2 }, Modifier::BUFFER);

		for (short r = 0; r < 5; r++)
		{
			gGrids.Activate_Link({ linkGrid->Get_Cols() / 2 - 1 - 3, linkGrid->Get_Rows() - 1 - r }, Modifier::BLOCKER);
			gGrids.Activate_Link({ linkGrid->Get_Cols() / 2 + 1 + 3, linkGrid->Get_Rows() - 1 - r }, Modifier::BLOCKER);
		}


		for (short c = 0; c < 4; c++)
		{
			gGrids.Activate_Link({ linkGrid->Get_Cols() / 2 - 1 - 3 + c, linkGrid->Get_Rows() - 6 }, Modifier::BLOCKER);
			gGrids.Activate_Link({ linkGrid->Get_Cols() / 2 + 1 + 3 - c, linkGrid->Get_Rows() - 6 }, Modifier::BLOCKER);
		}

		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols()  / 2 - 3, 5 }, RIGHT, 1,WallType::WEAK);

		gGrids.Activate_Link({ linkGrid->Get_Cols() / 2 + 5, 5});
		gGrids.Activate_Link({ linkGrid->Get_Cols() / 2 - 10 + 1, 5});
		gGrids.Activate_Link({ linkGrid->Get_Cols() / 2 - 8, 2});
		gGrids.Activate_Link({ linkGrid->Get_Cols() - 4 , 2 + 1});
		gGrids.Activate_Link({ linkGrid->Get_Cols() - 4 - 1 , linkGrid->Get_Rows() - 6 });
		gGrids.Activate_Link({ linkGrid->Get_Cols() / 2 - 1 , linkGrid->Get_Rows() - 7 });
		break;


	case 1:
		Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 4);
		skip = 2;
		break;

	case 2:
		Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 2);
		Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() - 2);
		break;

	case 3:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}


// Respostionnement avec les forcefield. Forcefield transfer #2
void Puzzle_3_9()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 10,7 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(0);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;


		// Version vertical
		//for (short c = 11; c < 16; c++)
		//{
		//	gGrids.Activate_Link({ c, 7 }, Modifier::FORCEFIELD);
		//	gGrids.Activate_Link({ c, 7 }, Modifier::FORCEFIELD);
		//}


		//for (short r = 0; r < 15; r++)
		//{
		//	gGrids.Activate_Link({ 10, r }, Modifier::BLOCKER);
		//	gGrids.Activate_Link({ 16, r }, Modifier::BLOCKER);
		//}



		//gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() / 2, 0 }, DOWN, 5);
		//gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() / 2, linkGrid->Get_Rows() - 1 }, UP, 4);
		//linkGrid->link[linkGrid->Get_Cols() / 2][linkGrid->Get_Rows() / 2].Activate_Lonely_Link(Modifier::FORCEFIELD);


		// Version horizontal
		for (short c = 0; c < linkGrid->Get_Cols(); c++)
		{
			gGrids.Activate_Link({ c, 5 }, Modifier::BLOCKER);
			gGrids.Activate_Link({ c, 9 }, Modifier::BLOCKER);
		}

		gGrids.Activate_Link({ linkGrid->Get_Cols() - 1, 8 }, Modifier::BLOCKER); // tip
		gGrids.Activate_Link({ linkGrid->Get_Cols() - 1, 6 }, Modifier::BLOCKER); // tip
		gGrids.Activate_Link({ 0, 6 }, Modifier::BLOCKER); // tip
		gGrids.Activate_Link({ 0, 8 }, Modifier::BLOCKER); // tip

		linkGrid->link[linkGrid->Get_Cols() / 2][linkGrid->Get_Rows() / 2 - 1].Activate_Lonely_Link(Modifier::FORCEFIELD);
		linkGrid->link[linkGrid->Get_Cols() / 2][linkGrid->Get_Rows() / 2].Activate_Lonely_Link(Modifier::FORCEFIELD);
		linkGrid->link[linkGrid->Get_Cols() / 2][linkGrid->Get_Rows() / 2 + 1].Activate_Lonely_Link(Modifier::FORCEFIELD);


		gGrids.Make_Chain_Of_Walls({ 4 , linkGrid->Get_Rows() / 2 }, RIGHT, 5,WallType::ENERGIZED);
		gGrids.Make_Chain_Of_Walls({ 20, linkGrid->Get_Rows() / 2 }, LEFT, 4, WallType::ENERGIZED);
		break;


	case 1:Add_Spec(UP, 14); skip = 3;break;
	case 2:Add_Spec(UP, 8);	 skip = 5;break;
	case 3:Add_Spec(UP, 14); skip = 5;break;
	case 4:Add_Spec(UP, 8);  skip = 6;break;
	case 5:Add_Spec(UP, 15); skip = 6;break;
	case 6:
		Add_Spec(UP, 2);
		Add_Spec(UP, 3);
		skip = 6;
		break;

	case 7:
		Add_Spec(UP, 25);  
		Add_Spec(UP, 24);  
		break;

	case 8:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}



void Puzzle_3_10()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 1,2 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(1);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;
		Cancel_Checkpoint_Delay();



		for (short r = 0; r < 13; r++)
		{
			if (r != 7)
			{
				gGrids.Activate_Link({ 2,r }, Modifier::BLOCKER);
				gGrids.Activate_Link({ 3,r }, Modifier::BLOCKER);
				gGrids.Activate_Link({ 4,r }, Modifier::BLOCKER);
			}
		}

		for (short r = 14; r > 1; r--)
		{
			if (r != 7)
			{
				gGrids.Activate_Link({ 7,r }, Modifier::BLOCKER);
				gGrids.Activate_Link({ 8,r }, Modifier::BLOCKER);
				gGrids.Activate_Link({ 9,r }, Modifier::BLOCKER);
			}
		}

		for (short r = 0; r < 13; r++)
		{
			if (r != 7)
			{
				gGrids.Activate_Link({ 12,r }, Modifier::BLOCKER);
				gGrids.Activate_Link({ 13,r }, Modifier::BLOCKER);
				gGrids.Activate_Link({ 14,r }, Modifier::BLOCKER);
			}
		}

		for (short r = 14; r > 1; r--)
		{
			if (r != 7)
			{
				gGrids.Activate_Link({ 17,r }, Modifier::BLOCKER);
				gGrids.Activate_Link({ 18,r }, Modifier::BLOCKER);
				gGrids.Activate_Link({ 19,r }, Modifier::BLOCKER);
			}
		}

		for (short r = 0; r < 6; r++)
		{
			if (r != 7)
			{
				gGrids.Activate_Link({ 22,r }, Modifier::BLOCKER);
				gGrids.Activate_Link({ 23,r }, Modifier::BLOCKER);
				gGrids.Activate_Link({ 24,r }, Modifier::BLOCKER);

				gGrids.Activate_Link({ 22,14 - r }, Modifier::BLOCKER);
				gGrids.Activate_Link({ 23,14 - r }, Modifier::BLOCKER);
				gGrids.Activate_Link({ 24,14 - r }, Modifier::BLOCKER);
			}
		}

		gGrids.Activate_Link({ 0,7 },  Modifier::REGULAR);
		gGrids.Activate_Link({ 1,14 }, Modifier::BLOCKER);
		gGrids.Activate_Link({ 6,13 }, Modifier::BLOCKER);
		gGrids.Activate_Link({ 5,0 },  Modifier::BLOCKER);
		gGrids.Activate_Link({ 11,1 }, Modifier::BLOCKER);
		gGrids.Activate_Link({ 10,14 },Modifier::BLOCKER);
		gGrids.Activate_Link({ 16,13 },Modifier::BLOCKER);
		gGrids.Activate_Link({ 15,0 }, Modifier::BLOCKER);
		gGrids.Activate_Link({ 21,1 }, Modifier::BLOCKER);
		gGrids.Activate_Link({ 20,8 }, Modifier::BLOCKER);

		

		for (short r = 0; r < linkGrid->Get_Rows(); r++)
			for (short c = 0; c < linkGrid->Get_Cols(); c++)
			{
				if (!linkGrid->Is_Link_Alive_Here({ c,r }))
					if (!(c == 1 && r <  3) && (r != 7))
						gGrids.Activate_Link({ c,r }, Modifier::FORCEFIELD);
			}

		gGrids.Activate_Link({ 1,  3 }, Modifier::REGULAR, 1);
		gGrids.Activate_Link({ 10, 1 }, Modifier::REGULAR, 1);
		gGrids.Activate_Link({ 10, 13 },Modifier::REGULAR, 1);
		gGrids.Activate_Link({ 5, 13 }, Modifier::REGULAR, 1);
		gGrids.Activate_Link({ 5, 1 },  Modifier::REGULAR, 1);
		gGrids.Activate_Link({ 1, 13 }, Modifier::REGULAR, 1);
		gGrids.Activate_Link({ 15, 13 },Modifier::REGULAR, 1);
		gGrids.Activate_Link({ 15, 1 }, Modifier::REGULAR, 1);
		gGrids.Activate_Link({ 20, 1 }, Modifier::REGULAR, 1);
		gGrids.Activate_Link({ 20, 7 }, Modifier::REGULAR, 1);
		gGrids.Activate_Link({ 25, 7 }, Modifier::REGULAR, 1);
		gGrids.Activate_Link({ 26, 7 }, Modifier::REGULAR, 1);

		gGrids.Make_Chain_Of_Walls({ 1,0 }, DOWN, 1, WallType::ENERGIZED);

		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 1, 3 });
		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 26, 7 });
		MsgQueue::Register(ENABLE_BLAST);
		break;


	case 1:skip = 5;break;
	case 2:Add_Spec(UP, 0);Add_Spec(DOWN, 0); break;
	case 3:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}



// Place walls correctly #2
void Puzzle_3_11()
{
	static GrdCoord center = { linkGrid->Get_Cols() / 2, 7 };
	static int distance = 2;
	static bool puzzleSolved;
	static int wallsToConvert;
	static int wallsPlacedIncorrectly;
	static GrdCoord coorectWallPlacement[] = {
		center.c,center.r - distance,
		center.c - 1,center.r - distance,
		center.c + 1,center.r - distance,
		center.c - distance ,center.r + 1 ,
		center.c + distance ,center.r ,
		center.c + 1 , center.r + distance,
		center.c , center.r + distance
	};

	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ linkGrid->Get_Cols() / 2 - 1,7 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(0);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;

		Ev_Take_Your_Time();
		gGrids.Activate_Link(center, Modifier::FORCEFIELD);

		//up 
		for (int c = center.c - distance; c < center.c + distance + 1; c++)
		{
			for (GrdCoord coord : coorectWallPlacement)
			{
				if (Are_Equal({ c, center.r - distance }, coord))
				{
					gGrids.Make_Chain_Of_Walls({ c, center.r - distance }, UP, 1, WallType::REGULAR);
					break;
				}
			}

			gGrids.Make_Chain_Of_Walls({ c, center.r - distance }, UP, 1, WallType::WEAK);
		}

		//down
		for (int c = center.c - distance; c < center.c + distance + 1; c++)
		{
			for (GrdCoord coord : coorectWallPlacement)
			{
				if (Are_Equal({ c, center.r + distance }, coord))
				{
					gGrids.Make_Chain_Of_Walls({ c, center.r + distance }, DOWN, 1, WallType::REGULAR);
					break;
				}
			}

			gGrids.Make_Chain_Of_Walls({ c, center.r + distance }, DOWN, 1, WallType::WEAK);
		}

		// Left 
		for (int r = center.r - distance; r < center.r + distance + 1; r++)
		{
			for (GrdCoord coord : coorectWallPlacement)
			{
				if (Are_Equal({ center.c - distance, r }, coord))
				{
					gGrids.Make_Chain_Of_Walls({ center.c - distance, r }, LEFT, 1, WallType::REGULAR);
					break;
				}
			}

			gGrids.Make_Chain_Of_Walls({ center.c - distance, r }, LEFT, 1, WallType::WEAK);
		}

		// right
		for (int r = center.r - distance; r < center.r + distance + 1; r++)
		{

			for (GrdCoord coord : coorectWallPlacement)
			{
				if (Are_Equal({ center.c + distance, r }, coord))
				{
					gGrids.Make_Chain_Of_Walls({ center.c + distance, r }, RIGHT, 1, WallType::REGULAR);
					break;
				}
			}

			gGrids.Make_Chain_Of_Walls({ center.c + distance, r }, RIGHT, 1, WallType::WEAK);
		}

		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() / 2, 7 - 2 }, DOWN, 1, WallType::WEAK);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() / 2, 7 + 2 }, UP, 1, WallType::WEAK);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() / 2 + 2, 7 }, LEFT, 1, WallType::WEAK);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() / 2 + 2, 7 - 1 }, LEFT, 1, WallType::WEAK);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() / 2 - 2, 7 - 1 }, RIGHT, 1, WallType::WEAK);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() / 2 + 2, 7 + 1 }, LEFT, 1, WallType::WEAK);
		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() / 2 - 2, 7 + 1 }, RIGHT, 1, WallType::WEAK);

		puzzleSolved = false;
		P1.Reset_Hp_And_Heart(1);
		break;


	case 1:skip = 10;break;
	case 2:

		wallsToConvert = 0;
		wallsPlacedIncorrectly = 0;

		// Complete old garbage 		
		for (GrdCoord coord : coorectWallPlacement)
		{
			if (linkGrid->link[coord.c][coord.r].Get_Num_Child() < 2) //Check si les murs convert sont bien placés
				wallsPlacedIncorrectly++;
			else
				if (linkGrid->link[coord.c][coord.r].Get_Child(0)->Get_Type() == WallType::WEAK || linkGrid->link[coord.c][coord.r].Get_Child(1)->Get_Type() == WallType::WEAK)
					wallsToConvert++; //Check si les murs sont bien convert
		}


		if (!wallsToConvert && !wallsPlacedIncorrectly && !blastP1.Is_Active())
		{
			puzzleSolved = true;
			Cancel_Ev_Take_Your_Time();
		}
		else
			gCurrPuzzleStep--;
		break;
	
	case 3:
		Add_Spec(LEFT,5);Add_Spec(RIGHT, 5);
		Add_Spec(UP,11);
		Add_Spec(DOWN, 14);
		Add_Spec(LEFT, 8);Add_Spec(RIGHT, 8);
		break;

	case 4:Add_Spec(LEFT, 5);break;
	case 5:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}


/// HARD, keep a wall alive, pure speed #1
void Puzzle_3_12()
{

	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 5 , 9 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(21);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;


		gGrids.Make_Chain_Of_Walls({ 17, 3 }, LEFT, 12);

		for (int c = 0; c < 15; c++)
		{
			gGrids.Activate_Link({ 4 + c ,2}, Modifier::BLOCKER);
			
			if(c < 13)
			 gGrids.Activate_Link({ 6 + c, 4 }, Modifier::BLOCKER);
		}
		gGrids.Activate_Link({ 18, 3 }, Modifier::BLOCKER);//tip

		for (int r = 0; r < 8; r++)
		{
			gGrids.Activate_Link({ 4 , 3 + r }, Modifier::BLOCKER);

			if (r < 4)
				gGrids.Activate_Link({ 6, 5 + r }, Modifier::BLOCKER);
		}

		for (int c = 0; c < 18; c++)
		{
			gGrids.Activate_Link({ 4 + c , 10 }, Modifier::BLOCKER);

			if (c < 16)
				gGrids.Activate_Link({ 6 + c, 8 }, Modifier::BLOCKER);
		}
		gGrids.Activate_Link({ 21, 9 }, Modifier::BLOCKER);//tip
		break;

	case 1:Add_Spec(UP, 16); instantSpawn = true; break;
	case 2:Add_Spec(DOWN, 19);	break;
	case 3:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}


/// HARD, extract an energized wall from destruction
void Puzzle_3_13()
{

	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({2,11});				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(0);						// Quantité d'ammo
		gCurrPuzzleStepMax = 12;

		
		
		for (int c = 4; c < 27; c++)
		{
			gGrids.Activate_Link({ c , 5 }, Modifier::BLOCKER);
			gGrids.Activate_Link({ c , 9 }, Modifier::BLOCKER);
			gGrids.Activate_Link({ c , 11 }, Modifier::BLOCKER);
		}


		for (int r = 12; r < 15 ; r++)
			gGrids.Activate_Link({ 4, r }, Modifier::BLOCKER); 

		for (int r = 0; r < 5; r++)
			gGrids.Activate_Link({ 4, r }, Modifier::BLOCKER);

		for (int r = 8; r < 15; r++)
			gGrids.Activate_Link({ 0, r }, Modifier::BLOCKER);

		for (int c = 0; c < 5; c++)
			gGrids.Activate_Link({ c, 0 }, Modifier::BLOCKER);

		for (int c = 0; c < 5; c++)
			gGrids.Activate_Link({ c, 8 }, Modifier::FORCEFIELD);

		for (int r = 6; r < 9; r++)
			gGrids.Activate_Link({ 4, r }, Modifier::FORCEFIELD);



		gGrids.Activate_Link({ 4, 10 }, Modifier::FORCEFIELD);


		gGrids.Activate_Link({ 0, 7 }, Modifier::REGULAR);

		gGrids.Make_Chain_Of_Walls({ 3, 0 + 1 }, LEFT, 3, WallType::REGULAR);
		gGrids.Make_Chain_Of_Walls({ 0, 0 + 1 }, DOWN, 1, WallType::REGULAR);
		gGrids.Make_Chain_Of_Walls({ 0, 1 + 1 }, RIGHT,3 , WallType::REGULAR);
		gGrids.Make_Chain_Of_Walls({ 3, 1 + 1 }, DOWN, 1 , WallType::REGULAR);
		gGrids.Make_Chain_Of_Walls({ 3, 2 + 1 }, LEFT, 3 , WallType::REGULAR);
		gGrids.Make_Chain_Of_Walls({ 0, 2 + 1 }, DOWN, 1 , WallType::REGULAR);
		gGrids.Make_Chain_Of_Walls({ 0, 3 + 1 }, RIGHT, 3 , WallType::REGULAR);
		gGrids.Make_Chain_Of_Walls({ 3, 3 + 1 }, DOWN, 1 , WallType::REGULAR);
		gGrids.Make_Chain_Of_Walls({ 3, 4 + 1 }, LEFT, 3 , WallType::REGULAR);
		gGrids.Make_Chain_Of_Walls({ 0, 4 + 1 }, DOWN, 1 , WallType::REGULAR);
		gGrids.Make_Chain_Of_Walls({ 0, 5 + 1 }, RIGHT, 3 , WallType::REGULAR);
		gGrids.Make_Chain_Of_Walls({ 3, 5 + 1 }, DOWN, 1, WallType::ENERGIZED);

		gGrids.Make_Chain_Of_Walls({ 26, 8 }, UP, 2, WallType::REGULAR);
		gGrids.Make_Chain_Of_Walls({ 26, 6 }, LEFT, 12, WallType::REGULAR);
		gGrids.Make_Chain_Of_Walls({ 14, 6 }, DOWN, 2, WallType::REGULAR);
		gGrids.Make_Chain_Of_Walls({ 14, 8 }, RIGHT, 11, WallType::REGULAR);
		gGrids.Make_Chain_Of_Walls({ 25, 8 }, UP, 1, WallType::REGULAR);
		gGrids.Make_Chain_Of_Walls({ 25, 7 }, LEFT, 9, WallType::REGULAR);
		gGrids.Make_Chain_Of_Walls({ 16, 7 }, LEFT, 1, WallType::ENERGIZED);
		

		gGrids.Activate_Link({ 1, 12 }, Modifier::FORCEFIELD);
		gGrids.Activate_Link({ 2, 12 }, Modifier::FORCEFIELD);
		gGrids.Activate_Link({ 3, 12 }, Modifier::FORCEFIELD);		
		gGrids.Activate_Link({ 1, 13 }, Modifier::FORCEFIELD);
		gGrids.Activate_Link({ 2, 13 }, Modifier::FORCEFIELD);
		gGrids.Activate_Link({ 3, 13 }, Modifier::FORCEFIELD);

		gGrids.Activate_Link({ 1, 14 }, Modifier::REGULAR);
		gGrids.Activate_Link({ 2, 14 }, Modifier::REGULAR);
		gGrids.Activate_Link({ 3, 14 }, Modifier::REGULAR);
		
		gGrids.Make_Chain_Of_Walls({ 1, 11 }, UP, 1,WallType::WEAK);
		gGrids.Make_Chain_Of_Walls({ 3, 9 }, DOWN, 1,WallType::WEAK);
		gGrids.Activate_Link({ 2, 10 }, Modifier::REGULAR);

		
		gGrids.Make_Chain_Of_Walls({ 26, 10 }, LEFT, 5, WallType::REGULAR);
		gGrids.Make_Chain_Of_Walls({ 21, 10 }, LEFT, 1, WallType::ENERGIZED);

		//gGrids.Make_Box_Of_Blockers({ 0,0 }, { 3 , 14 });
		//Clear les links de trop
		/*for (int r = 0; r < 3; r++)
			gGrids.Activate_Link({ 3, 6 + r }, Modifier::REGULAR,1); */
		break;


	case 1:
		Add_Spec(UP, 2);
		Add_Spec(RIGHT, 7);
		Add_Spec(DOWN, 25);
		instantSpawn = 1; 
		skip = 4;
		break;

	case 2:Add_Spec(LEFT, 13); break;
	case 3:Add_Spec(LEFT, 13); break;
	case 4:Add_Spec(LEFT, 13);break;
	case 5:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}

void Puzzle_3_14()
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
void Puzzle_3_15()
{
	static GrdCoord crd;

	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ linkGrid->Get_Cols() / 2 ,7 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(10);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;
		Set_Dr_Map_1(TXT_SPD_DR * 4);  // Erase la border au cas où le joueur est pas en mode quickstartS

		crd = P1.Get_Grd_Coord();

		for (int c = -1; c < 2; c++)
			for (int r = -1; r < 2; r++)
			{
				if (!(c == 0 && r == 0))
					linkGrid->link[crd.c + c][crd.r + r].Activate_Lonely_Link(Modifier::FORCEFIELD);
			}

		break;


	case 1:	skip = 15; break;
	case 2:	break;
	case 3:	break;
	case 4:	break;
	case 5:	break;
	case 6:	break;
	case 7:	break;
	case 8:	break;
	case 9:	break;
	case 11:break;
	case 12:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}
void Puzzle_3_16()
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
void Puzzle_3_17()
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
void Puzzle_3_18() {
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


void Puzzle_3_19() {
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

void Puzzle_3_20() {
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

void Puzzle_3_21() {
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

void Puzzle_3_22() {
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

void Puzzle_3_FINAL()
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