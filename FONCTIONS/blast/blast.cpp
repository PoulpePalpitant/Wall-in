#include <thread>

#include "../walls/walls.h"
#include "../grid/linkgrid.h"
#include "../animation/move_blast.h"
#include "blast.h"

/*
	Le blast horizontal sera 2 fois plus long, car les cases de la console windows sont deux fois plus grandes sur la hauteur,
	ce qui fait que les bot bougent deux fois plus vite sur cette axe. Ce qui fait qu'il est deux fois plus tough de les arrêter avec des blasts horizontales.
	C'est pourquoi, chaque tir horizontal va créer 2 murs aux lieux d'un seul.
*/

extern const Distance DFLT_BLAST_LENGTH_HOR = DELTA_X * 2 + 1;	// Le +1 c'est pour afficher l'extrémité du blast
extern const Distance DFLT_BLAST_LENGTH_VER = DELTA_Y + 1;		// La hauteur par défaut du blast
extern const time_t DFLT_BLAST_SPD = 8000;						// milliseconds			// Je pourrais agrandir la vitesse à l'horizontal!

// PEW PEW!!

extern Blast blastP1 = {};
extern Blast blastP2 = {};

// PEW PEW!!	

// INTIALISATION DES PROPRIÉTÉ DU BLAST
void Blast::Setup_Blast(BlastType type, GrdCoord &startPos, Direction &blastDir)
{
	this->type = type;								// type de blast
	dir = blastDir;								// La direction du blast
	Setup_Blast_UI();						// Son apparence futur
	Setup_Dist_Btw_Links();						// La distance entre chacune des colisions sur le grid de links
	Setup_Position_Incrementors(startPos);		// Sa position sur le Linkgrid et en XY
	Setup_Grid_Limit();							// La col, ou Row ou le blast va s'arrêté, s'il ne rentre dans rien d'autre avnat!
	Setup_Speed();							// Sa vitesse
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


// SETUP: L'APPARENCE DU BLAST 
void Blast::Setup_Blast_UI()				// Assigne l'apparence du blast
{
	if (type == BlastType::REGULAR)
	{
		switch (dir)		// Symboles par défaut
		{
		case UP:
		case DOWN: sym = (int)WallSym::SYM_VER; break;
		case LEFT:
		case RIGHT:sym = (int)WallSym::SYM_HOR; break;
		}

		color = Colors::WHITE;		// Couleur par défaut
	}

	Setup_Length();	// Ajuste la longueur du blast. Pourrait varier selon le type de tir

	// Autres types 
	// ...

}

// SETUP: LONGUEUR MAX DU BLAST
void Blast::Setup_Length()					// Ajuste la longueur du blast qui sera tiré
{
	switch (type)
	{
	case BlastType::REGULAR:									// à noter que tu risque d'ajuster la size vers la même chose à chaque fois, 
																// ¨ca me fait réalisé que je réassigne tout à chaque fois, même si c'est pas nécessaire quand je tir tjrs dans la même direction
		switch (dir)		// Symboles par défaut
		{
		case UP:	case DOWN: this->length = maxlengthVer; break;	// Longueur sur la verticale
		case LEFT:	case RIGHT:this->length = maxlengthHor; break;	// Longueur sur l'Horizontale
		}
		
		break;
		
	}
}

// setup: LA DISTANCE QUI SÉPARE CHACUN DES LINK QUE LE BLAST VA DEVOIR TRAVERSER DANS SON ÉPOPÉE. 
void Blast::Setup_Dist_Btw_Links()
{
	switch (dir)
	{
	case UP:
	case DOWN: btwLinks= DELTA_Y - 1; break;
	case LEFT:
	case RIGHT: btwLinks = DELTA_X - 1; break;
	}
}

// SETUP: LA DIRECTION DU BLAST EN XY ET EN COORD DE GRIDS 
void Blast::Setup_Position_Incrementors(GrdCoord &startPos)	// Sa position 
{
	// SETUP: POSITION DANS LE LINK GRID
	// Cette incrémenteur va faire avancer la position du blast sur le LinkGrid. Ça va servir pour la détection de de colision sur les éléments LinkGrid 
	grdPos.Initialize(startPos, dir);				// Initialise l'incrémenteur de position de grid à la position actuel.

	// SETUP: POSITION EN XY
	// Cette incrémenteur va faire avancer la position du DEVANT du blast dans la console en X et Y. Seul la coord de la tête du blast est nécessaire pour l'affichage
	Init_Axis_Incrementor(dir, frontXY);		// Initialise l'incrémenteur de position XY
	Equal_Coordinates(frontXY.coord, linkGrid.link[startPos.c][startPos.r].Get_XY());		// La coordonnée xy du Blast est initialisé à une position de départ, soit vraisemblablement celle du joueur
	
	Init_Axis_Incrementor(dir, tailXY);		// Initialise l'incrémenteur de d'Axe de position XY
	tailXY.coord = frontXY.coord;					// Head and tail commence avec le même XY
}

// SETUP: LA POSITION EN COL OU ROW OU LE BLAST VA DEVOIR S'ARRÊTER (pour par qu'il sorte de la box)
void Blast::Setup_Grid_Limit()													// Calcul la limite ou le blast va devoir s'arrêter
{
	// L'axe du grid, c'est celui de "grdPosition.axis". il est intialisé juste au dessus, dans l'autre fonction	o(-^^-)o
	
	switch (dir)
	{
	case UP:														// La limite sera la row 0 du grid
	case LEFT:	grdLimit = 0; break;								// La limite sera la col 0 du grid

	case DOWN:	grdLimit = linkGrid.Get_Rows() - 1; break;			// Le nombre de rows maximum du grid sera la limite
	case RIGHT:	grdLimit = linkGrid.Get_Cols() - 1;					// Le nombre de col maximum du link grid sera la limite
	}

}

// SETUP: VITESSE D'AFFICHAGE DU BLAST
void Blast::Setup_Speed()											// La vitesse d'affichage du blast(temps de pause entre chaque)
{
	switch (dir)
	{
	case UP:case DOWN:	
		switch (type)
		{
		case BlastType::REGULAR: speed = DFLT_BLAST_SPD;break;


		}
		break;

	case LEFT:case RIGHT:	
		switch (type)
		{
		case BlastType::REGULAR: speed = DFLT_BLAST_SPD / 2;break;	// Blast horizontal est maintenant 2x plus rapide qu'avant


		}
	}




}


// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// PEWWWWPEWWPEWPEWPEWPEWPEPWEPWPEPWEPWPEPWEPWPEWPEWPEEEEEEEEEEEEEEEEEEEEEEEEEWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW!....
// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!
// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!// LE//TIR//DU BLAST!!!

Blast* Blast::Blast_Shot(BlastType type, GrdCoord& startPos, Direction& blastDir)
{
	nbSteps = movesTillNxtLink = 0;		// Nombre de case que le blast à traversé et nombre de case avant un link	(on start sur un link, donc zéro ici)

	Setup_Blast(type, startPos, blastDir);

	// Si tu tir sur un link just enface, ça va juste faire un mur, no backtep amigo.

	while (!Has_Reached_Limit())											// Tant que le blast n'a pas atteint la limite de la "box" du jeu
	{
		if (Blast_Is_On_LinkGrid())											// Vérifie si le blast viens d'atteindre la position d'une case du grid
		{
			if(nbSteps)							// Si le blast n'est pas sur sa première position de départ
				grdPos.Increment_Coord();	// Nouvelle position sur le grid de Link. 
			
			if (linkGrid.Is_Link_Here(grdPos.index.c, grdPos.index.r))		// Vérifie la présence d'un link 
			{
				MoveBlast::Animate_Blast(this);			// Sert principalement à effacer la tail bien franchement 
				break;		// Doit vérifier son type aussi! si c'est un loner, le blast devrait complètement 
			}
			// OPTIONAL:  Check si d'autres trucs, comme un joueur ou un item est ici

			Reset_Countdown_Till_Nxt_Link();	// Reset le temps que ça va prendre avant le prochaine fois que le blast va être sur le grid de Links

		}
		else
		{
			// OPTIONAL: CHECK si d'autres trucs sont ici, comme un wall ou un bot

			movesTillNxtLink--;	// Se rapproche du prochain Link!

		}

		// ANIMATION!!!
		MoveBlast::Animate_Blast(this); // Bouge le blast!
		std::this_thread::sleep_for(std::chrono::microseconds(speed)); // Temps de pause entre chaque affichages		// speed * deltatime?


		// PROCHAINE position XY	
		Increment_Coordinates(frontXY);	// (+/- 1 dans une direction X/Y)

		// Prochain Nombre de steps total
		nbSteps++;	// Un pas de plus!Mais pour le prochain?
	}

	return this;	// Le nombre total de case que le blast à traversé

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
bool Blast::Has_Reached_Limit()		// Ça c'est la prochaine limite, c'est pas celle actuelle!
{
	return *grdPos.axis == grdLimit;	// Si la colonne, ou la row, sur lequel se trouve le blast est égal à la limite(soit la bordure de la box du terrain de jeu)
}										// Si cela est vrai, le blast s'arrête maintenant