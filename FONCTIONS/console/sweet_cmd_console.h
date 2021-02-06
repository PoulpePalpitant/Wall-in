#pragma once

#include <Windows.h>

extern HWND GAME_WND; 
extern RECT rect;

extern int gConWidth;
extern int gConHeight;
extern int gTotalRes;

void Change_Font(bool deflt, int size = 16);			
void Hide_Cursor();		
void Set_Console_Name();
void Upd_Console_Size();
void Set_Dflt_WND();	

void Change_Window_Position(); 
void Center_WND();

void Change_Typography();
void Hide_Scrollbar();
void Fullscreen();
void Disable_Quick_Edit();
void No_Resize();

