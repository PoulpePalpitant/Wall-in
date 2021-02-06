#include "item_spawner.h"

#include "../grid/AllGrids.h"
#include "../player/player.h"
#include "item_list.h"
#include "item_spw_drawer.h"

Intervals::ManageIntervalLists ItemSpawner::availableLinks(0, 0, 0);	// Position disponibles dans le grid pour spawner des items
ItemSpawnPool ItemSpawner::pool = {};
bool ItemSpawner::pause = false;	


/*
	LES SPAWNS DISPONIBLES SONT LESQUELLES?

	L'intervalle manager fonctionne comme suit:
	Chaque liste représente une colonne du linkgrid :											instance[3] = colonne #3 dans le grid;
	Chaque valeurs présentes dans les intervalles de ces listes sont des row du Linkgrid:		instance[colonne].start.min	= 2(row);
	Ne pas oublier que la valeur max de chaque intervalles est tjrs ingorés
	Donc pour accéder à une coord :

	instance[5].start -> Start est un intervalle. Il contient une valeur min et max	: tout les valeurs >= à min et < max sont les rows disponibles
	instance[5].start.min = 2(row)		-> crd{5,2}
*/



bool ItemSpawner::Spawn_This_Item(ItemType type, GrdCoord crd, bool cancel, bool noanimation, bool rdmCoord)	// Bypass la pool et le timer pour faire spawner un item
{
	Item item;
	item.itemType = type;	// that's my type
	item.active = true;	// Activate that boi
	bool found = false;


	if (!ItemsOnGrid::Reached_Max())
	{
		availableLinks.Reset_All_Lists();	// refresh that shit
		Items_Exclusion();			

		if(!rdmCoord)
			if (Pick_Specific_Coord(crd))
			{
				availableLinks.Remove_Value(crd.c, crd.r);	
				if (!linkGrid->Is_Link_Alive_Here(crd))	
					found = true;
			}

		while (!found)
		{
			if (cancel)
				return false;	
			else
				if (!ItemSpawner::Find_Spawn_Location(crd))
					return false;	// we couldn't spawn yo shit
				else
					found = true;

			if (linkGrid->Is_Link_Alive_Here(crd))
				found = false;
		}

		item.grdCrd = crd;
		ItemsOnGrid::Add(item); 

		if (noanimation)
			DrawItemSpawnList::Draw_Item(item.itemType, item.grdCrd);
		else
			DrawItemSpawnList::Add(item.itemType, item.grdCrd);

		return true;
	}
	else
		return false;
}


bool ItemSpawner::Add_To_Pool(ItemType type, int timerSpeed, int rngDelay)
{
	TypeSpawner temp;

	for (int i = 0; i < pool.size; i++) 
	{
		if (pool.spawner[i].type == type)			
		{
			Set_Spawner_Timer(pool.spawner[i], timerSpeed, rngDelay);
			return false;
		}
	}

	for (int i = pool.size; i < MAX_ITEM_TYPE; i++)	
	{
		if (pool.spawner[i].type == type)
		{
			if (i != pool.size)	
			{
				temp = pool.spawner[i];						
				pool.spawner[i] = pool.spawner[pool.size];
				pool.spawner[pool.size] = temp;
			}

			Set_Spawner_Timer(pool.spawner[pool.size], timerSpeed, rngDelay);	
		}
	}

	pool.size++;						
	return true;
}

bool ItemSpawner::Remove_From_Pool(ItemType type)
{
	TypeSpawner temp;

	pool.size--;	

	for (int i = 0; i < pool.size; i++)
	{
		if (pool.spawner[i].type == type)			
		{
			temp = pool.spawner[i];	

			for (i; i < pool.size; i++)			
				pool.spawner[i] = pool.spawner[i + 1];
			
			pool.spawner[i] = temp;	
			return true;
		}
	}

	return false;
}
 void ItemSpawner::Init_Pool_Types()	
 {
	 for (int type = 0; type < MAX_ITEM_TYPE; type++)
		 pool.spawner[type].type = (ItemType)type;
 }

 // TIMERS
 // ------
 void ItemSpawner::Set_Spawner_Timer(TypeSpawner& spawner, int timerduration, int rngDelay)
 {
	 spawner.spwSpeed = timerduration;
	 spawner.rdmDelay = rngDelay;
	 spawner.timer.Start_Timer(timerduration);	
 }

 bool ItemSpawner::Set_Spawner_Timer(ItemType type, int timerduration, int rngDelay)
 {
	 TypeSpawner* spawner = NULL;

	 for (int i = 0; i < pool.size; i++)
	 {
		 if (pool.spawner[i].type == type)
			 spawner = &pool.spawner[i];
	 }

	 if (spawner)
	 {
		 spawner->spwSpeed = timerduration;
		 spawner->rdmDelay = rngDelay;
		 spawner->timer.Start_Timer(timerduration);	
		 return true;
	 }
	 else
		 return false;
 }

 TypeSpawner* ItemSpawner::Get_Spawner(ItemType type) 
 {
	 TypeSpawner* spawner = NULL;

	 for (int i = 0; i < pool.size; i++)
	 {
		 if (pool.spawner[i].type == type)			
			 return spawner = &pool.spawner[i];	
	 }

	return spawner;
 }



 int ItemSpawner::Add_Delay(TypeSpawner * spawner)	
 {
	 if (!spawner)
		 return 0 ;	

	 float delaySec;	

	 if (spawner->rdmDelay)
		 delaySec = rand() % spawner->rdmDelay;	
	 else
		 return 0;

	 return (int)(delaySec * 1000);
 }


void ItemSpawner::UPD_Item_Spawn_Timers()
{
	static int acceleration; acceleration = 0;
	static Item item;
	static bool setupSpawnList; setupSpawnList = false;

	for (int i = 0; i < pool.size; i++)
	{
		while (pool.spawner[i].timer.Tick())	
		{
			if (!ItemsOnGrid::Reached_Max())
			{
				if (!setupSpawnList)
				{
					Refresh_Available_Spawn_List();
					setupSpawnList = true;
				}

				if (ItemSpawner::Find_Spawn_Location(item.grdCrd))	// Si aucun spawn location found?? Spawn juste pas pour ce cycle 
				{
					item.active = true;	
					item.itemType = pool.spawner[i].type;		

					ItemsOnGrid::Add(item); // Add à la lsite des items sur le grid
					DrawItemSpawnList::Add(item.itemType, item.grdCrd);	// Add a la list du drawer de spawn
				}
			}

			pool.spawner[i].timer.Start_Timer(pool.spawner[i].spwSpeed,1, false, Add_Delay(&pool.spawner[i]));
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
void ItemSpawner::Blast_Exclusion(GrdCoord P1Pos)	
{
	availableLinks.Empty_List(P1Pos.c);				
	availableLinks.Remove_Value_Everywhere(P1Pos.r);	
}

//// Exclut les links occupés par des items
void ItemSpawner::Items_Exclusion()	
{
	GrdCoord crd;

	for (int i = 0; i < ItemsOnGrid::size; i++)
	{
		crd = ItemsOnGrid::items[i].Get_Grd_Coord();
		availableLinks.Remove_Value(crd.c, crd.r);
	}
}
void ItemSpawner::Refresh_Available_Spawn_List()		
{
	GrdCoord P1Pos = P1.Get_Grd_Coord();
	availableLinks.Reset_All_Lists();	
	Blast_Exclusion(P1Pos);		
	Player_Exclusion(P1Pos);	
	Items_Exclusion();			
}


bool ItemSpawner::Generate_Rdm_Coord(GrdCoord &itmCrd)	
{	
	return availableLinks.Pick_From_Lists(itmCrd.c, itmCrd.r, true, true, Intervals::RDM_ALL);	// si échoue, aucune coord n'est dispo
}

bool ItemSpawner::Pick_Specific_Coord(GrdCoord& itmCrd)	
{
	return availableLinks.Find_Value(itmCrd.c, itmCrd.r);	
}

bool ItemSpawner::Find_Spawn_Location(GrdCoord &itemCrd)
{
	bool validCrd = false;

	while (!validCrd)
	{
		if (Generate_Rdm_Coord(itemCrd))
		{
			if (!linkGrid->Is_Link_Alive_Here(itemCrd))	
				validCrd = true;
			else
				availableLinks.Remove_Value(itemCrd.c, itemCrd.r);
		}
		else
			return false;	
	}

	return true;
}

