#pragma once

#include "../UI/coord.h"
#include "../UI/txtstyle.h"
#include "../global_types/global_types.h"

/*
	Les propriétés des Links
	
	State: Un Link sans child est un FREE link. Le joueur peut intéragir avec un FREE Link en se déplaçant dessus. Une fois 
	par dessus le joueur peut le transféré si il tir dans une autre direction que celle du Link. Le transfert détruit d'abord
	le link et créer un blast dans la direction du tir.	Quand un Link possède des childs, on dit qu'il est bound. Quand il est root, c'est qu'il est le premier sur la bordure, et qu'il ne peut pas avoir de parent
	Il devient donc un obstacle pour le joueur qui ne peut ni se déplacer dessus, ni le transférer. Si le Link est DEAD, il est
	inactif, et n'est donc pas affichés dans la console du jeu. Si il est LONER, les tirs sur celui-ci ne vont rien créer. Un Loner ne peut donc pas avoir de Child. Il peut néanmoins avoir un parent!
	Le type de Link est également important. Le type invincible est très puissant et ne pourra jamais être détruit ou transféré. Néanmoins, se type peut devenir un fardeau pour le joueur si celui-ci possède
	le statut de Loner; tout puissant et seul, pas d'illusion de grandeur icitte!
	Le type strong pourrait créer des walls plus durables entre lui-même et ces Child.
	Explody Pourrait péter des trucs autours, voir même une lane au complet?

	Deux Link de Type différents pourrait créer une combinaison d'effet pour le WALL se trouvant entre les deux!

	Idée intéressante à considérer: Un type de Link qui pourchasse le JOUEUR. Le parfait reversal! Ta puissance qui se retourne contre toi, with great power comes great responsibility and shit!
*/


enum class LinkState { DEAD, FREE, BOUND, ROOT, GODLIKE };	// si invincible, il ne peut changer de type, et ne peut mourir
//enum class LinkType{ REGULAR , ETERNAL, GROWER, CORRUPTED = 245 ,MINE,	 CHASER, BLOCKER};		// Si tu pile sur la mine, tu prend 1 de dégât. Si tu tir dessus, tu va créer une autre mine avec ton blast!!!

enum LinkSym 
{
	ROOT = 219,		// Le symbole du premier Link quand il touche la console
	PARENT = 79, 	// Le symbole de chaque Link ayant un child
	CHILD = 250,		// Le symbole de chaque Link n'ayant pas de child
	STRONG = 254
};

class Wall;		// Les Links sont reliés aux walls

class LinkMeta
{
	public:
		int active;		// Le nombre de bots en vie en ce moment
		int dead;		// Le nombre de bots qui ont péris

		void Add() { this->active++;}
		void Remove() { this->active--; this->dead++; }
};

class Link {
private:
	// Pour faire une destruction en chaîne de Links
	friend class ListsOfChainToModify;
	friend class StructureManager;

	static LinkMeta meta;	// das meta

	Coord coord;						// Coord xy du Link dans la console
	LinkState state = LinkState::DEAD;	// L'état du Link. Le joueur peut seulement se déplacer dessus si il est FREE.						
	Modifier modifier = REGULAR;						// type du link																						
																																			
	// UI																																							  //		 o	4 max		3max
	Colors clr = Colors::WHITE;			// Couleur du Link. Par défaut c'est white																					  //		 |				
	unsigned char sym = 250;						// Symbole représentant le Link, varie selon le nombre de child et du parent												  //		 |
	void Set_UI();						// Change la couleur et le symbole selon le Type et le State du Link														  //	  o--#--o	  o--#--o	
																																									  //		 |			 |
																																									  //		 |			 |
	Wall* pWalls[4] = {};		// Pointe vers ses childs de walls, trois MAX sur une bordure. 4 MAX si le Link est créer manuellement au milieu de la map			  //		 O			 O
	int numChild = 0;			// Le nombre de child actuelle qui sont lié au link																													  //
	Wall* pParent = NULL;		// Pointe vers le parent wall. Quand le wall est activé, le ptr est assigné
private:
	// Activation
	void Set_State(Wall* child = NULL);					// Assigne le state 

	// Le grid va handle sa position XY
	friend class LinkGrid;
	void Set_LinkXY(int col, int row);					// Initialise position X et Y du Link dans la console par rapport à sa position col et row dans son Grid (ne jamais utilisé directement, seul son grid devrait faire ça)
public:
	// Link transformation
	void Modifier_Inheritance(Modifier& mod);			//  le modifier
	void Convert_Modifier(Modifier mod);
	bool Set_First_Modifier(Modifier mod);// Assigne le state 	
	bool Activate_Link(Modifier& mod, Wall* child = NULL);	// Active un Link sur le grid, en lui donnant des propriétés and shit. Le connect tu suite à son child, si yen a un.
	bool Activate_Lonely_Link(Modifier mod = REGULAR);					// Active un link, sans le lier à aucun wall

	void Deactivate_Link();		// Désactive le Link
	bool Unbound_Wall_Child(Wall* child);		// change le state/détruit de le lin k si il n'a plus de child
	void Unbound_All_Child();					// 

	// GETS
	int Get_Num_Child() { return numChild; }		// À noter qu'un Link Root peut avoir aucun child, il est donc plus sécuritaire d'utiliser cette fonction pour vérifier ce fait
	Wall* Get_Child(int index) { return pWalls[index]; }
	Wall* Get_Parent() { return pParent; }			// Le parent WALL immédiat
	Coord Get_XY() { return coord; }				// Retrouve les Coord XY du Link 
	LinkState Get_State(){
		return this->state;
	}	// Donne l'état du Link pour savoir si il existe	
	Modifier Get_Modifier() { return modifier; }

	// UI
	void Change_Color(Colors clr);
	void Dsp_Link();			// Affiche le Link
	void Er_Link();			// Clear le Link	ne pas utilisé si le link est vivant doe
};


