#pragma once 

#include "../../player/player.h"

Coord Find_Heart_Ori_XY();					// position de départ pour draw le coeur
void Just_Dr_Heart(int hp = P1.Get_HP());	// Affiche le coueur instantly
void Ev_Dr_Heart();					 // Affiche le coueur à ses différents stades
void Ev_Dr_Extra_Hp();				// Draw un tit nombre représentant l'hep supplémentaire
void Set_Speed_Draw(bool slow = false);				// Affiche le coueur un peu plus dramatiquement
void Start_Ev_Dr_Heart(int hp, bool slow = false);		 // Setup l'event Précédent


void Fill_Heart_Randomly(bool rdmChars);
void Fill_Outside_Heart(bool fill);


void Just_Er_Heart();		// Efface le coueur

