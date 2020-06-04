
#include "../blast/convert_blast_type_to_wall.h"
#include "AllGrids.h"
#include "wallgrid.h"


// Créer un Grid de walls contenant tous les walls du jeu
// -----------------------------------------------

void WallGrid::Create(LinkGrid& linkGrid)	
{
	int col, row;	// Les dimensions qu'aura le Grid
	
	Adapt_To_LinkGrid_Size(col, row, linkGrid);	// Ceci va adapter la dimension du Grid des Walls selon celle Du Grid des Links

	// Le grid va pointer vers la liste de colonnes
	wall = new Wall * [col];

	// Chaques colonnes aura une liste de lignes(rows) contenant chacun 1 élément du Grid
	for (int i = 0; i < col ; ++i) {
		wall[i] = new Wall[row];

		for (int j = 0; j < row ; j++) {
			wall[i][j].Set_XY(i, j, this->gridAxis);	// Construire? tu dois incre,enter le xy&??  non le i j
			wall[i][j].Set_Axis(this->gridAxis);		// L'axe du wall est définit
			wall[i][j].Set_Default_Wall_UI();			// Et son Ui de base
		}
	}

	// Assignation de la dimension du Nouveau Grid :)
	this->UpdSize(col, row);
}

// Redimensionne.... Mais détruit aussi le grid...
// -----------------------------------------------

void WallGrid::Resize(LinkGrid& linkGrid)		
{
	int maxCol = this->Get_Cols();	// Le nombre max de colonnes

	// DESTRUCTION
	for (int i = 0; i < maxCol; ++i) {
		delete[] wall[i];
	}

	delete[] wall;	// Détruit le tableau de tableaux

	// CRÉATION
	Create(linkGrid);
}

// Calcul les dimensions qu'aura le grid selon celle du Link Grid
// -----------------------------------------------

void WallGrid::Adapt_To_LinkGrid_Size(int& col, int& row, LinkGrid& linkGrid)	
{															 
	col = linkGrid.Get_Cols();					//	 1  2  3  					 
	row = linkGrid.Get_Rows();				  	//	O--O--O--O			  
											  	//	|  |  |  |	3	O = Élément du LinkGrid	 		 
	if (Get_Grid_Axis() == Axis::HOR)			//	O--O--O--O		| = Élément du WallGrid Vertical	 	 
		col--;								  	//	|  |  |  |	2   -- = Élément du WallGrid Horizontal	 
	else									  	//	O--O--O--O		 
		row--;								  	//	|  |  |  |	1	Comme on peut voir Le Grid du Link est en 4col x 4row	 
											  	//	O--O--O--O		Par contre, le nombre de col du WallGrid Horizontal est plutôt de 3 (3 x 4)	 
											  	//					Comme on peut voir Le Grid des Walls vertical contient 4 col pour trois lignes (4 x 3)	 
}											  		 
								
bool WallGrid::Is_Wall_here(GrdCoord crd)		// WHERE IS WALL? I CAN'T FIND IT!
{
	if (!Is_Inbound(crd))	// Doit tjrs vérifier si la crd est INBOUND	
		return -1;

	if (this->wall[crd.c][crd.r].Get_State() == WallState::DEAD)										// Si le link sur ce grid est Dead, aussi bien dire qu'il n'y en a pas
		return false;	// Wall here is DEAD
	else
		return true;	// Wall here is alive
}

