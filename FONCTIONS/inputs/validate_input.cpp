
#include <conio.h>
#include <Windows.h>

#include "action_input.h"
#include "../blast/blast.h" // testing
#include "../grid/AllGrids.h"
#include "../player/player.h"
#include "../player/player_move.h"

#include "validate_input.h"



void Validate_Input()
{
	ActionType action = IDLE;
	Direction keyDirection = RESTE_ICITTE;
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
		GrdCoord grdCrd = P1.Get_Grd_Coord();	// Position du joueur
		
		//if(linkGrid->link[grdCrd.c][grdCrd.c].Get_State == LinkState::FREE)		
			// Destroy	// wall transfer// wall transfer// wall transfer// wall transfer// wall transfer// wall transfer// wall transfer// wall transfer// wall transfer


		Blast* blast = blastP1.Blast_Shot(BlastType::REGULAR, P1.Get_Grd_Coord(), keyDirection);	// tir
		gGrids.Activate_Walls_And_Links_From_Blast(blast);					// activation des murs et links
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