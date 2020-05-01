

#include "grid.h"


// CONSTANTES POUR L'AFFICHAGE SEULEMENT
// *************************************

extern const int START_X = 10;	// Position, sur l'axe des X de la console, du coin sup�rieur gauche du MAIN grid
extern const int START_Y = 2;	// Position, sur l'axe des Y de la console, du coin sup�rieur gauche du MAIN grid

extern const int DELTA_X = 5;	// pas mieux dans le grid?
extern const int DELTA_Y = 3;


// POINTEURS LOGIQUES VERS LES DIMENSIONS DE CHAQUE GRIDS
// ******************************************************

const grdCoord *pMaxGrdMain;   // Les valeurs maximales	du grid des d�placements du joueur
const grdCoord *pMaxGrdWall;   // Les valeurs maximales	du grid des WALLS (lignes que le joueurs cr��s avec les touches de tirs)
const grdCoord *pMaxGrdSpw;    // Les valeurs maximales	du grid des spawns des bots

//grdCoord** pMAXgrdMain;		



// Les pointeurs vers ces diff�rents Grd(ceux-ci changeront pour chaque niveaux)
CaseMainGrd* pgrdMain;
WallType* pgrdWall;

// Servira � naviguer dans les tableaux des grids
grdCoord grd;



// Je reviendrais te compl�ter toi!!!
void DEL_lvlgrid()	// D�truit tous les variables cr�es pour le grid du niveau
{
	// Les pointeurs vers les dimensions MAX des trois diff�rents grids du jeu
	delete pMaxGrdMain;
	delete pMaxGrdWall;
	delete pMaxGrdSpw;

	pMaxGrdMain = pMaxGrdWall = pMaxGrdSpw = 0;	// Pointe vers NULL

	// Les pointeurs vers ces diff�rents Grd(ceux-ci changeront pour chaque niveaux
	delete pgrdMain;  pgrdMain = 0;	// Pointe vers NULL
	delete pgrdWall;  pgrdWall = 0; // Pointe vers NULL
}