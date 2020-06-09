#pragma once


#include "grid.h"
#include "../spawns/spawnborder.h"


// GridCoord pour les spawns
struct SpwCrd {
	int border;		// cot� de la box
	int spwNum;		// le num�ro du spawn
};

class SpawnGrid : public Grid {
private:
	static int maxSpwnCrdX;		// Nombre de COORD de spawn Maximum sur les bordures horizontales UP(0) et DOWN(2)		static
	static int maxSpwnCrdY;		// Nombre de COORD de spawn Maximum sur les bordures verticales LEFT(1) et RIGHT(3)		static

public:
	//// Cr�ation de 4 bordures de Bot spawners, une pour chaque c�t� de la Box. (Il y en aura toujours 4, pour autant que windows ne release pas une console triangulaire)
	SpawnGrid() {
		
		border = new SpawnBorder[4];
	}// CONSTRUCTOR

	// � noter que cette objet est bad, il h�rite de Grid mains n'utilise pas la moit� des fonctions  et des variables de grid xD

	// Le grid de spawns sera entreposer bien au chaud ici. Mais il sera bien diff�rent des autres grids, car il pointera vers 4 "bordures" de spawns(1 pour chaque c�t� de la box du jeu, contenants chaucun un certain nombre de spawns
	SpawnBorder* border;

	void Create(LinkGrid& linkGrid);	// Ceci initialise tout les bordures de spawns avec des �l�ments spawns. Ces spawns auront �galement une coord XY assign�s
	void Resize(LinkGrid& linkGrid);	// D�truit, et ensuite redimensionne le Grid	

	static int Get_MaxSpwnCrdX() {return maxSpwnCrdX;}
	static int Get_MaxSpwnCrdY() { return maxSpwnCrdY;}
	bool Is_Inbound_Everywhere(GrdCoord spwnCrd);	// V�rification d'une coord sur TOUUT les bordures
	bool Is_Inbound(int boxSide, int spwNum);		// V�rification d'une coord sur 1 seule bordure		static
};

