#pragma once

#include "../UI/direction.h"

// p = pointeur!

// COORDONNÉES LOGIQUES DANS LA CONSOLE

struct GrdCoord { int c; int r; };		//  Les grids du jeux seront tous navigué par la logique: Colonnes(x) Lignes(y)

// CONSTANTES POUR L'AFFICHAGE SEULEMENT
// *************************************

extern const int START_X;	// Position, sur l'axe des X de la console, du coin supérieur gauche du main Grid
extern const int START_Y;	// Position, sur l'axe des Y de la console, du coin supérieur gauche du main Grid

extern const int START_X_LVL2;	// Position, sur l'axe des X de la console, du coin supérieur gauche du main Grid
extern const int START_Y_LVL2;	// Position, sur l'axe des Y de la console, du coin supérieur gauche du main Grid

extern const int DELTA_X;	// Saut sur l'axe des X d'une case à l'autre(Main Grid)
extern const int DELTA_Y;	// Saut sur l'axe des Y d'une case à l'autre

// CLASS DE GRID HERE WE GO

class Grid {	// Le Grid servira uniquement de références pour le LinkGrid et le WallGrid
private:
	int numCol;	// Dimension en colonne du Grid		// Warning, quand on accède au max, il faut faire [numCol -1]
	int numRow;	// Dimension en lignes du Grid		// Warning, quand on accède au max, il faut faire [numRow -1]
protected:
	void UpdSize(int col, int row) { this->numCol = col;this->numRow = row; }	//Update les lignes et les colonnes: utilisé dans la méthode Create
public:
	// LES MÉTHODES
	void Create(int col, int row, int**& grid);	// Créer le Grid. Persistera jusqu'au prochain Resize
	void Resize(int col, int row, int**& grid);	// Redimensionne.... Mais détruit aussi les valeurs du grid...
	bool Is_Inbound(GrdCoord crd);			// Vérifie si la coord donnée est présente dans le grid
	int Get_Rows() { return this->numRow; }				// Get numRow
	int Get_Cols() { return this->numCol; }				// Get numCol
};

void Equal_Coordinates(GrdCoord& from, GrdCoord to);		// Permet d'égaliser deux valeurs de coordonnées de grid [col][row]
bool Is_Equal(const GrdCoord &crd1, const GrdCoord &crd2);						// Vérification d'une égalité entre deux coordonnées de grid



