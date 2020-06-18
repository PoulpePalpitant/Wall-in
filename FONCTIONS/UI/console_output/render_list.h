#pragma once

#include "../coord.h"
#include "../txtstyle.h"
#include "../../time/clock.h"

struct OutputData {

	Coord crd;		// position
	Colors clr;		// couleur
	char symbol;	// symbole ascii
	OutputData* nxt = NULL;	
};

struct RenderQueue {
	OutputData* first = NULL;	// Le premier �l�ment de la liste � afficher. Il sera le premier partie
	OutputData* last = NULL;	// Le premier �l�ment de la liste � afficher. Il sera le premier partie
	int size;			// Nombre d'�l�mentsde la liste � afficher
};

struct TimerQueue {
	/* ID de la liste */
	/* Timer!!! stuff*/
	CDTimer delay;	// Entre chaque output dans cette liste
	RenderQueue queue;
	TimerQueue* nxtQueue = NULL;
};


// combine : sym,et clr ensemble si �a te tente




class ConsoleRender
{
	static TimerQueue* first, *last;	// Listes contenants tout les output � faire sur une base de temps
	static RenderQueue mainQueue;		// Liste principale. Elle est vid� � chaque render. C'est ta responsabilit� de ne pas la overfill et caus� du lags avec "cout"
	static int leftToAdd;	// Ce truc va servir de compteur pour  d�terminer quelle queue utiliser pour ajouter des charact�res � render			


	bool Is_Queue_Empty(const RenderQueue& queue);
	bool Is_Queue_Full(const RenderQueue& queue);
	void Add_New_Timer_Queue();		// Ajoute une nouvelle queue
	
	OutputData* Pop_From_Queue(RenderQueue& queue);		// Retire un OutputData d'une queue 
	void Push_To_Queue(Coord crd, char sym, Colors clr);// Ajoute un OutputData a la fin de la queue

	void Add_To_Main_Queue(Coord crd, char sym, Colors clr);
	void Add_To_Timer_Queue(Coord crd, char sym, Colors clr, float);
	void Render_Main_Queue();				// Affiche tout les �l�ments pr�sent dans la main queue
	void Render_Timer_Queue();				// Affiche tout les �l�ment qui doivent l'�tre selon les timer


public:
	void Add_To_Render_List(Coord crd, char sym, Colors clr = WHITE, float speed = 0);
	void Render();	// Output tout les charact�res dans la console, selon les listes, et les timers de ces listes
	
	
	
	void Set_How_Much_To_Add(int amount) { leftToAdd = amount; }	// Tant que leftToAdd n'atteint pas 0. Tout les prochains charact�res qui seront ajout�s seont ajout� dans la m�me timer list!!!
	// Je dois n�anmoins conna�tre le montant d'avance



};

