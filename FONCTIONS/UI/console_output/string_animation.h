#pragma once

#include "../coord.h"
#include "../txtstyle.h"
#include "../../time/countdown_clock.h"
#include "../../time/movement_timer.h"
#include "../../events/global_events/clear_all_states.h"


// Une donnée de base à afficher dans la console
struct CharData
{
	Coord crd = { 0,0 };	
	char symbol = 'B';		
	Colors clr = WHITE;		
};


class StringQueue
{
	int nbChar = 0;
	int curr = 0;		

	void Add(Coord XY, char sym, Colors clr);		
public:
	SpeedTimer* timer;				
	CharData* queue = NULL;			
	StringQueue* nxt = NULL;		

	void Add_String(Coord XY, std::string, Colors clr, bool erase);
	int Get_Current() { return curr; }
	bool Is_Empty() { return nbChar == 0; }
	CharData Pop_First();

	StringQueue(int stringLength, int speed = 100)
	{
		queue = new CharData[stringLength];
		timer = new SpeedTimer(false);				// dumb fix pour éviter d'utiliser le constructor qui assigne un id
		timer->Start_Timer(speed, stringLength);	
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
