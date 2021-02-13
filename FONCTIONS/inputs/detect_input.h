#pragma once

void Set_Input_Buffer_Handle();	// pour détecter les keyboard events
void Input_Thread_Handler();	// pour le thread 
void Read_Input_Buffer();		// détection d'input potentiel
void Handle_Input();			// Truc à faire avec les inputs
void Load_Loop_Buffer();		// detect 1 input entre deux frame et la conserve au cas ou le joueur pèse sur un piton entre deux frame

