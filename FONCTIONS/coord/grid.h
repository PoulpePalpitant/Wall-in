#pragma once

// p = pointeur!

// COORDONN�ES LOGIQUES DANS LA CONSOLE

struct grdCoord { int c; int l; };	//  Les grids du jeux seront tous navigu� par la logique: Colonnes(x) Lignes(y)
										
// LES OBJETS POUVANT SE TROUVER SUR UNE CASE DU GRID DE D�PLACEMENT DU JEU

enum HERE { Empty, Item, Player, Link, WeakLink };	// Les links sont les points qui relient chaque WALLS cr��s par le joueur. 

//	LES TYPES DE MURS POUVANT SE TROUVER SUR LE GRID DES WALLS CR��S PAR LE JOUEUR

enum WallType {Weak, Normal, Strong, BIGSTRONGWOW};	// Par d�faut, les tirs du joueur font des murs normal


// Les dimensions des trois diff�rents grids du jeu
extern const grdCoord *MAXgrdMain;								//transfomre en pointeur vers des const!!!!!
extern const grdCoord *MAXgrdWall;
extern const grdCoord *MAXgrdSpw;

// Les pointeurs vers ces diff�rents Grd(ceux-ci changeront pour chaque niveaux
extern HERE* pgrdMain;
extern WallType* pgrdWall;
//extern HERE* pgrdSpw;			// Logiques du grid des spawns doit �tre d�couverte

// Variable qui servira � naviguer dans les tableaux des grids
extern grdCoord grd;




// Pour naviguer ces valeurs imodifiables

//const grdCoord* Pgrd;