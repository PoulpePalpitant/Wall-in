
#include "lvl_1/lvl_1_script.h"
#include "lvl_script.h"

extern short gCurrentLevel = 0;	// Le niveau actuel!!1
extern bool binitializeLvl = true;	// si on initialize le niveau

void Peek_Lvl_Script()
{
	switch (gCurrentLevel)
	{
	case 0:// Menu_Script(); break;
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
