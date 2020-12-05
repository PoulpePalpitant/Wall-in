#pragma once
#include "../grid/grid.h"

extern const int NB_LVLS;


//lvls[gCurrentLevel -1]



extern const int NUMWAVES[];	// Nombre de bot waves selon chaques niveaux. Indice 0 = lvl 1
extern const int FINALHOUR[];	// � quel wave le final hour aura lieu


extern const int NUM_PUZZLES[];		

void (*LVL1_PUZZLES[])();// declare!
void (*LVL2_PUZZLES[])();
void (*LVL3_PUZZLES[])();

extern short gCurrentLevel;	
extern short gUnlockedLevels[3];
extern short gLastLvlUnlocked;

extern short gCurrentStage;	// Le sous-niveau actuel
extern short gCurrentPuzzle[];	// Le checkpoint que le joueur � r�ussie � reach durant le niveau
extern bool gDayStarted;	// Si le lvl � vraiment commenc�
extern bool gSkipStory;		// Quand le joueur start une game � partir du menu, il peut skipper la story pour arriver direct au lvevl
extern bool gRefreshStage;	// Refresh un stage
extern bool gRetryCheckpoint;		// Restart le niveau � partir d'un checkpoint

extern int gCurrPuzzleStep;		// Le step du puzzle en cours, chaque puzzle start � 0. D�s qu'un botspawncycle est fait, on avance de 1. S'arr�te � currPuzzleStepMax
extern int gCurrPuzzleStepMax;



void Peek_Lvl_Script();		
void Peek_Sub_Lvl_Script();
void Init_Puzzle();	// Initialise un puzzle