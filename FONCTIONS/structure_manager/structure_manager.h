
#include "../link/link.h"
#include "../walls/walls.h"
#include "modify_chain.h"


class StructureManager {	
public:
	static void Bond_Link_To_Child(Link* parent, Wall* child);				// Assigne les pointeurs du parent à son child et vice versa
	static void Bond_Wall_To_Child(Wall* parent, Link* child);				// Bon le wall vers son child
	static void Bond_Wall_To_Adjacent_Links(Wall* wall, Link* parent, Link* child);	
	static bool Is_Link_Corrupted(Link* parent);
	static bool Is_Parent_In_This_Direction(Link* link, Direction dir);		// Renseigne sur la position du parent d'un Link
};