

#include "detect_input.h"
#include <windows.h>
#include <stdio.h>
#include <thread>
#include "../UI/console_output/render_list.h"
#include "action_input.h"

#include "../time/timerOP.h"
#include "../events/msg_dispatcher.h"
#include "../choice/choice_time.h"
#include "../lvls/lvl_script.h"
#include "../update_game/update_game.h"

#include "button_state.h"

static HANDLE buffHandle;
static DWORD fdwMode;
static HANDLE flush;
static INPUT_RECORD buffer[128];
static DWORD cNumRead;

static int keyCode;
static int lastKeyPressed;
static int loopBuffer;			// Ceci va enregistrer la derni�re touche p`ser entre deux loop pour essayer d'�viter que le jeu detect pas un input
static bool keyHandled = false;	// Si un input � �t� trait� avec succ�s


/* Ceci est bas� sur le mod�le d'exemple de l'utilisation de la fonction "Reading Input Buffer Events" sur le site web de microsoft. 
J'ai enlev� quelque truc comme la d�tection des mouse events, ou la redimension
du buffer size*/

void KeyEventProc(KEY_EVENT_RECORD ker)
{
	static std::string event = "Key event:";
	static std::string pressed = "Pressed";
	static std::string released = "Released";
	static int y = 2;

	// key
	ConsoleRender::Add_String(event, {0, y});
	
	if (ker.bKeyDown)
	{
		ConsoleRender::Add_String(pressed, { 11, y });
		keyCode = ker.wVirtualKeyCode;
	}
	else
	{
		ConsoleRender::Add_String(released, { 11, y });
	}

	++y == 6 ? y = 2: y;

}

void Set_Input_Buffer_Handle()
{
	buffHandle = GetStdHandle(STD_INPUT_HANDLE);
	if (buffHandle == INVALID_HANDLE_VALUE)
		ExitProcess(0);

	fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;	
}

void Refresh_Buffer()
{	
	for (int i = 0; i < 128; i++)	
		buffer[i] = {};
}

Input input = {};

void Reset_For_Next_Frame()
{
	for (int i = 0; i < Buttons::BUTTON_COUNT; i++)
		input.buttons[i].changed = false;
}

void Handle_Input()
{
	switch (keyCode)	// Input de charact�res
	{
	case VK_LEFT:	keyDirection = LEFT;	action = BLAST;	break;
	case VK_RIGHT:	keyDirection = RIGHT;	action = BLAST;	break;
	case VK_UP:		keyDirection = UP;		action = BLAST;break;
	case VK_DOWN:	keyDirection = DOWN;	action = BLAST;break;

	case 'W':case 'w':	keyDirection = UP; action = MOVE; break;
	case 'A':case 'a':	keyDirection = LEFT; action = MOVE;	break;	// faire mouvement
	case 'S':case 's':	keyDirection = DOWN; action = MOVE; break;
	case 'D':case 'd':	keyDirection = RIGHT;action = MOVE; break;
	case 'Q':case 'q':	break;

	case 'P':case 'p':	lastKey = KeyPressed::JERRY; break;
	case 'R':case 'r':			
		if (gLevelStarted)
		{
			
			gRetryCheckpoint = false;
			gPauseUpdates = false;
			MsgQueue::Register(LOAD_CHECKPOINT);
		}
		else
			gRefreshStage = true; 
		break;	

	case 27: /*Esc */
		if (!gPauseUpdates)
			action = ActionType::PAUSE;
		else
			action = ActionType::UNPAUSE;
		break;

	case 13:	/* enter */
		if (gLevelStarted)
		{
			if (gPauseUpdates)
			{
				action = ActionType::UNPAUSE;
				gCurrentPuzzle[gCurrentLevel - 1] = 0;	// Reset le checkpoint au premier puzzle du niveau
				MsgQueue::Register(LOAD_CHECKPOINT);
				return;
			}
		}
 
		if (ChoiceTime::Is_Choice_Time())
			ChoiceTime::Apply_Choice();
		else
			if (gProceedTime)
			{
				MsgQueue::Register(PROCEED);
				gProceedTime = false;
			}

		MsgQueue::Register(PRESSED_ENTER);
		action = ENTER;
		break;	// 13 = enter

	case ' ':
		if (gPauseUpdates)	// Quand le jeu est en pause, tu va avoir le choix de retourner au menu principal	
		{
			MsgQueue::Register(RETURN_TO_MENU);
			gPauseUpdates = false;
		}
		else
			action = TELEPORT;


		break;
	}

	lastKeyPressed = keyCode;
	keyHandled = true;
}

// Cette version de d�tection d'input prend uniquement en compte les touches clavier "pressed", et non release. On Prend le dernier �l�ment d'enregistr� uniquement. Si celui-ci est un release, on prend l'autre d'avant
// et ainsi de suite. Il sera donc impossible de peser plus qu'un piton en m�me temps
// version 2

bool Check_Key_Hold()
{
	if(lastKeyPressed == keyCode)
			return true; 

	return false;
}

void Input_Thread_Handler()
{
	while (true)
	{
		Read_Input_Buffer();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void Read_Input_Buffer()
{
	static int counter;

	cNumRead = 0;	 //reset

	// Wait for the events. 
	if (!PeekConsoleInput(
		buffHandle,      // input buffer handle 
		buffer,     // buffer to read into 
		128,         // size of read buffer 
		&cNumRead)) // number of records read 
		ExitProcess(0);

	// Dispatch the events to the appropriate handler. 
	for (counter = cNumRead - 1; counter >= 0; counter--)// Test de juste prendre le dernier piton
	{
		if (buffer[counter].EventType == KEY_EVENT)
		{
			keyCode = buffer[counter].Event.KeyEvent.wVirtualKeyCode;

			if (gMenuInputs)
			{
				gMenuKey = keyCode;

				if(gMenuKey == 'Q' || gMenuKey == 'q')
					GameLoopClock::Stop();	// stop de game right here folks

				MsgQueue::Register(PRESSED_KEY);
			}
			else
			{
				if (Check_Key_Hold())
					if (!buffer[counter].Event.KeyEvent.bKeyDown) // fuck les key hold
						lastKeyPressed = NULL;
					else
						continue;

				if (buffer[counter].Event.KeyEvent.bKeyDown && buffer[counter].Event.KeyEvent.wRepeatCount == 1)// si le bouton n'est pas release/hold, mais pressed
					Handle_Input();
			}
			
		}
	}

	if (!keyHandled && loopBuffer)	//back up
	{
		keyCode = loopBuffer;
		Handle_Input();
	}

	keyHandled = loopBuffer = NULL;
	FlushConsoleInputBuffer(buffHandle);
	Refresh_Buffer();
}

void Load_Loop_Buffer()
{
	static int lastInput;
	// Wait for the events. 
	PeekConsoleInput(
		buffHandle,      // input buffer handle 
		buffer,     // buffer to read into 
		128,         // size of read buffer 
		&cNumRead); // number of records read 

	lastInput = cNumRead - 1;	// Dernier piton

	if (buffer[lastInput].EventType == KEY_EVENT)
		if (buffer[lastInput].Event.KeyEvent.bKeyDown && buffer[lastInput].Event.KeyEvent.wRepeatCount == 1)// si le bouton n'est pas release/hold, mais pressed
			loopBuffer = buffer[lastInput].Event.KeyEvent.wVirtualKeyCode;
}