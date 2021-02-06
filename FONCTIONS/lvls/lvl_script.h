#pragma once
#include "../grid/grid.h"

extern const int NB_LVLS;
extern const int NUM_PUZZLES[];		

void (*LVL1_PUZZLES[])(); // Déclaration d'un tableau de pointeurs de fonctions en c++. Quand même hideux.
void (*LVL2_PUZZLES[])();
void (*LVL3_PUZZLES[])();

extern int gCurrentLevel;	
extern int gUnlockedLevels[3];
extern int gLastLvlUnlocked;

extern int gCurrentStage;		
extern int gCurrentPuzzle[];	
extern bool gLevelStarted;		
extern bool gSkipTutorial;		
extern bool gRefreshStage;		
extern bool gRetryCheckpoint;	

extern int gCurrPuzzleStep;		
extern int gCurrPuzzleStepMax;

extern short tutoStep;
extern const short TUTO_TOTAL_STEPS;

// BONUS
extern bool gameCompleted;


void Peek_Lvl_Script();		
void Init_Puzzle();	// Initialise un puzzle
void Draw_Tuto_Progression(bool progression); // I don't care anymore'
