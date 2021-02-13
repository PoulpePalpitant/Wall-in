

#include "action_input.h"

ActionType action = IDLE;
Direction keyDirection = Direction::NONE;
KeyPressed lastKey = KeyPressed ::NONE;
bool teleportBuffered = false;
bool gChoiceTime = false;
bool gBlockInputs = false;
bool gTypeTime = false;
bool gProceedTime = false;
bool gSkipTime = false;
bool gBlockBlast = true;
bool gMenuInputs = true;
int gMenuKey = 0;

bool gTeleportBuffer = true;


void Reset_Input_Flags()	// Cancel tout les flags
{
	action = IDLE;
	keyDirection = Direction::NONE;
	lastKey = KeyPressed::NONE;
	teleportBuffered = false;
	gChoiceTime = false;
	gBlockInputs = false;
	gTypeTime = false;
	gProceedTime = false;
	gBlockBlast = true;
	gMenuInputs = false;
}


