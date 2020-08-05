#pragma once

#include "../UI/direction.h"

enum ActionType { MOVE, BLAST, CHANGE_BLAST, PAUSE, UNPAUSE, TELEPORT, IDLE, ENTER };	// type d'action que le joueur peut faire

enum class KeyPressed {NONE, ENTER};
extern KeyPressed lastKey;
extern ActionType action;			
extern Direction keyDirection;		
extern bool gChoiceTime;		
extern bool gBlockInputs;
extern bool gBlockBlast;
extern bool gTypeTime;
extern bool gMenuInputs;
extern int gMenuKey;
