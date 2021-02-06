#pragma once

#include "../UI/coord.h"
#include "../UI/txtstyle.h"
#include "../global_types/global_types.h"

/*
	Les propriétés des Links
	
	State: Un Link sans child est un FREE link. Le joueur peut intéragir avec un FREE Link en se déplaçant dessus.
	Une fois par dessus le joueur peut le transféré si il tir dans une autre direction que celle du Link. Le transfert détruit d'abordle link et créer un blast dans la direction du tir.	
	EXCEPTION, le joueur ne peut pas se déplacer sur les link qui possèdent un modifiers, même si ils sont FREE. SAUF, si le link est créé sous le joueur(par un tir). Le joueur peut aussi se teleport sur un link avec un modifier
	Quand un Link possède des childs, on dit qu'il est bound. Quand il est root, c'est qu'il est n'a pas de parent
	Il devient donc un obstacle pour le joueur qui ne peut ni se déplacer dessus, ni le transférer. 
	Si le Link est DEAD, il est	inactif, et n'est donc pas affichés dans la console du jeu.
	Les links qui possèdent un modifier autre que REGULAR et qui possède le LinkSTate::ROOT ne peuvent mourir.
*/


enum class LinkState { DEAD, FREE, BOUND, ROOT, GODLIKE };	

enum LinkSym 
{
	ROOT = 219,		
	PARENT = 79, 	
	CHILD = 250,	
	STRONG = 254
};

class Wall;		// Les Links sont reliés aux walls

class LinkMeta
{
	public:
		int active;	
		int dead;	

		void Add() { this->active++;}
		void Remove() { this->active--; this->dead++; }
};

class Link {
private:
	// Pour faire une destruction en chaîne de Links
	friend class ListsOfChainToModify;
	friend class StructureManager;

	static LinkMeta meta;	

	Coord coord;			
	LinkState state = LinkState::DEAD;	
	Modifier modifier = REGULAR;		
																																			
	// UI																																							  //		 o	4 max		3max
	Colors clr = Colors::WHITE;																																		  //		 |				
	unsigned char sym = 250;																																		  //		 |
	void Set_UI();																																					  //	  o--#--o	  o--#--o	
																																									  //		 |			 |
																																									  //		 |			 |
	Wall* pWalls[4] = {};		// Pointe vers ses childs de walls, trois MAX sur une bordure. 4 MAX si le Link est créer manuellement au milieu de la map			  //		 O			 O
	int numChild = 0;			// Le nombre de child actuelle qui sont lié au link																													  //
	Wall* pParent = NULL;		// Pointe vers le parent wall. Quand le wall est activé, le ptr est assigné
private:
	void Set_State(Wall* child = NULL);			

	friend class LinkGrid;
	void Set_LinkXY(int col, int row);		// Initialise position X et Y du Link dans la console par rapport à sa position col et row dans son Grid (ne jamais utilisé directement, seul son grid devrait faire ça)
public:
	void Modifier_Inheritance(Modifier& mod);			
	void Convert_Modifier(Modifier mod, bool overRideDumbRuleOfSpaghetti = false);
	bool Set_First_Modifier(Modifier mod);
	bool Activate_Link(Modifier& mod, Wall* child = NULL);
	bool Activate_Lonely_Link(Modifier mod = REGULAR);		

	void Deactivate_Link();		
	bool Unbound_Wall_Child(Wall* child);
	void Unbound_All_Child();			

	int Get_Num_Child() { return numChild; }		
	Wall* Get_Child(int index) { return pWalls[index]; }
	Wall* Get_Parent() { return pParent; }			
	Coord Get_XY() { return coord; }				
	LinkState Get_State(){	return this->state;	}	
	Modifier Get_Modifier() { return modifier; }

	void Change_Color(Colors clr);
	void Dsp_Link();
	void Er_Link();	
};


