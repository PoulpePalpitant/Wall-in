
#include "botlist.h"
#include "../grid/AllGrids.h"
#include "../player/player.h"

#include "botmove.h"

// �A SE PEUT QUE J'AILLE � FAIRE �A:

//// Ceci r�affiche les bots pour �viter leur disparition quand il sont proche 
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
	static Coord start, end;	// Pos d�part et d'arriv�e
	static Bot* bot, *prev;				// It�rateurs pour la liste de bots et son pr�c�dant
	static CoordIncrementor XY;// Position du bot
	static GridIndexIncrementor grdCrd;// Position du bot
	static WallGrid* wallGrid;	// Le bon wall grid

	prev = NULL;	// Le bot pr�c�dant
	bot = botList.pBotStrt;	// Le d�but de la liste: le premier bot

	while (bot)		// Temps qu'on a pas atteint la fin de la liste 
	{
		// Tu setup l'incr�menteur XY
		start = bot->XY;		// Coord de d�part
		XY.Initialize_All(start, bot->dir);	// Inr�menteur de position
		XY.Increment_Coord();	// avance d'un mouvement
		end = XY.coord;	// Coord d'arriv�e et nouvelle position du bot		// �a va pt chier
		
		// Enregistrement du mouvement au d�but de la loop
		bot->stepCount++;
		bot->stepLeft--;
		
		if(!bot->fixedColor)	// pas couleur fixe
			bot->Upd_Progression_Color();	// Change la couleur du bot quand il s'approche de sa sortie

		Bot::Animate_Bot(bot, end);		// Erase and draw
		
		bot->XY = end; // Ceci est apr�s, deal with it

		grdCrd = bot->nxtWallCrd;									// Crd du prochain mur qu'il va percuter
		wallGrid = gGrids.Find_Wall_Grid_From_Axis(Find_Opp_Axis(bot->dir));	// trouve le grid que le bot va traverser	/*IMPORTANT*/ Le grid que le Bot va traverser sera Perpendiculaire � celui-ci!
		
		if (Bot_Is_On_WallGrid(bot))
		{
			if (wallGrid->Is_Wall_here(grdCrd.index))
			{
				/* Fait un impact. Si l'impact tue le bot, we continue */
				if(Bot::Bot_Impact(bot, prev, &wallGrid->wall[grdCrd.index.c][grdCrd.index.r]))	// Im Pact!		
					continue;	
			}					

			bot->nxtWallCrd.Increment_Coord();	/*ou it->nxtWallcrd*/			// Prochain wall que le bot va percuter
			bot->Strt_Nxt_Wall_Time();									// et le temps que �a va prendre
		}
		else		
			bot->Upd_Nxt_Wall_Time();	// R�duit de un mouvement le temps que �a va prendre pour se rendre au prochain wall
		

		if (!bot->stepLeft)	// Le bot est sortie de la box!
		{
			P1.Player_Lose_HP();	// OUCH
			botList.Destroy_Bot(bot, prev);
			continue;	// N�CESSAIRE. Quand tu d�truit, ton ptr est automatiquement assign� au suivant
			// if dead, continue, else keep going

			/*// On D�truit(enfin) un BOT et tout les blockages de spawn qu'il a engendr�
			Destroy_BOT_and_Spawn_Blocks(bot, front_Spawn_COORD[bot]);*/
		}

		prev = bot;
		bot = bot->pNext; 		// Passe au prochain bot mon ami!

	} 
}


bool BotMove::Bot_Is_On_WallGrid(const Bot* const bot)	// �a check �a
{
	// CHECK: si le bot se trouve sur le Wall grid 

	if (bot->tillNxtWall == 0)	// Next Wall repr�sente le nombre de loop restant avant que le bot se trouve � nouveau sur le Wallgrid
		return true;
	else
		return false;


}