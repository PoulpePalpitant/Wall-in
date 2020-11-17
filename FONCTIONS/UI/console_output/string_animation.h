#pragma once

#include "../coord.h"
#include "../txtstyle.h"
#include "../../time/countdown_clock.h"
#include "../../time/movement_timer.h"
#include "../../events/global_events/clear_all_states.h"

/*
OPTIMISATION:
	Ultimement, l'animation queue devrait plutôt être convertit en 1 event qui gère des drawer queues! Ça règlerais le problème de framerate sur tout les affichages de string
*/

// Une data de base à afficher dans la console
struct CharData
{
	Coord crd = { 0,0 };		// position
	char symbol = 'B';		// symbole ascii
	Colors clr = WHITE;		// couleur
};


class StringQueue
{
	int nbChar = 0;
	int curr = 0;	// La position où on se trouve, le prochain char à afficher dnas la liste

	void Add(Coord XY, char sym, Colors clr);		// Ajoute un élément à draw
public:
	SpeedTimer* timer;	// Entre chaque output dans cette liste
	CharData* queue = NULL;			// La queue de la string à afficher
	StringQueue* nxt = NULL;			// La prochaine

	void Add_String(Coord XY, std::string, Colors clr, bool erase);
	int Get_Current() { return curr; }
	bool Is_Empty() { return nbChar == 0; }
	CharData Pop_First();

	StringQueue(int stringLength, int speed = 100)
	{
		queue = new CharData[stringLength];
		timer = new SpeedTimer(false);				// dumb fix pour éviter d'utiliser le constructor qui assigne un id
		timer->Start_Timer(speed, stringLength);	// Le timer va reset pour le nb de char présent dans la string
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
	StringQueue* first = NULL, * last = NULL;	// Listes contenants tout les output à faire sur une base de temps
	StringQueue* iterator = NULL;		// itérateur

};

//extern StringAnimationList strList;	// la liste de tous les animations de string
