

#include "grid.h"



const grdCoord *pMAXgrdMain;   // Les valeurs maximales	du grid des d�placements du joueur
const grdCoord *pMAXgrdWall;   // Les valeurs maximales	du grid des WALLS (lignes que le joueurs cr��s avec les touches de tirs)
const grdCoord *pMAXgrdSpw;	  // Les valeurs maximales	du grid des spawns des bots

//grdCoord** pMAXgrdMain;		



// Les pointeurs vers ces diff�rents Grd(ceux-ci changeront pour chaque niveaux)
HERE* pgrdMain;
WallType* pgrdWall;

// Servira � naviguer dans les tableaux des grids
grdCoord grd;



// Je reviendrais te compl�ter toi!!!
void DEL_lvlgrid()	// D�truit tous les variables cr�es pour le grid du niveau
{
	// Les pointeurs vers les dimensions MAX des trois diff�rents grids du jeu
	delete pMAXgrdMain;
	delete pMAXgrdWall;
	delete pMAXgrdSpw;

	pMAXgrdMain = pMAXgrdWall = pMAXgrdSpw = 0;	// Pointe vers NULL

	// Les pointeurs vers ces diff�rents Grd(ceux-ci changeront pour chaque niveaux
	delete pgrdMain;  pgrdMain = 0;	// Pointe vers NULL
	delete pgrdWall;  pgrdWall = 0; // Pointe vers NULL
}