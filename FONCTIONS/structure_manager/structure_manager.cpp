

#include "structure_manager.h"

// Assigne les pointeurs du parent à son child et vice versa
void StructureManager::Bond_Link_To_Child(Link* parent, Wall* child)
{
	if (child == NULL)	// Pas d'enfant icitte moé
		return;	

	/*mutex*/
	for (int i = 0; i < 4; i++)	// 4 = max number of childs. For real, si tu fais cette fonctions et qu'ya déjà 4 child, ta foiré quelque part Lol
	{
		if (parent->pWalls[i] == NULL)
		{
			parent->pWalls[i] = child;	// Voici ton fils
			child->pParent = parent;		// Voici ton père		/*je vais le faire au moment de créer le wall*/ 
			parent->numChild++;
			break;
		}
	}
	
	/*if(numChild++ == 0)
	Set_state*/
	/*mutex*/
}

 void StructureManager::Bond_Wall_To_Child(Wall* parent, Link* child)				// Bond le wall avec son child
{
	 parent->pChild = child;		// voici ton Link
	 child->pParent = parent;		// voici ton parent
}

 // tous ensemble!
void StructureManager::Bond_Wall_To_Adjacent_Links(Wall* wall, Link* parent, Link* child)
{		
	Bond_Link_To_Child(parent, wall);
	Bond_Wall_To_Child(wall, child);
}


// Vérifie si le Link parent est Corrompue
bool StructureManager::Is_Link_Corrupted(Link* parent)
{
	if (parent->Get_Modifier() == Modifier::CORRUPTER)
		return true;
	else
		return false;
}

// Check si le parent est dans une certaine direction
bool StructureManager::Is_Parent_In_This_Direction(Link* link, Direction dir)
{
	/*mutex*/
	Wall* parntWall; 
	parntWall = link->pParent;

	return Is_Same_Direction(dir, parntWall->axis, Get_Opp_Polar(parntWall->childPos));	// childPos = à la position du child, on veut celle du parent, c'est donc l'opposé
	/*mutex everything damn it*/
}

