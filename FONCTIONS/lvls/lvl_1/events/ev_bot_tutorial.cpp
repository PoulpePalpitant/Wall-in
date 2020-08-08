

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
#include "../../../bots/botmeta.h"
#include "../../../time/bot_move_cycle.h"
#include "../../../player/player.h"
#include "../../../structure_manager/modify_chain.h"
#include "../../../events/global_events/ev_countdown.h"
#include "../../../events/global_events/feedback/ev_glitch_screen.h"
#include "../msg_events/ev_stop_Jerry_1.h"
#include "../../../spawns/ev_spawn_Jerry.h"

static Event ev_BotTutorial(Ev_Bot_Tutorial, 100);

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
static std::string _3 = "Build Some Walls";
static std::string _4 = "Step #2";
static std::string _5 = "Let Them Smash Into Them";
static std::string _6 = "It's As Simple As That!";
static std::string _7 = "Now Jerry Here, ";
static std::string _8 = "Hi!";
static std::string _9 =  "Will Help Us With The Demonstration";
/*
	If You Would Like To Practice More 
	Just Give Me A Call
 
 */

/*
	Tutorial Goal:

	#1
	-Montrer comment les bots bougent et la limitent qu'ils ne doivent pas franchir
	Les "tirs" créer des Walls qui serveent à les arrêter

	#2 Deeper
	Les bots peuvent venir de tout les directions
	Il faut constamment construire des walls, sinon tu risque d'être overwhelm
	Faire des longues chaine des walls n'est pas une bonne stratégie, car les bots détruisent tout les walls qui dépendent de la chaîne

	#3 deeper
	Les walls peuvent se stacker dans les 4 directions
	Pour stopper les bots qui passent au milieu, mieux vaut stacker perpendiculairement
	mieux vaut ne pas tirer de loin, car le blast est en cooldown tant qu'il n'a pas atteint ça cible, c'est donc plus lent que de tirer de proche

	#idée ta très peu de temps pour arrêter des bots, et il faut que tu te déplace physiquement pour le faire, et non tirer de loin
	#idée ta très peu de temps pour arrêter des bots, et il faut que tu te stack perpendiculairement pour le faire et non spammer
*/



static std::string _10 = "Now Try To Build Some Walls";
static std::string _11 = "Jerry It's Your Turn Now";
static std::string _12 = "(You Got This Jerry!)";
static std::string _13 = "Okay, Here I Come!";
static std::string _14 = "Ow.";
static std::string _15 = "(Don't let Jerry Reach The Border)";
static std::string _16 = "Nice Work! You Stopped Jerry!";
static std::string _17 = "Actually, This Might Have Been";
static std::string _18 = "A Little Bit Too Easy";
static std::string _19 = "Let's Bring The Difficulty Up A Notch";
static std::string _20 = "You Know What To Do Jerry...";
static std::string _21 = "Yes, Mam!";
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
		//ev_BotTutorial.Go_To_X_Step(24);		// now that's a shortcut
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
				ev_BotTutorial.Advance(350);
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
				//Ev_Dr_Heart_3();

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
				Just_Dr_Heart();
				MsgQueue::Register(ACTIVATE_BLAST);	// backup

				ev_BotTutorial.Advance(200);
				break;

			case 15:
				prevMovSPeed = gBotMoveTimer.Get_Speed();	// vitesse de déplacement précédante
				Spawn_A_Jerry(RIGHT, 1, 20); // spawn Jerrry!

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

						gBotMoveTimer.Start_Timer(prevMovSPeed, 1, true);	// Rétablit la vitesse précédante
						ev_BotTutorial.delay.Stop();
						ev_BotTutorial.Advance(500);
					}
					else
					{
						//ConsoleRender::Add_String(_12, Boss_Txt_Crd(_12, 1), GRAY, TXT_SPD_ER, true);
						ConsoleRender::Add_String(sorry, Boss_Txt_Crd(sorry, 2), gBossClr, TXT_SPD_DR);
						ConsoleRender::Add_String(stop, Boss_Txt_Crd(stop, 3), gBossClr, TXT_SPD_DR);
						Ev_Glitch_Screen();

						ev_BotTutorial.delay.Stop();
						ev_BotTutorial.Go_To_X_Step(0);
						ev_BotTutorial.delay.Start_Timer(200);				
					}
				}
				break;

			case 0:
				ConsoleRender::Add_String(sorry, Boss_Txt_Crd(sorry, 2), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(stop, Boss_Txt_Crd(stop, 3), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_15, { 38 , 4 }, GRAY, TXT_SPD_DR);	// réaffichage
				Just_Dr_Arr_Keys();												// réaffichage
				P1.Player_Gains_HP();					// redonne de la vie
				
				ev_BotTutorial.delay.Start_Timer(600);
				ev_BotTutorial.Go_To_X_Step(15);
				break;

			case 18:
				ConsoleRender::Add_String(_14, Jerry_Txt_Crd(_14, 1), gJerClr, TXT_SPD_ER, true);	// Jerry à finis d'avancer
				ev_BotTutorial.Advance(700);
				break;
				
			case 19:
				ConsoleRender::Add_String(_16, Boss_Txt_Crd(_16), gBossClr, TXT_SPD_DR);
				ev_BotTutorial.Advance(350);
				break;
			
			case 20:
				ConsoleRender::Add_String(_16, Boss_Txt_Crd(_16), gBossClr, TXT_SPD_ER, true);
				ev_BotTutorial.Advance(500);
				break;
				
			case 21:
				ConsoleRender::Add_String(_17, Boss_Txt_Crd(_17), gBossClr, TXT_SPD_DR);
				ev_BotTutorial.Advance(700);
				break;

			case 22:
				ConsoleRender::Add_String(_18, Boss_Txt_Crd(_18, 1), gBossClr, TXT_SPD_DR);
				ev_BotTutorial.Advance(500);
				break;

			case 23:
				ConsoleRender::Add_String(_19, Boss_Txt_Crd(_19 , 2), gBossClr, TXT_SPD_DR);
				ev_BotTutorial.Advance(400);
				break;

			case 24:
				ConsoleRender::Add_String(_17, Boss_Txt_Crd(_17), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_18, Boss_Txt_Crd(_18, 1), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_19, Boss_Txt_Crd(_19, 2), gBossClr, TXT_SPD_ER, true);
				ev_BotTutorial.Advance(600);
				break;

			case 25:
				Set_Jerry_Time(5);
				Ev_Dr_Stop_Jerry();
				MsgQueue::Register(DEACTIVATE_BLAST);		/// Si le joueur tir avant, le blast ne sera pas cancelé
				ListsOfChainToModify::Annihilate_All_Links(); // Efface tout les Murs et Les Links
				ev_BotTutorial.Advance(400);
				break;

			case 26:
				ConsoleRender::Add_String(_15, { map.Get_Box_Limit(RIGHT) - (int)_15.length() / 2, 4 }, GRAY, TXT_SPD_DR);	// réaffichage
				Set_Flashy_Border(RIGHT, 7);
				Ev_Flash_Map_Border();	// Fait flasher la border pour signaler au joueur ou va aller Jerry
				Set_CoundDown_Dur(10);
				Ev_CountDown();	// Countdown
				ev_BotTutorial.Advance(0);
				ev_BotTutorial.delay.Start_Timer(10000, 1, true);
				break;

			case 27:
				if (CountDown_Finished())
				{
					MsgQueue::Register(ACTIVATE_BLAST);	// réactive le blast
					Spawn_A_Jerry(LEFT, 1, 20); // spawn Jerrry!
					
					ev_BotTutorial.delay.Stop();
					ev_BotTutorial.Advance(300);
				}
				break;

			case 28:
				Spawn_A_Jerry(LEFT, 10, 20); // spawn Jerrry!
				ev_BotTutorial.Advance(300);
				break;

			case 29:
				Spawn_A_Jerry(LEFT, 3, 20); // spawn Jerrry!
				ev_BotTutorial.Advance(300);
				break;

			case 30:
				Spawn_A_Jerry(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 1, 20); // spawn Jerrry!
				ev_BotTutorial.Advance(300);
				break;

			case 31:
 				Spawn_A_Jerry(LEFT, 0, 20); // spawn Jerrry!
				ev_BotTutorial.Advance(0);
				ev_BotTutorial.delay.Start_Timer(10000, 1, true);
				break;

			case 32:
				if (!jerryTime)
				{
					ConsoleRender::Add_String(_15, { map.Get_Box_Limit(RIGHT) - (int)_15.length() / 2, 4 }, GRAY, TXT_SPD_ER,true);	// réaffichage

					// say: nicely done!
					ev_BotTutorial.Advance(1000);
				}
				break;

			//case 25:
			//	ConsoleRender::Add_String(_20, Boss_Txt_Crd(_20), gBossClr, TXT_SPD_DR);	// You Know what to do
			//	ev_BotTutorial.Advance(500);
			//	break;
			//
			//case 26:
			//	ConsoleRender::Add_String(_21, Jerry_Txt_Crd(_21), gJerClr, TXT_SPD_DR);
			//	ev_BotTutorial.Advance(400);
			//	break;


				//case 20:
			//	ConsoleRender::Add_String(doubt, Jerry_Txt_Crd(doubt), gJerClr, 260);
			//	ev_BotTutorial.Advance(500);
			//	break;

			//case 21:
			//	ListsOfChainToModify::Annihilate_All_Links(); // Efface tout les Murs et Les Links
			//	ev_BotTutorial.Advance(1500);
			//	break;
			//
			//case 22:				
			//	ConsoleRender::Add_String(doubt, Jerry_Txt_Crd(doubt), gJerClr, TXT_SPD_ER, true);
			//	ConsoleRender::Add_String(_16, Boss_Txt_Crd(_16), gBossClr, TXT_SPD_ER, true);

			//	// Coord tu titre du choix
			//	XY.x = Find_Ctr_X((int)rate.size() / 2) - 5;
			//	XY.y = linkGrid->link[6][4].Get_XY().y + 4;
			//	ConsoleRender::Add_String(rate, XY, GRAY, TXT_SPD_DR);

			//	// Début d'un choix pour le joueur
			//	choiceCrd = { 0, 8 };

			//	for (int i = 0; i < 10; i++)		// Le joueur doit "Rater" la performance de Jerry!
			//	{
			//		
			//		if (i == 0)
			//		{
			//			ChoiceTime::Add_Choice(recom[i], "(Bad)", choiceCrd);
			//			choiceCrd.c += 2;
			//		}
			//		else
			//			if (i == 9)
			//			{
			//				choiceCrd.c++;
			//				ChoiceTime::Add_Choice(recom[i], "(Okay)", choiceCrd);
			//			}
			//			else
			//			{
			//				ChoiceTime::Add_Choice(recom[i], TXT_CONST.EMPTY, choiceCrd);
			//				choiceCrd.c++;
			//			}
			//	}

			//	ev_BotTutorial.Advance(0);
			//	ev_BotTutorial.delay.Start_Timer(2000, 1, true);	// infinite check here
			//	break;

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
