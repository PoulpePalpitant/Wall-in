

#include "linkgrid.h"
#include "../player/player.h"
#include "../blast/convert_blast_type_to_link.h"


// Cr�ation d'un grid selon les dimensions colonnes et lignes	(Celui-ci sera utilis� pour entreposer tous les Links)
void LinkGrid::Create(int col, int row)	 // Ceci ent�me la CR�ATION D'UN GRID!
{
	//Link**& link = this->link;

	// Le grid va pointer vers la liste de colonnes
	link = new Link * [col];

	// Chaques colonnes aura une liste de lignes(rows) contenant chacun 1 �l�ment du Grid
	for (int i = 0; i < col; ++i) {
		link[i] = new Link[row];
		
		for (int j = 0; j < row; j++) {
			link[i][j].Set_LinkXY(i, j);		// 	// Set les valeurs xy � tout les �l�ments Link point� par le grid
		}
		
	}

	// Assignation de la dimension du Nouveau Grid :)
	this->UpdSize(col, row);
}

// D�truit tout ce qui se trouvait sur le grid et le redimensionne
void LinkGrid::Resize(int col, int row)
{
	int maxCol = this->Get_Cols();	// Le nombre max de colonnes

	// DESTRUCTION
	for (int i = 0; i < maxCol; ++i) {
		delete[] link[i];
	}

	delete[] link;	// D�truit le tableau de tableaux

	// CR�ATION

	Create(col, row);
}


// CHECK: si la position actuelle sur le grid contient un Link vivant
int LinkGrid::Is_Link_Here(GrdCoord crd)			// WHERE IS LINK? I CAN'T FIND HIM!?
{																									
	if (!Is_Inbound(crd))	// Doit tjrs v�rifier si la crd est INBOUND	
		return -1;
	
	if (this->link[crd.c][crd.r].Get_State() != LinkState::DEAD)										// Si le link sur ce grid est Dead, aussi bien dire qu'il n'y en a pas
		return true;	// Link here, ain't dead
	else
		return false;	// No Link here, dead

}

// Pour d�terminer un si le Link pourrait �tre un ROOT
bool LinkGrid::Is_Link_On_Border(GrdCoord crd)		
{
	if (crd.c == 0 || crd.r == 0)		// Bordure UP & Left
		return true;

	if (crd.c == Get_Cols() - 1 || crd.r == Get_Rows() - 1)	// bordure Right & Down
		return true;

	return false;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////

//
//void Find_Link_ToActivate()
//{
//
//	// *Link
//	if (nbLinks == nbLinksTot)
//		toActivate = &this->link[linkCrd.index.c][linkCrd.index.r];
//	else
//		toActivate = child;
//
//	// *child
//	if (nbLinks == 1)		// Le dernier Link n'a pas de child		
//		child = NULL;
//	else
//	{
//		linkCrd.Decrement_Coord();							// Adresse du link pr�c�dent, que le blast � travers�
//		child = &this->link[linkCrd.index.c][linkCrd.index.r];	// Et voil� comment tu trouve le child
//	}
//}
//
//
//// Active tout les Link apr�s un blast
//void LinkGrid::Activate_Links_From_Blast(Blast* blast, bool drawLastLink)	
//{
//	static int  nbLinks, nbLinksTot;
//	static LinkType type;
//	static Link* toActivate, *child, *parent; toActivate = parent = child = NULL;	// Linka � activer et son child
//	static GridIndexIncrementor linkCrd;								// Coord final du blast
//
//	
//	linkCrd = blast->grdPos;											// Position du premier Link � cr�er
//	//type = Convert_Blast_Type_To_Link_Type(blast->strength);			// Tout les Link auront le m�me type brah?
//	nbLinksTot = nbLinks = blast->Nb_Of_Links_To_Activate();			// Total � activer
//	
//	if (!nbLinks)
//		return;	// Le blast n'a franchie aucune distance
//
//	while (nbLinks)	// [0,2+[. Les links viennent en pair avec le blast		o----.	
//	{
//		if (nbLinks == nbLinksTot)
//			toActivate = &this->link[linkCrd.index.c][linkCrd.index.r];
//		else
//			toActivate = child;
//
//		// *child
//		if (nbLinks == 1)		// Le dernier Link n'a pas de child		
//			child = NULL;
//		else
//		{
//			linkCrd.Decrement_Coord();							// Adresse du link pr�c�dent, que le blast � travers�
//			child = &this->link[linkCrd.index.c][linkCrd.index.r];	// Et voil� comment tu trouve le child
//		}
//
//		// VOIL�
//
//		toActivate->Activate_Link(blast->linkType, child);		// Active le Link, et le lis � son child
//
//		/*theoretical perte de tempo, les links s'activent toujours en pairs anyway, tu veux pas set le state 2fois c'est pourquoi ta fais ce que ta fais en haut*/
//
//		// dumb stuff hehe
//		if(!(drawLastLink && nbLinks == 1))	// ne veut pas afficher inutilement!
//			toActivate->Dsp_Link();		// dsp le symbole du Link
//
//		nbLinks--;
//	}
//
//}
