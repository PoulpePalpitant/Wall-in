
#include <conio.h>
#include <Windows.h>

#include "action_input.h"
#include "validate_input.h"
#include "../time/timerOP.h"
#include "../events/events.h"

void Validate_Input()
{
	keyDirection = NONE;

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
	case 'q':	action = CHANGE_BLAST; break;
	case 13: if (gChoiceTime) MessageQueue::Register(PRESSED_ENTER); action = ENTER; break;	// 13 = enter
	case ' ':	
		if (!GameLoopClock::pause)
			action = ActionType::PAUSE;
		else
			action = ActionType::UNPAUSE;
		break; 

	default: key = NULL;
	}
}


/* THREAD EXEMPLEs */

////std::thread blastTh(&Blast::Blast_Shot, &blastP1, swag, std::ref(keyDirection), std::ref(BLASTtype)); // Thread pour le blast
//static std::thread blastTh;
//blastTh = std::thread(&Blast::Blast_Shot, &blastP1, swag, std::ref(keyDirection), std::ref(BLASTtype)); // Thread pour le blast

//if (blastTh.joinable())		// thread waiting!
//	blastTh.join();

			//std::thread destroyTHREAD(&DestroyChainOfWalls::Destroy_Chain_Of_Walls, grdCrd);
			//std::thread destroyTHREAD(&DestroyChainOfWalls::LameStaticFunction, false, std::ref(*swa));

