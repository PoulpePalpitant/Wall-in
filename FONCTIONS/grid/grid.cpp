

#include "grid.h"



const grdCoord *pMAXgrdMain;   // Les valeurs maximales	du grid des déplacements du joueur
const grdCoord *pMAXgrdWall;   // Les valeurs maximales	du grid des WALLS (lignes que le joueurs créés avec les touches de tirs)
const grdCoord *pMAXgrdSpw;	  // Les valeurs maximales	du grid des spawns des bots

//grdCoord** pMAXgrdMain;		



// Les pointeurs vers ces différents Grd(ceux-ci changeront pour chaque niveaux)
HERE* pgrdMain;
WallType* pgrdWall;

// Servira à naviguer dans les tableaux des grids
grdCoord grd;



// Je reviendrais te compléter toi!!!
void DEL_lvlgrid()	// Détruit tous les variables crées pour le grid du niveau
{
	// Les pointeurs vers les dimensions MAX des trois différents grids du jeu
	delete pMAXgrdMain;
	delete pMAXgrdWall;
	delete pMAXgrdSpw;

	pMAXgrdMain = pMAXgrdWall = pMAXgrdSpw = 0;	// Pointe vers NULL

	// Les pointeurs vers ces différents Grd(ceux-ci changeront pour chaque niveaux
	delete pgrdMain;  pgrdMain = 0;	// Pointe vers NULL
	delete pgrdWall;  pgrdWall = 0; // Pointe vers NULL
}