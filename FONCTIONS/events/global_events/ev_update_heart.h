#pragma once 

#include "../../player/player.h"

//void Ev_Dr_Heart_3();	// Affiche le coueur à ses différents stades. 1 stade représente le niveau de HP du joueur

void Just_Dr_Heart(int hp = P1.Get_HP());	// Affiche le coueur instantly
void Ev_Dr_Heart();					 // Affiche le coueur à ses différents stades
void Set_Speed_Draw(bool slow = false);				// Affiche le coueur un peu plus dramatiquement
void Start_Ev_Dr_Heart(int hp, bool slow = false);		 // Setup l'event Précédent
//void Set_Up_Drawers(int hp);
void Fill_Heart_Randomly(bool rdmChars);
void Fill_Outside_Heart(bool fill);


void Just_Er_Heart();		// Efface le coueur

