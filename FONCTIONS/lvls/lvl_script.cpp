
#include "lvl_script.h"

/* LEs LEvels*/
#include "../menu/menu_script.h"
#include "lvl_1/lvl_1_spwn_script.h"
#include "lvl_2/lvl_2_spwn_script.h"
#include "lvl_1/sub_lvl_1_script.h"

// Ceci est la cons�quence de moi qui est trop lazy pour apprendre � faire des scripts

const int NB_LVLS = 2;								// Nombre de niveau que j'ai fais
const int NUMWAVES[NB_LVLS] = { 250, 100 };			// Nombre de bot waves selon chaques niveaux. Indice 0 = lvl 1
const int FINALHOUR[NB_LVLS] = { 203, 80 };			// � quel wave le final hour aura lieu
const int NUM_PUZZLES[NB_LVLS] = { 18, 4 };		// Nombre de Puzzles dans chaque lvl

const int LVL2_CHECKPOINT[] = {  20, 40, 67,  80 };
const int LVL3_CHECKPOINT[] = { 0 };
const int LVL4_CHECKPOINT[] = { 0 };
const int LVL5_CHECKPOINT[] = { 0 };


short gCurrentLevel = 0;		// Le niveau actuel!!1
short gCurrentStage = 0;		// Chaque niveau peut avoir plusieurs stages
short gCurrentPuzzle[NB_LVLS] = {};	// Le checkpoint que le joueur � r�ussie � reach durant chaque niveau. Si 0, le joueur na reach aucun checkpoint encore


int gCurrPuzzleStep = 0;		// Le step du puzzle en cours, chaque puzzle start � 0. D�s qu'un botspawncycle est fait, on avance de 1. S'arr�te � currPuzzleStepMax
int gCurrPuzzleStepMax = 0;


bool gDayStarted = false;
bool gSkipStory = false;		// Quand le joueur start une game � partir du menu, il peut skipper la story pour arriver direct au lvevl
bool gRefreshStage = false;		// Refresh un stage
bool gRetryCheckpoint = false;		// Restart le niveau � partir d'un checkpoint

																		// +1 pas oblig� finalement, on dirait que �a le skip toujours, pt � cause du timer
void Peek_Lvl_Script()
{
	switch (gCurrentLevel)
	{
	case 0: break;
	case 1:	
		Lvl_1_Spwn_Script(); break;	// D�termine quel sera la prochaine wave de spawn
		case 2: Lvl_2_Spwn_Script(); break;
		/*case 3: Level_3_Script(); break;
		case 4: Level_4_Script(); break;
		case 5: Level_5_Script(); break;
		case 6: Level_6_Script(); break;
		case 7: Level_7_Script(); break;
		case 8: Level_8_Script();*/
	}
}
void Peek_Sub_Lvl_Script()
{
	switch (gCurrentStage)
	{
	case 0: break;	// Fait rien
	case 1:	Sub_Lvl_1_Script(); break;		// oublis pas de reset le sublevel d�s qu'il est termin�
		/*case 2: Level_2_Script(); break;
		case 3: Level_3_Script(); break;
		case 4: Level_4_Script(); break;
		case 5: Level_5_Script(); break;
		case 6: Level_6_Script(); break;
		case 7: Level_7_Script(); break;
		case 8: Level_8_Script();*/
	}



}

void Init_Puzzle() {
	gCurrPuzzleStep = 0;
	if (gCurrentLevel == 1)
		LVL1_PUZZLES[gCurrentPuzzle[gCurrentLevel - 1]]();

	gCurrPuzzleStep++;

}