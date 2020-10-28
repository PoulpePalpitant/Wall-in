
#include "../player/player.h"
#include "../structure_manager/modify_chain.h"
#include "../bots/botlist.h"
#include "../UI/console_output/render_list.h"
#include "../animation/UI_move_blast.h"
#include "AllGrids.h"
#include "../global_types/global_types.h"

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

bool AllGrids::Activate_Walls_And_Links_From_Blast(Blast* blast)
{
	int nbOfWalls;	// Nombre de mur à activer
	static Wall* wall, *impactedWall;		// Wall à activer		/  Un wall est créer par dessus un bot, il faut donc détruire ce wall
	static Link* child, * parent;			// Link à activer et son child
	static WallGrid* wallGRID;				// grid de wall
	static GridIndexIncrementor wallCrd;	// crd du wall
	static GridIndexIncrementor linkCrd;	// Coord de chaque Link à afficher
	bool playerOnLink = false;				// N'affiche pas le link child si le player se trouve dessus
	static bool eraseBlast;			// Ne créer aucun wall. Se produit quand des modifiers se combinent ensemble

	// activate walls?
	// ou juste convert link?

	parent = child = NULL;
	wall = impactedWall = NULL; wallGRID = NULL;	/*safety*/

	linkCrd = blast->grdPos;	/* positions des links dans le grid*/			
	parent = &linkGrid->link[linkCrd.index.c][linkCrd.index.r];	// Le parent
	wallGRID = Find_Wall_Grid_From_Direction(blast->dir);	// Le bon grid
	wallCrd = linkCrd;	wallCrd.index = gGrids.Convert_LinkCrd_To_WallCrd(linkCrd);	// Première Coord de Wall

	// Doit d'abord déterminé si le blast ne fait que convertir un link sans créer de wall, ou si il se smash dans un blocker

	 Deal_With_Modifier_Combinations(blast->grdPos.index, blast->modifier, eraseBlast);

	if (eraseBlast)	// Aucun mur ne sera créé. Un link est probablement convertit, mais on créer rien d'autre
	{
		// Erase whole blast
		UI_MoveBlast::Setup_Blast_Eraser(blast);
	}
	else
	{
		// Le nombre de murs 
		nbOfWalls = blast->Nb_Of_Walls_Per_Blast();

		while (nbOfWalls)
		{
			wall = &wallGRID->wall[wallCrd.index.c][wallCrd.index.r];	// Le wall
			parent = &linkGrid->link[linkCrd.index.c][linkCrd.index.r];	// Le parent
			linkCrd.Decrement_Coord();	// Crd du child
			child = &linkGrid->link[linkCrd.index.c][linkCrd.index.r];	// le child

			parent->Activate_Link(blast->modifier, wall);		// Active le Link, et le lie à son child
			wall->Activate_Wall(blast->strength, child, Get_Opp_Polar(linkCrd.polar));		// active wall. *La polarization inverse est dû au fait que l'on fait le parcours inverse du blast, partant de la fin vers le début

			// WE won't STOP, si un bot est sur un mur qu'on veut créer
			if (wall->Get_Bot_On_Me() != -1)	// Si y'avait un bot sur le wall qu'on vient de créer, on VA détruire les deux
				impactedWall = wall;

			if (nbOfWalls == 1)
			{
				child->Activate_Link(blast->modifier);				// On active le Child qu'une fois, car il n'y en a qu'un seul
				
				if (parent->Get_Modifier() == blast->modifier)	// Si deux modifiers se rencontrent, le link free est obligatoirement modifié
					child->Convert_Modifier(blast->modifier);	// Si le link free est modifié, alors on peut pas piler dessus
				
			}

			parent->Dsp_Link();	// Draw le link Parent

			wallCrd.Decrement_Coord();	// prochaine coord de wall
			nbOfWalls--;
		}

		if (!(Are_Equal(P1.Get_Grd_Coord(), linkCrd.index)))	// Si le joueur n'est PAS sur le dernier Link child
			child->Dsp_Link();	// affiche le child

		if (impactedWall)
			botList.bot[impactedWall->Get_Bot_On_Me()].Bot_Impact(impactedWall);	// Im pact. Un mur fut créer par dessus un bot
	}

	return eraseBlast;	// Détermine si on doit attendre d'erase le avant de désactivé le blast
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
void AllGrids::Make_Chain_Of_Walls(GrdCoord grdCrd, Direction dir, int numWalls, WallStrength strength, Modifier type, bool multipleRoot)
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

	//ConsoleRender::Create_Animation_Queue(100);	// Début de l'animation

	while (numWalls)
	{
		wall = &wallGRID->wall[wallCrd.index.c][wallCrd.index.r];

		if (linkGrid->Is_Inbound(linkCrd.index)) // premier check
		{
			parent = &linkGrid->link[linkCrd.index.c][linkCrd.index.r];
			state = parent->Get_State();

			//if (state > LinkState::FREE)								//Le parent doit être au maximum free pour activer un link
			//	return;

			if (Are_Equal(P1.Get_Grd_Coord(), linkCrd.index))	// Si le joueur est sur le Link parent, WE STOP
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
				if(!multipleRoot)
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
		{
			child->Activate_Link(type);				// On active le Child qu'une fois, car il n'y en a qu'un seul 
			child->Dsp_Link();
		}


		// On affiche juste le parent, car le child pourrait changer de state, et donc de symbole à la prochaine loop. On l'affichera à la fin seulement
		parent->Dsp_Link();	// Draw le link Parent
		wall->Set_Drawer(); // wall->UI_Draw_Or_Erase_Wall(true);	// Draw Le mur!

		wallCrd.Increment_Coord();	// Coord du prochain wall
		numWalls--;	// and here we go again
	}

	//ConsoleRender::Stop_Queue();	// fin de l'animation

	//if (Is_Equal(P1.Get_Grd_Coord(), linkCrd.index))	// Si le joueur est sur le Link child
	//	playerOnLink = true;							

	//// Si le joueur n'est pas sur le child Link	//sad
	//if (!playerOnLink)
	//	child->Dsp_Link();

}

bool AllGrids::Deal_With_Modifier_Combinations(GrdCoord linkCrd, Modifier blastMod, bool& eraseBlast)
{
	Link* link = &linkGrid->link[linkCrd.c][linkCrd.r];
	Modifier linkMod = link->Get_Modifier();
	LinkState linkState = link->Get_State();
	eraseBlast = false;	// majority
	
	if (linkState != LinkState::DEAD)
	{
		switch (blastMod)
		{
		case REGULAR:		
			if (linkMod == BLOCKER)
				eraseBlast = true;
			break;

		case BUFFER:
			if (linkMod == BUFFER)
			{
				/* behaviour à déterminer*/	break;
			}

			if (linkMod == REGULAR)
			{
				if (link->Get_Num_Child())	// pas de chaîne à buff sans child
				{
					link->Convert_Modifier(BUFFER);	// convertit le link en buffer
					ListsOfChainToModify::Add_Chain_To_Modify(linkCrd, link, false, BUFF);	// BUFF tou les childs walls aà partir du Link
					eraseBlast = true;
				}
			}

			if (linkMod == BLOCKER)
				eraseBlast = true;	// Un buffer se fait détruire par blocker
			break;

		case BLOCKER:
			if (linkMod == BLOCKER) // faudrait créer un autre wall avec un blocker sinon? lol
			{
				// Parent destruction
			}
			else
			{
				// Si le Link était une root, faudrait tout chopper, non.... ? je pense pas en fait
				//if (link->Get_State() == LinkState::ROOT)
					//ListsOfChainToModify::Add_Chain_To_Modify({}, link, false, DESTROY);	// destroy le Link

				link->Convert_Modifier(blastMod);	// Convertit en blocker

				if(link->Get_Num_Child())	// pas de chaîne à détruire si ya pas de child
					ListsOfChainToModify::Add_Chain_To_Modify(linkCrd, link, true);	// Détruit la whole chaine
				eraseBlast = true;
			}

			break;

		case CORRUPTER:
			if (linkMod == BLOCKER || linkMod == BUFFER) // CONVERT: Convertit en corrupter, sans appliquer d'autres effets
			{
				link->Convert_Modifier(blastMod);	// Convertit en corrupter
				eraseBlast = true;
			}else
				if (linkMod == CORRUPTER)
				{
					// Convertit les parents?
				}
				else
					if (linkMod == REGULAR)
					{
						
						if (link->Get_Num_Child())	// pas de chaîne à convertir sans child
						{
							link->Convert_Modifier(CORRUPTER);	// convertit le link en corrupter
							ListsOfChainToModify::Add_Chain_To_Modify(linkCrd, link, false, CORRUPT);	// BUFF tou les childs walls aà partir du Link
							eraseBlast = true;
						}
					}
			break;

		case COLOR_A:
			if (linkMod == COLOR_B)
				eraseBlast = true;
			break;/* Destroy rest of blast*/

		case COLOR_B:
			if (linkMod == COLOR_A)
				eraseBlast = true;
			break;/* Destroy rest of blast*/


			//  YO, quAND TU TIR SUR LE MÊME TYPE, LE FREE LINK AU BOUTE EST AUTOMATIQUEMENT CONVERTIT

			// OU

			// L'EFFET SE PROPAGE AU PARENTS AUSSI!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

		}
	}
	else
	{
		///* Par défault, tout les modifiers vont créer des murs quand il atteigned la bordure. Ils vont aussi créer une ROOT, qui sra indestructible, mais modifiables
		// le child sera impassable également

		////if (blastMod != REGULAR)
		//{
		//		link->Activate_Root_Link(blastMod);		// créer le link tu seul
		//		link->Convert_Modifier(BLOCKER);	// ensuite le convertit
		//		eraseBlast = true;
		//}

	}
	return true;
}



void AllGrids::Corrupt_All_Children()
{

	// peut-t'elle convertir un blocker????

}
void AllGrids::Buff_All_Child_Walls()
{

// si un link est corrupt, n'ajoute pas ses childs walls dans la liste à buffer

}



// SPÉCIAL
// * ** * * 
void AllGrids::Remove_All_Bots_From_Grid()	// Si tu élimine les bots artificiellement, tu dois aussi les removes
{
	for (int col = 0; col < gGrids.wallGrdHor.Get_Cols(); col++)
		for (int row = 0; row < gGrids.wallGrdHor.Get_Rows(); row++)
			gGrids.wallGrdHor.wall[col][row].Remove_Bot_On_Me();

	for (int col = 0; col < gGrids.wallGrdVer.Get_Cols() ; col++)
		for (int row = 0; row < gGrids.wallGrdVer.Get_Rows(); row++)
			gGrids.wallGrdVer.wall[col][row].Remove_Bot_On_Me();
}

void AllGrids::Activate_Blocker(GrdCoord crd, bool deactivate)	// Active un blocker sUR UNE COORD. OU LE DÉSACTIVE
{
	if (crd.c < 0 || crd.r < 0)
		return;

	Modifier mod = BLOCKER;
	if (deactivate)
	{
		linkGrd.link[crd.c][crd.r].Deactivate_Link();
		linkGrd.link[crd.c][crd.r].Er_Link();
	}
	else
	{
		linkGrd.link[crd.c][crd.r].Activate_Link(mod);
		linkGrd.link[crd.c][crd.r].Dsp_Link();
	}
}