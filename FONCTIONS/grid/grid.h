#pragma once

// p = pointeur!

// COORDONNÉES LOGIQUES DANS LA CONSOLE

struct grdCoord { int c; int l; };	//  Les grids du jeux seront tous navigué par la logique: Colonnes(x) Lignes(y)
										
// LES OBJETS POUVANT SE TROUVER SUR UNE CASE DU GRID DE DÉPLACEMENT DU JEU

enum class CaseMainGrd { Empty, Item, Player, Link, WeakLink };	// Les links sont les points qui relient chaque WALLS créés par le joueur. 

// LES OBJETS POUVANT SE TROUVER SUR UNE CASE DU GRID DES "WALLS" 

enum class CaseWallGrd {Empty, Wall, Bot};

//	LES TYPES DE MURS POUVANT 

enum class WallType {Weak, Normal, Ghost, Strong, BIGSTRONGWOW};	// Par défaut, les tirs du joueur font des murs normal
															// "Ghost" : pourrait être des murs que les bot peuvent traverser

// CONSTANTES POUR L'AFFICHAGE SEULEMENT
// *************************************

extern const int START_X;	// Position, sur l'axe des X de la console, du coin supérieur gauche du main Grid
extern const int START_Y;	// Position, sur l'axe des Y de la console, du coin supérieur gauche du main Grid

extern const int DELTA_X;	// Saut sur l'axe des X d'une case à l'autre
extern const int DELTA_Y;	// Saut sur l'axe des Y d'une case à l'autre


// Les pointeurs vers les dimensions MAX des trois différents grids du jeu
extern const grdCoord *pMaxGrdMain;							
extern const grdCoord *pMaxGrdWall;
extern const grdCoord *pMaxGrdSpw;







//	PLUS COMPLIQUÉ QUE PRÉVU! voir lvl1grid.cpp
// Les pointeurs vers ces différents Grd(ceux-ci changeront pour chaque niveaux
//extern HERE* pgrdMain;
//extern WallType* pgrdWall;
//extern HERE* pgrdSpw;			

// Variable qui servira à naviguer dans les tableaux des grids
extern grdCoord grd;


//	FONCTIONS
//	---------

void DEL_lvlgrid();	// Détruit tous les variables créés pour les grid du niveau
