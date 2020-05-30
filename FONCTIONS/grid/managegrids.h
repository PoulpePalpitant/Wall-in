#pragma once

#include "AllGrids.h"

// Cr�ation de tous les Grids du jeu: Link,Wall et Spawn Grids, selon un nombre de Col et de rows 
// Cette dimension sera utilis� directement Pour le LinkGrid, et indirectement pour le reste

void Create_All_Grids(AllGrids& grid, int col, int row);	//	test
void Resize_All_Grids(AllGrids& grid, int col, int row);
void Resize_Grids_To_Level(AllGrids& grid, int lvl);