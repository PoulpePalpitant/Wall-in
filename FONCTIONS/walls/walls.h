#pragma once

#include "../UI/coord.h"
#include "../UI/txtstyle.h"
#include "../UI/axis.h"
#include "../blast/blast.h"

//	LES TYPES DE MURS												// Par défaut, les tirs du joueur font des murs normal
enum class WallType { WEAK, REGULAR, GHOST, STRONG, BIGSTRONGWOW };	// "Ghost" : pourrait être des murs que les bot peuvent traverser																
enum class WallSym { SYM_HOR = 196 , SYM_HOR2 = 205, SYM_VER = 179, SYM_VER2= 186};				// Le symbole d'un seul wall, horizontal et vertical
enum class WallState { DEAD, EXISTS, ETERNAL, SAD};					// Je reviendrais customize ça quand je serais plus avancé

// Les walls pourraient avoir deux propriétés; 1 pour chacun des deux Links qui les cadrent

// Les walls éxisteront uniquement à l'intérieur d'un Grid de walls de type Horizontal ou vertical
// Ils seront toujours constants jusqu'a leur destruction, c'est-à-dire une redimension du grid les contenants à la fin de 
// chaque niveaux

class Wall {
	friend class WallGrid;		// WallGrid va initialiser cette bouze

private:
	Coord XY = {};							// Coordxy
	WallType type = WallType::REGULAR;		// Type et force de résistance au bots du mur (dépend des propirétés du tir du joueur)
	WallState state = WallState::DEAD;		// Si le wall existe visuellement sur l'UI (que le joueur peut le voir)
	Colors color = Colors::WHITE;			// Colors is great. Par défaut se sera Blanc doe
	WallSym sym;							// Le symbole vertical ou horizontal. Celui-ci peut changer si le type de mur change
	Axis axis;								// Définis le wall comme étant vertical ou horizontal(Dépend du Grid dans lequel il se trouve)
	
	// NO TOUCHO!	BAD CODING HERE
	void Set_XY(int col, int row, Axis gridaxis);		// Pas utiliser Pour setup manuellement le xy du mur selon un son axe de grid. Ceci est fait en masse lors de la création du grid
	void Set_Axis(Axis gridAxis) { axis = gridAxis; }		// Ceci est fait à l'initialisation du Wallgrid, et ne devrait jamais changer!!!

	void Set_Default_Wall_UI();						// On reset l'apparance du mur à ses valeurs par défaut
	void Set_Wall_UI(WallType newType);				// On change l'apparance du mur selon son type!
	void Set_State(WallState newState) { state = newState; }
public:
	WallState Get_State() { return this->state; }
	WallType Get_Type() { return this->type; }		// Type et force de résistance du mur face aux impacts des bots
	
	// UI
	char Get_Sym() { return (char)this->sym; }	// Accès au Symbole du Mur
	Coord Get_XY() { return this->XY; }				// Retrouve les Coord XY du Wall 
	Colors Get_Clr() { return color; }				// La couleur
	

	// Créer un mur (techniquement, le mur était déjà là, mais ici on change son state et son type pour signifier qu'un bot peut à nouveau rentré dedans)
	void Activate_Wall(WallType newType = WallType::REGULAR) {			
		state = WallState::EXISTS;		// It's alive!
		
		Set_Wall_UI(newType);			// Update l'UI si le nouv type est le même que le précédent. Les symboles sur le walls sont pas très nécessaires à enregistré à chaque fois
		type = newType;					// Le nouveau type du mur
	}

	// Détruit un Wall. Se produit surtout quand un bot rentre dedans
	void Kill_Wall() { state = WallState::DEAD; }	
};