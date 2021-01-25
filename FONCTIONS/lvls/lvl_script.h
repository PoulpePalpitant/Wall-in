#pragma once
#include "../grid/grid.h"

extern const int NB_LVLS;
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
extern bool gSkipTutorial;		
extern bool gRefreshStage;	// Refresh un stage
extern bool gRetryCheckpoint;		// Restart le niveau � partir d'un checkpoint

extern int gCurrPuzzleStep;		// Le step du puzzle en cours, chaque puzzle start � 0. D�s qu'un botspawncycle est fait, on avance de 1. S'arr�te � currPuzzleStepMax
extern int gCurrPuzzleStepMax;

extern short tutoStep;
extern const short TUTO_TOTAL_STEPS;

// BONUS
extern bool gameCompleted;


void Peek_Lvl_Script();		
void Init_Puzzle();	// Initialise un puzzle
void Draw_Tuto_Progression(bool progression); // I don't care anymore'
