#pragma once 

#include "../bots/bot.h"
#include "../UI/direction.h"
#include "../grid/spawngrid.h"



//variables globales dans un namespace?
namespace bots_to_spawn {

	// COORD
	extern Direction gBoxSide;	
	extern int gSpwNum;			// Le combientieme spawn sur la bordure

	extern bool instantSpawn;	// Aucun warning de la part des bots


	// Random coordonnées		 Si aucune boxside/coord n'est spécifié, le spawn sera random
	extern bool gRandomSpwn, gRandomBoxSide;						
	extern bool gHorizontalSpawns, gVerticalSpawns, gAllSides;		
	extern BotType type;				
	extern int gNumSpawnTOT;				
	
	void Add(int amount);								 	// Ajoute des bots à spawner
	bool Set_Interval(Direction border, int min, int max);	// Setup un interval de coordonnée pour 1 seule bordure
	void Set_Randomness();									// Quand tu change boxside ou SpwNum, cela affecte le randomness, il faut donc changer ça... manuellement
	void Reset_To_Default();								// Valeurs par défaut du prochain spawn
	void Add_Spec(Direction boxSide, int crd);			// Ajoute une Coord spécific dans la liste des prochains bot à spawner
	bool Pop(SpwCrd& crd);								// "POP" une coord de spawn spécifique de la liste (:à partir du début)
	void Set_Custom_Bot(int delay, bool fixed = false, Colors color = WHITE, int hp = 1);	// Permet de set un bot custom

}


static bool Empty();		
static void Clear_List();  
