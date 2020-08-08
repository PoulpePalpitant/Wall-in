#pragma once 

#include "movement_timer.h"
#include <time.h>

extern bool gMoveBotsThisCycle;					// On bouge les bots durant ce cycle
extern int gBotMoveCycle;						// L'intervalle de BotMove cycle. La distance entre le current et le next
extern time_t gCurrentBotMoveCycle;	// Le BotMove cycle actuel
extern time_t gNextBotMoveCycle;	// Le prochain BotMove cycle
extern int gBotMoveCycleTot;							// Le nombre total de botmove cycle ayant u lieu
	
extern SpeedTimer gBotMoveTimer;
extern int prevMovSPeed;			// la vitesse de d�placement pr�c�dente des bots. � r�tablir une fois qu'on a finis avec un Jerry

void UPD_Bot_Move_Cycle();		// V�rifie si on bouge les bots durant ce cycle
bool Move_Bots_This_Cycle();	// Bouge les bots