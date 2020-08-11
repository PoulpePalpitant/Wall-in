

#include "action_input.h"

ActionType action = IDLE;
Direction keyDirection = Direction::NONE;
KeyPressed lastKey = KeyPressed ::NONE;
bool gChoiceTime = false;
bool gBlockInputs = false;
bool gTypeTime = false;
bool gProceedTime = false;
bool gBlockBlast = true;
bool gMenuInputs = true;
int gMenuKey = 0;


