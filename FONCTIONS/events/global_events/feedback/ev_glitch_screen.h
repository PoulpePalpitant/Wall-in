#pragma once 
#include	"../../../UI/map.h"

//void Ev_Dr_Glitch_Map();		//  R//  draw la map rapidement // ne doit plus �tre utilis� directement
//void Ev_Er_Glitch_Map();		//  R//  Erase la map rapidement
void Set_Custom_Glitch_Map_Ev(bool erase, int speed = 4000000, Colors clr = GRAY); // Est utilis� pour sett� un event de glitch map
void Ev_Glitch_Map_Retry();	// Utilise les events plus haut, et clr la screen quand �a la finis

