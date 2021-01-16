#include <iostream>



#include "../UI/console(v1.9).h"
#include "../UI/txtstyle.h"
#include "../UI/console_output/render_list.h"
#include "../grid/AllGrids.h"

#include "UI_move_blast.h"

SpeedTimer UI_MoveBlast::eraserTimer;	// Erase le reste d'un blast qui à fail	


// L'animation va se faire dans cette ordre:

/*
	1)	Affichage du symbole du blast à sa position XY EN AVANT des autres symboles de blast précédant. Si c'est le premier, le symbole s'affichera PAR-DESSUS le symbole du joueur.
	2)	Vérification de la grandeur maximale du blast. Si le blast à atteint sa longueur maximale, on va commencer à effacer les symboles derrière.
	3)	Effacement du symbole du blast se trouvant le plus loin derrière la tête du blast. Ceci trim la longueur du blast pour qu'elle conserve une certaine taille. Il se peut que le blast s'arrête avant même 
	d'atteindre	sa grandeur maximale, it's all fine.
*/


void UI_MoveBlast::Animate_Blast(Blast* blast) // voir paragraph
{
	Move_Blast_Head_Forward(blast);
	
	if(Chk_Max_Blast_Length(blast))
		Erase_Blast_Tail(blast);

}

void UI_MoveBlast::Move_Blast_Head_Forward(Blast* blast)	// DISPLAY: la tête du blast
{
	// Affichage du symbole du blast 
	ConsoleRender::Add_Char(blast->frontXY.coord, blast->sym, blast->color);
}

bool UI_MoveBlast::Chk_Max_Blast_Length(Blast* blast)	// CHECK: Si le blast à atteint sa taille max
{
	return blast->nbSteps >= blast->length ;	
}

void UI_MoveBlast::Erase_Blast_Tail(Blast* blast)	// ERASE: la queue du blast, si le blast à parcouru une distance >= que sa taille max
{
	// Efface la tail!
	ConsoleRender::Add_Char(blast->tailXY.coord, TXT_CONST.SPACE);

	// Incrémentation da la prochaine position XY
	blast->tailXY.Increment_Coord();

}
void UI_MoveBlast::Setup_Blast_Eraser(Blast* blast)
{
	int length = blast->length;
	
	if (blast->nbSteps < blast->length)
		length = blast->nbSteps;

	eraserTimer.Start_Timer(blast->speed, length - 1);	// un timer qui va effacer toute la longueur du blast. le - 1 c'est pour pas effacer l'extremité

}
 
// Quand le blast ne créer pas de mur, il faut l'effacer au complet
void UI_MoveBlast::Erase_Whole_Blast(Blast* blast){
	
	while (eraserTimer.Tick())
	{	
		//// temp bad: Remove after tests
		//if (Are_Equal(blast->frontXY.coord, blast->tailXY.coord)) 
		//{
		//	eraserTimer.Stop();
		//	break;
		//} 
		Erase_Blast_Tail(blast);

		//ConsoleRender::Add_Char(blast->tailXY.coord, TXT_CONST.SPACE);
		//blast->tailXY.Increment_Coord(); // Incrémentation da la prochaine position XY
		

	}
	
	// Godd final
	if (!eraserTimer.Is_On())
		blast->active = false;
}
