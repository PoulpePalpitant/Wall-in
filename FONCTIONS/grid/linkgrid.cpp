

#include "linkgrid.h"
#include "../player/player.h"
#include "../blast/convert_blast_type_to_link.h"


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
int LinkGrid::Is_Link_Alive_Here(GrdCoord crd)			// WHERE IS LINK? I CAN'T FIND HIM!?
{																									
	if (!Is_Inbound(crd))	// Doit tjrs vérifier si la crd est INBOUND	
		return -1;
	
	if (this->link[crd.c][crd.r].Get_State() != LinkState::DEAD)										// Si le link sur ce grid est Dead, aussi bien dire qu'il n'y en a pas
		return true;	// Link here, ain't dead
	else
		return false;	// No Link here, dead

}

// Pour déterminer un si le Link pourrait être un ROOT
bool LinkGrid::Is_Link_On_Border(GrdCoord crd)		
{
	if (crd.c == 0 || crd.r == 0)		// Bordure UP & Left
		return true;

	if (crd.c == Get_Cols() - 1 || crd.r == Get_Rows() - 1)	// bordure Right & Down
		return true;

	return false;
}


