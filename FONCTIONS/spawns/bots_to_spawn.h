#pragma once 

#include "../bots/bot.h"
#include "../UI/direction.h"
#include "../grid/spawngrid.h"


struct Sp_CoordIn { int min; int max; bool active = false; };	 // Le prochain spawn aura oui/non une coord dans un interval

//variables globales dans un namespace?
namespace bots_to_spawn {

	// COORD
	extern Direction gBoxSide;	// Le c�t� de la box 
	extern int gSpwNum;			// Le combientieme spawn sur la bordure

	// Random coordonn�es		/ Si aucune boxside// coord n'est sp�cifi�, le spawn sera random
	extern bool gRandomSpwn, gRandomBoxSide;	// Le prochain bot spawnera sur une COORD Al�atoire
	extern bool gHorizontalBorder, gVerticalBorder, gAllSides;		// Le prochain spawn sera vertical, ou horizontal	
	extern BotType type;				// Le type de tout les bots du prochain spawn 
	extern int gNumSpawnTOT;			// Le nombre de spawns maximal durant un cycle de "Current_Spawn_Cycle"
	//extern Sp_CoordIn gCrdInterval;		// Donne un interval de coordonn�e sur une bordure
	
	void Add(int amount);		// 	// Ajoute des bots � spawner
	bool Set_Interval(Direction border, int min, int max);	// Setup un interval de coordonn�e pour 1 seule bordure
	void Set_Randomness();									// Quand tu change boxside ou SpwNum, cela affecte le randomness, il faut donc changer �a... manuellement
	void Reset_To_Default();								// Valeurs par d�faut du prochain spawn
	void Add_Spec(Direction boxSide, int crd);			// Ajoute une Coord sp�cific dans la liste des prochains bot � spawner
	bool Pop(SpwCrd& crd);	// "POP" une coord de spawn sp�cifique de la liste (:� partir du d�but)
	void Set_Custom_Bot(int delay, bool fixed = false, Colors color = WHITE, int hp = 1);	// Permet de set un bot custom

}


static bool Empty();		// liste vide
static void Clear_List();  // Vide la liste
