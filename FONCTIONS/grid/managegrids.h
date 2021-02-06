#pragma once

#include "AllGrids.h"


void Create_All_Grids(AllGrids& grid, int col, int row);	
void Resize_All_Grids(AllGrids& grid, int col, int row);
bool Resize_Grids_To_Level(AllGrids& grid, int lvl, bool finalPuzzle = false);
