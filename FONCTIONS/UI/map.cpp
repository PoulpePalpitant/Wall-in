#include "map.h"


extern const Distance GAP_BTW_GRID = 2;	// Les Spawns se retrouvent 1 case plus loin que le grid de Links


extern Map map = {};	// Définition de la class map iciitttttttttteeeeee


void Map::Resize(LinkGrid& linkGrid)	// Resize les dimensions selon la nouvelle dimension du Grid principal(LinkGrid)
{
	limit[LEFT] = START_X;	// Limite de l'air de déplacement du joueur à gauche
	limit[RIGHT] = START_X + DELTA_X * (linkGrid.Get_Cols() - 1);	// Limite de l'air de déplacement du joueur à droite -1 car c'Est le nombre de colonne max, à partir de 0
	length = limit[RIGHT] - limit[LEFT];	// Largeur

	limit[UP] = START_Y;	// Limite de l'air de déplacement du joueur en haut
	limit[DOWN] = START_Y + DELTA_Y * (linkGrid.Get_Rows() - 1);	// Limite de l'air de déplacement du joueur en bas
	height = limit[DOWN] - limit[UP];	// Hauteur
}


