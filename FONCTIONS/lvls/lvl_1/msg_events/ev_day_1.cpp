
#include "ev_day_1.h"

#include "../../../UI/console_output/render_list.h"
#include "../../../console/sweet_cmd_console.h"
#include "../../../events/events.h"
#include "../../../events/msg_dispatcher.h"
#include "../../../math/manage_interval.h"
#include "../../../UI/map.h"
#include "../../../events/global_events/feedback/ev_draw_map.h"
#include "../../../events/global_events/feedback/ev_fill_map.h"
#include "../../../events/global_events/ev_lvl_start_warning.h"

static int numChars;
static Event ev_Dr_Day1(Ev_Dr_Day_1, 8);	// l'event

static Coord ori;	// Origine du titre
static Coord ori_2;	// Origine du titre
static Coord crd;	// random crd
static Intervals::ManageIntervalLists charToDr(0,0,0);	// Liste de tout les charactères de la console qui n'ont pas été remplis 


//static std::string day_1 = " DAY 1";
const std::string T_DAY_1[STANDARD_ASCII_SIZE] =	// Le titre principal
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

const std::string T_JOB[STANDARD_ASCII_SIZE] =	// Le titre principal
{
"-----_ -----_---_ - ------------------_ -  ---_ -----",
"----/ \\----| \\ | |-_____ -----__-----| |-___ | |__ --",
"---/ _ \\---|  \\| |/ _ \\ \\ /\\ / /  _ -| |/ _ \\| '_ \\--",
"--/ ___ \\--| |\\  |  __/\\ V  V /--| |_| | (_) | |_) |-",
"-/_/   \\_\\-|_|-\\_|\\___| \\_/\\_/----\\___/ \\___/|_.__/--",
"    -------------------------------------------------"
};
//const std::string T_JOB[STANDARD_ASCII_SIZE] =	// Le titre principal
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



//static void Dr_Or_Er_Day_1(bool erase = false)		// Cette version fait flasher le titre
//{
//	int size = (int)T_DAY_1[0].length();
//	char symbol = 0;
//
//	for (int line = 0; line < STANDARD_ASCII_SIZE; line++)
//	{
//		crd = ori;
//		
//		for (int sym = 0; sym < size; sym++, crd.x++)
//		{
//			if (T_DAY_1[line][sym] == TXT_CONST.SPACE)			
//				symbol = 250;
//			else
//			{
//				if (erase)
//					symbol = TXT_CONST.SPACE;
//				else
//					symbol = T_DAY_1[line][sym];
//			}
//				ConsoleRender::Add_Char({ crd.x, crd.y + line }, symbol);
//		}
//		//ConsoleRender::Add_String(T_DAY_1[line], { ori.x, ori.y + line }, WHITE, 0, erase);	
//	}
//}

static void Dr_Day_1()		
{
	int size = (int)T_DAY_1[0].length();
	char symbol = 0;

	for (int line = 0; line < STANDARD_ASCII_SIZE; line++)
	{
		crd = ori;

		for (int sym = 0; sym < size; sym++, crd.x++)
		{
			if (T_DAY_1[line][sym] == TXT_CONST.MINUS)
				continue;//symbol = 250;			
			else
				symbol = T_DAY_1[line][sym];
			
			ConsoleRender::Add_Char({ crd.x, crd.y + line }, symbol, LIGHT_YELLOW);
		}
	}
}


static void Dr_Job()
{
	int size = (int)T_JOB[0].length();
	char symbol = 0;

	for (int line = 0; line < STANDARD_ASCII_SIZE; line++)
	{
		crd = ori_2;

		for (int sym = 0; sym < (int)T_JOB[line].length(); sym++, crd.x++)
		{
			if (T_JOB[line][sym] == TXT_CONST.MINUS)
				continue;//symbol = 250;
			else
				symbol = T_JOB[line][sym];

			ConsoleRender::Add_Char({ crd.x, crd.y + line }, symbol, LIGHT_YELLOW);
		}
		//ConsoleRender::Add_String(T_DAY_1[line], { ori.x, ori.y + line }, WHITE, 0, erase);	
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Ev_Dr_Day_1()			//  Message d'avertissement que les bots s'en viennent et que le Niveau Commence
{
	if (!ev_Dr_Day1.Is_Active())
	{
		numChars = (map.Get_Length()) * (map.Get_Height());	// nombre de char à fill
		ori = { (Find_Ctr_X((int)std::size(T_DAY_1[0]))), (gConHeight / 2) - 15 };
		ori_2 = { (Find_Ctr_X((int)std::size(T_JOB[0]))), ori.y + 10};
		
		MsgQueue::Register(LOCK_PLAYER);
		Ev_Fill_Map();	// fill la map
		ev_Dr_Day1.Activate();
		ev_Dr_Day1.Start(200);	
	}
	else
	{
		while (ev_Dr_Day1.delay.Tick())
		{
			switch (ev_Dr_Day1.Get_Current_Step())
			{
			case 1:
				Dr_Day_1();	// Affiche le level
				ev_Dr_Day1.Advance(1000);
				break;

			case 2:		
				Dr_Job();
				ev_Dr_Day1.Advance(160);
				break;

			case 3:
				Ev_Lvl_Start_Warning();
				ev_Dr_Day1.Advance(0);
				break;
			}
		}
	}
}

