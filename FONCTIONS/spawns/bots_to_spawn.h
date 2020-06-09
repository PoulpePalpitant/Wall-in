#pragma once 

#include "../bots/bot.h"
#include "../UI/direction.h"
#include "../grid/spawngrid.h"


struct Sp_CoordIn { int min; int max; bool active = false; };	 // Le prochain spawn aura oui/non une coord dans un interval

//variables globales dans un namespace?
namespace bots_to_spawn {

	// COORD
	extern Direction gBoxSide;	// Le c�t� de la box 
	extern int gSpwNum;			// Le combientieme spawn sur la 

	// Random coordonn�es		/ Si aucune boxside// coord n'est sp�cifi�, le spawn sera random
	extern bool gRandomSpwn, gRandomBoxSide;	// Le prochain bot spawnera sur une COORD Al�atoire
	extern bool gHorizontalBorder, gVerticalBorder, Allsides;		// Le prochain spawn sera vertical, ou horizontal	
	extern BotType type;				// Le type de tout les bots du prochain spawn 
	extern int gNumSpawnTOT;			// Le nombre de spawns maximal durant un cycle de "Current_Spawn_Cycle"
	extern int gAdditonnalSpawns;		// Le nombre suppl�mentaire de spawn. Par d�faut, un sp�cific ajoute +1 au total de spawn durant ce cycle
	extern Sp_CoordIn gCrdInterval;		// Donne un interval de coordonn�e sur une bordure

	void Set_Interval(int min, int max);	// Setup un interval de coordonn�e
	void Reset_To_Default();				// Valeurs par d�faut du prochain spawn
	void Add_Specific(Direction boxSide, int crd);			// Ajoute une Coord sp�cific dans la liste des prochains bot � spawner
	bool Pop(SpwCrd& crd);	// "POP" une coord de spawn sp�cifique de la liste (:� partir du d�but)
}


static bool Empty();		// liste vide
static void Clear_List();  // Vide la liste
