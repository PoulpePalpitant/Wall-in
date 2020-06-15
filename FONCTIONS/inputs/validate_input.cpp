
#include <conio.h>
#include <Windows.h>

#include "action_input.h"
#include "../blast/blast.h" // testing
#include "../grid/AllGrids.h"
#include "../player/player.h"
#include "../player/player_move.h"
#include "../structure_manager/structure_manager.h"

#include "validate_input.h"



void Validate_Input()
{
	ActionType action = IDLE;
	Direction keyDirection = NONE;
	int key = _getch();

	// Input autres que des charactères
	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		keyDirection = LEFT;	action = BLAST;											// GETASYNCKEYSTATE, pour un thread
	}

	if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		keyDirection = RIGHT; action = BLAST;
	}

	if (GetKeyState(VK_UP) & 0x8000)
	{
		keyDirection = UP;	action = BLAST;
	}

	if (GetKeyState(VK_DOWN) & 0x8000)
	{
		keyDirection = DOWN;	action = BLAST;
	}

	switch (key)	// Input de charactères
	{
	case 'w':	keyDirection = UP; action = MOVE; break;
	case 'a':	keyDirection = LEFT; action = MOVE; break;	// faire mouvement
	case 's':	keyDirection = DOWN; action = MOVE; break;
	case 'd':	keyDirection = RIGHT;action = MOVE; break;
	case ' ':	break; // pause = truebreak;	// pause = true
	default: key = NULL;
	}



	if (action == MOVE)
	{
		Move_Player(P1, keyDirection);	// bouge le joueuruu!
	}

	if (action == BLAST)	// le type de blast pourrait varier selon le niveau et le statut du joueur
	{
		static GrdCoord grdCrd;	// Position du joueur
		grdCrd = P1.Get_Grd_Coord();	
		
		static Link* link;	// Link se trouvant sur la position du joueur
		link = &linkGrid->link[grdCrd.c][grdCrd.r];

		static Blast* blast;	// da blast
		bool cancelBlast = false;

		// Action Spéciale: Un transfer
		// Le Transfer à lieu quand le joueur se trouve sur un Link FREE. Si il tire dans une autre direction que le parent du Link, le Link FREE est détruit et un blast à lieu. C'est comme si on transférait le Wall
		if (link->Get_State() == LinkState::FREE && link->Get_Type() != LinkType::BLOCKER)// Un blocker empêche les transfer?
		{
			/*
			
			à Pt modifier un jour:		si tu fais un transfert sur une bordure, tu détruis le wall, mais le blast ne franchis aucune distance
			si tu fais un transfert horizontale, la longueur maximale n'est pas limité à un wall...
			*/

			// Si on tir dans la même direction que son parent wall		
			if (StructureManager::Is_Parent_In_This_Direction(link, keyDirection))
				cancelBlast = true; // rien va se passer
			else
				DestroyChainOfWalls::Destroy_Chain_Of_Walls(grdCrd);	// On destroy le Link que l'on veut transférer
			// ensuite on fait un tir normal
		}
		
		if (!cancelBlast)
		{
			blast = blastP1.Blast_Shot(P1.Get_Grd_Coord(), keyDirection);		// tir
			gGrids.Activate_Walls_And_Links_From_Blast(blast);					// activation des murs et links
		}
	}
	


}



//switch (key = _getch())
//{
//case 'w':keyDirection = UP; break;
//case 'a':keyDirection = LEFT; break;
//case 's':keyDirection = DOWN; break;
//case 'd':keyDirection = RIGHT; break;
//case ' ':break; // pause = true
//default: keyDirection = RESTE_ICITTE;	// Reset la direction
//}
//	// Input autres que des charactères
//if (GetKeyState(VK_LEFT) & 0x8000)
//{
//	key = VK_LEFT;	action = BLAST;
//}
//
//if (GetKeyState(VK_RIGHT) & 0x8000)
//{
//	key = VK_RIGHT; action = BLAST;
//}
//
//if (GetKeyState(VK_UP) & 0x8000)
//{
//	key = VK_UP;	action = BLAST;
//}
//
//if (GetKeyState(VK_DOWN) & 0x8000)
//{
//	key = VK_DOWN;	action = BLAST;
//}