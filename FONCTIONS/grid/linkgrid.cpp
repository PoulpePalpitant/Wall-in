

#include "linkgrid.h"
#include "../player/player.h"


// Création d'un grid selon les dimensions colonnes et lignes	(Celui-ci sera utilisé pour entreposer tous les Links)
void LinkGrid::Create(int col, int row)	 
{
	link = new Link * [col];

	for (int i = 0; i < col; ++i) {
		link[i] = new Link[row];
		
		for (int j = 0; j < row; j++) {
			link[i][j].Set_LinkXY(i, j);		
		}
	}

	this->UpdSize(col, row);
}

void LinkGrid::Resize(int col, int row)
{
	int maxCol = this->Get_Cols();	

	// DESTRUCTION
	for (int i = 0; i < maxCol; ++i) {
		delete[] link[i];
	}

	delete[] link;	

	// CRÉATION
	Create(col, row);
}


int LinkGrid::Is_Link_Alive_Here(GrdCoord crd)			
{																									
	if (!Is_Inbound(crd))	
		return -1;
	
	if (this->link[crd.c][crd.r].Get_State() != LinkState::DEAD)										
		return true;	
	else
		return false;

}

bool LinkGrid::Is_Link_On_Border(GrdCoord crd)		
{
	if (crd.c == 0 || crd.r == 0)		
		return true;

	if (crd.c == Get_Cols() - 1 || crd.r == Get_Rows() - 1)	
		return true;

	return false;
}


