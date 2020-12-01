
#include "ev_build_labyrinth.h"


#include "../../../console/sweet_cmd_console.h"
#include "../../lvl_script.h"
#include "../../../events/events.h"
#include "../../../grid/AllGrids.h"
#include "../../../player/player.h"
#include "../../../UI/console_output/render_list.h"
#include "../../../time/movement_timer.h"
#include "../../../events/msg_dispatcher.h"
#include "../../../grid/AllGrids.h"
#include "../../../events/global_events/feedback/ev_draw_map.h"
#include "../../../global_types/global_types.h"
#include "../../../events/global_events/clear_all_states.h"
#include "../../../events/global_events/feedback/ev_red_borders.h"


static Event ev_BuildLabyrinth(Ev_Build_Labyrinth, 20); // Def //

static std::string escape = "Do You Ever Feel Trapped?   ";
static std::string adv = "Adventure Here";

static std::string obj = "You Don't Belong Here";
static std::string obj2 = "Escape This Place...   ";

static std::string goal1 = "These Walls...   ";
static std::string goal2 = "Can't Contain You!";

static std::string menacing1 = "There Is No Escape";
static std::string menacing2 = "You Built These Walls";



// Tous ce que j'ai de besoin pour constuire le labyrinthe
static int rootR;	// Row de la root
static int rootC;	// Colonne de la root
static int numWalls;
static Direction dir;

// Chaque start de walls doit être fait sur une root, je peux juste pas faire ça ligne par ligne

void Ev_Build_Labyrinth()		// Le joueur doit passer à travers un labyrinth de murs pour obtenir ce qu'il désir
{
	static Modifier mod = REGULAR;

	//Just_Dr_Map_Borders();	// Pour m'orienter quand je build
	if (!ev_BuildLabyrinth.Is_Active())
	{

		ConsoleRender::Add_String(escape, { Find_Ctr_X(escape.size()), gConHeight / 2 }, WHITE, TXT_SPD_DR * 0.9);
		ev_BuildLabyrinth.Activate();
		ev_BuildLabyrinth.Start(250);
	}
	else
		while (ev_BuildLabyrinth.delay.Tick())
		{
			switch (ev_BuildLabyrinth.Get_Current_Step())
			{
			case 1:
				//wait for game title to erase
				ConsoleRender::Add_String(escape, { Find_Ctr_Grid(escape), gConHeight / 2 }, WHITE, TXT_SPD_ER * 2,1);
				MsgQueue::Register(SPAWN_PLAYER);	// spawn le player 
				ev_BuildLabyrinth.Advance(900);
				break;

			case 2:
				// Je commence le design dans le coin supérieur gauche
				rootC = 0;	rootR = 0; 		// Origin
				gGrids.Make_Chain_Of_Walls({ rootC, rootR + 1 }, RIGHT, 1);
				gGrids.Make_Chain_Of_Walls({ rootC + 1, rootR }, DOWN, 1);
				gGrids.Make_Chain_Of_Walls({ rootC + 1, rootR + 1 }, DOWN, 1);
				gGrids.Make_Chain_Of_Walls({ rootC + 1, rootR + 1 }, LEFT, 1);
				gGrids.Make_Chain_Of_Walls({ rootC + 1, rootR + 2 }, DOWN, 1);
				gGrids.Make_Chain_Of_Walls({ rootC + 1, rootR + 2 }, LEFT, 1);
				gGrids.Make_Chain_Of_Walls({ rootC + 1, rootR + 3 }, DOWN, 1);
				gGrids.Make_Chain_Of_Walls({ rootC + 1, rootR + 3 }, LEFT, 1);
				//gGrids.Make_Chain_Of_Walls({ rootC + 1, rootR + 4 }, LEFT, 1);	

				rootC = 1;	rootR = 0; 		// Origin
				gGrids.Make_Chain_Of_Walls({ rootC  , rootR }, LEFT, 1);

				rootC = 2;	rootR = 4; 		// Origin
				gGrids.Make_Chain_Of_Walls({ rootC, rootR }, UP, 1);
				gGrids.Make_Chain_Of_Walls({ rootC, rootR - 1 }, UP, 1);
				gGrids.Make_Chain_Of_Walls({ rootC, rootR - 2 }, UP, 1);
				gGrids.Make_Chain_Of_Walls({ rootC, rootR - 3 }, UP, 1);
				gGrids.Make_Chain_Of_Walls({ rootC, rootR - 4 }, UP, 1);
				gGrids.Make_Chain_Of_Walls({ rootC, rootR - 4 }, LEFT, 1);

				//rootC = 4;	rootR = 0; 	numWalls = 2;	// Origin
				//gGrids.Make_Chain_Of_Walls({ rootC, rootR }, RIGHT, 1);
				//gGrids.Make_Chain_Of_Walls({ rootC, rootR }, DOWN, numWalls);
				//gGrids.Make_Chain_Of_Walls({ rootC + 1, rootR }, DOWN, 1);


				rootC = 6;	rootR = 1; 		// Origin
				gGrids.linkGrd.link[rootC][rootR].Activate_Link(mod);	// 1 link tu seul
				gGrids.linkGrd.link[rootC][rootR].Dsp_Link();

				rootC = 6;	rootR = 2; 		// Origin
				gGrids.linkGrd.link[rootC][rootR].Activate_Link(mod);	// 1 link tu seul
				gGrids.linkGrd.link[rootC][rootR].Dsp_Link();
				//gGrids.Activate_Blocker({ rootC ,rootR });

				// modifying here
				rootC = 3;	rootR = 0; numWalls = 3;		// Origin
				gGrids.Make_Chain_Of_Walls({ rootC, rootR }, DOWN, numWalls);
				gGrids.Make_Chain_Of_Walls({ rootC, rootR + numWalls }, RIGHT, 1);
				gGrids.Make_Chain_Of_Walls({ rootC + 1, rootR + numWalls }, DOWN, 1);
				gGrids.Make_Chain_Of_Walls({ rootC + 1, rootR + numWalls + 1 }, LEFT, 1);
				//

				rootC = 0;	rootR = 5; numWalls = 2;		// Origin
				gGrids.Make_Chain_Of_Walls({ rootC, rootR }, RIGHT, numWalls);
				gGrids.Make_Chain_Of_Walls({ rootC, rootR }, UP, 1);
				gGrids.Make_Chain_Of_Walls({ rootC + numWalls, rootR }, DOWN, 1);
				gGrids.Make_Chain_Of_Walls({ rootC + numWalls, rootR + 1 }, LEFT, 1);

				rootC = 0;	rootR = 6; numWalls = 3;		// Origin
				gGrids.Make_Chain_Of_Walls({ rootC, rootR }, DOWN, 1);
				gGrids.Make_Chain_Of_Walls({ rootC, rootR + 1 }, RIGHT, numWalls);	numWalls = 2;	// numwalls was edit here
				gGrids.Make_Chain_Of_Walls({ rootC, rootR + 1 }, DOWN, numWalls);
				gGrids.Make_Chain_Of_Walls({ rootC + 1, rootR + 1 }, DOWN, numWalls);
				gGrids.Make_Chain_Of_Walls({ rootC + 2, rootR + 1 }, DOWN, numWalls);
				gGrids.Make_Chain_Of_Walls({ rootC + 3, rootR + 1 }, DOWN, numWalls);

				rootC = 3;	rootR = 6; 	numWalls = 3;	// Origin
				gGrids.Make_Chain_Of_Walls({ rootC, rootR }, RIGHT, 1);
				gGrids.Make_Chain_Of_Walls({ rootC + 1, rootR }, DOWN, numWalls);
				gGrids.Make_Chain_Of_Walls({ rootC + 1, rootR }, UP, 1);

				rootC = 3;	rootR = 5; 		// Origin
//				gGrids.Activate_Blocker({ rootC ,rootR });
				gGrids.linkGrd.link[rootC][rootR].Activate_Link(mod);	// 1 link tu seul
				gGrids.linkGrd.link[rootC][rootR].Dsp_Link();

				//rootC = 6;	rootR = 6; 	numWalls = 3;	// Origin	// fuck
				//gGrids.Make_Chain_Of_Walls({ rootC, rootR }, UP, 1);
				//gGrids.Make_Chain_Of_Walls({ rootC, rootR }, LEFT, 1);
				//gGrids.Make_Chain_Of_Walls({ rootC, rootR  - 1}, UP, 1);
				//gGrids.Make_Chain_Of_Walls({ rootC, rootR - 1}, LEFT, 1);
				//gGrids.Make_Chain_Of_Walls({ rootC - 1, rootR }, DOWN, numWalls);
				//gGrids.Make_Chain_Of_Walls({ rootC - 1, rootR - 1}, UP, 1);
				//gGrids.Make_Chain_Of_Walls({ rootC, rootR - 2 },RIGHT , 1);
				//gGrids.Make_Chain_Of_Walls({ rootC + 1, rootR - 2 },UP, 1);
				//gGrids.Make_Chain_Of_Walls({ rootC + 1, rootR - 3 },LEFT, 2);
				//gGrids.Make_Chain_Of_Walls({ rootC - 1, rootR - 3 },UP, 1);
				//gGrids.Make_Chain_Of_Walls({ rootC - 1, rootR - 4 },LEFT, 1);
				//gGrids.Make_Chain_Of_Walls({ rootC - 2, rootR - 4 },UP, 2);
				//gGrids.Make_Chain_Of_Walls({ rootC - 2, rootR - 6},RIGHT, 1);
				//gGrids.Make_Chain_Of_Walls({ rootC - 1, rootR - 6},DOWN, 1);

				rootC = 6;	rootR = 0; 	numWalls = 2;		// Origin
				gGrids.Make_Chain_Of_Walls({ rootC, rootR }, LEFT, numWalls);
				gGrids.Make_Chain_Of_Walls({ rootC - 1 , rootR }, DOWN, 1);
				gGrids.Make_Chain_Of_Walls({ rootC - numWalls , rootR }, DOWN, numWalls);
				gGrids.Make_Chain_Of_Walls({ rootC - numWalls, rootR + numWalls }, RIGHT, 1);
				gGrids.Make_Chain_Of_Walls({ rootC - 1, rootR + numWalls }, DOWN, 1);
				gGrids.Make_Chain_Of_Walls({ rootC - 1, rootR + numWalls + 1 }, RIGHT, numWalls);
				gGrids.Make_Chain_Of_Walls({ rootC + 1, rootR + numWalls + 1 }, DOWN, 1);
				gGrids.Make_Chain_Of_Walls({ rootC + 1, rootR + numWalls + 1 + 1 }, LEFT, 1);
				gGrids.Make_Chain_Of_Walls({ rootC , rootR + numWalls + 1 + 1 }, DOWN, 1);
				gGrids.Make_Chain_Of_Walls({ rootC , rootR + numWalls + 3 }, DOWN, 1);
				gGrids.Make_Chain_Of_Walls({ rootC , rootR + numWalls + 4 }, LEFT, 1);
				gGrids.Make_Chain_Of_Walls({ rootC - 1, rootR + numWalls + 4 }, UP, 2);
				gGrids.Make_Chain_Of_Walls({ rootC , rootR + numWalls + 4 }, LEFT, 1);
				gGrids.Make_Chain_Of_Walls({ rootC - 1, rootR + numWalls + 4 }, DOWN, 3);

				rootC = 8;	rootR = 0; 	numWalls = 2;	// Origin
				gGrids.Make_Chain_Of_Walls({ rootC, rootR }, DOWN, numWalls);
				gGrids.Make_Chain_Of_Walls({ rootC, rootR + numWalls }, LEFT, 1);
				gGrids.Make_Chain_Of_Walls({ rootC - 1, rootR + numWalls }, UP, 1);
				gGrids.Make_Chain_Of_Walls({ rootC, rootR + numWalls }, RIGHT, 1);
				gGrids.Make_Chain_Of_Walls({ rootC + 1, rootR + numWalls }, UP, numWalls);
				gGrids.Make_Chain_Of_Walls({ rootC + 1, rootR }, RIGHT, 1);
				gGrids.Make_Chain_Of_Walls({ rootC + numWalls, rootR }, DOWN, 1);
				gGrids.Make_Chain_Of_Walls({ rootC + numWalls, rootR + 1 }, RIGHT, 1);
				gGrids.Make_Chain_Of_Walls({ rootC + numWalls + 1, rootR + 1 }, DOWN, 1);

				rootC = 12;	rootR = 0; 	//origin
				gGrids.Make_Chain_Of_Walls({ rootC, rootR }, LEFT, 1);

				rootC = 12;	rootR = 3; 	//origin
				gGrids.Make_Chain_Of_Walls({ rootC, rootR }, UP, 2);
				gGrids.Make_Chain_Of_Walls({ rootC, rootR }, LEFT, 1);
				gGrids.Make_Chain_Of_Walls({ rootC, rootR }, DOWN, 2);

				rootC = 11;	rootR = 4; 	//origin
				//gGrids.Make_Chain_Of_Walls({ rootC, rootR }, LEFT, 1);
				gGrids.Make_Chain_Of_Walls({ rootC, rootR }, DOWN, 2);
				gGrids.Make_Chain_Of_Walls({ rootC, rootR - 2 }, RIGHT, 1);
				gGrids.Make_Chain_Of_Walls({ rootC + 1, rootR + 2 }, DOWN, 3);
				gGrids.Make_Chain_Of_Walls({ rootC , rootR + 2 }, RIGHT, 1);
				gGrids.Make_Chain_Of_Walls({ rootC + 1, rootR + 3 }, LEFT, 1);
				gGrids.Make_Chain_Of_Walls({ rootC + 1, rootR + 4 }, LEFT, 2);
				gGrids.Make_Chain_Of_Walls({ rootC , rootR + 4 }, DOWN, 1);
				gGrids.Make_Chain_Of_Walls({ rootC - 1, rootR + 4 }, DOWN, 1);
				gGrids.Make_Chain_Of_Walls({ rootC, rootR + 2 }, LEFT, 3);
				gGrids.Make_Chain_Of_Walls({ rootC - 1, rootR + 2 }, UP, 2);
				gGrids.Make_Chain_Of_Walls({ rootC - 1, rootR + 1 }, LEFT, 1);
				//gGrids.Make_Chain_Of_Walls({ rootC - 2, rootR + 2}, UP, 1);
				gGrids.Make_Chain_Of_Walls({ rootC - 3, rootR + 2 }, DOWN, 3);

				rootC = 8;	rootR = 3;	numWalls = 2;	//origin
				gGrids.Make_Chain_Of_Walls({ rootC, rootR }, RIGHT, numWalls);
				gGrids.Make_Chain_Of_Walls({ rootC + 1, rootR }, DOWN, 1);
				gGrids.Make_Chain_Of_Walls({ rootC + numWalls , rootR }, UP, 1);

				rootC = 8;	rootR = 5;		//origin
				gGrids.Make_Chain_Of_Walls({ rootC, rootR }, UP, 1);
				gGrids.Make_Chain_Of_Walls({ rootC , rootR }, LEFT, 1);
				gGrids.Make_Chain_Of_Walls({ rootC - 1, rootR }, DOWN, 4);
				gGrids.Make_Chain_Of_Walls({ rootC - 1, rootR + 2 }, LEFT, 1);
				gGrids.Make_Chain_Of_Walls({ rootC - 2, rootR + 2 }, DOWN, 2);

				rootC = 10;	rootR = 7;		//origin
				gGrids.Make_Chain_Of_Walls({ rootC, rootR }, LEFT, 1);
				gGrids.Make_Chain_Of_Walls({ rootC - 1, rootR }, DOWN, 2);


				rootC = 5;	rootR = 14;	numWalls = 5;	//origin
				gGrids.Make_Chain_Of_Walls({ rootC, rootR }, LEFT, numWalls);
				gGrids.Make_Chain_Of_Walls({ rootC, rootR }, UP, 2);

				rootC = 4;	rootR = 13;		//origin
				gGrids.Make_Chain_Of_Walls({ rootC, rootR }, UP, 1);

				rootC = 0;	rootR = 13;	numWalls = 3;	//origin
				gGrids.Make_Chain_Of_Walls({ rootC, rootR }, RIGHT, numWalls);

				rootC = 2;	rootR = 10;	numWalls = 5;	//origin
				gGrids.Make_Chain_Of_Walls({ rootC, rootR }, RIGHT, numWalls);

				rootC = 4;	rootR = 11;		//origin
				gGrids.Make_Chain_Of_Walls({ rootC, rootR }, LEFT, 4);
				gGrids.Make_Chain_Of_Walls({ rootC - 4, rootR }, UP, 1);
				gGrids.Make_Chain_Of_Walls({ rootC - 3, rootR }, DOWN, 1);
				gGrids.Make_Chain_Of_Walls({ 0 , rootR - 1 }, RIGHT, 1);
				gGrids.Make_Chain_Of_Walls({ 1 , rootR + 1 }, LEFT, 1);
				gGrids.Make_Chain_Of_Walls({ rootC - 3, rootR - 1 }, LEFT, 1);
				gGrids.Make_Chain_Of_Walls({ rootC - 2, rootR }, DOWN, 1);
				gGrids.Make_Chain_Of_Walls({ rootC - 2, rootR + 1 }, RIGHT, 1);
				//gGrids.Activate_Blocker({ rootC - 1, rootR + 1 });
				gGrids.Make_Chain_Of_Walls({ rootC - 2, rootR + 1 }, LEFT, 1);

				rootC = 7;	rootR = 14;	numWalls = 5;	//origin
				gGrids.Make_Chain_Of_Walls({ rootC, rootR }, UP, 2);
				gGrids.Make_Chain_Of_Walls({ rootC, rootR }, RIGHT, numWalls);

				rootC = 8;	rootR = 13;		//origin
				gGrids.Make_Chain_Of_Walls({ rootC, rootR }, UP, 1);

				rootC = 11;	rootR = 10;		//origin
				gGrids.Make_Chain_Of_Walls({ rootC, rootR }, LEFT, 2);
				gGrids.Make_Chain_Of_Walls({ rootC - 1, rootR }, DOWN, 2);
				gGrids.Make_Chain_Of_Walls({ rootC - 1, rootR + 2 }, LEFT, 1);
				gGrids.Make_Chain_Of_Walls({ rootC - 2, rootR + 2 }, UP, 1);
				gGrids.Make_Chain_Of_Walls({ rootC - 2, rootR + 1 }, LEFT, 4);
				gGrids.Make_Chain_Of_Walls({ rootC - 5, rootR + 1 }, DOWN, 2);
				gGrids.Make_Chain_Of_Walls({ rootC - 3, rootR + 1 }, UP, 1);

				rootC = 12;	rootR = 10;		//origin
				gGrids.Make_Chain_Of_Walls({ rootC, rootR }, DOWN, 1);
				gGrids.Make_Chain_Of_Walls({ rootC, rootR + 1 }, LEFT, 1);
				gGrids.Make_Chain_Of_Walls({ rootC - 1, rootR + 1 }, DOWN, 1);
				gGrids.Make_Chain_Of_Walls({ rootC - 1, rootR + 2 }, RIGHT, 1);
				gGrids.Make_Chain_Of_Walls({ rootC , rootR + 2 }, DOWN, 1);
				gGrids.Make_Chain_Of_Walls({ rootC , rootR + 3 }, LEFT, 3);
				//gGrids.Make_Chain_Of_Walls({ rootC , rootR }, UP, 1, WallStrength::REGULAR, REGULAR, true);// CONNECTEUR

				ConsoleRender::Add_Char(linkGrid->link[7][0].Get_XY(), TXT_CONST.SPACE_FILL, LIGHT_AQUA);
				ConsoleRender::Add_String(adv, { Find_Ctr_String_X(adv) + 3,START_Y -2 }, LIGHT_GREEN);
					

				ev_BuildLabyrinth.Advance(1000);
				break;


			case 3:
				ConsoleRender::Add_String(obj,  Heart_Txt_Crd_Left(obj), LIGHT_GREEN, TXT_SPD_DR);
				ev_BuildLabyrinth.Advance(600);
				break;

			case 4:
				ConsoleRender::Add_String(obj2, Heart_Txt_Crd_Right(obj), LIGHT_GREEN, TXT_SPD_DR);
				ev_BuildLabyrinth.Advance(250);
				break;

			case 5:
				ConsoleRender::Add_String(obj, Heart_Txt_Crd_Left(obj), LIGHT_GREEN, TXT_SPD_ER,1);
				ConsoleRender::Add_String(obj2, Heart_Txt_Crd_Right(obj), LIGHT_GREEN, TXT_SPD_ER,1);

				ev_BuildLabyrinth.Advance(0);
				ev_BuildLabyrinth.delay.Start_Timer(100000, 1, true);
				break;	
			
			//case 6:
			//	if (P1.Get_Grd_Coord().r == 8)
			//	{
			//	ConsoleRender::Add_String(goal1, { Heart_Txt_Crd_Left(goal1)}, LIGHT_GREEN, TXT_SPD_DR );
			//	ev_BuildLabyrinth.delay.Stop();
			//	ev_BuildLabyrinth.Advance(500);
			//	}
			//	break;

			//case 7:
			//	ConsoleRender::Add_String(goal2, { Heart_Txt_Crd_Right(goal2) }, LIGHT_GREEN, TXT_SPD_DR);
			//	ev_BuildLabyrinth.Advance(400);
			//	break;

			//case 8:
			//	ConsoleRender::Add_String(goal1, { Heart_Txt_Crd_Left(goal1) }, LIGHT_GREEN, TXT_SPD_ER,1);
			//	ConsoleRender::Add_String(goal2, { Heart_Txt_Crd_Right(goal2) }, LIGHT_GREEN, TXT_SPD_ER,1);
			//	ev_BuildLabyrinth.Advance(400);
			//	ev_BuildLabyrinth.delay.Start_Timer(100000, 1, true);
			//	break;


			case 6:
				if (Are_Equal(P1.Get_Grd_Coord(), { 7,1 }) || Are_Equal(P1.Get_Grd_Coord(), { 6,0 }))	// Le goal à reach pour le labyrinthe
				{
					Clear_Map();
					Clear_All_Renders();
					clrscr();
					P1.Dr_Player();
					Set_Ev_Red_Borders(200);

					//MsgQueue::Register(LOCK_PLAYER);
					MsgQueue::Register(DISABLE_BLAST);
					ev_BuildLabyrinth.delay.Stop();
					ev_BuildLabyrinth.Advance(1000);
				}
				break;

			case 7:
				ConsoleRender::Add_String(menacing1, { Find_Ctr_Grid(menacing1), gConHeight / 2 - 10 }, LIGHT_RED, 0);
				ev_BuildLabyrinth.Advance(600);
				break;

			case 8:
				ConsoleRender::Add_String(menacing2, { Find_Ctr_Grid(menacing2), gConHeight / 2 - 8 }, LIGHT_RED, 0);
				ev_BuildLabyrinth.Advance(400);
				break;

			case 9:
				Cancel_Ev_Red_Borders();
				clrscr();
				MsgQueue::Register(STAGE_ADVANCE);
				ev_BuildLabyrinth.Advance(0);
				ev_BuildLabyrinth.delay.Start_Timer(100000, 1, true);
				break;
			}
		}

}