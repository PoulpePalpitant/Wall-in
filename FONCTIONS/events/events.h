
#pragma once 

const int EV_QUEUE_SIZE = 20;


struct EventInfo {

	int id;	// l'Id de l'event
	bool isActive = false;			// Quand l'event est actif, on le fait
	bool ignore = false;			// Permet d'ingore le listener si l'event n'est pas suppos� �tre r�p�t�
};

class Event {
	friend class EventManager;
	EventInfo info;

	void Listener();				// V�rification des conditions pour trigger l'event
	// J'ai une liste de listener d'�v�nement au d�but d'une game. Ils sont tous pr�sents. Quand un event � lieux, on peut retirer le listener de la liste.
	// Si tu veux r�p�ter l'event dans le futur, ta juste � r�ajouter le l'ID de l'event dans la liste de listener, et d'update les conditions si n�cessaires!
	void Event_();					// Ce que l'event fait
	void Update_Conditions();		// Update Les conditions si l'event � eu lieu. 
};

void Events_Listener();			// V�rifie si un event est triggered
void Events_Handler();


class EventQueue
{
	friend class EventManager;

	int queue[EV_QUEUE_SIZE];
	int head = 0, tail = 0, it;		// d�but, fin, it�rateur d'indice du array

	void Add(Event* event );
	void Remove();
};

class EventManager
{
	EventQueue listener;
	EventQueue handler;
	
	void Update_Listeners();	// NO!
	void Update_Handlers();
};



