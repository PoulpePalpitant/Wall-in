
#include "../player/player.h"
#include "../structure_manager/modify_chain.h"
#include "../bots/botlist.h"
#include "../UI/console_output/render_list.h"
#include "../animation/UI_move_blast.h"
#include "AllGrids.h"
#include "../global_types/global_types.h"
#include "../events/global_events/feedback/ev_blast_splash.h"
#include "../events/msg_dispatcher.h"


extern AllGrids gGrids = {};	

// POINTEURS GLOBAux
extern LinkGrid *const linkGrid = &gGrids.linkGrd;			// Pour alléger l'utilisation des grids.	Pointera toujours vers le même LinkGrid 
extern WallGrid* const wallGridHor = &gGrids.wallGrdHor;
extern WallGrid* const wallGridVer = &gGrids.wallGrdVer;
extern SpawnGrid* const spawnGrid = &gGrids.spawnGrd;				

WallGrid* AllGrids::Find_Wall_Grid_From_Axis(Axis ax)
{
	if (ax == VER)
		return wallGridVer;
	else
		return wallGridHor;
}

WallGrid* AllGrids::Find_Wall_Grid_From_Direction(Direction dir)
{
	if (dir == UP || dir == DOWN)
		return wallGridVer;			
	else
		return wallGridHor;			
}

WallGrid* AllGrids::Find_Wall_Grid_From_Crd_Incrementor(const GridIndexIncrementor &crd)
{
	if (crd.axis == &crd.index.c)	// LEÇON: Tu dois mettre la coord en référence, parce que tu compare Deux ADRESSES. Si tu passe la coord par valeur, ça créé une copie qui n'aura pas la même adresse
		return wallGridVer;			
	else
		return wallGridHor;			
}

GrdCoord AllGrids::Convert_LinkCrd_To_WallCrd(const GridIndexIncrementor &linkCrd)
{
	GrdCoord wallCrd = linkCrd.index;

	if (linkCrd.polar == POS)
		if (linkCrd.axis == &linkCrd.index.c)// Tu déborde du grid mon gars. Le dernier Wall à droite correspond à L'AVANT dernier Link	   1    2    3	|	(Links)		col[3]
			wallCrd.c--;																												 //o----o----o	|Fin
		else																															 //   1   2		|	(walls)		col[2]
			wallCrd.r--;				
	
	return wallCrd;
}

GrdCoord AllGrids::Convert_LinkCrd_To_WallCrd(GrdCoord linkCrd, Direction dir)
{
	if (dir == DOWN)
		linkCrd.r--;				
	else
		if(dir == RIGHT)
			linkCrd.c--;
		return linkCrd;				
}


Wall* AllGrids::Find_Wall_From_Link_Coord_Incrementor(GridIndexIncrementor &incre, Direction dir)				
{
	WallGrid *wallgrid = Find_Wall_Grid_From_Direction(dir);
	GrdCoord wallCrd = {-1,-1};
	GridIndexIncrementor crd = incre;  // The stupidest shit I can witness from my own asshole
	crd.Initialize_Axis(Find_Opposite_Dir(dir));
	wallCrd = Convert_LinkCrd_To_WallCrd(crd);
	
	if (!wallgrid->Is_Inbound(wallCrd))
 		return NULL;

	return &wallgrid->wall[wallCrd.c][wallCrd.r];
}

// Attache ta tuque, ça pu ici
bool AllGrids::Activate_Walls_And_Links_From_Blast(Blast* blast)
{
	int nbOfWalls;	
	static Wall* wall, *impactedWall;		// Wall à activer		/  Un wall est créer par dessus un bot, il faut donc détruire ce wall
	static Link* child, * parent;			// Link à activer et son child
	static WallGrid* wallGRID;				// grid de wall
	static GridIndexIncrementor wallCrd;	// crd du wall
	static GridIndexIncrementor linkCrd;	// Coord de chaque Link à afficher
	bool playerOnLink = false;				// N'affiche pas le link child si le player se trouve dessus
	static bool eraseBlast;					// Ne créer aucun wall. Se produit quand des modifiers se combinent ensemble
	static Teleporter& tp = P1.Get_Teleporter();			/// le teleporteur du joueur					
	bool spaghettiTime = false;				

	parent = child = NULL;
	wall = impactedWall = NULL; wallGRID = NULL;

	linkCrd = blast->grdPos;	
	parent = &linkGrid->link[linkCrd.index.c][linkCrd.index.r];	
	wallGRID = Find_Wall_Grid_From_Direction(blast->dir);		
	wallCrd = linkCrd;	wallCrd.index = gGrids.Convert_LinkCrd_To_WallCrd(linkCrd);	

	// Doit d'abord déterminé si le blast ne fait que convertir un link sans créer de wall, ou si il se smash dans un blocker
	 Deal_With_Modifier_Combinations(blast->grdPos.index, blast->modifier, eraseBlast);

	if (eraseBlast)	// Aucun mur ne sera créé. Un link est probablement convertit, mais on créer rien d'autre
	{
		// Erase whole blast
		UI_MoveBlast::Setup_Blast_Eraser(blast);
		
		linkCrd.Decrement_Coord();
		tp.Set_Teleport_Location(linkCrd.index);
	}
	else
	{
		// Le nombre de murs 
		nbOfWalls = blast->Nb_Of_Walls_Per_Blast();

		while (nbOfWalls)
		{
			// Sert à ne pas lancer le blast_splash quand on tir sur une bordure mais qu'un ROOT était déjà là. Why? parce que je veux pas que l'autre animation
			// de border splash soit effacé par blast-splash
			if (parent->Get_State() != LinkState::DEAD)
				spaghettiTime = true;
			else
				MsgQueue::Register(BLAST_REACHED_BORDER);

			wall = &wallGRID->wall[wallCrd.index.c][wallCrd.index.r];	
			parent = &linkGrid->link[linkCrd.index.c][linkCrd.index.r];	
			linkCrd.Decrement_Coord();	
			child = &linkGrid->link[linkCrd.index.c][linkCrd.index.r];	

			parent->Activate_Link(blast->modifier, wall);		// Active le Link, et le lie à son child
			
			if(parent->Get_Modifier() == Modifier::ENERGIZER)
				wall->Activate_Wall(WallType::ENERGIZED, child, Get_Opp_Polar(linkCrd.polar));	
			else
				wall->Activate_Wall(blast->wallType, child, Get_Opp_Polar(linkCrd.polar));		// active wall. *La polarization inverse est dû au fait que l'on fait le parcours inverse du blast, partant de la fin vers le début

			if (wall->Get_Bot_On_Me() != -1)	// Si y'avait un bot sur le wall qu'on vient de créer, on VA détruire les deux
				impactedWall = wall;

			if (nbOfWalls == 1)
			{
				child->Activate_Link(blast->modifier);			// On active le Child(FREE LINK) qu'une fois, car il n'y en a qu'un seul
				
				if (parent->Get_Modifier() == blast->modifier)	// Si deux modifiers se rencontrent, le link free est obligatoirement modifié
					child->Convert_Modifier(blast->modifier);	
				
			}

			parent->Dsp_Link();	// Draw le link Parent

			wallCrd.Decrement_Coord();	// prochaine coord de wall
			nbOfWalls--;
		}

		if (!(Are_Equal(P1.Get_Grd_Coord(), linkCrd.index)))	// Si le joueur n'est PAS sur le dernier Link child
			child->Dsp_Link();	// affiche le child

		if (impactedWall)
			botList.bot[impactedWall->Get_Bot_On_Me()].Bot_Impact(impactedWall);	// Un mur fut créer par dessus un bot
		else
		{
			if (tp.Validate_Position(*child)) 
				tp.Set_Teleport_Location(linkCrd.index);
			else
			{
				// Le teleporte sera une case plus loin 
				linkCrd.Decrement_Coord();
				if(!Are_Equal( linkCrd.index, P1.Get_Grd_Coord()) && tp.Validate_Position(linkGrid->link[linkCrd.index.c][linkCrd.index.r]))
					tp.Set_Teleport_Location(linkCrd.index);
			}
		}

		// sploosh
		if(!blastP1.Has_Reached_Limit() || spaghettiTime) 
			Add_Blast_Splash(blastP1.dir,blastP1.frontXY.coord);
	}

	return eraseBlast;	// Détermine si on doit attendre d'erase avant de désactivé le blast
}



// Activation Manuelle de chaînes de murs
// **************************************

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
	wallCrd.index = gGrids.Convert_LinkCrd_To_WallCrd(wallCrd.index, dir);
	return wallCrd;
}

// Créer manuellement une chaîne de murs et de Links dans une direction
void AllGrids::Make_Chain_Of_Walls(GrdCoord grdCrd, Direction dir, int numWalls, WallType wallType, Modifier type, GrdCoord movePlayer)
{
	static Wall* wall;						
	static Link* child, * parent;			
	static WallGrid* wallGRID;				
	static LinkState state;					
	static GridIndexIncrementor wallCrd;	
	static GridIndexIncrementor linkCrd;	
	bool playerOnLink = false;				
	
	parent = child = NULL;	
	wall = NULL; wallGRID = NULL;	

	wallGRID = Find_Wall_Grid_From_Direction(dir);	
	linkCrd.Initialize_All(grdCrd, dir);	
	wallCrd = linkCrd;	wallCrd.index = gGrids.Convert_LinkCrd_To_WallCrd(wallCrd);		
	wallCrd.Increment_Coord();

	while (numWalls)
	{
		wall = &wallGRID->wall[wallCrd.index.c][wallCrd.index.r];

		if (linkGrid->Is_Inbound(linkCrd.index)) 
		{
			parent = &linkGrid->link[linkCrd.index.c][linkCrd.index.r];
			state = parent->Get_State();

			if (Are_Equal(P1.Get_Grd_Coord(), linkCrd.index))	
				if (Are_Equal(movePlayer, {-1,-1}))
					return; 
		}
		else
			return;

		linkCrd.Increment_Coord();	

		if (linkGrid->Is_Inbound(linkCrd.index)) // 2eme check
		{
			child = &linkGrid->link[linkCrd.index.c][linkCrd.index.r];
			state = child->Get_State();

			if (state > LinkState::FREE)	// 	le child doit être DEAD sinon...			
				return;

			if (state == LinkState::FREE)	// LE child ne Peut pas être déjà FREE, Sinon tu connect deux Branches!!!
			{
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

		parent->Activate_Link(type, wall);	
		wall->Activate_Wall(wallType, child, wallCrd.polar);	
		
		if (numWalls == 1)
		{
			child->Activate_Link(type);				// On active le Child qu'une fois, car il n'y en a qu'un seul 
			child->Dsp_Link();
		}


		// On affiche juste le parent, car le child pourrait changer de state, et donc de symbole à la prochaine loop. On l'affichera à la fin seulement
		parent->Dsp_Link();	
		wall->Set_Drawer(); 

		wallCrd.Increment_Coord();	// Coord du prochain wall
		numWalls--;	
	}
}

bool AllGrids::Deal_With_Modifier_Combinations(GrdCoord linkCrd, Modifier blastMod, bool& eraseBlast)
{
	Link* link = &linkGrid->link[linkCrd.c][linkCrd.r];
	Modifier linkMod = link->Get_Modifier();
	LinkState linkState = link->Get_State();
	eraseBlast = false;	
	
	if (linkState != LinkState::DEAD)
	{
		switch (blastMod)
		{
		case REGULAR:		
			if (linkMod == BLOCKER)
				eraseBlast = true;
			break;

		case BUFFER:
			if (linkMod == REGULAR)
			{
				link->Convert_Modifier(BUFFER);	

				if (link->Get_Num_Child())	// pas de chaîne à buff si ya pas de child
					ListsOfChainToModify::Add_Chain_To_Modify(linkCrd, link, false, BUFF);	// BUFF tou les childs walls aà partir du Link
				eraseBlast = true;
			}

			if (linkMod == BLOCKER)
				eraseBlast = true;	// Un buffer se fait détruire par blocker
			break;

		case BLOCKER:
			if (linkMod != BLOCKER)
			{
				link->Convert_Modifier(blastMod);	

				if(link->Get_Num_Child())	// pas de chaîne à détruire si ya pas de child
					ListsOfChainToModify::Add_Chain_To_Modify(linkCrd, link, true);	
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
		}
	}
	return true;
}


// SPÉCIAL
// * ** * * 

void AllGrids::Dr_Spawngrid()
{
	Coord crd;
	for (int i = 0; i < 4; i++)	
	{
		for (int j = 0; j < gGrids.spawnGrd.border[i].Get_Num_Spawns(); j++)
		{
			crd = gGrids.spawnGrd.border[i].spawn[j].Get_XY();

			switch (i)
			{
			case 0:crd.y -= 1;break;
			case 1:crd.x -= 2;break;
			case 2:crd.y += 2;break;
			case 3:crd.x += 2;break;

			}

			ConsoleRender::Add_String(std::to_string(j), crd);	
		}
	}

}


void AllGrids::Remove_All_Bots_From_Grid()	// Si tu élimine les bots artificiellement, tu dois aussi les removes
{
	for (int col = 0; col < gGrids.wallGrdHor.Get_Cols(); col++)
		for (int row = 0; row < gGrids.wallGrdHor.Get_Rows(); row++)
			gGrids.wallGrdHor.wall[col][row].Remove_Bot_On_Me();

	for (int col = 0; col < gGrids.wallGrdVer.Get_Cols() ; col++)
		for (int row = 0; row < gGrids.wallGrdVer.Get_Rows(); row++)
			gGrids.wallGrdVer.wall[col][row].Remove_Bot_On_Me();
}

void AllGrids::Activate_Blocker(GrdCoord crd, bool deactivate)	
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

void AllGrids::Activate_Link(GrdCoord crd, Modifier mod,bool deactivate)	
{
	if (crd.c < 0 || crd.r < 0)
		return;

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


void AllGrids::Make_Box_Of_Blockers(GrdCoord start, GrdCoord end, bool erase )
{
	for (int i = start.c; i <= end.c; i++)
	{
		gGrids.Activate_Blocker({ i, start.r }, erase);
		gGrids.Activate_Blocker({ i, end.r }, erase);
	}

	for (int i = start.r; i <= end.r; i++)
	{
		gGrids.Activate_Blocker({ start.c, i }, erase);
		gGrids.Activate_Blocker({ end.c, i }, erase);
	}
}

static bool Validate_Dead_Link(GrdCoord crd) {
	if (linkGrid->Is_Inbound({ crd.c,crd.r }))
		if (linkGrid->link[crd.c][crd.r].Get_State() == LinkState::DEAD)
			return true;
	return false;
}

void AllGrids::Make_Box_Around(GrdCoord center, Distance distance,Modifier mod, bool erase)
{
	int c, r;

	//up 
	for (c = center.c - distance; c < center.c + distance; c++)
		if (Validate_Dead_Link({ c,center.r - distance }))
			gGrids.Activate_Link({ c, center.r - distance }, mod, erase);
	
	//down
	for (c = center.c - distance; c < center.c + distance; c++)
		if (Validate_Dead_Link({ c,center.r + distance }))
			gGrids.Activate_Link({ c, center.r + distance }, mod, erase);

	// Left side right side
	for (r = center.r - distance + 1; r < center.r + distance; r++)
		if (Validate_Dead_Link({ center.c - distance, r }))
			gGrids.Activate_Link({ center.c - distance,r }, mod, erase);

	for (r = center.r - distance; r < center.r + distance + 1; r++)
		if (Validate_Dead_Link({ center.c + distance, r }))
			gGrids.Activate_Link({ center.c + distance,r }, mod, erase);
}

void AllGrids::Extremely_Dumb_Fix_To_Redraw_Walls()	// Le nom le dit: Ceci redraw tout les walls, parce que ça arrive que les walls sont pas bien affichés. Et débuggé cette merde est une perte de temps
{
	// Complete old garbage 		
	for (int r = 0; r < wallGridHor->Get_Rows(); r++)
	{
		for (int c = 0; c < wallGridHor->Get_Cols(); c++)
		{
			if (wallGridHor->wall[c][r].Is_Activated())
				wallGridHor->wall[c][r].Set_Drawer();
		}
	}
	for (int r = 0; r < wallGridVer->Get_Rows(); r++)
	{
		for (int c = 0; c < wallGridVer->Get_Cols(); c++)
		{
			if (wallGridVer->wall[c][r].Is_Activated())
				wallGridVer->wall[c][r].Set_Drawer();
		}
	}
}