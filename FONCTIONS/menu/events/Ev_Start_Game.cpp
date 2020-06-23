
#include "../../lvls/lvl_script.h"
#include "../../lvls/lvl_initializer.h"

#include "../../inputs/action_input.h"
#include "Ev_Game_Title.h"
#include "Ev_Start_Game.h"


void Ev_Start_Game()
{

	gCurrentLevel = 1;
	gLvlInitializer = true;	// Dumbest shit
	
	Ev_Erase_Game_Title();	// Erase Title Screen
	gEraseTitle.ignore = false;
	gDrawTitle.ignore = false;
	gChoiceTime = false;
	
}