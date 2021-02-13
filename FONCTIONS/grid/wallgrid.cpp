
#include "AllGrids.h"
#include "wallgrid.h"


void WallGrid::Create(LinkGrid& linkGrid)	
{
	int col, row;
	
	Adapt_To_LinkGrid_Size(col, row, linkGrid);	

	wall = new Wall * [col];

	for (int i = 0; i < col ; ++i) {
		wall[i] = new Wall[row];

		for (int j = 0; j < row ; j++) {
			wall[i][j].Set_XY(i, j, this->gridAxis);	
			wall[i][j].Set_Axis(this->gridAxis);		 
			wall[i][j].Set_Default_Wall_UI();			
		}
	}

	this->UpdSize(col, row);
}

void WallGrid::Resize(LinkGrid& linkGrid)		
{
	int maxCol = this->Get_Cols();

	for (int i = 0; i < maxCol; ++i) {
		delete[] wall[i];
	}

	delete[] wall;

	Create(linkGrid);
}

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
								
bool WallGrid::Is_Wall_here(GrdCoord crd)		
{
	if (!Is_Inbound(crd))	
		throw "Doit tjrs vérifier si la crd est INBOUND	";

	if (this->wall[crd.c][crd.r].Get_State() == WallState::DEAD)										
		return false;	
	else
		return true;	
}

