
#include "../grid/AllGrids.h"
#include "../UI/console_output/render_list.h"
#include "UI_invalid_move.h"
#include "../events/global_events/feedback/ev_wrong_action.h"

// DEVRAIT ÊTRE UN EVENT

// int dumb debug delay : 300 : à 5000
void UI_Invalide_Action()
{
	Ev_Wrong_Action_Add(); // Le joueur flash un ti peu
}

