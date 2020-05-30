#pragma once

#include "../UI/coord.h"
#include "../UI/txtstyle.h"


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
	LinkState state = LinkState::DEAD;	// L'�tat du Link. Le joueur peut seulement se d�placer dessus si il est FREE.
	LinkType type;						// type du link

	// UI
	Colors clr = Colors::WHITE;			// Couleur du Link. Par d�faut c'est white
	char sym = 'B';						// Symbole repr�sentant le Link, varie selon le nombre de child et du parent
	void Set_UI();						// Change la couleur et le symbole selon le Type et le State du Link

	// Pour faire une destruction en cha�ne de Links
	friend class DestroyChainOfWalls;

	Link* pChild[3] = {};		// Pointe vers ses childs, trois MAX
	int numChild;				// Le nombre de child actuelle qui sont li� au link
	Link* pParent = NULL;		// Pointe vers le parent
	Polarization parentPos;		// Renseigne sur la position du parent selon la polarisation POS/NEG		Si POS: Le parent est soit � droite, soit en bas.		Contraire pour le NEG
	// Wall* btwnParent;		// Le wall positionn� entre ce Link et son parent 
private:
	// Activation
	void Bond_Link_To_Child(Link* child);				// Assigne les pointeurs du parent � son child et vice versa
	void Set_State(Link* child = NULL);					// Assigne le state 

	// Le grid va handle sa position XY
	friend class LinkGrid;
	void Set_LinkXY(int col, int row);					// Initialise position X et Y du Link dans la console par rapport � sa position col et row dans son Grid (ne jamais utilis� directement, seul son grid devrait faire �a)

public:
	Coord Get_XY() { return coord; }				// Retrouve les Coord XY du Link 
	LinkState Get_State() { return this->state; }	// Donne l'�tat du Link pour savoir si il existe
	
	void Dsp_Link();			// Affiche le Link
	void Clr_Link();			// Clear le Link	ne pas utilis� si le link est vivant doe
	
	bool Activate_Link(LinkType &type, Link* child = NULL);	// Active un Link sur le grid, en lui donnant des propri�t�s and shit. Le connect tu suite � son child, si yen a un.
	void Deactivate_Link();		// D�sactive le Link
};


