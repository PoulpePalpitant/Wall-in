#include "botmove.h"

#include "botlist.h"
#include "../grid/AllGrids.h"
#include "../player/player.h"
#include "botmeta.h"

void BotMove::Move_Bots()	//// On bouge tous les BOTS
{
	static Coord start, end;			
	static Bot* bot;					 
	static int toMove;					
	static CoordIncrementor XY;			
	static GridIndexIncrementor grdCrd; 
	static WallGrid* wallGrid;			

	if (gAllBotMeta.alive == 0)	
		return;

	toMove = gAllBotMeta.alive;	
	if (gAllBotMeta.dead == 1)
		gAllBotMeta.dead = 1;

	for (int b = 0; b < MAX_NUM_BOTS; b++)
	{
		bot = &botList.bot[b];	// Le bot à bouger

		if (bot->Is_Dead())		// Un bot dead ne bouge pas
			continue;

		// Si le warning est actif, on ne bouge pas le bot, on affiche le warning à la place
		if (bot->spwnWarning.Show_Spawn_Warning())
			bot->UI_Dis_Warning();
		else
		{
			wallGrid = gGrids.Find_Wall_Grid_From_Axis(Find_Opp_Axis(bot->dir));	// trouve le grid que le bot va traverser	/*IMPORTANT*/ Le grid que le Bot va traverser sera Perpendiculaire à celui-ci!
			grdCrd = bot->nxtWallCrd;											
	
			start = bot->XY;		
			XY.Initialize_All(start, bot->dir);
			XY.Increment_Coord();	// avance d'un mouvement
			end = XY.coord;			

			bot->stepCount++;
			bot->stepLeft--;
			wallGrid->wall[bot->onAWall.c][bot->onAWall.r].Remove_Bot_On_Me();	
			bot->onAWall = {};

			if (!bot->fixedColor)	
				bot->Upd_Progression_Color();	// Change la couleur du bot quand il s'approche de sa sortie

			Bot::Animate_Bot(bot, end);		

			bot->XY = end; // Ceci est après, deal with it

			if (Bot_Is_On_WallGrid(bot))
			{
				if (bot->Bot_Impact(&wallGrid->wall[grdCrd.index.c][grdCrd.index.r]))	
					continue;

				wallGrid->wall[grdCrd.index.c][grdCrd.index.r].Add_Bot_On_Me(b);	
				bot->onAWall = grdCrd.index;

				bot->nxtWallCrd.Increment_Coord();	
				bot->Strt_Nxt_Wall_Time();			
			}
			else
				bot->Upd_Nxt_Wall_Time();	

			if (!bot->stepLeft)	// Le bot est sortie de la box!
			{
				P1.Player_Lose_HP(P1.Get_HP());	// OUCH
				bot->Destroy_Bot();

				toMove--;	

				if (!toMove)	
					break;

				continue;	// NÉCESSAIRE. Quand tu détruit, ton ptr est automatiquement assigné au suivant
			}
		}
		toMove--;	

		if (!toMove)	
			break;

	}
}


bool BotMove::Bot_Is_On_WallGrid(const Bot* const bot)	
{
	if (bot->tillNxtWall == 0)	
		return true;
	else
		return false;
}