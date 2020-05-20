#pragma once

#include "../UI/coord.h"
#include "../UI/txtstyle.h"


/*
	Les propriétés des Links

	State: Un Link sans child est un FREE link. Le joueur peut intéragir avec un FREE Link en se déplaçant dessus. Une fois 
	par dessus le joueur peut le transféré si il tir dans une autre direction que celle du Link. Le transfert détruit d'abord
	le link et créer un blast dans la direction du tir.	Quand un Link possède des childs, on dit qu'il est bound. 
	Il devient donc un obstacle pour le joueur qui ne peut ni se déplacer dessus, ni le transférer. Si le Link est DEAD, il est
	inactif, et n'est donc pas affichés dans la console du jeu. Si il est LONER, les tirs sur celui-ci ne vont rien créer. Un Loner ne peut donc pas avoir de Child. Il peut néanmoins avoir un parent!
	Le type de Link est également important. Le type invincible est très puissant et ne pourra jamais être détruit ou transféré. Néanmoins, se type peut devenir un fardeau pour le joueur si celui-ci possède
	le statut de Loner; tout puissant et seul, pas d'illusion de grandeur icitte!
	Le type strong pourrait créer des walls plus durables entre lui-même et ces Child.
	Explody Pourrait péter des trucs autours, voir même une lane au complet?

	
	Idée intéressante à considérer: Un type de Link qui pourchasse le JOUEUR. Le parfait reversal! Ta puissance qui se retourne contre toi, with great power comes great responsibility and shit!
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
	LinkState state;	// L'état du Link. Le joueur peut seulement se déplacer dessus si il est FREE.
	Link* parent;		// Pointe vers le parent
	Link* child[3];		// Pointe vers ses childs, trois MAX
	
	// Le grid va handle sa position XY
	friend class LinkGrid;
	void Set_LinkXY(int col, int row);	// Initialise position X et Y du Link dans la console par rapport à sa position col et row dans son Grid (ne jamais utilisé directement, seul son grid devrait faire ça)

public:
	Colors color = Colors::WHITE;		// Couleur du Link. Par défaut c'est white
	char Sym;							// Symbole représentant le Link, varie selon le nombre de child et du parent
	Coord Get_XY() { return coord; }	// Retrouve les Coord XY du Link 
	LinkState Get_State() { return this->state; };	// Donne l'état du Link pour savoir si il existe
	
	void KillLink();					// À DÉTERMINER LORS de la destruction
	void BoundLink();					// À déterminer lors de la création
	void FreeLink();					// À déterminer lors de la création
};


