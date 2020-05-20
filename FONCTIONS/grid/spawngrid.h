#pragma once


#include "grid.h"
#include "../spawns/spawnborder.h"


class Spawn_Grid : public Grid {
public:
	//// Création de 4 bordures de Bot spawners, une pour chaque côté de la Box. (Il y en aura toujours 4, pour autant que windows ne release pas une console triangulaire)
	Spawn_Grid() {
		
		border = new SpawnBorder[4];
	}// CONSTRUCTOR

	// À noter que cette objet est bad, il hérite de Grid mains n'utilise pas la moité des fonctions  et des variables de grid xD

	// Le grid de spawns sera entreposer bien au chaud ici. Mais il sera bien différent des autres grids, car il pointera vers 4 "bordures" de spawns(1 pour chaque côté de la box du jeu, contenants chaucun un certain nombre de spawns
	SpawnBorder* border;

	void Create(LinkGrid& linkGrid);	// Ceci initialise tout les bordures de spawns avec des éléments spawns. Ces spawns auront également une coord XY assignés
	void Resize(LinkGrid& linkGrid);	// Détruit, et ensuite redimensionne le Grid	
};

// VARIABLE GLOBALE

extern Spawn_Grid spawnGrid;