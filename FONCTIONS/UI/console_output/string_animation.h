#pragma once

#include "../coord.h"
#include "../txtstyle.h"
#include "../../time/countdown_clock.h"
#include "../../time/movement_timer.h"
#include "../../events/global_events/clear_all_states.h"

/*
OPTIMISATION:
	Ultimement, l'animation queue devrait plut�t �tre convertit en 1 event qui g�re des drawer queues! �a r�glerais le probl�me de framerate sur tout les affichages de string
*/

// Une data de base � afficher dans la console
struct CharData
{
	Coord crd = { 0,0 };		// position
	char symbol = 'B';		// symbole ascii
	Colors clr = WHITE;		// couleur
};


class StringQueue
{
	int nbChar = 0;
	int curr = 0;	// La position o� on se trouve, le prochain char � afficher dnas la liste

	void Add(Coord XY, char sym, Colors clr);		// Ajoute un �l�ment � draw
public:
	SpeedTimer* timer;	// Entre chaque output dans cette liste
	CharData* queue = NULL;			// La queue de la string � afficher
	StringQueue* nxt = NULL;			// La prochaine

	void Add_String(Coord XY, std::string, Colors clr, bool erase);
	int Get_Current() { return curr; }
	bool Is_Empty() { return nbChar == 0; }
	CharData Pop_First();

	StringQueue(int stringLength, int speed = 100)
	{
		queue = new CharData[stringLength];
		timer = new SpeedTimer(false);				// dumb fix pour �viter d'utiliser le constructor qui assigne un id
		timer->Start_Timer(speed, stringLength);	// Le timer va reset pour le nb de char pr�sent dans la string
	}

	~StringQueue()
	{
		delete[] queue;
		delete timer;
	}

};

class StringAnimationList
{
	friend void Clear_All_States(bool eraseMap);	// Gros reset button

	void Empty_All();	// Efface tout les queues
public:
	StringQueue* first = NULL, * last = NULL;	// Listes contenants tout les output � faire sur une base de temps
	StringQueue* iterator = NULL;		// it�rateur

};

//extern StringAnimationList strList;	// la liste de tous les animations de string
