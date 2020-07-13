#include "item_spawner.h"

#include "../grid/AllGrids.h"
#include "../player/player.h"
#include "item_list.h"
#include "item_spw_drawer.h"

Intervals::ManageIntervalLists ItemSpawner::availableLinks(0, 0, 0);	// Position disponibles dans le grid pour spawner des items
ItemSpawnPool ItemSpawner::pool = {};
bool ItemSpawner::pause = false;	// permet de pauser les updates

bool ItemSpawner::Add_To_Pool(ItemType type, int timerSpeed, int rngDelay)
{
	TypeSpawner temp;

	for (int i = 0; i < pool.size; i++)
	{
		if (pool.spawner[i].type== type)			// Était déjà dans la pool
			return false;
	}

	for (int i = pool.size; i < MAX_ITEM_TYPE; i++)
	{
		if (pool.spawner[i].type == type)
		{
			if (i != pool.size)	// Si n'était pas simplement le prochain
			{
				temp = pool.spawner[i];						// Switch l'ordre
				pool.spawner[i] = pool.spawner[pool.size];
				pool.spawner[pool.size] = temp;
			}

			Set_Spawner_Timer(pool.spawner[pool.size], timerSpeed, rngDelay);	// set le nouveau timer
		}
	}

	pool.size++;						// Plus 1
	return true;
}

bool ItemSpawner::Remove_From_Pool(ItemType type)
{
	TypeSpawner temp;

	pool.size--;	//	1 de moins

	for (int i = 0; i < pool.size; i++)
	{
		if (pool.spawner[i].type == type)			// décale tout les autres items
		{
			temp = pool.spawner[i];	// temp

			for (i; i < pool.size; i++)			
				pool.spawner[i] = pool.spawner[i + 1];
			
			pool.spawner[i] = temp;	// restore
			return true;
		}
	}

	return false;
}
 void ItemSpawner::Init_Pool_Types()	// Initialize la pool avec tout les types actuel. Devrait être fait 1 seul fois?
 {
	 for (int type = 0; type < MAX_ITEM_TYPE; type++)
		 pool.spawner[type].type = (ItemType)type;
 }
 void ItemSpawner::Set_Spawner_Timer(TypeSpawner& spawner, int timerduration, int rngDelay)
 {
	 spawner.spwSpeed = timerduration;
	 spawner.rdmAcceleration = rngDelay;
	 spawner.timer.Start_Timer(timerduration);	// start le timer aussi?
 }


// TIMERS
void ItemSpawner::UPD_Item_Spawn_Timers()
{
	static int acceleration; acceleration = 0;
	static Item item;
	static bool setupSpawnList; setupSpawnList = false;

	for (int i = 0; i < pool.size; i++)
	{
		while (pool.spawner[i].timer.Tick())	// si le tick finis
		{
			if (!ItemsOnGrid::Reached_Max())
			{
				if (!setupSpawnList)
				{
					Refresh_Available_Spawn_List();
					setupSpawnList = true;
				}

				// Generate random coord
				if (ItemSpawner::Find_Spawn_Location(item.grdCrd))	// Si aucun spawn location found?? Spawn juste pas pour ce cycle 
				{

					item.active = true;	// Activate that boi
					item.itemType = pool.spawner[i].type;		// le bon type

					ItemsOnGrid::Add(item); // Add à la lsite des items sur le grid
					DrawItemSpawnList::Add(item.itemType, item.grdCrd);	// Add a la list du drawer de spawn
				}
			}

			// Reset timer avec extra sauce(delay random)
			if (pool.spawner[i].rdmAcceleration)
				acceleration = rand() % pool.spawner[i].rdmAcceleration;	// prochain timer sera accéléré ...
			else
				acceleration = 0;

				pool.spawner[i].timer.Start_Timer(pool.spawner[i].spwSpeed + acceleration);
		}
	}
}

 // EXCLUSION
// ----------
// va retirer les spawns qui seraient vrmt trop proches du joueur
void ItemSpawner::Player_Exclusion(GrdCoord P1Pos)	
{
	availableLinks.Remove_Value(P1Pos.c - 1, P1Pos.r + 1);	// Retire le spw à 1 case en diagonale du joueur
	availableLinks.Remove_Value(P1Pos.c - 1, P1Pos.r - 1);
	availableLinks.Remove_Value(P1Pos.c + 1, P1Pos.r - 1);
	availableLinks.Remove_Value(P1Pos.c + 1, P1Pos.r - 1);
}

// On voudrait pas spawner 1 item sur la même ligne qu'un blast, serait moche
void ItemSpawner::Blast_Exclusion(GrdCoord P1Pos)	// Thats a long name
{
	availableLinks.Empty_List(P1Pos.c);				// Remove tout les spawn sur la même colonne
	availableLinks.Remove_Value_Everywhere(P1Pos.r);	// vide la row
}

//// Exclut les links occupés par des items
void ItemSpawner::Items_Exclusion()	// 
{
	GrdCoord crd;

	for (int i = 0; i < ItemsOnGrid::size; i++)
	{
		crd = ItemsOnGrid::items[i].Get_Grd_Coord();
		availableLinks.Remove_Value(crd.c, crd.r);	//yey
	}
}
void ItemSpawner::Refresh_Available_Spawn_List()		// Refresh le trouver de spawn libre
{
	GrdCoord P1Pos = P1.Get_Grd_Coord();
	availableLinks.Reset_All_Lists();	// refresh that shit
	Blast_Exclusion(P1Pos);		// Exclut d'abord les coord irrecevable
	Player_Exclusion(P1Pos);	// Exclut 1 case tout autours du joueur
	Items_Exclusion();			// Exclut les items déjà présents
}


bool ItemSpawner::Generate_Rdm_Coord(GrdCoord &itmCrd)	// Trouve une coord. si non-dispo, en trouve une autre au hasard
{	
	return availableLinks.Pick_From_Lists(itmCrd.c, itmCrd.r, true, true, Intervals::RDM_ALL);	// si échoue, aucune coord n'est dispo
}

bool ItemSpawner::Find_Spawn_Location(GrdCoord &itemCrd)
{
	bool validCrd = false;

	while (!validCrd)
	{
		if (Generate_Rdm_Coord(itemCrd))
		{
			if (!linkGrid->Is_Link_Here(itemCrd))	// Trouvé une coord !
				validCrd = true;
			else
				availableLinks.Remove_Value(itemCrd.c, itemCrd.r);	// gotta remove it	?
		}
		else
			return false;	// Plus de coord disponibles dans le grid
	}

	// Liste 4 Exclut tout les autres invalidés par les Links
	return true;
}

