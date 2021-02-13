
#include "initialize_game.h"
#include "../items/item_spawner.h"
#include "../player/player_move.h"


void Initialize_Game()	// Initialize tout plein de shit qui ont pas rapport ensemble. Un peu mieux que d'avoir des variables globales doe
{
	ItemSpawner::Init_Pool_Types();	// Content qu'il y est pas grand chose ici finalement
}

