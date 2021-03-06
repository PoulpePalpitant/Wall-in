

#include "choice_time.h"
#include "../UI/console_output/render_list.h"
#include "../console/sweet_cmd_console.h"
#include "../events/events.h"
#include "../player/player.h"
#include "../events/msg_dispatcher.h"
#include "../inputs/action_input.h"
#include "../player/player.h"
#include "../grid/AllGrids.h"
#include "../structure_manager/structure_manager.h"
#include "../events/global_events/clear_all_states.h"

// Choice time static stuff
Choice ChoiceTime::choiceList[MAX_CHOICES];	// liste des choix
bool ChoiceTime::choiceTime = false;
unsigned short ChoiceTime::numChoices;	// nb de choix actuel
Choice ChoiceTime::selected;		// Le choix actuellement s�lectionn� par le joueur
std::string ChoiceTime::choiceMade;	// Le choix fait lors du choice time pr�c�dant
bool ChoiceTime::enterDrawn = false;

// Pure static stuff
static Coord XY;	// pour draw
static GrdCoord crd;
static std::string enter = "(Press Enter To Select)";
static std::string choice= "(Make Choice Before You Can Proceed)";


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
	 
	 if (!Are_Equal(P1.Get_XY(),XY))	// draw pas par dessu le joueur
		ConsoleRender::Add_Char(XY, TXT_CONST.DOT, BRIGHT_WHITE);	// affiche le tit dot
 }
 void ChoiceTime::Draw_Names(int index, Colors clr)
 {
	 crd = choiceList[index].crd;
	 XY = linkGrid->link[crd.c][crd.r].Get_XY();	// XY

	 // Affiche le nom au dessus du point sur le grid
	 XY.y -= 4;	// quatres cases plus haut
	 XY.x = XY.x - ((int)choiceList[index].name.size() / 2);	// nom centr�
	 ConsoleRender::Add_String(choiceList[index].name, XY, clr, TXT_SPD_FAST); // affiche le nomd

	 if (choiceList[index].subname != TXT_CONST.EMPTY)
	 {
		 XY = linkGrid->link[crd.c][crd.r].Get_XY();	// XY
		 XY.y -= 2;	// 2 cases plus bas
		 XY.x = XY.x - ((int)choiceList[index].subname.size() / 2);	// nom centr�

		 if(clr == LIGHT_YELLOW)	// Si le Texte est highlight�, la couleur est jaune
			ConsoleRender::Add_String(choiceList[index].subname, XY, WHITE); // affiche le subname
		 else
			 ConsoleRender::Add_String(choiceList[index].subname, XY, GRAY); // affiche le subname
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
	 XY.x = XY.x - (int)choiceList[index].name.size() / 2;	// nom centr�
	 ConsoleRender::Add_String(choiceList[index].name, XY, WHITE, TXT_SPD_ER, true); // affiche le nom
 
	 // efface
	 if (choiceList[index].subname != TXT_CONST.EMPTY) 
	 {
		 XY = linkGrid->link[crd.c][crd.r].Get_XY();	// XY
		 XY.y -= 2;	// 2 cases plus bas
		 XY.x = XY.x - (int)choiceList[index].subname.size() / 2;	// nom centr�
		 ConsoleRender::Add_String(choiceList[index].subname, XY, WHITE, TXT_SPD_ER, true); // affiche le subname
	 }
 }

 void ChoiceTime::Draw_Press_Enter()
 {
	 XY.x = Find_Ctr_Grid(enter);
	 XY.y = linkGrid->link[0][linkGrid->Get_Rows() - 1].Get_XY().y - 1;
	 ConsoleRender::Add_String(enter, XY, GRAY); // affiche ce titre
	 enterDrawn = true;
 }
 void ChoiceTime::Erase_Press_Enter()
 {
	 XY.x = Find_Ctr_Grid(enter);
	 //XY.x = Find_Ctr_X((int)enter.size() - 1);
	 XY.y = linkGrid->link[0][linkGrid->Get_Rows() - 1].Get_XY().y - 1;
	 ConsoleRender::Add_String(enter, XY, WHITE, 0, true); // Efface ce titre
	 enterDrawn = false;
 }

 // lazy copy paste
 void ChoiceTime::Draw_Alternate_Title(bool erase)
 {
	 XY.x = Find_Ctr_Grid(choice);
	 XY.y = linkGrid->link[0][linkGrid->Get_Rows() - 1].Get_XY().y - 2;
	 ConsoleRender::Add_String(choice, XY, GRAY, 0, erase); // Efface ce titre
 }



int ChoiceTime::Find_Selected()		// Retrouve le choix s�lectionn� par le joueur dans la liste
{
	for (int i = 0; i < numChoices; i++)
	{
		if (Are_Equal(choiceList[i].crd, selected.crd))	// found the choice
			return i;
	}

	throw "dafuck is going on here";
}

bool ChoiceTime::Select_If_Player_On()			// Player fait une s�lection 
{
	crd = P1.Get_Grd_Coord();

	for (int i = 0; i < numChoices; i++)
	{
		if (Are_Equal(choiceList[i].crd, crd))	// found the choice
		{
			if (!enterDrawn)
				Draw_Press_Enter();				// Avertit le joueur, sur comment y peut s�lect

			selected = choiceList[i];
			Draw_Names(i, LIGHT_YELLOW);	// HighLight en jaune
			return true;
		}
	}

	if(enterDrawn)
		Erase_Press_Enter();	

	return false;

}

bool ChoiceTime::Unselect_If_Player_Off()		// Retire la s�lection. Le player n'est plus sur un choix
{
	if (selected.name != TXT_CONST.EMPTY)	// si ya un choix de s�lectionn�
	{
		crd = P1.Get_Grd_Coord();

		if (!Are_Equal(selected.crd, crd))	// found the choice
		{
			int index = Find_Selected();
			Draw_Choice(index);				// Retire l'highlight de couleur sur le nom. R�affiche le tit point
			selected = {};	// pu de s�lection
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
	choiceMade = TXT_CONST.EMPTY;	// release le choix pr�c�dant
	blastP1.Clear_Blast();	// stop and clear
	ListsOfChainToModify::Annihilate_All_Links();	// Links
}


bool ChoiceTime::Apply_Choice()		// Le joueur fait son choix. Retourn le nom du choix. Met �galement fin au choice time
{
	if (selected.name != TXT_CONST.EMPTY)
	{
		choiceMade = selected.name;
		Stop_Choice_Time();	// we stahp this
		return true;
	}
	else
	{
		if (gProceedTime)
			Draw_Alternate_Title();
		return false;
	}
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

		Select_If_Player_On();	// si le joueur �tait d�j� sur un choix

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
	Draw_Alternate_Title(true);
}


