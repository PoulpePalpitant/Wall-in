#pragma once

#include "../UI/coord.h"
#include "../UI/txtstyle.h"
#include "../UI/axis.h"
#include "../bots/bot.h"
#include "wall_drawer.h"

extern const int WALL_SIZE_X;	// Le nombre de case qui composent chaque wall horizontale
extern const int WALL_SIZE_Y;	// Le nombre de case qui composent chaque wall verticale

//	LES TYPES DE MURS												
enum class WallType { WEAK, REGULAR, STRONG, INVINCIBRU, ENERGIZED}; // Par défaut, les tirs du joueur font des murs REGULAR
enum class WallState { DEAD, EXISTS, ETERNAL, SAD};					// Je reviendrais customize ça quand je serais plus avancé
enum class WallSym {DEAD = 255, SYM_HOR = 196 , SYM_HOR2 = 205, SYM_HOR3 = 240,  SYM_VER = 179, SYM_VER2= 186, SYM_VER3 = 221};				// Le symbole d'un seul wall, horizontal et vertical

// Les walls éxisteront uniquement à l'intérieur d'un Grid de walls de type Horizontal ou vertical
// Ils seront toujours constants jusqu'a leur destruction, c'est-à-dire une redimension du grid les contenants à la fin de chaque niveaux

class Link;	// Les Walls sont relié au links

class Wall {
	friend class WallGrid;					// WallGrid va initialiser cette bouze
	friend class ListsOfChainToModify;
	friend class StructureManager;

	WallDrawer drawer;						// Responsable de l'affichage du wall
	Coord XY = {};							
	WallType type = WallType::REGULAR;		
	WallState state = WallState::DEAD;		// Si le wall existe visuellement sur l'UI (que le joueur peut le voir)
	Colors clr = Colors::BRIGHT_WHITE;		
	WallSym sym = WallSym::DEAD;			
	Axis axis = HOR;						// Définis le wall comme étant vertical ou horizontal(Dépend du Grid dans lequel il se trouve)
	int hp;									
	int botOnMe = -1;						// Si le wall s'active au même moment qu'un bot se trouve dessus, celui-ci sera détruit

	Link* pParent = NULL;					// Le Link par lequel le wall dépend pour éxister. Si le Link est détruit, le wall est détruit
	Link* pChild = NULL;					// Le Link qui dépend de ce wall. Si ce Wall ou son parent est détruis, ce child le sera aussi
	Polarization childPos = POS;			// Renseigne sur la position du CHILD selon la polarisation POS/NEG		Si POS: Le child est soit à droite, soit en bas. Contraire pour le NEG

	// NO TOUCHO!	BAD CODING HERE
	void Set_XY(int col, int row, Axis gridaxis);			
	void Set_Axis(Axis gridAxis) { axis = gridAxis; }		// Ceci est fait à l'initialisation du Wallgrid, et ne devrait jamais changer!!!

	void Set_Default_Wall_UI();						
	void Set_State(WallState newState) { state = newState; }
	void Set_Strength_From_Parent(WallType type = WallType::REGULAR);

public:
	WallState Get_State() { return this->state; }
	Modifier Get_Parent_Modifier() { return pParent->Get_Modifier(); }
	WallType Get_Type() { return this->type; }		
	int Get_Hp() { return hp; }
	char Get_Sym() { return (char)this->sym; }		
	Axis Get_Axis() { return axis; }				
	Coord Get_XY() { return this->XY; }				
	Colors Get_Clr() { return clr; }				
	int Get_Wall_Size(Axis axis);					
	int Get_Bot_On_Me() { return botOnMe; }			

	// Active un mur (techniquement, le mur était déjà là, mais ici on change son state et son type pour signifier qu'un bot peut à nouveau rentré dedans)
	void Activate_Wall(WallType newStrgt, Link* child, Polarization plr);
	bool Is_Activated();		

	void Add_Bot_On_Me(int botIndex) { botOnMe = botIndex; }	// Un bot se trouve sur le wall 
	void Remove_Bot_On_Me();

	// Détruit un Wall. Se produit surtout quand un bot rentre dedans
	void Deactivate_Wall();

	void Take_Damage(int dmg);		// Dépend de la force du bot
	void Set_Wall_UI();				// On change l'apparance du mur selon son type!
	void Set_Drawer(bool erase = false, bool instant = false);									// Préparation pour l'affichage ou l'effaçage
	void Set_Type(WallType type) {
		this->type = type;
		Set_Strength_From_Parent(type);
		Set_Wall_UI();
	}
};

