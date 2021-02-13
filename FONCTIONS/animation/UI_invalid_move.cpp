
#include "UI_invalid_move.h"
#include "../events/global_events/feedback/ev_wrong_action.h"

// DEVRAIT ÊTRE UN EVENT
void UI_Invalide_Action()
{
	Ev_Wrong_Action_Add(); 
}

