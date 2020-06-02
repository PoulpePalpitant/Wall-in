
#include "../player/player.h"

#include "AllGrids.h"


extern AllGrids gGrids = {};	//	 La variable globale contenant tout les grids

// POINTEURS GLOBAux

extern LinkGrid *const linkGrid = &gGrids.linkGrd;			// Pour alléger l'utilisation des grids.	Pointera toujours vers le même LinkGrid 
extern WallGrid* const wallGridHor = &gGrids.wallGrdHor;
extern WallGrid* const wallGridVer = &gGrids.wallGrdVer;
extern SpawnGrid* const spawnGrid = &gGrids.spawnGrd;				// LE GRID DE SPAWNBORDERS


// Trouve quel wallgrid correspond à une direction 
WallGrid* AllGrids::Find_Wall_Grid_From_Direction(Direction dir)
{
	if (dir == UP || dir == DOWN)
		return wallGridVer;			// WallGrid vertical
	else
		return wallGridHor;			// Wallgrid horizontal
}

// Trouve quel wallgrid correspond à un axe de direction
WallGrid* AllGrids::Find_Wall_Grid_From_Crd_Incrementor(GridIndexIncrementor crd)
{
	if (crd.axis == &crd.index.c)
		return wallGridVer;			// WallGrid vertical
	else
		return wallGridHor;			// Wallgrid horizontal
}

// Trouve un wall qui possède la même position qu'un Link avec la polarisation et l'axe
GridIndexIncrementor AllGrids::Convert_LinkCrd_To_WallCrd(GridIndexIncrementor linkCrd)
{
	if (linkCrd.polar == POS)
		if (linkCrd.axis == &linkCrd.index.c)	// Tu déborde du grid mon gars. Le dernier Wall à droite correspond à L'AVANT dernier Link	   1    2    3	|	(Links)		col[3]
			linkCrd.index.c--;																												 //o----o----o	|Fin
		else																																 //   1   2		|	(walls)		col[2]
			linkCrd.index.r--;				// Tu déborde du grid mon gars
	
	return linkCrd;
}

// Trouve un wall qui possède la même position qu'un Link avec la direction
GrdCoord AllGrids::Convert_LinkCrd_To_WallCrd(GrdCoord linkCrd, Direction dir)
{
	if (dir == DOWN)// Tu déborde du grid mon gars
		linkCrd.r--;				
	else
		if(dir == RIGHT)
			linkCrd.c--;
		return linkCrd;				// Tu déborde du grid mon gars. Le dernier Wall à droite correspond à L'AVANT dernier Link	   1    2    3	|	(Links)		col[3]																															 //o----o----o	|Fin																															 //   1   2		|	(walls)		col[2]
}



// Activation d'éléments sur les grids:
// ***********************************

void AllGrids::Activate_Walls_And_Links_From_Blast(Blast* blast)
{
	static bool drawPlayer;														// Affiche le joueur, si le dernier Link se retrouve sur la même position		//DONT TRY TO UNDESTAND, KEEP GOING, WE DOIN THIS
	blast->length >= blast->nbSteps ? drawPlayer = true : drawPlayer = false;	// Le dernier Link sera certainemennt sur la même position que le joueur
	P1.Upd_Sym_From_Direction(blast->dir);	P1.Dis_Player_Sym();				// Affiche le joueur

	linkGrid->Activate_Links_From_Blast(blast, drawPlayer);	
	// bound Link to wall?
	Find_Wall_Grid_From_Direction(blast->dir)->Activate_Walls_From_Blast(blast);	// Active les murs sur le bon grid de wall
}



// Activation Manuelle
// *******************

// Si la pair de Link autours du wall sont Free, on doit stopper tout. Why? Parce que ça connecterais deux branches de walls ensemble!!
static bool Are_Both_Links_Free(Link* parent, Link* child)
{
	if (parent->Get_State() == LinkState::FREE && child->Get_State() == LinkState::FREE)
		return true;

	return false;
}

static GridIndexIncrementor Find_First_Wall_Crd(const WallGrid &grid, const GrdCoord &linkCrd, const Direction &dir)
{
	GridIndexIncrementor wallCrd;

	wallCrd.Initialize_All(linkCrd, dir);
	wallCrd = gGrids.Convert_LinkCrd_To_WallCrd(wallCrd);
	return wallCrd;
}

// Créer manuellement une chaîne de murs et de Links dans une direction
void AllGrids::Activate_Chain_Of_Walls(GrdCoord grdCrd, Direction dir, int numWalls, WallStrength strength, LinkType type)	
{
	/* je dois merge les deux trucs ici*/

	static Wall* wall;						// Wall à activer
	static Link* child, * parent;			// Linka à activer et son child
	static WallGrid* wallGRID;				// grid de wall
	static LinkState state;					// Pour vérifier si un Link est existe déjà
	static GridIndexIncrementor wallCrd;	// crd du wall
	static GridIndexIncrementor linkCrd;	// Coord de chaque Link à afficher
	bool playerOnLink = false;				// N'affiche pas le link child si le player se trouve dessus
	
	parent = child = NULL;	
	wall = NULL; wallGRID = NULL;	/*safety*/

	wallGRID = Find_Wall_Grid_From_Direction(dir);	// Le bon grid
	Find_First_Wall_Crd(*wallGRID, grdCrd, dir);	// Première Coord de Wall
	
	while (numWalls)
	{
		if (linkGrid->Is_Inbound(linkCrd.index.c, linkCrd.index.r)) // premier check
		{
			parent = &linkGrid->link[linkCrd.index.c][linkCrd.index.r];
			state = parent->Get_State();
			if(state > LinkState::FREE)								//Le parent doit être au maximum free pour activer un link
				if (Is_Equal(P1.Get_Grd_Coord(), linkCrd.index))	// Si le joueur est sur le Link parent, WE STOP
				{
					playerOnLink = true;	// On créé pas un Link par-dessus le joueur. Sauf si c'est un child
					break;
				}
		}

		linkCrd.Increment_Coord();	// Crd du child

		if (linkGrid->Is_Inbound(linkCrd.index.c, linkCrd.index.r)) // 2eme check
		{
			child = &linkGrid->link[linkCrd.index.c][linkCrd.index.r];
			state = child->Get_State();
			if (state > LinkState::FREE)						//Le parent doit être au maximum free pour activer un link
				break;
		}

		if (Are_Both_Links_Free(parent, child))
			break;

		parent->Activate_Link(type, child);		// Active le Link, et le lie à son child
		child->Activate_Link(type);				// Eh oui, le child n'aura pas de child, ce qui veut dire qu'il devra être activé une seconde fois
		wallGRID->wall[wallCrd.index.c][wallCrd.index.r].Activate_Wall(strength);			// active wall

		// On affiche juste le parent, car le child pourrait changer de state, et donc de symbole à la prochaine loop. On l'affichera à la fin seulement
		parent->Dsp_Link();	// Draw le link Parent
		wallGRID->wall[wallCrd.index.c][wallCrd.index.r].UI_Draw_Wall(wallCrd.polar);	// Draw Le mur!
		wallCrd.Increment_Coord();	// Coord du prochain wall
		numWalls--;	// and here we go again
	}

	// Si le joueur n'est pas sur le child Link 
	if (!playerOnLink)
		child->Dsp_Link();

}

