
#pragma once 

const int EV_QUEUE_SIZE = 20;


struct EventInfo {

	int id;	// l'Id de l'event
	bool isActive = false;			// Quand l'event est actif, on le fait
	bool ignore = false;			// Permet d'ingore le listener si l'event n'est pas supposé être répété
};

class Event {
	friend class EventManager;
	EventInfo info;

	void Listener();				// Vérification des conditions pour trigger l'event
	// J'ai une liste de listener d'évènement au début d'une game. Ils sont tous présents. Quand un event à lieux, on peut retirer le listener de la liste.
	// Si tu veux répéter l'event dans le futur, ta juste à réajouter le l'ID de l'event dans la liste de listener, et d'update les conditions si nécessaires!
	void Event_();					// Ce que l'event fait
	void Update_Conditions();		// Update Les conditions si l'event à eu lieu. 
};

void Events_Listener();			// Vérifie si un event est triggered
void Events_Handler();


class EventQueue
{
	friend class EventManager;

	int queue[EV_QUEUE_SIZE];
	int head = 0, tail = 0, it;		// début, fin, itérateur d'indice du array

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



