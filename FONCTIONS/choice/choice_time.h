#pragma once

#include "../UI/txtstyle.h"
#include "../queue/queue.h"
#include "../grid/AllGrids.h"
#include "../events/global_events/clear_all_states.h"

/* 
POST-MORTEM
	
	"Lors du processus de développement, il faut faire des sacrifices et abandonner des idées intéressantes qui ne sont pas un bon match avec le produit qu'on est en train de créer.
	Ceci en était une que je trouvais quand même cool"


	Choice Time: Fait apparaître des choix sur le terrain de jeu.
	Si le joueur se déplace sur le tit point en bas d'un choix, celui-ci sera sélectionné. 
	Si le joueur pèse sur enter, le choix sera fait.
*/

 int const MAX_CHOICES = 20;	// nb de choix max

struct Choice
{
	GrdCoord crd;		// position dans le grid
	std::string name;	// le nom
	std::string subname;// un tit espace de txt supplémentaire
	//unsigned int id;	// l'id
};

class ChoiceTime
{
	static bool enterDrawn;
	static Choice choiceList[MAX_CHOICES];	// liste des choix
	static bool choiceTime;				// it is
	static unsigned short numChoices;	// nb de choix actuel
	static Choice selected;		// Le choix actuellement sélectionné par le joueur
	static std::string choiceMade;	// Le choix fait lors du choice time précédant
	//static unsigned int id;		// total d'id créé 


	static void Start_Choice_Time();	// Signale au joueur qu'il doit faire un choix

	static void Clear_List();

	/* Empêche de shooter quand c'est choice time  !!*/
	static int Find_Selected();		// Retrouve le choix sélectionné par le joueur dans la liste
	
	// UI
	static void Draw_Choice(int index, Colors clr = BRIGHT_WHITE);
	static void Erase_Choice(int index);
	static void Draw_Dot(int index);
	static void Draw_Names(int index, Colors clr = BRIGHT_WHITE);
	static void Draw_Press_Enter();
	static void Draw_Alternate_Title(bool erase = false);
	static void Erase_Press_Enter();

public:
	static void Stop_Choice_Time();		// Pour arrêter le choice time
	static bool Select_If_Player_On();			// Player fait une sélection, en étant sur un choix
	static bool Unselect_If_Player_Off();		// Retire la sélection. Le player n'est plus sur un choix
	static bool Add_Choice(std::string name, std::string subname, GrdCoord crd);
	static bool Is_Choice_Time() { return choiceTime; }	// it is choice time
	static bool Apply_Choice();		// Le joueur fait son choix. Retourn le nom du choix. Met également fin au choice time
	static std::string Get_Choice_Made() { return choiceMade; }	// le choix fait par le joueur		

};