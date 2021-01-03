

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


static Event ev_BotTutorial(Ev_Bot_Tutorial2, 150);

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



/*
	Tutorial Goal:

	#1
	-Montrer comment les bots bougent et la limitent qu'ils ne doivent pas franchir		/ lash la border
	Les "tirs" créer des Walls qui serveent à les arrêter

	#2 Deeper
	Les bots peuvent venir de tout les directions	/ gauche et droite
	Il faut constamment construire des walls, sinon tu risque d'être overwhelm(instaurer climat d'urgence)	/ Avec le countdown

	#3 deeper
	Les walls peuvent se stacker dans les 4 directions	/ Le boute avec les smaller walls
	Pour stopper les bots qui passent au milieu, mieux vaut stacker perpendiculairement  / illustré, mais pas conditionné
	Faire des longues chaine des walls n'est pas une bonne stratégie, car les bots détruisent tout les walls qui dépendent de la chaîne / dit au joueur :(
	mieux vaut ne pas tirer de loin, car le blast est en cooldown tant qu'il n'a pas atteint ça cible, c'est donc plus lent que de tirer de proche / mmmm

	#idée ta très peu de temps pour arrêter des bots, et il faut que tu te déplace physiquement pour le faire, et non tirer de loin
	#idée ta très peu de temps pour arrêter des bots, et il faut que tu te stack perpendiculairement pour le faire et non spammer
*/

static std::string _15 = "(Don't Let Jerry Reach The Border)";
static std::string _15_1 = "(Don't let The Shapes Reach This Border)";
static std::string _24 = "Overshooting Drains HEALTH";
static std::string _25 = "(<-- Try this)";
static std::string _26 = "- AMMO";

static int stepToSendBack;	// Si le joueur fail une étape, il va devoir être send back à une étape précédante
static bool practiceTime = false;

static bool Retry_If_Fail()
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
		Cancel_Ultimate_Test();		// idem

		if (stepToSendBack > 100)
			Press_X_To_Proceed(0, true);// idem
		P1.Set_Hp(3);
		Cancel_Ev_Ammo_Depleted();
		blastP1.Get_Ammo_Manager().Deactivate();

		ev_BotTutorial.delay.Stop();
		ev_BotTutorial.delay.Start_Timer(200);
		ev_BotTutorial.Go_To_X_Step(stepToSendBack);
		return true;
	}
	return false;
}

static void Free_Das_Player()
{
	MsgQueue::Register(FREE_PLAYER);
	MsgQueue::Register(ENABLE_BLAST);
}


void Ev_Bot_Tutorial2()// Trace un chemin vers une fausse porte de sortie
{
	if (!ev_BotTutorial.Is_Active())
	{
		prevMovSpeed = 10000;
		MsgQueue::Register(FREE_PLAYER);
		ev_BotTutorial.Activate();
		ev_BotTutorial.Start(350);
		//ev_BotTutorial.Go_To_X_Step(140);		// jerry answer
		//ev_BotTutorial.Go_To_X_Step(130);		// jerry's is sorry
		//ev_BotTutorial.Go_To_X_Step(114);		// just survived
		//ev_BotTutorial.Go_To_X_Step(58);		// ultimate test start
		//ev_BotTutorial.Go_To_X_Step(41);		// now that's a shortcut
		//ev_BotTutorial.Go_To_X_Step(25);		// second trial
		//ev_BotTutorial.Go_To_X_Step(18);		// first trial
	}
	//else	// doin stuff 
	//{
	//	while (ev_BotTutorial.delay.Tick())
	//	{
	//		if (jerryTime)
	//			Retry_If_Fail();	// Si le joueur fail un bout du tutorial, on step back sur des étapes de l'event


	//		static int step; step = ev_BotTutorial.Get_Current_Step();

	//		switch (step)	// STEP 1 à 20 -> Montre au joueur comment se déplacer
	//		{
	//		case 1:
	//			ConsoleRender::Add_String(_1, Boss_Txt_Crd(_1), gBossClr, TXT_SPD_DR);
	//			ev_BotTutorial.Advance(300);
	//			break;

	//		case 2:
	//			ConsoleRender::Add_String(_1, Boss_Txt_Crd(_1), gBossClr, TXT_SPD_FAST, true);
	//			ev_BotTutorial.Advance(500);

	//			Ev_Dumb_Dialogue_Fixer();
	//			ev_BotTutorial.delay.Start_Timer(10000, 1, true);
	//			break;

	//		case 3:
	//			if (!ev_DumbDialogueFixer.Is_Active())
	//			{
	//				ev_BotTutorial.delay.Stop();
	//				ConsoleRender::Add_String(_2, Boss_Txt_Crd(_2), gBossClr, TXT_SPD_DR);
	//				ev_BotTutorial.Advance(600);
	//			}
	//			break;

	//		case 4:
	//			ConsoleRender::Add_String(_3, Boss_Txt_Crd(_3, 1), gBossClr, TXT_SPD_DR);
	//			ev_BotTutorial.Advance(700);
	//			break;

	//		case 5:
	//			ConsoleRender::Add_String(_4, Boss_Txt_Crd(_4, 2), gBossClr, TXT_SPD_DR);
	//			ev_BotTutorial.Advance(700);
	//			break;

	//		case 6:
	//			ConsoleRender::Add_String(_5, Boss_Txt_Crd(_5, 3), gBossClr, TXT_SPD_DR);
	//			ev_BotTutorial.Advance(350);
	//			break;

	//		case 7:
	//			ConsoleRender::Add_String(_2, Boss_Txt_Crd(_2), gBossClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_3, Boss_Txt_Crd(_3, 1), gBossClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_4, Boss_Txt_Crd(_4, 2), gBossClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_5, Boss_Txt_Crd(_5, 3), gBossClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_6, Boss_Txt_Crd(_6), gBossClr, TXT_SPD_DR);
	//			ev_BotTutorial.Advance(400);
	//			break;


	//		case 8:
	//			ConsoleRender::Add_String(_6, Boss_Txt_Crd(_6), gBossClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_7, Boss_Txt_Crd(_7, 1), gBossClr, TXT_SPD_DR);
	//			ev_BotTutorial.Advance(1000);
	//			break;

	//		case 9:
	//			ConsoleRender::Add_String(_8, Jerry_Txt_Crd(_8), gJerClr, TXT_SPD_DR);
	//			ev_BotTutorial.Advance(1000);
	//			break;

	//		case 10:
	//			ConsoleRender::Add_String(_8, Jerry_Txt_Crd(_8), gJerClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_9, Boss_Txt_Crd(_9, 2), gBossClr, TXT_SPD_DR);
	//			ev_BotTutorial.Advance(500);

	//			break;

	//		case 11:
	//			ConsoleRender::Add_String(_7, Boss_Txt_Crd(_7, 1), gBossClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_9, Boss_Txt_Crd(_9, 2), gBossClr, TXT_SPD_ER, true);
	//			Set_Dr_Map_1(TXT_SPD_DR * 3);	// Erase les borders
	//			ev_BotTutorial.Advance(700);
	//			break;

	//		case 12:
	//			Ev_Dr_Arr_Keys();
	//			ConsoleRender::Add_String(_10, Boss_Txt_Crd(_10), gBossClr, TXT_SPD_DR);
	//			ev_BotTutorial.Advance(50);
	//			break;

	//		case 13:
	//			ConsoleRender::Add_String(_10, Boss_Txt_Crd(_10), gBossClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_11, Boss_Txt_Crd(_11, 1), gBossClr, TXT_SPD_DR);
	//			ev_BotTutorial.Advance(400);
	//			break;
	//		
	//		case 14:
	//			ConsoleRender::Add_String(_15, { map.Get_Box_Limit(LEFT) - Half_String(_15) , map.Get_Box_Limit(UP) - 3 }, GRAY, TXT_SPD_DR);
	//			ConsoleRender::Add_String(_11, Boss_Txt_Crd(_11, 1), gBossClr, TXT_SPD_ER, true);
	//			Set_Flashy_Border(LEFT);
	//			Ev_Flash_Map_Border();	// Fait flasher la border pour signaler au joueur ou va aller Jerry
	//			Just_Dr_Heart();
	//			MsgQueue::Register(ENABLE_BLAST);	// backup
	//			ev_BotTutorial.Advance(200);
	//			break;

	//		case 15:
	//			prevMovSpeed = gBotMoveTimer.Get_Speed();	// vitesse de déplacement précédante
	//			Spawn_A_Jerry(RIGHT, 1, 30); // spawn Jerrry!
	//			ConsoleRender::Add_String(_13, Jerry_Txt_Crd(_13), gJerClr, TXT_SPD_DR);
	//			ev_BotTutorial.Advance(250);
	//			break;


	//		case 16:
	//			ConsoleRender::Add_String(_13, Jerry_Txt_Crd(_13), gJerClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_12, Boss_Txt_Crd(_12, 5), gBossClr, TXT_SPD_DR);

	//			ev_BotTutorial.Advance(0);
	//			ev_BotTutorial.delay.Start_Timer(5000,1, true);
	//			break;

	//		case 17:
	//			if (!gAllBotMeta.alive)
	//			{
	//				if (P1.Get_HP() == 3)	// Si le joueur à péter Jerry
	//				{
	//					ConsoleRender::Add_String(_14, Jerry_Txt_Crd(_14, 1), gJerClr, TXT_SPD_DR);	// Jerry à finis d'avancer
	//					//ConsoleRender::Add_String(sorry, Boss_Txt_Crd(sorry, 2), gBossClr, TXT_SPD_ER, true);
	//					//ConsoleRender::Add_String(stop, Boss_Txt_Crd(stop, 3), gBossClr, TXT_SPD_ER, true);
	//					ConsoleRender::Add_String(_15_1, { map.Get_Box_Limit(LEFT) - Half_String(_15) , map.Get_Box_Limit(UP) - 3 }, GRAY, TXT_SPD_ER, true);
	//					ConsoleRender::Add_String(_12, Boss_Txt_Crd(_12, 5), gBossClr, TXT_SPD_DR, true);

	//					gBotMoveTimer.Start_Timer(prevMovSpeed, 1, true);	// Rétablit la vitesse précédante
	//					ev_BotTutorial.delay.Stop();
	//					ev_BotTutorial.Advance(500);
	//				}
	//				else
	//				{
	//					//ConsoleRender::Add_String(sorry, Boss_Txt_Crd(sorry, 2), gBossClr, TXT_SPD_DR);
	//					//ConsoleRender::Add_String(stop, Boss_Txt_Crd(stop, 3), gBossClr, TXT_SPD_DR);
	//					ListsOfChainToModify::Annihilate_All_Links(); // Efface tout les Murs et Les Links										
	//					Ev_Glitch_Map_Retry();

	//					ev_BotTutorial.delay.Stop();
	//					ev_BotTutorial.Go_To_X_Step(0);
	//					ev_BotTutorial.delay.Start_Timer(200);				
	//				}
	//			}
	//			break;

	//		case 0:
	//			ConsoleRender::Add_String(sorry, Boss_Txt_Crd(sorry, 2), gBossClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(stop, Boss_Txt_Crd(stop, 3), gBossClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_15_1, { map.Get_Box_Limit(LEFT) - Half_String(_15) , map.Get_Box_Limit(UP) - 3 }, GRAY, TXT_SPD_DR);	// réaffichage
	//			Just_Dr_Arr_Keys();												// réaffichage
	//			P1.Player_Gains_HP();					// redonne de la vie
	//			
	//			ev_BotTutorial.delay.Start_Timer(600);
	//			ev_BotTutorial.Go_To_X_Step(15);
	//			break;

	//		case 18:
	//			ConsoleRender::Add_String(_14, Jerry_Txt_Crd(_14, 1), gJerClr, TXT_SPD_ER, true);	// Jerry à finis d'avancer
	//			ev_BotTutorial.Advance(700);
	//			break;
	//			
	//		case 19:
	//			ConsoleRender::Add_String(_16, Boss_Txt_Crd(_16), gBossClr, TXT_SPD_DR);
	//			ev_BotTutorial.Advance(350);
	//			break;
	//		
	//		case 20:
	//			ConsoleRender::Add_String(_16, Boss_Txt_Crd(_16), gBossClr, TXT_SPD_ER, true);
	//			ev_BotTutorial.Advance(500);
	//			break;
	//			
	//		case 21:
	//			ConsoleRender::Add_String(_17, Boss_Txt_Crd(_17), gBossClr, TXT_SPD_DR);
	//			ev_BotTutorial.Advance(700);
	//			break;

	//		case 22:
	//			ConsoleRender::Add_String(_18, Boss_Txt_Crd(_18, 1), gBossClr, TXT_SPD_DR);
	//			ev_BotTutorial.Advance(500);
	//			break;

	//		case 23:
	//			ConsoleRender::Add_String(_19, Boss_Txt_Crd(_19 , 2), gBossClr, TXT_SPD_DR);
	//			ev_BotTutorial.Advance(400);
	//			break;

	//		case 24:
	//			Free_Das_Player();
	//			ConsoleRender::Add_String(_17, Boss_Txt_Crd(_17), gBossClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_18, Boss_Txt_Crd(_18, 1), gBossClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_19, Boss_Txt_Crd(_19, 2), gBossClr, TXT_SPD_ER, true);
	//			Set_CountDown(10);
	//			Ev_CountDown();	// Countdown
	//			ev_BotTutorial.Advance(600);
	//			break;

	//		case 25:
	//			stepToSendBack = 24;	// si le joueur fail ce test, il sera send back à cette étape
	//			Set_Jerry_Time(5);
	//			Ev_Dr_Stop_Jerry();
	//			ListsOfChainToModify::Annihilate_All_Links(); // Efface tout les Murs et Les Links										
	//			P1.Set_Hp(3); Just_Dr_Heart(); Just_Dr_Arr_Keys();	// réaffichage et redonne de la vie

	//			MsgQueue::Register(DISABLE_BLAST);		/// Si le joueur tir avant, le blast ne sera pas cancelé
	//			ev_BotTutorial.Advance(400);
	//			break;

	//		case 26:
	//			ConsoleRender::Add_String(_15_1, { map.Get_Box_Limit(RIGHT) - Half_String(_15) , map.Get_Box_Limit(UP) - 3 }, GRAY, TXT_SPD_DR);	// réaffichage
	//			Set_Flashy_Border(RIGHT, 11);
	//			Ev_Flash_Map_Border();	// Fait flasher la border pour signaler au joueur ou va aller Jerry

	//			ev_BotTutorial.Advance(0);
	//			ev_BotTutorial.delay.Start_Timer(10000, 1, true);
	//			break;

	//		case 27:
 //				if (CountDown_Finished())
	//			{
	//				MsgQueue::Register(ENABLE_BLAST);	// réactive le blast
	//				Spawn_A_Jerry(LEFT, 1, 20); // spawn Jerrry!
	//				
	//				ev_BotTutorial.delay.Stop();
	//				ev_BotTutorial.Advance(400);
	//			}
	//			break;

	//		case 28:
	//			Spawn_A_Jerry(LEFT, 10, 20); // spawn Jerrry!
	//			ev_BotTutorial.Advance(400);
	//			break;

	//		case 29:
	//			Spawn_A_Jerry(LEFT, 3, 20); // spawn Jerrry!
	//			ev_BotTutorial.Advance(400);
	//			break;

	//		case 30:
	//			Spawn_A_Jerry(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 1, 20); // spawn Jerrry!
	//			ev_BotTutorial.Advance(400);
	//			break;

	//		case 31:
 //				Spawn_A_Jerry(LEFT, 0, 20); // spawn Jerrry!
	//			ev_BotTutorial.Advance(0);
	//			ev_BotTutorial.delay.Start_Timer(10000, 1, true);
	//			break;

	//		case 32:
	//			if (!jerryTime)
	//			{
	//				ConsoleRender::Add_String(_15_1, { map.Get_Box_Limit(RIGHT) - Half_String(_15) , map.Get_Box_Limit(UP) - 3 }, GRAY, TXT_SPD_ER, true);
	//				ConsoleRender::Add_String(_20, Boss_Txt_Crd(_20), gBossClr, TXT_SPD_DR);	// // congratz!			
	//				ev_BotTutorial.delay.Stop();
	//				ev_BotTutorial.Advance(500);
	//			}				
	//			break;

	//		case 33:
	//			ConsoleRender::Add_String(_21, Boss_Txt_Crd(_21, 1), gBossClr, TXT_SPD_DR);	// // congratz!				
	//			ev_BotTutorial.Advance(400);
	//			break;


	//		case 34:
	//			ConsoleRender::Add_String(jer_1, Jerry_Txt_Crd(jer_1), gJerClr, TXT_SPD_DR); // jerry wants feedback too :(				
	//			ev_BotTutorial.Advance(600);
	//			break;

	//		case 35:
	//			ConsoleRender::Add_String(jer_2, Jerry_Txt_Crd(jer_2,1), gJerClr, TXT_SPD_DR);
	//			ConsoleRender::Add_String(_20, Boss_Txt_Crd(_20), gBossClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_21, Boss_Txt_Crd(_21, 1), gBossClr, TXT_SPD_ER, true);			
	//			ev_BotTutorial.Advance(400);
	//			break;

	//		case 36:
	//			ConsoleRender::Add_String(jer_3, Boss_Txt_Crd(jer_3), gBossClr, TXT_SPD_DR);
	//			ev_BotTutorial.Advance(500);
	//			break;		
	//		
	//		case 37:
	//			ConsoleRender::Add_String(jer_1, Jerry_Txt_Crd(jer_1), gJerClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(jer_2, Jerry_Txt_Crd(jer_2, 1), gJerClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(jer_4, Jerry_Txt_Crd(jer_4, 2), GRAY, TXT_SPD_DR);
	//			ev_BotTutorial.Advance(300);
	//			break;

	//		case 38:
	//			ConsoleRender::Add_String(jer_4, Jerry_Txt_Crd(jer_4, 2), gJerClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(jer_3, Boss_Txt_Crd(jer_3), gBossClr, TXT_SPD_ER, true);
	//			ev_BotTutorial.Advance(1000);
	//			break;

	//		case 39:
	//			ConsoleRender::Add_String(_22, Boss_Txt_Crd(_22), gBossClr, TXT_SPD_DR);				
	//			ev_BotTutorial.Advance(500);
	//			break;

	//		case 40:
	//			MsgQueue::Register(DISABLE_BLAST);		/// Si le joueur tir avant, le blast ne sera pas cancelé
	//			ConsoleRender::Add_String(_23, Boss_Txt_Crd(_23, 1), gBossClr, TXT_SPD_DR);
	//			ev_BotTutorial.Advance(500);
	//			break;

	//		case 41:
	//			P1.Dr_Player();
	//			MsgQueue::Register(FREE_PLAYER);
	//			ConsoleRender::Add_String(_24, Boss_Txt_Crd(_24, 2), gBossClr, TXT_SPD_DR);			
	//			ListsOfChainToModify::Annihilate_All_Links(); // Efface tout les Murs et Les Links										
	//			Set_CountDown(10);
	//			Ev_CountDown();	// Countdown
	//			blastP1.Get_Ammo_Manager().Set_Ammo(10);
	//			ConsoleRender::Add_String(_26, { (map.Get_Box_Limit(RIGHT) + 12),(map.Get_Box_Limit(UP) - 1) }, GRAY, TXT_SPD_DR);	// AMMO
	//			ev_BotTutorial.Advance(420);
	//			break;

	//		case 42:
	//			MsgQueue::Register(DISABLE_BLAST);		/// Si le joueur tir avant, le blast ne sera pas cancelé
	//			ConsoleRender::Add_String(_25, { map.Get_Box_Limit(RIGHT)  + 4 , linkGrid->link[0][linkGrid->Get_Rows() / 2].Get_XY().y - 2 }, GRAY, TXT_SPD_DR);	// lols
	//			Build_Lvl_1_Walls();			// Builder un wall qui se fait destroy LOCK le jeu indéfinimment
	//			ev_BotTutorial.Advance(350);
	//			break;

	//		case 43:
	//			stepToSendBack = 41;	// si le joueur fail ce test, il sera send back icitte
	//			Set_Jerry_Time(5);
	//			Ev_Dr_Stop_Jerry();
	//			P1.Set_Hp(3); Just_Dr_Heart(); Just_Dr_Arr_Keys();	// réaffichage et redonne de la vie	BACKUP
	//			ev_BotTutorial.Advance(400);
	//			break;						

	//		case 44:
	//			ConsoleRender::Add_String(_15_1, { map.Get_Box_Limit(RIGHT) - Half_String(_15) , map.Get_Box_Limit(UP) - 3 }, GRAY, TXT_SPD_DR);	// réaffichage
	//			Set_Flashy_Border(RIGHT, 11);
	//			Ev_Flash_Map_Border();	// Fait flasher la border pour signaler au joueur ou va aller Jerry

	//			ev_BotTutorial.Advance(0);
	//			ev_BotTutorial.delay.Start_Timer(10000, 1, true);
	//			break;

	//		case 45:
	//			if (CountDown_Finished())
	//			{
	//				MsgQueue::Register(ENABLE_BLAST);	// réactive le blast
	//				Spawn_A_Jerry(LEFT, 3, SPWN_DLAY); // spawn Jerrry!

	//				ev_BotTutorial.delay.Stop();
	//				ev_BotTutorial.Advance(500);
	//			}
	//			break;

	//		case 46:
	//			Spawn_A_Jerry(LEFT, 6, SPWN_DLAY); // spawn Jerrry!
	//			ev_BotTutorial.Advance(400);
	//			break;

	//		case 47:
	//			Spawn_A_Jerry(LEFT, 8, SPWN_DLAY); // spawn Jerrry!
	//			ev_BotTutorial.Advance(400);
	//			break;

	//		case 48:
	//			Spawn_A_Jerry(LEFT, 6, SPWN_DLAY); // spawn Jerrry!
	//			ev_BotTutorial.Advance(700);
	//			break;

	//		case 49:
	//			Spawn_A_Jerry(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 4, SPWN_DLAY); // spawn Jerrry!
	//			ev_BotTutorial.Advance(150);
	//			break;

	//		case 50:
	//			//Spawn_A_Jerry(LEFT, 3, SPWN_DLAY); // spawn Jerrry!			
	//			ev_BotTutorial.Advance(0);
	//			break;

	//		case 51:
	//			//Spawn_A_Jerry(LEFT, 5, SPWN_DLAY); // spawn Jerrry!
	//			//Spawn_A_Jerry(LEFT, 9, SPWN_DLAY); // spawn Jerrry!
	//			ev_BotTutorial.Advance(0);
	//			break;

	//		case 52:
	//			//Spawn_A_Jerry(LEFT, 7, SPWN_DLAY); // spawn Jerrry!
	//			ev_BotTutorial.Advance(0);
	//			break;

	//		case 53:
	//			//Spawn_A_Jerry(LEFT, 7, SPWN_DLAY); // spawn Jerrry!
	//			ev_BotTutorial.Advance(0);
	//			ev_BotTutorial.delay.Start_Timer(10000, 1, true);
	//			break;

	//		case 54:
	//			if (!jerryTime)
	//			{
	//				blastP1.Get_Ammo_Manager().Deactivate();
	//				ConsoleRender::Add_String(_26, { (map.Get_Box_Limit(RIGHT) + 12),(map.Get_Box_Limit(UP) - 1) }, GRAY, TXT_SPD_DR,true);	// <- AMMO
	//				ConsoleRender::Add_String(_22, Boss_Txt_Crd(_22), gBossClr, TXT_SPD_ER, true);
	//				ConsoleRender::Add_String(_23, Boss_Txt_Crd(_23, 1), gBossClr, TXT_SPD_ER, true);
	//				ConsoleRender::Add_String(_24, Boss_Txt_Crd(_24, 2), gBossClr, TXT_SPD_ER, true);
	//				ConsoleRender::Add_String(_15_1, { map.Get_Box_Limit(RIGHT) - Half_String(_15) , map.Get_Box_Limit(UP) - 3 }, GRAY, TXT_SPD_ER, true);
	//				ConsoleRender::Add_String(_25, { map.Get_Box_Limit(RIGHT) + 4 , linkGrid->link[0][linkGrid->Get_Rows() / 2].Get_XY().y - 2 }, WHITE, TXT_SPD_ER, true);	// lols
	//				ListsOfChainToModify::Annihilate_All_Links(); // Efface tout les Murs et Les Links				
	//				P1.Set_Hp(3);
	//				ev_BotTutorial.delay.Stop();
	//				ev_BotTutorial.Advance(700);
	//			}
	//			break;



	//		case 55:
	//			ConsoleRender::Add_String(_28, Boss_Txt_Crd(_28), gBossClr, TXT_SPD_DR);
	//			ev_BotTutorial.Advance(375);
	//			break;

	//		case 56:
	//			ConsoleRender::Add_String(_29, Boss_Txt_Crd(_29,1 ), gBossClr, TXT_SPD_DR);
	//			ev_BotTutorial.Advance(250);
	//			break;

	//		case 57:
	//			Free_Das_Player();
	//			ConsoleRender::Add_String(_28, Boss_Txt_Crd(_28), gBossClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_29, Boss_Txt_Crd(_29, 1), gBossClr, TXT_SPD_ER, true);
	//			ev_BotTutorial.Advance(1000);
	//			break;

	//		case 58:
	//			P1.Dr_Player();
	//			blastP1.Get_Ammo_Manager().Set_Ammo(100);
	//			ConsoleRender::Add_String(_30, { Boss_Txt_X() - 10, Boss_Txt_Y()}, gBossClr, 0);
	//			ev_BotTutorial.Advance(550);
	//			break;

	//		case 59:
	//			ConsoleRender::Add_String(_31, { Boss_Txt_X() - 4,Boss_Txt_Y() }, gBossClr, 0);
	//			ev_BotTutorial.Advance(500);
	//			break;
	//			
	//		case 60:
	//			stepToSendBack = 57;	// si le joueur fail ce test, il sera send back icitte
	//			MsgQueue::Register(ENABLE_BLAST);	// réactive le blast
	//			Temporary_Bot_Speed_Switch(2000);	// vitesse de déplacement 
	//			Ev_Ultimate_Test();
	//			ConsoleRender::Add_String(_32, { Boss_Txt_X() + 7 ,Boss_Txt_Y() }, gBossClr, 0);
	//			ev_BotTutorial.Advance(400);
	//			break;


	//		case 61:
	//			ConsoleRender::Add_String(TXT_CONST.DOTDOTDOT, Boss_Txt_Crd(TXT_CONST.DOTDOTDOT, 2), gBossClr, TXT_SPD_DR / 2);
	//			ev_BotTutorial.Advance(320);
	//			break;

	//		case 62:
	//			ConsoleRender::Add_String(_30, { Boss_Txt_X() - 10, Boss_Txt_Y() }, gBossClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_31, { Boss_Txt_X() - 4,Boss_Txt_Y() }, gBossClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_32, { Boss_Txt_X() + 7 ,Boss_Txt_Y() }, gBossClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(TXT_CONST.DOTDOTDOT, Boss_Txt_Crd(TXT_CONST.DOTDOTDOT, 2), gBossClr, TXT_SPD_ER, true);
	//			ev_BotTutorial.Advance(1000);
	//			break;

	//		case 63:
	//			ConsoleRender::Add_String(_33, Boss_Txt_Crd(_33), gBossClr, TXT_SPD_DR);
	//			ev_BotTutorial.Advance(900);
	//			break;

	//		case 64:
	//			ConsoleRender::Add_String(_34, Jerry_Txt_Crd(_34), gJerClr, TXT_SPD_DR);
	//			ev_BotTutorial.Advance(600);
	//			break;

	//		case 65:
	//			ConsoleRender::Add_String(_35, Boss_Txt_Crd(_35, 2), gBossClr, TXT_SPD_DR);
	//			ev_BotTutorial.Advance(400);
	//			break;

	//		case 66:
	//			ConsoleRender::Add_String(_36, Jerry_Txt_Crd(_36, 1), gJerClr, TXT_SPD_DR);
	//			ev_BotTutorial.Advance(360);
	//			break;

	//		case 67:
	//			ConsoleRender::Add_String(_37, Jerry_Txt_Crd(_37, 2), gJerClr, TXT_SPD_DR - 2);
	//			ConsoleRender::Add_String(_33, Boss_Txt_Crd(_33), gBossClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_34, Jerry_Txt_Crd(_34), gJerClr, TXT_SPD_ER, true);				
	//			ConsoleRender::Add_String(_35, Boss_Txt_Crd(_35, 2), gBossClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_36, Jerry_Txt_Crd(_36, 1), gJerClr, TXT_SPD_ER, true);
	//			ev_BotTutorial.Advance(400);
	//			break;

	//		case 68:
	//			ConsoleRender::Add_String(_38, Jerry_Txt_Crd(_38, 3), gJerClr, TXT_SPD_DR);
	//			ev_BotTutorial.Advance(240);
	//			break;

	//		case 69:
	//			ConsoleRender::Add_String(_39, Boss_Txt_Crd(_39, 1), gBossClr, TXT_SPD_DR);
	//			ev_BotTutorial.Advance(300);
	//			break;

	//		case 70:
	//			ConsoleRender::Add_String(_39_1, Boss_Txt_Crd(_39_1, 2), gBossClr, TXT_SPD_DR);
	//			ev_BotTutorial.Advance(350);
	//			break;

	//		case 71:
	//			ConsoleRender::Add_String(_40, Jerry_Txt_Crd(_40), gJerClr, TXT_SPD_DR - 2);
	//			ConsoleRender::Add_String(_36, Jerry_Txt_Crd(_36, 1), gJerClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_37, Jerry_Txt_Crd(_37, 2), gJerClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_38, Jerry_Txt_Crd(_38, 3), gJerClr, TXT_SPD_ER, true);
	//			ev_BotTutorial.Advance(190);
	//			break;
	//		
	//		case 72:
	//			ConsoleRender::Add_String(_39, Boss_Txt_Crd(_39, 1), gBossClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_39_1, Boss_Txt_Crd(_39_1, 2), gBossClr, 0, true);
	//			ConsoleRender::Add_String(_41, Boss_Txt_Crd(_41, 2), gBossClr, TXT_SPD_ER);
	//			ev_BotTutorial.Advance(500);
	//			break;

	//		case 73:
	//			ConsoleRender::Add_String(_42, Jerry_Txt_Crd(_42, 2), gJerClr, TXT_SPD_DR - 1);
	//			ev_BotTutorial.Advance(400);
	//			break;

	//		case 74:
	//			ConsoleRender::Add_String(_43, Boss_Txt_Crd(_43), gBossClr, TXT_SPD_FAST);
	//			ConsoleRender::Add_String(_40, Jerry_Txt_Crd(_40), gJerClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_41, Boss_Txt_Crd(_41, 2), gBossClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_42, Jerry_Txt_Crd(_42, 2), gJerClr, TXT_SPD_ER, true);
	//			ev_BotTutorial.Advance(400);
	//			break;

	//		case 75:
	//			ConsoleRender::Add_String(_43_1, Boss_Txt_Crd(_43_1, 1), gBossClr, TXT_SPD_FAST);			
	//			ev_BotTutorial.Advance(800);
	//			break;

	//		case 76:
	//			//ConsoleRender::Add_String(_41, Boss_Txt_Crd(_41, 2), gBossClr, TXT_SPD_ER, true);
	//			ev_BotTutorial.Advance(0);
	//			break;

	//		case 77:

	//			ConsoleRender::Add_String(_44, Jerry_Txt_Crd(_44, 1), gJerClr, TXT_SPD_DR);
	//			ev_BotTutorial.Advance(800);
	//			break;

	//		case 78:
	//			ConsoleRender::Add_String(_45, Boss_Txt_Crd(_45, 2), gBossClr, TXT_SPD_DR);
	//			ev_BotTutorial.Advance(500);
	//			break;

	//		case 79:
	//			ConsoleRender::Add_String(_44, Jerry_Txt_Crd(_44, 1), gJerClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_46, Boss_Txt_Crd(_46, 3), gBossClr, TXT_SPD_DR - 3);
	//			ev_BotTutorial.Advance(300);
	//			break;

	//		case 80:
	//			ConsoleRender::Add_String(_47, Jerry_Txt_Crd(_47, 2), gJerClr, TXT_SPD_DR);
	//			ev_BotTutorial.Advance(400);
	//			break;

	//		case 81:	
	//			ConsoleRender::Add_String(_43, Boss_Txt_Crd(_43), gBossClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_43_1, Boss_Txt_Crd(_43_1, 1), gBossClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_45, Boss_Txt_Crd(_45, 2), gBossClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_46, Boss_Txt_Crd(_46, 3), gBossClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_47, Jerry_Txt_Crd(_47, 2), gJerClr, TXT_SPD_ER, true);
	//			ev_BotTutorial.Advance(1000);
	//			break;
	//		
	//		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//		case 82:// V2
	//		ConsoleRender::Add_String(_48, Boss_Txt_Crd(_48), gBossClr, TXT_SPD_FAST);
	//		ev_BotTutorial.Advance(400);
	//		break;

	//		case 83:
	//		ConsoleRender::Add_String(_49, Jerry_Txt_Crd(_49), gJerClr, TXT_SPD_DR);
	//		ev_BotTutorial.Advance(1000);
	//		break;

	//		case 84:
	//		ConsoleRender::Add_String(_50, Boss_Txt_Crd(_50, 1), gBossClr, TXT_SPD_DR);
	//		ev_BotTutorial.Advance(700);
	//		break;

	//		case 85:
	//		ConsoleRender::Add_String(_51, Jerry_Txt_Crd(_51, 1), gJerClr, TXT_SPD_DR);
	//		ev_BotTutorial.Advance(600);
	//		break;

	//		case 86:
	//		ConsoleRender::Add_String(_53, Boss_Txt_Crd(_53, 2), gBossClr, TXT_SPD_DR);
	//		ev_BotTutorial.Advance(600);
	//		break;

	//		case 87:
	//		//ConsoleRender::Add_String(_54, Jerry_Txt_Crd(_54, 2), gJerClr, 450);
	//		ev_BotTutorial.Advance(0);
	//		break;

	//		case 88:
	//			ConsoleRender::Add_String(_48, Boss_Txt_Crd(_48), gBossClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_49, Jerry_Txt_Crd(_49), gJerClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_50, Boss_Txt_Crd(_50, 1), gBossClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_51, Jerry_Txt_Crd(_51, 1), gJerClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_53, Boss_Txt_Crd(_53, 2), gBossClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_54, Jerry_Txt_Crd(_54, 2), gJerClr, TXT_SPD_DR - 5);
	//			ev_BotTutorial.Advance(500);
	//			break;

	//		case 89:
	//			ConsoleRender::Add_String(_55, Boss_Txt_Crd(_55), gBossClr, TXT_SPD_FAST);
	//			ev_BotTutorial.Advance(600);
	//			break;
	//			
	//		case 90:
	//			ConsoleRender::Add_String(_55_1, Boss_Txt_Crd(_55_1, 1), gBossClr, TXT_SPD_FAST);
	//			ConsoleRender::Add_String(_56, Boss_Txt_Crd(_56, 2), gBossClr, TXT_SPD_DR - 4);
	//			ev_BotTutorial.Advance(400);
	//			break;
	//			

	//		case 91:
	//			ConsoleRender::Add_String(_55, Boss_Txt_Crd(_55), gBossClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_54, Jerry_Txt_Crd(_54, 2), gJerClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_55_1, Boss_Txt_Crd(_55_1, 1), gBossClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_56, Boss_Txt_Crd(_56, 2), gBossClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_57, Jerry_Txt_Crd(_57), gJerClr, TXT_SPD_DR - 3);
	//			ev_BotTutorial.Advance(450);
	//			break;

	//		case 92:
	//			ConsoleRender::Add_String(_58, Boss_Txt_Crd(_58), gBossClr, TXT_SPD_FAST);
	//			ev_BotTutorial.Advance(600);
	//			break;


	//		case 93:
	//			ConsoleRender::Add_String(_57, Jerry_Txt_Crd(_57), gJerClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_58, Boss_Txt_Crd(_58), gBossClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_59, Jerry_Txt_Crd(_59, 1), gJerClr, TXT_SPD_DR - 3);
	//			ev_BotTutorial.Advance(350);
	//			break;

	//		case 94:
	//			ConsoleRender::Add_String(_60, Jerry_Txt_Crd(_60, 2), gJerClr, TXT_SPD_DR - 3);
	//			ev_BotTutorial.Advance(510);
	//			break;

	//		case 95:
	//			ConsoleRender::Add_String(_61, Boss_Txt_Crd(_61), gBossClr, TXT_SPD_DR);
	//			ev_BotTutorial.Advance(400);
	//			break;

	//		case 96:
	//			ConsoleRender::Add_String(_62, Jerry_Txt_Crd(_62), gJerClr, TXT_SPD_DR -7);
	//			ConsoleRender::Add_String(_59, Jerry_Txt_Crd(_59, 1), gJerClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_60, Jerry_Txt_Crd(_60, 2), gJerClr, TXT_SPD_ER, true);
	//			ev_BotTutorial.Advance(250);
	//			break;


	//		case 97:
	//			ConsoleRender::Add_String(_61, Boss_Txt_Crd(_61), gBossClr, 0, true);
	//			ConsoleRender::Add_String(_62_1, { Jerry_Txt_X() + (int)_62.size() / 2, Jerry_Txt_Y() }, gJerClr);
	//			ev_BotTutorial.Advance(1200);
	//			break;

	//		case 98:
	//			ConsoleRender::Add_String(_63, Boss_Txt_Crd(_63), gBossClr, TXT_SPD_FAST);
	//			ev_BotTutorial.Advance(300);
	//			break;

	//		case 99:
	//			ConsoleRender::Add_String(_62, Jerry_Txt_Crd(_62), gJerClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_62_1, { Jerry_Txt_X() + (int)_62.size() / 2, Jerry_Txt_Y() }, gJerClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_64, Boss_Txt_Crd(_64, 1), gBossClr, TXT_SPD_DR);
	//			ev_BotTutorial.Advance(350);
	//			break;

	//		case 100:
	//			ConsoleRender::Add_String(_63, Boss_Txt_Crd(_63), gBossClr, 0, true);
	//			ConsoleRender::Add_String(_64, Boss_Txt_Crd(_64, 1), gBossClr, 0, true);
	//			ev_BotTutorial.Advance(800);
	//			break;

	//		case 101:
	//			ConsoleRender::Add_String(_65, Boss_Txt_Crd(_65, 1), gBossClr, TXT_SPD_DR);
	//			ev_BotTutorial.Advance(400);
	//			break;

	//		case 102:
	//			ConsoleRender::Add_String(_66, Boss_Txt_Crd(_66, 2), gBossClr, TXT_SPD_DR);
	//			ev_BotTutorial.Advance(400);
	//			break;

	//		case 103:
	//			ConsoleRender::Add_String(_67, Boss_Txt_Crd(_67, 3), gBossClr, TXT_SPD_DR);
	//			ev_BotTutorial.Advance(400);
	//			break;

	//		case 104:
	//			ConsoleRender::Add_String(TXT_CONST.DOTDOTDOT, Boss_Txt_Crd(TXT_CONST.DOTDOTDOT, 4), gBossClr, TXT_SPD_DR  / 3);
	//			ev_BotTutorial.Advance(400);
	//			break;

	//		case 105:
	//			ConsoleRender::Add_String(_68, Boss_Txt_Crd(_68, 5), gBossClr, TXT_SPD_DR);
	//			ev_BotTutorial.Advance(300);
	//			break;

	//		case 106:
	//			ConsoleRender::Add_String(_64, Boss_Txt_Crd(_64), gBossClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_65, Boss_Txt_Crd(_65, 1), gBossClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_66, Boss_Txt_Crd(_66, 2), gBossClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_67, Boss_Txt_Crd(_67, 3), gBossClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(TXT_CONST.DOTDOTDOT, Boss_Txt_Crd(TXT_CONST.DOTDOTDOT, 4), gBossClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_68, Boss_Txt_Crd(_68, 5), gBossClr, TXT_SPD_ER, true);
	//			ev_BotTutorial.Advance(300);
	//			break;

	//		case 107:
	//			ConsoleRender::Add_String(_69, Boss_Txt_Crd(_69), gBossClr, TXT_SPD_FAST);
	//			ev_BotTutorial.Advance(800);
	//			break;

	//		case 108:
	//			ConsoleRender::Add_String(_70, Jerry_Txt_Crd(_70), gJerClr, TXT_SPD_FAST);
	//			ev_BotTutorial.Advance(700);
	//			break;

	//		case 109:
	//			ConsoleRender::Add_String(_71, Boss_Txt_Crd(_71, 2), gBossClr, TXT_SPD_FAST);
	//			ev_BotTutorial.Advance(700);
	//			break;

	//		case 110:
	//			ConsoleRender::Add_String(_72, { Jerry_Txt_X() - 5, Jerry_Txt_Y(3) }, gJerClr, TXT_SPD_DR / 10);
	//			ev_BotTutorial.Advance(300);
	//			break;

	//		case 111:
	//			ConsoleRender::Add_String(_73, { Jerry_Txt_X() + 1, Jerry_Txt_Y(3) }, gJerClr, TXT_SPD_DR);
	//			ev_BotTutorial.Advance(2000);
	//			break;

	//		case 112:
	//			ConsoleRender::Add_String(_74, Boss_Txt_Crd(_74, 5), gBossClr);
	//			ev_BotTutorial.Advance(0);	// fait juste wait here. Tout sera effacé par Finish_Ultimate_Test()
	//			ev_BotTutorial.delay.Start_Timer(10000, 1, true);
	//			break;

	//		case 113:			
	//			break;

	//		case 114:
	//			P1.Set_Hp(3);
	//			Start_Ev_Dr_Heart(3);
	//			ConsoleRender::Add_String(_75, Boss_Txt_Crd(_75 + _76), gBossClr, TXT_SPD_DR - 2);
	//			ev_BotTutorial.Advance(350);	
	//			break;

	//		case 115:
	//			Erase_All_Jerry_Txt();
	//			ConsoleRender::Add_String(_76, { Boss_Txt_X() - 3, Boss_Txt_Y() }, gBossClr, TXT_SPD_DR - 1);
	//			ev_BotTutorial.Advance(500);
	//			break;

	//		case 116:
	//			ConsoleRender::Add_String(_75 + _76, Boss_Txt_Crd(_75 + _76), gBossClr, TXT_SPD_ER, true);
	//			ev_BotTutorial.Advance(1000);
	//			break;

	//		case 117:
	//			ConsoleRender::Add_String(_77, Boss_Txt_Crd(_77), gBossClr, TXT_SPD_DR );
	//			ev_BotTutorial.Advance(420);
	//			break;

	//		case 118:
	//			ConsoleRender::Add_String(_78, Boss_Txt_Crd(_78, 2), gBossClr, TXT_SPD_DR);
	//			//ConsoleRender::Add_String(_79, Jerry_Txt_Crd(_79), gJerClr, 350);
	//			ev_BotTutorial.Advance(420);
	//			break;

	//		case 119:
	//			ConsoleRender::Add_String(_77, Boss_Txt_Crd(_77), gBossClr, 0, true);
	//			ConsoleRender::Add_String(_78, Boss_Txt_Crd(_78, 2), gBossClr, TXT_SPD_ER, true);
	//			//ConsoleRender::Add_String(_79, Jerry_Txt_Crd(_79), gJerClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(TXT_CONST.DOTDOTDOT, Boss_Txt_Crd(TXT_CONST.DOTDOTDOT), gBossClr, TXT_SPD_DR / 4);
	//			ev_BotTutorial.Advance(320);
	//			break;

	//		case 120:
	//			ConsoleRender::Add_String(TXT_CONST.DOTDOTDOT, Boss_Txt_Crd(TXT_CONST.DOTDOTDOT), gBossClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_80, Boss_Txt_Crd(_80, 2), gBossClr, TXT_SPD_ER);
	//			ev_BotTutorial.Advance(400);
	//			break;

	//		case 121:
	//			ConsoleRender::Add_String(_81, Boss_Txt_Crd(_81, 3), gBossClr, TXT_SPD_DR);
	//			ev_BotTutorial.Advance(320);
	//			break;

	//		case 122:				
	//			ConsoleRender::Add_String(_80, Boss_Txt_Crd(_80, 2), gBossClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_81, Boss_Txt_Crd(_81, 3), gBossClr, TXT_SPD_ER, true);
	//			ev_BotTutorial.Advance(1000);
	//			break;

	//		case 123:
	//			ConsoleRender::Add_String(_82, Boss_Txt_Crd(_82), gBossClr, TXT_SPD_DR);
	//			ev_BotTutorial.Advance(700);					 
	//			break;

	//		case 124:
	//			ConsoleRender::Add_String(_83, Boss_Txt_Crd(_83, 1), gBossClr, TXT_SPD_DR);
	//			ev_BotTutorial.Advance(450);
	//			break;

	//		case 125:
	//			//ConsoleRender::Add_String(_84, Boss_Txt_Crd(_84, 3), gBossClr, 250);
	//			ev_BotTutorial.Advance(0);
	//			break;

	//		case 126:
	//			ConsoleRender::Add_String(_85, Boss_Txt_Crd(_85, 4), gBossClr, TXT_SPD_DR / 2);
	//			ev_BotTutorial.Advance(390);
	//			break;
	//		
	//		case 127:
	//			ConsoleRender::Add_String(_82, Boss_Txt_Crd(_82),	 gBossClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_83, Boss_Txt_Crd(_83, 1), gBossClr, TXT_SPD_ER, true);
	//			//ConsoleRender::Add_String(_84, Boss_Txt_Crd(_84, 3), gBossClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(_85, Boss_Txt_Crd(_85, 4), gBossClr, TXT_SPD_ER, true);
	//			ev_BotTutorial.Advance(1000);
	//			break;

	//		case 128:
	//			ConsoleRender::Add_String(_86, Boss_Txt_Crd(_86, 3), gBossClr, TXT_SPD_ER);
	//			ev_BotTutorial.Advance(700);
	//			break;

	//		case 129:
	//			ConsoleRender::Add_String(_86, Boss_Txt_Crd(_86, 3), gBossClr, TXT_SPD_ER, true);
	//			ev_BotTutorial.Advance(500);
	//			break;
	//		
	//		case 130:
	//			ConsoleRender::Add_String(jer_5, Jerry_Txt_Crd(jer_5), gJerClr, TXT_SPD_DR);
	//			ev_BotTutorial.Advance(350);
	//			break;

	//		case 131:
	//			ConsoleRender::Add_String(jer_6, Jerry_Txt_Crd(jer_6, 2), gJerClr, TXT_SPD_DR + 2);
	//			ev_BotTutorial.Advance(250);
	//			break;

	//		case 132:
	//			ev_BotTutorial.Advance(1000);
	//			break;

	//		case 133:
	//			ConsoleRender::Add_String(jer_5, Jerry_Txt_Crd(jer_5), gJerClr, 0, true);
	//			ConsoleRender::Add_String(jer_6, Jerry_Txt_Crd(jer_6, 2), gJerClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(jer_7, Jerry_Txt_Crd(jer_7), gJerClr, TXT_SPD_DR);
	//			ev_BotTutorial.Advance(500);
	//			break;

	//		case 134:
	//			ConsoleRender::Add_String(jer_8, Jerry_Txt_Crd(jer_8, 1), gJerClr, TXT_SPD_FAST);
	//			ev_BotTutorial.Advance(400);
	//			break;

	//		case 135:
	//			ConsoleRender::Add_String(jer_9, Jerry_Txt_Crd(jer_9, 2), gJerClr, TXT_SPD_FAST);
	//			ev_BotTutorial.Advance(500);
	//			break;

	//		case 136:
	//			ConsoleRender::Add_String(jer_10, Jerry_Txt_Crd(jer_10, 3), gJerClr, TXT_SPD_FAST);
	//			ev_BotTutorial.Advance(600);
	//			break;

	//		case 137:
	//			ConsoleRender::Add_String(jer_7, Jerry_Txt_Crd(jer_7), gJerClr, 0, true);
	//			ConsoleRender::Add_String(jer_8, Jerry_Txt_Crd(jer_8, 1), gJerClr, 0, true);
	//			ConsoleRender::Add_String(jer_9, Jerry_Txt_Crd(jer_9, 2), gJerClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(jer_10, Jerry_Txt_Crd(jer_10, 3), gJerClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(jer_11, Jerry_Txt_Crd(jer_11), gJerClr, TXT_SPD_FAST);
	//			ev_BotTutorial.Advance(800);
	//			break;

	//		case 138:
	//			MsgQueue::Register(FREE_PLAYER);
	//			ConsoleRender::Add_String(jer_12, Jerry_Txt_Crd(jer_12, 1), gJerClr, TXT_SPD_FAST);
	//			ev_BotTutorial.Advance(1000);
	//			break;

	//		case 139:
	//			ConsoleRender::Add_String(jer_13, Jerry_Txt_Crd(jer_13, 3), gJerClr, TXT_SPD_FAST);
	//			ListsOfChainToModify::Annihilate_All_Links(); // Efface tout les Murs et Les Links
	//			MsgQueue::Register(DISABLE_BLAST);
	//			ev_BotTutorial.Advance(500);
	//			break;

	//		case 140:				
	//			ConsoleRender::Add_String(jer_12, Jerry_Txt_Crd(jer_12), gJerClr, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(jer_13, Jerry_Txt_Crd(jer_13, 2), gJerClr, TXT_SPD_ER, true);

	//			// Coord tu titre du choix
	//			XY.x = Find_Ctr_X((int)rate.size() / 2) - 5;
	//			XY.y = linkGrid->link[6][4].Get_XY().y + 4;
	//			ConsoleRender::Add_String(rate, XY, GRAY, TXT_SPD_DR);
	//			ConsoleRender::Add_String(rate_1, { XY.x - 5,XY.y + 1 }, GRAY, TXT_SPD_DR);
	//			
	//			// Début d'un choix pour le joueur
	//			choiceCrd = { 0, 8 };

	//			//v1
	//			//for (int i = 0; i < 10; i++)		// Le joueur doit "Rater" la performance de Jerry!
	//			//{
	//			//	
	//			//	if (i == 0)
	//			//	{
	//			//		ChoiceTime::Add_Choice(recom[i], recomSub[0], choiceCrd);					
	//			//		choiceCrd.c++;
	//			//	}
	//			//	else
	//			//		if (i == 9) // le dixième choix
	//			//			ChoiceTime::Add_Choice(recom[i], recomSub[1], choiceCrd);
	//			//		else
	//			//			ChoiceTime::Add_Choice(recom[i], TXT_CONST.SPACE_STRING, choiceCrd); // nada

	//			//	if (i == 8) // Pour le dixième choix
	//			//		choiceCrd.c+= 2;
	//	
	//			//	choiceCrd.c++;
	//			//}
	//			choiceCrd = { 1, 8 };

	//			for (int i = 0; i < 12; i++)		// Le joueur doit "Rater" la performance de Jerry!
	//			{
	//				switch (i)
	//				{			
	//				case 0:  choiceCrd = { 1, 8 }; break;
	//				case 1:  choiceCrd = { 10, 8 }; break;
	//				case 2:  choiceCrd = { 4, 12 }; break;
	//				case 3:  choiceCrd = { 7, 12 }; break;
	//				case 4:  choiceCrd = { 12, 10 }; break;
	//				case 5:  choiceCrd = { 5, 9 }; break;
	//				case 6:  choiceCrd = { 9, 9 }; break;
	//				case 7:  choiceCrd = { 0, 14 }; break;
	//				case 8:  choiceCrd = { 6, 11 }; break;
	//				case 9: choiceCrd = { 11, 13 }; break;
	//				case 10: choiceCrd = { 2, 10 }; break;
	//				case 11: choiceCrd = { 10, 11 }; break;
	//				}
	//				ChoiceTime::Add_Choice(recom[i], recomSub2[i], choiceCrd);

	//			}

	//			ev_BotTutorial.Advance(0);
	//			ev_BotTutorial.delay.Start_Timer(2000, 1, true);	// infinite check here
	//			break;

	//		case 141:
	//			if (!ChoiceTime::Is_Choice_Time())
	//			{
	//				ConsoleRender::Add_String(rate, XY, GRAY, TXT_SPD_ER, true);
	//				ConsoleRender::Add_String(rate_1, { XY.x - 5,XY.y + 1 }, GRAY, TXT_SPD_ER, true);
	//				ConsoleRender::Add_String(jer_11, Jerry_Txt_Crd(jer_11), gJerClr, TXT_SPD_ER, true);
	//				ConsoleRender::Add_String(jer_12, Jerry_Txt_Crd(jer_12, 1), gJerClr, TXT_SPD_ER, true);
	//				ConsoleRender::Add_String(jer_13, Jerry_Txt_Crd(jer_13, 3), gJerClr, TXT_SPD_ER, true);
	//				ev_BotTutorial.delay.Stop();
	//				ev_BotTutorial.Advance(500);
	//			}
	//			break;

	//		case 142:
	//			choiceMade = ChoiceTime::Get_Choice_Made();
	//			practiceTime = false;

	//			for (int i = 0; i < 12; i++)
	//			{
	//				if (choiceMade == recom[i])
	//				{
	//					// 0-5 7-8
	//					// 6 9 10
	//					// 11 delic
	//					// 12 best
	//					if (i == 0)
	//					{
	//						jerResponse = jerrAnswer[0];
	//						jerFeelings = answer[0];
	//						practiceTime = true;
	//					}
	//					else
	//						if (i == 5 || i == 8 || i == 9)
	//						{
	//							jerResponse = jerrAnswer[2];
	//							jerFeelings = answer[2];
	//						}
	//						else
	//							if (i == 10)
	//							{
	//								jerResponse = jerrAnswer[3];
	//								jerFeelings = answer[3];
	//							}
	//							else
	//								if (i == 11)
	//								{
	//									jerResponse = jerrAnswer[4];
	//									jerFeelings = answer[4];
	//									practiceTime = true;
	//								}
	//								else
	//								{
	//									jerResponse = jerrAnswer[1];
	//									jerFeelings = answer[1];
	//									practiceTime = true;
	//								}

	//					break;
	//				}
	//			}
	//			ev_BotTutorial.Advance(3000);
	//			break;
	//		
	//		case 143:
	//			ConsoleRender::Add_String(jerResponse, Jerry_Txt_Crd(jerResponse), gJerClr, TXT_SPD_DR );
	//			ev_BotTutorial.Advance(400);
	//			break;

	//		case 144:
	//			ConsoleRender::Add_String(jerFeelings, Up_Txt_2(jerFeelings), GRAY, TXT_SPD_FAST );
	//			ev_BotTutorial.Advance(150);
	//			break;

	//		case 145:
	//			ConsoleRender::Add_String(jerFeelings, Up_Txt_2(jerFeelings), GRAY, TXT_SPD_ER, true);
	//			ConsoleRender::Add_String(jerResponse, Jerry_Txt_Crd(jerResponse), GRAY, TXT_SPD_ER, true);

	//			stepToSendBack = 138;
	//			P1.Set_Hp(3); Just_Dr_Heart(); Press_X_To_Proceed(1);
	//			
	//			if (!practiceTime)	// Jerry Might Not want to help you
	//			{
	//				//P1.Set_Hp(2000); // testing okay?
	//				jerryTime = true;
	//				Make_It_Vertical_Only();
	//				Set_Jerry(NONE, -1, prevMovSpeed);	// Tu peux pas mettre un boxisde random et une crd de spawn specific
	//				Ev_Spawn_Jerry();

	//				MsgQueue::Register(ENABLE_BLAST);
	//			}


	//			ev_BotTutorial.Advance(400);
	//			ev_BotTutorial.delay.Start_Timer(10000, 1, true);	// l'event doit rester actif si le joueur die.
	//			break;


	//			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//			// Cet Event Doit être arrêté manuellement!

	//		}


	//	}
	//}
}
	

// __/\\\\\\\\\\\\\\\__/\\\________/\\\________/\\\\\\\\\__/\\\________/\\\_______________/\\\____        
//  _\/\\\///////////__\/\\\_______\/\\\_____/\\\////////__\/\\\_____/\\\//______________/\\\\\\\__       
//   _\/\\\_____________\/\\\_______\/\\\___/\\\/___________\/\\\__/\\\//________________/\\\\\\\\\_      
//    _\/\\\\\\\\\\\_____\/\\\_______\/\\\__/\\\_____________\/\\\\\\//\\\_______________\//\\\\\\\__     
//     _\/\\\///////______\/\\\_______\/\\\_\/\\\_____________\/\\\//_\//\\\_______________\//\\\\\___    
//      _\/\\\_____________\/\\\_______\/\\\_\//\\\____________\/\\\____\//\\\_______________\//\\\____   
//       _\/\\\_____________\//\\\______/\\\___\///\\\__________\/\\\_____\//\\\_______________\///_____  
//        _\/\\\______________\///\\\\\\\\\/______\////\\\\\\\\\_\/\\\______\//\\\_______________/\\\____ 
//         _\///_________________\/////////___________\/////////__\///________\///_______________\///_____
                                                                                                       
