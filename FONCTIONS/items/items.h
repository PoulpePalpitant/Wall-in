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

	-HEALTH
	Donne +1 de vie au joueur

*/

enum class ItemType
{ 
	REGULAR, BUFFER, BLOCKER, CORRUPTED, COLOR_A, COLOR_B, BLIND_COLOR, HEALTH, LIFE 
};

class ItemMeta
{
private:
	//static ItemMeta AllMeta;
public:
	int total;		// Le nombre d'items spawné
	int current;	// Le nombre d'item dans la box en ce moment
	int pickup;		// Le nombre d'item pickup
	int missed;		// Le nombre d'item pas pickup
	

	void Item_Spawned() {
		this->current++; this->total++; 
	//	AllMeta.current++; AllMeta.total++;
	}
	void Item_Picked_Up() {
		this->current--;//AllMeta.current--;
		this->pickup++;	//AllMeta.pickup++;
	}
	void Item_Disappeared() { 
	this->current--;	//AllMeta.current--; 
	this->missed++; 	//AllMeta.missed++;
	}
};


class Item {

private:		
	friend class ItemsOnGrid;
	friend class ItemSpawner;

	ItemType  itemType;
	bool active = false;					

	// POSITION
	GrdCoord grdCrd;						// On utilise le système de coordonnées des grids pour changer faire apparâitre les items

	static ItemMeta meta;	// info sur le groupe d'items

	// SETS
	void Set_Position(GrdCoord newPos) { grdCrd = newPos; }			// Change sa position sur le Grid

public:
	// GETS
	GrdCoord Get_Grd_Coord() { return grdCrd; }	// Sa position dans le grid
	ItemType Get_Type() { return itemType; }
	bool Is_Active() { return active; }

	// SET
	void Set_Coord(GrdCoord coord) { grdCrd = coord; }
	void Set_Type(ItemType type) { itemType = type; }
	void Activate() { active = true; }
	void Dectivate() { active = false; }
};


