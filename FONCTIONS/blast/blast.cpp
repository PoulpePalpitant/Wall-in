
#include "../walls/walls.h"
#include "../grid/linkgrid.h"
#include "blast.h"
#include "../animation/move_blast.h"

/*
	Le blast horizontal sera 2 fois plus long, car les cases de la console windows sont deux fois plus grandes sur la hauteur,
	ce qui fait que les bot bougent deux fois plus vite sur cette axe. Ce qui fait qu'il est deux fois plus tough de les arrêter avec des blasts horizontales.
	C'est pourquoi, chaque tir horizontal va créer 2 murs aux lieux d'un seul.
*/

extern const Distance DFLT_BLAST_LENGTH_HOR = DELTA_X * 2;
extern const Distance DFLT_BLAST_LENGTH_VER = DELTA_Y;		// La hauteur par défaut du blast

// PEW PEW!!

extern Blast blastP1;
extern Blast blastP2;

// PEW PEW!!	

// INTIALISATION DES PROPRIÉTÉ DU BLAST
void Blast::Setup_Blast(BlastType& type, GrdCoord &startPos, Direction &blastDir)
{
	Setup_Blast_UI(type, blastDir);							// Son apparence futur
	Setup_Dist_Btw_Links(blastDir);							// La distance entre chacune des colisions sur le grid de links
	Setup_Position_Incrementors(blastDir, startPos);		// Sa position sur le Linkgrid et en XY
	Setup_Grid_Limit(blastDir);								// La col, ou Row ou le blast va s'arrêté, s'il ne rentre dans rien d'autre!
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


// SETUP: L'APPARENCE DU BLAST 
void Blast::Setup_Blast_UI(BlastType& type, Direction &blastDir)				// Assigne l'apparence du blast
{
	if (type == BlastType::REGULAR)
	{
		switch (blastDir)		// Symboles par défaut
		{
		case UP:
		case DOWN: sym = (int)WallSym::SYM_VER; break;
		case LEFT:
		case RIGHT:sym = (int)WallSym::SYM_HOR; break;
		}

		color = Colors::WHITE;		// Couleur par défaut
	}

	// Autres types 
	// ...

}

// setup: LA DISTANCE QUI SÉPARE CHACUN DES LINK QUE LE BLAST VA DEVOIR TRAVERSER DANS SON ÉPOPÉE. 
void Blast::Setup_Dist_Btw_Links(Direction& blastDir)
{
	switch (blastDir)
	{
	case UP:
	case DOWN: btwLinks= DELTA_Y; break;
	case LEFT:
	case RIGHT: btwLinks = DELTA_X; break;
	}
}

// SETUP: LA DIRECTION DU BLAST EN XY ET EN COORD DE GRIDS 
void Blast::Setup_Position_Incrementors(Direction &direction, GrdCoord &startPos)	// Sa position 
{
	// SETUP: POSITION DANS LE LINK GRID
	// Cette incrémenteur va faire avancer la position du blast sur le LinkGrid. Ça va servir pour la détection de de colision sur les éléments LinkGrid 
	Init_Axis_Incrementor( direction, grdPos);		// Initialise l'incrémenteur de position de grid
	Equal_Coordinates(grdPos.index, startPos);		// Permet d'égaliser deux valeurs de coordonnées de grid [col][row]

	// SETUP: POSITION EN XY
	// Cette incrémenteur va faire avancer la position du DEVANT du blast dans la console en X et Y. Seul la coord de la tête du blast est nécessaire pour l'affichage
	Init_Axis_Incrementor( direction, frontXY);		// Initialise l'incrémenteur de position XY
	Equal_Coordinates(frontXY.coord, linkGrid.link[startPos.c][startPos.r].Get_XY());		// La coordonnée xy du Blast est initialisé à une position de départ, soit vraisemblablement celle du joueur
	
	tailXY = frontXY; // Head and tail are the same
}

// SETUP: LA POSITION EN COL OU ROW OU LE BLAST VA DEVOIR S'ARRÊTER (pour par qu'il sorte de la box)
void Blast::Setup_Grid_Limit(Direction &direction)													// Calcul la limite ou le blast va devoir s'arrêter
{
	// L'axe du grid, c'est celui de "grdPosition.axis". il est intialisé juste au dessus, dans l'autre fonction	o(-^^-)o
	
	switch (direction)
	{
	case UP:														// La limite sera la row 0 du grid
	case LEFT:	grdLimit = 0; break;								// La limite sera la col 0 du grid

	case DOWN:	grdLimit = linkGrid.Get_Rows() - 1; break;			// Le nombre de rows maximum du grid sera la limite
	case RIGHT:	grdLimit = linkGrid.Get_Cols() - 1;					// Le nombre de col maximum du link grid sera la limite
	}

}



// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// PEWWWWPEWWPEWPEWPEWPEWPEPWEPWPEPWEPWPEPWEPWPEWPEWPEEEEEEEEEEEEEEEEEEEEEEEEEWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW!....
// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!
// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!

int Blast::Blast_Shot()
{
	static bool stopBlast; stopBlast = false;
	nbSteps = 0;															// Nombre de case que le blast à traversé

	while (!Has_Reached_Limit())											// Tant que le blast n'a pas atteint la limite de la "box" du jeu
	{
		if (Blast_Is_On_LinkGrid())											// Vérifie si le blast viens d'atteindre la position d'une case du grid
		{
			if (linkGrid.Is_Link_Here(grdPos.index.c, grdPos.index.r))		// Vérifie la présence d'un link 
				break;		
			
			// OPTIONAL:  Check si d'autres trucs, comme un joueur ou un item est ici

			Reset_Countdown_Till_Nxt_Link();							// Reset le temps que ça va prendre avant le prochaine fois que le blast va être sur le grid de Links
		}
		else
		{
			// OPTIONAL: CHECK si d'autres trucs sont ici, comme un wall ou un bot

			movesTillNxtLink--;	// Se rapproche du prochain Link!

		}
		
		//MoveBlast::Animate_Blast();

		// ANIMATION!!!
		
		nbSteps++;	// Un pas de plus!
	}

	return nbSteps;	// Le nombre total de case que le blast à traversé

}
// PEWWWWPEWWPEWPEWPEWPEWPEPWEPWPEPWEPWPEPWEPWPEWPEWPEEEEEEEEEEEEEEEEEEEEEEEEEWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW!....
// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!
// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!



// CHECK: si le blast se trouve sur le link grid 
bool Blast::Blast_Is_On_LinkGrid()
{
	if (this->movesTillNxtLink == 0)	// Next link représente le nombre de loop restant avant que le blast se trouve à nouveau sur le linkgrid
		return true;
	else
		return false;
}

// CHECK : si le blast à atteint la fin de son périple
bool Blast::Has_Reached_Limit()		
{
	return *grdPos.axis == grdLimit;	// Si la colonne, ou la row, sur lequel se trouve le blast est égal à la limite(soit la bordure de la box du terrain de jeu)
}										// Si cela est vrai, le blast s'arrête maintenant