#pragma once

// p = pointeur!

// COORDONN�ES LOGIQUES DANS LA CONSOLE

struct grdCoord { int c; int l; };	//  Les grids du jeux seront tous navigu� par la logique: Colonnes(x) Lignes(y)
										
// LES OBJETS POUVANT SE TROUVER SUR UNE CASE DU GRID DE D�PLACEMENT DU JEU

enum class CaseMainGrd { Empty, Item, Player, Link, WeakLink };	// Les links sont les points qui relient chaque WALLS cr��s par le joueur. 

// LES OBJETS POUVANT SE TROUVER SUR UNE CASE DU GRID DES "WALLS" 

enum class CaseWallGrd {Empty, Wall, Bot};

//	LES TYPES DE MURS POUVANT 

enum class WallType {Weak, Normal, Ghost, Strong, BIGSTRONGWOW};	// Par d�faut, les tirs du joueur font des murs normal
															// "Ghost" : pourrait �tre des murs que les bot peuvent traverser

// CONSTANTES POUR L'AFFICHAGE SEULEMENT
// *************************************

extern const int START_X;	// Position, sur l'axe des X de la console, du coin sup�rieur gauche du main Grid
extern const int START_Y;	// Position, sur l'axe des Y de la console, du coin sup�rieur gauche du main Grid

extern const int DELTA_X;	// Saut sur l'axe des X d'une case � l'autre
extern const int DELTA_Y;	// Saut sur l'axe des Y d'une case � l'autre


// Les pointeurs vers les dimensions MAX des trois diff�rents grids du jeu
extern const grdCoord *pMaxGrdMain;							
extern const grdCoord *pMaxGrdWall;
extern const grdCoord *pMaxGrdSpw;







//	PLUS COMPLIQU� QUE PR�VU! voir lvl1grid.cpp
// Les pointeurs vers ces diff�rents Grd(ceux-ci changeront pour chaque niveaux
//extern HERE* pgrdMain;
//extern WallType* pgrdWall;
//extern HERE* pgrdSpw;			

// Variable qui servira � naviguer dans les tableaux des grids
extern grdCoord grd;


//	FONCTIONS
//	---------

void DEL_lvlgrid();	// D�truit tous les variables cr��s pour les grid du niveau
