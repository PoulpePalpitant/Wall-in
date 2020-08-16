#pragma once 

#include "../../player/player.h"

void Ev_Dr_Heart_3();	// Affiche le coueur à ses différents stades. 1 stade représente le niveau de HP du joueur
void Just_Dr_Heart(int hp = P1.Get_HP());	// Affiche le coueur instantly
void Set_Up_Drawers(int hp);
void Just_Er_Heart();		// Efface le coueur
void Ev_Add_Excess_Health();	// Si le joueur à plus que 3 de vie, on ajoute un tit +"nombre" à côté
void Ev_Rmv_Excess_Health();	// Même principe, sauf que retire le tit + 