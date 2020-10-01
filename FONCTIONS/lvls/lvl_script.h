#pragma once

extern const int NB_LVLS;


// La liste de chacun des checkpoints dans chaque niveau. Le nombre correspond � une spawnwave. Le dernier sera souvent le finalhour
extern const int LVL1_CHECKPOINT[];
extern const int LVL2_CHECKPOINT[];
extern const int LVL3_CHECKPOINT[];
extern const int LVL4_CHECKPOINT[];
extern const int LVL5_CHECKPOINT[];

extern short gCurrentLevel;	// Le niveau actuel!!1
extern short gCurrentStage;	// Le sous-niveau actuel
extern short gCurrentCheckPoints[];	// Le checkpoint que le joueur � r�ussie � reach durant le niveau
extern bool gDayStarted;	// Si le lvl � vraiment commenc�
extern bool gSkipStory;		// Quand le joueur start une game � partir du menu, il peut skipper la story pour arriver direct au lvevl
extern bool gRefreshStage;	// Refresh un stage
extern bool gRetryCheckpoint;		// Restart le niveau � partir d'un checkpoint



void Peek_Lvl_Script();		
void Peek_Sub_Lvl_Script();
