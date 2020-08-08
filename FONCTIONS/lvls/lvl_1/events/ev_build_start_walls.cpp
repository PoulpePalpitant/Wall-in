
#include "ev_build_start_walls.h"


#include "../../../console/sweet_cmd_console.h"
#include "../../lvl_script.h"
#include "../../../events/events.h"
#include "../../../grid/AllGrids.h"
#include "../../../player/player.h"
#include "../../../UI/console_output/render_list.h"
#include "../../../time/movement_timer.h"
#include "../../../events/msg_dispatcher.h"
#include "../../../grid/AllGrids.h"

static GrdCoord startCrd;	// Pos en grdcord
static int row;
static int col;
static int numWalls;


void Build_Lvl_1_Walls()	// Fait appa^raître des murs pour aider le joueur
{
	// Premierère structure à gauche
	col = 0;
	row = linkGrid->Get_Rows() / 2;
	numWalls = 2;
	gGrids.Activate_Chain_Of_Walls({col, row}, RIGHT, numWalls);	// R R

	col++;
	gGrids.Activate_Chain_Of_Walls({ col, row }, UP, numWalls);		// UP
	gGrids.Activate_Chain_Of_Walls({ col, row }, DOWN, numWalls);		// UP

	// 2e structure à droite
	col = linkGrid->Get_Cols() - 1;
	gGrids.Activate_Chain_Of_Walls({ col, row }, LEFT, numWalls);	

	col--;
	gGrids.Activate_Chain_Of_Walls({ col, row }, UP, numWalls);		
	gGrids.Activate_Chain_Of_Walls({ col, row }, DOWN, numWalls);	
}