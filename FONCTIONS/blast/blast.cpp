#include <thread>

#include "../grid/AllGrids.h"
#include "../animation/UI_move_blast.h"
#include "../player/player.h"

#include "blast.h"

/*
	Le blast horizontal sera 2 fois plus long, car les cases de la console windows sont deux fois plus grandes sur la hauteur,
	ce qui fait que les bot bougent deux fois plus vite sur cette axe. Ce qui fait qu'il est deux fois plus tough de les arr�ter avec des blasts horizontales.
	C'est pourquoi, chaque tir horizontal va cr�er 2 murs aux lieux d'un seul.
*/

extern const Distance DFLT_BLAST_LENGTH_HOR = DELTA_X * 2 + 1;	// Le +1 c'est pour afficher l'extr�mit� du blast
extern const Distance DFLT_BLAST_LENGTH_VER = DELTA_Y + 1;		// La hauteur par d�faut du blast
extern const time_t DFLT_BLAST_SPD_VER = 100000;			/*8000*/			// TEMPS DE PAUSE entre chaque affichage, en milliseconds			// Je pourrais agrandir la vitesse � l'horizontal!
extern const time_t DFLT_BLAST_SPD_HOR = DFLT_BLAST_SPD_VER / 2;			

// Les propri�t�s principales du Blast par d�faut
extern const BlastType DFLT_BLAST =	{WallStrength::REGULAR, LinkType::REGULAR};

// PEW PEW!!

extern Blast blastP1 = {}; 
extern Blast blastP2 = {};

// PEW PEW!!	




// INTIALISATION DES PROPRI�T� DU BLAST
void Blast::Setup_Blast(GrdCoord &newStartPos, Direction &newblastDir, const BlastType &type)
{
	strength = type.strength;				// Force du blast. Affecte la puissance du wall qui sera cr��
	linkType = type.linkType;					// type de Link � cr�er
	
	//if (dir != newblastDir)					// aurait pu �tre nice, mais je dois v�rifi� � chaque fois si les valeurs max n'ont pas chang� entre le blast pr�c�dent
	//{
		dir = newblastDir;							// La direction du blast
		Setup_Length();								// Ajuste la longueur du blast. Pourrait varier selon le type de tir
		Setup_Grid_Limit();							// La col, ou Row ou le blast va s'arr�t�, s'il ne rentre dans rien d'autre avnat!
		Setup_Speed();								// Sa vitesse
		Setup_Dist_Btw_Links();						// La distance entre chacune des colisions sur le grid de links
	//}			

	Setup_Blast_UI();							// Son apparence futur
	Setup_Position_Incrementors(newStartPos);	// Sa position sur le Linkgrid et en XY
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


// SETUP: L'APPARENCE DU BLAST 
void Blast::Setup_Blast_UI()				// Assigne l'apparence du blast
{
	if (strength == WallStrength::REGULAR)
	{
		switch (dir)		// Symboles par d�faut
		{
		case UP:
		case DOWN: sym = (int)WallSym::SYM_VER; break;
		case LEFT:
		case RIGHT:sym = (int)WallSym::SYM_HOR; break;
		}

		color = Colors::WHITE;		// Couleur par d�faut
	}


	// Autres types 
	// ...

}

// SETUP: LONGUEUR MAX DU BLAST
void Blast::Setup_Length()					// Ajuste la longueur du blast qui sera tir�
{
	switch (dir)		// Symboles par d�faut
	{
	case UP:	case DOWN: this->length = maxlengthVer; break;	// Longueur sur la verticale
	case LEFT:	case RIGHT:this->length = maxlengthHor; break;	// Longueur sur l'Horizontale
	}
}

// setup: LA DISTANCE QUI S�PARE CHACUN DES LINK QUE LE BLAST VA DEVOIR TRAVERSER DANS SON �POP�E. 
void Blast::Setup_Dist_Btw_Links()
{
	switch (dir)
	{
	case UP:
	case DOWN: btwLinks = DELTA_Y - 1; break;
	case LEFT:
	case RIGHT: btwLinks = DELTA_X - 1; break;
	}
}


// SETUP: LA POSITION EN COL OU ROW OU LE BLAST VA DEVOIR S'ARR�TER (pour par qu'il sorte de la box)
void Blast::Setup_Grid_Limit()													// Calcul la limite ou le blast va devoir s'arr�ter
{
	// L'axe du grid, c'est celui de "grdPosition.axis". il est intialis� juste au dessus, dans l'autre fonction	o(-^^-)o
	
	switch (dir)
	{
	case UP:														// La limite sera la row 0 du grid
	case LEFT:	grdLimit = 0; break;								// La limite sera la col 0 du grid

	case DOWN:	grdLimit = linkGrid->Get_Rows() - 1; break;			// Le nombre de rows maximum du grid sera la limite
	case RIGHT:	grdLimit = linkGrid->Get_Cols() - 1;					// Le nombre de col maximum du link grid sera la limite
	}

}

// SETUP: VITESSE D'AFFICHAGE DU BLAST
void Blast::Setup_Speed()											// La vitesse d'affichage du blast(temps de pause entre chaque)
{
	switch (dir)
	{
	case UP:case DOWN:		
		speed = (int)speedVer;	break;
	case LEFT:case RIGHT:	
		speed = (int)speedHor;	break;	// Blast horizontal est maintenant 2x plus rapide qu'avant		
	}
}

// SETUP: LA DIRECTION DU BLAST EN XY ET EN COORD DE GRIDS 
void Blast::Setup_Position_Incrementors(GrdCoord& startPos)	// Sa position 
{
	// SETUP: POSITION DANS LE LINK GRID
	// Cette incr�menteur va faire avancer la position du blast sur le LinkGrid. �a va servir pour la d�tection de de colision sur les �l�ments LinkGrid 
	grdPos.Initialize_All(startPos, dir);				// Initialise l'incr�menteur de position de grid � la position actuel.

	// SETUP: POSITION EN XY
	// Cette incr�menteur va faire avancer la position du DEVANT du blast dans la console en X et Y. Seul la coord de la t�te du blast est n�cessaire pour l'affichage
	frontXY.Initialize_Axis(dir);		// Initialise l'incr�menteur de position XY
	Equal_Coordinates(frontXY.coord, linkGrid->link[startPos.c][startPos.r].Get_XY());		// La coordonn�e xy du Blast est initialis� � une position de d�part, soit vraisemblablement celle du joueur

	tailXY.Initialize_Axis(dir);				// Initialise l'incr�menteur de d'Axe de position XY
	tailXY.coord = frontXY.coord;					// Head and tail commence avec le m�me XY
}
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// PEWWWWPEWWPEWPEWPEWPEWPEPWEPWPEPWEPWPEPWEPWPEWPEWPEEEEEEEEEEEEEEEEEEEEEEEEEWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW!....
// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!
// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!

void Blast::Blast_Shot(GrdCoord startPos, Direction& blastDir, const BlastType& type)
{
	nbSteps = movesTillNxtLink = 0;		// Nombre de case que le blast � travers� et nombre de case avant un link	(on start sur un link, donc z�ro ici)

	Setup_Blast(startPos, blastDir, type);

	// Si tu tir sur un link just enface, �a va juste faire un mur, no backtep amigo.

	while (!Has_Reached_Limit())											// Tant que le blast n'a pas atteint la limite de la "box" du jeu
	{
		if (Blast_Is_On_LinkGrid())											// V�rifie si le blast viens d'atteindre la position d'une case du grid
		{
			if(nbSteps)							// Si le blast n'est pas sur sa premi�re position de d�part
				grdPos.Increment_Coord();	// Nouvelle position sur le grid de Link. 
			
			if (linkGrid->Is_Link_Here(grdPos.index))		// V�rifie la pr�sence d'un link 
			{
				if(nbSteps != 0)
					UI_MoveBlast::Animate_Blast(this);			// Sert principalement � effacer la tail bien franchement 
				break;		// Doit v�rifier son type aussi! si c'est un loner, le blast devrait compl�tement 
			}
			// OPTIONAL:  Check si d'autres trucs, comme un joueur ou un item est ici

			Reset_Countdown_Till_Nxt_Link();	// Reset le temps que �a va prendre avant le prochaine fois que le blast va �tre sur le grid de Links

		}
		else
		{
			// OPTIONAL: CHECK si d'autres trucs sont ici, comme un wall ou un bot

			movesTillNxtLink--;	// Se rapproche du prochain Link!

		}

		// ANIMATION!!!
		UI_MoveBlast::Animate_Blast(this); // Bouge le blast!
		std::this_thread::sleep_for(std::chrono::microseconds(speed)); // Temps de pause entre chaque affichages		// speed * deltatime?


		// PROCHAINE position XY	
		frontXY.Increment_Coord();	// (+/- 1 dans une direction X/Y)

		// Prochain Nombre de steps total
		nbSteps++;	// Un pas de plus!Mais pour le prochain?
	}

	P1.Upd_Sym_From_Direction(dir);	
	P1.Dis_Player_Sym();				// Faut r�afficher le joueur apr�s le tir

	gGrids.Activate_Walls_And_Links_From_Blast(this);	// Active les murs qui ont �t� tir�s
}
// PEWWWWPEWWPEWPEWPEWPEWPEPWEPWPEPWEPWPEPWEPWPEWPEWPEEEEEEEEEEEEEEEEEEEEEEEEEWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW!....
// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!
// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!



// CHECK: si le blast se trouve sur le link grid 
bool Blast::Blast_Is_On_LinkGrid()
{
	if (this->movesTillNxtLink == 0)	// Next link repr�sente le nombre de loop restant avant que le blast se trouve � nouveau sur le linkgrid
		return true;
	else
		return false;
}

// CHECK : si le blast � atteint la fin de son p�riple
bool Blast::Has_Reached_Limit()		// �a c'est la prochaine limite, c'est pas celle actuelle!
{
	return *grdPos.axis == grdLimit;	// Si la colonne, ou la row, sur lequel se trouve le blast est �gal � la limite(soit la bordure de la box du terrain de jeu)
}										// Si cela est vrai, le blast s'arr�te maintenant


// POST-BLAST
// **********


// Le nombre de Link � "Activer" selon la distance parcouru
//---------------------------------------------------------

int Blast::Nb_Of_Links_To_Activate()
{
	if (nbSteps == 0)	// Le blast n'a parcouru aucune distance (le player � s�rement tir� sur la bordure)
		return 0;
	else
		if (nbSteps >= length)		// La blast � parcouru une distance plus grande ou �gale � sa longueur 
			return 1 + (length) / (btwLinks + 1);	// Longueur du blast / par DELTA_X/DELTA_Y sur le grid + 1 (NOMBRE MAX DE WALLS � ENREGISTRER)
		else
			return 1 + nbSteps / (btwLinks + 1);	// +1, car garentie d'avoir au moins deux Link
}

// Le nombre de walls � "Creer" selon un "Blast" du joueur
//---------------------------------------------------------

int Blast::Nb_Of_Walls_Per_Blast()
{
	if (nbSteps == 0)	// Le blast n'a parcouru aucune distance (le player � s�rement tir� sur la bordure)
		return 0;
	else
		if (nbSteps >= length)		// La blast � parcouru une distance plus grande ou �gale � sa longueur 
			return length / (btwLinks + 1);	// La longueur max / par la distance qui s�pare chaque link	(NOMBRE MAX DE WALLS � ENREGISTRER)
		else
			return nbSteps / (btwLinks + 1); //works
}
