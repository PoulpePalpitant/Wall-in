#pragma once 

#include "../../player/player.h"

Coord Find_Heart_Ori_XY();					// position de d�part pour draw le coeur
void Just_Dr_Heart(int hp = P1.Get_HP());	// Affiche le coueur instantly
void Ev_Dr_Heart();					 // Affiche le coueur � ses diff�rents stades
void Ev_Dr_Extra_Hp();				// Draw un tit nombre repr�sentant l'hep suppl�mentaire
void Set_Speed_Draw(bool slow = false);				// Affiche le coueur un peu plus dramatiquement
void Start_Ev_Dr_Heart(int hp, bool slow = false);		 // Setup l'event Pr�c�dent


void Fill_Heart_Randomly(bool rdmChars);
void Fill_Outside_Heart(bool fill);


void Just_Er_Heart();		// Efface le coueur

