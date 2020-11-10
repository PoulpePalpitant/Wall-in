

#include "detect_input.h"
#include <windows.h>
#include <stdio.h>
#include <thread>
#include "../UI/console_output/render_list.h"
// ceci
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
static int loopBuffer;		// Ceci va enregistrer la dernière touche p`ser entre deux loop pour essayer d'éviter que le jeu detect pas un input
static bool keyHandled = false;	// Si un input à été traité avec succès
/* Ceci est basé sur le modèle d'exemple de l'utilisation de la fonction "Reading Input Buffer Events" sur le site web de microsoft. J'ai enlevé quelque truc comme la détection des mouse events, ou la redimension
du buffer size*/

/* V2 */


//void KeyEventProc(KEY_EVENT_RECORD);

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

	fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;	// pt nécessaire
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

// V1
//void Read_Input_Buffer()
//{
//	static DWORD cNumRead;
//	static int counter;
//
//	cNumRead = 0;	 //reset
//
//	// Wait for the events. 
//	if (!PeekConsoleInput(
//		buffHandle,      // input buffer handle 
//		buffer,     // buffer to read into 
//		128,         // size of read buffer 
//		&cNumRead)) // number of records read 
//		ExitProcess(0);
//
//	// Dispatch the events to the appropriate handler. 
//
//	//for (counter = 0; counter < cNumRead; counter++)// Test de juste prendre le dernier piton
//	{
//		counter = cNumRead - 1; // Test de juste prendre le dernier piton
//		
//		if (buffer[counter].EventType == KEY_EVENT)
//		{
//			keyCode = buffer[counter].Event.KeyEvent.wVirtualKeyCode;
//			if (gMenuInputs)
//			{
//				gMenuKey = keyCode;
//				MsgQueue::Register(PRESSED_KEY);
//			}
//			else
//			switch (keyCode)	// Input de charactères
//			{
//			case VK_LEFT:
//				if (input.buttons[ARROW_LEFT].isDown)
//					input.buttons[ARROW_LEFT].isDown = false;
//				else {
//					input.buttons[ARROW_LEFT].isDown = true;
//					input.buttons[ARROW_LEFT].changed = true;
//					keyDirection = LEFT;		action = BLAST;
//				}
//				break;
//
//			case VK_RIGHT:
//				input.buttons[ARROW_RIGHT].isDown = true;
//				input.buttons[ARROW_RIGHT].changed = true;
//				keyDirection = RIGHT;	action = BLAST;	break;
//			case VK_UP:
//				input.buttons[ARROW_UP].isDown = true;
//				input.buttons[ARROW_UP].changed = true;
//				keyDirection = UP;		action = BLAST;break;
//			case VK_DOWN: 
//				input.buttons[ARROW_DOWN].isDown = true;
//				input.buttons[ARROW_DOWN].changed = true;
//				keyDirection = DOWN;	action = BLAST;break;
//
//			case 'W':case 'w':	
//				input.buttons[MOVE_UP].isDown = true;
//				input.buttons[MOVE_UP].changed = true;
//				keyDirection = UP; action = MOVE; break;
//			case 'A':case 'a':
//				if (input.buttons[MOVE_LEFT].isDown)
//					input.buttons[MOVE_LEFT].isDown = false;
//				else
//				{
//					input.buttons[MOVE_LEFT].isDown = true;
//					input.buttons[MOVE_LEFT].changed = true;
//					keyDirection = LEFT; action = MOVE; 
//				}
//				break;	// faire mouvement
//			case 'S':case 's':
//				input.buttons[MOVE_DOWN].isDown = true;
//				input.buttons[MOVE_DOWN].changed = true;
//				keyDirection = DOWN; action = MOVE; break;
//			case 'D':case 'd':
//				input.buttons[MOVE_RIGHT].isDown = true;
//				input.buttons[MOVE_RIGHT].changed = true;
//				keyDirection = RIGHT;action = MOVE; break;
//
//			case 'Q':case 'q':	action = CHANGE_BLAST; break;
//
//			case 27:
//				if (gProceedTime)	/* Esc */
//				{
//					MsgQueue::Register(PROCEED);
//					gProceedTime = false;
//				}
//				break;
//
//			case 13:	/* enter */
//				if (ChoiceTime::Is_Choice_Time())
//					ChoiceTime::Apply_Choice();
//
//				MsgQueue::Register(PRESSED_ENTER);
//				action = ENTER;
//				break;	// 13 = enter
//
//			case ' ':
//				if (!GameLoopClock::pause)
//					action = ActionType::PAUSE;
//				else
//					action = ActionType::UNPAUSE;
//				break;
//			default: keyCode = NULL;
//			}
//
//		}
//	}
//
//	Handle_Input();
//	FlushConsoleInputBuffer(buffHandle);
//	Refresh_Buffer();
//	Reset_For_Next_Frame();
//}

void Handle_Input()
{
	switch (keyCode)	// Input de charactères
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
	case 'J':case 'j':	lastKey = KeyPressed::JERRY; break;
	case 'R':case 'r':			
		if (gDayStarted)
		{
			
			gRetryCheckpoint = false;
			gPauseUpdates = false;
			MsgQueue::Register(LOAD_CHECKPOINT);
		}
		else
			gRefreshStage = true; 
		break;	
	// Refresh un stage, quand c'est possible
	//case 'P':case 'p':
	//break;	//Skip le stage actuel, on avance

	case 27: /*Esc */
		if (!gPauseUpdates)
			action = ActionType::PAUSE;
		else
			action = ActionType::UNPAUSE;
		break;

	case 13:	/* enter */
		
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

// Cette version de détection d'input prend uniquement en compte les touches clavier "pressed", et non release. On Prend le dernier élément d'enregistré uniquement. Si celui-ci est un release, on prend l'autre d'avant
// et ainsi de suite. Il sera donc impossible de peser plus qu'un piton en même temps
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