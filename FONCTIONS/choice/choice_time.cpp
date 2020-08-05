

#include "choice_time.h"
#include "../UI/console_output/render_list.h"
#include "../console/sweet_cmd_console.h"
#include "../events/events.h"
#include "../player/player.h"
#include "../events/msg_dispatcher.h"
#include "../inputs/action_input.h"
#include "../player/player.h"

// Choice time static stuff
Choice ChoiceTime::choiceList[MAX_CHOICES];	// liste des choix
bool ChoiceTime::choiceTime = false;
unsigned short ChoiceTime::numChoices;	// nb de choix actuel
Choice ChoiceTime::selected;		// Le choix actuellement sélectionné par le joueur
std::string ChoiceTime::choiceMade;	// Le choix fait lors du choice time précédant
 bool ChoiceTime::enterDrawn = false;

// Pure static stuff
static Coord XY;	// pour draw
static GrdCoord crd;
static std::string enter = "(Press Enter To Select)";


// AFFICHAGE
void ChoiceTime::Draw_Choice(int index, Colors clr)	// Affiche le choix
{
	Draw_Dot(index);
	Draw_Names(index, clr);
}

 void ChoiceTime::Draw_Dot(int index)
 {
	 crd = choiceList[index].crd;
	 XY = linkGrid->link[crd.c][crd.r].Get_XY();	// XY
	 ConsoleRender::Add_Char(XY, TXT_CONST.DOT, BRIGHT_WHITE);	// affiche le tit dot
 }
 void ChoiceTime::Draw_Names(int index, Colors clr)
 {
	 crd = choiceList[index].crd;
	 XY = linkGrid->link[crd.c][crd.r].Get_XY();	// XY

	 // Affiche le nom au dessus du point sur le grid
	 XY.y -= 4;	// quatres cases plus haut
	 XY.x = XY.x - ((int)choiceList[index].name.size() / 2);	// nom centré
	 ConsoleRender::Add_String(choiceList[index].name, XY, clr, 25); // affiche le nomd

	 if (choiceList[index].subname != TXT_CONST.EMPTY)
	 {
		 XY = linkGrid->link[crd.c][crd.r].Get_XY();	// XY
		 XY.y -= 2;	// 2 cases plus bas
		 XY.x = XY.x - ((int)choiceList[index].subname.size() / 2);	// nom centré
		 ConsoleRender::Add_String(choiceList[index].subname, XY, GRAY, 25); // affiche le subname
	 }
 }
 
 void ChoiceTime::Erase_Choice(int index)	// Efface un choix
 {
	 crd = choiceList[index].crd; 
	 XY = linkGrid->link[crd.c][crd.r].Get_XY();	// XY
	 
	 if (!Are_Equal(crd, P1.Get_Grd_Coord())) 
		 ConsoleRender::Add_Char(XY, TXT_CONST.SPACE);	// affiche le tit dot

	 // efface
	 XY.y -= 4;	// quatres cases plus haut
	 XY.x = XY.x - (int)choiceList[index].name.size() / 2;	// nom centré
	 ConsoleRender::Add_String(choiceList[index].name, XY, WHITE, 50, true); // affiche le nom
 
	 // efface
	 if (choiceList[index].subname != TXT_CONST.EMPTY) 
	 {
		 XY = linkGrid->link[crd.c][crd.r].Get_XY();	// XY
		 XY.y -= 2;	// 2 cases plus bas
		 XY.x = XY.x - (int)choiceList[index].subname.size() / 2;	// nom centré
		 ConsoleRender::Add_String(choiceList[index].subname, XY, WHITE, 50, true); // affiche le subname
	 }
 }

 void ChoiceTime::Draw_Press_Enter()
 {
	 XY.x = Find_Ctr_X((int)enter.size());
	 XY.y = gConHeight - 15;
	 ConsoleRender::Add_String(enter, XY, GRAY, 90); // affiche ce titre
	 enterDrawn = true;
 }
 void ChoiceTime::Erase_Press_Enter()
 {
	 XY.x = Find_Ctr_X((int)enter.size());
	 XY.y = gConHeight - 15;
	 ConsoleRender::Add_String(enter, XY, WHITE, 90, true); // Efface ce titre
	 enterDrawn = false;
 }




int ChoiceTime::Find_Selected()		// Retrouve le choix sélectionné par le joueur dans la liste
{
	for (int i = 0; i < numChoices; i++)
	{
		if (Are_Equal(choiceList[i].crd, selected.crd))	// found the choice
			return i;
	}

	throw "dafuck is going on here";
}

bool ChoiceTime::Select_If_Player_On()			// Player fait une sélection 
{
	crd = P1.Get_Grd_Coord();

	for (int i = 0; i < numChoices; i++)
	{
		if (Are_Equal(choiceList[i].crd, crd))	// found the choice
		{
			if (!enterDrawn)
				Draw_Press_Enter();				// Avertit le joueur, sur comment y peut sélect

			selected = choiceList[i];
			Draw_Names(i, LIGHT_YELLOW);	// HighLight en jaune
			return true;
		}
	}

	if(enterDrawn)
		Erase_Press_Enter();	

	return false;

}

bool ChoiceTime::Unselect_If_Player_Off()		// Retire la sélection. Le player n'est plus sur un choix
{
	if (selected.name != TXT_CONST.EMPTY)	// si ya un choix de sélectionné
	{
		crd = P1.Get_Grd_Coord();

		if (!Are_Equal(selected.crd, crd))	// found the choice
		{
			int index = Find_Selected();
			Draw_Choice(index);				// Retire l'highlight de couleur sur le nom. Réaffiche le tit point
			selected = {};	// pu de sélection
			return true;
		}
	}
	
	return false;
}


void ChoiceTime::Stop_Choice_Time()
{
	Clear_List();
	selected = {};
	choiceTime = false;
}

void ChoiceTime::Start_Choice_Time()	// Signale au joueur qu'il doit faire un choix
{
	choiceTime = true;
	choiceMade = TXT_CONST.EMPTY;	// release le choix précédant
}


bool ChoiceTime::Apply_Choice()		// Le joueur fait son choix. Retourn le nom du choix. Met également fin au choice time
{
	
	if (selected.name != TXT_CONST.EMPTY)
	{
		choiceMade = selected.name;
		Stop_Choice_Time();	// we stahp this
		return true;
	}
	else
		return false;
}


// GESTION DE LISTE

bool ChoiceTime::Add_Choice(std::string name, std::string subname, GrdCoord crd)
{
	if (!Is_Choice_Time())
		Start_Choice_Time();

	
	if (numChoices < MAX_CHOICES)
	{
		choiceList[numChoices].name = name;
		choiceList[numChoices].subname = subname;
		choiceList[numChoices].crd = crd;

		// highlight le choix si le player se trouve dessus?

		Draw_Choice(numChoices);		// affiche le choix

		numChoices++;

		return true;
	}
	else
		return false;
}

void ChoiceTime::Clear_List()	// pu yen
{
	for (int i = 0; i < MAX_CHOICES; i++)
	{
		// ERASE
		if (choiceList[i].name != TXT_CONST.EMPTY)
		{
			Erase_Choice(i);		// efface tout les choix
			choiceList[i] = {};
			numChoices--;
		}
	}

	Erase_Press_Enter();
}


