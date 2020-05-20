#pragma once

#include "../UI/coord.h"
#include "../UI/txtstyle.h"


/*
	Les propri�t�s des Links

	State: Un Link sans child est un FREE link. Le joueur peut int�ragir avec un FREE Link en se d�pla�ant dessus. Une fois 
	par dessus le joueur peut le transf�r� si il tir dans une autre direction que celle du Link. Le transfert d�truit d'abord
	le link et cr�er un blast dans la direction du tir.	Quand un Link poss�de des childs, on dit qu'il est bound. 
	Il devient donc un obstacle pour le joueur qui ne peut ni se d�placer dessus, ni le transf�rer. Si le Link est DEAD, il est
	inactif, et n'est donc pas affich�s dans la console du jeu. Si il est LONER, les tirs sur celui-ci ne vont rien cr�er. Un Loner ne peut donc pas avoir de Child. Il peut n�anmoins avoir un parent!
	Le type de Link est �galement important. Le type invincible est tr�s puissant et ne pourra jamais �tre d�truit ou transf�r�. N�anmoins, se type peut devenir un fardeau pour le joueur si celui-ci poss�de
	le statut de Loner; tout puissant et seul, pas d'illusion de grandeur icitte!
	Le type strong pourrait cr�er des walls plus durables entre lui-m�me et ces Child.
	Explody Pourrait p�ter des trucs autours, voir m�me une lane au complet?

	
	Id�e int�ressante � consid�rer: Un type de Link qui pourchasse le JOUEUR. Le parfait reversal! Ta puissance qui se retourne contre toi, with great power comes great responsibility and shit!
*/


enum class LinkState { DEAD, FREE, BOUND, LONER };
enum class LinkType{ REGULAR, INVINCIBLE, STRONG, EXPLODY, CHASER };

enum LinkSym 
{
	ROOT = 219,		// Le symbole du premier Link quand il touche la console
	PARENT = 79, 	// Le symbole de chaque Link ayant un child
	CHILD = 250		// Le symbole de chaque Link n'ayant pas de child
};


class Link {
private:
	Coord coord;		// Coord xy du Link dans la console
	LinkState state;	// L'�tat du Link. Le joueur peut seulement se d�placer dessus si il est FREE.
	Link* parent;		// Pointe vers le parent
	Link* child[3];		// Pointe vers ses childs, trois MAX
	
	// Le grid va handle sa position XY
	friend class LinkGrid;
	void Set_LinkXY(int col, int row);	// Initialise position X et Y du Link dans la console par rapport � sa position col et row dans son Grid (ne jamais utilis� directement, seul son grid devrait faire �a)

public:
	Colors color = Colors::WHITE;		// Couleur du Link. Par d�faut c'est white
	char Sym;							// Symbole repr�sentant le Link, varie selon le nombre de child et du parent
	Coord Get_XY() { return coord; }	// Retrouve les Coord XY du Link 
	LinkState Get_State() { return this->state; };	// Donne l'�tat du Link pour savoir si il existe
	
	void KillLink();					// � D�TERMINER LORS de la destruction
	void BoundLink();					// � d�terminer lors de la cr�ation
	void FreeLink();					// � d�terminer lors de la cr�ation
};


