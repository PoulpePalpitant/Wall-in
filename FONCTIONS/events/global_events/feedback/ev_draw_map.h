#pragma once 

#include "../../events.h"

extern Event ev_DrawMap1;

void Ev_Dr_Map_Borders_1();		// Affiche instantannément
void Erase_Map_Borders_1(int speed = 0);		// Efface instantanément, ou avec une vitesse

void Ev_Flash_Map_Border(Direction border);		 // Affiche instantannément
//// Affiche le joueur
//void UI_Draw_Map_Borders_2();
//void UI_Erase_Map_Borders_2();
//
//// Affiche le joueur
//void UI_Draw_Map_Borders_3();
//void UI_Erase_Map_Borders_3();