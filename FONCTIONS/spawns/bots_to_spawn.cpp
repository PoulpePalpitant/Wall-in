

#include "valid_spwn_intervals.h"
//#include "../grid/spawngrid.h"
#include "../grid/AllGrids.h"

#include "bots_to_spawn.h"

// RENSEIGNE SUR LES PROCHAINES COORD DE SPAWN POUR CE CYCLE
// *********************************************************

struct SpecificSpawn {	// Va servir � ajouter des spawns avec des Coordonn�es sp�cifiques dans le scenario du niveau
	SpwCrd spwCrd;
	SpecificSpawn* nxt;
};

static SpecificSpawn* start = NULL, * end = NULL, * it = NULL;	// Pour cr�er une liste de Specific Spawn

namespace bots_to_spawn {

	Direction gBoxSide = NONE;	// ou int
	int gSpwNum = -1;			// le num�ro
	GrdCoord nxtSpawn = {};		//ou �a
   
	bool gRandomSpwn = true;
	bool gRandomBoxSide = true;	// Le prochain bot spawnera sur une COORD Al�atoire
	bool gHorizontalBorder = false, gVerticalBorder = false, gAllSides = false;		// Le prochain spawn sera vertical, ou horizontal	
	BotType type = {};

	int gNumSpawnTOT = 0;				// Le nombre de spawns maximal durant un cycle de "Current_Spawn_Cycle"
	int gAdditonnalSpawns = 0;			

	Sp_CoordIn gCrdInterval = {};		// Donne un interval de coordonn�e sur une bordure


	// Ajoute une Coord sp�cific dans la liste des prochains bot � spawner
	// -------------------------------------------------------------------

	void Add_Specific(Direction boxSide, int crd)			// spawn script � besoin de �a
	{
		if (end == NULL)	// list vide
			start = end = new SpecificSpawn;
		else
			end = end->nxt = new SpecificSpawn;	// ajout d'un �l�ment

		end->spwCrd.border = boxSide;
		end->spwCrd.spwNum = crd;
		end->nxt = NULL;

		gNumSpawnTOT++;
	}

	// Prend une coord de spawn sp�cifique de la liste
	// -----------------------------------------------

	bool Pop(SpwCrd& crd)		// find_next_spawn � besoin de �a
	{
		if (!Empty())		// Prend l'objet en dessous et le retire de la liste
		{
			it = start;
			crd.border = it->spwCrd.border;	// Copie la valeure de la crd du spawn
			crd.spwNum = it->spwCrd.spwNum;

			if (start == end)	// Si ya juste 1 �l�ment
			{
				delete it;			// et delete le sp�cific 
				start = end = it = NULL;	// On va reset tout les pointeurs
			}
			else
			{
				start = start->nxt;
				delete it;			// et delete le sp�cific 
				it = NULL;	// Reset pointeur
			}
			return true;
		}
		else
			return false;
	}

	// // Valeurs par d�faut du prochain spawn
	// -----------------------------------------------
	void Reset_To_Default()		// Valeurs par d�faut du prochain spawn
	{
		 gBoxSide = NONE;	// -1	(0 est d�j� pris)
		 gSpwNum = -1;		// -1

		 gRandomSpwn = true;		// Spawn random
		 gRandomBoxSide = true;		// BoxSide random
		 gHorizontalBorder = false;	// Le prochain spawn sera horizontal	
		 gVerticalBorder = false;	// Le prochain spawn sera vertical	
		 gAllSides = true;			// Spawn sur une bordure random
		 type = BotType::REGULAR;	// I'll take a regular one please.

		gNumSpawnTOT = 1;			// Le nombre de spawns maximal durant un cycle de "Current_Spawn_Cycle"
		gAdditonnalSpawns = 0;		// Le nombre suppl�mentaire de spawn. Par d�faut, un sp�cific ajoute +1 au total de spawn durant ce cycle

		gCrdInterval.active = false;// Donne un interval de coordonn�e sur une bordure
	}

	// Setup un interval de coordonn�e
	// --------------------------------
	bool Set_Interval(Direction border, int min, int max)		// NOTE: Un interval peut �tre invalide si il est plus grand que le nombre de spawn sur une bordure
	{		
		if (spawnGrid->Is_Inbound(border, max))			// Ne v�rifira pas si le min est valide.	:			Peut bugger si min < 0
		{
			ValidSpwnIntervals::Add_Primary_Interval(border, min, max);
			return true;	// valid stuf
		}
		else
			return false;	// ain't gonna work
	}

	// Ajoute des bots � spawner
	// -------------------------
	void Add_Spwns(int amount)		// Le nombre suppl�mentaire de spawn. Par d�faut, un sp�cific ajoute +1 au total de spawn durant ce cycle
	{
		gNumSpawnTOT += amount;		
	}

	// Donne une valeur pr�cise � une coordonn�e, affecte le random
	// -------------------------------------------------------------

	void Set_Randomness() {				// Doit �tre utilis� qu'une seule fois par cycle
		
		// traitement du random
		if (gHorizontalBorder || gVerticalBorder)
			gAllSides = false;
		if (gBoxSide != -1)
			gRandomBoxSide = false;
		if (gSpwNum != -1 )
			gRandomSpwn = false;
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

