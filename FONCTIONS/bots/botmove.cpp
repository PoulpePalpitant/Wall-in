
#include "botlist.h"
#include "../grid/AllGrids.h"
#include "../player/player.h"

#include "botmove.h"

// ÇA SE PEUT QUE J'AILLE À FAIRE ÇA:

//// Ceci réaffiche les bots pour éviter leur disparition quand il sont proche 
//for (int bot = 0; bot < MaxNumBOTS; ++bot)
//{
//	if (BOTXY[bot] != 0)
//	{
//		if (UPD_BOT_Warning_Cycles(bot))
//			UI_AF_BOT_Warning(bot);
//		else
//			Afficher_ou_Effacer_BOT(bot, EffacerBOT);
//	}
//}
//



void BotMove::Move_Bots()
{
	static Coord start, end;	// Pos départ et d'arrivée
	static Bot* bot, *prev;				// Itérateurs pour la liste de bots et son précédant
	static CoordIncrementor XY;// Position du bot
	static GridIndexIncrementor grdCrd;// Position du bot
	static WallGrid* wallGrid;	// Le bon wall grid

	prev = NULL;	// Le bot précédant
	bot = botList.pBotStrt;	// Le début de la liste: le premier bot

	while (bot)		// Temps qu'on a pas atteint la fin de la liste 
	{
		// Tu setup l'incrémenteur XY
		start = bot->XY;		// Coord de départ
		XY.Initialize_All(start, bot->dir);	// Inrémenteur de position
		XY.Increment_Coord();	// avance d'un mouvement
		end = XY.coord;	// Coord d'arrivée et nouvelle position du bot		// ça va pt chier
		
		// Enregistrement du mouvement au début de la loop
		bot->stepCount++;
		bot->stepLeft--;
		
		if(!bot->fixedColor)	// pas couleur fixe
			bot->Upd_Progression_Color();	// Change la couleur du bot quand il s'approche de sa sortie

		Bot::Animate_Bot(bot, end);		// Erase and draw
		
		bot->XY = end; // Ceci est après, deal with it

		grdCrd = bot->nxtWallCrd;									// Crd du prochain mur qu'il va percuter
		wallGrid = gGrids.Find_Wall_Grid_From_Axis(Find_Opp_Axis(bot->dir));	// trouve le grid que le bot va traverser	/*IMPORTANT*/ Le grid que le Bot va traverser sera Perpendiculaire à celui-ci!
		
		if (Bot_Is_On_WallGrid(bot))
		{
			if (wallGrid->Is_Wall_here(grdCrd.index))
			{
				/* Fait un impact. Si l'impact tue le bot, we continue */
				if(Bot::Bot_Impact(bot, prev, &wallGrid->wall[grdCrd.index.c][grdCrd.index.r]))	// Im Pact!		
					continue;	
			}					

			bot->nxtWallCrd.Increment_Coord();	/*ou it->nxtWallcrd*/			// Prochain wall que le bot va percuter
			bot->Strt_Nxt_Wall_Time();									// et le temps que ça va prendre
		}
		else		
			bot->Upd_Nxt_Wall_Time();	// Réduit de un mouvement le temps que ça va prendre pour se rendre au prochain wall
		

		if (!bot->stepLeft)	// Le bot est sortie de la box!
		{
			P1.Player_Lose_HP();	// OUCH
			botList.Destroy_Bot(bot, prev);
			continue;	// NÉCESSAIRE. Quand tu détruit, ton ptr est automatiquement assigné au suivant
			// if dead, continue, else keep going

			/*// On Détruit(enfin) un BOT et tout les blockages de spawn qu'il a engendré
			Destroy_BOT_and_Spawn_Blocks(bot, front_Spawn_COORD[bot]);*/
		}

		prev = bot;
		bot = bot->pNext; 		// Passe au prochain bot mon ami!

	} 
}


bool BotMove::Bot_Is_On_WallGrid(const Bot* const bot)	// ça check ça
{
	// CHECK: si le bot se trouve sur le Wall grid 

	if (bot->tillNxtWall == 0)	// Next Wall représente le nombre de loop restant avant que le bot se trouve à nouveau sur le Wallgrid
		return true;
	else
		return false;


}