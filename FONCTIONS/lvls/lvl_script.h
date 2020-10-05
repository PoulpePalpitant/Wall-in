#pragma once

extern const int NB_LVLS;

extern const int NUMWAVES[];	// Nombre de bot waves selon chaques niveaux. Indice 0 = lvl 1
extern const int FINALHOUR[];	// À quel wave le final hour aura lieu

// La liste de chacun des checkpoints dans chaque niveau. Le nombre correspond à une spawnwave. Le dernier sera souvent le FINALHOUR
extern const int NUM_CHECKPOINT[];		// Nombre de checkpoint dans chaque lvlv
extern const int LVL1_CHECKPOINT[];
extern const int LVL2_CHECKPOINT[];
extern const int LVL3_CHECKPOINT[];
extern const int LVL4_CHECKPOINT[];
extern const int LVL5_CHECKPOINT[];

extern short gCurrentLevel;	// Le niveau actuel!!1
extern short gCurrentStage;	// Le sous-niveau actuel
extern short gCurrentCheckPoints[];	// Le checkpoint que le joueur à réussie à reach durant le niveau
extern bool gDayStarted;	// Si le lvl à vraiment commencé
extern bool gSkipStory;		// Quand le joueur start une game à partir du menu, il peut skipper la story pour arriver direct au lvevl
extern bool gRefreshStage;	// Refresh un stage
extern bool gRetryCheckpoint;		// Restart le niveau à partir d'un checkpoint


int Get_Lvl_Checkpoint();	// Rapporte le nombre qui correspond au spawncycletot d'où le checkpoint à été fixé
void Peek_Lvl_Script();		
void Peek_Sub_Lvl_Script();
