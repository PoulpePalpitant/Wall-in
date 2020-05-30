#pragma once

#include "AllGrids.h"

// Création de tous les Grids du jeu: Link,Wall et Spawn Grids, selon un nombre de Col et de rows 
// Cette dimension sera utilisé directement Pour le LinkGrid, et indirectement pour le reste

void Create_All_Grids(AllGrids& grid, int col, int row);	//	test
void Resize_All_Grids(AllGrids& grid, int col, int row);
void Resize_Grids_To_Level(AllGrids& grid, int lvl);