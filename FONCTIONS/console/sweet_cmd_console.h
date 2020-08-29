#pragma once

#include <Windows.h>

extern HWND GAME_WND; 
extern RECT rect;

extern int gConWidth;
extern int gConHeight;
extern int gTotalRes;

void Change_Font(bool deflt, int size = 16);			// ajuste la taille de charact�re si la screen size est trop petite.
void Hide_Cursor();			// rend le curseur invisible
void Set_Console_Name();	// donne le nom du jeu � la console
void Upd_Console_Size();	// Width and height
void Set_Dflt_WND();		// Fen�tre par d�faut du jeu
void Shake_That_Window();


void Change_Window_Position(); // temp
void Center_WND();			// Met la fen�tre au centre de ton �cran

void Change_Typography();
// SetWindowPos(GAME_WND, HWND_TOP, 363, 0, 1401, 1073, SWP_SHOWWINDOW | SWP_NOZORDER);	// Bonne dimension par d�faut de la fen�tre du jeu
