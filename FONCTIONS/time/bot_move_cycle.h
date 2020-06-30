#pragma once 

#include "movement_timer.h"
#include <time.h>

extern bool gMoveBotsThisCycle;					// On bouge les bots durant ce cycle
extern int gBotMoveCycle;						// L'intervalle de BotMove cycle. La distance entre le current et le next
extern time_t gCurrentBotMoveCycle;	// Le BotMove cycle actuel
extern time_t gNextBotMoveCycle;	// Le prochain BotMove cycle
extern int gBotMoveCycleTot;							// Le nombre total de botmove cycle ayant u lieu
	
extern MovementTimer gBotMoveTimer;

void UPD_Bot_Move_Cycle();		// Vérifie si on bouge les bots durant ce cycle
bool Move_Bots_This_Cycle();	// Bouge les bots