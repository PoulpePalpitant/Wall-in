#pragma once

#include "../UI/coord.h"
#include "../UI/txtstyle.h"
#include "../UI/axis.h"


extern const int WALL_SIZE_X;	// Le nombre de case qui composent chaque wall horizontale
extern const int WALL_SIZE_Y;	// Le nombre de case qui composent chaque wall verticale

//	LES TYPES DE MURS												// Par d�faut, les tirs du joueur font des murs normal
enum class WallType { CORRUPTED, INVINCIBLE};															
enum class WallStrength { WEAK, REGULAR, STRONG, BIGSTRONGWOW};
enum class WallState { DEAD, EXISTS, ETERNAL, SAD};					// Je reviendrais customize �a quand je serais plus avanc�
enum class WallSym { SYM_HOR = 196 , SYM_HOR2 = 205, SYM_VER = 179, SYM_VER2= 186};				// Le symbole d'un seul wall, horizontal et vertical

// Les walls pourraient avoir deux propri�t�s; 1 pour chacun des deux Links qui les cadrent

// Les walls �xisteront uniquement � l'int�rieur d'un Grid de walls de type Horizontal ou vertical
// Ils seront toujours constants jusqu'a leur destruction, c'est-�-dire une redimension du grid les contenants � la fin de 
// chaque niveaux

class Link;	// Les Walls sont reli� au links

class Wall {
	friend class WallGrid;		// WallGrid va initialiser cette bouze
	friend class StructureManager;

private:
	Coord XY = {};							// Coordxy
	WallStrength strgt = WallStrength::REGULAR;		// Type et force de r�sistance au bots du mur (d�pend des propir�t�s du tir du joueur)
	WallState state = WallState::DEAD;		// Si le wall existe visuellement sur l'UI (que le joueur peut le voir)
	Colors color = Colors::WHITE;			// Colors is great. Par d�faut se sera Blanc doe
	WallSym sym;							// Le symbole vertical ou horizontal. Celui-ci peut changer si le type de mur change
	Axis axis;								// D�finis le wall comme �tant vertical ou horizontal(D�pend du Grid dans lequel il se trouve)

	Link* pChild;							// Le Link qui d�pend de ce wall. Si ce Wall ou son parent est d�truis, ce child le sera aussi
private:
	friend class StructureManager;

	Link* pParent;							// Le Link par lequel le wall d�pend pour �xister. Si le Link est d�truit, le wall est d�truit
private:
	// NO TOUCHO!	BAD CODING HERE
	void Set_XY(int col, int row, Axis gridaxis);		// Pas utiliser Pour setup manuellement le xy du mur selon un son axe de grid. Ceci est fait en masse lors de la cr�ation du grid
	void Set_Axis(Axis gridAxis) { axis = gridAxis; }		// Ceci est fait � l'initialisation du Wallgrid, et ne devrait jamais changer!!!

	void Set_Default_Wall_UI();						// On reset l'apparance du mur � ses valeurs par d�faut
	void Set_Wall_UI(WallStrength newType);				// On change l'apparance du mur selon son type!
	void Set_State(WallState newState) { state = newState; }
	void Set_Strength(WallStrength strgt);

public:
	WallState Get_State() { return this->state; }
	WallStrength Get_Type() { return this->strgt; }		// Type et force de r�sistance du mur face aux impacts des bots
	int Get_Wall_Size(Axis axis);						// La longueur du wall
	char Get_Sym() { return (char)this->sym; }		// Acc�s au Symbole du Mur
	Axis Get_Axis() { return axis; }				// Axe du wall
	Coord Get_XY() { return this->XY; }				// Retrouve les Coord XY du Wall 
	Colors Get_Clr() { return color; }				// La couleur

	// Cr�er un mur (techniquement, le mur �tait d�j� l�, mais ici on change son state et son type pour signifier qu'un bot peut � nouveau rentr� dedans)
	void Activate_Wall(WallStrength newStrgt, Link* child);

	// D�truit un Wall. Se produit surtout quand un bot rentre dedans
	void Deactivate_Wall() {
		state = WallState::DEAD;
		pParent = pChild = NULL;
	}

	/* stuff to do here */
	// get hit (r�duit hp de 1)
	// special effect when hit/destroyed
	// erase wall

	void Kill_Wall() { state = WallState::DEAD; }	
	void UI_Draw_Wall(Polarization plr);
};

