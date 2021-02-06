
#include "UI_move_blast.h"

SpeedTimer UI_MoveBlast::eraserTimer;	// Erase le reste d'un blast qui � fail	

// L'animation va se faire dans cette ordre:
/*
	1)	Affichage du symbole du blast � sa position XY EN AVANT des autres symboles de blast pr�c�dant. Si c'est le premier, le symbole s'affichera PAR-DESSUS le symbole du joueur.
	2)	V�rification de la grandeur maximale du blast. Si le blast � atteint sa longueur maximale, on va commencer � effacer les symboles derri�re.
	3)	Effacement du symbole du blast se trouvant le plus loin derri�re la t�te du blast. Ceci trim la longueur du blast pour qu'elle conserve une certaine taille. 
*/


void UI_MoveBlast::Animate_Blast(Blast* blast) // voir paragraph
{
	Move_Blast_Head_Forward(blast);
	
	if(Chk_Max_Blast_Length(blast))
		Erase_Blast_Tail(blast);

}

void UI_MoveBlast::Move_Blast_Head_Forward(Blast* blast)	
{
	ConsoleRender::Add_Char(blast->frontXY.coord, blast->sym, blast->color);
}

bool UI_MoveBlast::Chk_Max_Blast_Length(Blast* blast)	
{
	return blast->nbSteps >= blast->length ;	
}

void UI_MoveBlast::Erase_Blast_Tail(Blast* blast)	// ERASE: la queue du blast, si le blast � parcouru une distance >= que sa taille max
{
	ConsoleRender::Add_Char(blast->tailXY.coord, TXT_CONST.SPACE);
	blast->tailXY.Increment_Coord();
}

void UI_MoveBlast::Setup_Blast_Eraser(Blast* blast)
{
	int length = blast->length;
	
	if (blast->nbSteps < blast->length)
		length = blast->nbSteps;

	eraserTimer.Start_Timer(blast->speed, length - 1);	// un timer qui va effacer toute la longueur du blast. le - 1 c'est pour pas effacer l'extremit�

}
 
// Quand le blast ne cr�er pas de mur, il faut l'effacer au complet
void UI_MoveBlast::Erase_Whole_Blast(Blast* blast){
	
	while (eraserTimer.Tick())
		Erase_Blast_Tail(blast);
	
	if (!eraserTimer.Is_On())
		blast->active = false;
}
