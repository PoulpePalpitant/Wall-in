#pragma once

#include "../grid/AllGrids.h"
#include "item_list.h"
#include "../events/global_events/clear_all_states.h"


struct ItemDrawer
{
	Coord XY;
	ItemType type;
	int currStep = 0;
	bool cancel = false;		// emp�che de draw le symbole du milieu. Survient que le joueur se d�place dessus, ou qu'un blast passe � travers
								// FIX: 1 blast peut s'arr�ter dessus, il faut donc tout canceler les output sur les axes
	SpeedTimer timer;	
};

class DrawItemSpawnList
{
	friend void Clear_All_States(bool eraseMap );	
		
	static int animationSteps;
	static ItemDrawer  drawer[MAX_ITEMS];	
	static int total;

	static void Remove(int index);
	static void Find_Item_Sym(ItemType type);
public:
	static void Remove_All(); // w�w minute papillon
	static void Draw_Item(ItemType type, GrdCoord crd);
	static void Draw_Item_Spawn();	// Draw them items mmk�6?
	static void Cancel(Coord XY);	
	static bool Add(ItemType type , GrdCoord crd);	
};
