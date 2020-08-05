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

void Resize_To_Game_Map();	// redimensionne la fen�tre de console pour que �a fit
void Set_Dflt_WND();		// Fen�tre par d�faut
void Center_WND();			// Met la fen�tre au centre de ton �cran
void Upd_Console_Size();	// Width and height

// SetWindowPos(GAME_WND, HWND_TOP, 363, 0, 1401, 1073, SWP_SHOWWINDOW | SWP_NOZORDER);	// Bonne dimension par d�faut de la fen�tre du jeu
