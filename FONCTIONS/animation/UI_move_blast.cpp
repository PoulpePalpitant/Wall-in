#include <iostream>



#include "../UI/console(v1.9).h"
#include "../UI/txtstyle.h"
#include "../UI/console_output/dsp_char.h"


#include "UI_move_blast.h"

// L'animation va se faire dans cette ordre:

/*
	1)	Affichage du symbole du blast � sa position XY EN AVANT des autres symboles de blast pr�c�dant. Si c'est le premier, le symbole s'affichera PAR-DESSUS le symbole du joueur.
	2)	V�rification de la grandeur maximale du blast. Si le blast � atteint sa longueur maximale, on va commencer � effacer les symboles derri�re.
	3)	Effacement du symbole du blast se trouvant le plus loin derri�re la t�te du blast. Ceci trim la longueur du blast pour qu'elle conserve une certaine taille. Il se peut que le blast s'arr�te avant m�me 
	d'atteindre	sa grandeur maximale, it's all fine.
*/


void UI_MoveBlast::Animate_Blast(Blast* blast) // voir paragraph
{
	Move_Blast_Head_Forward(blast);
	
	if(Chk_Max_Blast_Length(blast))
		Erase_Blast_Tail(blast);

}



void UI_MoveBlast::Move_Blast_Head_Forward(Blast* blast)	// DISPLAY: la t�te du blast
{
	// Affichage du symbole du blast 
	UI_Dsp_Char(blast->frontXY.coord, blast->sym, blast->color);

	// XY du blast
	// Couleur du symbole			
	// affiche le symbole			
	// Couleur du symbole			

}

bool UI_MoveBlast::Chk_Max_Blast_Length(Blast* blast)	// CHECK: Si le blast � atteint sa taille max
{
	return blast->nbSteps >= blast->length ;	
}

void UI_MoveBlast::Erase_Blast_Tail(Blast* blast)	// ERASE: la queue du blast, si le blast � parcouru une distance >= que sa taille max
{
	// Efface la tail!
	UI_Dsp_Char(blast->tailXY.coord, TXT_CONST.SPACE);

	// Incr�mentation da la prochaine position XY
	blast->tailXY.Increment_Coord();

}