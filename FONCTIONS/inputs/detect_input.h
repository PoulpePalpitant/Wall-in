#pragma once

void Set_Input_Buffer_Handle();	// pour d�tecter les keyboard events
void Input_Thread_Handler();	// pour le thread 
void Read_Input_Buffer();		// d�tection d'input potentiel
void Handle_Input();			// Truc � faire avec les inputs
void Load_Loop_Buffer();		// detect 1 input entre deux frame et la conserve au cas ou le joueur p�se sur un piton entre deux frame

