#pragma once

#include "grid.h"
#include "../blast/blast.h"
#include "../link/link.h"

// Grid de Links
class LinkGrid : public Grid {
	int Nb_Of_Link_Per_Blast(Blast* blast);		// Calcul le nombre de walls � enregistrer apr�s un blast.



public:
	Link** link;	// Va contenir le Grid contenant les pointeurs vers les arrays de Walls
	
	void Create(int col, int row);	// Cr�er le Grid. Persistera jusqu'au prochain Resize. Assignent une valeur XY pour chacun des �l�ments du Grid
	void Resize(int col, int row);	// Redimensionne.... Mais d�truit aussi le grid...
	// V�rification de la pr�sence d'un Link(vivant) dans le grid
	int Is_Link_Here(int col, int row);						// WHERE IS LINK? I CAN'T FIND HIM!?

	// Cr�er une cha�ne de link � partir d'un blast
	void Activate_Links_From_Blast(Blast* blast);
};

extern LinkGrid linkGrid;	// Le seul et unique, le champion, le dernier de sa grande lign�e de Grid




	// Mmmm. Create et resize ne devrait jamais �tre utilis�s directement, mais uniquement � travers les functions CreateAll
	// Et resize All, au tout premier niveau et � la fin de chaques niveaux. Pour l'instant je sais pas comment s�curiser
	// �a, alors let's proceed! With caution!