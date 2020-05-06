#pragma once

// p = pointeur!

// COORDONN�ES LOGIQUES DANS LA CONSOLE

struct GrdCoord { int c; int l; };	//  Les grids du jeux seront tous navigu� par la logique: Colonnes(x) Lignes(y)
										
// LES OBJETS POUVANT SE TROUVER SUR UNE CASE DU GRID DE D�PLACEMENT DU JEU

enum class MainGrdElem { EMPTY, ITEM, PLAYER, LINK, WEAKLINK };	// Les links sont les points qui relient chaque WALLS cr��s par le joueur. 

// LES OBJETS POUVANT SE TROUVER SUR UNE CASE DU GRID DES "WALLS" 

enum class CaseWallGrd {EMPTY, WALL, BOT};

//	LES TYPES DE MURS

enum class WallType {WEAK, NORMAL, GHOST, STRONG, BIGSTRONGWOW};	// Par d�faut, les tirs du joueur font des murs normal
																	// "Ghost" : pourrait �tre des murs que les bot peuvent traverser

// CONSTANTES POUR L'AFFICHAGE SEULEMENT
// *************************************

extern const int START_X;	// Position, sur l'axe des X de la console, du coin sup�rieur gauche du main Grid
extern const int START_Y;	// Position, sur l'axe des Y de la console, du coin sup�rieur gauche du main Grid

extern const int DELTA_X;	// Saut sur l'axe des X d'une case � l'autre(Main Grid)
extern const int DELTA_Y;	// Saut sur l'axe des Y d'une case � l'autre

// Metre main gridet wall grid dans une seule classe grid?

// ou s�prarer les m�thodes de walls et main pour faire deux objet grid distinct?//
// le truc cest que les deux sont tr`s li�

// CLASS DE GRID HERE WE GO

class Grid {

	int numCol;	// Dimension en colonne du Grid
	int numRow;	// Dimension en lignes du Grid
	static MainGrdElem** mainGrdElem;	// Le grid est un pointeur vers un tableau de pointeurs vers un �l�ment GRID

public:
	// D�claration du Constructor
	Grid(int col, int row);				// Cr�er le Grid. Persistera tout le long de la game
	
	// LES M�THODES: Plyer Grid
	int getRows() {return numRow;};		// Get numRow
	int getCols() {return numCol;};		// Get numCol
	bool isInbound(int col, int row);	// V�rifie si la coord donn�e est pr�sente dans le grid

	void Resize(int col, int row);		// Redimensionne.... Mais d�truit aussi le grid...Et set aussi les valeurs � empty >:(
	void setValue(int col, int row, MainGrdElem &Ele);
	MainGrdElem getValue(int col, int row);

	// Overload operator [][] pour acc�der � un �l�ment du Grid
	//MainGrdElem operator[] (int col, int row);


	// Wall grid: Fait juste changer le type qui sera trait�!!!!
	//void Resize(int col, int row);		// Redimensionne.... Mais d�truit aussi le grid...
	//Grid(int col, int row);				// Cr�er le Grid. Persistera tout le long de la game
	
	// void setValue(int col, int row, CaseWallGrd &Ele);
	// getvalue


	// Get object on grid
	// Get coord XY
	
	
	// SetAll
	// Check IfInbound
	
		// operator
		//grid[row][col]	Overloads [] to select elements from this grid.
};

// Object GridHorizontal

// static WallGridElem** wallGridElem









// Les pointeurs vers les dimensions MAX des trois diff�rents grids du jeu
extern const GrdCoord *pMaxGrdMain;							
extern const GrdCoord *pMaxGrdWall;
extern const GrdCoord *pMaxGrdSpw;




//	PLUS COMPLIQU� QUE PR�VU! voir lvl1grid.cpp
// Les pointeurs vers ces diff�rents Grd(ceux-ci changeront pour chaque niveaux
//extern HERE* pgrdMain;
//extern WallType* pgrdWall;
//extern HERE* pgrdSpw;			

// Variable qui servira � naviguer dans les tableaux des grids
extern GrdCoord gGrd;


//	FONCTIONS
//	---------

void DEL_lvlgrid();	// D�truit tous les variables cr��s pour les grid du niveau
