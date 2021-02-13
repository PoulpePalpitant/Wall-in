#pragma once

#include "../UI/direction.h"

struct GrdCoord { int c; int r; };		//  Les grids du jeux seront tous navigué par la logique: Colonnes(x) Lignes(y)

// CONSTANTES POUR L'AFFICHAGE SEULEMENT
// *************************************

// Je me rend compte que si l'écran du joueur est petite, ça vaut plus rien tout ça, alors START_ ne sera pas constante
extern int START_X;	// Position, sur l'axe des X de la console, du coin supérieur gauche du main Grid
extern int START_Y;	// Position, sur l'axe des Y de la console, du coin supérieur gauche du main Grid

extern const int DELTA_X;	// Saut sur l'axe des X d'une case à l'autre(Main Grid)
extern const int DELTA_Y;	// Saut sur l'axe des Y d'une case à l'autre

// Ceci fut ma première tentative ever à faire de l'héritage en programmation orienté objet...

class Grid {	// Le Grid servira uniquement de références pour le LinkGrid et le WallGrid
private:
	int numCol;	// Quand on accède au max, il faut faire [numCol -1]
	int numRow;	// Quand on accède au max, il faut faire [numRow -1]
protected:
	void UpdSize(int col, int row) { this->numCol = col;this->numRow = row; }	
public:
	void Create(int col, int row, int**& grid);	// Créer le Grid. Persistera jusqu'au prochain Resize
	void Resize(int col, int row, int**& grid);	// Redimensionne.... Mais détruit aussi les valeurs du grid...
	bool Is_Inbound(GrdCoord crd);			
	int Get_Rows() { return this->numRow; }	
	int Get_Cols() { return this->numCol; }	
};

void Equal_Coordinates(GrdCoord& from, GrdCoord to);		
bool Are_Equal(const GrdCoord &crd1, const GrdCoord &crd2);	



