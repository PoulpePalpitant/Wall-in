#pragma once

#include "../coord.h"
#include "../txtstyle.h"
#include "../../time/countdown_clock.h"

struct OutputData {

	Coord crd;		// position
	Colors clr;		// couleur
	char symbol;	// symbole ascii
	OutputData* nxt = NULL;	
};

struct RenderQueue {
	OutputData* first = NULL;	// Le premier �l�ment de la liste � afficher. Il sera le premier partie
	OutputData* last = NULL;	// Le dernier �l�ment de la liste � afficher. Il sera le dernier partie
	int size = 0;			// Nombre d'�l�mentsde la liste � afficher
};

struct AnimationQueue {
	/* ID de la liste */
	/* Timer!!! stuff*/
	CDTimer timer;	// Entre chaque output dans cette liste
	RenderQueue queue;
	AnimationQueue* nxtQueue = NULL;
};


// combine : sym,et clr ensemble si �a te tente


class ConsoleRender
{
	static AnimationQueue* first, *last;// Listes contenants tout les output � faire sur une base de temps
	static AnimationQueue* sameQueue;	// Permet d'ajouter tout les prochains �l�ments dans la m�me queue
	static RenderQueue mainQueue;		// Liste principale. Elle est vid� � chaque render. C'est ta responsabilit� de ne pas la overfill et caus� du lags avec "cout"
	static bool addToSameQueue;			// D�termine quelle queue utiliser pour ajouter des charact�res � render			

	static bool Is_Empty(const RenderQueue& queue);
	static bool Is_Queue_Full(const RenderQueue& queue);
	
	static void Pop_From_Queue(RenderQueue& queue, OutputData& data);		// Retire un OutputData d'une queue 

	static void Add_Animation_Queue(float speed);		// Ajoute une nouvelle queue
	static void Push_To_Queue(Coord crd, char sym, Colors clr, RenderQueue& queue);// Ajoute un OutputData a la fin de la queue
	static void Add_To_Main_Queue(Coord crd, char sym, Colors clr);
	static void Add_To_Animation_Queue(Coord crd, char sym, Colors clr, float);
	static void Render_Main_Queue();				// Affiche tout les �l�ments pr�sent dans la main queue
	static void Render_Animation_Queue();				// Affiche tout les �l�ment qui doivent l'�tre selon les timer


public:
	static void Add_String_To_Render_List(std::string text, Coord crd,  Colors clr = WHITE, float speed = 0);
	static void Add_Char_To_Render_List(Coord crd, char sym, Colors clr = WHITE, float speed = 0);	// Ajoute un charact�re � afficher pour le prochain render
	static void Stop_Queue();								// Stop l'ajout d'�l�ment dans la queue d'animation actuelle
	static void Render();	// Output tout les charact�res dans la console, selon les listes, et les timers de ces listes
};	

