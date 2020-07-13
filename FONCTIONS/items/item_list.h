#pragma once

#include "items.h"

#include "../global_types/global_types.h"

const int MAX_ITEMS = 30;



class ItemsOnGrid
{
public:
	static Item items[MAX_ITEMS];
	static int size;			// dimension de la liste

	static bool Reached_Max() {	return size == MAX_ITEMS;}
	static bool Is_Item_Here(GrdCoord crd);	// 
	static void Pickup_Item_Here(GrdCoord crd);
	static bool Is_Item_Modifier( Item& item);
	static bool Add(Item& item);
	static void Remove(int index);
};

