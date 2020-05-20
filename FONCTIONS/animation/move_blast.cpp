
#include "../UI/console(v1.9).h"
#include "move_blast.h"
#include "../UI/txtstyle.h"
#include <iostream>

// L'animation va se faire dans cette ordre:

/*
	1)	Affichage du symbole du blast � sa position XY EN AVANT des autres symboles de blast pr�c�dant. Si c'est le premier, le symbole s'affichera PAR-DESSUS le symbole du joueur.
	2)	V�rification de la grandeur maximale du blast. Si le blast � atteint sa longueur maximale, on va commencer � effacer les symboles derri�re.
	3)	Effacement du symbole du blast se trouvant le plus loin derri�re la t�te du blast. Ceci trim la longueur du blast pour qu'elle conserve une certaine taille. Il se peut que le blast s'arr�te avant m�me 
	d'atteindre	sa grandeur maximale, it's all fine.
*/


void MoveBlast::Animate_Blast(Blast* blast) // voir paragraph
{
	Move_Blast_Head_Forward(blast);
	
	if(Chk_Max_Blast_Length(blast))
		Erase_Blast_Tail(blast);
}



void MoveBlast::Move_Blast_Head_Forward(Blast* blast)	// DISPLAY: la t�te du blast
{
	gotoxy(blast->frontXY.coord.x, blast->frontXY.coord.y);	// XY du blast
	Change_Color(blast->color);								// Couleur du symbole			// Sudden R�alisation que changer la position du curseur va faire chier avec les thread!!! c'est comme une race condition pour changer les 
	std::cout << blast->sym;								// affiche le symbole				valeurs de la console!!!!
	Change_Color(blast->color);								// Couleur du symbole			// sudden r�alisation que les threads vont faire chier avec les changements de couleurs!!!

	//d'ailleur' cette fonction est suffisament basic pour �tre plac� ailleurs

		//check ton autre main pour savoir comment

}

bool MoveBlast::Chk_Max_Blast_Length(Blast* blast)	// CHECK: Si le blast � atteint sa taille max
{
	return blast->nbSteps == blast->maxSize;	
}

void MoveBlast::Erase_Blast_Tail(Blast* blast)	// ERASE: la queue du blast, si le blast � parcouru une distance >= que sa taille max
{
	// Position de la tail
	gotoxy(blast->tailXY.coord.x, blast->tailXY.coord.y);
	std::cout << TXT_CONST.EMPTY;		// Efface la tail!

	// Incr�mentation da la prochaine position XY
	blast->tailXY.axis += blast->tailXY.polar;
}