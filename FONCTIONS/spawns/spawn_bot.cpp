

#include "../bots/botlist.h"
#include "bots_to_spawn.h"
#include "find_next_spawn_crd.h"
#include "invalid_spwns.h"
#include "../grid/spawngrid.h"

#include "spawn_bot.h"



// Variables priv�es de liste
// --------------------------



// �a c'�tait pour les spawn block je crois
// Cr�ation des pointeurs pour la liste d'indice de coord de spawns invalide
static BotSpawner* deb = NULL, * fin = NULL, * it = NULL;		//	Pointe vers le d�but et la fin de la liste de Coord
static int cptr = 0;												// Le nombre spawns Coord Indice qu'on a v�rifi� comme �tant invalide
static int cptrInv = 0;												// Le nombre de spawn invalid� (ceux qui sont r�serv� pour un bot uniquement durant ce cycle)
static bool ValidCoord;

static SpwCrd spwCrd = {};


static void Spawn_Da_Bot_On_Da_Coord(SpwCrd crd)
{
	botList.Add_Bot(bots_to_spawn::type, crd, gCustomBot.is);	// Tous le m�me TYPE, ils ont
	// SpawnWarning Stuff???

}


void Spawn_Bot()
{
	for (int &i = bots_to_spawn::gNumSpawnTOT; i > 0; i--)
	{
		spwCrd = Find_Spwn_Coord();			//retourne le spawn
		Spawn_Da_Bot_On_Da_Coord(spwCrd);
		
		if(i > 1)	// Optimization
			InvalidSpwCrd::Add_Invalid_Coord_To_List(spwCrd);	// Add la crd in the "DO NOT SPAWN BOT HERE" list			On voudrais pas que deux bot spawn � la m�me place au m^^eme moment
	}

	InvalidSpwCrd::Empty_Invalid_Coord_List();	// SAFETY	: Vide la liste � chaque cycle de spawn
}


//
//void SpawnBOT()
//{		
//				// VALIDATION SPAWN!	
//
//				// V�RIFICATION DES �L�MENTS DANS LA LISTE des indices d�j� v�rifi�s
//				it = deb;
//
//				while (it) // ou tout simplement while (it)
//				{
//					if (Indice_Spawn_COORD == it->Ind)
//					{
//						ValidCoord = Spawn_Valide = false;				// La coordonn�e est invalide
//						break;
//					}
//					else
//						it = it->nxt;					// passe au prochain �l�ment
//				}
//
//				if (!ValidCoord)		// On recommence!
//					continue;
//
//				// YO SI CETTE LISTE EST AUSSI GRANDE QUE LE NOMBRE DE SPAWN COORD SUR UNE BORDURE, TU DEVRAIS CANCELLER LE 
//				// RESTE DES SPAWNS
//				// EN FAISANT BREAK; ET EN SETTANT LE NUMSPAWN � 0!
//
//				while (itXY) // ou tout simplement while (it)
//				{
//					if (NextSpawnXY == itXY->spwnXY)
//					{
//						ValidCoord = Spawn_Valide = false;				// La coordonn�e est invalide
//						break;
//					}
//					else
//						itXY = itXY->nxt;					// passe au prochain �l�ment
//				}
//
//				if (!ValidCoord)		// On recommence!
//					continue;
//
//				// Ceci v�rifie la pr�sence d'un front spawn block 
//				if (Check_Front_Spawn_If_Blocked(BoxSide, Indice_Spawn_COORD))
//				{
//					Spawn_Valide = false;
//					Random_Spawn_COORD = true;
//				}
//
//			} while (!Spawn_Valide);
//
//