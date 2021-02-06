

#include "valid_spwn_intervals.h"
#include "../grid/AllGrids.h"

#include "bots_to_spawn.h"

// RENSEIGNE SUR LES PROCHAINES COORD DE SPAWN POUR CE CYCLE
// *********************************************************

struct SpecificSpawn {	
	SpwCrd spwCrd;
	SpecificSpawn* nxt;
};

static SpecificSpawn* start = NULL, * end = NULL, * it = NULL;	

namespace bots_to_spawn {


	Direction gBoxSide = NONE;	
	int gSpwNum = -1;			
	GrdCoord nxtSpawn = {};		

	bool instantSpawn = false;	// Aucun warning de la part des bots
	bool gRandomSpwn = true;
	bool gRandomBoxSide = true;	
	bool gHorizontalSpawns = false, gVerticalSpawns = false, gAllSides = false;		
	BotType type = {};

	int gNumSpawnTOT = 0;
	int gAdditonnalSpawns = 0;			



	// Ajoute une Coord sp�cific dans la liste des prochains bot � spawner
	// -------------------------------------------------------------------

	void Add_Spec(Direction boxSide, int crd)			// spawn script � besoin de �a
	{
		if (end == NULL)	
			start = end = new SpecificSpawn;
		else
			end = end->nxt = new SpecificSpawn;	

		end->spwCrd.border = boxSide;
		end->spwCrd.spwNum = crd;
		end->nxt = NULL;

		gNumSpawnTOT++;
	}

	// Prend une coord de spawn sp�cifique de la liste
	// -----------------------------------------------

	bool Pop(SpwCrd& crd)		// find_next_spawn � besoin de �a
	{
		if (!Empty())		
		{
			it = start;
			crd.border = it->spwCrd.border;	
			crd.spwNum = it->spwCrd.spwNum;

			if (start == end)	
			{
				delete it;		
				start = end = it = NULL;
			}
			else
			{
				start = start->nxt;
				delete it;			
				it = NULL;	
			}
			return true;
		}
		else
			return false;
	}

	// // Valeurs par d�faut du prochain spawn
	// -----------------------------------------------
	void Reset_To_Default()		
	{
		 gBoxSide = NONE;	// -1	(0 est d�j� pris)
		 gSpwNum = -1;		
		 
		 instantSpawn = false;
		 gRandomSpwn = true;		
		 gRandomBoxSide = true;		
		 gHorizontalSpawns = false;	
		 gVerticalSpawns = false;	
		 gAllSides = true;			
		 type = BotType::REGULAR;	// I'll take a regular one please.

		gNumSpawnTOT = 0;			
		gAdditonnalSpawns = 0;		// Le nombre suppl�mentaire de spawn. Par d�faut, un sp�cific ajoute +1 au total de spawn durant ce cycle
	}

	// Setup un interval de coordonn�e
	// --------------------------------
	bool Set_Interval(Direction border, int min, int max)		// NOTE: Un interval peut �tre invalide si il est plus grand que le nombre de spawn sur une bordure
	{		
		if (spawnGrid->Is_Inbound(border, max - 1))			// Ne v�rifira pas si le min est valide.	:			Peut bugger si min < 0
		{
			ValidSpwnIntervals::Add_Primary_Interval(border, min, max);
			return true;	
		}
		else
			return false;	
	}

	// Ajoute des bots � spawner
	// -------------------------
	void Add(int amount)	
	{
		gNumSpawnTOT += amount;		
	}

	// Donne une valeur pr�cise � une coordonn�e, affecte le random
	// -------------------------------------------------------------

	void Set_Randomness() {				// Doit �tre utilis� qu'une seule fois par cycle
		
		// traitement du random
		if (gHorizontalSpawns || gVerticalSpawns)
			gAllSides = false;
		if (gBoxSide != -1)
			gRandomBoxSide = false;
		if (gSpwNum != -1 )
			gRandomSpwn = false;
	}
	void Set_Custom_Bot(int delay, bool fixed , Colors color , int hp )	
	{
		gCustomBot.health = hp;
		gCustomBot.clr = color;
		gCustomBot.fixedColor = fixed;
		gCustomBot.warningDelay = delay;
		gCustomBot.is = true;
	}


}

// EN DEHORS DU NAMESPACE
// **********************

bool Empty() {	
	return start == NULL;
}

void Clear_List() {

	if (it = start) {
		start = start->nxt;
		delete it;
	}

	it = start = end = NULL;	
}

