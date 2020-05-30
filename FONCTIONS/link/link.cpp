
#include "../grid/grid.h"
#include "../UI/console_output/dsp_char.h"


#include "link.h"


// La position x et y du Link dans la console, par rapport à son propre LinkGrid
void Link::Set_LinkXY(int col, int row)
{
	this->coord.x = START_X + DELTA_X * col;			
	this->coord.y = START_Y + DELTA_Y * row;
}

void Link::Set_State(Link* child )	// Assigne le state 
{
	if (!this->pParent)	// Pas de Parent? T'es le premier d'une ligné!
		state = LinkState::ROOT;
	else
		if (child == NULL)
			state = LinkState::FREE;	// Pas de child? T'es FREE!
		else
			state = LinkState::BOUND;		// Ah, tu es lié finalement
}

// Change la couleur et le symbole selon le Type et le State du Link
void Link::Set_UI()						
{
	switch (this->type)
	{
	case LinkType::REGULAR: 
	case LinkType::EXPLODY:
	case LinkType::INVINCIBLE:	// BREAK!
	case LinkType::CHASER:
	case LinkType::STRONG:
		if (state == LinkState::ROOT)
			sym = (char)LinkSym::ROOT;
		if (state == LinkState::BOUND)
			sym = (char)LinkSym::PARENT;
		if (state == LinkState::FREE)
			sym = (char)LinkSym::CHILD;	// BREAK!
	}
	clr = WHITE;	//default bitch
}

// Assigne les pointeurs du parent à son child et vice versa
void Link::Bond_Link_To_Child(Link* child)
{
	if (child == NULL)	// Pas d'enfant icitte moé
		return;	
	/*mutex*/
	for (int i = 0; i < 3; i++)	// 3 = max number of childs. For real, si tu fais cette fonctions et qu'ya déjà trois child, ta foiré quelque part
	{
		if (this->pChild[i] == NULL)
		{
			this->pChild[i] = child;	// Voici ton fils
			child->pParent = this;		// Voici ton père
			break;
		}
	}
	
	numChild++;	
	/*if(numChild++ == 0)
	Set_state*/
	/*mutex*/
}

// Active un Link et le relie à un Child
bool Link::Activate_Link(LinkType& type, Link* child)
{
	this->type = type;	// Son nouveau type	(certaines conversions seront impossible dans le futur)

	if (this->state == LinkState::DEAD || this->state == LinkState::FREE)		// error brah, le link était pas libre ou DEAD
	{
		Set_State(child);				// Set le state selon le fait qu'il a un child ou non, ou si ya pas de parent
	}

	Bond_Link_To_Child(child);		// Assignation des pointeurs
	Set_UI();						// affichage

	return true;
}

void Link::Deactivate_Link()					// À DÉTERMINER LORS de la destruction
{
	this->pParent = NULL;
								// reset pointers
	for (int i = 0; i < 3; i++)	// reset pointers
		this->pChild[i] = NULL;	// reset pointers
	
	this->parentPos = Polarization::NUL;


	state = LinkState::DEAD;

	//if(type != LinkType::REGULAR)
		/*do stuff*/

	// Efface le Link
	Dsp_Link();
}




//UI
void Link::Dsp_Link()						// Affiche le Link
{
	UI_Dsp_Char(this->coord, this->sym, this->clr);
}

void Link::Clr_Link()						// Clear le Link
{
	UI_Dsp_Char(this->coord, TXT_CONST.SPACE);
}