
#include "botlist.h"
#include "../grid/AllGrids.h"
#include "../player/player.h"
#include "botmeta.h"
#include "botmove.h"

void BotMove::Move_Bots()	//// On bouge tous les BOTS
{
	static Coord start, end;			// Pos d�part et d'arriv�e
	static Bot* bot;					// It�rateurs pour la liste de bots 
	static int toMove;					// Le nombre de bots � bouger
	static CoordIncrementor XY;			// Position du bot
	static GridIndexIncrementor grdCrd; // Position du bot
	static WallGrid* wallGrid;			// Le bon wall grid

	if (gAllBotMeta.alive == 0)	// Ain't nobody here
		return;

	toMove = gAllBotMeta.alive;		// nombre de bots � bouger au total
	if (gAllBotMeta.dead == 1)
		gAllBotMeta.dead = 1;

	for (int b = 0; b < MAX_NUM_BOTS; b++)
	{
		bot = &botList.bot[b];	// Le bot � bouger

		if (bot->Is_Dead())		// Un bot dead ne bouge pas
			continue;

		// Si le warning est actif, on ne bouge pas le bot, on affiche le warning � la place
		if (bot->spwnWarning.Show_Spawn_Warning())
			bot->UI_Dis_Warning();
		else
		{
			wallGrid = gGrids.Find_Wall_Grid_From_Axis(Find_Opp_Axis(bot->dir));	// trouve le grid que le bot va traverser	/*IMPORTANT*/ Le grid que le Bot va traverser sera Perpendiculaire � celui-ci!
			grdCrd = bot->nxtWallCrd;											
	
			start = bot->XY;		
			XY.Initialize_All(start, bot->dir);
			XY.Increment_Coord();	// avance d'un mouvement
			end = XY.coord;			// Coord d'arriv�e et nouvelle position du bot		

			// Enregistrement du mouvement au d�but de la loop
			bot->stepCount++;
			bot->stepLeft--;
			wallGrid->wall[bot->onAWall.c][bot->onAWall.r].Remove_Bot_On_Me();	// bot est pati!
			bot->onAWall = {};	// no more!

			if (!bot->fixedColor)	
				bot->Upd_Progression_Color();	// Change la couleur du bot quand il s'approche de sa sortie

			Bot::Animate_Bot(bot, end);		// Erase and draw

			bot->XY = end; // Ceci est apr�s, deal with it

			if (Bot_Is_On_WallGrid(bot))
			{
				if (bot->Bot_Impact(&wallGrid->wall[grdCrd.index.c][grdCrd.index.r]))	
					continue;

				wallGrid->wall[grdCrd.index.c][grdCrd.index.r].Add_Bot_On_Me(b);	// Ajoute la position du bot 
				bot->onAWall = grdCrd.index;	// L'adresse du mur sur lequel le bot se trouve

				bot->nxtWallCrd.Increment_Coord();	/*ou it->nxtWallcrd*/			// Prochain wall que le bot va percuter
				bot->Strt_Nxt_Wall_Time();									// et le temps que �a va prendre
			}
			else
				bot->Upd_Nxt_Wall_Time();	// R�duit de un mouvement le temps que �a va prendre pour se rendre au prochain wall

			if (!bot->stepLeft)	// Le bot est sortie de la box!
			{
				P1.Player_Lose_HP(P1.Get_HP());	// OUCH
				bot->Destroy_Bot();

				toMove--;	// 1 bot de moins � bouger

				if (!toMove)	// pu yin � bouger
					break;

				continue;	// N�CESSAIRE. Quand tu d�truit, ton ptr est automatiquement assign� au suivant
			}
		}
		toMove--;	

		if (!toMove)	
			break;

	}
}


bool BotMove::Bot_Is_On_WallGrid(const Bot* const bot)	
{
	if (bot->tillNxtWall == 0)	// Next Wall repr�sente le nombre de loop restant avant que le bot se trouve � nouveau sur le Wallgrid
		return true;
	else
		return false;
}