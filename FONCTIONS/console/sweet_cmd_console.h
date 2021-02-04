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

void Change_Window_Position(); 
void Center_WND();

void Change_Typography();
void Hide_Scrollbar();
void Fullscreen();
void Disable_Quick_Edit();
void No_Resize();

