
#include <mutex>
#include <iostream>
#include "dsp_int.h"




/* Problème de race condition: *SOLVED*
: // J'ai solve ce problème en utilisant la fonction "to_string()" qui convertit tout int en string. Therefore, ceci est désuet 

prob:J'ai vérrouillé deux fonctions de base avec mutex, Dsp_Char et Dsp_Int. Néanmoins, les deux ne sont pas relié, il se peut qu'afficher un int modifie la position xy du curseur en même temps que Dsp_Char le fasse
it fucking did...	*/



//// WARNING: À UTILISER AVEC PRÉCAUTION
//void UI_Dsp_Int(Coord crd, int nb, Colors clr, time_t time)	// affiche un int dans la console
//{
//	static std::mutex mu;
//
//
//	mu.lock();
//	gotoxy(crd.x, crd.y);		// Positionnement du curseur
//
//	if (Get_Current_Color() != clr)	// Check si on a déjà la bonne couleur
//		Change_Color(clr);			// Changement de couleur
//
//	std::cout << nb;				// Output!
//	mu.unlock();
//	Sleep((int)time);				// temps d'attente
//	
//
//}