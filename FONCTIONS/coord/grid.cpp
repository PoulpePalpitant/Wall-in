

#include "grid.h"





// doit vérifié si initialisé à NULL!!!!

const grdCoord *MAXgrdMain;   // Les valeurs maximales	du grid des déplacements du joueur
const grdCoord *MAXgrdWall;   // Les valeurs maximales	du grid des WALLS (lignes que le joueurs créés avec les touches de tirs)
const grdCoord *MAXgrdSpw;	  // Les valeurs maximales	du grid des spawns des bots

// Les pointeurs vers ces différents Grd(ceux-ci changeront pour chaque niveaux)
HERE* pgrdMain;
WallType* pgrdWall;

// Servira à naviguer dans les tableaux des grids
grdCoord grd;