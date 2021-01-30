

#include "lvl_3_spwn_script.h"
#include "../../time/spawn_cycle.h"
#include "../../grid/managegrids.h"
#include "../../spawns/bots_to_spawn.h"
#include "../../events/msg_dispatcher.h"
#include "../lvl_script.h"
#include "../../console/sweet_cmd_console.h"
#include "../../player/player.h"
#include "../../bots/botmeta.h"
#include "../../blast/mod_queue_animator.h"
#include "../../bots/botlist.h"

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
//void Puzzle_3_19();
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
//Puzzle_3_19,
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
		blastP1.Get_Ammo_Manager().Set_Ammo(7);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;

		for (int r = 0; r <= 14; r++)
		{
			for (int c = 0; c < 9; c++)
			{
				if (c < 3 || c > 5)
					gGrids.Activate_Link({ linkGrid->Get_Cols() / 2 - 4 + c,r }, Modifier::FORCEFIELD);
			}
		}

		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() / 2 , 3 }, DOWN, 7, WallType::ENERGIZED, Modifier::REGULAR);
		break;


	case 1:skip = 8;break;
	case 2:Add_Spec(UP, 0);Add_Spec(UP, 11); skip = 10;break;
	case 3:Add_Spec(UP, 14);Add_Spec(UP, 25);skip = 5;break;
	case 4:Add_Spec(UP, 0);Add_Spec(UP, 11); skip = 4;break;
	case 5:Add_Spec(UP, 14);Add_Spec(UP, 25);skip = 3;break;
	case 6:Add_Spec(UP, 0);Add_Spec(UP, 11); skip = 2;break;
	case 7:Add_Spec(UP, 14);Add_Spec(UP, 25);skip = 1;break;
	case 8:Add_Spec(UP, 0);Add_Spec(UP, 11); break;

	case 9:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}

// TELEPORTATION TUTORIAL
void Puzzle_3_1()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ linkGrid->Get_Cols() - 1, 14 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(1);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;

		// Very Temporary! Doit être remove
		ConsoleRender::Add_String(" TELEPORTATION SHOT", { (Find_Ctr_X((int)std::size(" TELEPORTATION SHOT")) / 2) / 2, (gConHeight / 2) / 2 }, BRIGHT_WHITE, TXT_SPD_DR);
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

//// Teleport pour placer des murs ensuite
void Puzzle_3_2()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ linkGrid->Get_Cols() / 2,5 });
		blastP1.Get_Ammo_Manager().Set_Ammo(7);
		gCurrPuzzleStepMax = 12;

		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() / 2,3 }, DOWN, 1, WallType::ENERGIZED);

		linkGrid->link[linkGrid->Get_Cols() / 2][7].Activate_Lonely_Link(Modifier::FORCEFIELD);

		for (short r = 0; r <= 10; r++)
		{
			gGrids.Activate_Link({ linkGrid->Get_Cols() / 2 + 1 , r }, Modifier::BLOCKER);
		}

		for (short r = 4; r <= 14; r++)
		{
			gGrids.Activate_Link({ linkGrid->Get_Cols() / 2 - 1  , r }, Modifier::BLOCKER);
		}

		for (short r = 10; r <= 14; r++)
		{
			gGrids.Activate_Link({ linkGrid->Get_Cols() / 2 + 3 , r }, Modifier::BLOCKER);
		}
		gGrids.Activate_Link({ linkGrid->Get_Cols() / 2 + 2 , 10 }, Modifier::BLOCKER);

		for (short r = 0; r <= 4; r++)
		{
			gGrids.Activate_Link({ linkGrid->Get_Cols() / 2 - 3 , r }, Modifier::BLOCKER);
		}
		gGrids.Activate_Link({ linkGrid->Get_Cols() / 2 - 2 , 4 }, Modifier::BLOCKER);



		for (short r = 0; r <= 4; r++)
		{
			gGrids.Activate_Link({ linkGrid->Get_Cols() / 2 - 2 , r }, Modifier::REGULAR);
			gGrids.Activate_Link({ linkGrid->Get_Cols() / 2 + 2 , 14 - r }, Modifier::REGULAR);
		}
		break;


	case 1:	Add_Spec(DOWN, 14);	break;
	case 2:	Add_Spec(DOWN, 14);	break;
	case 3:	Add_Spec(DOWN, 14);	break;
	case 4:	Add_Spec(DOWN, 14); skip = 4;break;
	case 5:	Add_Spec(UP, 11);	break;
	case 6:	Add_Spec(UP, 11);	break;
	case 7:	Add_Spec(UP, 11);	break;
	case 8:	Add_Spec(UP, 11);	break;
	case 9:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}

// Teleporting madness, Super fast
void Puzzle_3_3()
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


	case 1:skip = 12;break;
	case 2:Add_Spec(UP, 25); instantSpawn = true; break;
	case 3:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}

// Respostionnement avec les forcefield. Forcefield transfer #2
void Puzzle_3_4()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 10,7 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(0);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;

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


		gGrids.Make_Chain_Of_Walls({ 4 , linkGrid->Get_Rows() / 2 }, RIGHT, 5, WallType::ENERGIZED);
		gGrids.Make_Chain_Of_Walls({ 20, linkGrid->Get_Rows() / 2 }, LEFT, 4, WallType::ENERGIZED);
		break;


	case 1:Add_Spec(UP, 14); skip = 5;break;
	case 2:Add_Spec(UP, 8);	 skip = 6;break;
	case 3:Add_Spec(UP, 14); skip = 9;break;
	case 4:Add_Spec(UP, 8);  skip = 10;break;
	case 5:Add_Spec(UP, 15); skip = 9;break;
	case 6:
		Add_Spec(UP, 0);
		Add_Spec(UP, 1);
		Add_Spec(UP, 2);
		Add_Spec(UP, 3);
		break;

	case 7:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}

// Initialisation au weak walls
void Puzzle_3_5()
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
void Puzzle_3_6()
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
		for (short c = 0; c <= 26; c++)
		{
			gGrids.Activate_Link({ c, 0 }, Modifier::BLOCKER);
			gGrids.Activate_Link({ c, 14 }, Modifier::BLOCKER);
		}

		for (short c = 0; c < 4; c++)
		{
			gGrids.Activate_Link({ linkGrid->Get_Cols() / 2 - 1 - 3 + c, linkGrid->Get_Rows() - 6 }, Modifier::BLOCKER);
			gGrids.Activate_Link({ linkGrid->Get_Cols() / 2 + 1 + 3 - c, linkGrid->Get_Rows() - 6 }, Modifier::BLOCKER);
		}

		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() / 2 - 3, 5 }, RIGHT, 1, WallType::WEAK);

		gGrids.Activate_Link({ linkGrid->Get_Cols() / 2 + 5, 5 });
		gGrids.Activate_Link({ linkGrid->Get_Cols() / 2 - 10 + 1, 5 });
		gGrids.Activate_Link({ linkGrid->Get_Cols() / 2 - 8, 2 });
		gGrids.Activate_Link({ linkGrid->Get_Cols() - 4 , 2 + 1 });
		gGrids.Activate_Link({ linkGrid->Get_Cols() - 4 - 1 , linkGrid->Get_Rows() - 6 });
		gGrids.Activate_Link({ linkGrid->Get_Cols() / 2 - 1 , linkGrid->Get_Rows() - 7 });
		break;


	case 1:
		Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 4);
		instantSpawn = true;
		skip = 2;
		break;

	case 2:
		instantSpawn = true;
		Add_Spec(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 2);
		Add_Spec(RIGHT, spawnGrid->Get_MaxSpwnCrdY() - 2);
		break;

	case 3:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}


//  No extra ammo. Solve this puzzle #1
void Puzzle_3_7()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 15,9 });									// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(2);							// Quantité d'ammo
		blastP1.Get_Ammo_Manager().Set_Nb_Emergency_Ammo(0);			// EXCEPTIONNAL

		gCurrPuzzleStepMax = 12;

		gGrids.Make_Chain_Of_Walls({ 14,5 }, LEFT, 1, WallType::WEAK);
		gGrids.Make_Chain_Of_Walls({ 14,9 }, UP, 1, WallType::WEAK);

		gGrids.Make_Box_Of_Blockers({ 11,4 }, { 17,10 });

		for (int c = 11; c < 17; c++)
			gGrids.Activate_Link({ c, 7 }, Modifier::FORCEFIELD);
		break;


	case 1:skip = 7;break;
	case 2:
		Add_Spec(LEFT, 5);
		Add_Spec(LEFT, 6);
		Add_Spec(RIGHT, 7);
		Add_Spec(RIGHT, 8);
		break;

	case 3:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}

// Intro au laisser passer dans les walls pour activer
void Puzzle_3_8() {
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 4, 2 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(3);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;

		gGrids.Make_Box_Of_Blockers({ 0,0 }, { 26,14 });

		gGrids.Make_Chain_Of_Walls({ 2 , 2 }, RIGHT, 1, WallType::WEAK);
		gGrids.Activate_Link({ 2 , 3 });

		gGrids.Activate_Link({ 24, 2 });
		gGrids.Make_Chain_Of_Walls({ 24 , 3 }, LEFT, 1, WallType::WEAK);
		gGrids.Activate_Link({ 24, 4 });

		gGrids.Activate_Link({ 23 , 12 });
		gGrids.Make_Chain_Of_Walls({ 22 , 12 }, UP, 1, WallType::WEAK);
		gGrids.Activate_Link({ 21 , 12 });

		gGrids.Activate_Link({ 2 , 11 });
		break;

	case  1:Add_Spec(UP, 2);skip = 5;break;
	case  2:Add_Spec(UP, 23);skip = 1;break;
	case  3:Add_Spec(UP, 23);skip = 3;break;
	case  4:Add_Spec(RIGHT, 11);break;
	case  5:Add_Spec(RIGHT, 11);skip = 7;break;
	case  6:Add_Spec(DOWN, 2);break;
	case 13:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}


void Puzzle_3_9()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({13 , 2});				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(2);					// Quantité d'ammo
		gCurrPuzzleStepMax = 12;


		gGrids.Make_Chain_Of_Walls({13, 0 }, DOWN, 1, WallType::ENERGIZED);

		for (int d = 0; d <= 13; d++)
		{
			gGrids.Activate_Link({ 12, d  }, Modifier::BLOCKER);
			gGrids.Activate_Link({ 14, d  }, Modifier::BLOCKER);
		}
		for (int r = 9; r <= 13; r++)
		{
			gGrids.Activate_Link({ 13, r });
		}

		for (int c = 0; c <= 26; c++)
		{
			if(c != 13)
				gGrids.Activate_Link({ c, 13 }, Modifier::BLOCKER);
		}

		gGrids.Activate_Link({ 13,  7}, Modifier::FORCEFIELD);
		break;

	case 1: skip = 2;break;
	case 2:
		Add_Spec(UP, 0);
		Add_Spec(UP, 25);
		break;
		
	case 3:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}



// Transfère de weak sur des doubles forcefield #1
void Puzzle_3_10()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 6,10 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(0);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;

		gGrids.Make_Chain_Of_Walls({ 16,3 }, DOWN, 1, WallType::WEAK);
		gGrids.Make_Chain_Of_Walls({ 16,4 }, LEFT, 1, WallType::WEAK);

		gGrids.Make_Chain_Of_Walls({ 15,4 }, DOWN, 1, WallType::WEAK);
		gGrids.Make_Chain_Of_Walls({ 15,5 }, LEFT, 1, WallType::WEAK);

		gGrids.Make_Chain_Of_Walls({ 14,5 }, DOWN, 1, WallType::WEAK);
		gGrids.Make_Chain_Of_Walls({ 14,6 }, LEFT, 1, WallType::WEAK);

		gGrids.Make_Chain_Of_Walls({ 13,6 }, DOWN, 1, WallType::WEAK);
		gGrids.Make_Chain_Of_Walls({ 13,7 }, LEFT, 1, WallType::WEAK);

		gGrids.Make_Chain_Of_Walls({ 12,7 }, DOWN, 1, WallType::WEAK);
		gGrids.Make_Chain_Of_Walls({ 12,8 }, LEFT, 1, WallType::WEAK);
		gGrids.Make_Chain_Of_Walls({ 11,8 }, DOWN, 1, WallType::WEAK);

		// up
		gGrids.Activate_Link({ 12, 0 }, Modifier::FORCEFIELD);
		gGrids.Activate_Link({ 12, 1 }, Modifier::FORCEFIELD);
		gGrids.Activate_Link({ 13, 2 }, Modifier::FORCEFIELD);
		gGrids.Activate_Link({ 13, 3 }, Modifier::FORCEFIELD);

		// right
		gGrids.Activate_Link({ 21, 8 }, Modifier::FORCEFIELD);
		gGrids.Activate_Link({ 20, 8 }, Modifier::FORCEFIELD);
		gGrids.Activate_Link({ 19, 5 }, Modifier::FORCEFIELD);
		gGrids.Activate_Link({ 18, 5 }, Modifier::FORCEFIELD);
		gGrids.Activate_Link({ 23, 4 }, Modifier::FORCEFIELD);
		gGrids.Activate_Link({ 24, 4 }, Modifier::FORCEFIELD);

		// DOwn
		gGrids.Activate_Link({ 11, 13 }, Modifier::FORCEFIELD);
		gGrids.Activate_Link({ 11, 14 }, Modifier::FORCEFIELD);
		gGrids.Activate_Link({ 13, 12 }, Modifier::FORCEFIELD);
		gGrids.Activate_Link({ 13, 13 }, Modifier::FORCEFIELD);
		gGrids.Activate_Link({ 14, 11 }, Modifier::FORCEFIELD);
		gGrids.Activate_Link({ 14, 12 }, Modifier::FORCEFIELD);

		// Left
		gGrids.Activate_Link({ 3, 8 }, Modifier::FORCEFIELD);
		gGrids.Activate_Link({ 4, 8 }, Modifier::FORCEFIELD);
		gGrids.Activate_Link({ 5, 5 }, Modifier::FORCEFIELD);
		gGrids.Activate_Link({ 6, 5 }, Modifier::FORCEFIELD);
		gGrids.Activate_Link({ 7, 4 }, Modifier::FORCEFIELD);
		gGrids.Activate_Link({ 8, 4 }, Modifier::FORCEFIELD);
		break;

	case 1:skip = 20;break;
	case 2:
		Add_Spec(LEFT, 13);
		Add_Spec(UP, 3);
		Add_Spec(DOWN, 20);
		Add_Spec(RIGHT, 0);
		Add_Spec(LEFT, 12);
		Add_Spec(RIGHT, 2);
		Add_Spec(LEFT, 11);
		Add_Spec(UP, 5);
		Add_Spec(DOWN, 18);
		Add_Spec(UP, 7);
		Add_Spec(DOWN, 23);
		break;
	case 3:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}


// Transfère de weak sur des doubles forcefield #2
void Puzzle_3_11()
{

	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 15 ,1 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(4);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;

		for (int r = 0; r <= 14; r++)
		{
			gGrids.Activate_Link({ 2 , r }, Modifier::BLOCKER);
			
			if(r <= 9)
				gGrids.Activate_Link({ 17 , r }, Modifier::BLOCKER);

		}

		gGrids.Activate_Link({ 20, 10 }, Modifier::REGULAR);
		gGrids.Activate_Link({ 20, 11 }, Modifier::REGULAR);
		gGrids.Activate_Link({ 20, 12 }, Modifier::REGULAR);
		gGrids.Activate_Link({ 20, 13 }, Modifier::REGULAR);


		gGrids.Activate_Link({ 11 - 2, 9 - 1 }, Modifier::FORCEFIELD);
		gGrids.Activate_Link({ 12 - 2, 9 - 1 }, Modifier::FORCEFIELD);
		gGrids.Activate_Link({ 9 - 2, 7 - 1 }, Modifier::FORCEFIELD);
		gGrids.Activate_Link({ 10 - 2, 7 - 1 }, Modifier::FORCEFIELD);
		gGrids.Activate_Link({ 7 - 2, 5 - 1 }, Modifier::FORCEFIELD);
		gGrids.Activate_Link({ 8 - 2, 5 - 1 }, Modifier::FORCEFIELD);
		gGrids.Activate_Link({ 5 - 2, 3 - 1 }, Modifier::FORCEFIELD);
		gGrids.Activate_Link({ 6 - 2, 3 - 1 }, Modifier::FORCEFIELD);
		gGrids.Activate_Link({ 16, 2 - 1 }, Modifier::REGULAR);
		gGrids.Activate_Link({ 16, 4 - 1 }, Modifier::REGULAR);
		gGrids.Activate_Link({ 16, 6 - 1 }, Modifier::REGULAR);
		gGrids.Activate_Link({ 16, 8 - 1 }, Modifier::REGULAR);
		gGrids.Make_Chain_Of_Walls({ 15 , 14 }, UP, 4, WallType::WEAK);

		for (int c = 17; c <= 21; c++)
			gGrids.Activate_Link({ c , 9 }, Modifier::BLOCKER);


		for (int r = 9; r <= 14; r++)
			gGrids.Activate_Link({ 21 , r }, Modifier::BLOCKER);

		break;

	case 1:
		gGrids.Extremely_Dumb_Fix_To_Redraw_Walls(); // wowsies
		skip = 5;
		break;

	case 2:	Add_Spec(UP, 9); skip = 4;break;
	case 3:	Add_Spec(UP, 19); skip = 4;break;
	case 4:	Add_Spec(UP, 7); skip = 4;break;
	case 5:	Add_Spec(UP, 19); skip = 4;break;
	case 6:	Add_Spec(UP, 5); skip = 4;break;
	case 7:	Add_Spec(UP, 19); skip = 4;break;
	case 8:	Add_Spec(UP, 3); skip = 4;break;
	case 9:	Add_Spec(DOWN, 19); skip = 4;break;
	case 10:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}

// Wall go through : #2: MEDIUM
void Puzzle_3_12() {
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 2,7 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(0);// Quantité d'ammo
		blastP1.Get_Ammo_Manager().Set_Nb_Emergency_Ammo(0);			// EXCEPTIONNAL
		gCurrPuzzleStepMax = 12;


		for (int c = 0; c <= 7; c++)
		{
			gGrids.Activate_Link({ c , 5 }, Modifier::BLOCKER);
			gGrids.Activate_Link({ c , 9 }, Modifier::BLOCKER);
		}
		for (int r = 6; r <= 9; r++)
		{
			gGrids.Activate_Link({ 7 , r }, Modifier::BLOCKER);
		}


		gGrids.Make_Chain_Of_Walls({ 6 , 6 }, LEFT, 1, WallType::REGULAR);
		gGrids.Make_Chain_Of_Walls({ 5 , 6 }, LEFT, 1, WallType::WEAK);

		gGrids.Make_Chain_Of_Walls({ 6 , 7 }, LEFT, 1, WallType::WEAK);
		gGrids.Make_Chain_Of_Walls({ 5 , 7 }, LEFT, 1, WallType::WEAK);

		gGrids.Make_Chain_Of_Walls({ 6 , 8 }, LEFT, 1, WallType::WEAK);
		gGrids.Make_Chain_Of_Walls({ 5 , 8 }, LEFT, 1, WallType::REGULAR);
		break;


	case 1:skip = 3;break;
	case 2:Add_Spec(DOWN, 0);skip = 2;break;
	case 3:Add_Spec(UP, 0);skip = 2;break;
	case 4:Add_Spec(UP, 0);skip = 2;break;
	case 5:Add_Spec(DOWN, 0);skip = 2;break;
	case 6:Add_Spec(DOWN, 0);skip = 2;break;
	case 7:Add_Spec(UP, 0);skip = 2;break;
	case 12:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}


// What to do with you?
void Puzzle_3_13()
{
	int start = 4;
	int numWalls = 6;

	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ start + numWalls + 1,7 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(0);		// Quantité d'ammo
		gCurrPuzzleStepMax = 12;


		ConsoleRender::Add_String(" TELEPORTATION SHOT", { (Find_Ctr_X((int)std::size(" TELEPORTATION SHOT")) / 2) / 2, (gConHeight / 2) / 2 }, BRIGHT_WHITE, TXT_SPD_DR, 1);
		ConsoleRender::Add_String("(Shoot, then spacebar)", { (Find_Ctr_X((int)std::size("(Shoot , then spacebar)")) / 2) / 2 , (gConHeight / 2) / 2 + 2 }, WHITE, TXT_SPD_DR, 1);


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


/// HARD, keep a wall alive, pure speed #1
void Puzzle_3_14()
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
void Puzzle_3_15()
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


		// Hint
		gGrids.Activate_Link({ 19, 11 }, Modifier::BLOCKER,1);
		gGrids.Activate_Link({ 18, 12 }, Modifier::BLOCKER);
		gGrids.Activate_Link({ 18, 13 }, Modifier::BLOCKER);
		gGrids.Activate_Link({ 19, 13 }, Modifier::BLOCKER);
		gGrids.Activate_Link({ 20, 13 }, Modifier::BLOCKER);
		gGrids.Activate_Link({ 20, 12 }, Modifier::BLOCKER);


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
		break;


	case 1:
		Add_Spec(DOWN, 25);
		instantSpawn = 1; 
		skip = 6;
		break;

	case 2:
		Add_Spec(UP, 2);
		Add_Spec(RIGHT, 7);
		instantSpawn = 1;
		break;

	case 3:Add_Spec(RIGHT, 13); instantSpawn = 1;break;
	case 4:Add_Spec(RIGHT, 13); instantSpawn = 1;break;
	case 5:Add_Spec(RIGHT, 13); instantSpawn = 1;break;
	case 6:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}


// VERY HARD. No extra ammo. Solve this puzzle #2
void Puzzle_3_16()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 15,9 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(0);// Quantité d'ammo
		blastP1.Get_Ammo_Manager().Set_Nb_Emergency_Ammo(0);			// EXCEPTIONNAL
		gCurrPuzzleStepMax = 12;



		gGrids.Make_Chain_Of_Walls({ 15,7 }, DOWN, 1, WallType::WEAK);
		gGrids.Make_Chain_Of_Walls({ 16,9 }, UP, 1, WallType::WEAK);

		gGrids.Make_Chain_Of_Walls({ 12,5 }, DOWN, 1, WallType::WEAK);
		gGrids.Make_Chain_Of_Walls({ 12,10 }, UP, 1, WallType::WEAK);

		gGrids.Activate_Link({ 12,8 }, Modifier::REGULAR);
		gGrids.Activate_Link({ 15,5 }, Modifier::REGULAR);
		gGrids.Activate_Link({ 16,7 }, Modifier::REGULAR);



		gGrids.Make_Box_Of_Blockers({ 11,4 }, { 17,11 });

		for (int r = 5; r < 11; r++)
		{
			gGrids.Activate_Link({ 14,r }, Modifier::FORCEFIELD);
		}
		break;


	case 1:skip = 25;break;
	case 2:
		Add_Spec(UP, 13);
		Add_Spec(DOWN, 13);
		Add_Spec(UP, 14);
		Add_Spec(DOWN, 14);
		break;
	case 3:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}



// Cool tp weak/energized
void Puzzle_3_17() {
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 16 ,3 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(0);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;

		for (int r = 2; r <= 13; r++)
		{
			gGrids.Activate_Link({ 8 , r }, Modifier::BLOCKER);
			gGrids.Activate_Link({ 19 , r }, Modifier::BLOCKER);

		}


		for (int c = 8; c <= 12; c++)
		{
			gGrids.Activate_Link({ c , 2 }, Modifier::BLOCKER);
			gGrids.Activate_Link({ c , 13 }, Modifier::BLOCKER);
		}

		for (int c = 15; c <= 18; c++)
		{
			gGrids.Activate_Link({ c , 2 }, Modifier::BLOCKER);
			gGrids.Activate_Link({ c , 13 }, Modifier::BLOCKER);
		}

		for (int r = 0; r <= 3; r++)
		{
			gGrids.Activate_Link({ 12 , r }, Modifier::BLOCKER);
			gGrids.Activate_Link({ 15 , r }, Modifier::BLOCKER);

		}

		for (int r = 12; r <= 14; r++)
		{
			gGrids.Activate_Link({ 12 , r}, Modifier::BLOCKER);
			gGrids.Activate_Link({ 15 , r}, Modifier::BLOCKER);
		}
		for (int c = 0; c <= 3; c++)
		{
			gGrids.Activate_Link({ 12 + c , 0 }, Modifier::BLOCKER);

		}



		gGrids.Activate_Link({ 11 + 2, 5  - 1}, Modifier::FORCEFIELD);
		gGrids.Activate_Link({ 12 + 2, 5  - 1}, Modifier::FORCEFIELD);
		gGrids.Activate_Link({ 11 + 2, 6  - 1}, Modifier::FORCEFIELD);
		gGrids.Activate_Link({ 12 + 2, 6  - 1}, Modifier::FORCEFIELD);
		gGrids.Activate_Link({ 11 + 2, 7  - 1}, Modifier::FORCEFIELD);
		gGrids.Activate_Link({ 12 + 2, 7  - 1}, Modifier::FORCEFIELD);
		gGrids.Activate_Link({ 11 + 2, 8  - 1}, Modifier::FORCEFIELD);
		gGrids.Activate_Link({ 12 + 2, 8  - 1}, Modifier::FORCEFIELD);
		gGrids.Activate_Link({ 11 + 2, 9  - 1}, Modifier::FORCEFIELD);
		gGrids.Activate_Link({ 12 + 2, 9  - 1}, Modifier::FORCEFIELD);
		gGrids.Activate_Link({ 11 + 2,10  - 1}, Modifier::FORCEFIELD);
		gGrids.Activate_Link({ 12 + 2,10  - 1}, Modifier::FORCEFIELD);


		gGrids.Make_Chain_Of_Walls({ 9 , 5 - 1 }, RIGHT, 1, WallType::WEAK);
		gGrids.Make_Chain_Of_Walls({ 9 , 7 - 1 }, RIGHT, 1, WallType::WEAK);
		gGrids.Make_Chain_Of_Walls({ 9 , 9 - 1 }, RIGHT, 1, WallType::WEAK);

		gGrids.Make_Chain_Of_Walls({ 18 , 6 -1 }, LEFT, 1, WallType::WEAK);
		gGrids.Make_Chain_Of_Walls({ 18 , 8 -1 }, LEFT, 1, WallType::WEAK);
		gGrids.Make_Chain_Of_Walls({ 18 ,10 -1 }, LEFT, 1, WallType::WEAK);

		
		
		gGrids.Make_Chain_Of_Walls({ 16 , 5 }, UP, 1, WallType::ENERGIZED);
		gGrids.Activate_Link({ 16, 8 - 1 }, Modifier::REGULAR);
		gGrids.Activate_Link({ 16,10 - 1 }, Modifier::REGULAR);

		gGrids.Activate_Link({ 11, 7 - 1 }, Modifier::REGULAR);
		gGrids.Activate_Link({ 11, 9 - 1 }, Modifier::REGULAR);
		gGrids.Activate_Link({ 11,11 - 1 }, Modifier::REGULAR);
		

		gGrids.Make_Chain_Of_Walls({ 13 , 1 }, DOWN, 1, WallType::ENERGIZED);
		gGrids.Activate_Link({ 14, 1 }, Modifier::REGULAR);

		gGrids.Activate_Link({ 16, 12 }, Modifier::REGULAR);
		gGrids.Activate_Link({ 13, 11 }, Modifier::REGULAR);
		gGrids.Activate_Link({ 13, 13 }, Modifier::REGULAR);

		gGrids.Make_Chain_Of_Walls({ 13 , 13 }, UP, 1, WallType::ENERGIZED);
		gGrids.Make_Chain_Of_Walls({ 14 , 13 }, UP, 1, WallType::ENERGIZED);

		break;

	case 1:
		gGrids.Extremely_Dumb_Fix_To_Redraw_Walls(); // wowsies
		break;

	case 2:	Add_Spec(UP, 13); skip = 2;break;
	case 3:	Add_Spec(UP, 13); skip = 2;break;
	case 4:	Add_Spec(UP, 13); skip = 1;break;
	case 5:	Add_Spec(UP, 13); skip = 1;break;
	case 6:	Add_Spec(UP, 13); skip = 8;break;
	case 7:	Add_Spec(UP, 13); 
		Add_Spec(LEFT, 1);
		Add_Spec(LEFT, 12);
		Add_Spec(RIGHT, 1);
		Add_Spec(RIGHT, 12);
		instantSpawn = true;
		break;

	case 8:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}

// Teleporting madness 2
void Puzzle_3_18()
{
	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 22,1 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(0);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;
		Cancel_Checkpoint_Delay();



		for (short c = 2; c <= 26; c++)
		{
			gGrids.Activate_Link({ c,2 }, Modifier::BLOCKER);
		}

		for (short c = 2; c <= 24; c++)
		{
			gGrids.Activate_Link({ c,12 }, Modifier::BLOCKER);
		}

		for (short c = 5; c <= 24; c++)
		{
			gGrids.Activate_Link({ c,5 }, Modifier::BLOCKER);
		}

		for (short c = 5; c <= 21; c++)
		{
			gGrids.Activate_Link({ c,9 }, Modifier::BLOCKER);
		}

		for (short r = 12; r >= 2; r--)
		{
			gGrids.Activate_Link({ 2,r }, Modifier::BLOCKER);
		}

		for (short r = 12; r >= 5; r--)
		{
			gGrids.Activate_Link({ 24,r }, Modifier::BLOCKER);
		}

		for (short r = 9; r >= 5; r--)
		{
			gGrids.Activate_Link({ 5,r }, Modifier::BLOCKER);
		}

		for (short r = 9; r >= 7; r--)
		{
			gGrids.Activate_Link({ 21,r }, Modifier::BLOCKER);
		}

		gGrids.Make_Chain_Of_Walls({ 24,1 }, LEFT, 1, WallType::ENERGIZED);
		gGrids.Activate_Link({ 25,1 }, Modifier::REGULAR);
		gGrids.Activate_Link({ 21,1 }, Modifier::FORCEFIELD);

		// Chemin #1, l'allez
		gGrids.Activate_Link({ 0,1 }, Modifier::REGULAR);
		gGrids.Activate_Link({ 1,14 }, Modifier::REGULAR);
		gGrids.Activate_Link({ 26,13 }, Modifier::REGULAR);
		gGrids.Activate_Link({ 25,3 }, Modifier::REGULAR);
		gGrids.Activate_Link({ 3,4 }, Modifier::REGULAR);
		gGrids.Activate_Link({ 4,11 }, Modifier::REGULAR);
		gGrids.Activate_Link({ 23,10 }, Modifier::REGULAR);
		linkGrid->link[22][5].Convert_Modifier(Modifier::REGULAR, 1);
		linkGrid->link[5][6].Convert_Modifier(Modifier::REGULAR, 1);
		linkGrid->link[6][9].Convert_Modifier(Modifier::REGULAR, 1);
		linkGrid->link[21][8].Convert_Modifier(Modifier::REGULAR, 1);

		// Chemin #2, le retour
		gGrids.Make_Chain_Of_Walls({ 21,7 }, LEFT, 1, WallType::WEAK);
		linkGrid->link[5][7].Convert_Modifier(Modifier::REGULAR, 1);
		linkGrid->link[6][5].Convert_Modifier(Modifier::REGULAR, 1);
		linkGrid->link[24][6].Convert_Modifier(Modifier::REGULAR, 1);
		linkGrid->link[23][12].Convert_Modifier(Modifier::REGULAR, 1);
		linkGrid->link[2][11].Convert_Modifier(Modifier::REGULAR, 1);
		linkGrid->link[3][2].Convert_Modifier(Modifier::REGULAR, 1);
		break;


	case 1:skip = 4;break;
	case 2:Add_Spec(UP, 20); skip = 19;break;
	case 3:Add_Spec(DOWN, 24);break;
	case 4:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}

// Take your time #3 ! The final one
// Prepare yourself for glorious copy-pasta
void Puzzle_3_19()
{
	static GrdCoord center;center = { linkGrid->Get_Cols() / 2, 7 };
	static int distance = 3;
	static bool puzzleSolved;
	static int wallsToConvert;
	static int wallsPlacedIncorrectly;
	static bool correctWallFound;
	static GrdCoord correctWeakWallPlacement[] = {
		center.c,			center.r - distance,
		center.c - 2,		center.r - distance,
		center.c + 2,		center.r - distance,
		center.c - distance,center.r + 2 ,
		center.c + 2,		center.r + distance,
		center.c,			center.r + distance
	};

	static GrdCoord correctEnergizedWallsPlacement[] = {
	center.c - distance,		center.r - 1,
	center.c - distance,		center.r + 1,
	center.c - 1,				center.r - distance,
	center.c - 1,				center.r + distance,
	center.c + distance,		center.r - 1,
	center.c + 1,				center.r - distance
	};

	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ center.c, center.r - 1 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(0);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;


		Ev_Take_Your_Time();
		gGrids.Activate_Link(center, Modifier::FORCEFIELD);
		gGrids.Activate_Link({center.c + 1,center.r}, Modifier::FORCEFIELD);
		gGrids.Activate_Link({center.c - 1,center.r}, Modifier::FORCEFIELD);
		gGrids.Activate_Link({ center.c + 2,center.r }, Modifier::FORCEFIELD);
		gGrids.Activate_Link({ center.c - 2,center.r }, Modifier::FORCEFIELD);

		//up 
		for (int c = center.c - distance; c < center.c + distance + 1; c++)
		{
			correctWallFound = false;

			for (GrdCoord coord : correctWeakWallPlacement)
			{
				if (Are_Equal({ c, center.r - distance }, coord))
				{
					gGrids.Make_Chain_Of_Walls({ c, center.r - distance }, UP, 1, WallType::REGULAR);
					break;
				}
			}

			if (!correctWallFound)
				for (GrdCoord coord : correctEnergizedWallsPlacement)
				{
					if (Are_Equal({ c, center.r - distance }, coord))
					{
						gGrids.Make_Chain_Of_Walls({ c, center.r - distance }, UP, 1, WallType::ENERGIZED);
						break;
					}
				}

			if(!correctWallFound)
				gGrids.Make_Chain_Of_Walls({ c, center.r - distance }, UP, 1, WallType::WEAK);
		}

		//down
		for (int c = center.c - distance; c < center.c + distance + 1; c++)
		{
			correctWallFound = false;

			for (GrdCoord coord : correctWeakWallPlacement)
			{
				if (Are_Equal({ c, center.r + distance }, coord))
				{
					gGrids.Make_Chain_Of_Walls({ c, center.r + distance }, DOWN, 1, WallType::REGULAR);
					break;
				}
			}

			if (!correctWallFound)
				for (GrdCoord coord : correctEnergizedWallsPlacement)
				{
					if (Are_Equal({ c, center.r + distance }, coord))
					{
						gGrids.Make_Chain_Of_Walls({ c, center.r + distance }, DOWN, 1, WallType::ENERGIZED);
						break;
					}
				}

			if (!correctWallFound)
				gGrids.Make_Chain_Of_Walls({ c, center.r + distance }, DOWN, 1, WallType::WEAK);
		}

		// Left 
		for (int r = center.r - distance; r < center.r + distance + 1; r++)
		{
			correctWallFound = false;

			for (GrdCoord coord : correctWeakWallPlacement)
			{
				if (Are_Equal({ center.c - distance, r }, coord))
				{
					gGrids.Make_Chain_Of_Walls({ center.c - distance, r }, LEFT, 1, WallType::REGULAR);
					break;
				}
			}

			if (!correctWallFound)
				for (GrdCoord coord : correctEnergizedWallsPlacement)
				{
					if (Are_Equal({ center.c - distance, r }, coord))
					{
						gGrids.Make_Chain_Of_Walls({ center.c - distance, r }, LEFT, 1, WallType::ENERGIZED);
						break;
					}
				}

			if (!correctWallFound)
				gGrids.Make_Chain_Of_Walls({ center.c - distance, r }, LEFT, 1, WallType::WEAK);
		}

		// right
		for (int r = center.r - distance; r < center.r + distance + 1; r++)
		{
			correctWallFound = false;

			for (GrdCoord coord : correctWeakWallPlacement)
			{
				if (Are_Equal({ center.c + distance, r }, coord))
				{
					gGrids.Make_Chain_Of_Walls({ center.c + distance, r }, RIGHT, 1, WallType::REGULAR);
					break;
				}
			}

			if (!correctWallFound)
				for (GrdCoord coord : correctEnergizedWallsPlacement)
				{
					if (Are_Equal({ center.c + distance, r }, coord))
					{
						gGrids.Make_Chain_Of_Walls({ center.c + distance, r }, RIGHT, 1, WallType::ENERGIZED);
						break;
					}
				}

			if (!correctWallFound)
				gGrids.Make_Chain_Of_Walls({ center.c + distance, r }, RIGHT, 1, WallType::WEAK);
		}

		gGrids.Make_Chain_Of_Walls({ center.c, center.r + distance }, UP, 1, WallType::WEAK);
		gGrids.Make_Chain_Of_Walls({ center.c + 2, center.r + distance }, UP, 1, WallType::WEAK);
		gGrids.Make_Chain_Of_Walls({ center.c + 1, center.r + distance }, UP, 1, WallType::ENERGIZED);
		gGrids.Make_Chain_Of_Walls({ center.c - 1 , center.r - distance }, DOWN, 1, WallType::WEAK);
		gGrids.Make_Chain_Of_Walls({ center.c - 2 , center.r - distance }, DOWN, 1, WallType::WEAK);
		gGrids.Make_Chain_Of_Walls({ center.c , center.r - distance },	   DOWN, 1, WallType::ENERGIZED);
		gGrids.Make_Chain_Of_Walls({ center.c + 2 , center.r - distance }, DOWN, 1, WallType::ENERGIZED);
		gGrids.Make_Chain_Of_Walls({ center.c + distance, center.r - 1 }, LEFT, 1, WallType::WEAK);
		gGrids.Make_Chain_Of_Walls({ center.c + distance, center.r + 1 }, LEFT, 1, WallType::ENERGIZED);
		gGrids.Make_Chain_Of_Walls({ center.c - distance, center.r + 1 }, RIGHT, 1, WallType::WEAK);
		gGrids.Make_Chain_Of_Walls({ center.c - distance, center.r - 1 }, RIGHT, 1, WallType::ENERGIZED);
		gGrids.Make_Chain_Of_Walls({ center.c - distance, center.r + 2 }, RIGHT, 1, WallType::ENERGIZED);

		puzzleSolved = false;


		break;


	case 1: skip = 10;break;
	case 2:
		wallsToConvert = 0;
		wallsPlacedIncorrectly = 0;

		for (GrdCoord coord : correctWeakWallPlacement)
		{
			if (linkGrid->link[coord.c][coord.r].Get_Num_Child() < 2) //Check si les murs convert sont bien placés
				wallsPlacedIncorrectly++;
			else
				if (linkGrid->link[coord.c][coord.r].Get_Child(0)->Get_Type() == WallType::WEAK || linkGrid->link[coord.c][coord.r].Get_Child(1)->Get_Type() == WallType::WEAK)
					wallsToConvert++; //Check si les murs sont bien convert
		}

		for (GrdCoord coord : correctEnergizedWallsPlacement)
		{
			if (linkGrid->link[coord.c][coord.r].Get_Num_Child() < 2) 
				wallsPlacedIncorrectly++;
			else
				if (linkGrid->link[coord.c][coord.r].Get_Child(0)->Get_Type() != WallType::ENERGIZED || linkGrid->link[coord.c][coord.r].Get_Child(1)->Get_Type() != WallType::ENERGIZED)
					wallsToConvert++; 
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
		Add_Spec(UP, 10);
		Add_Spec(RIGHT, 4);Add_Spec(LEFT, 4);
		Add_Spec(RIGHT, 9);Add_Spec(LEFT, 9);
		break;

	case 4:
		Add_Spec(UP, 10);
		Add_Spec(RIGHT, 4);Add_Spec(LEFT, 4);
		break;

	case 5:
		Add_Spec(UP, 10);
		Add_Spec(DOWN, 15);
		Add_Spec(RIGHT, 4);
		Add_Spec(LEFT, 9);
		break;

	case 6:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
	}
}

void Puzzle_3_FINAL()
{
	static bool upOrDown = false;
	static Direction leftOrRight = LEFT;

	static std::string _1 = "- SURVIVE -";
	static std::string _2 = "Waves Remaining :";

	static Coord crd;
	static Direction dir;
	const int SHAPES_TO_KILL = 15;
	static int shapesRemaining;

	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ 13,7 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(80);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;

		upOrDown = false;
		leftOrRight = LEFT;
		shapesRemaining = SHAPES_TO_KILL;
		crd = { Find_Ctr_String_X(_1) - 1, 6 };


		// DEBUG 
		// *****
		//seenFinalHour = 1;


		if (seenFinalHour)
			Cancel_Checkpoint_Delay();
		break;

	case 1:
		if (!seenFinalHour)
		{
			MsgQueue::Register(LOCK_PLAYER);
			MsgQueue::Register(FINAL_HOUR);	// montre ça juste une fois, EVER
			P1.Er_Player();
			seenFinalHour = true;
			skip = 10;
		}
		else
			skip = -1;
		break;

	case 2:
		if (P1.Cant_Do_Stuff())
		{
			P1.Set_Position({ 13,7 });				// Coord de départ du jouer
			Set_Ev_Spawn_Player(3);
		}

		ConsoleRender::Add_String(_1, crd, BRIGHT_WHITE, TXT_SPD_DR);
		ConsoleRender::Add_String(_2, { crd.x - 5, crd.y + 1 }, WHITE, TXT_SPD_DR);
		ConsoleRender::Add_String("???", { crd.x + 13,crd.y + 1 }, LIGHT_AQUA, TXT_SPD_DR);

		// Phase 1: REGULAR
		for (int c = 0; c < linkGrid->Get_Cols(); c++)
		{
			gGrids.Make_Chain_Of_Walls({ c,6 }, UP, 1);
			gGrids.Make_Chain_Of_Walls({ c,8 }, DOWN, 1);
		}

		// DEBUG
		/// ****
		//gCurrPuzzleStep = 15;//PHASE 2
		//gCurrPuzzleStep = 24;//PHASE 3
		//gCurrPuzzleStep = 37;//PHASE 4
		//gCurrPuzzleStep = 50;//PHASE 5
		//gCurrPuzzleStep = 63;//PHASE 6
		//gCurrPuzzleStep = 82;//PHASE 7
		break;


	case 3:Add_Spec(LEFT, 6); break;
	case 4:Add_Spec(LEFT, 6); break;
	case 5:Add_Spec(RIGHT, 6);break;
	case 6:Add_Spec(LEFT, 7); break;
	case 7:Add_Spec(RIGHT, 7);break;
	case 8:Add_Spec(LEFT, 7);break;
	case 9:dir = LEFT; Add(2);Set_Interval(dir, 6, 8);break;
	case 10:Add(2);Set_Interval(dir, 6, 8);;break;
	case 11:Add(2);Set_Interval(dir, 6, 8);;break;
	case 12:Add(2);Set_Interval(dir, 6, 8);;break;
	case 13:
	case 14:
	case 15:break;

		// Phase 2 !
	case 16:
		if (gAllBotMeta.alive || !P1.Get_HP())
			gCurrPuzzleStep--;
		else
		{
			// Setup phase 2
			Clear_Map();

			blastP1.Get_Ammo_Manager().Activate();
			P1.Set_Position({ 13,7 });
			Set_Ev_Spawn_Player(3);
			MsgQueue::Register(LOCK_PLAYER);

			for (int r = 0; r < linkGrid->Get_Rows(); r++)
				for (int c = 0; c < linkGrid->Get_Cols(); c++)
				{
					if (r <= 5 || r >= 9)
					{
						if (r == 5 || r == 9)
							gGrids.Activate_Link({ c,r }, Modifier::BLOCKER);
					}
					else
						if (!Are_Equal({ c,r }, P1.Get_Grd_Coord()))
						{
							ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { c,r });
						}
				}

		}
		break;

	case 17:dir = LEFT; break;
	case 18:Add(2);Set_Interval(dir, 5, 9);skip = 3;		 break;
	case 19:Add(2);Set_Interval(dir, 5, 9);skip = 3;		 break;
	case 20:Add(2);Set_Interval(dir, 5, 9);skip = 3;		 break;
	case 21:Add(2);Set_Interval(dir, 5, 9);skip = 3;		 break;
	case 22:Add(2);Set_Interval(dir, 5, 9);skip = 3;		 break;
	case 23:
	case 24:break;

		// PHASE 3
		// *******
	case 25:
		if (gAllBotMeta.alive || !P1.Get_HP())
			gCurrPuzzleStep--;
		else
		{
			Clear_Map();

			blastP1.Get_Ammo_Manager().Activate();
			P1.Set_Position({ 13,7 });
			Set_Ev_Spawn_Player(3);
			MsgQueue::Register(LOCK_PLAYER);

			for (int c = 0; c < linkGrid->Get_Cols(); c++)
			{
				gGrids.Make_Chain_Of_Walls({ c,4 }, UP, 1);
				gGrids.Make_Chain_Of_Walls({ c,10 }, DOWN, 1);
			}

			for (int r = 5; r < 10; r++)
			{
				gGrids.Activate_Link({ 11,r });
				gGrids.Activate_Link({ 15,r });
			}


		}
		break;


	case 26:dir = UP;break;
	case 27:Add(2);Set_Interval(dir, 11, 13);skip = 3;break;
	case 28:Add(3);Set_Interval(dir, 12, 15);skip = 2;break;
	case 29:Add(1);Set_Interval(dir, 11, 15);skip = 1;break;
	case 30:Add(2);Set_Interval(dir, 11, 15);skip = 4;break;
	case 31:Add(3);Set_Interval(dir, 11, 14);break;
	case 32:
	case 33:
	case 34:
	case 35:
	case 36:
	case 37:break;

		// PHASE 4
		// *******
	case 38:
		if (gAllBotMeta.alive || !P1.Get_HP())
			gCurrPuzzleStep--;
		else
		{
			Clear_Map();

			blastP1.Get_Ammo_Manager().Activate();
			P1.Set_Position({ 13,7 });
			Set_Ev_Spawn_Player(3);
			MsgQueue::Register(LOCK_PLAYER);

			for (int r = 0; r < linkGrid->Get_Rows(); r++)
				for (int c = 0; c < linkGrid->Get_Cols(); c++)
				{
					if (r <= 3 || r >= 11)
					{
						if (r == 3 || r == 11)
							gGrids.Activate_Link({ c,r }, Modifier::BUFFER);
					}
				}
			gGrids.Activate_Link({ 13 - 1 , 7 + 1 }, Modifier::BUFFER);
			gGrids.Activate_Link({ 13 + 0 , 7 + 2 }, Modifier::BUFFER);
			gGrids.Activate_Link({ 13 + 1 , 7 + 3 }, Modifier::BUFFER);


			gGrids.Activate_Link({ 13 + 1  , 7 - 1 }, Modifier::BUFFER);
			gGrids.Activate_Link({ 13 - 0  , 7 - 2 }, Modifier::BUFFER);
			gGrids.Activate_Link({ 13 - 1  , 7 - 3 }, Modifier::BUFFER);
		}
		break;

	case 39:dir = LEFT; break;
	case 40:Add(8);Set_Interval(dir, 3, 11);skip = 0;break;
	case 41:Add(8);Set_Interval(dir, 3, 11);skip = 14;break;
	case 42:Add(8);Set_Interval(dir, 3, 11);skip = 0;break;
	case 43:Add(8);Set_Interval(dir, 3, 11);skip = 0;break;
	case 44:
	case 45:
	case 46:
	case 47:break;
	case 48:break;
	case 49:break;
	case 50:break;

		// PHASE 5
		// *******
	case 51:
		if (gAllBotMeta.alive || !P1.Get_HP())
			gCurrPuzzleStep--;
		else
		{
			// Setup phase 2
			Clear_Map();

			blastP1.Get_Ammo_Manager().Activate();
			P1.Set_Position({ 13,7 });
			Set_Ev_Spawn_Player(3);
			MsgQueue::Register(LOCK_PLAYER);

			for (int c = 0; c < linkGrid->Get_Cols(); c++)
			{
				gGrids.Make_Chain_Of_Walls({ c,2 }, UP, 1, WallType::REGULAR, Modifier::BUFFER);
				gGrids.Make_Chain_Of_Walls({ c,12 }, DOWN, 1, WallType::REGULAR, Modifier::BLOCKER);

			}



			for (int r = 0; r < linkGrid->Get_Rows(); r++)
				for (int c = 0; c < linkGrid->Get_Cols(); c++)
				{
					if (!Are_Equal({ c,r }, P1.Get_Grd_Coord()))
						if (r > 2 && r <= 4)
							ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { c,r });
						else
							if (r > 9 && r <= 11)
								ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { c,r });

				}
		}
		break;

	case 52:dir = LEFT; skip = 4; break;
	case 53:Add(2);Set_Interval(dir, 2, 4); skip = 4;break;
	case 54:Add(2);Set_Interval(dir, 10, 12);break;
	case 55:Add(2);Set_Interval(dir, 2, 4);skip = 4;break;
	case 56:Add(2);Set_Interval(dir, 10, 12);skip = 0;break;
	case 57:Add(2);Set_Interval(dir, 2, 4);skip = 0;break;
	case 58:Add(2);Set_Interval(dir, 2, 4);skip = 0;break;
	case 59:Add(2);Set_Interval(dir, 2, 4);skip = 0;break;
	case 60:Add(2);Set_Interval(dir, 10, 12);skip = 0;break;

		// PHASE 6
		// *******
	case 64:
		if (gAllBotMeta.alive || !P1.Get_HP())
			gCurrPuzzleStep--;
		else
		{
			// Setup phase 2
			Clear_Map();

			blastP1.Get_Ammo_Manager().Activate();
			P1.Set_Position({ 2, 3 });
			Set_Ev_Spawn_Player(3);
			MsgQueue::Register(LOCK_PLAYER);

			for (int c = 0; c < linkGrid->Get_Cols(); c++)
				for (int r = 1; r < linkGrid->Get_Rows() - 1; r++)
				{
					//if (r != 7)
					if (c == 5 || c == 13 || c == 21)
						gGrids.Activate_Link({ c,r }, Modifier::FORCEFIELD);
				}

			for (int r = 0; r <= 26; r++)
			{
				if (r >= 2 && r <= 6)
					gGrids.Make_Chain_Of_Walls({ 0,r }, RIGHT, 1, WallType::WEAK);
			}
			gGrids.Make_Chain_Of_Walls({ 0,7 }, RIGHT, 1, WallType::ENERGIZED);
			//gGrids.Make_Chain_Of_Walls({ 13,7 }, RIGHT, 1, WallType::ENERGIZED);


			for (int r = 0; r <= 26; r++)
			{
				if (r >= 8 && r <= 12)
					gGrids.Make_Chain_Of_Walls({ 26,r }, LEFT, 1, WallType::WEAK);
			}
			//gGrids.Make_Chain_Of_Walls({ 26,12 }, LEFT, 1, WallType::ENERGIZED);
			//gGrids.Make_Chain_Of_Walls({ 13,12 }, LEFT, 1, WallType::REGULAR);



			// Lignes horizontales
			for (int c = 0; c <= 26; c++)
			{
				gGrids.Make_Chain_Of_Walls({ c,1 }, UP, 1, WallType::REGULAR, Modifier::FORCEFIELD);
				gGrids.Make_Chain_Of_Walls({ c,13 }, DOWN, 1, WallType::REGULAR, Modifier::FORCEFIELD);
			}
		}
		break;

	case 65:dir = UP;skip = 3; break;
	case 66:Add(1);Set_Interval(UP, 12, 13);skip = 0;break;
	case 67:Add(1);Set_Interval(UP, 12, 13);skip = 0;break;
	case 68:Add(1);Set_Interval(UP, 12, 13);skip = 0;break;
	case 69:Add(1);Set_Interval(UP, 12, 13);skip = 0;break;
	case 70:Add(1);Set_Interval(UP, 12, 13);skip = 8;break;
	case 71:Add(1);Set_Interval(DOWN, 13, 14);skip = 0;break;
	case 72:Add(1);Set_Interval(DOWN, 13, 14);skip = 0;break;
	case 73:Add(1);Set_Interval(DOWN, 13, 14);skip = 0;break;
	case 74:Add(1);Set_Interval(DOWN, 13, 14);skip = 0;break;
	case 75:Add(1);Set_Interval(DOWN, 13, 14);skip = 0;break;
	case 76:
	case 77:
	case 79:
	case 80:
	case 81:
	case 82:break;


		// PHASE 7
		// *******
	case 83:
		if (gAllBotMeta.alive || !P1.Get_HP())
			gCurrPuzzleStep--;
		else
		{
			// Setup phase 2
			Clear_Map();

			blastP1.Get_Ammo_Manager().Activate();
			P1.Set_Position({ 13,11 });
			Set_Ev_Spawn_Player(3);
			MsgQueue::Register(LOCK_PLAYER);

			//for (short r = 0; r < linkGrid->Get_Rows(); r++)
			//{
			//	gGrids.Activate_Link({ 0, r }, Modifier::REGULAR);
			//	gGrids.Activate_Link({ 26, r }, Modifier::REGULAR);
			//}

			//for (short c = 0; c < linkGrid->Get_Cols(); c++)
			//{
			//	gGrids.Activate_Link({ c, 0 }, Modifier::REGULAR);
			//	gGrids.Activate_Link({ c, 14 }, Modifier::REGULAR);
			//}


			gGrids.Activate_Link({ 13, 6 }, Modifier::REGULAR);

		}
		break;


	case 84:break;
	case 85:Add(300); skip = 4;break;
	case 86:
		botList.Destroy_All_Bots();
		Add_Spec(RIGHT, 6);
		instantSpawn = true;

		// The end...
		MsgQueue::Register(STOP_BOT_SPAWNS);
		Ev_Wait_For_Victory(); // Wait que le dernier bot meurt pour trigger la victoire
		break;
	}
	
	dir = Find_Opposite_Dir(dir);
}
//
//// Place walls correctly #2 Take your time
//void Puzzle_3_10()
//{
//	static GrdCoord center = { linkGrid->Get_Cols() / 2, 7 };
//	static int distance = 2;
//	static bool puzzleSolved;
//	static int wallsToConvert;
//	static int wallsPlacedIncorrectly;
//	static GrdCoord coorectWallPlacement[] = {
//		center.c,center.r - distance,
//		center.c - 1,center.r - distance,
//		center.c + 1,center.r - distance,
//		center.c - distance ,center.r + 1 ,
//		center.c + distance ,center.r ,
//		center.c + 1 , center.r + distance,
//		center.c , center.r + distance
//	};
//
//	switch (gCurrPuzzleStep)
//	{
//	case 0:P1.Set_Position({ linkGrid->Get_Cols() / 2 - 1,7 });				// Coord de départ du jouer
//		blastP1.Get_Ammo_Manager().Set_Ammo(0);// Quantité d'ammo
//		blastP1.Get_Ammo_Manager().Set_Nb_Emergency_Ammo(0);			// EXCEPTIONNAL
//
//		gCurrPuzzleStepMax = 12;
//
//		Ev_Take_Your_Time();
//		gGrids.Activate_Link(center, Modifier::FORCEFIELD);
//
//		//up 
//		for (int c = center.c - distance; c < center.c + distance + 1; c++)
//		{
//			for (GrdCoord coord : coorectWallPlacement)
//			{
//				if (Are_Equal({ c, center.r - distance }, coord))
//				{
//					gGrids.Make_Chain_Of_Walls({ c, center.r - distance }, UP, 1, WallType::REGULAR);
//					break;
//				}
//			}
//
//			gGrids.Make_Chain_Of_Walls({ c, center.r - distance }, UP, 1, WallType::WEAK);
//		}
//
//		//down
//		for (int c = center.c - distance; c < center.c + distance + 1; c++)
//		{
//			for (GrdCoord coord : coorectWallPlacement)
//			{
//				if (Are_Equal({ c, center.r + distance }, coord))
//				{
//					gGrids.Make_Chain_Of_Walls({ c, center.r + distance }, DOWN, 1, WallType::REGULAR);
//					break;
//				}
//			}
//
//			gGrids.Make_Chain_Of_Walls({ c, center.r + distance }, DOWN, 1, WallType::WEAK);
//		}
//
//		// Left 
//		for (int r = center.r - distance; r < center.r + distance + 1; r++)
//		{
//			for (GrdCoord coord : coorectWallPlacement)
//			{
//				if (Are_Equal({ center.c - distance, r }, coord))
//				{
//					gGrids.Make_Chain_Of_Walls({ center.c - distance, r }, LEFT, 1, WallType::REGULAR);
//					break;
//				}
//			}
//
//			gGrids.Make_Chain_Of_Walls({ center.c - distance, r }, LEFT, 1, WallType::WEAK);
//		}
//
//		// right
//		for (int r = center.r - distance; r < center.r + distance + 1; r++)
//		{
//
//			for (GrdCoord coord : coorectWallPlacement)
//			{
//				if (Are_Equal({ center.c + distance, r }, coord))
//				{
//					gGrids.Make_Chain_Of_Walls({ center.c + distance, r }, RIGHT, 1, WallType::REGULAR);
//					break;
//				}
//			}
//
//			gGrids.Make_Chain_Of_Walls({ center.c + distance, r }, RIGHT, 1, WallType::WEAK);
//		}
//
//		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() / 2, 7 - 2 }, DOWN, 1, WallType::WEAK);
//		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() / 2, 7 + 2 }, UP, 1, WallType::WEAK);
//		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() / 2 + 2, 7 }, LEFT, 1, WallType::WEAK);
//		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() / 2 + 2, 7 - 1 }, LEFT, 1, WallType::WEAK);
//		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() / 2 - 2, 7 - 1 }, RIGHT, 1, WallType::WEAK);
//		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() / 2 + 2, 7 + 1 }, LEFT, 1, WallType::WEAK);
//		gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() / 2 - 2, 7 + 1 }, RIGHT, 1, WallType::WEAK);
//
//		puzzleSolved = false;
//
//		break;
//
//
//	case 1:skip = 10;break;
//	case 2:
//
//		wallsToConvert = 0;
//		wallsPlacedIncorrectly = 0;
//
//		// Complete old garbage 		
//		for (GrdCoord coord : coorectWallPlacement)
//		{
//			if (linkGrid->link[coord.c][coord.r].Get_Num_Child() < 2) //Check si les murs convert sont bien placés
//				wallsPlacedIncorrectly++;
//			else
//				if (linkGrid->link[coord.c][coord.r].Get_Child(0)->Get_Type() == WallType::WEAK || linkGrid->link[coord.c][coord.r].Get_Child(1)->Get_Type() == WallType::WEAK)
//					wallsToConvert++; //Check si les murs sont bien convert
//		}
//
//
//		if (!wallsToConvert && !wallsPlacedIncorrectly && !blastP1.Is_Active())
//		{
//			puzzleSolved = true;
//			Cancel_Ev_Take_Your_Time();
//		}
//		else
//			gCurrPuzzleStep--;
//		break;
//
//	case 3:
//		Add_Spec(LEFT, 5);Add_Spec(RIGHT, 5);
//		Add_Spec(UP, 11);
//		Add_Spec(DOWN, 14);
//		Add_Spec(LEFT, 8);Add_Spec(RIGHT, 8);
//		break;
//
//	case 4:Add_Spec(LEFT, 5);break;
//	case 5:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
//	}
//}
//


//
//// Place walls correctly #1
//void Puzzle_3_5()
//{
//	static GrdCoord center = { linkGrid->Get_Cols() / 2, 7 };
//	static int distance = 2;
//	static bool puzzleSolved;
//	static int wallsToConvert;
//	static int wallsPlacedIncorrectly;
//
//	static GrdCoord coorectWallPlacement[] = {
//		center.c,center.r - distance,
//		center.c ,center.r + distance,
//		center.c - distance , center.r + 1,
//		center.c - distance,center.r - 1,
//	};
//
//	switch (gCurrPuzzleStep)
//	{
//	case 0:P1.Set_Position({ center.c ,center.r - 1 });				// Coord de départ du jouer
//		blastP1.Get_Ammo_Manager().Set_Ammo(0);// Quantité d'ammo
//		blastP1.Get_Ammo_Manager().Set_Nb_Emergency_Ammo(0);			// EXCEPTIONNAL
//		gCurrPuzzleStepMax = 12;
//
//		Ev_Take_Your_Time();
//
//		gGrids.Activate_Link(center, Modifier::FORCEFIELD);
//		gGrids.Activate_Link({ center.c - 1,center.r }, Modifier::FORCEFIELD);
//		gGrids.Activate_Link({ center.c + 1,center.r }, Modifier::FORCEFIELD);
//
//		//up 
//		for (int c = center.c - distance; c < center.c + distance + 1; c++)
//		{
//			for (GrdCoord coord : coorectWallPlacement)
//			{
//				if (Are_Equal({ c, center.r - distance }, coord))
//				{
//					gGrids.Make_Chain_Of_Walls({ c, center.r - distance }, UP, 1, WallType::ENERGIZED);
//					break;
//				}
//			}
//
//			gGrids.Make_Chain_Of_Walls({ c, center.r - distance }, UP, 1, WallType::REGULAR);
//		}
//
//		//down
//		for (int c = center.c - distance; c < center.c + distance + 1; c++)
//		{
//			for (GrdCoord coord : coorectWallPlacement)
//			{
//				if (Are_Equal({ c, center.r + distance }, coord))
//				{
//					gGrids.Make_Chain_Of_Walls({ c, center.r + distance }, DOWN, 1, WallType::ENERGIZED);
//					break;
//				}
//			}
//
//			gGrids.Make_Chain_Of_Walls({ c, center.r + distance }, DOWN, 1, WallType::REGULAR);
//		}
//
//		// Left 
//		for (int r = center.r - distance; r < center.r + distance + 1; r++)
//		{
//			for (GrdCoord coord : coorectWallPlacement)
//			{
//				if (Are_Equal({ center.c - distance, r }, coord))
//				{
//					gGrids.Make_Chain_Of_Walls({ center.c - distance, r }, LEFT, 1, WallType::ENERGIZED);
//					break;
//				}
//			}
//
//			gGrids.Make_Chain_Of_Walls({ center.c - distance, r }, LEFT, 1, WallType::REGULAR);
//		}
//
//		// right
//		for (int r = center.r - distance; r < center.r + distance + 1; r++)
//		{
//
//			for (GrdCoord coord : coorectWallPlacement)
//			{
//				if (Are_Equal({ center.c + distance, r }, coord))
//				{
//					gGrids.Make_Chain_Of_Walls({ center.c + distance, r }, RIGHT, 1, WallType::ENERGIZED);
//					break;
//				}
//			}
//
//			gGrids.Make_Chain_Of_Walls({ center.c + distance, r }, RIGHT, 1, WallType::REGULAR);
//		}
//
//		gGrids.Make_Chain_Of_Walls({ center.c - 1, center.r + distance }, UP, 1, WallType::ENERGIZED);
//		gGrids.Make_Chain_Of_Walls({ center.c - 1, center.r - distance }, DOWN, 1, WallType::ENERGIZED);
//		gGrids.Make_Chain_Of_Walls({ center.c + 1,	  center.r - distance }, DOWN, 1, WallType::ENERGIZED);
//		gGrids.Make_Chain_Of_Walls({ center.c + distance, center.r + 1 }, LEFT, 1, WallType::ENERGIZED);
//
//		puzzleSolved = false;
//		P1.Set_Hp(1);
//
//		break;
//
//
//	case 1:skip = 10;break;
//	case 2:
//
//		wallsToConvert = 0;
//		wallsPlacedIncorrectly = 0;
//
//		// Complete old garbage 		
//		for (GrdCoord coord : coorectWallPlacement)
//		{
//			if (linkGrid->link[coord.c][coord.r].Get_Num_Child() < 2) //Check si les murs convert sont bien placés
//				wallsPlacedIncorrectly++;
//			else
//				if (linkGrid->link[coord.c][coord.r].Get_Child(0)->Get_Type() == WallType::WEAK || linkGrid->link[coord.c][coord.r].Get_Child(1)->Get_Type() == WallType::WEAK)
//					wallsToConvert++; //Check si les murs sont bien convert
//		}
//
//
//		if (!wallsToConvert && !wallsPlacedIncorrectly && !blastP1.Is_Active())
//		{
//			puzzleSolved = true;
//			Cancel_Ev_Take_Your_Time();
//		}
//		else
//			gCurrPuzzleStep--;
//		break;
//
//	case 3:
//		Add_Spec(RIGHT, 5);
//		Add_Spec(UP, 11);
//		Add_Spec(DOWN, 11);
//		Add_Spec(LEFT, 8);
//		break;
//
//	case 4:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
//	}
//}

//
//// Take your time #3 ! The final one
//// Prepare yourself for glorious copy-pasta
//void Puzzle_3_20()
//{
//	static GrdCoord center;center = { linkGrid->Get_Cols() / 2, 7 };
//	static int distance = 3;
//	static bool puzzleSolved;
//	static int wallsToConvert;
//	static int wallsPlacedIncorrectly;
//	static bool correctWallFound;
//	static GrdCoord correctWeakWallPlacement[] = {
//		center.c,			center.r - distance,
//		center.c - 2,		center.r - distance,
//		center.c + 2,		center.r - distance,
//		center.c - distance,center.r + 2 ,
//		center.c + 2,		center.r + distance,
//		center.c,			center.r + distance
//	};
//
//	static GrdCoord correctEnergizedWallsPlacement[] = {
//	center.c - distance,		center.r - 1,
//	center.c - distance,		center.r + 1,
//	center.c - 1,				center.r - distance,
//	center.c - 1,				center.r + distance,
//	center.c + distance,		center.r - 1,
//	center.c + 1,				center.r - distance
//	};
//
//	switch (gCurrPuzzleStep)
//	{
//	case 0:P1.Set_Position({ center.c, center.r - 1 });				// Coord de départ du jouer
//		blastP1.Get_Ammo_Manager().Set_Ammo(0);// Quantité d'ammo
//		blastP1.Get_Ammo_Manager().Set_Nb_Emergency_Ammo(0);			// EXCEPTIONNAL
//		gCurrPuzzleStepMax = 12;
//
//
//		Ev_Take_Your_Time();
//		gGrids.Activate_Link(center, Modifier::FORCEFIELD);
//		gGrids.Activate_Link({ center.c + 1,center.r }, Modifier::FORCEFIELD);
//		gGrids.Activate_Link({ center.c - 1,center.r }, Modifier::FORCEFIELD);
//		gGrids.Activate_Link({ center.c + 2,center.r }, Modifier::FORCEFIELD);
//		gGrids.Activate_Link({ center.c - 2,center.r }, Modifier::FORCEFIELD);
//
//		//up 
//		for (int c = center.c - distance; c < center.c + distance + 1; c++)
//		{
//			correctWallFound = false;
//
//			for (GrdCoord coord : correctWeakWallPlacement)
//			{
//				if (Are_Equal({ c, center.r - distance }, coord))
//				{
//					gGrids.Make_Chain_Of_Walls({ c, center.r - distance }, UP, 1, WallType::REGULAR);
//					break;
//				}
//			}
//
//			if (!correctWallFound)
//				for (GrdCoord coord : correctEnergizedWallsPlacement)
//				{
//					if (Are_Equal({ c, center.r - distance }, coord))
//					{
//						gGrids.Make_Chain_Of_Walls({ c, center.r - distance }, UP, 1, WallType::ENERGIZED);
//						break;
//					}
//				}
//
//			if (!correctWallFound)
//				gGrids.Make_Chain_Of_Walls({ c, center.r - distance }, UP, 1, WallType::WEAK);
//		}
//
//		//down
//		for (int c = center.c - distance; c < center.c + distance + 1; c++)
//		{
//			correctWallFound = false;
//
//			for (GrdCoord coord : correctWeakWallPlacement)
//			{
//				if (Are_Equal({ c, center.r + distance }, coord))
//				{
//					gGrids.Make_Chain_Of_Walls({ c, center.r + distance }, DOWN, 1, WallType::REGULAR);
//					break;
//				}
//			}
//
//			if (!correctWallFound)
//				for (GrdCoord coord : correctEnergizedWallsPlacement)
//				{
//					if (Are_Equal({ c, center.r + distance }, coord))
//					{
//						gGrids.Make_Chain_Of_Walls({ c, center.r + distance }, DOWN, 1, WallType::ENERGIZED);
//						break;
//					}
//				}
//
//			if (!correctWallFound)
//				gGrids.Make_Chain_Of_Walls({ c, center.r + distance }, DOWN, 1, WallType::WEAK);
//		}
//
//		// Left 
//		for (int r = center.r - distance; r < center.r + distance + 1; r++)
//		{
//			correctWallFound = false;
//
//			for (GrdCoord coord : correctWeakWallPlacement)
//			{
//				if (Are_Equal({ center.c - distance, r }, coord))
//				{
//					gGrids.Make_Chain_Of_Walls({ center.c - distance, r }, LEFT, 1, WallType::REGULAR);
//					break;
//				}
//			}
//
//			if (!correctWallFound)
//				for (GrdCoord coord : correctEnergizedWallsPlacement)
//				{
//					if (Are_Equal({ center.c - distance, r }, coord))
//					{
//						gGrids.Make_Chain_Of_Walls({ center.c - distance, r }, LEFT, 1, WallType::ENERGIZED);
//						break;
//					}
//				}
//
//			if (!correctWallFound)
//				gGrids.Make_Chain_Of_Walls({ center.c - distance, r }, LEFT, 1, WallType::WEAK);
//		}
//
//		// right
//		for (int r = center.r - distance; r < center.r + distance + 1; r++)
//		{
//			correctWallFound = false;
//
//			for (GrdCoord coord : correctWeakWallPlacement)
//			{
//				if (Are_Equal({ center.c + distance, r }, coord))
//				{
//					gGrids.Make_Chain_Of_Walls({ center.c + distance, r }, RIGHT, 1, WallType::REGULAR);
//					break;
//				}
//			}
//
//			if (!correctWallFound)
//				for (GrdCoord coord : correctEnergizedWallsPlacement)
//				{
//					if (Are_Equal({ center.c + distance, r }, coord))
//					{
//						gGrids.Make_Chain_Of_Walls({ center.c + distance, r }, RIGHT, 1, WallType::ENERGIZED);
//						break;
//					}
//				}
//
//			if (!correctWallFound)
//				gGrids.Make_Chain_Of_Walls({ center.c + distance, r }, RIGHT, 1, WallType::WEAK);
//		}
//
//		gGrids.Make_Chain_Of_Walls({ center.c, center.r + distance }, UP, 1, WallType::WEAK);
//		gGrids.Make_Chain_Of_Walls({ center.c + 2, center.r + distance }, UP, 1, WallType::WEAK);
//		gGrids.Make_Chain_Of_Walls({ center.c + 1, center.r + distance }, UP, 1, WallType::ENERGIZED);
//		gGrids.Make_Chain_Of_Walls({ center.c - 1 , center.r - distance }, DOWN, 1, WallType::WEAK);
//		gGrids.Make_Chain_Of_Walls({ center.c - 2 , center.r - distance }, DOWN, 1, WallType::WEAK);
//		gGrids.Make_Chain_Of_Walls({ center.c , center.r - distance }, DOWN, 1, WallType::ENERGIZED);
//		gGrids.Make_Chain_Of_Walls({ center.c + 2 , center.r - distance }, DOWN, 1, WallType::ENERGIZED);
//		gGrids.Make_Chain_Of_Walls({ center.c + distance, center.r - 1 }, LEFT, 1, WallType::WEAK);
//		gGrids.Make_Chain_Of_Walls({ center.c + distance, center.r + 1 }, LEFT, 1, WallType::ENERGIZED);
//		gGrids.Make_Chain_Of_Walls({ center.c - distance, center.r + 1 }, RIGHT, 1, WallType::WEAK);
//		gGrids.Make_Chain_Of_Walls({ center.c - distance, center.r - 1 }, RIGHT, 1, WallType::ENERGIZED);
//		gGrids.Make_Chain_Of_Walls({ center.c - distance, center.r + 2 }, RIGHT, 1, WallType::ENERGIZED);
//
//		puzzleSolved = false;
//
//
//		break;
//
//
//	case 1: skip = 10;break;
//	case 2:
//		wallsToConvert = 0;
//		wallsPlacedIncorrectly = 0;
//
//		for (GrdCoord coord : correctWeakWallPlacement)
//		{
//			if (linkGrid->link[coord.c][coord.r].Get_Num_Child() < 2) //Check si les murs convert sont bien placés
//				wallsPlacedIncorrectly++;
//			else
//				if (linkGrid->link[coord.c][coord.r].Get_Child(0)->Get_Type() == WallType::WEAK || linkGrid->link[coord.c][coord.r].Get_Child(1)->Get_Type() == WallType::WEAK)
//					wallsToConvert++; //Check si les murs sont bien convert
//		}
//
//		for (GrdCoord coord : correctEnergizedWallsPlacement)
//		{
//			if (linkGrid->link[coord.c][coord.r].Get_Num_Child() < 2)
//				wallsPlacedIncorrectly++;
//			else
//				if (linkGrid->link[coord.c][coord.r].Get_Child(0)->Get_Type() != WallType::ENERGIZED || linkGrid->link[coord.c][coord.r].Get_Child(1)->Get_Type() != WallType::ENERGIZED)
//					wallsToConvert++;
//		}
//
//
//		if (!wallsToConvert && !wallsPlacedIncorrectly && !blastP1.Is_Active())
//		{
//			puzzleSolved = true;
//			Cancel_Ev_Take_Your_Time();
//		}
//		else
//			gCurrPuzzleStep--;
//		break;
//
//	case 3:
//		Add_Spec(UP, 10);
//		Add_Spec(RIGHT, 4);Add_Spec(LEFT, 4);
//		Add_Spec(RIGHT, 9);Add_Spec(LEFT, 9);
//		break;
//
//	case 4:
//		Add_Spec(UP, 10);
//		Add_Spec(RIGHT, 4);Add_Spec(LEFT, 4);
//		break;
//
//	case 5:
//		Add_Spec(UP, 10);
//		Add_Spec(DOWN, 15);
//		Add_Spec(RIGHT, 4);
//		Add_Spec(LEFT, 9);
//		break;
//
//	case 6:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
//	}
//}

//
//// Take your time #3 ! The final one
//// Prepare yourself for glorious copy-pasta
//void Puzzle_3_19()
//{
//	static GrdCoord center;center = { linkGrid->Get_Cols() / 2, 7 };
//	static int distance = 3;
//	static bool puzzleSolved;
//	static int wallsToConvert;
//	static int wallsPlacedIncorrectly;
//	static bool correctWallFound;
//	static GrdCoord correctWeakWallPlacement[] = {
//		center.c,			center.r - distance,
//		center.c - 2,		center.r - distance,
//		center.c + 2,		center.r - distance,
//		center.c - distance,center.r + 2 ,
//		center.c + 2,		center.r + distance,
//		center.c,			center.r + distance
//	};
//
//	static GrdCoord correctEnergizedWallsPlacement[] = {
//	center.c - distance,		center.r - 1,
//	center.c - distance,		center.r + 1,
//	center.c - 1,				center.r - distance,
//	center.c - 1,				center.r + distance,
//	center.c + distance,		center.r - 1,
//	center.c + 1,				center.r - distance
//	};
//
//	switch (gCurrPuzzleStep)
//	{
//	case 0:P1.Set_Position({ center.c, center.r - 1 });				// Coord de départ du jouer
//		blastP1.Get_Ammo_Manager().Set_Ammo(0);// Quantité d'ammo
//		gCurrPuzzleStepMax = 12;
//
//
//		Ev_Take_Your_Time();
//		gGrids.Activate_Link(center, Modifier::FORCEFIELD);
//		gGrids.Activate_Link({ center.c + 1,center.r }, Modifier::FORCEFIELD);
//		gGrids.Activate_Link({ center.c - 1,center.r }, Modifier::FORCEFIELD);
//		gGrids.Activate_Link({ center.c + 2,center.r }, Modifier::FORCEFIELD);
//		gGrids.Activate_Link({ center.c - 2,center.r }, Modifier::FORCEFIELD);
//
//		//up 
//		for (int c = center.c - distance; c < center.c + distance + 1; c++)
//		{
//			correctWallFound = false;
//
//			for (GrdCoord coord : correctWeakWallPlacement)
//			{
//				if (Are_Equal({ c, center.r - distance }, coord))
//				{
//					gGrids.Make_Chain_Of_Walls({ c, center.r - distance }, UP, 1, WallType::REGULAR);
//					break;
//				}
//			}
//
//			if (!correctWallFound)
//				for (GrdCoord coord : correctEnergizedWallsPlacement)
//				{
//					if (Are_Equal({ c, center.r - distance }, coord))
//					{
//						gGrids.Make_Chain_Of_Walls({ c, center.r - distance }, UP, 1, WallType::ENERGIZED);
//						break;
//					}
//				}
//
//			if (!correctWallFound)
//				gGrids.Make_Chain_Of_Walls({ c, center.r - distance }, UP, 1, WallType::WEAK);
//		}
//
//		//down
//		for (int c = center.c - distance; c < center.c + distance + 1; c++)
//		{
//			correctWallFound = false;
//
//			for (GrdCoord coord : correctWeakWallPlacement)
//			{
//				if (Are_Equal({ c, center.r + distance }, coord))
//				{
//					gGrids.Make_Chain_Of_Walls({ c, center.r + distance }, DOWN, 1, WallType::REGULAR);
//					break;
//				}
//			}
//
//			if (!correctWallFound)
//				for (GrdCoord coord : correctEnergizedWallsPlacement)
//				{
//					if (Are_Equal({ c, center.r + distance }, coord))
//					{
//						gGrids.Make_Chain_Of_Walls({ c, center.r + distance }, DOWN, 1, WallType::ENERGIZED);
//						break;
//					}
//				}
//
//			if (!correctWallFound)
//				gGrids.Make_Chain_Of_Walls({ c, center.r + distance }, DOWN, 1, WallType::WEAK);
//		}
//
//		// Left 
//		for (int r = center.r - distance; r < center.r + distance + 1; r++)
//		{
//			correctWallFound = false;
//
//			for (GrdCoord coord : correctWeakWallPlacement)
//			{
//				if (Are_Equal({ center.c - distance, r }, coord))
//				{
//					gGrids.Make_Chain_Of_Walls({ center.c - distance, r }, LEFT, 1, WallType::REGULAR);
//					break;
//				}
//			}
//
//			if (!correctWallFound)
//				for (GrdCoord coord : correctEnergizedWallsPlacement)
//				{
//					if (Are_Equal({ center.c - distance, r }, coord))
//					{
//						gGrids.Make_Chain_Of_Walls({ center.c - distance, r }, LEFT, 1, WallType::ENERGIZED);
//						break;
//					}
//				}
//
//			if (!correctWallFound)
//				gGrids.Make_Chain_Of_Walls({ center.c - distance, r }, LEFT, 1, WallType::WEAK);
//		}
//
//		// right
//		for (int r = center.r - distance; r < center.r + distance + 1; r++)
//		{
//			correctWallFound = false;
//
//			for (GrdCoord coord : correctWeakWallPlacement)
//			{
//				if (Are_Equal({ center.c + distance, r }, coord))
//				{
//					gGrids.Make_Chain_Of_Walls({ center.c + distance, r }, RIGHT, 1, WallType::REGULAR);
//					break;
//				}
//			}
//
//			if (!correctWallFound)
//				for (GrdCoord coord : correctEnergizedWallsPlacement)
//				{
//					if (Are_Equal({ center.c + distance, r }, coord))
//					{
//						gGrids.Make_Chain_Of_Walls({ center.c + distance, r }, RIGHT, 1, WallType::ENERGIZED);
//						break;
//					}
//				}
//
//			if (!correctWallFound)
//				gGrids.Make_Chain_Of_Walls({ center.c + distance, r }, RIGHT, 1, WallType::WEAK);
//		}
//
//		gGrids.Make_Chain_Of_Walls({ center.c, center.r + distance }, UP, 1, WallType::WEAK);
//		gGrids.Make_Chain_Of_Walls({ center.c + 2, center.r + distance }, UP, 1, WallType::WEAK);
//		gGrids.Make_Chain_Of_Walls({ center.c + 1, center.r + distance }, UP, 1, WallType::ENERGIZED);
//		gGrids.Make_Chain_Of_Walls({ center.c - 1 , center.r - distance }, DOWN, 1, WallType::WEAK);
//		gGrids.Make_Chain_Of_Walls({ center.c - 2 , center.r - distance }, DOWN, 1, WallType::WEAK);
//		gGrids.Make_Chain_Of_Walls({ center.c , center.r - distance }, DOWN, 1, WallType::ENERGIZED);
//		gGrids.Make_Chain_Of_Walls({ center.c + 2 , center.r - distance }, DOWN, 1, WallType::ENERGIZED);
//		gGrids.Make_Chain_Of_Walls({ center.c + distance, center.r - 1 }, LEFT, 1, WallType::WEAK);
//		gGrids.Make_Chain_Of_Walls({ center.c + distance, center.r + 1 }, LEFT, 1, WallType::ENERGIZED);
//		gGrids.Make_Chain_Of_Walls({ center.c - distance, center.r + 1 }, RIGHT, 1, WallType::WEAK);
//		gGrids.Make_Chain_Of_Walls({ center.c - distance, center.r - 1 }, RIGHT, 1, WallType::ENERGIZED);
//		gGrids.Make_Chain_Of_Walls({ center.c - distance, center.r + 2 }, RIGHT, 1, WallType::ENERGIZED);
//
//		puzzleSolved = false;
//
//
//		break;
//
//
//	case 1: skip = 10;break;
//	case 2:
//		wallsToConvert = 0;
//		wallsPlacedIncorrectly = 0;
//
//		for (GrdCoord coord : correctWeakWallPlacement)
//		{
//			if (linkGrid->link[coord.c][coord.r].Get_Num_Child() < 2) //Check si les murs convert sont bien placés
//				wallsPlacedIncorrectly++;
//			else
//				if (linkGrid->link[coord.c][coord.r].Get_Child(0)->Get_Type() == WallType::WEAK || linkGrid->link[coord.c][coord.r].Get_Child(1)->Get_Type() == WallType::WEAK)
//					wallsToConvert++; //Check si les murs sont bien convert
//		}
//
//		for (GrdCoord coord : correctEnergizedWallsPlacement)
//		{
//			if (linkGrid->link[coord.c][coord.r].Get_Num_Child() < 2)
//				wallsPlacedIncorrectly++;
//			else
//				if (linkGrid->link[coord.c][coord.r].Get_Child(0)->Get_Type() != WallType::ENERGIZED || linkGrid->link[coord.c][coord.r].Get_Child(1)->Get_Type() != WallType::ENERGIZED)
//					wallsToConvert++;
//		}
//
//
//		if (!wallsToConvert && !wallsPlacedIncorrectly && !blastP1.Is_Active())
//		{
//			puzzleSolved = true;
//			Cancel_Ev_Take_Your_Time();
//		}
//		else
//			gCurrPuzzleStep--;
//		break;
//
//	case 3:
//		Add_Spec(UP, 10);
//		Add_Spec(RIGHT, 4);Add_Spec(LEFT, 4);
//		Add_Spec(RIGHT, 9);Add_Spec(LEFT, 9);
//		break;
//
//	case 4:
//		Add_Spec(UP, 10);
//		Add_Spec(RIGHT, 4);Add_Spec(LEFT, 4);
//		break;
//
//	case 5:
//		Add_Spec(UP, 10);
//		Add_Spec(DOWN, 15);
//		Add_Spec(RIGHT, 4);
//		Add_Spec(LEFT, 9);
//		break;
//
//	case 6:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
//	}
//}
