

#include "linkgrid.h"
#include "../blast/convert_blast_type_to_link.h"

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
int LinkGrid::Is_Link_Here(int col, int row)			// WHERE IS LINK? I CAN'T FIND HIM!?
{																									
	if (!Is_Inbound(col, row))	// Doit tjrs vérifier si la crd est INBOUND	
		return -1;
	
	if(linkGrid.link[col][row].Get_State() != LinkState::DEAD)										// Si le link sur ce grid est Dead, aussi bien dire qu'il n'y en a pas
		return true;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////

// Le nombre de Link à "Activer" selon un "Blast" du joueur
//---------------------------------------------------------

int LinkGrid::Nb_Of_Link_Per_Blast(Blast* blast)
{
	if (blast->nbSteps == 0)	// Le blast n'a parcouru aucune distance (le player à sûrement tiré sur la bordure)
		return 0;
	else
		if (blast->nbSteps >= blast->length)		// La blast à parcouru une distance plus grande ou égale à sa longueur 
			return 1 + (blast->length) / (blast->btwLinks + 1);	// Longueur du blast / par DELTA_X/DELTA_Y sur le grid + 1 (NOMBRE MAX DE WALLS À ENREGISTRER)
		else
			return 1 + blast->nbSteps / (blast->btwLinks + 1) ;	// +1, car garentie d'avoir au moins deux Link
}




// Active tout les Link après un blast
void LinkGrid::Activate_Links_From_Blast(Blast* blast)	
{
	static int  nbLinks, nbLinksTot;
	static LinkType type;
	static Link* toActivate;	// Linka à activer
	static Link* child;			// et son child
	static GridIndexIncrementor linkCrd;	// Coord final du blast

	linkCrd = blast->grdPos;	// Position du premier Link à créer
	type = Convert_Blast_Type_To_Link_Type(blast->type);		// Tout les Link auront le même Link brah?
	nbLinksTot = nbLinks = Nb_Of_Link_Per_Blast(blast);			// Total à activer
	
	if (!nbLinks)
		return;	// Le blast n'a franchie aucune distance

	while (nbLinks)	// [0,2+[. Les links viennent en pair avec le blast		o----.	
	{
		// *Link
		if (nbLinks == nbLinksTot)
			toActivate = &linkGrid.link[linkCrd.index.c][linkCrd.index.r];
		else
			toActivate = child;

		// *child
		if (nbLinks == 1)		// Le dernier Link n'a pas de child		
			child = NULL;
		else
		{
			*linkCrd.axis -= linkCrd.polar;							// Adresse du link précédent, que le blast à traversé
			child = &linkGrid.link[linkCrd.index.c][linkCrd.index.r];	// Et voilà comment tu trouve le child
		}

		// VOILÀ

		toActivate->Activate_Link(type, child);		// Active le Link
		
		// dumb stuff hehe
		toActivate->Dsp_Link();		// dsp le symbole du Link

		nbLinks--;
	}
}
