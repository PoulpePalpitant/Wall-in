
#pragma once 

const int QUEUE_SIZE = 20;

/*
	Pour les events du jeu, j'ai décidé de limiter la complexité au maximum afin de pouvoir finir le plus rapidement possible. Il y aurait beaucoup de manière d'intégrer un système de gestion de message et j'ai du mal à trouver rapidement une 
	BONNE manière de faire à mon niveau de compréhension. Je crois pas que ce projet est le bon pour tester ça, surtout considérant les besoins limités en matière d'event. Pour le futur, voici desw pistes, en plus des recherches que 
	ta mis dans tes favoris su chrome.

*/

enum EventType 
{ /* Blast Stuff*/
	BLAST_REACHED_BORDER

/* Clavier*/	
, PRESSED_ENTER /* Le joueur à pesé sur enter, pour faire un choix */
};


struct EventInfo {
	bool isActive = false;			// Quand l'event est actif, on le fait
	bool ignore = false;			// Permet d'ingore le listener si l'event n'est pas supposé être répété
};


void Update_Events();		// Par ici qu'on va updater tout les events du niveau
void Upd_Global_Events();	// Update tout les autres qui sont pas dans des modules indépendants


// La liste de tout les messages D'EVENT


class MessageQueue			// Initialisation à un ring buffer
{
	static EventType queue[QUEUE_SIZE];	// La liste de tout les messages enregistré pendant une frame
	static int head, tail;				// début, fin, itérateur d'indice du array
	static int total;

	static void Unregister();
public:
	static void Register(EventType msg);	// Ajoute le message à la liste des message à traiter pour ce cycle
	static void Update();
};










/* FRAMEWORK ACTUEL POUR CHACUN DES EVENTS. BCP DE RÉPÉTITIONS DE CODE */


//void Ev_Hello()
//{
//	static EventInfo info;	// info.Generate_ID;
//
//	if (info.ignore)
//		return;
//
//	if (info.isActive)
//	{
//		return;		// Do stuff
//	}
//	else
//	{
//
//		//	Check les conditions
//
//	}
//
//}












/* STUFF THAT I TRIED BRIEFLY*/

	// J'ai une liste de listener d'évènement au début d'une game. Ils sont tous présents. Quand un event à lieux, on peut retirer le listener de la liste.
	// Si tu veux répéter l'event dans le futur, ta juste à réajouter le l'ID de l'event dans la liste de listener, et d'update les conditions si nécessaires!
	// Tu répète la même affaire pour les events handler

//class Event {
//	EventInfo info;
//	void Listener();				// Vérification des conditions pour trigger l'event
//	void Event_();					// Ce que l'event fait
//	void Update_Conditions();		// Update Les conditions si l'event à eu lieu. 
//};
//
//class RingBuffer			// Initialisation à un ring buffer
//{
//	int queue[QUEUE_SIZE];
//	int head = 0, tail = 0, it;		// début, fin, itérateur d'indice du array
//
//	void Add(int data);
//	void Remove();
//};
//
//class EventManager
//{
//	RingBuffer listener;
//	RingBuffer handler;
//	
//	void Update_Listeners();	// NO!
//	void Update_Handlers();
//	void Update_Events();
//};
//
//EventManager Audio;
//EventManager Txt_Bubbles;
//
//

