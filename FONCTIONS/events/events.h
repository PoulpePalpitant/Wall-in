
#pragma once 

const int QUEUE_SIZE = 20;

/*
	Pour les events du jeu, j'ai d�cid� de limiter la complexit� au maximum afin de pouvoir finir le plus rapidement possible. Il y aurait beaucoup de mani�re d'int�grer un syst�me de gestion de message et j'ai du mal � trouver rapidement une 
	BONNE mani�re de faire � mon niveau de compr�hension. Je crois pas que ce projet est le bon pour tester �a, surtout consid�rant les besoins limit�s en mati�re d'event. Pour le futur, voici desw pistes, en plus des recherches que 
	ta mis dans tes favoris su chrome.

*/

enum EventType 
{ /* Blast Stuff*/
	BLAST_REACHED_BORDER

/* Clavier*/	
, PRESSED_ENTER /* Le joueur � pes� sur enter, pour faire un choix */
};


struct EventInfo {
	bool isActive = false;			// Quand l'event est actif, on le fait
	bool ignore = false;			// Permet d'ingore le listener si l'event n'est pas suppos� �tre r�p�t�
};


void Update_Events();		// Par ici qu'on va updater tout les events du niveau
void Upd_Global_Events();	// Update tout les autres qui sont pas dans des modules ind�pendants


// La liste de tout les messages D'EVENT


class MessageQueue			// Initialisation � un ring buffer
{
	static EventType queue[QUEUE_SIZE];	// La liste de tout les messages enregistr� pendant une frame
	static int head, tail;				// d�but, fin, it�rateur d'indice du array
	static int total;

	static void Unregister();
public:
	static void Register(EventType msg);	// Ajoute le message � la liste des message � traiter pour ce cycle
	static void Update();
};










/* FRAMEWORK ACTUEL POUR CHACUN DES EVENTS. BCP DE R�P�TITIONS DE CODE */


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

	// J'ai une liste de listener d'�v�nement au d�but d'une game. Ils sont tous pr�sents. Quand un event � lieux, on peut retirer le listener de la liste.
	// Si tu veux r�p�ter l'event dans le futur, ta juste � r�ajouter le l'ID de l'event dans la liste de listener, et d'update les conditions si n�cessaires!
	// Tu r�p�te la m�me affaire pour les events handler

//class Event {
//	EventInfo info;
//	void Listener();				// V�rification des conditions pour trigger l'event
//	void Event_();					// Ce que l'event fait
//	void Update_Conditions();		// Update Les conditions si l'event � eu lieu. 
//};
//
//class RingBuffer			// Initialisation � un ring buffer
//{
//	int queue[QUEUE_SIZE];
//	int head = 0, tail = 0, it;		// d�but, fin, it�rateur d'indice du array
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

