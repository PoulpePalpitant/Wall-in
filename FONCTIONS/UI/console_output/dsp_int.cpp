
#include <mutex>
#include <iostream>
#include "dsp_int.h"




/* Probl�me de race condition: *SOLVED*
: // J'ai solve ce probl�me en utilisant la fonction "to_string()" qui convertit tout int en string. Therefore, ceci est d�suet 

prob:J'ai v�rrouill� deux fonctions de base avec mutex, Dsp_Char et Dsp_Int. N�anmoins, les deux ne sont pas reli�, il se peut qu'afficher un int modifie la position xy du curseur en m�me temps que Dsp_Char le fasse
it fucking did...	*/



//// WARNING: � UTILISER AVEC PR�CAUTION
//void UI_Dsp_Int(Coord crd, int nb, Colors clr, time_t time)	// affiche un int dans la console
//{
//	static std::mutex mu;
//
//
//	mu.lock();
//	gotoxy(crd.x, crd.y);		// Positionnement du curseur
//
//	if (Get_Current_Color() != clr)	// Check si on a d�j� la bonne couleur
//		Change_Color(clr);			// Changement de couleur
//
//	std::cout << nb;				// Output!
//	mu.unlock();
//	Sleep((int)time);				// temps d'attente
//	
//
//}