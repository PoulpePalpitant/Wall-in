
#include "../grid/grid.h"
#include "../UI/console_output/render_list.h"
#include "../structure_manager/structure_manager.h"	// Pour gérer relation entre Link et walls
#include "../events/msg_dispatcher.h"
#include "../player/player.h"
#include "link.h"


LinkMeta Link::meta = {};	

void Link::Set_LinkXY(int col, int row)
{
	this->coord.x = START_X + DELTA_X * col;			
	this->coord.y = START_Y + DELTA_Y * row;
}

void Link::Set_State(Wall* child )	
{
	if (!this->pParent)			// Pas de Parent? T'es le premier d'une ligné!
		state = LinkState::ROOT;
	else
		if (child == NULL)
			state = LinkState::FREE;	// Pas de child? T'es FREE!
		else
			state = LinkState::BOUND;		// Ah, tu es lié finalement
}

void Link::Set_UI()						
{
	switch (this->modifier)
	{
	case Modifier::REGULAR:
		clr = WHITE;	

		if (state == LinkState::BOUND)
			sym = (char)LinkSym::PARENT;
		if (state == LinkState::FREE)
		{
			sym = (char)LinkSym::CHILD;	
			clr = GRAY;
		}
		break;

	case BUFFER:
		sym = (char)LinkSym::PARENT;

		clr = LIGHT_YELLOW;
		break;

	case Modifier::BLOCKER:
		sym = (char)LinkSym::PARENT;
		clr = LIGHT_RED;
		break;

	case Modifier::CORRUPTER:
		sym = (char)LinkSym::PARENT;
		clr = LIGHT_PURPLE;
		break;

	case Modifier::FORCEFIELD:
		sym = 176;
		clr = Colors::TEST;
		break;

	case Modifier::ENERGIZER:
		clr = LIGHT_PURPLE;
		break;
	}

	if (state == LinkState::ROOT && modifier != Modifier::FORCEFIELD)
		sym = (char)LinkSym::ROOT;
}

bool Link::Set_First_Modifier(Modifier mod)		
{
	if (Get_State() != LinkState::FREE && modifier == REGULAR)	// shame.		dont' edit, it makes sense
	{
		modifier = mod;
		return true;
	}
	else
		return false;
	
	
}
void Link::Convert_Modifier(Modifier mod,bool overRideDumbRuleOfSpaghetti)	// I guess qu'on convertit pas en regular: Je fais ça uniquement pour ne pas convertir un forcefield en regular............
{
	if (mod != Modifier::REGULAR || overRideDumbRuleOfSpaghetti == true)		// J'ai overide cette façon miteuse de faire. Fuck this shit
	{
		modifier = mod;
		Set_UI();	

		if (!Are_Equal(P1.Get_XY(), coord))
			Dsp_Link();	
	}
}

void Link::Modifier_Inheritance(Modifier& mod)
{
	if(pParent != NULL)
		if (pParent->Get_Parent_Modifier() == CORRUPTER)
			mod = CORRUPTER;
}

bool Link::Activate_Link(Modifier& mod, Wall* child)
{
	// INTÉRACTIONS
	if(modifier != Modifier::FORCEFIELD)
		if (modifier == REGULAR)
			Modifier_Inheritance(mod);

	if (this->state == LinkState::DEAD || this->state == LinkState::FREE || modifier == Modifier::FORCEFIELD)		// error brah, le link était pas libre ou DEAD
		Set_State(child);				

	StructureManager::Bond_Link_To_Child(this, child);	
	Set_First_Modifier(mod);		// Si le link est free, il ne peut avoir autre modifier que le REGULAR. Il pourra être convertit par un blast plus tard . Why?, parce que je veut qu'un buffer puisse
									// transformer le child d'un corrupter? Et que les child des corrupter soit toujours Regular pour que ce soit claire que le joueur peut uniquement bouger sur des tits points
	Set_UI();						

	meta.Add();
	MsgQueue::Register(LINK_ACTIVATED);
	return true;
}

bool Link::Activate_Lonely_Link(Modifier mod)
{
	bool dead = false;
	if (state == LinkState::DEAD)
		dead = true;
	
	modifier = mod;
	
	if (mod == Modifier::FORCEFIELD)
		state = LinkState::ROOT;	
	else
		Set_State(NULL);				

	Set_UI();

	if (dead)
	{
		meta.Add();
		MsgQueue::Register(LINK_ACTIVATED);
	}

	Dsp_Link();
	return true;
}

void Link::Deactivate_Link()			
{
	int children = this->numChild;
	this->pParent = NULL;
										 
	for (int i = 0; i < numChild; i++)			
	{
		this->pWalls[i] = NULL;	
		children--;
	}

	numChild = children;	
	state = LinkState::DEAD;
	modifier = REGULAR;	// faut bien reset ça

	meta.Remove();
	
	if(!ListsOfChainToModify::annihilating)
		MsgQueue::Register(LINK_DEACTIVATED); 
}

void Link::Unbound_All_Child()	
{
	numChild = 0;
	
	for (size_t i = 0; i < 4; i++)
		pWalls[i] = NULL;
}


bool Link::Unbound_Wall_Child(Wall* child)
{
	if (this->state == LinkState::DEAD)		
		return false;

	for (size_t i = 0; i < this->numChild; i++)
	{
		if (this->pWalls[i] == child)				
		{		
			for (size_t j = i; j < numChild; j++)						
			{
				if (j + 1 < numChild)
					this->pWalls[j] = this->pWalls[j + 1];
				else
					this->pWalls[j] = NULL;	// Le dernier sera NULL car on viens de le destroy hha. pOW. Pachinka Haha... SzwIINNg.. PAF! Hehe. SPatatra!!! Ohoho' FLshaq, HaHa.
			}
			
			numChild--;	
			break;
		}
	}

	if (!numChild)
	{ 
		if (state == LinkState::BOUND)
		{
			state = LinkState::FREE;
			this->Set_UI();		
			this->Dsp_Link();	
		}
		else
			if (state == LinkState::ROOT && modifier == REGULAR)		// Si le root n'a plus de Child, il mourre, SAUF SI C'EST UN MOTHERFUCKER MODIFIER
			{
				this->Deactivate_Link();				
				Er_Link();		
			}
		return true;		
	}

	return false;
}

void Link::Change_Color(Colors clr)
{
	this->clr = clr;
	Dsp_Link();
}

void Link::Dsp_Link()						
{
	ConsoleRender::Add_Char(this->coord, this->sym, this->clr);
}

void Link::Er_Link( )						
{
	if (!Are_Equal(P1.Get_XY(), Get_XY()))
		ConsoleRender::Add_Char(this->coord, TXT_CONST.SPACE, WHITE);	
	else
		return;
}