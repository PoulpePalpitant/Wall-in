

#include "linkgrid.h"

// VARIABLE GLOBAL

extern LinkGrid linkGrid = {};	// Le seul et unique, le champion, le dernier de sa grande lignée de Grid

// Création d'un grid selon les dimensions colonnes et lignes	(Celui-ci sera utilisé pour entreposer tous les Links)
void LinkGrid::Create(int col, int row)	 // Ceci entâme la CRÉATION D'UN GRID!
{
	//Link**& link = this->link;

	// Le grid va pointer vers la liste de colonnes
	link = new Link * [col];

	// Chaques colonnes aura une liste de lignes(rows) contenant chacun 1 élément du Grid
	for (int i = 0; i < col; ++i) {
		link[i] = new Link[row];
		
		for (int j = 0; j < row; j++) {
			link[i][j].Set_LinkXY(i, j);		// 	// Set les valeurs xy à tout les éléments Link pointé par le grid
		}
		
	}

	// Assignation de la dimension du Nouveau Grid :)
	this->UpdSize(col, row);
}

// Détruit tout ce qui se trouvait sur le grid et le redimensionne
void LinkGrid::Resize(int col, int row)
{
	int maxCol = this->Get_Cols();	// Le nombre max de colonnes

	// DESTRUCTION
	for (int i = 0; i < maxCol; ++i) {
		delete[] link[i];
	}

	delete[] link;	// Détruit le tableau de tableaux

	// CRÉATION

	Create(col, row);
}


// CHECK: si la position actuelle sur le grid contient un Link vivant
bool LinkGrid::Is_Link_Here(int col, int row)			// WHERE IS LINK? I CAN'T FIND HIM!?
{																										// Les brackets [][] servent toujours à accéder à un élément d'un grid. Je me rend bien compte que la notation commence à être dégueuse
	return linkGrid.link[col][row].Get_State() == LinkState::DEAD;										// Si le link sur ce grid est Dead, aussi bien dire qu'il n'y en a pas
}