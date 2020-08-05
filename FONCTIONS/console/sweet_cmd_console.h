#pragma once

#include <Windows.h>

extern HWND GAME_WND; 
extern RECT rect;

extern int gConWidth;
extern int gConHeight;
extern int gTotalRes;

void Change_Typography();
void Shake_That_Window();
void Setup_Console_Window();			// temp
void Change_Window_Position(); // temp

void Resize_To_Game_Map();	// redimensionne la fenêtre de console pour que ça fit
void Set_Dflt_WND();		// Fenêtre par défaut
void Center_WND();			// Met la fenêtre au centre de ton écran
void Upd_Console_Size();	// Width and height

// SetWindowPos(GAME_WND, HWND_TOP, 363, 0, 1401, 1073, SWP_SHOWWINDOW | SWP_NOZORDER);	// Bonne dimension par défaut de la fenêtre du jeu
