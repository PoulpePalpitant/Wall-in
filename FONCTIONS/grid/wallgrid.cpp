
#include "wallgrid.h"


// D�FINITION DES VARIABLES GLOBALES

extern WallGrid wallGridHor(HOR);
extern WallGrid wallGridVer(VER);
extern AllWallGrids wallGrids(wallGridHor, wallGridVer);		// Contient les deux grids plus haut	 

// Cr�er un Grid de walls contenant tous les walls du jeu
// -----------------------------------------------

void WallGrid::Create(LinkGrid& linkGrid)	
{
	int col, row;	// Les dimensions qu'aura le Grid
	
	Adapt_To_LinkGrid_Size(col, row, linkGrid);	// Ceci va adapter la dimension du Grid des Walls selon celle Du Grid des Links

	// Le grid va pointer vers la liste de colonnes
	wall = new Wall * [col];

	// Chaques colonnes aura une liste de lignes(rows) contenant chacun 1 �l�ment du Grid
	for (int i = 0; i < col ; ++i) {
		wall[i] = new Wall[row];

		for (int j = 0; j < row ; j++) {
			wall[i][j].Set_XY(i, j, this->gridAxis);	// Construire? tu dois incre,enter le xy&??  non le i j
			wall[i][j].Set_Axis(this->gridAxis);		// L'axe du wall est d�finit
			wall[i][j].Set_Default_Wall_UI();			// Et son Ui de base
		}
	}

	// Assignation de la dimension du Nouveau Grid :)
	this->UpdSize(col, row);
}

// Redimensionne.... Mais d�truit aussi le grid...
// -----------------------------------------------

void WallGrid::Resize(LinkGrid& linkGrid)		
{
	int maxCol = this->Get_Cols();	// Le nombre max de colonnes

	// DESTRUCTION
	for (int i = 0; i < maxCol; ++i) {
		delete[] wall[i];
	}

	delete[] wall;	// D�truit le tableau de tableaux

	// CR�ATION
	Create(linkGrid);
}

// Calcul les dimensions qu'aura le grid selon celle du Link Grid
// -----------------------------------------------

void WallGrid::Adapt_To_LinkGrid_Size(int& col, int& row, LinkGrid& linkGrid)	
{															 
	col = linkGrid.Get_Cols();					//	 1  2  3  					 
	row = linkGrid.Get_Rows();				  	//	O--O--O--O			  
											  	//	|  |  |  |	3	O = �l�ment du LinkGrid	 		 
	if (Get_Grid_Axis() == Axis::HOR)			//	O--O--O--O		| = �l�ment du WallGrid Vertical	 	 
		col--;								  	//	|  |  |  |	2   -- = �l�ment du WallGrid Horizontal	 
	else									  	//	O--O--O--O		 
		row--;								  	//	|  |  |  |	1	Comme on peut voir Le Grid du Link est en 4col x 4row	 
											  	//	O--O--O--O		Par contre, le nombre de col du WallGrid Horizontal est plut�t de 3 (3 x 4)	 
											  	//					Comme on peut voir Le Grid des Walls vertical contient 4 col pour trois lignes (4 x 3)	 
}											  		 
									
// Trouve quel wallgrid correspond � une direction 
WallGrid* AllWallGrids::Find_Grid_From_Direction(Direction dir)
{
	if (dir == UP || dir == DOWN)
		return this->ver;			// WallGrid vertical
	else
		return this->hor;			// Wallgrid horizontal
}


// Trouve la crd de wall entre deux Link
GridIndexIncrementor WallGrid::Find_Wall_Btwn_Links()
{
	if(this.)



}

GridIndexIncrementor Find_Wall_With_LinkDir()		// Trouve le wall avec la coord d'un Link et une direction
{



}

// Le nombre de walls � "Creer" selon un "Blast" du joueur
//---------------------------------------------------------

int WallGrid::Nb_Of_Walls_Per_Blast(Blast* blast)
{
	if (blast->nbSteps == 0)	// Le blast n'a parcouru aucune distance (le player � s�rement tir� sur la bordure)
		return 0;
	else
		if (blast->nbSteps >= blast->length)		// La blast � parcouru une distance plus grande ou �gale � sa longueur 
			return blast->length / blast->btwLinks;	// La longueur max / par la distance qui s�pare chaque link	(NOMBRE MAX DE WALLS � ENREGISTRER)
		else
			return blast->nbSteps / blast->btwLinks;	// Devrait donner entre 0 et 1 si la longueur du blast fait moins de deux intervalles de distance de grid, sinon, well ce commentaire est vraiment utile		
}





// Active tout les murs cr�� par un blast
void AllWallGrids::Activate_Walls_From_Blast(Blast* blast)	// Cr�er des murs(modifie leur valeurs) d'apr�s un certains blast . Quand le joueur tir, �a laisse un mur, et il faut le record dans le grid
{
	static int nbOfWalls;
	static GridIndexIncrementor wallCrd;	// crd du wall
	static WallGrid* wallgrd;				// le bon grid de wall
	
	wallgrd = Find_Grid_From_Direction(blast->dir);


	nbOfWalls = wallgrd.Nb_Of_Walls_Per_Blast(blast);

	while (nbOfWalls)
	{




	}

}
							  		 