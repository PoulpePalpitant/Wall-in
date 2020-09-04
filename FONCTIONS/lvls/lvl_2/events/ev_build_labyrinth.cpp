
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

// Tous ce que j'ai de besoin pour constuire le labyrinthe
static int rootR;	// Row de la root
static int rootC;	// Colonne de la root
static int numWalls;
static Direction dir;

// Chaque start de walls doit être fait sur une root, je peux juste pas faire ça ligne par ligne

void Ev_Build_Labyrinth()		// Le joueur doit passer à travers un labyrinth de murs pour obtenir ce qu'il désir
{
	//Just_Dr_Map_Borders();	// Pour m'orienter quand je build

	int maxC = gGrids.linkGrd.Get_Cols();
	int maxR = gGrids.linkGrd.Get_Rows();
	Coord xy;
	Modifier mod = REGULAR;

	rootR = 0;
	for (int c = 0; c < maxC; c++)	// Affiche Le Link grid
	{
		xy = gGrids.linkGrd.link[c][rootR].Get_XY(); ConsoleRender::Add_String(std::to_string(c), xy);
	}

	rootC = 0;
	for (int r = 0; r < maxR; r++)
	{
		xy = gGrids.linkGrd.link[rootC][r].Get_XY(); ConsoleRender::Add_String(std::to_string(r), xy);
	}


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

	// modifying here
	rootC = 3;	rootR = 0; numWalls = 3;		// Origin
	gGrids.Make_Chain_Of_Walls({ rootC, rootR  }, DOWN, numWalls);
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
	gGrids.Make_Chain_Of_Walls({ rootC, rootR + 1}, DOWN, numWalls);
	gGrids.Make_Chain_Of_Walls({ rootC + 1, rootR + 1}, DOWN, numWalls);
	gGrids.Make_Chain_Of_Walls({ rootC + 2, rootR + 1}, DOWN, numWalls);
	gGrids.Make_Chain_Of_Walls({ rootC + 3, rootR + 1}, DOWN, numWalls);

	rootC = 3;	rootR = 6; 	numWalls = 3;	// Origin
	gGrids.Make_Chain_Of_Walls({ rootC, rootR }, RIGHT, 1);
	gGrids.Make_Chain_Of_Walls({ rootC + 1, rootR }, DOWN, numWalls);
	gGrids.Make_Chain_Of_Walls({ rootC + 1, rootR }, UP, 1);

	rootC = 3;	rootR = 5; 		// Origin
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
	gGrids.Make_Chain_Of_Walls({ rootC - numWalls, rootR  + numWalls }, RIGHT, 1);
	gGrids.Make_Chain_Of_Walls({ rootC - 1, rootR  + numWalls }, DOWN, 1);
	gGrids.Make_Chain_Of_Walls({ rootC - 1, rootR  + numWalls + 1 }, RIGHT, numWalls);
	gGrids.Make_Chain_Of_Walls({ rootC + 1, rootR  + numWalls + 1 }, DOWN, 1);
	gGrids.Make_Chain_Of_Walls({ rootC + 1, rootR  + numWalls + 1 + 1 }, LEFT, 1);
	gGrids.Make_Chain_Of_Walls({ rootC , rootR  + numWalls + 1 + 1 }, DOWN, 1);
	gGrids.Make_Chain_Of_Walls({ rootC , rootR  + numWalls + 3 }, DOWN, 1);
	gGrids.Make_Chain_Of_Walls({ rootC , rootR  + numWalls + 4 }, LEFT, 1);
	gGrids.Make_Chain_Of_Walls({ rootC - 1, rootR  + numWalls + 4 }, UP, 2);
	gGrids.Make_Chain_Of_Walls({ rootC , rootR  + numWalls + 4 }, LEFT, 1);
	gGrids.Make_Chain_Of_Walls({ rootC - 1, rootR  + numWalls + 4 }, DOWN, 3);

	rootC = 8;	rootR = 0; 	numWalls = 2;	// Origin
	gGrids.Make_Chain_Of_Walls({ rootC, rootR }, DOWN, numWalls);
	gGrids.Make_Chain_Of_Walls({ rootC, rootR + numWalls }, LEFT, 1);
	gGrids.Make_Chain_Of_Walls({ rootC - 1, rootR + numWalls }, UP, 1);
	gGrids.Make_Chain_Of_Walls({ rootC, rootR + numWalls }, RIGHT, 1);
	gGrids.Make_Chain_Of_Walls({ rootC + 1, rootR + numWalls }, UP, numWalls);
	gGrids.Make_Chain_Of_Walls({ rootC + 1, rootR }, RIGHT, 1);
	gGrids.Make_Chain_Of_Walls({ rootC + numWalls, rootR}, DOWN, 1);
	gGrids.Make_Chain_Of_Walls({ rootC + numWalls, rootR + 1}, RIGHT, 1);
	gGrids.Make_Chain_Of_Walls({ rootC + numWalls + 1, rootR + 1}, DOWN, 1);

	rootC = 12;	rootR = 0; 	//origin
	gGrids.Make_Chain_Of_Walls({ rootC, rootR }, LEFT, 1);

	rootC = 12;	rootR = 3; 	//origin
	gGrids.Make_Chain_Of_Walls({ rootC, rootR }, UP, 2);
	gGrids.Make_Chain_Of_Walls({ rootC, rootR }, LEFT, 1);
	gGrids.Make_Chain_Of_Walls({ rootC, rootR }, DOWN, 2);

	rootC = 11;	rootR = 4; 	//origin
	//gGrids.Make_Chain_Of_Walls({ rootC, rootR }, LEFT, 1);
	gGrids.Make_Chain_Of_Walls({ rootC, rootR }, DOWN, 2);
	gGrids.Make_Chain_Of_Walls({ rootC, rootR - 2}, RIGHT, 1);
	gGrids.Make_Chain_Of_Walls({ rootC + 1, rootR + 2}, DOWN, 3);
	gGrids.Make_Chain_Of_Walls({ rootC , rootR + 2}, RIGHT, 1);
	gGrids.Make_Chain_Of_Walls({ rootC + 1, rootR + 3 }, LEFT, 1);
	gGrids.Make_Chain_Of_Walls({ rootC + 1, rootR + 4 }, LEFT, 2);
	gGrids.Make_Chain_Of_Walls({ rootC , rootR + 4 }, DOWN, 1);
	gGrids.Make_Chain_Of_Walls({ rootC - 1, rootR + 4 }, DOWN, 1);
	gGrids.Make_Chain_Of_Walls({ rootC, rootR + 2}, LEFT, 3);
	gGrids.Make_Chain_Of_Walls({ rootC - 1, rootR + 2}, UP, 2);
	gGrids.Make_Chain_Of_Walls({ rootC - 1, rootR + 1}, LEFT, 1);
	//gGrids.Make_Chain_Of_Walls({ rootC - 2, rootR + 2}, UP, 1);
	gGrids.Make_Chain_Of_Walls({ rootC - 3, rootR + 2}, DOWN, 3);

	rootC = 8;	rootR = 3;	numWalls = 2;	//origin
	gGrids.Make_Chain_Of_Walls({ rootC, rootR }, RIGHT, numWalls);
	gGrids.Make_Chain_Of_Walls({ rootC + 1, rootR }, DOWN, 1);
	gGrids.Make_Chain_Of_Walls({ rootC + numWalls , rootR }, UP, 1);

	rootC = 8;	rootR = 5;		//origin
	gGrids.Make_Chain_Of_Walls({ rootC, rootR }, UP, 1);
	gGrids.Make_Chain_Of_Walls({ rootC , rootR }, LEFT, 1);
	gGrids.Make_Chain_Of_Walls({ rootC - 1, rootR }, DOWN, 4);
	gGrids.Make_Chain_Of_Walls({ rootC - 1, rootR + 2}, LEFT, 1);
	gGrids.Make_Chain_Of_Walls({ rootC - 2, rootR + 2}, DOWN, 2);

	rootC = 10;	rootR = 7;		//origin
	gGrids.Make_Chain_Of_Walls({ rootC, rootR }, LEFT, 1);
	gGrids.Make_Chain_Of_Walls({ rootC - 1, rootR }, DOWN, 2);
}