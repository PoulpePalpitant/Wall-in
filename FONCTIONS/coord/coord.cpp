
#include "coord.h"



// CONSTANTES POUR L'AFFICHAGE SEULEMENT
// *************************************

extern const int START_X = 10;	// Position, sur l'axe des X de la console, du coin supérieur gauche du damier
extern const int START_Y = 2;	// Position, sur l'axe des Y de la console, du coin supérieur gauche du damier

extern const int DELTA_X = 5;	// pas mieux dans le grid?
extern const int DELTA_Y = 3;

// On obtient la coord X selon la position logique du maingrid
// --------------------------------------------------------

int Get_X(int col)
{
	return START_X + DELTA_X * col;
}

// On obtient la coord Y selon la position logique du maingrd
// ---------------------------------------------------------

int Get_Y(int lig)
{
	return START_Y + DELTA_Y * lig;
}
