#pragma once

#include "player.h"
#include "../UI/direction.h"


void Move_Player(Player &player, Direction dir);	

GrdCoord Find_End_Position(GrdCoord& start, Direction dir);	
bool Validate_Move(const GrdCoord &pos);
