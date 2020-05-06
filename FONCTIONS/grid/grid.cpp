

#include "grid.h"


// CONSTANTES POUR L'AFFICHAGE SEULEMENT
// *************************************

extern const int START_X = 10;	// Position, sur l'axe des X de la console, du coin sup�rieur gauche du MAIN grid
extern const int START_Y = 2;	// Position, sur l'axe des Y de la console, du coin sup�rieur gauche du MAIN grid

extern const int DELTA_X = 5;	// Distance s�parant chaque point du du Main Grid en X 
extern const int DELTA_Y = 3;	// Note:  Le joueur peut uniquement se d�placer sur cette distance

// DIMENSIONS DES GRIDS

// LOGIQUES DES GRIDS: MAIN GRID, WALL GRID ET SPAWN GRID
// ------------------------------------------------------

/*	
	Chaque niveau est consitu� de plusieurs Grids logiques qui permettent notamment de naviguer l'espace de la console.
	Le terrain de jeu est construit par un Grid (main Grd) sur lequelle le joueur peut se d�placer. Le joueur ne peut sortir
	de Ce Grid, et ne peut pas bouger autrement que par l'intervalle qui s�pare chaque point du Grid. Le joueur peut tirer,
	et ces tirs laissent une ligne qu'on appel simplement un Wall. Chaque Walls sont reli� par les point du Main Grid comme 
	�a : O----O----O		 Mgrid = O    Walls = ---- 
	
	Pour retracer la localisation de chaque wall, un Grid horizontal[col][lig] et vertical[col][lig] est n�cessaire.
	� NOTER: contrairement au main Grid qui est constitu� d'unique	Coordonn�es XY dans la console, un Wall sur le wall grid
	est constitu� de plusieurs charat�res sur une suite de case. Pour convertir la position logique en une Coord XY	dans 
	la console on proc�de avec la logique suivante : le premier char du wall se trouve � +1 case du main grid	 

	 LEGENDE:	M= XY Main Grid			W = XY WallGrid 		Le reste des walls : ---, |||

		HorizontalWall Grid:	MW---	(+1 en X)				Vertical Wall Grid : M	(+1 en Y)
																					 w
																					 |
																					 |
	
	SPAWN GRID:

*/

MainGrdElem **Grid::mainGrdElem;


// D�finition du Constructor de la class Grid	
Grid::Grid(int col, int row)	 // Ceci ent�me la CR�ATION D'UN GRID!
{
	// Le grid va pointer vers la liste de colonnes
	mainGrdElem = new MainGrdElem * [col];

	// Chaques colonnes aura une liste de lignes(rows) contenant chacun 1 �l�ment du Grid
	for (int i = 0; i < col; ++i) {
		mainGrdElem[i] = new MainGrdElem[row];

		for (size_t j = 0; j < row; j++){
			mainGrdElem[i][j] = MainGrdElem::EMPTY;
		}
	}

	// Assignation de la dimension du Nouveau Grid :)
	numCol = col;
	numRow = row;
}

// D�truit tout ce qui se trouvait sur le grid et le redimensionne
void Grid::Resize(int col, int row)
{
	
	// DESTRUCTION
	// Destruction de l'array
	for (int i = 0; i < col; ++i) {
		delete[] Grid::mainGrdElem[i];
	}

	delete[] Grid::mainGrdElem;	// D�truit le tableau de tableaux

	// CR�ATION
	// Le grid va pointer vers la liste de colonnes
	Grid::mainGrdElem = new MainGrdElem * [col];

	// Chaques colonnes aura une liste de lignes(rows) contenant chacun 1 �l�ment du Grid
	for (int i = 0; i < col; ++i) {
		Grid::mainGrdElem[i] = new MainGrdElem[row];
	}





	// REDIMENSION
	// Assignation de la dimension du Nouveau Grid :)
	numCol = col;
	numRow = row;
}

bool Grid::isInbound(int col, int row)
{
	if (col > numCol || row > numRow)	// Validation d'une coordonn�e trop grande
		return false;

	if (numCol < 0 || row < 0)		// Validation d'une coordonn�e dans les n�gatifs
		return false;

	return true;
}

void Grid::setValue(int col, int row, MainGrdElem &Ele)	// tu passe juste un �l�ment >:(
{
	mainGrdElem[col][row] = Ele;
}

MainGrdElem Grid::getValue(int col, int row)
{
	return mainGrdElem[col][row];
}


 MainGrdElem** mainGrdElem = 0;





// D�cision: 
//faire une class Grid
// Utilise Grid pour faire Maingrid
// meme chose avec Wallgrid hor, wallgrid ver
// et spawnCoord UP, down, left right
// A chaque lvl je redimensionne les grids?


// Les spawns ne sont pas vraiment des grids? 


// adpate les constructor, Ex:spawn contient 1 array slmt.
//Et les attributes: ex : Main contient plyer. Wall contient BOTS, 








// POINTEURS LOGIQUES VERS LES DIMENSIONS DE CHAQUE GRIDS
// ******************************************************

const GrdCoord* pMaxGrdMain;   // Les valeurs maximales	du grid des d�placements du joueur
const GrdCoord* pMaxGrdWall;   // Les valeurs maximales	du grid des WALLS (lignes que le joueurs cr��s avec les touches de tirs)
const GrdCoord* pMaxGrdSpw;    // Les valeurs maximales	du grid des spawns des bots

//grdCoord** pMAXgrdMain;		

// Les pointeurs vers ces diff�rents Grd(ceux-ci changeront pour chaque niveaux)
MainGrdElem* pGrdMain;
WallType* pGrdWall;

// Servira � naviguer dans les tableaux des grids
GrdCoord gGrd;



// Je reviendrais te compl�ter toi!!!
void DEL_lvlgrid()	// D�truit tous les variables cr�es pour le grid du niveau
{
	// Les pointeurs vers les dimensions MAX des trois diff�rents grids du jeu
	delete pMaxGrdMain;
	delete pMaxGrdWall;
	delete pMaxGrdSpw;

	pMaxGrdMain = pMaxGrdWall = pMaxGrdSpw = 0;	// Pointe vers NULL

	// Les pointeurs vers ces diff�rents Grd(ceux-ci changeront pour chaque niveaux
	delete pGrdMain;  pGrdMain = 0;	// Pointe vers NULL
	delete pGrdWall;  pGrdWall = 0; // Pointe vers NULL
}