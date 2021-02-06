#pragma once


#include "grid.h"
#include "../spawns/spawnborder.h"


// GridCoord pour les spawns
struct SpwCrd {
	int border;		// cot� de la box
	int spwNum;		// le num�ro du spawn
};

	// � noter que cette objet est bad, il h�rite de Grid mains n'utilise pas la moit� des fonctions  et des variables de grid xD
class SpawnGrid : public Grid {
private:
	static int maxSpwnCrdX;		
	static int maxSpwnCrdY;		

public:
	//// Cr�ation de 4 bordures de Bot spawners, une pour chaque c�t� de la Box. (Il y en aura toujours 4, pour autant que windows ne release pas une console triangulaire)
	SpawnGrid() {

		border = new SpawnBorder[4];
	}


	// Le grid de spawns sera entreposer bien au chaud ici. Mais il sera bien diff�rent des autres grids, car il pointera vers 4 "bordures" de spawns(1 pour chaque c�t� de la box du jeu, 
	// contenants chaucun un certain nombre de spawns
	SpawnBorder* border;

	void Create(LinkGrid& linkGrid);	
	void Resize(LinkGrid& linkGrid);	

	static int Get_MaxSpwnCrdX() {return maxSpwnCrdX;}
	static int Get_MaxSpwnCrdY() { return maxSpwnCrdY;}
	bool Is_Inbound_Everywhere(GrdCoord spwnCrd);	
	bool Is_Inbound(int boxSide, int spwNum);		
};

