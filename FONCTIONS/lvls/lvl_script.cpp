

#include "../menu/menu_script.h"
#include "lvl_1/lvl_1_script.h"
#include "lvl_1/sub_lvl_1_script.h"
#include "lvl_script.h"

extern short gCurrentLevel = 0;	// Le niveau actuel!!1
extern short gCurrentSubLevel = 0;	// Chaque niveau va avoir un mini level qui va le précédé
extern bool gInitializeLvl = true;	// si on initialize le niveau

void Peek_Lvl_Script()
{
	switch (gCurrentLevel)
	{
	case 0: Menu_Script(); break;
	case 1:	Level_1_Script(); break;
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
	switch (gCurrentSubLevel)
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