
#include "lvl_script.h"

/* LEs LEvels*/
#include "../menu/menu_script.h"
#include "lvl_1/lvl_1_spwn_script.h"
#include "lvl_2/lvl_2_spwn_script.h"
#include "lvl_3/lvl_3_spwn_script.h"
#include "lvl_1/sub_lvl_1_script.h"
#include "../UI/console_output/render_list.h"

const int NB_LVLS = 3;								// Nombre de niveau que j'ai fais
const int NUM_PUZZLES[NB_LVLS] = { 18, 24,20 };		// Nombre de Puzzles dans chaque lvl


int gCurrentLevel = 0;		// Le niveau actuel!!1
int gCurrentStage = 0;		// Chaque niveau peut avoir plusieurs stages
int gCurrentPuzzle[NB_LVLS] = {};	// Le checkpoint que le joueur à réussie à reach durant chaque niveau. Si 0, le joueur na reach aucun checkpoint encore
int gUnlockedLevels[3] = {1,0,0};
int gLastLvlUnlocked = -1;

int gCurrPuzzleStep = 0;		// Le step du puzzle en cours, chaque puzzle start à 0. Dès qu'un botspawncycle est fait, on avance de 1. S'arrête à currPuzzleStepMax
int gCurrPuzzleStepMax = 0;

const short TUTO_TOTAL_STEPS = 7;
short tutoStep = 0;

bool gDayStarted = false;
bool gSkipTutorial = false;		
bool gRefreshStage = false;		// Refresh un stage
bool gRetryCheckpoint = false;		// Restart le niveau à partir d'un checkpoint
											
bool gameCompleted = false;

void Peek_Lvl_Script()
{
	switch (gCurrentLevel)
	{
	case 0: break;
	case 1:	Lvl_1_Spwn_Script(); break;	// Détermine quel sera la prochaine wave de spawn
	case 2: Lvl_2_Spwn_Script(); break;
	case 3: Lvl_3_Spwn_Script(); break;
	}
}


void Init_Puzzle() {
	gCurrPuzzleStep = 0;
	if (gCurrentLevel == 1)
		LVL1_PUZZLES[gCurrentPuzzle[gCurrentLevel - 1]]();
	else
		if (gCurrentLevel == 2)
			LVL2_PUZZLES[gCurrentPuzzle[gCurrentLevel - 1]]();
		else
			if (gCurrentLevel == 3)
				LVL3_PUZZLES[gCurrentPuzzle[gCurrentLevel - 1]]();
	
	gCurrPuzzleStep++;

}

void Draw_Tuto_Progression(bool progression) {
	if (progression)
		tutoStep++;

	ConsoleRender::Add_String("Tutorial Progress :", { 20, 4 }, LIGHT_GREEN);
	ConsoleRender::Add_String(std::to_string(tutoStep), { 40, 4 }, LIGHT_GREEN);
	ConsoleRender::Add_Char({ 41,4 }, '/', WHITE);
	ConsoleRender::Add_String(std::to_string(TUTO_TOTAL_STEPS), { 42, 4 }, LIGHT_GREEN);
}