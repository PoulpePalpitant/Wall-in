#pragma once

#include "grid.h"
#include "../link/link.h"

// Grid de Links
class LinkGrid : public Grid {
	public:
	Link** link;	// Va contenir le Grid contenant les pointeurs vers les arrays de Walls
	void Create(int col, int row);	// Créer le Grid. Persistera jusqu'au prochain Resize. Assignent une valeur XY pour chacun des éléments du Grid
	void Resize(int col, int row);	// Redimensionne.... Mais détruit aussi le grid...
	
	// Vérification de la présence d'un Link(vivant) dans le grid
	bool Is_Link_Here(int col, int row);						// WHERE IS LINK? I CAN'T FIND HIM!?
};

extern LinkGrid linkGrid;	// Le seul et unique, le champion, le dernier de sa grande lignée de Grid




	// Mmmm. Create et resize ne devrait jamais être utilisés directement, mais uniquement à travers les functions CreateAll
	// Et resize All, au tout premier niveau et à la fin de chaques niveaux. Pour l'instant je sais pas comment sécuriser
	// ça, alors let's proceed! With caution!