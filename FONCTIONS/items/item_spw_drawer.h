#pragma once

#include "../grid/AllGrids.h"
#include "item_list.h"
#include "../events/global_events/clear_all_states.h"


struct ItemDrawer
{
	Coord XY;
	ItemType type;
	SpeedTimer timer;	
	int currStep = 0;
	bool cancelMid = false;		// empêche de draw le symbole du milieu. Survient que le joueur se déplace dessus, ou qu'un blast passe à travers
};

class DrawItemSpawnList
{
	friend void Clear_All_States(bool eraseMap );	// Gros reset button
		
	static int animationSteps;
	static ItemDrawer  drawer[MAX_ITEMS];	// woah tha's way too much buddy
	static int total;

	//static void Set_Drawer_From_Type(const ItemType& type);
	static void Remove(int index);
	static void Find_Item_Sym(ItemType type);
public:
	static void Remove_All(); // wôw minute papillon
	static void Draw_Item(ItemType type, GrdCoord crd);
	static void Draw_Item_Spawn();	// Draw them items mmké6?
	static void Cancel(Coord XY);					// Stop l'animation de l'item sur cette position
	static bool Add(ItemType type , GrdCoord crd);	// Ajoute un item à draw
};
