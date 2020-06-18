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
	OutputData* first = NULL;	// Le premier élément de la liste à afficher. Il sera le premier partie
	OutputData* last = NULL;	// Le premier élément de la liste à afficher. Il sera le premier partie
	int size;			// Nombre d'élémentsde la liste à afficher
};

struct TimerQueue {
	/* ID de la liste */
	/* Timer!!! stuff*/
	CDTimer delay;	// Entre chaque output dans cette liste
	RenderQueue queue;
	TimerQueue* nxtQueue = NULL;
};


// combine : sym,et clr ensemble si ça te tente




class ConsoleRender
{
	static TimerQueue* first, *last;	// Listes contenants tout les output à faire sur une base de temps
	static RenderQueue mainQueue;		// Liste principale. Elle est vidé à chaque render. C'est ta responsabilité de ne pas la overfill et causé du lags avec "cout"
	static int leftToAdd;	// Ce truc va servir de compteur pour  déterminer quelle queue utiliser pour ajouter des charactères à render			


	bool Is_Queue_Empty(const RenderQueue& queue);
	bool Is_Queue_Full(const RenderQueue& queue);
	void Add_New_Timer_Queue();		// Ajoute une nouvelle queue
	
	OutputData* Pop_From_Queue(RenderQueue& queue);		// Retire un OutputData d'une queue 
	void Push_To_Queue(Coord crd, char sym, Colors clr);// Ajoute un OutputData a la fin de la queue

	void Add_To_Main_Queue(Coord crd, char sym, Colors clr);
	void Add_To_Timer_Queue(Coord crd, char sym, Colors clr, float);
	void Render_Main_Queue();				// Affiche tout les éléments présent dans la main queue
	void Render_Timer_Queue();				// Affiche tout les élément qui doivent l'être selon les timer


public:
	void Add_To_Render_List(Coord crd, char sym, Colors clr = WHITE, float speed = 0);
	void Render();	// Output tout les charactères dans la console, selon les listes, et les timers de ces listes
	
	
	
	void Set_How_Much_To_Add(int amount) { leftToAdd = amount; }	// Tant que leftToAdd n'atteint pas 0. Tout les prochains charactères qui seront ajoutés seont ajouté dans la même timer list!!!
	// Je dois néanmoins connaître le montant d'avance



};

