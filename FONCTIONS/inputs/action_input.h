#pragma once

#include "../UI/direction.h"

enum ActionType { MOVE, BLAST, CHANGE_BLAST, PAUSE, UNPAUSE, TELEPORT, IDLE, ENTER };	// type d'action que le joueur peut faire

extern ActionType action;			
extern Direction keyDirection;		
extern bool gChoiceTime;		
extern bool gBlockInputs;

