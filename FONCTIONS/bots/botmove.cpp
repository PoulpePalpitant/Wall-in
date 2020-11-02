
#include "botlist.h"
#include "../grid/AllGrids.h"
#include "../player/player.h"
#include "botmeta.h"
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



void BotMove::Move_Bots()	//// On bouge tous les BOTS
{
	static Coord start, end;			// Pos départ et d'arrivée
	static Bot* bot;					// Itérateurs pour la liste de bots 
	static int toMove;					// Le nombre de bots à bouger
	static CoordIncrementor XY;			// Position du bot
	static GridIndexIncrementor grdCrd; // Position du bot
	static WallGrid* wallGrid;			// Le bon wall grid

	if (gAllBotMeta.alive == 0)	// Ain't nobody here
		return;

	toMove = gAllBotMeta.alive;		// nombre de bots à bouger au total
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
			grdCrd = bot->nxtWallCrd;									// Crd du prochain mur qu'il va percuter
			/*
			// Doit vérifier uniquement quand le bot entre dans le grid
			if (bot->stepCount >= 2)
				if (bot->Bot_Impact(&wallGrid->wall[bot->onAWall.c][bot->onAWall.r]))	// // Vérification qu'un wall n'a pas été créé par dessus le bot qu'on va bouger
				{
					wallGrid->wall[bot->onAWall.c][bot->onAWall.r].Remove_Bot_On_Me();	// bot est pati!
					continue;	// Si Oui, il y aura un impact!!
				}*/
	
			// Tu setup l'incrémenteur XY
			start = bot->XY;		// Coord de départ
			XY.Initialize_All(start, bot->dir);	// Inrémenteur de position
			XY.Increment_Coord();	// avance d'un mouvement
			end = XY.coord;	// Coord d'arrivée et nouvelle position du bot		// ça va pt chier

			// Enregistrement du mouvement au début de la loop
			bot->stepCount++;
			bot->stepLeft--;
			wallGrid->wall[bot->onAWall.c][bot->onAWall.r].Remove_Bot_On_Me();	// bot est pati!
			bot->onAWall = {};	// no more!

			if (!bot->fixedColor)	// pas couleur fixe
				bot->Upd_Progression_Color();	// Change la couleur du bot quand il s'approche de sa sortie

			Bot::Animate_Bot(bot, end);		// Erase and draw

			bot->XY = end; // Ceci est après, deal with it

			if (Bot_Is_On_WallGrid(bot))
			{
				/* Fait un impact. Si l'impact tue le bot, we continue */
				if (bot->Bot_Impact(&wallGrid->wall[grdCrd.index.c][grdCrd.index.r]))	// Im Pact!		
					continue;

				wallGrid->wall[grdCrd.index.c][grdCrd.index.r].Add_Bot_On_Me(b);	// Ajoute la position du bot 
				bot->onAWall = grdCrd.index;	// L'adresse du mur sur lequel le bot se trouve

				bot->nxtWallCrd.Increment_Coord();	/*ou it->nxtWallcrd*/			// Prochain wall que le bot va percuter
				bot->Strt_Nxt_Wall_Time();									// et le temps que ça va prendre
			}
			else
				bot->Upd_Nxt_Wall_Time();	// Réduit de un mouvement le temps que ça va prendre pour se rendre au prochain wall

			if (!bot->stepLeft)	// Le bot est sortie de la box!
			{
				// BIG EDIT!	:	Les bot one shot le joueur
				//**********
				P1.Player_Lose_HP(P1.Get_HP());	// OUCH
				bot->Destroy_Bot();

				/* ME RÉPÈTE*/
				toMove--;	// 1 bot de moins à bouger

				if (!toMove)	// pu yin à bouger
					break;

				continue;	// NÉCESSAIRE. Quand tu détruit, ton ptr est automatiquement assigné au suivant
				// if dead, continue, else keep going

				/*// On Détruit(enfin) un BOT et tout les blockages de spawn qu'il a engendré
				Destroy_BOT_and_Spawn_Blocks(bot, front_Spawn_COORD[bot]);*/
			}
		}

		toMove--;	// 1 bot de moins à bouger

		if (!toMove)	// pu yin à bouger
			break;

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