#pragma once

#include "linkgrid.h"
#include "wallgrid.h"
#include "spawngrid.h"

// Création de tous les Grids du jeu: Link,Wall et Spawn Grids, selon un nombre de Col et de rows 
// Cette dimension sera utilisé directement Pour le LinkGrid, et indirectement pour le reste

void Create_All_Grids(LinkGrid& linkGrid, AllWallGrids& wallGrid, Spawn_Grid& spwnGrid, int col, int row);
void Resize_All_Grids(LinkGrid& linkGrid, AllWallGrids& wallGrid, Spawn_Grid& spwnGrid, int col, int row);
void Resize_Grids_To_Level(LinkGrid& linkGrid, AllWallGrids& wallGrid, Spawn_Grid& spwnGrid, int lvl);