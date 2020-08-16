#pragma once

#include "player.h"
#include "../UI/direction.h"


void Move_Player(Player &player, Direction dir);	// 

GrdCoord Find_End_Position(GrdCoord& start, Direction dir);	// Position dans le grid, après le move
bool Validate_Move(const GrdCoord &pos);
void Update_Dumb_Shit();
void Set_Dumb_Shit();