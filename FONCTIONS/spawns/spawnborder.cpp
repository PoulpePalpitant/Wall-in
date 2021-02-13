
#include "spawnborder.h"
#include "../UI/map.h"


// Trouve la Coordonnée XY du premier élément Spawn de la bordure de spawn
static Coord FindStartOfBorderXY(LinkGrid& linkGrid, int borderSide)
{
	Coord SpawnXY = {};	// La coordonnée qu'on cherche

	switch (borderSide)
	{
	case UP:	case DOWN:		SpawnXY.x = START_X + 1; break;	 // La bordure 0 et 2, soit Up et Down ont tout les deux le même X
	case LEFT:	case RIGHT:		SpawnXY.y = START_Y + 1; break;	 // La bordure 1 et 3, soit Left et Right ont tout les deux le même Y
	}

	switch (borderSide)
	{
	case UP: SpawnXY.y = map.Get_Limit(UP) - GAP_BTW_GRID; break;		
	case DOWN:	SpawnXY.y = map.Get_Limit(DOWN) + GAP_BTW_GRID; break;	
	case LEFT:	SpawnXY.x = map.Get_Limit(LEFT) - GAP_BTW_GRID;break;	
	case RIGHT:	SpawnXY.x = map.Get_Limit(RIGHT) + GAP_BTW_GRID; break;	
	}
	return SpawnXY;	
}

// Constructor baby
void SpawnBorder::Create_Border(LinkGrid& linkGrid, Direction border) {

	Coord SpawnXY = FindStartOfBorderXY(linkGrid, border);	// Trouve la coordonnée X et Y de départ du premier Spawn sur la bordure
	int* incrBtwSpw = NULL;	// Pour chaque Spawn sur la bordure, ceci va incrémenter la Coordonnée X, OU Y, d'UNE distance fixe : Soit DELTA_X OU DELTA_Y(distance entre chaque éléments des Grids)
	
	// Préparation: 
	//		Assigné la distance qui sépare chaque spawn
	//		Assigné l'axe sur lequel incrémenté cette distance
	//		Assigné le nombre de spawn à créer sur la bordure. À noter qu'il en aura toujours un de moins que le nombre de col ou de rows du LinkGrid. Voir la logique de tout ça dans Grid.H  

	switch (border)
	{
	case UP:	case DOWN:	this->btwSpw = DELTA_X; incrBtwSpw = &SpawnXY.x; numSpawns = linkGrid.Get_Cols() - 1; break;	// À noter que le bordure UP est horizontal, même si elle est en "Haut"
	case LEFT:	case RIGHT: this->btwSpw = DELTA_Y;	incrBtwSpw = &SpawnXY.y; numSpawns = linkGrid.Get_Rows() - 1;break;	// À noter que le bordure Left est Vertical, même si elle est elle n'est pas en haut
	}	
	
	this->spawn = new BotSpawner[numSpawns]; // Création du nombre de spawn sur la bordure

	for (int i = 0; i < numSpawns; i++)
	{
		spawn[i].Set_XY(SpawnXY);		// Assignation des valeurs XY pour chacun des spawns sur la bordure
		*incrBtwSpw += btwSpw;			// Incrémentation de la distance séparant chaque spawns sur un Axe(x ou y)
	}
}

