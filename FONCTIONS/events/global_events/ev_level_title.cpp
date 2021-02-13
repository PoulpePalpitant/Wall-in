
#include "ev_level_title.h"
#include "../../UI/console_output/render_list.h"
#include "../../console/sweet_cmd_console.h"
#include "../../events/events.h"
#include "../../events/msg_dispatcher.h"
#include "../../math/manage_interval.h"
#include "../../UI/map.h"
#include "../../events/global_events/feedback/ev_draw_map.h"
#include "../../events/global_events/feedback/ev_fill_map.h"
#include "../../events/global_events/ev_lvl_start_warning.h"
#include "../../grid/managegrids.h"
#include "../../lvls/lvl_script.h"	 

static Event ev_Dr_LevelTitle(Ev_Dr_Level_Title, 800);	// l'event

static Coord ori;	// Origine du titre
static Coord ori_2;	// Origine du titre # 2
static Coord crd;	// random crd

//static std::string day_2 = " DAY 2";
const std::string LEVEL_TITLE[STANDARD_ASCII_SIZE] =	// Le titre principal
{
	"----__-------------------__-",
	"---/ /---___ _---_____--/ /-",
	"--/ /---/ _ \\ | / / _ \\/ /--",
	"-/ /___/  __/ |/ /  __/ /___",
	"/_____/\\___/|___/\\___/_____/",
	"----------------------------",
};

const std::string FINAL_TITLE[STANDARD_ASCII_SIZE] =	
{
"----_______-------------__",
"---/ ____(_)___--____-_/ /",
"--/ /_  / / __ \\/ __ `/ /-",
"-/ __/ / / / / / /_/ / /--",
"/_/---/_/_/-/_/\\__,_/_/---",
"--------------------------",};                         


//const std::string T_DAY_1[STANDARD_ASCII_SIZE] =	// Le titre principal
//{
//
//      __                   __ 
//     / /   ___ _   _____  / / 
//    / /   / _ \ | / / _ \/ /  
//   / /___/  __/ |/ /  __/ /___
//  /_____/\___/|___/\___/_____/
//
//};


const std::string LEVEL_NUM_TITLE[3][STANDARD_ASCII_SIZE] =	// Le titre principal
{
{
"---___",
"--<  /",
"--/ /-",
"-/ /--",
"/_/---",
"------"
},
{
	"- ___----",
	"--|__ \\--",
	"- __/ /--",
	" / __/---",
	"/____/--",
	"----------"  

},
{

"---_____",
"---|__  /",
"---/_ <-",
"-___/ /-",
"/____/--",
"--------",
},
};

                                
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void Dr_Level_Title()
{
	int size = (int)LEVEL_TITLE[0].length();
	char symbol = 0;

	for (int line = 0; line < STANDARD_ASCII_SIZE; line++)
	{
		crd = ori;

		for (int sym = 0; sym < size; sym++, crd.x++)
		{
			if (LEVEL_TITLE[line][sym] == TXT_CONST.MINUS)
				continue;//symbol = 250;			
			else
				symbol = LEVEL_TITLE[line][sym];
			
			ConsoleRender::Add_Char({ crd.x, crd.y + line }, symbol, LIGHT_YELLOW);
		}
	}
}


static void Dr_Level_Num()
{
	int size = (int)LEVEL_NUM_TITLE[gCurrentLevel - 1][0].length();
	char symbol = 0;

	for (int line = 0; line < STANDARD_ASCII_SIZE; line++)
	{
		crd = ori_2;

		for (int sym = 0; sym < (int)LEVEL_NUM_TITLE[gCurrentLevel - 1][line].length(); sym++, crd.x++)
		{
			if (LEVEL_NUM_TITLE[gCurrentLevel - 1][line][sym] == TXT_CONST.MINUS)
				continue;//symbol = 250;
			else
				symbol = LEVEL_NUM_TITLE[gCurrentLevel - 1][line][sym];

			ConsoleRender::Add_Char({ crd.x, crd.y + line }, symbol, LIGHT_YELLOW);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Ev_Dr_Level_Title()			//  Message d'avertissement que les bots s'en viennent et que le Niveau Commence
{
	if (!ev_Dr_LevelTitle.Is_Active())
	{
		//ori = { (Find_Ctr_X((int)std::size(LEVEL_TITLE[0]))), (gConHeight / 2) - 15 };
		//ori_2 = { (Find_Ctr_X((int)std::size(LEVEL_NUM_TITLE[0]))), ori.y + 10};

		ori = { Find_Ctr_Grid(LEVEL_TITLE[0]) - 4, (gConHeight / 2) - 3 };

		if (gCurrentLevel == 3)
			ori.x -= 10;

		ori_2 = { ori.x + (int)std::size(LEVEL_TITLE[0]) + 3, ori.y };



		clrscr();
		MsgQueue::Register(LOCK_PLAYER);
		Ev_Fill_Map();	// fill la map
		ev_Dr_LevelTitle.Activate();
		ev_Dr_LevelTitle.Start(200);
	}
	else
	{
		while (ev_Dr_LevelTitle.delay.Tick())
		{
			switch (ev_Dr_LevelTitle.Get_Current_Step())
			{
			case 1:
				if (gCurrentLevel != 3)
					Dr_Level_Title();
				else
					Dr_Or_Er_Title(FINAL_TITLE, ori, STANDARD_ASCII_SIZE, LIGHT_YELLOW);

				ev_Dr_LevelTitle.Advance(800);
				break;

			case 2:
				if (gCurrentLevel != 3)
					Dr_Level_Num();	// Affiche le level
				else
					Dr_Or_Er_Title(LEVEL_TITLE, ori_2, STANDARD_ASCII_SIZE, LIGHT_YELLOW);


				ev_Dr_LevelTitle.Advance(500);
				break;

			case 3:
				ev_Dr_LevelTitle.Advance(0);
				ev_Dr_LevelTitle.delay.Start_Timer(100000, 1, 1);

			case 4:
				if (!Is_Ev_Fill_Map_Active())
				{
					ev_Dr_LevelTitle.delay.Stop();
					if (gCurrentLevel != 3)
						ev_Dr_LevelTitle.Advance(700);
					else
						ev_Dr_LevelTitle.Advance(500);


				}
				break;

			case 5:
				ev_Dr_LevelTitle.Cancel();
				MsgQueue::Register(STAGE_ADVANCE); // Here they come baby
				break;
			}
		}
	}
}

/*
void Ev_Big_GG() {

	static int length = (int)gg[0].size();
	static Coord xy;
	static int r, c;
	static int speed = 800000;

	static unsigned long long clrNum = 0;
	static Colors clr;

	if (!ev_BigGG.Is_Active())
	{
		xy = { Find_Ctr_String_X(gg[0]),13 };

		clrNum++;

		switch (clrNum % NUM_COLOR)
		{
		case 0:	clr = LIGHT_RED;	 break;
		case 1:	clr = LIGHT_YELLOW;  break;
		case 2:	clr = LIGHT_GREEN;	 break;
		case 3:	clr = LIGHT_PURPLE;  break;
		case 4:	clr = BRIGHT_WHITE;   break;
		case 5:	clr = LIGHT_AQUA;	break;
		}

		ev_BigGG.Activate();
		ev_BigGG.Start(0);
		ev_BigGG.delay.Start_Timer(speed, 1, true);
	}
	else
		while (ev_BigGG.delay.Tick())
		{
			if (++r >= 16)
			{
				r = 0;
				if (++c >= length)
				{
					c = 0;
					ev_BigGG.Cancel();
					return;
				}
			}

			if (gg[r][c] != TXT_CONST.SPACE)
				if (gg[r][c] == TXT_CONST.DOTDOT)
					ConsoleRender::Add_Char({ xy.x + c,xy.y + r }, gg[r][c], BRIGHT_WHITE);
				else
					ConsoleRender::Add_Char({ xy.x + c,xy.y + r }, gg[r][c], clr);
		}
}*/