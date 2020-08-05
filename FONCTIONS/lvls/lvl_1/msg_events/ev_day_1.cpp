
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

const int NUM_COOL_CHARS = 23;
const int NUM_RECT_CHARS = 7;
const int COOL_CHARS[NUM_COOL_CHARS] = {170,193,196,197,194,191,192,195,213,217,218,201,204,200,203,206,205,202,187,186,240,238,242};
const int RECT_CHARS[NUM_RECT_CHARS] = { 176,178,177,220,219,223,254 };

static int numChars;
static Event ev_Dr_Day1(Ev_Dr_Day_1, 8);	// l'event

static Coord ori;	// Origine du titre
static Coord ori_2;	// Origine du titre
static Coord crd;	// random crd
static Intervals::ManageIntervalLists charToFill(0,0,0);	// Liste de tout les charactères de la console qui n'ont pas été remplis 


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

static void Set_Screen_Filler()
{
	charToFill.Resize(gConWidth, 0, gConHeight);

	// Fill uniquement la box maintenant

	// Exclut côté gauche
	for (int row = 0; row < map.Get_Box_Limit(LEFT); row++)	
		charToFill.Empty_List(row);
	// Exclut côté droit
	for (int row = map.Get_Box_Limit(RIGHT) + 1; row < gConWidth; row++)
		charToFill.Empty_List(row);
	// Exclut côté up
	for (int col = 0; col < map.Get_Box_Limit(UP) ; col++)
		charToFill.Remove_Value_Everywhere(col);
	// Exclut côté droit
	for (int col = map.Get_Box_Limit(DOWN) + 1; col < gConHeight; col++)
		charToFill.Remove_Value_Everywhere(col);


	

	//charToFill.Resize(map.Get_Box_Limit(RIGHT) - map.Get_Box_Limit(LEFT), 0, map.Get_Box_Limit(DOWN));
	//charToFill.Empty_List(0);
	//charToFill.Empty_List(1);
	//charToFill.Empty_List(2);
	//charToFill.Empty_List(gConWidth - 1);
	//charToFill.Empty_List(gConWidth - 2 );
	//charToFill.Empty_List(gConWidth - 3 );
	//charToFill.Remove_Value_Everywhere(0);
	//charToFill.Remove_Value_Everywhere(1);
	//charToFill.Remove_Value_Everywhere(2);
}

static void Fill_Screen_Randomly(bool erase = false)
{
	charToFill.Pick_From_Lists(crd.x, crd.y, true, true, Intervals::RDM_ALL);	// pogne une coord random

	if(erase)
		ConsoleRender::Add_Char(crd, TXT_CONST.SPACE);	// blakc
	else	
		//ConsoleRender::Add_Char(crd, TXT_CONST.SPACE_FILL);	// pour l'instant c'est blanc
		ConsoleRender::Add_Char(crd, COOL_CHARS[rand() % NUM_COOL_CHARS], GRAY);

}

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
		//Dr_Or_Er_Day_1();
		
		Ev_Fill_Map();	// fill la map
		ev_Dr_Day1.Activate();
		ev_Dr_Day1.Start(150);	
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
				ev_Dr_Day1.Advance(200);
				break;
				//if (ev_Dr_Day1.delay.Get_Moves_Left() % 2 == 0)
				//	Dr_Or_Er_Day_1();
				//else
				//	Dr_Or_Er_Day_1(true);
				
				//if(ev_Dr_Day1.delay.Get_Moves_Left() == 1)
				//	Set_Screen_Filler();
			case 3:
				Ev_Lvl_Start_Warning();
				ev_Dr_Day1.Advance(0);
				break;
			}
		}
	}
}

