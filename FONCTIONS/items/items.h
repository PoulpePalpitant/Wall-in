#pragma once

#include "../grid/grid.h"
#include "../UI/txtstyle.h"
#include "../time/countdown_clock.h"
#include "../math/manage_interval.h"
#include "../events/global_events/ev_resize_from_grids.h"

const int MAX_ITEM_TYPE = 10;
const unsigned char ITEM_SYM[MAX_ITEM_TYPE] = { '+',  254 ,158, 207, 176,176,245,245 };
 
/*
	ITEMS
	Des items apparaissent sur les cases de déplacement du joueur
	Pour activer un item, le joueur peut soit marcher dessus, ou tirer dessus
	Il y a des items MODIFIER, et les autres
	Si le joueur pogne un modifier, son prochain blast sera modifié
*/

enum class ItemType
{ 
	REGULAR, BUFFER, BLOCKER, CORRUPTED, COLOR_A, COLOR_B, BLIND_COLOR, AMMO, LIFE 
};

class ItemMeta
{
private:
public:
	int total;		
	int current;	
	int pickup;		

	void Item_Spawned() {
		this->current++; this->total++; 
	}
	void Item_Picked_Up() {
		this->current--;
		this->pickup++;	
	}
};


class Item {

private:		
	friend class ItemsOnGrid;
	friend class ItemSpawner;

	ItemType  itemType;
	bool active = false;					

	GrdCoord grdCrd;					

	static ItemMeta meta;	

	void Set_Position(GrdCoord newPos) { grdCrd = newPos; }			

public:
	GrdCoord Get_Grd_Coord() { return grdCrd; }	
	ItemType Get_Type() { return itemType; }
	bool Is_Active() { return active; }

	void Set_Coord(GrdCoord coord) { grdCrd = coord; }
	void Set_Type(ItemType type) { itemType = type; }
	void Activate() { active = true; }
	void Dectivate() { active = false; }
};


