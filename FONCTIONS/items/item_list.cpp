
#include "item_list.h"
#include "../blast/blast.h"
#include "../blast/blast_modifier_queue.h"
#include "item_spw_drawer.h"
#include "../events/msg_dispatcher.h"
#include "../player/player.h"
#include "item_spawner.h"

Item ItemsOnGrid::items[MAX_ITEMS] = {};
int ItemsOnGrid::size;	// dimension de la liste

bool ItemsOnGrid::Is_Item_Here(GrdCoord crd)	// 
{
	for (int i = 0; i < size; i++)
	{
		if (Are_Equal(items[i].Get_Grd_Coord(), crd))
			return true;
	}
	return false;
}

 void ItemsOnGrid::Remove(int index){
 
	 items[index].active = false;

	 for (int i = index; i < size; i++)		// Décale tout
		 items[i] = items[i + 1];

	 size--;
 }

 void ItemsOnGrid::Remove_All()
 {
	 for (int i = 0; i < MAX_ITEMS; i++)		// Décale tout»
	 {
		 if (!(items[i].grdCrd.c > linkGrid->Get_Cols() || items[i].grdCrd.c < 0 || items[i].grdCrd.r > linkGrid->Get_Rows() || items[i].grdCrd.r < 0)) // hehe, fuck you
			 linkGrid->link[items[i].grdCrd.c][items[i].grdCrd.r].Er_Link();
		 else
			 throw "hehehe";

		 items[i] = {};	// erase tout anyway
	 }
	 size = 0;
 }

 bool ItemsOnGrid::Add(Item& item)
 {
	 if (size == MAX_ITEMS)
		 return false;
	 else
	 {
		 size++;
		 Item::meta.Item_Spawned();

		 for (int i = 0; i < size; i++)
		 {
			 if (!items[i].Is_Active())				// ou item[i] = item info?
			 {
				 items[i] = item;
				 break;
			 }
		 }

		 return true;

	 }
 }

 bool ItemsOnGrid::Is_Item_Modifier(Item& item)
 {
	 switch (item.Get_Type())
	 {
	 case ItemType::REGULAR:
	 case ItemType::CORRUPTED:
	 case ItemType::BLOCKER:
	 case ItemType::BUFFER:
	 return true;
	 }

	 return false;
 }




void ItemsOnGrid::Pickup_Item_Here(GrdCoord crd)
{
	for (int i = 0; i < size; i++)
	{
		if (Are_Equal(items[i].Get_Grd_Coord(), crd))
		{

			if (Is_Item_Modifier(items[i]))
			{
				if (blastP1.Is_Active() && blastP1.Get_Modifier() == Modifier::REGULAR)
					blastP1.Setup_Modifier((Modifier)items[i].Get_Type());		// change le blast actuel
				else
					BlastModifierQueue::Add_Modifier((Modifier)items[i].Get_Type());		// Ajoute l'item à la blast modifier queue
			}
			else
			{
				if (items[i].Get_Type() == ItemType::AMMO)	// 10 ammo
					blastP1.Get_Ammo_Manager().Add_Ammo(10);
				else
					if (items[i].Get_Type() == ItemType::HEALTH)
						P1.Player_Gains_HP();	// 1 de vie
			}
			// Cancel l'animation de spawn ssi y elle avait lieux
			DrawItemSpawnList::Cancel(linkGrid->link[items[i].grdCrd.c][items[i].grdCrd.r].Get_XY());	// ouach lol
			Item::meta.Item_Picked_Up();	// picked up!
			MsgQueue::Register(ITEM_PICKUP);

			Remove(i);	// retire l'item de la liste des items actifs
			return;
		}
	}
}
