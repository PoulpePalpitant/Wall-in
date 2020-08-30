
#include "lvl_script.h"

/* LEs LEvels*/
#include "../menu/menu_script.h"
#include "lvl_1/lvl_1_spwn_script.h"

#include "lvl_1/sub_lvl_1_script.h"

short gCurrentLevel = 0;	// Le niveau actuel!!1
short gCurrentStage = 0;	// Chaque niveau peut avoir plusieurs stages
bool gDayStarted = false;
bool gSkipStory = false;		// Quand le joueur start une game à partir du menu, il peut skipper la story pour arriver direct au lvevl

void Peek_Lvl_Script()
{
	switch (gCurrentLevel)
	{
	case 0: break;
	case 1:	
		Lvl_1_Spwn_Script(); break;	// Détermine quel sera la prochaine wave de spawn
		/*case 2: Level_2_Script(); break;
		case 3: Level_3_Script(); break;
		case 4: Level_4_Script(); break;
		case 5: Level_5_Script(); break;
		case 6: Level_6_Script(); break;
		case 7: Level_7_Script(); break;
		case 8: Level_8_Script();*/
	}
}
void Peek_Sub_Lvl_Script()
{
	switch (gCurrentStage)
	{
	case 0: break;	// Fait rien
	case 1:	Sub_Lvl_1_Script(); break;		// oublis pas de reset le sublevel dès qu'il est terminé
		/*case 2: Level_2_Script(); break;
		case 3: Level_3_Script(); break;
		case 4: Level_4_Script(); break;
		case 5: Level_5_Script(); break;
		case 6: Level_6_Script(); break;
		case 7: Level_7_Script(); break;
		case 8: Level_8_Script();*/
	}



}