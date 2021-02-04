

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
		seenFinalHour = false;

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
	case 0:P1.Set_Position({ 4, 3 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(0);// Quantité d'ammo
		gCurrPuzzleStepMax = 12;

		gGrids.Make_Box_Of_Blockers({ 0,0 }, { 26,14 });

		gGrids.Make_Chain_Of_Walls({ 2 , 1 }, DOWN, 1, WallType::WEAK);
		gGrids.Make_Chain_Of_Walls({ 3 , 1 }, DOWN, 1, WallType::WEAK);
		gGrids.Make_Chain_Of_Walls({ 4 , 1 }, DOWN, 1);

		gGrids.Make_Chain_Of_Walls({ 8 , 1 }, LEFT, 2, WallType::WEAK);
		gGrids.Activate_Link({ 8, 2 });

		gGrids.Activate_Link({ 6 , 8 });
		gGrids.Activate_Link({ 7 , 8 });
		gGrids.Make_Chain_Of_Walls({ 8 , 7 }, UP, 1, WallType::WEAK);
		gGrids.Make_Chain_Of_Walls({ 9 , 7 }, UP, 1, WallType::WEAK);
		gGrids.Make_Chain_Of_Walls({ 10 , 7 }, UP, 1);

		gGrids.Activate_Link({ 23 , 6 });
		gGrids.Make_Chain_Of_Walls({ 23 , 7 }, LEFT, 2, WallType::WEAK);


		gGrids.Activate_Link({ 22 , 13 });
		gGrids.Activate_Link({ 21 , 13 });
		gGrids.Make_Chain_Of_Walls({23 , 12 }, UP, 1, WallType::WEAK);


		gGrids.Activate_Link({ 2 , 11 });
		gGrids.Activate_Link({ 3 , 12 });

		break;

	case 1:Add_Spec(LEFT, 1); instantSpawn = 1; break;
	case 2:Add_Spec(UP, 7); Add_Spec(UP, 6); Add_Spec(LEFT, 7);Add_Spec(LEFT, 6);break;
	case 3:Add_Spec(LEFT, 7); skip = 8;break;
	case 4:Add_Spec(DOWN, 21);Add_Spec(DOWN, 22);skip = 5;break;
	case 5:Add_Spec(RIGHT, 12);break;
	case 6:Add_Spec(RIGHT, 12);Add_Spec(RIGHT, 11);skip = 15;break;
	case 10:MsgQueue::Register(CHECKPOINT_REACHED); break; // CHECKPOINTHERE CHECKPOINTHERE CHECKPOINTHERE
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
	
	static int distance = 5;

	switch (gCurrPuzzleStep)
	{
	case 0:P1.Set_Position({ distance - 4,7 });				// Coord de départ du jouer
		blastP1.Get_Ammo_Manager().Set_Ammo(0);// Quantité d'ammo
		blastP1.Get_Ammo_Manager().Set_Nb_Emergency_Ammo(0);			// EXCEPTIONNAL
		gCurrPuzzleStepMax = 12;


		for (int c = 0; c <= distance; c++)
		{
			gGrids.Activate_Link({ c , 5 }, Modifier::BLOCKER);
			gGrids.Activate_Link({ c , 9 }, Modifier::BLOCKER);
		}
		for (int r = 6; r <= 9; r++)
		{
			gGrids.Activate_Link({ distance  , r }, Modifier::BLOCKER);
		}


		gGrids.Make_Chain_Of_Walls({ distance - 1 , 6 }, LEFT, 1, WallType::REGULAR);
		gGrids.Make_Chain_Of_Walls({ distance - 2 , 6 }, LEFT, 1, WallType::WEAK);

		gGrids.Make_Chain_Of_Walls({ distance - 1 , 7 }, LEFT, 1, WallType::WEAK);
		gGrids.Make_Chain_Of_Walls({ distance - 2 , 7 }, LEFT, 1, WallType::WEAK);

		gGrids.Make_Chain_Of_Walls({ distance - 1 , 8 }, LEFT, 1, WallType::WEAK);
		gGrids.Make_Chain_Of_Walls({ distance - 2 , 8 }, LEFT, 1, WallType::REGULAR);
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
		
		gGrids.Activate_Link({ 12 , 11 }, Modifier::BLOCKER);
		gGrids.Activate_Link({ 12 , 10 }, Modifier::BLOCKER);


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
		blastP1.Get_Ammo_Manager().Set_Nb_Emergency_Ammo(0);	// Cheese prevention engaged
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
		blastP1.Get_Ammo_Manager().Set_Ammo(15);
		//blastP1.Get_Ammo_Manager().Set_Ammo(14);
		gCurrPuzzleStepMax = 12;

		upOrDown = false;
		leftOrRight = LEFT;
		shapesRemaining = SHAPES_TO_KILL;
		crd = { Find_Ctr_String_X(_1) - 1, 6 };


		// DEBUG 
		// *****
		seenFinalHour = 1;


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

		for (int c = 0; c < linkGrid->Get_Cols(); c++)
		{
			//gGrids.Make_Chain_Of_Walls({ c,5 }, UP, 1);
			//gGrids.Make_Chain_Of_Walls({ c,9 }, DOWN, 1);
			gGrids.Activate_Link({ c,5 });
			gGrids.Activate_Link({ c,9 });
		}

		gGrids.Activate_Link({ 11,7 });
		gGrids.Activate_Link({ 15,7 });


		for (int c = 12; c < 15; c++)
		{
			ItemSpawner::Spawn_This_Item(ItemType::AMMO, { c,6 });
			ItemSpawner::Spawn_This_Item(ItemType::AMMO, { c,8 });

			if (c != 13)
				ItemSpawner::Spawn_This_Item(ItemType::AMMO, { c,7 });
		}

		// DEBUG
		/// ****
		//gCurrPuzzleStep = 15;//PHASE 2
		//gCurrPuzzleStep = 24;//PHASE 3
		//gCurrPuzzleStep = 31;//PHASE 4
		//gCurrPuzzleStep = 50;//PHASE 5
		//gCurrPuzzleStep = 63;//PHASE 6
		//gCurrPuzzleStep = 82;//PHASE 7
		break;


	case 3: dir = UP;Add(2);Set_Interval(dir, 11, 14);skip = 3;break;
	case 4: Add(3);Set_Interval(dir, 12, 15);skip = 7;break;
	case 5: Add(1);Set_Interval(dir, 11, 15);break;
	case 6: dir = LEFT;Add_Spec(LEFT, 6); break;
	case 7:Add(1);Set_Interval(LEFT, 5, 7);break;
	case 8:Add(1);Set_Interval(RIGHT, 5, 7);break;
	case 9:Add(1);Set_Interval(LEFT, 5, 7);break;
	case 10:Add_Spec(RIGHT, 8);break;
	case 11:Add(1);Set_Interval(LEFT, 6, 8);break;

		// Phase 2 !
	case 16:
		if (gAllBotMeta.alive || !P1.Get_HP())
			gCurrPuzzleStep--;
		else
		{
			Clear_Map();

			//blastP1.Get_Ammo_Manager().Activate();
			//blastP1.Get_Ammo_Manager().Set_Ammo(12);
			P1.Set_Position({ 13,7 });
			Set_Ev_Spawn_Player(3);
			MsgQueue::Register(LOCK_PLAYER);

			for (int c = 0; c < linkGrid->Get_Cols(); c++)
			{
				if (c < 11 && c > 4)
				{
					ItemSpawner::Spawn_This_Item(ItemType::AMMO, { c,6 });
					ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { c,8 });
				}
				else
				{
					if (c <= 4)
					{
						ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { c,6 });
						ItemSpawner::Spawn_This_Item(ItemType::AMMO, { c,8 });
					}
				}

				if (c > 16 && c < 22)
				{
					ItemSpawner::Spawn_This_Item(ItemType::AMMO, { c,6 });
					ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { c,8 });
				}
				else
				{
					if (c >= 22)
					{
						ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { c,6 });
						ItemSpawner::Spawn_This_Item(ItemType::AMMO, { c,8 });
					}
				}
			}
			for (int c = 0; c < linkGrid->Get_Cols(); c++)
			{
				if (c < 11 && c > 15)
					ItemSpawner::Spawn_This_Item(ItemType::AMMO, { c,7 });

			}

			for (int c = 0; c < linkGrid->Get_Cols(); c++)
			{
				gGrids.Activate_Link({ c,5 }, Modifier::BLOCKER);
				gGrids.Activate_Link({ c,9 }, Modifier::BLOCKER);
			}

			gGrids.Activate_Link({ 11,7 }, Modifier::BLOCKER);
			gGrids.Activate_Link({ 15,7 }, Modifier::BLOCKER);


			for (int c = 12; c < 15; c++)
			{
				ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { c,6 });
				ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { c,8 });

				if (c != 13)
					ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { c,7 });
			}

		}
		break;

	case 17:dir = LEFT; /*Add(2);Set_Interval(dir, 5, 9); skip = 7;*/ skip = 3; break;
	case 18:Add(2);Set_Interval(dir, 5, 9);skip = 3;		 break;
	case 19:Add(2);Set_Interval(dir, 5, 9);skip = 3;		 break;
	case 20:Add(2);Set_Interval(dir, 5, 9);skip = 3;		 break;
	case 21:Add(2);Set_Interval(dir, 5, 9);skip = 10;		 break;
	case 22:dir = UP; Add(2);Set_Interval(dir, 11, 13); skip = 3;break;
	case 23:Add(2);Set_Interval(dir, 12, 14);skip = 4;break;
	case 24:Add(2);Set_Interval(dir, 11, 14);break;

		// PHASE 3
		// *******
	case 25:
		if (gAllBotMeta.alive || !P1.Get_HP())
			gCurrPuzzleStep--;
		else
		{
			Clear_Map();

			blastP1.Get_Ammo_Manager().Activate();
			//blastP1.Get_Ammo_Manager().Set_Ammo(12);

			P1.Set_Position({ 13,6 });
			Set_Ev_Spawn_Player(3);
			MsgQueue::Register(LOCK_PLAYER);


			for (int c = 0; c < linkGrid->Get_Cols(); c++)
			{
				gGrids.Activate_Link({ c,5 }, Modifier::BUFFER);
				gGrids.Activate_Link({ c,9 }, Modifier::BUFFER);
			}

			/*gGrids.Activate_Link({ 11,7 }, Modifier::BUFFER);
			gGrids.Activate_Link({ 15,7 }, Modifier::BUFFER);*/
			gGrids.Activate_Link({ 11,8 }, Modifier::BUFFER);
			gGrids.Activate_Link({ 15,6 }, Modifier::BUFFER);
			gGrids.Activate_Link({ 13,7 }, Modifier::BUFFER);


			ItemSpawner::Spawn_This_Item(ItemType::AMMO, { 14,6 });
			ItemSpawner::Spawn_This_Item(ItemType::AMMO, { 12,8 });
			ItemSpawner::Spawn_This_Item(ItemType::AMMO, { 12,7 });
			ItemSpawner::Spawn_This_Item(ItemType::AMMO, { 14,7 });
		}
		break;

	case 26:dir = LEFT; skip = 3;break;
	case 27:Add_Spec(UP, 11); Add_Spec(DOWN, 11); skip = 2;break;
	case 28:Add_Spec(UP, 14);Add_Spec(DOWN, 14);skip = 2;break;
	case 29:Add_Spec(UP, 12);Add_Spec(DOWN, 12);skip = 2;break;
	case 30:Add_Spec(UP, 13);Add_Spec(DOWN, 13);break;
	case 31:Add(8);Set_Interval(LEFT, 5, 9);Set_Interval(RIGHT, 5,9);  skip = 23;break;

		// PHASE 4
		// *******
	case 32:
		if (gAllBotMeta.alive || !P1.Get_HP())
			gCurrPuzzleStep--;
		else
		{
			Clear_Map();

			blastP1.Get_Ammo_Manager().Activate();
			//blastP1.Get_Ammo_Manager().Set_Ammo(16);

			P1.Set_Position({ 13,6 });
			Set_Ev_Spawn_Player(3);
			MsgQueue::Register(LOCK_PLAYER);

			for (int c = 0; c < linkGrid->Get_Cols(); c++)
			{
				gGrids.Make_Chain_Of_Walls({ c,5 }, UP, 1);
				gGrids.Make_Chain_Of_Walls({ c,9 }, DOWN, 1);
			}

			for (int c = 1; c <= 4 ; c++)
			{
				gGrids.Activate_Link({ c,7 }, Modifier::FORCEFIELD);
				gGrids.Activate_Link({ c,8 }, Modifier::FORCEFIELD);
			}

			for (int c = 22; c <= 25; c++)
			{
				gGrids.Activate_Link({ c,6 }, Modifier::FORCEFIELD);
				gGrids.Activate_Link({ c,7 }, Modifier::FORCEFIELD);
			}


			for (int r = 6; r < 9; r++)
			{
				gGrids.Activate_Link({ 7,r }, Modifier::FORCEFIELD);
				gGrids.Activate_Link({ 19,r }, Modifier::FORCEFIELD);
			}

			// Walls à bouger
			gGrids.Make_Chain_Of_Walls({ 0,6 }, RIGHT, 4, WallType::WEAK);
			gGrids.Make_Chain_Of_Walls({ 26,8 }, LEFT, 4, WallType::WEAK);

			gGrids.Make_Chain_Of_Walls({ 11,8 }, UP, 2, WallType::WEAK);
			gGrids.Make_Chain_Of_Walls({ 15,6 }, DOWN, 2, WallType::WEAK);
			
			gGrids.Activate_Link({ 10,6 }, Modifier::FORCEFIELD);
			gGrids.Activate_Link({ 10,7 }, Modifier::FORCEFIELD);
			gGrids.Activate_Link({ 9,6 }, Modifier::FORCEFIELD);
			gGrids.Activate_Link({ 9,7 }, Modifier::FORCEFIELD);

			gGrids.Activate_Link({ 17,7 }, Modifier::FORCEFIELD);
			gGrids.Activate_Link({ 17,8 }, Modifier::FORCEFIELD);
			gGrids.Activate_Link({ 16,7 }, Modifier::FORCEFIELD);
			gGrids.Activate_Link({ 16,8 }, Modifier::FORCEFIELD);


			// Anchor points
			gGrids.Make_Chain_Of_Walls({ 13,8 }, UP, 1, WallType::ENERGIZED);
			gGrids.Activate_Link({ 5,7 });
			gGrids.Activate_Link({ 21,7 });
		}
		break;

	case 33:dir = LEFT; skip = 5; break;
	case 34:Add_Spec(UP, 9);Add_Spec(DOWN, 9);skip = 1;break;
	case 35:Add_Spec(UP, 16);Add_Spec(DOWN, 16);skip = 11;break;
	case 36:Add_Spec(LEFT, 7); skip = 1;break;
	case 37:Add_Spec(LEFT, 7); skip = 1;break;
	case 38:Add_Spec(LEFT, 7); skip = 1;break;
	case 39:Add_Spec(LEFT, 7); skip = 1;break;
	case 41:Add_Spec(RIGHT, 6);break;
	case 44:Add_Spec(RIGHT, 6);break;
	case 45:Add_Spec(RIGHT, 6);break;
	case 46:Add_Spec(RIGHT, 6);break;

		// PHASE 5, the bait
		// *****************
	case 47:

		if (gAllBotMeta.alive || !P1.Get_HP())
			gCurrPuzzleStep--;
		else
		{
			Clear_Map();
			blastP1.Get_Ammo_Manager().Activate();

			P1.Set_Position({ 13,11 });
			Set_Ev_Spawn_Player(3);
			MsgQueue::Register(LOCK_PLAYER);

			gGrids.Activate_Link({ 13, 6 }, Modifier::REGULAR);
		}
		break;

	case 49:break;
	case 50:Add(300); skip = 4;break;
	case 51:
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
