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


	// Random coordonn�es		 Si aucune boxside/coord n'est sp�cifi�, le spawn sera random
	extern bool gRandomSpwn, gRandomBoxSide;						
	extern bool gHorizontalSpawns, gVerticalSpawns, gAllSides;		
	extern BotType type;				
	extern int gNumSpawnTOT;				
	
	void Add(int amount);								 	// Ajoute des bots � spawner
	bool Set_Interval(Direction border, int min, int max);	// Setup un interval de coordonn�e pour 1 seule bordure
	void Set_Randomness();									// Quand tu change boxside ou SpwNum, cela affecte le randomness, il faut donc changer �a... manuellement
	void Reset_To_Default();								// Valeurs par d�faut du prochain spawn
	void Add_Spec(Direction boxSide, int crd);			// Ajoute une Coord sp�cific dans la liste des prochains bot � spawner
	bool Pop(SpwCrd& crd);								// "POP" une coord de spawn sp�cifique de la liste (:� partir du d�but)
	void Set_Custom_Bot(int delay, bool fixed = false, Colors color = WHITE, int hp = 1);	// Permet de set un bot custom

}


static bool Empty();		
static void Clear_List();  
