

#include "ev_waking_up.h"
#include "../../../UI/console_output/render_list.h"
#include "../../../console/sweet_cmd_console.h"
#include "../../../events/events.h"
#include "../../../player/player.h"
#include "../../../events/msg_dispatcher.h"
#include "../../../inputs/action_input.h"
#include "ev_enter_name.h"
#include "../../../choice/choice_time.h"
#include "../msg_events/ev_arr_keys.h"
#include "../../../events/global_events/feedback/ev_draw_map.h"
#include "../../../events/global_events/ev_update_heart.h"
#include "../events/ev_bot_tutorial.h"
#include "../../lvl_script.h"
#include "../../../UI/console_output/dsp_string.h"

static Event ev_WakeUp(Ev_Wake_Up, 30);

static std::string _1 = "Hey, Are You Listening !?"; 
static std::string _2 = "Could You Not Sleep When";
static std::string _3 = "I'm Talking To You?";
static std::string _4 = "So As I Was Saying...";
static std::string _5 = "Your Job Here Is To Stop";
static std::string _6 = "These Awful 'T' Like Shapes!";
static std::string _7 = "So, Do You Think You Can Do That?";
static std::string _8 = "Great!";
static std::string _9 = "You, Don't Look So Sure?";
static std::string _10 ="Alright, I'll let you be then";
static std::string _11 = "And Just In Case You Are Overconfident";
static std::string _12= "Good Luck!";
static std::string _13= "And Try Not To Die.";

/* Patching tes string à la con xD*/

static std::string _14 = "As You Should Know";
static std::string _15 = "\"IF\", You Had Read";
static std::string _16 = "\"The Good Employee Operation Manual\"";
static std::string _17 = "- ULTRA PERFORMANCE EDITION - ";
static std::string _18 = "We Sent You""And Try Not To Die.";
static std::string _19 = "And Try Not To Die.";


// CHOICE STRINGS
static std::string yes_1 = "Huuh...";				// Accept de faire le tutorial
static std::string subyes_1 =  "(Start Tutorial)";	// Accept de faire le tutorial
static std::string yes_2 = "Actually, Maybe Not.";
static std::string subyes_2 = "(You Swallow your Ego)";
static std::string no_1 = "Yes!";					// refuse de faire le tutorial
static std::string subno_1 = "(You Are Confident)";	// refuse de faire le tutorial
static std::string no_2 = "Absolutely!";
static std::string subno_2 = "(You Know What You're Doing)";

static std::string prob = "No Problem Here";
static std::string honest= "I Appreciate Honesty";


Colors deluxe;

void Ev_Wake_Up()			// Accueil Le joueur quand il sort de son répit
{
	if (!ev_WakeUp.Is_Active())
	{
		Ev_Dr_Map_Borders_1();
		ev_WakeUp.Activate();
		ev_WakeUp.Start(500);	// 1000 / 2 = 500.		2 secondes
		MsgQueue::Register(STAGE_ADVANCE);
	}
	else
	{
		while (ev_WakeUp.delay.Tick())
			switch (ev_WakeUp.Get_Current_Step())
			{
			case 1:
				ConsoleRender::Add_String(_1, Boss_Txt_Crd(_1), gBossClr, TXT_SPD_DR);
				ev_WakeUp.Advance(350);
				break;

			case 2:
				ConsoleRender::Add_String(_1, Boss_Txt_Crd(_1), gBossClr, TXT_SPD_ER, true);
				ev_WakeUp.Advance(700);
				break;

			case 3:
				ConsoleRender::Add_String(_2, Boss_Txt_Crd(_2), gBossClr, TXT_SPD_DR);
				ev_WakeUp.Advance(800);
				break;

			case 4:
				ConsoleRender::Add_String(_3, Boss_Txt_Crd(_3, 1), gBossClr, TXT_SPD_DR);
				ev_WakeUp.Advance(340);
				break;

			case 5:
				ev_WakeUp.Advance(0);
				break;

			case 6:
				ConsoleRender::Add_String(_2, Boss_Txt_Crd(_2), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_3, Boss_Txt_Crd(_3, 1), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_4, Boss_Txt_Crd(_4), gBossClr, TXT_SPD_DR);
				ev_WakeUp.Advance(400);
				break;

			case 7:
				ConsoleRender::Add_String(_4, Boss_Txt_Crd(_4), gBossClr, TXT_SPD_ER, true);
				ev_WakeUp.Advance(800);
				break;

			case 8:
				ConsoleRender::Add_String(_14, Boss_Txt_Crd(_14), gBossClr, TXT_SPD_DR);
				ev_WakeUp.Advance(600);
				break;

			case 9:
				ConsoleRender::Add_String(_15, Boss_Txt_Crd(_15, 1), gBossClr, TXT_SPD_DR);
				ev_WakeUp.Advance(900);
				break;

			case 10:
				ConsoleRender::Add_String(_16, Boss_Txt_Crd(_16, 2), gBossClr, TXT_SPD_DR);
				ev_WakeUp.Advance(350);
				break;

			case 11:

				for (int i = 0; i < 150; i++)
				{
					for (size_t clr = 9; clr < 15; clr++)
					{
						UI_Dsp_String(Boss_Txt_Crd(_17, 3), _17, (Colors)clr, 10);
					}
				}


				//ConsoleRender::Add_String(TXT_CONST.DOTDOTDOT, Boss_Txt_Crd(TXT_CONST.DOTDOTDOT), gBossClr, 400);
				ev_WakeUp.Advance(0);
				break;

			case 12:
				ConsoleRender::Add_String(_14, Boss_Txt_Crd(_14), gBossClr,    TXT_SPD_ER, true);
				ConsoleRender::Add_String(_15, Boss_Txt_Crd(_15, 1), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_16, Boss_Txt_Crd(_16, 2), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_17, Boss_Txt_Crd(_17, 3), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_5, Boss_Txt_Crd(_5), gBossClr, TXT_SPD_DR);
				//ConsoleRender::Add_String(TXT_CONST.DOTDOTDOT, Boss_Txt_Crd(TXT_CONST.DOTDOTDOT, 1), gBossClr, 400);
				ev_WakeUp.Advance(900);
				break;

			case 13:
				ConsoleRender::Add_String(_6, Boss_Txt_Crd(_6, 2), gBossClr, TXT_SPD_DR);
				//ConsoleRender::Add_String(TXT_CONST.DOTDOTDOT, Boss_Txt_Crd(TXT_CONST.DOTDOTDOT, 2), gBossClr, 400);
				ev_WakeUp.Advance(300);
				break;

			case 14:
				ConsoleRender::Add_String(_5, Boss_Txt_Crd(_5), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_6, Boss_Txt_Crd(_6, 2), gBossClr, TXT_SPD_ER, true);
				//ConsoleRender::Add_String(TXT_CONST.DOTDOTDOT, Boss_Txt_Crd(TXT_CONST.DOTDOTDOT, 2), gBossClr, TXT_SPD_ER, true);
				//ConsoleRender::Add_String(TXT_CONST.DOTDOTDOT, Boss_Txt_Crd(TXT_CONST.DOTDOTDOT, 1), gBossClr, TXT_SPD_ER, true);
				//ConsoleRender::Add_String(TXT_CONST.DOTDOTDOT, Boss_Txt_Crd(TXT_CONST.DOTDOTDOT, 0), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_7, Boss_Txt_Crd(_7), gBossClr, TXT_SPD_DR);
				ev_WakeUp.Advance(400);
				break;

			case 15:
				// Début d'un choix pour le joueur
				ChoiceTime::Add_Choice(yes_1, subyes_1, { 3,7 });
				ChoiceTime::Add_Choice(no_1, subno_1, { 9,7 });
				ev_WakeUp.Advance(0);
				ev_WakeUp.delay.Start_Timer(2000, 1, true);	// infinite check here
				break;

			case 16:
				if (ChoiceTime::Get_Choice_Made() == yes_1)
				{
					ConsoleRender::Add_String(_7, Boss_Txt_Crd(_7), gBossClr, TXT_SPD_ER, true);
					Ev_Bot_Tutorial();	// start tuto avec jerry
					ev_WakeUp.Cancel();	// Stop l'event right now
				}
				else
					if (ChoiceTime::Get_Choice_Made() == no_1) // start second choice					
					{
						ConsoleRender::Add_String(_7, Boss_Txt_Crd(_7), gBossClr, TXT_SPD_ER, true);
						ev_WakeUp.delay.Stop();
						ev_WakeUp.Advance(500);
					}
				break;

			case 17:
				ConsoleRender::Add_String(_8, Boss_Txt_Crd(_8), gBossClr, TXT_SPD_DR);
				ev_WakeUp.Advance(400);
				break;

			case 18:
				ConsoleRender::Add_String(TXT_CONST.DOTDOTDOT, Boss_Txt_Crd(TXT_CONST.DOTDOTDOT, 2), gBossClr, TXT_SPD_DR / 3);
				ev_WakeUp.Advance(600);
				break;


			case 19:
				ConsoleRender::Add_String(_8, Boss_Txt_Crd(_8), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(TXT_CONST.DOTDOTDOT, Boss_Txt_Crd(TXT_CONST.DOTDOTDOT, 2), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_9, Boss_Txt_Crd(_9), gBossClr, TXT_SPD_DR);
				ev_WakeUp.Advance(700);
				break;

			case 20:
				// Début d'un 2e choix pour le joueur
				ChoiceTime::Add_Choice(yes_2, subyes_2, { 3,7 });
				ChoiceTime::Add_Choice(no_2, subno_2, { 9,7 });
				ev_WakeUp.Advance(0);
				ev_WakeUp.delay.Start_Timer(2000, 1, true);	// infinite check here
				break;

			case 21:
				// Début d'un choix pour le joueur
				ev_WakeUp.delay.Start_Timer(2000, 1, true);	// infinite check here

				if (ChoiceTime::Get_Choice_Made() == yes_2)
				{
					ev_WakeUp.Go_To_X_Step(28);						// Stop l'event right now
					ConsoleRender::Add_String(_9, Boss_Txt_Crd(_9), gBossClr, TXT_SPD_ER, true);

				}
				else
					if (ChoiceTime::Get_Choice_Made() == no_2) // pas du tutorial today, MAIS... On va afficher les touches claviers avant le premier niveau au moins					
					{
						ConsoleRender::Add_String(_9, Boss_Txt_Crd(_9), gBossClr, TXT_SPD_ER, true);
						ConsoleRender::Add_String(_10, Boss_Txt_Crd(_10), gBossClr, TXT_SPD_DR);
						Erase_Map_Borders_1();	// erase borders
						ev_WakeUp.delay.Stop();
						ev_WakeUp.Advance(300);
					}
				break;

			case 22:
				ConsoleRender::Add_String(_10, Boss_Txt_Crd(_10), gBossClr, TXT_SPD_ER, true);
				ev_WakeUp.Advance(400);
				break;

			case 23:
				ConsoleRender::Add_String(_11, Boss_Txt_Crd(_11), gBossClr, TXT_SPD_DR);
				Ev_Dr_Arr_Keys();
				ev_WakeUp.Advance(300);
				break;

			case 24:
				ConsoleRender::Add_String(_11, Boss_Txt_Crd(_11), gBossClr, TXT_SPD_ER, true);
				ev_WakeUp.Advance(400);
				break;

			case 25:
				ConsoleRender::Add_String(_12, Boss_Txt_Crd(_12), gBossClr, TXT_SPD_DR);
				ev_WakeUp.Advance(400);
				break;

			case 26:
				ConsoleRender::Add_String(_13, Boss_Txt_Crd(_13, 1), gBossClr, TXT_SPD_DR);
				ev_WakeUp.Advance(200);
				break;

			case 27:
				ConsoleRender::Add_String(_12, Boss_Txt_Crd(_12), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_13, Boss_Txt_Crd(_13, 1), gBossClr, TXT_SPD_ER, true);

				//Just_Dr_Heart();	// redraw le coeur

				MsgQueue::Register(STAGE_ADVANCE);	// Avance d'un stage	// faut que le stage soit le 4e
				ev_WakeUp.Cancel();
				break;


				/* Cheat laid ici, branching dialogue de bouette*/
			case 28:
				ConsoleRender::Add_String(prob, Boss_Txt_Crd(prob), gBossClr, TXT_SPD_DR);
				ev_WakeUp.delay.Stop();
				ev_WakeUp.Advance(400);
				break;

			case 29:
				ConsoleRender::Add_String(honest, Boss_Txt_Crd(honest, 1), gBossClr, TXT_SPD_DR);
				ev_WakeUp.Advance(400);
				break;

			case 30:
				ConsoleRender::Add_String(prob, Boss_Txt_Crd(prob), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(honest, Boss_Txt_Crd(honest, 1), gBossClr, TXT_SPD_ER, true);
				Ev_Bot_Tutorial();	// start tuto avec jerry
				ev_WakeUp.Advance(0);
				break;
			}

	}
}