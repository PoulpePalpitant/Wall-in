

#include "grid.h"





// doit v�rifi� si initialis� � NULL!!!!

const grdCoord *MAXgrdMain;   // Les valeurs maximales	du grid des d�placements du joueur
const grdCoord *MAXgrdWall;   // Les valeurs maximales	du grid des WALLS (lignes que le joueurs cr��s avec les touches de tirs)
const grdCoord *MAXgrdSpw;	  // Les valeurs maximales	du grid des spawns des bots

// Les pointeurs vers ces diff�rents Grd(ceux-ci changeront pour chaque niveaux)
HERE* pgrdMain;
WallType* pgrdWall;

// Servira � naviguer dans les tableaux des grids
grdCoord grd;