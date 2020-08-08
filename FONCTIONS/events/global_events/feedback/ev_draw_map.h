#pragma once 

#include "../../events.h"

extern Event ev_DrawMap1;

void Ev_Dr_Map_Borders_1();		// Affiche instantannément
void Erase_Map_Borders_1(int speed = 0);		// Efface instantanément, ou avec une vitesse
void Just_Dr_Map_Borders();

void Set_Flashy_Border(Direction border, int numFlash = 11);
void Ev_Flash_Map_Border();		 // Fait flasher une bordure




//// Affiche le joueur
//void UI_Draw_Map_Borders_2();
//void UI_Erase_Map_Borders_2();
//
//// Affiche le joueur
//void UI_Draw_Map_Borders_3();
//void UI_Erase_Map_Borders_3();