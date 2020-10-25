#pragma once 

#include "../bots/bot.h"
#include "../UI/direction.h"
#include "../grid/spawngrid.h"


struct Sp_CoordIn { int min; int max; bool active = false; };	 // Le prochain spawn aura oui/non une coord dans un interval

//variables globales dans un namespace?
namespace bots_to_spawn {

	// COORD
	extern Direction gBoxSide;	// Le côté de la box 
	extern int gSpwNum;			// Le combientieme spawn sur la bordure

	// Random coordonnées		/ Si aucune boxside// coord n'est spécifié, le spawn sera random
	extern bool gRandomSpwn, gRandomBoxSide;	// Le prochain bot spawnera sur une COORD Aléatoire
	extern bool gHorizontalBorder, gVerticalBorder, gAllSides;		// Le prochain spawn sera vertical, ou horizontal	
	extern BotType type;				// Le type de tout les bots du prochain spawn 
	extern int gNumSpawnTOT;			// Le nombre de spawns maximal durant un cycle de "Current_Spawn_Cycle"
	//extern Sp_CoordIn gCrdInterval;		// Donne un interval de coordonnée sur une bordure
	
	void Add(int amount);		// 	// Ajoute des bots à spawner
	bool Set_Interval(Direction border, int min, int max);	// Setup un interval de coordonnée pour 1 seule bordure
	void Set_Randomness();									// Quand tu change boxside ou SpwNum, cela affecte le randomness, il faut donc changer ça... manuellement
	void Reset_To_Default();								// Valeurs par défaut du prochain spawn
	void Add_Spec(Direction boxSide, int crd);			// Ajoute une Coord spécific dans la liste des prochains bot à spawner
	bool Pop(SpwCrd& crd);	// "POP" une coord de spawn spécifique de la liste (:à partir du début)
	void Set_Custom_Bot(int delay, bool fixed = false, Colors color = WHITE, int hp = 1);	// Permet de set un bot custom

}


static bool Empty();		// liste vide
static void Clear_List();  // Vide la liste
