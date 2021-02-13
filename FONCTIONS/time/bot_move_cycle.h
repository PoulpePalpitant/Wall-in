#pragma once 

#include "movement_timer.h"
#include <time.h>

extern bool gMoveBotsThisCycle;					// On bouge les bots durant ce cycle
extern int gBotMoveCycle;						// L'intervalle de BotMove cycle. La distance entre le current et le next
extern time_t gCurrentBotMoveCycle;	
extern time_t gNextBotMoveCycle;
extern int gBotMoveCycleTot;							
	
extern SpeedTimer gBotMoveTimer;
extern int prevMovSpeed;			

void UPD_Bot_Move_Cycle();		
bool Move_Bots_This_Cycle();

void Temporary_Bot_Speed_Switch(int speed, bool overwritePrev = true);	
void Restore_Prev_Bot_Speed();	
