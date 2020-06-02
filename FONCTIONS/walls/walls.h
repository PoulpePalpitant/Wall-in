#pragma once

#include "../UI/coord.h"
#include "../UI/txtstyle.h"
#include "../UI/axis.h"
#include "../blast/blast.h"
#include "../link/link.h"

extern const int WALL_SIZE_X;	// Le nombre de case qui composent chaque wall horizontale
extern const int WALL_SIZE_Y;	// Le nombre de case qui composent chaque wall verticale

//	LES TYPES DE MURS												// Par défaut, les tirs du joueur font des murs normal
enum class WallType { CORRUPTED, INVINCIBLE};															
enum class WallStrength { WEAK, REGULAR, STRONG, BIGSTRONGWOW};
enum class WallState { DEAD, EXISTS, ETERNAL, SAD};					// Je reviendrais customize ça quand je serais plus avancé
enum class WallSym { SYM_HOR = 196 , SYM_HOR2 = 205, SYM_VER = 179, SYM_VER2= 186};				// Le symbole d'un seul wall, horizontal et vertical

// Les walls pourraient avoir deux propriétés; 1 pour chacun des deux Links qui les cadrent

// Les walls éxisteront uniquement à l'intérieur d'un Grid de walls de type Horizontal ou vertical
// Ils seront toujours constants jusqu'a leur destruction, c'est-à-dire une redimension du grid les contenants à la fin de 
// chaque niveaux

class Wall {
	friend class WallGrid;		// WallGrid va initialiser cette bouze

private:
	Coord XY = {};							// Coordxy
	WallStrength strgt = WallStrength::REGULAR;		// Type et force de résistance au bots du mur (dépend des propirétés du tir du joueur)
	WallState state = WallState::DEAD;		// Si le wall existe visuellement sur l'UI (que le joueur peut le voir)
	Colors color = Colors::WHITE;			// Colors is great. Par défaut se sera Blanc doe
	WallSym sym;							// Le symbole vertical ou horizontal. Celui-ci peut changer si le type de mur change
	Axis axis;								// Définis le wall comme étant vertical ou horizontal(Dépend du Grid dans lequel il se trouve)
	
	Link* pParent;							// Le Link par lequel le wall dépend pour éxister. Si le Link est détruit, le wall est détruit
	Link* pChild;							// Le Link qui dépend de ce wall. Si ce Wall ou son parent est détruis, ce child le sera aussi

	// NO TOUCHO!	BAD CODING HERE
	void Set_XY(int col, int row, Axis gridaxis);		// Pas utiliser Pour setup manuellement le xy du mur selon un son axe de grid. Ceci est fait en masse lors de la création du grid
	void Set_Axis(Axis gridAxis) { axis = gridAxis; }		// Ceci est fait à l'initialisation du Wallgrid, et ne devrait jamais changer!!!

	void Set_Default_Wall_UI();						// On reset l'apparance du mur à ses valeurs par défaut
	void Set_Wall_UI(WallStrength newType);				// On change l'apparance du mur selon son type!
	void Set_State(WallState newState) { state = newState; }
	void Set_Strength(WallStrength strgt);
	void Bound_To_Adjacent_Links(Link* parent, Link* child) { pParent = parent; pChild = child; }	// Pointeurs vers les deux Links autours du wall

public:
	WallState Get_State() { return this->state; }
	WallStrength Get_Type() { return this->strgt; }		// Type et force de résistance du mur face aux impacts des bots
	int Get_Wall_Size(Axis axis);						// La longueur du wall
	char Get_Sym() { return (char)this->sym; }		// Accès au Symbole du Mur
	Axis Get_Axis() { return axis; }				// Axe du wall
	Coord Get_XY() { return this->XY; }				// Retrouve les Coord XY du Wall 
	Colors Get_Clr() { return color; }				// La couleur

	// Créer un mur (techniquement, le mur était déjà là, mais ici on change son state et son type pour signifier qu'un bot peut à nouveau rentré dedans)
	void Activate_Wall(WallStrength newStrgt, Link* parent, Link* child) {
		
		state = WallState::EXISTS;				// It's alive!
		Bound_To_Adjacent_Links(parent, child);	// Relie le wall à deux Links
		Set_Strength(newStrgt);					// La nouvelle force du mur
		Set_Wall_UI(newStrgt);					// Update l'UI si le nouv type est différent que le précédent.

		/* Fut changé */

	}

	// Détruit un Wall. Se produit surtout quand un bot rentre dedans
	void Kill_Wall() { state = WallState::DEAD; }	
	void UI_Draw_Wall(Polarization plr;
};

