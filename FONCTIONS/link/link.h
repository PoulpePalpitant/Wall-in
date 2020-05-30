#pragma once

#include "../UI/coord.h"
#include "../UI/txtstyle.h"


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


enum class LinkState { DEAD, FREE, BOUND, ROOT };
enum class LinkType{ REGULAR, LONER , INVINCIBLE, STRONG, EXPLODY, CHASER };

enum LinkSym 
{
	ROOT = 219,		// Le symbole du premier Link quand il touche la console
	PARENT = 79, 	// Le symbole de chaque Link ayant un child
	CHILD = 250		// Le symbole de chaque Link n'ayant pas de child
};


class Link {
private:
	Coord coord;						// Coord xy du Link dans la console
	LinkState state = LinkState::DEAD;	// L'état du Link. Le joueur peut seulement se déplacer dessus si il est FREE.
	LinkType type;						// type du link

	// UI
	Colors clr = Colors::WHITE;			// Couleur du Link. Par défaut c'est white
	char sym = 'B';						// Symbole représentant le Link, varie selon le nombre de child et du parent
	void Set_UI();						// Change la couleur et le symbole selon le Type et le State du Link

	// Pour faire une destruction en chaîne de Links
	friend class DestroyChainOfWalls;

	Link* pChild[3] = {};		// Pointe vers ses childs, trois MAX
	int numChild;				// Le nombre de child actuelle qui sont lié au link
	Link* pParent = NULL;		// Pointe vers le parent
	Polarization parentPos;		// Renseigne sur la position du parent selon la polarisation POS/NEG		Si POS: Le parent est soit à droite, soit en bas.		Contraire pour le NEG
	// Wall* btwnParent;		// Le wall positionné entre ce Link et son parent 
private:
	// Activation
	void Bond_Link_To_Child(Link* child);				// Assigne les pointeurs du parent à son child et vice versa
	void Set_State(Link* child = NULL);					// Assigne le state 

	// Le grid va handle sa position XY
	friend class LinkGrid;
	void Set_LinkXY(int col, int row);					// Initialise position X et Y du Link dans la console par rapport à sa position col et row dans son Grid (ne jamais utilisé directement, seul son grid devrait faire ça)

public:
	Coord Get_XY() { return coord; }				// Retrouve les Coord XY du Link 
	LinkState Get_State() { return this->state; }	// Donne l'état du Link pour savoir si il existe
	
	void Dsp_Link();			// Affiche le Link
	void Clr_Link();			// Clear le Link	ne pas utilisé si le link est vivant doe
	
	bool Activate_Link(LinkType &type, Link* child = NULL);	// Active un Link sur le grid, en lui donnant des propriétés and shit. Le connect tu suite à son child, si yen a un.
	void Deactivate_Link();		// Désactive le Link
};


