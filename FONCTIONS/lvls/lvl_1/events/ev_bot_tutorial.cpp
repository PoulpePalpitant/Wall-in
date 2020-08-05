

#include "ev_bot_tutorial.h"

#include "../../lvl_script.h"
#include "../../../events/events.h"
#include "../../../events/msg_dispatcher.h"
#include "../../../grid/AllGrids.h"
#include "../../../UI/console_output/render_list.h"
#include "../../../player/player.h"
#include "../../../events/global_events/ev_update_heart.h"
#include "../../../events/global_events/feedback/ev_draw_map.h"
#include "../../../choice/choice_time.h"
#include "../msg_events/ev_arr_keys.h"
#include "../../../spawns/ev_spawn_Jerry.h"
#include "../../../bots/botmeta.h"
#include "../../../time/bot_move_cycle.h"
#include "../../../player/player.h"
#include "../../../structure_manager/modify_chain.h"

static Event ev_BotTutorial(Ev_Bot_Tutorial, 29);

/* Dis gonna be a long one:
	
	Tutorial qui montre au joueur comment jouer. 
	Choses à montrer:

	- Les Bots, leurs déplacement et leur destination
	- Tirer, comment stacker perpendiculairement
	- Détuire les bots, en utilisant la méthode de tirer, ne peut pas tirer directement dessus(en fait techniquement oui)
	- Tu dois survivre le niveau, qui à une fin

*/

static Coord XY;			// Pour tout les XY
static GrdCoord choiceCrd;

// A shit load of texte

static std::string _1 = "Alright Then, Let's Get You Started";
static std::string _2 = "Step #1";
static std::string _3 = "Build A Wall";
static std::string _4 = "Step #2";
static std::string _5 = "Let Them Smash Into It";
static std::string _6 = "It's As Simple As That!";
static std::string _7 = "Now Jerry Here, ";
static std::string _8 = "Hi!";
static std::string _9 =  "Will Help Us With The Demonstration";
/*
	If You Would Like To Practice More 
	Just Give Me A Call
 
 */
static std::string _10 = "Get Ready";
static std::string _11 = "Jerry It's Your Turn Now";
static std::string _12 = "(You Got This Jerry!)";
static std::string _13 = "Okay, Here I Come!";
static std::string _14 = "...";
static std::string _15 = "(Don't let Jerry Reach The Border)";
static std::string _16 = "Nice Work! You Stopped Jerry!";
static std::string _17 = "Actually, This Might Have Been";
static std::string _18 = "A Little Too Easy";
static std::string _19 = "Let's Bring The Difficulty Up A Notch";
static std::string _20 = "Jerry, You Know What To Do...";
static std::string _22 = "Yes, Mam!";
//static std::string _20 = "There You Go! I Think You Are All Set";
//static std::string _20 = "If You Need More Practice";
//static std::string _20 = "Just Ask Jerry";
static std::string sorry = "I'm Sorry, But I Can't Let You Continue";
static std::string stop = "Until You Stop Mah Boi Jerry";


// CHOICE STUFF
static std::string automatic = "This Is An Automatic Performance Review for:";
static std::string jerry = "Jerry SoreBottom";
static std::string prfom = "How Would You Rate Jerry's Performance Today?";

static std::string doubt = "How, Was I, Did I Do Good?";
static std::string rate = "Rate Jerry's Performance";
static std::string choiceMade;
static std::string recom[] = { " 1 ", " 2 ", " 3 ", " 4 ", " 5 ", " 6 ", " 7 ", " 8 ", " 9 ", " 10 " };
static std::string answer[] =
{ 
	"You Didn't Seem Honest Enough. Jerry Seems Disappointed",
	"Jerry Doesn't Seem Satisfied By Your Answer",
	"Jerry Appreciates Your FeedBack. Even Though You Have Hurt His Feelings", 
	"Jerry Appreciates Your FeedBack. Even Though It was Just A MeaningLess Number",
	"Jerry Appreciates Your FeedBack. Even Though Your Opinion Means Very Little To Him"
};
static std::string tempAnswer;


void Ev_Bot_Tutorial()// Trace un chemin vers une fausse porte de sortie
{
	if (!ev_BotTutorial.Is_Active())
	{
		//Erase_Map_Borders_1(23);	// erase borders
		ev_BotTutorial.Activate();
		ev_BotTutorial.Start(400);
	}
	else	// doin stuff 
	{

		while (ev_BotTutorial.delay.Tick())
		{
			static int step; step = ev_BotTutorial.Get_Current_Step();

			switch (step)	// STEP 1 à 20 -> On troll le joueur en faisant déplacer un tit point
			{
			case 1:
				ConsoleRender::Add_String(_1, Boss_Txt_Crd(_1), gBossClr, 100);
				ev_BotTutorial.Advance(400);
				break;

			case 2:
				ConsoleRender::Add_String(_1, Boss_Txt_Crd(_1), gBossClr, TXT_SPD_ER, true);
				ev_BotTutorial.Advance(500);
				break;

			case 3:
				ConsoleRender::Add_String(_2, Boss_Txt_Crd(_2), gBossClr, TXT_SPD_DR);
				ev_BotTutorial.Advance(600);
				break;

			case 4:
				ConsoleRender::Add_String(_3, Boss_Txt_Crd(_3, 1), gBossClr, TXT_SPD_DR);
				ev_BotTutorial.Advance(700);
				break;

			case 5:
				ConsoleRender::Add_String(_4, Boss_Txt_Crd(_4, 2), gBossClr, TXT_SPD_DR);
				ev_BotTutorial.Advance(700);
				break;

			case 6:
				ConsoleRender::Add_String(_5, Boss_Txt_Crd(_5, 3), gBossClr, TXT_SPD_DR);
				ev_BotTutorial.Advance(500);
				break;

			case 7:
				ConsoleRender::Add_String(_2, Boss_Txt_Crd(_2), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_3, Boss_Txt_Crd(_3, 1), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_4, Boss_Txt_Crd(_4, 2), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_5, Boss_Txt_Crd(_5, 3), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_6, Boss_Txt_Crd(_6), gBossClr, TXT_SPD_DR);
				ev_BotTutorial.Advance(400);
				break;


			case 8:
				ConsoleRender::Add_String(_6, Boss_Txt_Crd(_6), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_7, Boss_Txt_Crd(_7, 1), gBossClr, TXT_SPD_DR);
				ev_BotTutorial.Advance(1000);
				break;

			case 9:
				ConsoleRender::Add_String(_8, Jerry_Txt_Crd(_8), gJerClr, 100);
				ev_BotTutorial.Advance(1000);
				break;

			case 10:
				ConsoleRender::Add_String(_8, Jerry_Txt_Crd(_8), gJerClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_9, Boss_Txt_Crd(_9, 2), gBossClr, 100);
				ev_BotTutorial.Advance(500);

				break;

			case 11:
				ConsoleRender::Add_String(_7, Boss_Txt_Crd(_7, 1), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_9, Boss_Txt_Crd(_9, 2), gBossClr, TXT_SPD_ER, true);
				Erase_Map_Borders_1(50);	// Erase les borders
				Ev_Dr_Heart_3();

				ev_BotTutorial.Advance(700);
				break;

			case 12:
				Ev_Dr_Arr_Keys();

				ConsoleRender::Add_String(_10, Boss_Txt_Crd(_10), gBossClr, 100);
				ev_BotTutorial.Advance(50);
				break;

			case 13:
				ConsoleRender::Add_String(_10, Boss_Txt_Crd(_10), gBossClr, 50, true);
				ConsoleRender::Add_String(_11, Boss_Txt_Crd(_11, 1), gBossClr, TXT_SPD_DR);
				ev_BotTutorial.Advance(400);
				break;
			
			case 14:
				ConsoleRender::Add_String(_15, {38 , 4}, GRAY, TXT_SPD_DR);
				ConsoleRender::Add_String(_11, Boss_Txt_Crd(_11, 1), gBossClr, TXT_SPD_ER, true);
				Set_Flashy_Border(LEFT);
				Ev_Flash_Map_Border();	// Fait flasher la border pour signaler au joueur ou va aller Jerry

				ev_BotTutorial.Advance(200);
				break;

			case 15:
				// setup le bot custom
				gCustomBot.is = true;
				gCustomBot.clr = LIGHT_GREEN;
				gCustomBot.warningDelay = 20;
				Spawn_A_Bot(RIGHT, 6);			// spawn Jerrry!
				gBotMoveTimer.Start_Timer(4000, 1, true);	// vitesse de déplacement de Jerry

				ConsoleRender::Add_String(_13, Jerry_Txt_Crd(_13), gJerClr, TXT_SPD_DR);
				ev_BotTutorial.Advance(250);
				break;


			case 16:
				ConsoleRender::Add_String(_13, Jerry_Txt_Crd(_13), gJerClr, TXT_SPD_ER, true);
				//ConsoleRender::Add_String(_12, Boss_Txt_Crd(_12, 1), GRAY, TXT_SPD_DR);
				ev_BotTutorial.Advance(0);
				ev_BotTutorial.delay.Start_Timer(5000,1, true);
				break;

			case 17:
				if (!gAllBotMeta.alive)
				{
					if (P1.Get_HP() == 3)	// Si le joueur à péter Jerry
					{
						ConsoleRender::Add_String(_14, Jerry_Txt_Crd(_14, 1), gJerClr, TXT_SPD_DR);	// Jerry à finis d'avancer
						//ConsoleRender::Add_String(_12, Boss_Txt_Crd(_12, 1), GRAY, TXT_SPD_ER, true);
						ConsoleRender::Add_String(sorry, Boss_Txt_Crd(sorry, 2), gBossClr, TXT_SPD_ER, true);
						ConsoleRender::Add_String(stop, Boss_Txt_Crd(stop, 3), gBossClr, TXT_SPD_ER, true);
						ConsoleRender::Add_String(_15, { 38 , 4 }, GRAY, TXT_SPD_ER, true);

						ev_BotTutorial.delay.Stop();
						ev_BotTutorial.Advance(500);
					}
					else
					{
						//ConsoleRender::Add_String(_12, Boss_Txt_Crd(_12, 1), GRAY, TXT_SPD_ER, true);
						ConsoleRender::Add_String(sorry, Boss_Txt_Crd(sorry, 2), gBossClr, TXT_SPD_DR);
						ConsoleRender::Add_String(stop, Boss_Txt_Crd(stop, 3), gBossClr, TXT_SPD_DR);
						ev_BotTutorial.delay.Stop();
						ev_BotTutorial.Go_To_X_Step(0);
						ev_BotTutorial.delay.Start_Timer(200);				

					}
				}
				break;

			case 0:
				P1.Player_Gains_HP();					// redonne de la vie
				ev_BotTutorial.delay.Start_Timer(600);
				ev_BotTutorial.Go_To_X_Step(15);
				break;

			case 18:
				ConsoleRender::Add_String(_14, Jerry_Txt_Crd(_14, 1), gJerClr, TXT_SPD_ER, true);	// Jerry à finis d'avancer
				ev_BotTutorial.Advance(500);
				break;
				
			case 19:
				ConsoleRender::Add_String(_16, Boss_Txt_Crd(_16), gBossClr, TXT_SPD_DR);
				ev_BotTutorial.Advance(500);
				break;

			case 20:
				ConsoleRender::Add_String(doubt, Jerry_Txt_Crd(doubt), gJerClr, 260);
				ev_BotTutorial.Advance(500);
				break;

			case 21:
				ListsOfChainToModify::Annihilate_All_Links(); // Efface tout les Murs et Les Links
				ev_BotTutorial.Advance(1500);
				break;
			
			case 22:				
				ConsoleRender::Add_String(doubt, Jerry_Txt_Crd(doubt), gJerClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_16, Boss_Txt_Crd(_16), gBossClr, TXT_SPD_ER, true);

				// Coord tu titre du choix
				XY.x = Find_Ctr_X((int)rate.size() / 2) - 5;
				XY.y = linkGrid->link[6][4].Get_XY().y + 4;
				ConsoleRender::Add_String(rate, XY, GRAY, TXT_SPD_DR);

				// Début d'un choix pour le joueur
				choiceCrd = { 0, 8 };

				for (int i = 0; i < 10; i++)		// Le joueur doit "Rater" la performance de Jerry!
				{
					
					if (i == 0)
					{
						ChoiceTime::Add_Choice(recom[i], "(Bad)", choiceCrd);
						choiceCrd.c += 2;
					}
					else
						if (i == 9)
						{
							choiceCrd.c++;
							ChoiceTime::Add_Choice(recom[i], "(Okay)", choiceCrd);
						}
						else
						{
							ChoiceTime::Add_Choice(recom[i], TXT_CONST.EMPTY, choiceCrd);
							choiceCrd.c++;
						}
				}

				ev_BotTutorial.Advance(0);
				ev_BotTutorial.delay.Start_Timer(2000, 1, true);	// infinite check here
				break;

			//case 23:
			//	if (!ChoiceTime::Is_Choice_Time())
			//	{
			//		ConsoleRender::Add_String(_7, Boss_Txt_Crd(_7), gBossClr, TXT_SPD_ER, true);
					//ConsoleRender::Add_String(rate, XY, GRAY, TXT_SPD_ER, true);

			//		ev_BotTutorial.delay.Stop();
			//		ev_BotTutorial.Advance(400);
			//	}
			//	break;

			//case 24:
			//	choiceMade = ChoiceTime::Get_Choice_Made();

			//	for (int i = 0; i < 10; i++)
			//	{
			//		if (choiceMade == rview[i])
			//		{
			//			//tempAnswer = answer[i];
			//			break;
			//		}
			//	}

			//	ConsoleRender::Add_String(tempAnswer, Jerry_Txt_Crd(tempAnswer), GRAY, 260);
			//	ev_BotTutorial.Advance(500);
			//	break;
			}


		}
	}
}
	

//case 14:
