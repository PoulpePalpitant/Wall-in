#pragma once

#include "grid.h"
#include "../link/link.h"

// Grid de Links
class LinkGrid : public Grid {

public:
	Link** link;	
	
	void Create(int col, int row);	
	void Resize(int col, int row);	
	
	int Is_Link_Alive_Here(GrdCoord crd);		// WHERE IS LINK? I CAN'T FIND HIM!?
	bool Is_Link_On_Border(GrdCoord crd);		
};

