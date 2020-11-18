
#include "lvl_script.h"

/* LEs LEvels*/
#include "../menu/menu_script.h"
#include "lvl_1/lvl_1_spwn_script.h"
#include "lvl_2/lvl_2_spwn_script.h"
#include "lvl_1/sub_lvl_1_script.h"

// Ceci est la conséquence de moi qui est trop lazy pour apprendre à faire des scripts

const int NB_LVLS = 2;								// Nombre de niveau que j'ai fais
const int NUMWAVES[NB_LVLS] = { 250, 100 };			// Nombre de bot waves selon chaques niveaux. Indice 0 = lvl 1
const int FINALHOUR[NB_LVLS] = { 203, 80 };			// À quel wave le final hour aura lieu
const int NUM_CHECKPOINT[NB_LVLS] = { 17, 4 };		// Nombre de checkpoint dans chaque lvl

//const int LVL1_CHECKPOINT[] = {  30, 49, 67, 100 }; //	VERSION 1:LEGACY: 
const int LVL1_CHECKPOINT[] = {  10, 19, 35, 40, 52,55, 68, 78, 95, 105, 108/*vertical start*/,116,139,154, 170,198,202};  //		VERSION PUZZLE checkpoint: + final hour est le dernier
const int LVL2_CHECKPOINT[] = {  20, 40, 67,  80 };
const int LVL3_CHECKPOINT[] = { 0 };
const int LVL4_CHECKPOINT[] = { 0 };
const int LVL5_CHECKPOINT[] = { 0 };

// Le joueur possède ce montant d'ammo durant un checkpoint
const int LVL1_BLAST_AMMO[] = {3,7,14,5, 12,  1, 20, 0, 0, 18, 10/*vertical start*/, 6, 0, 19, 37,41, 20  };
const int LVL2_BLAST_AMMO[] = { 20,20,20,20};

const GrdCoord LVL1_CHECKPOINT_P1_CRD[] = { {6,5}, {6,5} ,{6,5},{6,6} ,{4,7} ,{9,14} ,{11,11}, {4,6} ,{4,1},{10,10},  {6,6}/*vertical start*/,{6,6},{6,4} ,{10,1}, {12,13},{6,7},{3,7} }; // {6,6}

short gCurrentLevel = 0;		// Le niveau actuel!!1
short gCurrentStage = 0;		// Chaque niveau peut avoir plusieurs stages
short gCurrentPuzzle[NB_LVLS] = {};	// Le checkpoint que le joueur à réussie à reach durant chaque niveau. Si 0, le joueur na reach aucun checkpoint encore


int gCurrPuzzleStep = 0;		// Le step du puzzle en cours, chaque puzzle start à 0. Dès qu'un botspawncycle est fait, on avance de 1. S'arrête à currPuzzleStepMax
int gCurrPuzzleStepMax = 0;


bool gDayStarted = false;
bool gSkipStory = false;		// Quand le joueur start une game à partir du menu, il peut skipper la story pour arriver direct au lvevl
bool gRefreshStage = false;		// Refresh un stage
bool gRetryCheckpoint = false;		// Restart le niveau à partir d'un checkpoint

int Get_Lvl_Checkpoint()	// Rapporte le nombre qui correspond au spawncycletot d'où le checkpoint à été fixé
{
	if (gCurrentPuzzle[gCurrentLevel - 1] == 0)	// 0 veut dire aucun checkpoint n'aété reach encore
		return 0;
	else
		return LVL1_CHECKPOINT[gCurrentPuzzle[gCurrentLevel - 1] - 1] /*+ 1*/;	// > 0: Faut accéder au éléments de la liste LVL1_CHECKPOINT en convertissant le checkpoint 1 en index 0
}																			// le + 1 c'est pour commencer 1 spawnscycle plus tard
																			// +1 pas obligé finalement, on dirait que ça le skip toujours, pt à cause du timer
void Peek_Lvl_Script()
{
	switch (gCurrentLevel)
	{
	case 0: break;
	case 1:	
		Lvl_1_Spwn_Script(); break;	// Détermine quel sera la prochaine wave de spawn
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
	case 1:	Sub_Lvl_1_Script(); break;		// oublis pas de reset le sublevel dès qu'il est terminé
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