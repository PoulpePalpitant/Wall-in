

#include "../grid/spawngrid.h"

#include "bots_to_spawn.h"

// RENSEIGNE SUR LES PROCHAINES COORD DE SPAWN POUR CE CYCLE
// *********************************************************

struct SpecificSpawn {	// Va servir à ajouter des spawns avec des Coordonnées spécifiques dans le scenario du niveau
	SpwCrd spwCrd;
	SpecificSpawn* nxt;
};

static SpecificSpawn* start = NULL, * end = NULL, * it = NULL;	// Pour créer une liste de Specific Spawn

namespace bots_to_spawn {

	Direction gBoxSide = NONE;	// ou int
	int gSpwNum = -1;			// le numéro
	GrdCoord nxtSpawn = {};		//ou ça
   
	bool gRandomSpwn = true;
	bool gRandomBoxSide = true;	// Le prochain bot spawnera sur une COORD Aléatoire
	bool gHorizontalBorder = false, gVerticalBorder = false, Allsides = false;		// Le prochain spawn sera vertical, ou horizontal	
	BotType type = {};

	int gNumSpawnTOT = 0;				// Le nombre de spawns maximal durant un cycle de "Current_Spawn_Cycle"
	int gAdditonnalSpawns = 0;			// Le nombre supplémentaire de spawn. Par défaut, un spécific ajoute +1 au total de spawn durant ce cycle

	Sp_CoordIn gCrdInterval = {};		// Donne un interval de coordonnée sur une bordure


	// Ajoute une Coord spécific dans la liste des prochains bot à spawner
	// -------------------------------------------------------------------

	void Add_Specific(Direction boxSide, int crd)			// spawn script à besoin de ça
	{
		if (end == NULL)	// list vide
			start = end = new SpecificSpawn;
		else
			end = end->nxt = new SpecificSpawn;	// ajout d'un élément

		end->spwCrd.border = boxSide;
		end->spwCrd.spwNum = crd;
		end->nxt = NULL;

		gNumSpawnTOT++;
	}

	// Prend une coord de spawn spécifique de la liste
	// -----------------------------------------------

	bool Pop(SpwCrd& crd)		// find_next_spawn à besoin de ça
	{
		if (!Empty())		// Prend l'objet en dessous et le retire de la liste
		{
			it = start;
			crd.border = it->spwCrd.border;	// Copie la valeure de la crd du spawn
			crd.spwNum = it->spwCrd.spwNum;

			if (start == end)	// Si ya juste 1 élément
			{
				delete it;			// et delete le spécific 
				start = end = it = NULL;	// On va reset tout les pointeurs
			}
			else
			{
				start = start->nxt;
				delete it;			// et delete le spécific 
				it = NULL;	// Reset pointeur
			}
			return true;
		}
		else
			return false;
	}

	// // Valeurs par défaut du prochain spawn
	// -----------------------------------------------
	void Reset_To_Default()		// Valeurs par défaut du prochain spawn
	{
		 gBoxSide = NONE;	// -1	(0 est déjà pris)
		 gSpwNum = -1;		// -1

		 gRandomSpwn = true;		// Spawn random
		 gRandomBoxSide = true;		// BoxSide random
		 gHorizontalBorder = false;	// Le prochain spawn sera horizontal	
		 gVerticalBorder = false;	// Le prochain spawn sera vertical	
		 type = BotType::REGULAR;	// I'll take a regular one please.

		gNumSpawnTOT = 1;			// Le nombre de spawns maximal durant un cycle de "Current_Spawn_Cycle"
		gAdditonnalSpawns = 0;		// Le nombre supplémentaire de spawn. Par défaut, un spécific ajoute +1 au total de spawn durant ce cycle

		gCrdInterval.active = false;// Donne un interval de coordonnée sur une bordure
	}

	// Setup un interval de coordonnée
	// --------------------------------
	void Set_Interval(int min, int max)		// NOTE: Un interval peut être invalide si il est plus grand que le nombre de spawn sur une bordure
	{
		gCrdInterval.min = min;
		gCrdInterval.max = max;
		gCrdInterval.active = true;
	}

}

// EN DEHORS DU NAMESPACE
// **********************


/// Empty stuff over here
//-----------------------
bool Empty() {	// liste vide
	return start == NULL;
}

// Clear la liste just au cas
// -------------------------
void Clear_List() { // Vide la liste

	if (it = start) {
		start = start->nxt;
		delete it;
	}

	it = start = end = NULL;	// bonne pratique
}

