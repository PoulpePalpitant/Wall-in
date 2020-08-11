

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
#include "../../../bots/botlist.h"
#include "../../../structure_manager/modify_chain.h"
#include "../../../events/global_events/ev_countdown.h"
#include "../../../events/global_events/feedback/ev_glitch_screen.h"
#include "../msg_events/ev_stop_Jerry_1.h"
#include "../../../spawns/ev_spawn_Jerry.h"
#include "../events/ev_build_start_walls.h"
#include "ev_ultimate_test.h"
#include "../../../events/global_events/ev_to_proceed.h"

static Event ev_BotTutorial(Ev_Bot_Tutorial, 150);

/* Dis gonna be a long one:
	
	Tutorial qui montre au joueur comment jouer. 
	Choses � montrer:

	- Les Bots, leurs d�placement et leur destination
	- Tirer, comment stacker perpendiculairement
	- D�tuire les bots, en utilisant la m�thode de tirer, ne peut pas tirer directement dessus(en fait techniquement oui)
	- Tu dois survivre le niveau, qui � une fin

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
	-Montrer comment les bots bougent et la limitent qu'ils ne doivent pas franchir		/ lash la border
	Les "tirs" cr�er des Walls qui serveent � les arr�ter

	#2 Deeper
	Les bots peuvent venir de tout les directions	/ gauche et droite
	Il faut constamment construire des walls, sinon tu risque d'�tre overwhelm(instaurer climat d'urgence)	/ Avec le countdown

	#3 deeper
	Les walls peuvent se stacker dans les 4 directions	/ Le boute avec les smaller walls
	Pour stopper les bots qui passent au milieu, mieux vaut stacker perpendiculairement  / illustr�, mais pas conditionn�
	Faire des longues chaine des walls n'est pas une bonne strat�gie, car les bots d�truisent tout les walls qui d�pendent de la cha�ne / dit au joueur :(
	mieux vaut ne pas tirer de loin, car le blast est en cooldown tant qu'il n'a pas atteint �a cible, c'est donc plus lent que de tirer de proche / mmmm

	#id�e ta tr�s peu de temps pour arr�ter des bots, et il faut que tu te d�place physiquement pour le faire, et non tirer de loin
	#id�e ta tr�s peu de temps pour arr�ter des bots, et il faut que tu te stack perpendiculairement pour le faire et non spammer
*/



static std::string _10 = "Now Try To Build Some Walls";
static std::string _11 = "Jerry It's Your Turn Now";
static std::string _12 = "You Got This Jerry!";
static std::string _13 = "Okay, Here I Come!";
static std::string _14 = "Ow";
static std::string _15 = "(Don't let Jerry Reach The Border)";
static std::string _16 = "Nice Work! You Stopped Jerry!";
static std::string _17 = "Actually, This Might Have Been";
static std::string _18 = "A Little Bit Too Easy";
static std::string _19 = "Let's Bring The Difficulty Up A Notch";
static std::string _20 = "Nicely done!";
static std::string _21 = "You Are Getting Better By the Seconds!";
static std::string _22 = "Now, A Tip For The Next Step:";
static std::string _23 = "Big Structures Are Easily Breakable";
static std::string _24 = "Try To Build Smaller Walls!";
static std::string _25 = "(<-- Try this)";
static std::string _26 = "Smaller Chain Of Walls";
static std::string _27 = "Are Less Easy To Destroy!";
static std::string _28 = "Good Job, You're Almost Ready To Get To Work";
static std::string _29 = "To Proceed, However, You Must Accomplish Sucessfully...";
static std::string _30 = "THE";
static std::string _31 = "ULTIMATE ";
static std::string _32 = "TEST �";// . . . 
static std::string _33 = "Jerry, What Are You Doing?";
static std::string _34 = "What?";
static std::string _35 = "That Is Not \" THE ULTIMATE TEST � \"?";
static std::string _36 = "Yeah I Know Boss But...";
static std::string _37 = "With All These Positive Feedbacks And...";
static std::string _38 = "I Fell, Like... We Can Do Anything, Right?";
static std::string _39 = "'88', Are You Insane? We Can't Even Stop Them!";
static std::string _39_1 = "The Employee's Gonna Die!";
static std::string _40 = "Yeah, Huh, No? But, I Mean.... Really?";
static std::string _41 = "What The Hell Were You Thinking You Doofus!";
static std::string _42 = "Hey Don't Call Me That!";
static std::string _43 = "I Know I Shouldn't Call You That!";
static std::string _43_1 = "But You Ruined Everything, Damn It!";
static std::string _44 = "But!.... There Is A Change th-";
static std::string _45 = "Now Our Brand New Employee Here";
static std::string _46 = "Is Gonna Die A Horrible Death Because Of You!";
static std::string _47 = "I'm Sorry Boss!";
// v2 
static std::string _48 = "Now How Am I Going To Explain That To HR?";
static std::string _49 = "I Huh... I Don't Know!";
static std::string _50 = "You Don't Know?";
static std::string _51 = "Hehhggg... Yes?";
static std::string _52 = " . . . ?";
static std::string _53 = "Come On Then! Tell Me. ";// Something You Know?
static std::string _54 = "I Huh, Hum, ehh Trees...";
static std::string _55 = "TREES!?";
static std::string _55_1 = "What The Hell Do Trees";
static std::string _56 = "Have Anything To Do With This?";
static std::string _57 = "I-ahhh Am Under A Lot Of Pressure Ok!";
static std::string _58 = "Oh, Really?";
static std::string _59 = "Yes. I Just... If You Hadn't Given Me Such";
static std::string _60 = "Nice Comments On My Performance I W-";
static std::string _61 = "Oh Now It's My Fault If You Were Cocky?";
static std::string _62 = "........................";
static std::string _62_1 = "Kind Of?";
static std::string _63 = "GOD DAMN It Jerry!";
static std::string _64 = "Do You Even Realize How Serious This Is?";
// v1
static std::string _65 = "Now I Have To Ask HR To Send Us Another One!";
static std::string _66= "A Freshly Picked, Packaged and Untrained Employee";
static std::string _67 = "And I'm Gonna Have To Waste Another"; /// ...
static std::string _68 = "15 Minutes Of My Life Explaining Stuff Again";
static std::string _69 = "Do You Feel The Guilt Now?";
static std::string _70 = "Yes, I Do.";
static std::string _71 = "DO YOU!?";
static std::string _72 = "I.....";
static std::string _73 = "No!";
static std::string _74 = "FUCK!!";
static std::string _75 = "Oh. ";
static std::string _76 = "You Made It. ";
static std::string _77 = "Yes We Expected That";
static std::string _78 = "Congratulation! Hah.";
static std::string _79 = "Good Job";
static std::string _80 = "Since You Survived That";
static std::string _81 = "Hum. Well, I Think You Are All Set Then";
static std::string _82 = "I Have To Go, Now. But...";
static std::string _83 = "If You Need More Practice";
static std::string _84 = "If You Want...";
static std::string _85 = "Just Ask...Jerry";
static std::string _86 = "Good Luck!";

static std::string sorry = "I'm Sorry, But I Can't Let You Continue";
static std::string stop = "Until You Stop Mah Boi Jerry";

static std::string jer_1= "How about me?";
static std::string jer_2= "Did I Do Good?";
static std::string jer_3 = "Yes, You Too Did Good Jerry!";
static std::string jer_4 = "(Jerry's Confidence Was Boosted)";
static std::string jer_5 = "Sorry About The Ultimate Test Thing";
static std::string jer_6 = "Still, Did, Did I Do Good?";
static std::string scale = "Like On A scale, How Would You Rate It?";
static std::string rate = "Rate Jerry's Performance";
static std::string choiceMade;
static std::string recom[] = { " 1 ", " 2 ", " 3 ", " 4 ", " 5 ", " 6 ", " 7 ", " 8 ", " 9 ", " 10 " };
static std::string recomSub[] = { "The Actual Worst You Have Ever Seen", " Okay " };
static std::string answer[] =
{ 
	"Jerry Is Feeling Miserable About Himself. He Doesn't Have Any Power To Help You"
	"You Said That Just To Be Mean. Jerry Felt That. Jerry Doesn't Want To Help You Anymore",
	"You Didn't Seem Honest Enough. Jerry Seems Disappointed",
	"Jerry Doesn't Seem Satisfied By Your Answer",
	"Jerry Appreciates Your FeedBack. Even Though You Have Hurt His Feelings", 
	"Jerry Appreciates Your FeedBack. Even Though It was Just A MeaningLess Number",
	"Jerry Appreciates Your FeedBack. Even Though Your Opinion Means Very Little To Him"
};

static std::string tempAnswer;

static int stepToSendBack;	// Si le joueur fail une �tape, il va devoir �tre send back � une �tape pr�c�dante

static bool Retry_If_Fail()
{
	if (!P1.Get_HP())		// Fait restarter la s�quence 
	{
		Ev_Glitch_Screen();
		Stop_Ev_Dr_Stop_Jerry();	// stop l'even de jerrys
		BotList::Destroy_All_Bots();	// clear les bots qui aurait pu rest�
		Restore_Prev_Bot_Speed();	// r�tablit la vitesse pr�c�dante
		Ev_Stop_Spawn_Jerry();		// arr�te cet event, mais si il est actif une fois � la fin

		ev_BotTutorial.delay.Stop();
		ev_BotTutorial.delay.Start_Timer(500);
		ev_BotTutorial.Go_To_X_Step(stepToSendBack);
		return true;
	}
	return false;
}

void Finish_Ultimate_Test()
{
	if (Ultimate_Test_Succeed())	// SUCESS
	{
		Restore_Prev_Bot_Speed();
		Erase_Right_Text();
		ev_BotTutorial.delay.Stop();
		ev_BotTutorial.delay.Start_Timer(0);
		ev_BotTutorial.Go_To_X_Step(114);
	}

}


void Ev_Bot_Tutorial()// Trace un chemin vers une fausse porte de sortie
{
	if (!ev_BotTutorial.Is_Active())
	{
		//Erase_Map_Borders_1(23);	// erase borders
		ev_BotTutorial.Activate();
		ev_BotTutorial.Start(400);
		//ev_BotTutorial.Go_To_X_Step(114);		// now that's a shortcut
		ev_BotTutorial.Go_To_X_Step(129);		// now that's a shortcut
		//ev_BotTutorial.Go_To_X_Step(56);		// now that's a shortcut
		//ev_BotTutorial.Go_To_X_Step(42);		// now that's a shortcut
		//ev_BotTutorial.Go_To_X_Step(14);		// now that's a shortcut
	}
	else	// doin stuff 
	{
		while (ev_BotTutorial.delay.Tick())
		{
			if (jerryTime)
				Retry_If_Fail();	// Si le joueur fail un bout du tutorial, on step back sur des �tapes de l'event

			Finish_Ultimate_Test();	// Cancel la discussion entre les deux personnages 

			static int step; step = ev_BotTutorial.Get_Current_Step();

			switch (step)	// STEP 1 � 20 -> On troll le joueur en faisant d�placer un tit point
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
				MsgQueue::Register(ENABLE_BLAST);	// backup

				ev_BotTutorial.Advance(200);
				break;

			case 15:
				prevMovSPeed = gBotMoveTimer.Get_Speed();	// vitesse de d�placement pr�c�dante
				Spawn_A_Jerry(RIGHT, 1, 20); // spawn Jerrry!
				ConsoleRender::Add_String(_13, Jerry_Txt_Crd(_13), gJerClr, TXT_SPD_DR);
				ev_BotTutorial.Advance(250);
				break;


			case 16:
				ConsoleRender::Add_String(_13, Jerry_Txt_Crd(_13), gJerClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_12, Boss_Txt_Crd(_12, 5), gBossClr, TXT_SPD_DR);

				ev_BotTutorial.Advance(0);
				ev_BotTutorial.delay.Start_Timer(5000,1, true);
				break;

			case 17:
				if (!gAllBotMeta.alive)
				{
					if (P1.Get_HP() == 3)	// Si le joueur � p�ter Jerry
					{
						ConsoleRender::Add_String(_14, Jerry_Txt_Crd(_14, 1), gJerClr, TXT_SPD_DR);	// Jerry � finis d'avancer
						ConsoleRender::Add_String(sorry, Boss_Txt_Crd(sorry, 2), gBossClr, TXT_SPD_ER, true);
						ConsoleRender::Add_String(stop, Boss_Txt_Crd(stop, 3), gBossClr, TXT_SPD_ER, true);
						ConsoleRender::Add_String(_15, { 38 , 4 }, GRAY, TXT_SPD_ER, true);
						ConsoleRender::Add_String(_12, Boss_Txt_Crd(_12, 5), gBossClr, TXT_SPD_ER, true);

						gBotMoveTimer.Start_Timer(prevMovSPeed, 1, true);	// R�tablit la vitesse pr�c�dante
						ev_BotTutorial.delay.Stop();
						ev_BotTutorial.Advance(500);
					}
					else
					{
						ConsoleRender::Add_String(sorry, Boss_Txt_Crd(sorry, 2), gBossClr, TXT_SPD_DR);
						ConsoleRender::Add_String(stop, Boss_Txt_Crd(stop, 3), gBossClr, TXT_SPD_DR);
						ListsOfChainToModify::Annihilate_All_Links(); // Efface tout les Murs et Les Links										
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
				ConsoleRender::Add_String(_15, { 38 , 4 }, GRAY, TXT_SPD_DR);	// r�affichage
				Just_Dr_Arr_Keys();												// r�affichage
				P1.Player_Gains_HP();					// redonne de la vie
				
				ev_BotTutorial.delay.Start_Timer(600);
				ev_BotTutorial.Go_To_X_Step(15);
				break;

			case 18:
				ConsoleRender::Add_String(_14, Jerry_Txt_Crd(_14, 1), gJerClr, TXT_SPD_ER, true);	// Jerry � finis d'avancer
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
				stepToSendBack = 24;	// si le joueur fail ce test, il sera send back � cette �tape
				Set_Jerry_Time(5);
				Ev_Dr_Stop_Jerry();
				Set_CountDown(10);
				Ev_CountDown();	// Countdown
				ListsOfChainToModify::Annihilate_All_Links(); // Efface tout les Murs et Les Links										
				P1.Set_Hp(3); Just_Dr_Heart(); Just_Dr_Arr_Keys();	// r�affichage et redonne de la vie

				MsgQueue::Register(DISABLE_BLAST);		/// Si le joueur tir avant, le blast ne sera pas cancel�
				ev_BotTutorial.Advance(400);
				break;

			case 26:
				ConsoleRender::Add_String(_15, { map.Get_Box_Limit(RIGHT) - (int)_15.length() / 2, 4 }, GRAY, TXT_SPD_DR);	// r�affichage
				Set_Flashy_Border(RIGHT, 11);
				Ev_Flash_Map_Border();	// Fait flasher la border pour signaler au joueur ou va aller Jerry

				ev_BotTutorial.Advance(0);
				ev_BotTutorial.delay.Start_Timer(10000, 1, true);
				break;

			case 27:
 				if (CountDown_Finished())
				{
					MsgQueue::Register(ENABLE_BLAST);	// r�active le blast
					Spawn_A_Jerry(LEFT, 1, 20); // spawn Jerrry!
					
					ev_BotTutorial.delay.Stop();
					ev_BotTutorial.Advance(400);
				}
				break;

			case 28:
				Spawn_A_Jerry(LEFT, 10, 20); // spawn Jerrry!
				ev_BotTutorial.Advance(400);
				break;

			case 29:
				Spawn_A_Jerry(LEFT, 3, 20); // spawn Jerrry!
				ev_BotTutorial.Advance(400);
				break;

			case 30:
				Spawn_A_Jerry(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 1, 20); // spawn Jerrry!
				ev_BotTutorial.Advance(400);
				break;

			case 31:
 				Spawn_A_Jerry(LEFT, 0, 20); // spawn Jerrry!
				ev_BotTutorial.Advance(0);
				ev_BotTutorial.delay.Start_Timer(10000, 1, true);
				break;

			case 32:
				if (!jerryTime)
				{
					ConsoleRender::Add_String(_15, { map.Get_Box_Limit(RIGHT) - (int)_15.length() / 2, 4 }, GRAY, TXT_SPD_ER, true);
					ConsoleRender::Add_String(_20, Boss_Txt_Crd(_20), gBossClr, TXT_SPD_DR);	// // congratz!			
					ev_BotTutorial.delay.Stop();
					ev_BotTutorial.Advance(500);
				}				
				break;

			case 33:
				ConsoleRender::Add_String(_21, Boss_Txt_Crd(_21, 1), gBossClr, TXT_SPD_DR);	// // congratz!				
				ev_BotTutorial.Advance(400);
				break;


			case 34:
				ConsoleRender::Add_String(jer_1, Jerry_Txt_Crd(jer_1), gJerClr, 200); // jerry wants feedback too :(				
				ev_BotTutorial.Advance(600);
				break;

			case 35:
				ConsoleRender::Add_String(jer_2, Jerry_Txt_Crd(jer_2,1), gJerClr, 200);		
				ConsoleRender::Add_String(_20, Boss_Txt_Crd(_20), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_21, Boss_Txt_Crd(_21, 1), gBossClr, TXT_SPD_ER, true);			
				ev_BotTutorial.Advance(400);
				break;

			case 36:
				ConsoleRender::Add_String(jer_3, Boss_Txt_Crd(jer_3), gBossClr, 200);
				ev_BotTutorial.Advance(500);
				break;		
			
			case 37:
				ConsoleRender::Add_String(jer_1, Jerry_Txt_Crd(jer_1), gJerClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(jer_2, Jerry_Txt_Crd(jer_2, 1), gJerClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(jer_4, Jerry_Txt_Crd(jer_4, 2), GRAY, 200); 		
				ev_BotTutorial.Advance(300);
				break;

			case 38:
				ConsoleRender::Add_String(jer_4, Jerry_Txt_Crd(jer_4, 2), gJerClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(jer_3, Boss_Txt_Crd(jer_3), gBossClr, TXT_SPD_ER, true);
				ev_BotTutorial.Advance(1000);
				break;

			case 39:
				ConsoleRender::Add_String(_22, Boss_Txt_Crd(_22), gBossClr, TXT_SPD_DR);				
				ev_BotTutorial.Advance(500);
				break;

			case 40:
				ConsoleRender::Add_String(_23, Boss_Txt_Crd(_23, 1), gBossClr, TXT_SPD_DR);				
				ev_BotTutorial.Advance(500);
				break;


			case 41:
				ConsoleRender::Add_String(_24, Boss_Txt_Crd(_24, 2), gBossClr, TXT_SPD_DR);			
				ev_BotTutorial.Advance(420);
				break;

			case 42:
				ListsOfChainToModify::Annihilate_All_Links(); // Efface tout les Murs et Les Links										
				ConsoleRender::Add_String(_25, { map.Get_Box_Limit(RIGHT)  + 4 , linkGrid->link[0][linkGrid->Get_Rows() / 2].Get_XY().y - 2 }, GRAY, TXT_SPD_DR);	// lols
				Build_Lvl_1_Walls();
				Set_CountDown(10);
				Ev_CountDown();	// Countdown
				ev_BotTutorial.Advance(350);
				break;

			case 43:
				stepToSendBack = 38;	// si le joueur fail ce test, il sera send back icitte
				Set_Jerry_Time(10);
				Ev_Dr_Stop_Jerry();
				P1.Set_Hp(3); Just_Dr_Heart(); Just_Dr_Arr_Keys();	// r�affichage et redonne de la vie	BACKUP
				MsgQueue::Register(DISABLE_BLAST);		/// Si le joueur tir avant, le blast ne sera pas cancel�
				ev_BotTutorial.Advance(400);
				break;						

			case 44:
				ConsoleRender::Add_String(_15, { map.Get_Box_Limit(RIGHT) - (int)_15.length() / 2, 4 }, GRAY, TXT_SPD_DR);	// r�affichage
				Set_Flashy_Border(RIGHT, 11);
				Ev_Flash_Map_Border();	// Fait flasher la border pour signaler au joueur ou va aller Jerry

				ev_BotTutorial.Advance(0);
				ev_BotTutorial.delay.Start_Timer(10000, 1, true);
				break;

			case 45:
				if (CountDown_Finished())
				{
					MsgQueue::Register(ENABLE_BLAST);	// r�active le blast
					Spawn_A_Jerry(LEFT, 3, SPWN_DLAY); // spawn Jerrry!

					ev_BotTutorial.delay.Stop();
					ev_BotTutorial.Advance(500);
				}
				break;

			case 46:
				Spawn_A_Jerry(LEFT, 6, SPWN_DLAY); // spawn Jerrry!
				ev_BotTutorial.Advance(400);
				break;

			case 47:
				Spawn_A_Jerry(LEFT, 8, SPWN_DLAY); // spawn Jerrry!
				ev_BotTutorial.Advance(400);
				break;

			case 48:
				Spawn_A_Jerry(LEFT, 6, SPWN_DLAY); // spawn Jerrry!
				ev_BotTutorial.Advance(700);
				break;

			case 49:
				Spawn_A_Jerry(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 4, SPWN_DLAY); // spawn Jerrry!
				ev_BotTutorial.Advance(150);
				break;

			case 50:
				Spawn_A_Jerry(LEFT, 3, SPWN_DLAY); // spawn Jerrry!			
				ev_BotTutorial.Advance(300);
				break;

			case 51:
				Spawn_A_Jerry(LEFT, 5, SPWN_DLAY); // spawn Jerrry!
				Spawn_A_Jerry(LEFT, 8, SPWN_DLAY); // spawn Jerrry!
				ev_BotTutorial.Advance(1000);
				break;

			case 52:
				Spawn_A_Jerry(LEFT, 7, SPWN_DLAY); // spawn Jerrry!
				ev_BotTutorial.Advance(1000);
				break;

			case 53:
				Spawn_A_Jerry(LEFT, 7, SPWN_DLAY); // spawn Jerrry!
				ev_BotTutorial.Advance(0);
				ev_BotTutorial.delay.Start_Timer(10000, 1, true);

				break;

			case 54:
				if (!jerryTime)
				{
					ConsoleRender::Add_String(_22, Boss_Txt_Crd(_22), gBossClr, TXT_SPD_ER, true);
					ConsoleRender::Add_String(_23, Boss_Txt_Crd(_23, 1), gBossClr, TXT_SPD_ER, true);
					ConsoleRender::Add_String(_24, Boss_Txt_Crd(_24, 2), gBossClr, TXT_SPD_ER, true);
					ConsoleRender::Add_String(_15, { map.Get_Box_Limit(RIGHT) - (int)_15.length() / 2, 4 }, GRAY, TXT_SPD_ER, true);	
					ConsoleRender::Add_String(_25, { map.Get_Box_Limit(RIGHT) + 4 , linkGrid->link[0][linkGrid->Get_Rows() / 2].Get_XY().y - 2 }, WHITE, TXT_SPD_ER, true);	// lols
					ListsOfChainToModify::Annihilate_All_Links(); // Efface tout les Murs et Les Links				
					P1.Set_Hp(3);
					ev_BotTutorial.delay.Stop();
					ev_BotTutorial.Advance(700);
				}
				break;



			case 55:
				ConsoleRender::Add_String(_28, Boss_Txt_Crd(_28), gBossClr, TXT_SPD_DR);
				ev_BotTutorial.Advance(375);
				break;

			case 56:
				ConsoleRender::Add_String(_29, Boss_Txt_Crd(_29,1 ), gBossClr, TXT_SPD_DR);
				ev_BotTutorial.Advance(250);
				break;

			case 57:
				ConsoleRender::Add_String(_28, Boss_Txt_Crd(_28), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_29, Boss_Txt_Crd(_29, 1), gBossClr, TXT_SPD_ER, true);
				ev_BotTutorial.Advance(1000);
				break;

			case 58:
				stepToSendBack = 58;	// si le joueur fail ce test, il sera send back icitte
				MsgQueue::Register(ENABLE_BLAST);	// r�active le blast
				Temporary_Bot_Speed_Switch(2000);	// vitesse de d�placement 
				Ev_Ultimate_Test();
				ConsoleRender::Add_String(_30, { Boss_Txt_X() - 10, Boss_Txt_Y()}, gBossClr, 0);
				ev_BotTutorial.Advance(550);
				break;

			case 59:
				ConsoleRender::Add_String(_31, { Boss_Txt_X() - 4,Boss_Txt_Y() }, gBossClr, 0);
				ev_BotTutorial.Advance(500);
				break;
				
			case 60:
				ConsoleRender::Add_String(_32, { Boss_Txt_X() + 7 ,Boss_Txt_Y() }, gBossClr, 0);
				ev_BotTutorial.Advance(400);
				break;


			case 61:
				ConsoleRender::Add_String(TXT_CONST.DOTDOTDOT, Boss_Txt_Crd(TXT_CONST.DOTDOTDOT, 2), gBossClr, 300);
				ev_BotTutorial.Advance(320);
				break;

			case 62:
				ConsoleRender::Add_String(_30, { Boss_Txt_X() - 10, Boss_Txt_Y() }, gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_31, { Boss_Txt_X() - 4,Boss_Txt_Y() }, gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_32, { Boss_Txt_X() + 7 ,Boss_Txt_Y() }, gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(TXT_CONST.DOTDOTDOT, Boss_Txt_Crd(TXT_CONST.DOTDOTDOT, 2), gBossClr, TXT_SPD_ER, true);
				ev_BotTutorial.Advance(1000);
				break;

			case 63:
				ConsoleRender::Add_String(_33, Boss_Txt_Crd(_33), gBossClr, TXT_SPD_DR);
				ev_BotTutorial.Advance(900);
				break;

			case 64:
				ConsoleRender::Add_String(_34, Jerry_Txt_Crd(_34), gJerClr, TXT_SPD_DR);
				ev_BotTutorial.Advance(600);
				break;

			case 65:
				ConsoleRender::Add_String(_35, Boss_Txt_Crd(_35, 1), gBossClr, TXT_SPD_DR);
				ev_BotTutorial.Advance(700);
				break;

			case 66:
				ConsoleRender::Add_String(_36, Jerry_Txt_Crd(_36, 1), gJerClr, TXT_SPD_DR);
				ev_BotTutorial.Advance(400);
				break;

			case 67:
				ConsoleRender::Add_String(_37, Jerry_Txt_Crd(_37, 2), gJerClr, 250);
				ConsoleRender::Add_String(_33, Boss_Txt_Crd(_33), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_34, Jerry_Txt_Crd(_34), gJerClr, TXT_SPD_ER, true);				
				ConsoleRender::Add_String(_35, Boss_Txt_Crd(_35, 1), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_36, Jerry_Txt_Crd(_36, 1), gJerClr, TXT_SPD_ER, true);
				ev_BotTutorial.Advance(400);
				break;

			case 68:
				ConsoleRender::Add_String(_38, Jerry_Txt_Crd(_38, 3), gJerClr, TXT_SPD_DR);
				ev_BotTutorial.Advance(240);
				break;

			case 69:
				ConsoleRender::Add_String(_39, Boss_Txt_Crd(_39, 1), gBossClr, TXT_SPD_DR);
				ev_BotTutorial.Advance(300);
				break;

			case 70:
				ConsoleRender::Add_String(_39_1, Boss_Txt_Crd(_39_1, 2), gBossClr, TXT_SPD_DR);
				ev_BotTutorial.Advance(250);
				break;

			case 71:
				ConsoleRender::Add_String(_40, Jerry_Txt_Crd(_40), gJerClr, 300);
				ConsoleRender::Add_String(_36, Jerry_Txt_Crd(_36, 1), gJerClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_37, Jerry_Txt_Crd(_37, 2), gJerClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_38, Jerry_Txt_Crd(_38, 3), gJerClr, TXT_SPD_ER, true);
				ev_BotTutorial.Advance(190);
				break;
			
			case 72:
				ConsoleRender::Add_String(_39, Boss_Txt_Crd(_39, 1), gBossClr, 50, true);
				ConsoleRender::Add_String(_39_1, Boss_Txt_Crd(_39_1, 2), gBossClr, 0, true);
				ConsoleRender::Add_String(_41, Boss_Txt_Crd(_41, 2), gBossClr, 80);
				ev_BotTutorial.Advance(500);
				break;

			case 73:
				ConsoleRender::Add_String(_42, Jerry_Txt_Crd(_42, 2), gJerClr, 150);
				ev_BotTutorial.Advance(400);
				break;

			case 74:
				ConsoleRender::Add_String(_43, Boss_Txt_Crd(_43), gBossClr, TXT_SPD_FAST);
				ConsoleRender::Add_String(_40, Jerry_Txt_Crd(_40), gJerClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_41, Boss_Txt_Crd(_41, 2), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_42, Jerry_Txt_Crd(_42, 2), gJerClr, TXT_SPD_ER, true);
				ev_BotTutorial.Advance(400);
				break;

			case 75:
				ConsoleRender::Add_String(_43_1, Boss_Txt_Crd(_43_1, 1), gBossClr, TXT_SPD_FAST);			
				ev_BotTutorial.Advance(800);
				break;

			case 76:
				//ConsoleRender::Add_String(_41, Boss_Txt_Crd(_41, 2), gBossClr, TXT_SPD_ER, true);
				ev_BotTutorial.Advance(0);
				break;

			case 77:

				ConsoleRender::Add_String(_44, Jerry_Txt_Crd(_44, 1), gJerClr, 150);
				ev_BotTutorial.Advance(800);
				break;

			case 78:
				ConsoleRender::Add_String(_45, Boss_Txt_Crd(_45, 2), gBossClr, TXT_SPD_DR);
				ev_BotTutorial.Advance(500);
				break;

			case 79:
				ConsoleRender::Add_String(_44, Jerry_Txt_Crd(_44, 1), gJerClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_46, Boss_Txt_Crd(_46, 3), gBossClr, 250);
				ev_BotTutorial.Advance(300);
				break;

			case 80:
				ConsoleRender::Add_String(_47, Jerry_Txt_Crd(_47, 2), gJerClr, TXT_SPD_DR);
				ev_BotTutorial.Advance(400);
				break;

			case 81:	
				ConsoleRender::Add_String(_43, Boss_Txt_Crd(_43), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_43_1, Boss_Txt_Crd(_43_1, 1), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_45, Boss_Txt_Crd(_45, 2), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_46, Boss_Txt_Crd(_46, 3), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_47, Jerry_Txt_Crd(_47, 2), gJerClr, TXT_SPD_ER, true);
				ev_BotTutorial.Advance(1000);
				break;
			
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			case 82:// V2
			ConsoleRender::Add_String(_48, Boss_Txt_Crd(_48), gBossClr, TXT_SPD_FAST);
			ev_BotTutorial.Advance(400);
			break;

			case 83:
			ConsoleRender::Add_String(_49, Jerry_Txt_Crd(_49), gJerClr, TXT_SPD_DR);
			ev_BotTutorial.Advance(1000);
			break;

			case 84:
			ConsoleRender::Add_String(_50, Boss_Txt_Crd(_50, 1), gBossClr, TXT_SPD_DR);
			ev_BotTutorial.Advance(700);
			break;

			case 85:
			ConsoleRender::Add_String(_51, Jerry_Txt_Crd(_51, 1), gJerClr, TXT_SPD_DR);
			ev_BotTutorial.Advance(600);
			break;

			case 86:
			ConsoleRender::Add_String(_53, Boss_Txt_Crd(_53, 2), gBossClr, TXT_SPD_DR);
			ev_BotTutorial.Advance(600);
			break;

			case 87:
			//ConsoleRender::Add_String(_54, Jerry_Txt_Crd(_54, 2), gJerClr, 450);
			ev_BotTutorial.Advance(0);
			break;

			case 88:
				ConsoleRender::Add_String(_48, Boss_Txt_Crd(_48), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_49, Jerry_Txt_Crd(_49), gJerClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_50, Boss_Txt_Crd(_50, 1), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_51, Jerry_Txt_Crd(_51, 1), gJerClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_53, Boss_Txt_Crd(_53, 2), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_54, Jerry_Txt_Crd(_54, 2), gJerClr, 360);
				ev_BotTutorial.Advance(500);
				break;

			case 89:
				ConsoleRender::Add_String(_55, Boss_Txt_Crd(_55), gBossClr, TXT_SPD_FAST);
				ev_BotTutorial.Advance(600);
				break;
				
			case 90:
				ConsoleRender::Add_String(_55_1, Boss_Txt_Crd(_55_1, 1), gBossClr, TXT_SPD_FAST);
				ConsoleRender::Add_String(_56, Boss_Txt_Crd(_56, 2), gBossClr, 300);
				ev_BotTutorial.Advance(400);
				break;
				

			case 91:
				ConsoleRender::Add_String(_55, Boss_Txt_Crd(_55), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_54, Jerry_Txt_Crd(_54, 2), gJerClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_55_1, Boss_Txt_Crd(_55_1, 1), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_56, Boss_Txt_Crd(_56, 2), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_57, Jerry_Txt_Crd(_57), gJerClr, 300);
				ev_BotTutorial.Advance(450);
				break;

			case 92:
				ConsoleRender::Add_String(_58, Boss_Txt_Crd(_58), gBossClr, TXT_SPD_FAST);
				ev_BotTutorial.Advance(600);
				break;


			case 93:
				ConsoleRender::Add_String(_57, Jerry_Txt_Crd(_57), gJerClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_58, Boss_Txt_Crd(_58), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_59, Jerry_Txt_Crd(_59, 1), gJerClr, 320);
				ev_BotTutorial.Advance(350);
				break;

			case 94:
				ConsoleRender::Add_String(_60, Jerry_Txt_Crd(_60, 2), gJerClr, 300);
				ev_BotTutorial.Advance(510);
				break;

			case 95:
				ConsoleRender::Add_String(_61, Boss_Txt_Crd(_61), gBossClr, TXT_SPD_FAST);
				ev_BotTutorial.Advance(600);
				break;

			case 96:
				ConsoleRender::Add_String(_62, Jerry_Txt_Crd(_62), gJerClr, 600);
				ConsoleRender::Add_String(_59, Jerry_Txt_Crd(_59, 1), gJerClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_60, Jerry_Txt_Crd(_60, 2), gJerClr, TXT_SPD_ER, true);
				ev_BotTutorial.Advance(250);
				break;


			case 97:
				ConsoleRender::Add_String(_61, Boss_Txt_Crd(_61), gBossClr, 0, true);
				ConsoleRender::Add_String(_62_1, { Jerry_Txt_X() + (int)_62.size() / 2, Jerry_Txt_Y() }, gJerClr);
				ev_BotTutorial.Advance(1200);
				break;

			case 98:
				ConsoleRender::Add_String(_63, Boss_Txt_Crd(_63), gBossClr, TXT_SPD_FAST);
				ev_BotTutorial.Advance(300);
				break;

			case 99:
				ConsoleRender::Add_String(_64, Boss_Txt_Crd(_64, 1), gBossClr, TXT_SPD_DR);
				ev_BotTutorial.Advance(500);
				break;

			case 100:
				ConsoleRender::Add_String(_62, Jerry_Txt_Crd(_62), gJerClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_62_1, { Jerry_Txt_X() + (int)_62.size() / 2, Jerry_Txt_Y() }, gJerClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_63, Boss_Txt_Crd(_63), gBossClr, 0, true);
				ConsoleRender::Add_String(_64, Boss_Txt_Crd(_64, 1), gBossClr, 0, true);
				ev_BotTutorial.Advance(1000);
				break;

			case 101:
				ConsoleRender::Add_String(_65, Boss_Txt_Crd(_65, 1), gBossClr, TXT_SPD_DR);
				ev_BotTutorial.Advance(400);
				break;

			case 102:
				ConsoleRender::Add_String(_66, Boss_Txt_Crd(_66, 2), gBossClr, TXT_SPD_DR);
				ev_BotTutorial.Advance(400);
				break;

			case 103:
				ConsoleRender::Add_String(_67, Boss_Txt_Crd(_67, 3), gBossClr, TXT_SPD_DR);
				ev_BotTutorial.Advance(400);
				break;

			case 104:
				ConsoleRender::Add_String(TXT_CONST.DOTDOTDOT, Boss_Txt_Crd(TXT_CONST.DOTDOTDOT, 4), gBossClr, 400);
				ev_BotTutorial.Advance(400);
				break;

			case 105:
				ConsoleRender::Add_String(_68, Boss_Txt_Crd(_68, 5), gBossClr, 200);
				ev_BotTutorial.Advance(300);
				break;

			case 106:
				ConsoleRender::Add_String(_64, Boss_Txt_Crd(_64), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_65, Boss_Txt_Crd(_65, 1), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_66, Boss_Txt_Crd(_66, 2), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_67, Boss_Txt_Crd(_67, 3), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(TXT_CONST.DOTDOTDOT, Boss_Txt_Crd(TXT_CONST.DOTDOTDOT, 4), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_68, Boss_Txt_Crd(_68, 5), gBossClr, TXT_SPD_ER, true);
				ev_BotTutorial.Advance(300);
				break;

			case 107:
				ConsoleRender::Add_String(_69, Boss_Txt_Crd(_69), gBossClr, TXT_SPD_FAST);
				ev_BotTutorial.Advance(800);
				break;

			case 108:
				ConsoleRender::Add_String(_70, Jerry_Txt_Crd(_70), gJerClr, TXT_SPD_FAST);
				ev_BotTutorial.Advance(700);
				break;

			case 109:
				ConsoleRender::Add_String(_71, Boss_Txt_Crd(_71, 2), gBossClr, TXT_SPD_FAST);
				ev_BotTutorial.Advance(700);
				break;

			case 110:
				ConsoleRender::Add_String(_72, { Jerry_Txt_X() - 5, Jerry_Txt_Y(3) }, gJerClr, 1000);
				ev_BotTutorial.Advance(300);
				break;

			case 111:
				ConsoleRender::Add_String(_73, { Jerry_Txt_X() + 1, Jerry_Txt_Y(3) }, gJerClr, TXT_SPD_DR);
				ev_BotTutorial.Advance(2000);
				break;

			case 112:
				ConsoleRender::Add_String(_74, Boss_Txt_Crd(_74, 5), gBossClr);
				ev_BotTutorial.Advance(0);	// fait juste wait here. Tout sera effac� par Finish_Ultimate_Test()
				ev_BotTutorial.delay.Start_Timer(10000, 1, true);
				break;

			case 113:			
				Finish_Ultimate_Test();
				break;

			case 114:
				ConsoleRender::Add_String(_75, Boss_Txt_Crd(_75 + _76), gBossClr, 300);
				ev_BotTutorial.Advance(350);	
				break;

			case 115:
				ConsoleRender::Add_String(_76, { Boss_Txt_X() - 3, Boss_Txt_Y() }, gBossClr, 250);
				ev_BotTutorial.Advance(500);
				break;

			case 116:
				ConsoleRender::Add_String(_75 + _76, Boss_Txt_Crd(_75 + _76), gBossClr, TXT_SPD_ER, true);
				ev_BotTutorial.Advance(1000);
				break;

			case 117:
				ConsoleRender::Add_String(_77, Boss_Txt_Crd(_77), gBossClr, 250);
				ev_BotTutorial.Advance(420);
				break;

			case 118:
				ConsoleRender::Add_String(_78, Boss_Txt_Crd(_78, 2), gBossClr, 250);
				ConsoleRender::Add_String(_79, Jerry_Txt_Crd(_79), gJerClr, 350);
				ev_BotTutorial.Advance(420);
				break;

			case 119:
				ConsoleRender::Add_String(_77, Boss_Txt_Crd(_77), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_78, Boss_Txt_Crd(_78, 2), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_79, Jerry_Txt_Crd(_79), gJerClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(TXT_CONST.DOTDOTDOT, Boss_Txt_Crd(TXT_CONST.DOTDOTDOT, 1), gBossClr, 400);
				ev_BotTutorial.Advance(420);
				break;

			case 120:
				ConsoleRender::Add_String(_80, Boss_Txt_Crd(_80, 2), gBossClr, 250);
				ev_BotTutorial.Advance(600);
				break;

			case 121:
				ConsoleRender::Add_String(_81, Boss_Txt_Crd(_81, 3), gBossClr, 250);
				ev_BotTutorial.Advance(320);
				break;

			case 122:				
				ConsoleRender::Add_String(_80, Boss_Txt_Crd(_80, 2), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_81, Boss_Txt_Crd(_81, 3), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(TXT_CONST.DOTDOTDOT, Boss_Txt_Crd(TXT_CONST.DOTDOTDOT, 1), gBossClr, TXT_SPD_ER, true);
				ev_BotTutorial.Advance(390);
				break;

			case 123:
				ConsoleRender::Add_String(_82, Boss_Txt_Crd(_82), gBossClr, 250);
				ev_BotTutorial.Advance(390);					 
				break;

			case 124:
				ConsoleRender::Add_String(_83, Boss_Txt_Crd(_83, 1), gBossClr, 250);
				ev_BotTutorial.Advance(390);
				break;

			case 125:
				ConsoleRender::Add_String(_84, Boss_Txt_Crd(_84, 3), gBossClr, 250);
				ev_BotTutorial.Advance(390);
				break;

			case 126:
				ConsoleRender::Add_String(_85, Boss_Txt_Crd(_85, 4), gBossClr, 500);
				ev_BotTutorial.Advance(390);
				break;
			
			case 127:
				ConsoleRender::Add_String(_82, Boss_Txt_Crd(_82),	 gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_83, Boss_Txt_Crd(_83, 1), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_84, Boss_Txt_Crd(_84, 3), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_85, Boss_Txt_Crd(_85, 4), gBossClr, TXT_SPD_ER, true);
				ev_BotTutorial.Advance(390);
				break;

			case 128:
				ConsoleRender::Add_String(_86, Boss_Txt_Crd(_86, 3), gBossClr, 250);
				ev_BotTutorial.Advance(500);
				break;

			case 129:
				ConsoleRender::Add_String(_86, Boss_Txt_Crd(_86, 3), gBossClr, TXT_SPD_ER, true);
				ev_BotTutorial.Advance(1000);
				break;
			
			case 130:
				ev_BotTutorial.Advance(400);
				break;
				
			case 131:
				stepToSendBack = 129;
				jerryTime = true;
				P1.Set_Hp(3); Just_Dr_Heart(); Press_X_To_Proceed();
				Make_It_Vertical_Only();
				Set_Jerry(NONE, -1, prevMovSPeed);
				Ev_Spawn_Jerry();
				MsgQueue::Register(ENABLE_BLAST);
				ev_BotTutorial.Advance(400);
				ev_BotTutorial.delay.Start_Timer(10000, 1, true);
				break;

			case 132:

				ConsoleRender::Add_String(_86, Boss_Txt_Crd(_86, 3), gBossClr, TXT_SPD_ER, true);
				ev_BotTutorial.Advance(400);
				break;

			case 133:
				ConsoleRender::Add_String(_86, Boss_Txt_Crd(_86, 3), gBossClr, TXT_SPD_ER, true);
				ev_BotTutorial.Advance(400);
				break;

			case 134:
				ConsoleRender::Add_String(_86, Boss_Txt_Crd(_86, 3), gBossClr, TXT_SPD_ER, true);
				ev_BotTutorial.Advance(400);
				break;

			case 135:
				ConsoleRender::Add_String(_86, Boss_Txt_Crd(_86, 3), gBossClr, TXT_SPD_ER, true);
				ev_BotTutorial.Advance(400);
				break;

			case 136:
				ConsoleRender::Add_String(_86, Boss_Txt_Crd(_86, 3), gBossClr, TXT_SPD_ER, true);
				ev_BotTutorial.Advance(400);
				break;
				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//case 82:// V1 
			//	ConsoleRender::Add_String(_48, Boss_Txt_Crd(_48), gBossClr, TXT_SPD_DR);
			//	ev_BotTutorial.Advance(400);
			//	break;

			//case 83:
			//	ConsoleRender::Add_String(_49, Boss_Txt_Crd(_49, 1 ), gBossClr, TXT_SPD_DR);
			//	ev_BotTutorial.Advance(400);
			//	break;

			//case 84:
			//	ConsoleRender::Add_String(_50, Boss_Txt_Crd(_50, 2), gBossClr, TXT_SPD_DR);
			//	ev_BotTutorial.Advance(300);
			//	break;

			//case 85:
			//	ConsoleRender::Add_String(_51, Boss_Txt_Crd(_51, 3), gBossClr, TXT_SPD_FAST);
			//	ev_BotTutorial.Advance(400);
			//	break;

			//case 86:
			//	ConsoleRender::Add_String(_52, Jerry_Txt_Crd(_52), gJerClr, TXT_SPD_DR);
			//	ev_BotTutorial.Advance(400);
			//	break;
				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



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

			//	// D�but d'un choix pour le joueur
			//	choiceCrd = { 0, 8 };

			//	for (int i = 0; i < 10; i++)		// Le joueur doit "Rater" la performance de Jerry!
			//	{
			//		
			//		if (i == 0)
			//		{
			//			ChoiceTime::Add_Choice(recom[i], "(The Worst)", choiceCrd);
			//		}
			//		else
			//			if (i == 9) // le dixi�me choix
			//			{
			//				ChoiceTime::Add_Choice(recom[i], "(Okay)", choiceCrd);
			//				choiceCrd.c++;
			//			}
			//			else
			//			{
			//				ChoiceTime::Add_Choice(recom[i], TXT_CONST.EMPTY, choiceCrd);
			//			}
			//		choiceCrd.c++;

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
	

// __/\\\\\\\\\\\\\\\__/\\\________/\\\________/\\\\\\\\\__/\\\________/\\\_______________/\\\____        
//  _\/\\\///////////__\/\\\_______\/\\\_____/\\\////////__\/\\\_____/\\\//______________/\\\\\\\__       
//   _\/\\\_____________\/\\\_______\/\\\___/\\\/___________\/\\\__/\\\//________________/\\\\\\\\\_      
//    _\/\\\\\\\\\\\_____\/\\\_______\/\\\__/\\\_____________\/\\\\\\//\\\_______________\//\\\\\\\__     
//     _\/\\\///////______\/\\\_______\/\\\_\/\\\_____________\/\\\//_\//\\\_______________\//\\\\\___    
//      _\/\\\_____________\/\\\_______\/\\\_\//\\\____________\/\\\____\//\\\_______________\//\\\____   
//       _\/\\\_____________\//\\\______/\\\___\///\\\__________\/\\\_____\//\\\_______________\///_____  
//        _\/\\\______________\///\\\\\\\\\/______\////\\\\\\\\\_\/\\\______\//\\\_______________/\\\____ 
//         _\///_________________\/////////___________\/////////__\///________\///_______________\///_____
                                                                                                       
