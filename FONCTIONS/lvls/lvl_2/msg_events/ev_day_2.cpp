
#include "ev_day_2.h"

#include "../../../UI/console_output/render_list.h"
#include "../../../console/sweet_cmd_console.h"
#include "../../../events/events.h"
#include "../../../events/msg_dispatcher.h"
#include "../../../math/manage_interval.h"
#include "../../../UI/map.h"
#include "../../../events/global_events/feedback/ev_draw_map.h"
#include "../../../events/global_events/feedback/ev_fill_map.h"
#include "../../../events/global_events/ev_lvl_start_warning.h"

static Event ev_Dr_Day2(Ev_Dr_Day_2, 8);	// l'event

static Coord ori;	// Origine du titre
static Coord ori_2;	// Origine du titre # 2
static Coord crd;	// random crd

//static int numChars;
//static Intervals::ManageIntervalLists charToDr(0,0,0);	// Liste de tout les charactères de la console qui n'ont pas été remplis 


//static std::string day_2 = " DAY 2";
const std::string T_DAY_2[STANDARD_ASCII_SIZE] =	// Le titre principal
{
	"- ____ ---------------_ --",
	"-|  _ \\  __ _ _   _  / |--",
	"-| | | |/ _` | | | | | |--",
	"-| |_| | (_| | |_| | | |--",
	"-|____/ \\__,_|\\__, | |_|---",
	"--------------|___/ -------"
};

//const std::string T_DAY_1[STANDARD_ASCII_SIZE] =	// Le titre principal
//{
//	"  ____                _   ",
//	" |  _ \\  __ _ _   _  / |  ",
//	" | | | |/ _` | | | | | |  ",
//	" | |_| | (_| | |_| | | |  ",
//	" |____/ \\__,_|\\__, | |_|   ",
//	"              |___/        "
//};

const std::string T_TITLE[STANDARD_ASCII_SIZE] =	// Le titre principal
{
"-----_ -----_---_ - ------------------_ -  ---_ -----",
"----/ \\----| \\ | |-_____ -----__-----| |-___ | |__ --",
"---/ _ \\---|  \\| |/ _ \\ \\ /\\ / /  _ -| |/ _ \\| '_ \\--",
"--/ ___ \\--| |\\  |  __/\\ V  V /--| |_| | (_) | |_) |-",
"-/_/   \\_\\-|_|-\\_|\\___| \\_/\\_/----\\___/ \\___/|_.__/--",
"    -------------------------------------------------"
};
//const std::string T_TITLE[STANDARD_ASCII_SIZE] =	// Le titre principal
//{
//"     _      _   _                     _       _      ",
//"    / \\    | \\ | | _____      __     | | ___ | |__   ",
//"   / _ \\   |  \\| |/ _ \\ \\ /\\ / /  _  | |/ _ \\| '_ \\  ",
//"  / ___ \\  | |\\  |  __/\\ V  V /  | |_| | (_) | |_) | ",
//" /_/   \\_\\ |_| \\_|\\___| \\_/\\_/    \\___/ \\___/|_.__/  ",
//"                                                     "
//};
			// ____                _      
			//|  _ \  __ _ _   _  / |_    
			//| | | |/ _` | | | | | (_)   
			//| |_| | (_| | |_| | | |_    
			//|____/ \__,_|\__, | |_(_)   
			//             |___/          

 //    _      _   _                     _       _     
 //   / \    | \ | | _____      __     | | ___ | |__  
 //  / _ \   |  \| |/ _ \ \ /\ / /  _  | |/ _ \| '_ \ 
 // / ___ \  | |\  |  __/\ V  V /  | |_| | (_) | |_) |
 ///_/   \_\ |_| \_|\___| \_/\_/    \___/ \___/|_.__/ 
 //                                                   

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void Dr_Day_2()		
{
	int size = (int)T_DAY_2[0].length();
	char symbol = 0;

	for (int line = 0; line < STANDARD_ASCII_SIZE; line++)
	{
		crd = ori;

		for (int sym = 0; sym < size; sym++, crd.x++)
		{
			if (T_DAY_2[line][sym] == TXT_CONST.MINUS)
				continue;//symbol = 250;			
			else
				symbol = T_DAY_2[line][sym];
			
			ConsoleRender::Add_Char({ crd.x, crd.y + line }, symbol, LIGHT_YELLOW);
		}
	}
}


static void Dr_Title()
{
	int size = (int)T_TITLE[0].length();
	char symbol = 0;

	for (int line = 0; line < STANDARD_ASCII_SIZE; line++)
	{
		crd = ori_2;

		for (int sym = 0; sym < (int)T_TITLE[line].length(); sym++, crd.x++)
		{
			if (T_TITLE[line][sym] == TXT_CONST.MINUS)
				continue;//symbol = 250;
			else
				symbol = T_TITLE[line][sym];

			ConsoleRender::Add_Char({ crd.x, crd.y + line }, symbol, LIGHT_YELLOW);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Ev_Dr_Day_2()			//  Message d'avertissement que les bots s'en viennent et que le Niveau Commence
{
	if (!ev_Dr_Day2.Is_Active())
	{
		//numChars = (map.Get_Length()) * (map.Get_Height());	// nombre de char à fill
		ori = { (Find_Ctr_X((int)std::size(T_DAY_2[0]))), (gConHeight / 2) - 15 };
		ori_2 = { (Find_Ctr_X((int)std::size(T_TITLE[0]))), ori.y + 10};
		
		MsgQueue::Register(LOCK_PLAYER);
		Ev_Fill_Map();	// fill la map
		ev_Dr_Day2.Activate();
		ev_Dr_Day2.Start(250);	
	}
	else
	{
		while (ev_Dr_Day2.delay.Tick())
		{
			switch (ev_Dr_Day2.Get_Current_Step())
			{
			case 1:
				Dr_Day_2();	// Affiche le level
				ev_Dr_Day2.Advance(1000);
				break;

			case 2:		
				Dr_Title();
				ev_Dr_Day2.Advance(160);
				break;

			case 3:
				Ev_Lvl_Start_Warning();
				ev_Dr_Day2.Advance(0);
				break;
			}
		}
	}
}

