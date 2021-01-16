#pragma once

#include "../UI/coord.h"
#include "../UI/txtstyle.h"
#include "../global_types/global_types.h"

/*
	Les propri�t�s des Links
	
	State: Un Link sans child est un FREE link. Le joueur peut int�ragir avec un FREE Link en se d�pla�ant dessus. Une fois 
	par dessus le joueur peut le transf�r� si il tir dans une autre direction que celle du Link. Le transfert d�truit d'abord
	le link et cr�er un blast dans la direction du tir.	Quand un Link poss�de des childs, on dit qu'il est bound. Quand il est root, c'est qu'il est le premier sur la bordure, et qu'il ne peut pas avoir de parent
	Il devient donc un obstacle pour le joueur qui ne peut ni se d�placer dessus, ni le transf�rer. Si le Link est DEAD, il est
	inactif, et n'est donc pas affich�s dans la console du jeu. Si il est LONER, les tirs sur celui-ci ne vont rien cr�er. Un Loner ne peut donc pas avoir de Child. Il peut n�anmoins avoir un parent!
	Le type de Link est �galement important. Le type invincible est tr�s puissant et ne pourra jamais �tre d�truit ou transf�r�. N�anmoins, se type peut devenir un fardeau pour le joueur si celui-ci poss�de
	le statut de Loner; tout puissant et seul, pas d'illusion de grandeur icitte!
	Le type strong pourrait cr�er des walls plus durables entre lui-m�me et ces Child.
	Explody Pourrait p�ter des trucs autours, voir m�me une lane au complet?

	Deux Link de Type diff�rents pourrait cr�er une combinaison d'effet pour le WALL se trouvant entre les deux!

	Id�e int�ressante � consid�rer: Un type de Link qui pourchasse le JOUEUR. Le parfait reversal! Ta puissance qui se retourne contre toi, with great power comes great responsibility and shit!
*/


enum class LinkState { DEAD, FREE, BOUND, ROOT, GODLIKE };	// si invincible, il ne peut changer de type, et ne peut mourir
//enum class LinkType{ REGULAR , ETERNAL, GROWER, CORRUPTED = 245 ,MINE,	 CHASER, BLOCKER};		// Si tu pile sur la mine, tu prend 1 de d�g�t. Si tu tir dessus, tu va cr�er une autre mine avec ton blast!!!

enum LinkSym 
{
	ROOT = 219,		// Le symbole du premier Link quand il touche la console
	PARENT = 79, 	// Le symbole de chaque Link ayant un child
	CHILD = 250,		// Le symbole de chaque Link n'ayant pas de child
	STRONG = 254
};

class Wall;		// Les Links sont reli�s aux walls

class LinkMeta
{
	public:
		int active;		// Le nombre de bots en vie en ce moment
		int dead;		// Le nombre de bots qui ont p�ris

		void Add() { this->active++;}
		void Remove() { this->active--; this->dead++; }
};

class Link {
private:
	// Pour faire une destruction en cha�ne de Links
	friend class ListsOfChainToModify;
	friend class StructureManager;

	static LinkMeta meta;	// das meta

	Coord coord;						// Coord xy du Link dans la console
	LinkState state = LinkState::DEAD;	// L'�tat du Link. Le joueur peut seulement se d�placer dessus si il est FREE.						
	Modifier modifier = REGULAR;						// type du link																						
																																			
	// UI																																							  //		 o	4 max		3max
	Colors clr = Colors::WHITE;			// Couleur du Link. Par d�faut c'est white																					  //		 |				
	unsigned char sym = 250;						// Symbole repr�sentant le Link, varie selon le nombre de child et du parent												  //		 |
	void Set_UI();						// Change la couleur et le symbole selon le Type et le State du Link														  //	  o--#--o	  o--#--o	
																																									  //		 |			 |
																																									  //		 |			 |
	Wall* pWalls[4] = {};		// Pointe vers ses childs de walls, trois MAX sur une bordure. 4 MAX si le Link est cr�er manuellement au milieu de la map			  //		 O			 O
	int numChild = 0;			// Le nombre de child actuelle qui sont li� au link																													  //
	Wall* pParent = NULL;		// Pointe vers le parent wall. Quand le wall est activ�, le ptr est assign�
private:
	// Activation
	void Set_State(Wall* child = NULL);					// Assigne le state 

	// Le grid va handle sa position XY
	friend class LinkGrid;
	void Set_LinkXY(int col, int row);					// Initialise position X et Y du Link dans la console par rapport � sa position col et row dans son Grid (ne jamais utilis� directement, seul son grid devrait faire �a)
public:
	// Link transformation
	void Modifier_Inheritance(Modifier& mod);			//  le modifier
	void Convert_Modifier(Modifier mod);
	bool Set_First_Modifier(Modifier mod);// Assigne le state 	
	bool Activate_Link(Modifier& mod, Wall* child = NULL);	// Active un Link sur le grid, en lui donnant des propri�t�s and shit. Le connect tu suite � son child, si yen a un.
	bool Activate_Lonely_Link(Modifier mod = REGULAR);					// Active un link, sans le lier � aucun wall

	void Deactivate_Link();		// D�sactive le Link
	bool Unbound_Wall_Child(Wall* child);		// change le state/d�truit de le lin k si il n'a plus de child
	void Unbound_All_Child();					// 

	// GETS
	int Get_Num_Child() { return numChild; }		// � noter qu'un Link Root peut avoir aucun child, il est donc plus s�curitaire d'utiliser cette fonction pour v�rifier ce fait
	Wall* Get_Child(int index) { return pWalls[index]; }
	Wall* Get_Parent() { return pParent; }			// Le parent WALL imm�diat
	Coord Get_XY() { return coord; }				// Retrouve les Coord XY du Link 
	LinkState Get_State(){
		return this->state;
	}	// Donne l'�tat du Link pour savoir si il existe	
	Modifier Get_Modifier() { return modifier; }

	// UI
	void Change_Color(Colors clr);
	void Dsp_Link();			// Affiche le Link
	void Er_Link();			// Clear le Link	ne pas utilis� si le link est vivant doe
};


