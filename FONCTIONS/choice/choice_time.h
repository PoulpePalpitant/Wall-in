#pragma once

#include "../UI/txtstyle.h"
#include "../queue/queue.h"
#include "../grid/AllGrids.h"


/* 
	Choice Time: Fait appara�tre des choix sur le terrain de jeu. Si le joueur se d�place sur le tit point en bas d'un choix, celui-ci sera s�lectionn�. Si le joueur p�se sur enter, le choix sera fait

*/

 int const MAX_CHOICES = 20;	// nb de choix max

struct Choice
{
	GrdCoord crd;		// position dans le grid
	std::string name;	// le nom
	std::string subname;// un tit espace de txt suppl�mentaire
	//unsigned int id;	// l'id
};

class ChoiceTime
{
	static bool enterDrawn;
	static Choice choiceList[MAX_CHOICES];	// liste des choix
	static bool choiceTime;				// it is
	static unsigned short numChoices;	// nb de choix actuel
	static Choice selected;		// Le choix actuellement s�lectionn� par le joueur
	static std::string choiceMade;	// Le choix fait lors du choice time pr�c�dant
	//static unsigned int id;		// total d'id cr�� 


	static void Start_Choice_Time();	// Signale au joueur qu'il doit faire un choix
	static void Stop_Choice_Time();	

	static void Clear_List();

	/* Emp�che de shooter quand c'est choice time  !!*/

	static int Find_Selected();		// Retrouve le choix s�lectionn� par le joueur dans la liste
	
	
	//static void Remove_Choice(std::string name);
	//static void Highlight_Selected();	// Change la couleur du txt du choix s�lectionn�
	//static bool Is_Player_On_Choice();	// Si le player est sur une case du grid contenant un choix

	// UI

	static void Draw_Choice(int index, Colors clr = BRIGHT_WHITE);
	static void Erase_Choice(int index);
	static void Draw_Dot(int index);
	static void Draw_Names(int index, Colors clr = BRIGHT_WHITE);
	static void Draw_Press_Enter();
	static void Erase_Press_Enter();

public:
	static bool Select_If_Player_On();			// Player fait une s�lection, en �tant sur un choix
	static bool Unselect_If_Player_Off();		// Retire la s�lection. Le player n'est plus sur un choix
	static bool Add_Choice(std::string name, std::string subname, GrdCoord crd);
	static bool Is_Choice_Time() { return choiceTime; }	// it is choice time
	static bool Apply_Choice();		// Le joueur fait son choix. Retourn le nom du choix. Met �galement fin au choice time
	static std::string Get_Choice_Made() { return choiceMade; }	// le choix fait par le joueur		

};