

#include "ev_waking_up_2.h"
#include "../../../UI/console_output/render_list.h"
#include "../../../console/sweet_cmd_console.h"
#include "../../../events/events.h"
#include "../../../player/player.h"
#include "../../../events/msg_dispatcher.h"
#include "../../../inputs/action_input.h"
#include "../../../structure_manager/modify_chain.h"
#include "../../../events/global_events/ev_to_proceed.h"
#include "../../../items/item_spawner.h"
#include "../../../blast/blast_modifier_queue.h"

#include "../../../choice/choice_time.h"
#include "../../../events/global_events/feedback/ev_draw_map.h"
#include "../../lvl_script.h"
#include "../../../UI/console_output/dsp_string.h"
#include "../../lvl_1/msg_events/ev_enter_name.h"		// INTRUDER
#include "../../../events/global_events/ev_spwn_player.h"

static void Ev_Dumb_Dialogue_Fixer();

static Event ev_WakeUp2(Ev_Wake_Up_2, 50);
static Event ev_DumbDialogueFixer(Ev_Dumb_Dialogue_Fixer,20);

 //;
 //"I Can't Recall Your Name Somehow"; What was you name again? (choice time) = Custom reaction
// The Company Is Introducing New Tools  To Help You On Your Work. I'm Just Here To Present Them To You
// anyway, here they are. Try Them both. "Very Useful Right?". Yeah, im not sure either. But Apparently, if you don't use them you're gonna have a bad time.I Think You will Be The Judge Of That
// .

static std::string _1 = "Hey, It's......You!";
static std::string _2 = "You Work Here Right?";
static std::string _3 = "No?";
static std::string _4 = "I'm Sorry If I Don't Remember You";
static std::string _5 = "There Is Just, Too Many New Faces";
static std::string _6 = "What Was Your Name again?";
static std::string _10 = "Anyway, Welcome Back, Trainee!";
static std::string _11 = "Usually, People Tend To Quit On Their First Day";
static std::string _12 = "I Mean, If They Manage To Survive That Is...";

static std::string fix_1 = "You Are Not Out Of The Woods Yet, However";
static std::string fix_2 = "If You Manage To Complete 2 More Days";
static std::string fix_3 = "Of Training, You Will Be Officially Hired Here";
static std::string fix_4 = "And As A, Bonus, You Will Get Paid!";
static std::string fix_5 = "Money Is Great Right? I Love Money...";

static std::string _13 = "Now, For Today";
static std::string _14 = "You Will Have To Use Our Brand NEW Mandatory \"Tools\"";
static std::string _15 = "Here They Are";
static std::string _16 = "Try Them Both";
static std::string _17 = "Very Useful Right?";
static std::string _18 = ". . . .";
static std::string _19 = "Honestly, I Have No Idea What They Do";
static std::string _20 = "I Just Do What I'm Told, Sorry";
static std::string _21 = "Feel Free To Experiment Here As Long As You Want";
static std::string _22 = "Good Luck!";

// Faire un choix: Ici c'est choisir son propre nom :_)
static std::string choiceMade;	// Choix fait par le joueur
static std::string choiceTitle = "What Is Your Name?";
static std::string choices[4] = { "Gardakan, The Great", "Paul", "Megan", "Custom Name" };


static std::string* branch;					// Point vers la branch
static int const BRANCH_SIZE[3] = {3,2,3};	// Le nombre de string présent dans chaques branches de choix
static int branchIndex;					
static int stringIndex;				

static std::string answersBranch_1[] = {"Wow. That...", "As Cool As Your Name Sounds", "I Do Not Remember You, Sorry"};	// Branche de dialogue pour gardakan
static std::string answersBranch_2[] = {"What A Bland Name", "Probably Why I Couldn't Remember It"};	// Pour les noms ordinaire "Paul" "Megan" 
static std::string answersBranch_3[] = {"\"Custom Name\"?", "That's Your Name?", "Wow. I feel Sorry For You"/*Probably A Rough Childhood Too*/};	// Le Nom custom
//
//static std::string answersBranch[] =
//{ "Wow. That...", "Cool Name. Although I Still Can't Remember You Sorry" , // Branche de dialogue pour gardakan
//"What A Bland Name", "Probably Why I Couldn't Remember It", // Pour les noms ordinaire "Paul" "Megan" 
//"\"Custom Name\"?", "That's Your Name?", "Wow. I feel Sorry For You"/*Probably A Rough Childhood Too*/ }; // Le Nom custom


//static std::string _24 =
// Histoire, le boss à reçu une mauvaise performance review et ça se peut qu'il se fasse mettre à la porte, ou du moins remplacé par Jerry
// Next Level On apprend qu'il s'est fait remplacé par Jerry, Qui est bcp trop intense, et qui a réussie à monter grâce à sa détermination
// Mais Jerry à des standards trop élevés (LVL Fast)


void Lvl2_S1_Refresher()	/// Refresher du niveau 2, stage 1
{
	if (gRefreshStage)
	{
		blastP1.Clear_Blast();
		ListsOfChainToModify::Annihilate_All_Links();	// Links
		ItemsOnGrid::Remove_All();	// enlève tout les items spawné
		P1.Er_Player();
		P1.Set_Position({ 6,1 });
		P1.Dr_Player();
		gGrids.Make_Chain_Of_Walls({ 3,9 }, DOWN, wallGridVer->Get_Rows() - 9);	// Mur que le joueurs va tirés avec les items
		gGrids.Make_Chain_Of_Walls({ 9,9 }, DOWN, wallGridVer->Get_Rows() - 9);	// Mur que le joueurs va tirés avec les items
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 3,5 });
		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 9,5 });
		gRefreshStage = false;
	}
}

void Ev_Wake_Up_2()
{
	if (!ev_WakeUp2.Is_Active())
	{
		Just_Dr_Map_Borders();
		P1.Set_Sym(AllPlyrSym[0]); P1.Set_Position({ 6,1 });
		Set_Ev_Spawn_Player(3);

		ListsOfChainToModify::Annihilate_All_Links();
		ev_WakeUp2.Activate();
		ev_WakeUp2.Start(1000);
		MsgQueue::Register(ENABLE_BLAST);


		//ev_WakeUp2.Go_To_X_Step(21);
	}
	else
	{
		Lvl2_S1_Refresher();
		while (ev_WakeUp2.delay.Tick())
			switch (ev_WakeUp2.Get_Current_Step())
			{
			case 1:
				Press_X_To_Proceed(4);
				for (int c = 0; c < linkGrid->Get_Cols(); c++)
					gGrids.Activate_Blocker({ c,4 });

				ConsoleRender::Add_String(_1, Boss_Txt_Crd(_1), gBossClr, TXT_SPD_DR - 3);
				ev_WakeUp2.Advance(300);
				break;

			case 2:
				ConsoleRender::Add_String(_1, Boss_Txt_Crd(_1), gBossClr, TXT_SPD_ER, true);
				ev_WakeUp2.Advance(500);
				break;

			case 3:
				ConsoleRender::Add_String(_2, Boss_Txt_Crd(_2), gBossClr, TXT_SPD_DR);
				ev_WakeUp2.Advance(400);
				break;

			case 4:
				ConsoleRender::Add_String(_3, Boss_Txt_Crd(_3, 1), gBossClr, TXT_SPD_DR);
				ev_WakeUp2.Advance(1000);
				break;

			case 5:
				ConsoleRender::Add_String(_4, Boss_Txt_Crd(_4, 2), gBossClr, TXT_SPD_DR);
				ev_WakeUp2.Advance(300);
				break;

			case 6:
				ConsoleRender::Add_String(_2, Boss_Txt_Crd(_2), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_3, Boss_Txt_Crd(_3, 1), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_4, Boss_Txt_Crd(_4, 2), gBossClr, TXT_SPD_ER, true);
				ev_WakeUp2.Advance(1000);
				break;

			case 7:
				ConsoleRender::Add_String(_5, Boss_Txt_Crd(_5), gBossClr, TXT_SPD_DR);
				ev_WakeUp2.Advance(300);
				break;

			case 8:
				//ConsoleRender::Add_String(_5, Boss_Txt_Crd(_5), gBossClr, TXT_SPD_ER, true);
				ev_WakeUp2.Advance(0);
				break;

			case 9:
				ConsoleRender::Add_String(_6, Boss_Txt_Crd(_6, 1), gBossClr, TXT_SPD_DR);
				ev_WakeUp2.Advance(900);
				break;

			case 10:
				// Début d'un choix pour le joueur
				ConsoleRender::Add_String(choiceTitle, { Find_Ctr_X((int)choiceTitle.size() / 2) - 5, linkGrid->link[6][4].Get_XY().y + 4 }, gBossClr, TXT_SPD_DR, true);
				ChoiceTime::Add_Choice(choices[0], TXT_CONST.SPACE_STRING, { 3,9 });
				ChoiceTime::Add_Choice(choices[1], TXT_CONST.SPACE_STRING, { 9,11 });
				ChoiceTime::Add_Choice(choices[2], TXT_CONST.SPACE_STRING, { 7, 12 });
				ChoiceTime::Add_Choice(choices[3], TXT_CONST.SPACE_STRING, { 2, 13 });

				for (int c = 0; c < linkGrid->Get_Cols(); c++)	// Désctive une rangée de blockers
					gGrids.Activate_Blocker({ c,3 }, true);

				ev_WakeUp2.Advance(0);
				ev_WakeUp2.delay.Start_Timer(2000, 1, true);	// infinite check here
				break;

			case 11:
				if (!ChoiceTime::Is_Choice_Time())
				{
					ConsoleRender::Add_String(_5, Boss_Txt_Crd(_5), gBossClr, TXT_SPD_ER, true);
					ConsoleRender::Add_String(_6, Boss_Txt_Crd(_6, 1), gBossClr, TXT_SPD_ER, true); // Erase la question

					choiceMade = ChoiceTime::Get_Choice_Made();

					if (choiceMade == choices[0])
					{
						branchIndex = 0;
						branch = answersBranch_1;
					}
					if (choiceMade == choices[2] || choiceMade == choices[1])
					{
						branchIndex = 1;
						branch = answersBranch_2;
					}
					if (choiceMade == choices[3])
					{
						branchIndex = 2;
						branch = answersBranch_3;
					}
					ev_WakeUp2.delay.Stop();
					ev_WakeUp2.Advance(600, BRANCH_SIZE[branchIndex]);
				}

				stringIndex = 0;
				break;

			case 12:
				ConsoleRender::Add_String(branch[stringIndex], Boss_Txt_Crd(branch[stringIndex], stringIndex), gBossClr, TXT_SPD_DR);
				stringIndex++;
				ev_WakeUp2.Advance(350);
				break;

			case 13:
				Erase_All_Boss_Txt(true);
				ev_WakeUp2.Advance(1000);
				break;

			case 14:
				ev_WakeUp2.Advance(0);
				break;

			case 15:
				ev_WakeUp2.Advance(0);
				break;

			case 16:
				ConsoleRender::Add_String(_10, Boss_Txt_Crd(_10), gBossClr, TXT_SPD_DR);
				ev_WakeUp2.Advance(350);
				break;

			case 17:
				ConsoleRender::Add_String(_11, Boss_Txt_Crd(_11, 1), gBossClr, TXT_SPD_DR);
				ev_WakeUp2.Advance(500);
				break;

			case 18:
				ConsoleRender::Add_String(_12, Boss_Txt_Crd(_12, 2), gBossClr, TXT_SPD_DR);
				ev_WakeUp2.Advance(300);
				break;

			case 19:
				ConsoleRender::Add_String(_10, Boss_Txt_Crd(_10), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_11, Boss_Txt_Crd(_11, 1), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_12, Boss_Txt_Crd(_12, 2), gBossClr, TXT_SPD_ER, true);
				Ev_Dumb_Dialogue_Fixer();
				break;

			case 20:
				ConsoleRender::Add_String(_13, Boss_Txt_Crd(_13), gBossClr, TXT_SPD_DR);
				ev_WakeUp2.Advance(400);
				break;

			case 21:
				ConsoleRender::Add_String(_14, Boss_Txt_Crd(_14, 1), gBossClr, TXT_SPD_DR);
				ev_WakeUp2.Advance(250);
				break;

			case 22:
				ConsoleRender::Add_String(_13, Boss_Txt_Crd(_13), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_14, Boss_Txt_Crd(_14, 1), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_15, Boss_Txt_Crd(_15, 2), gBossClr, TXT_SPD_DR);
				ev_WakeUp2.Advance(800);
				break;

			case 23:
				ConsoleRender::Add_String(_16, Boss_Txt_Crd(_16, 3), gBossClr, TXT_SPD_DR);
				ev_WakeUp2.Advance(1000);
				break;

			case 24:
				gRefreshStage = true;
				Lvl2_S1_Refresher();
				ev_WakeUp2.Advance(0);
				ev_WakeUp2.delay.Start_Timer(10000, 1, true);

			case 25:
				if (!ItemsOnGrid::size && !BlastModifierQueue::What_Is_Size())
				{
					// Erase tout les textes
					ConsoleRender::Add_String(_15, Boss_Txt_Crd(_15, 2), gBossClr, TXT_SPD_ER, true);
					ConsoleRender::Add_String(_16, Boss_Txt_Crd(_16, 3), gBossClr, TXT_SPD_ER, true);

					ev_WakeUp2.delay.Stop();
					ev_WakeUp2.Advance(1000);
				}
				break;

			case 26:
				Press_R_To_Refresh();
				ConsoleRender::Add_String(_17, Boss_Txt_Crd(_17), gBossClr, TXT_SPD_DR);
				ev_WakeUp2.Advance(500);
				break;

			case 27:
				ConsoleRender::Add_String(_18, Boss_Txt_Crd(_18, 1), gBossClr, TXT_SPD_DR);
				ev_WakeUp2.Advance(300);
				break;

			case 28:
				ConsoleRender::Add_String(_17, Boss_Txt_Crd(_17), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_18, Boss_Txt_Crd(_18, 1), gBossClr, TXT_SPD_ER, true);
				ev_WakeUp2.Advance(400);
				break;

			case 29:
				ConsoleRender::Add_String(_19, Boss_Txt_Crd(_19), gBossClr, TXT_SPD_DR);
				ev_WakeUp2.Advance(300);
				break;

			case 30:
				ConsoleRender::Add_String(_20, Boss_Txt_Crd(_20, 1), gBossClr, TXT_SPD_DR);
				ev_WakeUp2.Advance(300);
				break;

			case 31:
				ConsoleRender::Add_String(_19, Boss_Txt_Crd(_19), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_20, Boss_Txt_Crd(_20, 1), gBossClr, TXT_SPD_ER, true);
				ev_WakeUp2.Advance(1000);
				break;

			case 32:
				ConsoleRender::Add_String(_21, Boss_Txt_Crd(_21), gBossClr, TXT_SPD_DR);
				ev_WakeUp2.Advance(400);
				break;

			case 33:
				ConsoleRender::Add_String(_21, Boss_Txt_Crd(_21), gBossClr, TXT_SPD_ER, 1);
				ev_WakeUp2.Advance(500);
				break;

			case 34:
				ConsoleRender::Add_String(_22, Boss_Txt_Crd(_22, 1), gBossClr, TXT_SPD_DR);
				ev_WakeUp2.Advance(250);
				break;

			case 35:
				ConsoleRender::Add_String(_22, Boss_Txt_Crd(_22, 1), gBossClr, TXT_SPD_ER, true);
				ev_WakeUp2.Advance(500);
				break;
			}
	}
	// ON NE CANCEL PAS L'EVENT
}

void Ev_Dumb_Dialogue_Fixer()
{
	if (!ev_DumbDialogueFixer.Is_Active())
	{
		ev_DumbDialogueFixer.Activate();
		ev_DumbDialogueFixer.Start(400);
	}
	else
	{
		while (ev_DumbDialogueFixer.delay.Tick())
			switch (ev_DumbDialogueFixer.Get_Current_Step())
			{
			case 1:	ConsoleRender::Add_String(fix_1, Boss_Txt_Crd(fix_1), gBossClr, TXT_SPD_DR);ev_DumbDialogueFixer.Advance(400);break;
			case 2:	ConsoleRender::Add_String(fix_2, Boss_Txt_Crd(fix_2, 1), gBossClr, TXT_SPD_DR);ev_DumbDialogueFixer.Advance(700);break;
			case 3:	ConsoleRender::Add_String(fix_3, Boss_Txt_Crd(fix_3, 2), gBossClr, TXT_SPD_DR);ev_DumbDialogueFixer.Advance(200);break;

			case 4:
				ConsoleRender::Add_String(fix_1, Boss_Txt_Crd(fix_1), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(fix_2, Boss_Txt_Crd(fix_2, 1), gBossClr, TXT_SPD_ER, true); ev_DumbDialogueFixer.Advance(600);
				ConsoleRender::Add_String(fix_3, Boss_Txt_Crd(fix_3, 2), gBossClr, TXT_SPD_ER, 1);break;

			case 5:ConsoleRender::Add_String(fix_4, Boss_Txt_Crd(fix_4), gBossClr, TXT_SPD_DR);ev_DumbDialogueFixer.Advance(400);break;
			case 6:ConsoleRender::Add_String(fix_5, Boss_Txt_Crd(fix_5, 1), gBossClr, TXT_SPD_DR);ev_DumbDialogueFixer.Advance(300);break;
			case 7:
				ConsoleRender::Add_String(fix_4, Boss_Txt_Crd(fix_4), gBossClr, TXT_SPD_ER, 1);
				ConsoleRender::Add_String(fix_5, Boss_Txt_Crd(fix_5, 1), gBossClr, TXT_SPD_ER, 1);
				ev_DumbDialogueFixer.Advance(500);
				break;

			case 8:
				ev_DumbDialogueFixer.Cancel();
				ev_WakeUp2.Advance(1000);
				break;
			}
	}
}