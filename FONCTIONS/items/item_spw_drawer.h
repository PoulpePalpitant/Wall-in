#pragma once

#include "../grid/AllGrids.h"
#include "item_list.h"



struct ItemDrawer
{
	Coord XY;
	ItemType type;
	SpeedTimer timer;	
	int currStep = 0;
	bool cancelMid = false;		// emp�che de draw le symbole du milieu. Survient que le joueur se d�place dessus, ou qu'un blast passe � travers
};

class DrawItemSpawnList
{
	static int animationSteps;
	static ItemDrawer  drawer[20];
	static int total;

	//static void Set_Drawer_From_Type(const ItemType& type);
	static void Remove(int index);
	static void Find_Item_Sym(ItemType type);
public:

	static void Draw_Item_Spawn();	// Draw them items mmk�6?
	static void Cancel(Coord XY);					// Stop l'animation de l'item sur cette position
	static bool Add(ItemType type , GrdCoord crd);	// Ajoute un item � draw
};
