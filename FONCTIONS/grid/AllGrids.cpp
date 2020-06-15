
#include "../player/player.h"
#include "../structure_manager/destroy_chain.h"
#include "AllGrids.h"


extern AllGrids gGrids = {};	//	 La variable globale contenant tout les grids

// POINTEURS GLOBAux

extern LinkGrid *const linkGrid = &gGrids.linkGrd;			// Pour alléger l'utilisation des grids.	Pointera toujours vers le même LinkGrid 
extern WallGrid* const wallGridHor = &gGrids.wallGrdHor;
extern WallGrid* const wallGridVer = &gGrids.wallGrdVer;
extern SpawnGrid* const spawnGrid = &gGrids.spawnGrd;				// LE GRID DE SPAWNBORDERS

// Trouve le grid de wall qui correspond à un axe
WallGrid* AllGrids::Find_Wall_Grid_From_Axis(Axis ax)
{
	if (ax == VER)
		return wallGridVer;
	else
		return wallGridHor;
}

// Trouve quel wallgrid correspond à une direction 
WallGrid* AllGrids::Find_Wall_Grid_From_Direction(Direction dir)
{
	if (dir == UP || dir == DOWN)
		return wallGridVer;			// WallGrid vertical
	else
		return wallGridHor;			// Wallgrid horizontal
}

// Trouve quel wallgrid correspond à un axe de direction
WallGrid* AllGrids::Find_Wall_Grid_From_Crd_Incrementor(const GridIndexIncrementor &crd)
{
	if (crd.axis == &crd.index.c)	// LEÇON: Tu dois mettre la coord en référence, parce que tu compare Deux ADRESSES. Si tu passe la coord par valeur, ça créé une copie qui n'aura pas la même adresse
		return wallGridVer;			// WallGrid vertical
	else
		return wallGridHor;			// Wallgrid horizontal
}

// Trouve un wall qui possède la même position qu'un Link avec la polarisation et l'axe
GrdCoord AllGrids::Convert_LinkCrd_To_WallCrd(const GridIndexIncrementor &linkCrd)
{
	GrdCoord wallCrd = linkCrd.index;

	if (linkCrd.polar == POS)// LEÇON: Tu dois mettre la coord en référence, parce que tu compare Deux ADRESSES. Si tu passe la coord par valeur, ça créé une copie qui n'aura pas la même adresse
		if (linkCrd.axis == &linkCrd.index.c)	// Tu déborde du grid mon gars. Le dernier Wall à droite correspond à L'AVANT dernier Link	   1    2    3	|	(Links)		col[3]
			wallCrd.c--;																												 //o----o----o	|Fin
		else																																 //   1   2		|	(walls)		col[2]
			wallCrd.r--;				// Tu déborde du grid mon gars
	
	return wallCrd;
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
	int nbOfWalls;	// Nombre de mur à activer
	static Wall* wall;						// Wall à activer
	static Link* child, * parent;			// Link à activer et son child
	static WallGrid* wallGRID;				// grid de wall
	static GridIndexIncrementor wallCrd;	// crd du wall
	static GridIndexIncrementor linkCrd;	// Coord de chaque Link à afficher
	bool playerOnLink = false;				// N'affiche pas le link child si le player se trouve dessus

	parent = child = NULL;
	wall = NULL; wallGRID = NULL;	/*safety*/

	linkCrd = blast->grdPos;	// positions des links dans le grid
	wallGRID = Find_Wall_Grid_From_Direction(blast->dir);	// Le bon grid
	wallCrd = linkCrd;	wallCrd.index = gGrids.Convert_LinkCrd_To_WallCrd(linkCrd);	// Première Coord de Wall

	// Le nombre de murs 
	nbOfWalls = blast->Nb_Of_Walls_Per_Blast();		

	while (nbOfWalls)
	{
		wall = &wallGRID->wall[wallCrd.index.c][wallCrd.index.r];	// Le wall
		parent = &linkGrid->link[linkCrd.index.c][linkCrd.index.r];	// Le parent
		linkCrd.Decrement_Coord();	// Crd du child
		child = &linkGrid->link[linkCrd.index.c][linkCrd.index.r];	// le child
		
		parent->Activate_Link(blast->linkType, wall);		// Active le Link, et le lie à son child
		wall->Activate_Wall(blast->strength, child, Get_Opp_Polar(linkCrd.polar));		// active wall. *La polarization inverse est dû au fait que l'on fait le parcours inverse du blast, partant de la fin vers le début
		
		// WE STOP, si un bot est sur un mur qu'on veut créer
		if (wall->Get_Bot_On_Me())	// Si y'avait un bot sur le wall qu'on vient de créer, on détruit les deux
		{
			if (Bot::Bot_Impact(Get_Bot_On_Me(), Get_Bot_On_Me(), &wallGrid->wall[grdCrd.index.c][grdCrd.index.r]))	// Im Pact!		



			return;
		}

		if(nbOfWalls == 1)
			child->Activate_Link(blast->linkType);				// On active le Child qu'une fois, car il n'y en a qu'un seul
		
		parent->Dsp_Link();	// Draw le link Parent

		wallCrd.Decrement_Coord();	// prochaine coord de wall
		nbOfWalls--;
	}

	if (!(Is_Equal(P1.Get_Grd_Coord(), linkCrd.index)))	// Si le joueur n'est PAS sur le dernier Link child
		child->Dsp_Link();	// affiche le child
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
	wallCrd.index = gGrids.Convert_LinkCrd_To_WallCrd(wallCrd);
	return wallCrd;
}

// Créer manuellement une chaîne de murs et de Links dans une direction
void AllGrids::Activate_Chain_Of_Walls(GrdCoord grdCrd, Direction dir, int numWalls, WallStrength strength, LinkType type)	
{
	static Wall* wall;						// Wall à activer
	static Link* child, * parent;			// Link à activer et son child
	static WallGrid* wallGRID;				// grid de wall
	static LinkState state;					// Pour vérifier si un Link est existe déjà
	static GridIndexIncrementor wallCrd;	// crd du wall
	static GridIndexIncrementor linkCrd;	// Coord de chaque Link à afficher
	bool playerOnLink = false;				// N'affiche pas le link child si le player se trouve dessus
	
	parent = child = NULL;	
	wall = NULL; wallGRID = NULL;	/*safety*/

	wallGRID = Find_Wall_Grid_From_Direction(dir);	// Le bon grid
	linkCrd.Initialize_All(grdCrd, dir);	// Grd coord du premier Link
	wallCrd = linkCrd;	wallCrd.index = gGrids.Convert_LinkCrd_To_WallCrd(wallCrd);		// Première Coord de Wall
	wallCrd.Increment_Coord();

	while (numWalls)
	{
		wall = &wallGRID->wall[wallCrd.index.c][wallCrd.index.r];

		if (linkGrid->Is_Inbound(linkCrd.index)) // premier check
		{
			parent = &linkGrid->link[linkCrd.index.c][linkCrd.index.r];
			state = parent->Get_State();

			if (state > LinkState::FREE)								//Le parent doit être au maximum free pour activer un link
				return;

			if (Is_Equal(P1.Get_Grd_Coord(), linkCrd.index))	// Si le joueur est sur le Link parent, WE STOP
				return;

		}
		else
			return;	// Ta coord n'est pas dans le grid biiiiig

		linkCrd.Increment_Coord();	// Crd du child

		if (linkGrid->Is_Inbound(linkCrd.index)) // 2eme check
		{
			child = &linkGrid->link[linkCrd.index.c][linkCrd.index.r];
			state = child->Get_State();

			if (state > LinkState::FREE)	// 	le child doit être DEAD sinon...			
				return;

			if (state == LinkState::FREE)	// LE child ne Peut pas être déjà FREE, Sinon tu connect deux Branches!!!
			{
				if (Are_Both_Links_Free(parent, child)) // La fonction est un échec, tu ne peux pas activer 1 mur connectant deux branches existantes
					return;

				parent->Activate_Link(type);	// Il faut activer le parent qui n'aura en fait aucun Child
				parent->Dsp_Link();
				return;
			}		
		}
		else
		{
			parent->Activate_Link(type);	//On a atteint la limite.  Il faut activer le dernier parent qui n'aura en fait aucun Child
			break;
		}

		parent->Activate_Link(type, wall);		// Active le Link, et le lie à son child
		wall->Activate_Wall(strength, child, wallCrd.polar);	// active wall
		
		if (numWalls == 1)
			child->Activate_Link(type);				// On active le Child qu'une fois, car il n'y en a qu'un seul 


		// On affiche juste le parent, car le child pourrait changer de state, et donc de symbole à la prochaine loop. On l'affichera à la fin seulement
		parent->Dsp_Link();	// Draw le link Parent
		wall->UI_Draw_Or_Erase_Wall();	// Draw Le mur!



		wallCrd.Increment_Coord();	// Coord du prochain wall
		numWalls--;	// and here we go again
	}

	if (Is_Equal(P1.Get_Grd_Coord(), linkCrd.index))	// Si le joueur est sur le Link child
		playerOnLink = true;							

	// Si le joueur n'est pas sur le child Link 
	if (!playerOnLink)
		child->Dsp_Link();

}

