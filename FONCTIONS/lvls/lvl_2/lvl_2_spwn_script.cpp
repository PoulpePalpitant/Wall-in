

#include "lvl_2_spwn_script.h"
#include "../../time/spawn_cycle.h"
#include "../../grid/managegrids.h"
#include "../../spawns/bots_to_spawn.h"
#include "../../events/msg_dispatcher.h"
#include "../lvl_script.h"

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
		int skip = 0;		

		LVL2_PUZZLES[gCurrentPuzzle[gCurrentLevel - 1]]();	// Script du puzzle
		gCurrPuzzleStep++;	// Prochain step du puzzle!

		if (skip)
			gSpwBotTimer.Add_Count(skip);
	}
}


void Puzzle_2_0(){}
void Puzzle_2_1(){}
void Puzzle_2_2(){}
void Puzzle_2_3(){}
void Puzzle_2_4(){}
void Puzzle_2_5(){}
void Puzzle_2_6(){}
void Puzzle_2_7(){}
void Puzzle_2_8(){}
void Puzzle_2_9(){}
void Puzzle_2_10(){}
void Puzzle_2_11(){}
void Puzzle_2_12(){}
void Puzzle_2_13(){}
void Puzzle_2_14(){}
void Puzzle_2_15(){}
void Puzzle_2_16(){}
void Puzzle_2_17(){}
void Puzzle_2_18(){}
void Puzzle_2_19(){}
void Puzzle_2_FINAL(){}