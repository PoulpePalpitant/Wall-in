
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
									


//// Trouve la crd de wall entre deux Link
//GridIndexIncrementor WallGrid::Find_Wall_Btwn_Links()
//{
//	if(this.)
//
//
//
//}
//
//GridIndexIncrementor Find_Wall_With_LinkDir()		// Trouve le wall avec la coord d'un Link et une direction
//{
//
//
//
//}

//GridIndexIncrementor WallGrid::Find_Wall_From_Link_Dir(GrdCoord crd, Direction dir)		// Trouve le wall avec la coord d'un Link et une direction
//{
//
//
//
//
//}

// Le nombre de walls à "Creer" selon un "Blast" du joueur
//---------------------------------------------------------

int WallGrid::Nb_Of_Walls_Per_Blast(Blast* blast)
{
	if (blast->nbSteps == 0)	// Le blast n'a parcouru aucune distance (le player à sûrement tiré sur la bordure)
		return 0;
	else
		if (blast->nbSteps >= blast->length)		// La blast à parcouru une distance plus grande ou égale à sa longueur 
			return blast->length / (blast->btwLinks + 1) ;	// La longueur max / par la distance qui sépare chaque link	(NOMBRE MAX DE WALLS À ENREGISTRER)
		else
			return blast->nbSteps / (blast->btwLinks + 1); //works
}





// Active tout les murs créé par un blast
void WallGrid::Activate_Walls_From_Blast(Blast* blast)	// Créer des murs(modifie leur valeurs) d'après un certains blast . Quand le joueur tir, ça laisse un mur, et il faut le record dans le grid
{
	static int nbOfWalls;
	static WallType type;
	static Wall* toActivate;	// Wall à activer
	static GridIndexIncrementor crd;	// crd du wall
	

	type = Convert_Blast_Type_To_Wall_Type(blast->type);	

	/*find first wall crd*/
	crd = blast->grdPos;
	if(blast->dir == RIGHT)		// Tu déborde du grid mon gars. Le dernier Wall à droite correspond à L'AVANT dernier Link	   1    2    3	|	(Links)		col[3]
		crd.index.c--;																										 //o----o----o	|Fin
	else																													 //   1   2		|	(walls)		col[2]
		if (blast->dir == DOWN)		// Tu déborde du grid mon gars
		crd.index.r--;

	nbOfWalls = this->Nb_Of_Walls_Per_Blast(blast);	// si merge: clear
	while (nbOfWalls)
	{
		toActivate = &this->wall[crd.index.c][crd.index.r];	// wall à activer
		toActivate->Activate_Wall(type);

		if(nbOfWalls > 1)
			crd.Decrement_Coord();	

		nbOfWalls--;
	}

}
							  		 
//
//
//// Création ou Destruction de tous les murs possibles se situant entre deux coord (côte-à-côte sur le grid)
//void Creation_or_Destruction_Walls_Btwn_Links(int CoordDepart, int CoordFin, Time Delay, bool Creation)
//{
//	int NbdeWalls;		// Le nombre de walls entre 2 coord
//	Axe axe;			// L'axe des murs entre la CoordDepart et la Coord de fin
//	Polarisation polar;	// La polarisation entre la Coordonnée de départ et la coord de fin
//	char Sym;			// Le symbole pour l'affichage du Wall
//
//	axe = Axe_Entre_Deux_Coord(CoordDepart, CoordFin);				// Donne l'axe
//	polar = Polarisation_Selon_Deux_Coord(CoordDepart, CoordFin);	// Trouve la polarisation entre là coordonnée 
//
//	//// Le nombre de walls et le symbol du wall
//	if (axe == x) { NbdeWalls = NbWallX; Sym = BlastSymX; }
//	else { NbdeWalls = NbWallY; Sym = BlastSymY; }
//
//	// On va commencer la destruction/Création à partir de la coordonnée de départ
//	Goto_Coordinnates(CoordX, CoordY, CoordDepart);
//
//	for (int l = 0; l < NbdeWalls; ++l)	// Destruction de chacun des murs entre les deux Links
//	{
//		// La coordonnée de chacun des murs à détruire est déterminée par l'incrémentation de x ou y de +1 ou -1 case selon l'axe ou se trouve les walls
//		axe == y ? CoordY += polar : CoordX += polar;
//		if (Creation)
//			Create_Wall(CoordX, CoordY, Sym);	// Création d'un mur
//		else
//			Destroy_WALL(CoordX, CoordY);		// Destruction du mur et effacement du symbole
//		Sleep(Delay);
//	}
//}
