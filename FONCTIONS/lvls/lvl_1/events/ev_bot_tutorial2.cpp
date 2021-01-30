

#include "ev_bot_tutorial2.h"

// That is a lot of includes my dudes
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
#include "../../../bots/botlist.h"
#include "../../../structure_manager/modify_chain.h"
#include "../../../events/global_events/ev_countdown.h"
#include "../../../events/global_events/feedback/ev_glitch_screen.h"
#include "../msg_events/ev_stop_Jerry_1.h"
#include "../../../spawns/ev_spawn_Jerry.h"
#include "../events/ev_build_start_walls.h"
#include "ev_ultimate_test.h"
#include "../../../events/global_events/ev_to_proceed.h"
#include "../../../events/global_events/feedback/ev_ammo_depleted.h"
#include "../../../blast/blast_ammo_animator.h"
#include "../msg_events/ev_wasd.h"
#include "../../../events/global_events/feedback/ev_good_job.h"
#include "../../../events/global_events/feedback/ev_rainbow_borders.h"

static void Retry_If_Fail();

static Event ev_BotTutorial2(Ev_Bot_Tutorial2, 150);
static Event ev_RetryIfFail(Retry_If_Fail,2);

/* Dis gonna be a long one:
	
	Tutorial qui montre au joueur comment jouer. 
	Choses à montrer:

	- Les Bots, leurs déplacement et leur destination
	- Tirer, comment stacker perpendiculairement
	- Détuire les bots, en utilisant la méthode de tirer, ne peut pas tirer directement dessus(en fait techniquement oui)
	- La notion d'ammo limité
	- Enticiper les déplacements
*/

static Coord XY;			// Pour tout les XY
static GrdCoord choiceCrd;
static bool overShot = false;
static GrdCoord dotChase;

static std::string b = BOT_DESIGN_1C[1] + " ' ";
static std::string _15_1 = ("(Don't let the 'Shape' reach this border) : ");
static std::string _15_2 = ("(Don't let the shapes reach this border)");
static std::string _24 = "- Ammo is limited - ";
static std::string _24_1 = "Overshooting Drains HEALTH";
static std::string _25 = "(<-- Try this)";

static std::string _20 = "TUTORIAL COMPLETE!";




static int stepToSendBack;	// Si le joueur fail une étape, il va devoir être send back à une étape précédante
static bool practiceTime = false;

static void Retry_If_Fail()
{
	if (!ev_RetryIfFail.Is_Active())
	{
		ev_RetryIfFail.Activate();
		ev_RetryIfFail.Start(0);
		ev_RetryIfFail.delay.Stop();
		ev_RetryIfFail.delay.Start_Timer(100000, 1, true);
	}
	else
	{
		if (!P1.Get_HP())		// Fait restarter la séquence 
		{
			MsgQueue::Register(LOCK_PLAYER);
			MsgQueue::Register(DISABLE_BLAST);
			Ev_Glitch_Map_Retry();
			Stop_Ev_Dr_Stop_Jerry();	// stop l'even de jerrys
			Ev_Stop_Spawn_Jerry();		// arrête cet event, mais si il est actif une fois à la fin
			ListsOfChainToModify::Annihilate_All_Links();	// for good mesure
			BotList::Destroy_All_Bots();	// clear les bots qui aurait pu resté
			Restore_Prev_Bot_Speed();	// rétablit la vitesse précédante

			if (stepToSendBack > 100)
				Press_X_To_Proceed(0, true);// idem
			P1.Set_Hp(3);
			Cancel_Ev_Ammo_Depleted();
			blastP1.Get_Ammo_Manager().Deactivate();

			jerryTime = false;
			CountDown_Cancel();

			ev_BotTutorial2.delay.Stop();
			ev_BotTutorial2.delay.Start_Timer(200);
			ev_BotTutorial2.Go_To_X_Step(stepToSendBack);
		}
	}
}

static void Free_Das_Player()
{
	MsgQueue::Register(FREE_PLAYER);
	MsgQueue::Register(ENABLE_BLAST);
}

static void Setup()
{
	Just_Dr_Wasd();
	Just_Dr_Arr_Keys();
	Free_Das_Player();
	P1.Dr_Player();
	Retry_If_Fail();
	Draw_Tuto_Progression(0);
}



void Ev_Bot_Tutorial2()// Trace un chemin vers une fausse porte de sortie
{
	if (!ev_BotTutorial2.Is_Active())
	{
		prevMovSpeed = 10000;
		MsgQueue::Register(FREE_PLAYER);
		ev_BotTutorial2.Activate();
		ev_BotTutorial2.Start(1000);
		//ev_BotTutorial2.Go_To_X_Step(35);		// freetime
		//ev_BotTutorial2.Go_To_X_Step(20);		// third
		//ev_BotTutorial2.Go_To_X_Step(10);		// second trial
		//ev_BotTutorial2.Go_To_X_Step(4);		// first trial

		Retry_If_Fail();
	}
	else	// doin stuff 
	{


		while (ev_BotTutorial2.delay.Tick())
		{
			static int step; step = ev_BotTutorial2.Get_Current_Step();


			switch (step)	// STEP 1 à 20 -> Montre au joueur comment se déplacer
			{
			case 1:

				dotChase = { 6, 6 };		// Premier Dot
				if (P1.Get_Grd_Coord().c == 6 || P1.Get_Grd_Coord().r == 6)
					dotChase = { 8, 8 };

				ConsoleRender::Add_Char(linkGrid->link[dotChase.c][dotChase.r].Get_XY(), '?', LIGHT_GREEN);
				ev_BotTutorial2.Advance(0);
				ev_BotTutorial2.delay.Start_Timer(10000, 1, true);	// va checker à l'infinie pour vérifier si le joueur se trouve sur la position
				break;

			case 2:
				if (Are_Equal(P1.Get_Grd_Coord(), dotChase))	// Si le player se déplace sur le dot
				{
					Draw_Tuto_Progression(1);

					Set_Dr_Map_1(TXT_SPD_DR * 3);	// Erase les borders

					ev_BotTutorial2.delay.Stop();
					ev_BotTutorial2.Advance(700);
				}
				break;

			case 3:
				Ev_Dr_Arr_Keys();
				ev_BotTutorial2.Advance(100);
				break;

			case 4:
				stepToSendBack = 4;
				ev_BotTutorial2.Advance(500);
				break;

			case 5:
				ConsoleRender::Add_String(_15_1, { map.Get_Box_Limit(LEFT) - Half_String(_15_1) - 4 , map.Get_Box_Limit(UP) - 3 }, GRAY, TXT_SPD_DR);
				ConsoleRender::Add_Char({ map.Get_Box_Limit(LEFT) + Half_String(_15_1) - 2 , map.Get_Box_Limit(UP) - 3 }, BOT_DESIGN_1C[1], LIGHT_RED);

				Set_Flashy_Border(LEFT);
				Ev_Flash_Map_Border();	// Fait flasher la border pour signaler au joueur ou va aller Jerry
				Setup();

				ev_BotTutorial2.Advance(200);
				break;

			case 6:
				prevMovSpeed = gBotMoveTimer.Get_Speed();	// vitesse de déplacement précédante
				Spawn_A_Jerry(RIGHT, 1, 30); // spawn Jerrry!
				ev_BotTutorial2.Advance(0);
				break;

			case 7:
				ev_BotTutorial2.Advance(0);
				ev_BotTutorial2.delay.Start_Timer(50000, 1, true);
				break;

			case 8:
				if (!gAllBotMeta.alive)
				{
					if (P1.Get_HP() == 3)	// Si le joueur à péter Jerry
					{
						ConsoleRender::Add_String(_15_1, { map.Get_Box_Limit(LEFT) - Half_String(_15_1) - 4 , map.Get_Box_Limit(UP) - 3 }, GRAY, TXT_SPD_DR, 1);
						ConsoleRender::Add_Char({ map.Get_Box_Limit(LEFT) + Half_String(_15_1) - 2 , map.Get_Box_Limit(UP) - 3 }, TXT_CONST.SPACE);

						gBotMoveTimer.Start_Timer(prevMovSpeed, 1, true);	// Rétablit la vitesse précédante
						ev_BotTutorial2.delay.Stop();
						ev_BotTutorial2.Advance(0);

						Draw_Tuto_Progression(1);
						Ev_Rainbow_Borders();				// fait flasher tout de manière gratifiante
						Ev_Good_Job();						// Félicite le joueur
					}
					else
						Retry_If_Fail();	// Si le joueur fail un bout du tutorial, on step back sur des étapes de l'event
				}
				break;

			case 9:
				ev_BotTutorial2.Advance(0);
				break;

			case 10:
				stepToSendBack = 10;	// si le joueur fail ce test, il sera send back à cette étape
				ev_BotTutorial2.Advance(1000);
				break;

			case 11:
				Free_Das_Player();
				Set_CountDown(10);
				Ev_CountDown();	// Countdown
				ev_BotTutorial2.Advance(600);
				break;

			case 12:
				Set_Jerry_Time(5);
				Ev_Dr_Stop_Jerry();
				ListsOfChainToModify::Annihilate_All_Links(); // Efface tout les Murs et Les Links										
				P1.Set_Hp(3); Just_Dr_Arr_Keys();	// réaffichage et redonne de la vie

				MsgQueue::Register(DISABLE_BLAST);		/// Si le joueur tir avant, le blast ne sera pas cancelé
				ev_BotTutorial2.Advance(400);
				break;

			case 13:
				ConsoleRender::Add_String(_15_2, { map.Get_Box_Limit(RIGHT) - Half_String(_15_2) , map.Get_Box_Limit(UP) - 3 }, GRAY, TXT_SPD_DR);	// réaffichage
				Set_Flashy_Border(RIGHT, 11);
				Ev_Flash_Map_Border();	// Fait flasher la border pour signaler au joueur ou va aller Jerry

				ev_BotTutorial2.Advance(0);
				ev_BotTutorial2.delay.Start_Timer(10000, 1, true);
				break;

			case 14:
				if (CountDown_Finished())
				{
					MsgQueue::Register(ENABLE_BLAST);	// réactive le blast
					Spawn_A_Jerry(LEFT, 1, 20); // spawn Jerrry!

					ev_BotTutorial2.delay.Stop();
					ev_BotTutorial2.Advance(400);
				}
				break;

			case 15:
				Spawn_A_Jerry(LEFT, 10, 20); // spawn Jerrry!
				ev_BotTutorial2.Advance(400);
				break;

			case 16:
				Spawn_A_Jerry(LEFT, 3, 20); // spawn Jerrry!
				ev_BotTutorial2.Advance(400);
				break;

			case 17:
				Spawn_A_Jerry(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 1, 20); // spawn Jerrry!
				ev_BotTutorial2.Advance(400);
				break;

			case 18:
				Spawn_A_Jerry(LEFT, 0, 20); // spawn Jerrry!
				ev_BotTutorial2.Advance(0);
				ev_BotTutorial2.delay.Start_Timer(10000, 1, true);
				break;

			case 19:
				if (!jerryTime && P1.Get_HP() != 0)
				{
					ConsoleRender::Add_String(_15_2, { map.Get_Box_Limit(RIGHT) - Half_String(_15_2) , map.Get_Box_Limit(UP) - 3 }, GRAY, TXT_SPD_ER, true);

					Draw_Tuto_Progression(1);
					Ev_Rainbow_Borders();				// fait flasher tout de manière gratifiante
					Ev_Good_Job();						// Félicite le joueur

					ev_BotTutorial2.delay.Stop();
					ev_BotTutorial2.Advance(300);
				}
				break;


			case 20:
				blastP1.Cancel();
				CountDown_Cancel();
				stepToSendBack = 20;	// si le joueur fail ce test, il sera send back icitte
				ConsoleRender::Add_String(_24, Jerry_Txt_Crd(_24), WHITE, TXT_SPD_DR);


				MsgQueue::Register(DISABLE_BLAST);
				ev_BotTutorial2.Advance(300);
				break;

			case 21:
				Setup();
				ListsOfChainToModify::Annihilate_All_Links(); // Efface tout les Murs et Les Links										

				Set_CountDown(10);
				Ev_CountDown();	// Countdown
				blastP1.Get_Ammo_Manager().Set_Ammo(7);
				ev_BotTutorial2.Advance(420);
				break;

			case 22:
				Build_Lvl_1_Walls();
				ConsoleRender::Add_String(_25, { map.Get_Box_Limit(RIGHT) + 4 , linkGrid->link[0][linkGrid->Get_Rows() / 2].Get_XY().y - 2 }, GRAY, TXT_SPD_DR);	// lols

				MsgQueue::Register(DISABLE_BLAST);

				ev_BotTutorial2.Advance(350);
				break;

			case 23:
				Set_Jerry_Time(5);
				Ev_Dr_Stop_Jerry();
				P1.Set_Hp(3);

				ev_BotTutorial2.Advance(400);
				break;

			case 24:
				ConsoleRender::Add_String(_15_2, { map.Get_Box_Limit(RIGHT) - Half_String(_15_2) , map.Get_Box_Limit(UP) - 3 }, GRAY, TXT_SPD_DR);	// réaffichage
				Set_Flashy_Border(RIGHT, 11);
				Ev_Flash_Map_Border();

				ev_BotTutorial2.Advance(0);
				ev_BotTutorial2.delay.Start_Timer(10000, 1, true);
				break;

			case 25:
				if (CountDown_Finished())
				{
					MsgQueue::Register(ENABLE_BLAST);
					Spawn_A_Jerry(LEFT, 3, SPWN_DLAY);

					ev_BotTutorial2.delay.Stop();
					ev_BotTutorial2.Advance(500);
				}
				break;

			case 26:
				Spawn_A_Jerry(LEFT, 6, SPWN_DLAY); // spawn Jerrry!
				ev_BotTutorial2.Advance(400);
				break;

			case 27:

				Spawn_A_Jerry(LEFT, 8, SPWN_DLAY); // spawn Jerrry!
				ev_BotTutorial2.Advance(400);
				break;

			case 28:
				Spawn_A_Jerry(LEFT, 6, SPWN_DLAY); // spawn Jerrry!
				ev_BotTutorial2.Advance(400);
				break;

			case 29:
				Spawn_A_Jerry(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 5, SPWN_DLAY); // spawn Jerrry!
				ev_BotTutorial2.Advance(150);
				break;

			case 30:
				ev_BotTutorial2.Advance(0);
				break;

			case 31:
				ev_BotTutorial2.Advance(0);
				break;

			case 32:
				ev_BotTutorial2.Advance(0);
				break;

			case 33:
				ev_BotTutorial2.Advance(0);
				ev_BotTutorial2.delay.Start_Timer(10000, 1, true);
				break;

			case 34:
				if (!jerryTime && P1.Get_HP() != 0)
				{
					blastP1.Get_Ammo_Manager().Deactivate();
					ConsoleRender::Add_String(_24, Jerry_Txt_Crd(_24), gBossClr, TXT_SPD_ER, 1);
					ConsoleRender::Add_String(_25, { map.Get_Box_Limit(RIGHT) + 4 , linkGrid->link[0][linkGrid->Get_Rows() / 2].Get_XY().y - 2 }, WHITE, TXT_SPD_ER, true);	// lols


					ConsoleRender::Add_String(_15_2, { map.Get_Box_Limit(RIGHT) - Half_String(_15_2) , map.Get_Box_Limit(UP) - 3 }, GRAY, TXT_SPD_ER, true);
					ListsOfChainToModify::Annihilate_All_Links();
					P1.Set_Hp(3);

					Draw_Tuto_Progression(1);
					Ev_Rainbow_Borders();				// fait flasher tout de manière gratifiante
					Ev_Good_Job();						// Félicite le joueur

					ev_BotTutorial2.delay.Stop();
					ev_BotTutorial2.Advance(300);
				}
				break;

			case 35:
				clrscr();
				stepToSendBack = 35;
				Setup();
				P1.Set_Hp(3);
				
				gCurrentStage = 2;
				Press_X_To_Proceed(1);

				//gCurrentStage = 2;
				ConsoleRender::Add_String(_20, Up_Txt_2(_20), LIGHT_GREEN, TXT_SPD_DR);
				ev_BotTutorial2.Advance(500);
				break;

			case 36:
				if (!practiceTime)	// Jerry Might Not want to help you
				{
					jerryTime = true;
					Make_It_Vertical_Only();
					Set_Jerry(NONE, -1, prevMovSpeed);	// Tu peux pas mettre un boxisde random et une crd de spawn specific
					Ev_Spawn_Jerry();

					MsgQueue::Register(ENABLE_BLAST);
				}

				ev_BotTutorial2.Advance(400);
				ev_BotTutorial2.delay.Start_Timer(10000, 1, true);	// l'event doit rester actif si le joueur die.
				break;


				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				// Cet Event Doit être arrêté manuellement!
			}
		}
	}
}

void Cancel_All_That_Buggy_Shit() {
	ev_BotTutorial2.Cancel();
	ev_RetryIfFail.Cancel();
}
//
//// __/\\\\\\\\\\\\\\\__/\\\________/\\\________/\\\\\\\\\__/\\\________/\\\_______________/\\\____        
////  _\/\\\///////////__\/\\\_______\/\\\_____/\\\////////__\/\\\_____/\\\//______________/\\\\\\\__       
////   _\/\\\_____________\/\\\_______\/\\\___/\\\/___________\/\\\__/\\\//________________/\\\\\\\\\_      
////    _\/\\\\\\\\\\\_____\/\\\_______\/\\\__/\\\_____________\/\\\\\\//\\\_______________\//\\\\\\\__     
////     _\/\\\///////______\/\\\_______\/\\\_\/\\\_____________\/\\\//_\//\\\_______________\//\\\\\___    
////      _\/\\\_____________\/\\\_______\/\\\_\//\\\____________\/\\\____\//\\\_______________\//\\\____   
////       _\/\\\_____________\//\\\______/\\\___\///\\\__________\/\\\_____\//\\\_______________\///_____  
////        _\/\\\______________\///\\\\\\\\\/______\////\\\\\\\\\_\/\\\______\//\\\_______________/\\\____ 
////         _\///_________________\/////////___________\/////////__\///________\///_______________\///_____
//                                                                                                       
