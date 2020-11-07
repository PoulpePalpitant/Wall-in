#include "ev_final_hour_1.h"

#include "../events.h"
#include "../../time/cycles.h"
#include "../msg_dispatcher.h"
#include "../../UI/console_output/render_list.h"
#include "ev_progress_bar.h"
#include "../../math/manage_interval.h"
#include "../../console/sweet_cmd_console.h"
#include "feedback/ev_rainbow_borders.h"

static std::string msg_1 = "FINAL HOUR";
Coord finalHour = { 0,0 };	// La coord sité sur la progress bar qui indique le final hour


static Event ev_FinalHour_1(Ev_Final_Hour_1, 4);

static Intervals::ManageIntervalLists charToDr(0, 0, 0);	// Liste de tout les charactères de la console qui n'ont pas été remplis 
static Coord ori;	
static Coord ori_2;
static Coord crd;



//static std::string day_1 = " DAY 1";
const std::string FINAL[STANDARD_ASCII_SIZE] =	// Le titre principal
{
	"----___________ --_____ ---__-",
	"---/ ____/  _/ |-/ /   |--/ /-",
	"--/ /_---/ //  |/ / /| |-/ /--",
	"-/ __/-_/ // /|  / ___ |/ /___",
	"/_/---/___/_/-|_/_/--|_/_____/",
	"------------------------------"
};

const std::string HOUR[STANDARD_ASCII_SIZE] =	// Le titre principal
{
"----__--______--__--______-",
"---/ /-/ / __ \\/ /-/ / __ \\",
"--/ /_/ / / / / /-/ / /_/ /",
"-/ __  / /_/ / /_/ / _, _/-",
"/_/-/_/\\____/\\____/_/-|_|--",
"---------------------------"
};

//    ___________   _____    __ 
//   / ____/  _/ | / /   |  / / 
//  / /_   / //  |/ / /| | / /  
// / __/ _/ // /|  / ___ |/ /___
///_/   /___/_/ |_/_/  |_/_____/
//    __  ______  __  ______ 
//   / / / / __ \/ / / / __ \
//  / /_/ / / / / / / / /_/ /
// / __  / /_/ / /_/ / _, _/ 
///_/ /_/\____/\____/_/ |_|  
//                           

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




// Avertit le joueur que le final push arrive!
void  Ev_Final_Hour_1()
{
	static const std::string* title;
	static const std::string* title2;
	static bool erOrDr = false;
	static int step;
	static Colors clr = LIGHT_RED;
	static const int NUM_COLORS = STANDARD_ASCII_SIZE - 1;

	if (!ev_FinalHour_1.Is_Active())
	{


		/* V1 */
		//// La progress bar doit être dessiné en a priori
		//finalHour.x -= (int)msg_1.size() / 2;
		//finalHour.y -= 2;

		ori = { (Find_Ctr_X((int)std::size(FINAL[0]))) - 1,(gConHeight / 2) - 10 };				// Origine du titre
		ori_2 = { (Find_Ctr_X((int)std::size(HOUR[0]))) - 1, ori.y + 8 };;	// Origine du titre
		//Dr_Or_Er_Title(title = FINAL, ori);
		//Dr_Or_Er_Title(title = HOUR, ori_2);

		step = STANDARD_ASCII_SIZE;
		title = FINAL;

		ev_FinalHour_1.Activate();
		ev_FinalHour_1.Start(8000, step);
		Ev_Rainbow_Borders_Extra();// super wow!
	}
	else
		while (ev_FinalHour_1.delay.Tick())
		{

			//switch (step % NUM_COLORS)
			//{
			//case 0:	clr = LIGHT_RED;	 break;
			//case 1:	clr = LIGHT_YELLOW;break;
			//case 2:	clr = LIGHT_GREEN;break;
			//case 3:	clr = LIGHT_PURPLE;  break;
			//case 4:	clr = LIGHT_AQUA;    break;
			//default: clr = BRIGHT_WHITE;
			//}

			switch (ev_FinalHour_1.Get_Current_Step())
			{

			case 1:
				Dr_Or_Er_Title_Line(title, ori, step - STANDARD_ASCII_SIZE, clr, TXT_SPD_FAST * 1.3);
				step++;

				if (!ev_FinalHour_1.delay.Is_On())
				{
					title = HOUR;
					step = STANDARD_ASCII_SIZE;
					ev_FinalHour_1.Advance(8000, step);
				}
				break;

			case 2:
				Dr_Or_Er_Title_Line(title, ori_2, step - STANDARD_ASCII_SIZE, clr, TXT_SPD_FAST * 1.3);
				step++;

				if (!ev_FinalHour_1.delay.Is_On())
					ev_FinalHour_1.Advance(500);
				break;

			case 3:
				step = STANDARD_ASCII_SIZE;
				ev_FinalHour_1.Advance(7000, step);
				break;

			case 4:
				Dr_Or_Er_Title_Line(FINAL, ori, step - STANDARD_ASCII_SIZE, clr, TXT_SPD_FAST * 2, true);
				Dr_Or_Er_Title_Line(HOUR, ori_2, step - STANDARD_ASCII_SIZE, clr, TXT_SPD_FAST * 2,true);
				step++;

				if (!ev_FinalHour_1.delay.Is_On())
					ev_FinalHour_1.Cancel();
				break;
			}
		}
}




//	// V1 Fais flasher du texte en haut de la bar, pas assez grandiose à mon avis
//	10 Steps

//case 1:case 3: case 5: case 7: case 9:
//	ConsoleRender::Add_String(msg_1, finalHour, LIGHT_RED);//Affiche
//	ev_FinalPush.Advance(1000);
//	break;

//case 2:case 4: case 6: case 8: case 10:
//	ConsoleRender::Add_String(msg_1, finalHour, WHITE, 0, true);// efface
//	ev_FinalPush.Advance(1000);
//	break;


// V2 Flashy: un peu agraissant
//if (erOrDr)
//erOrDr = false;
//else
//erOrDr = true;
//
//Dr_Or_Er_Title(title = FINAL, ori, STANDARD_ASCII_SIZE, erOrDr);// 
//Dr_Or_Er_Title(title = HOUR, ori_2, STANDARD_ASCII_SIZE, erOrDr);//
//
//if (++step == 13)
//ev_FinalHour_1.Cancel();