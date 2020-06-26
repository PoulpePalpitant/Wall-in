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
	OutputData* first = NULL;	// Le premier élément de la liste à afficher. Il sera le premier partie
	OutputData* last = NULL;	// Le dernier élément de la liste à afficher. Il sera le dernier partie
	int size = 0;			// Nombre d'élémentsde la liste à afficher
};

struct AnimationQueue {
	/* ID de la liste */
	/* Timer!!! stuff*/
	CDTimer timer;	// Entre chaque output dans cette liste
	RenderQueue queue;
	AnimationQueue* nxtQueue = NULL;
	bool isLinear;		// Linear veut dire que tout les éléments seront affichés l'un après l'autre avec du élai entre chaque, à l'opposé de tout en même temps
};


// combine : sym,et clr ensemble si ça te tente


class ConsoleRender
{
	static AnimationQueue* first, *last;// Listes contenants tout les output à faire sur une base de temps
	static AnimationQueue* animationQueue;	// Permet d'ajouter tout les prochains éléments dans la même queue. Ils seront affichés 1 après l'autre avec un certain délai
	static RenderQueue mainQueue;		// Liste principale. Elle est vidé à chaque render. C'est ta responsabilité de ne pas la overfill et causé du lags avec "cout"
	static bool addToNewQueue;			// Détermine quelle queue utiliser pour ajouter des charactères à render			

	static bool Is_Empty(const RenderQueue& queue);
	//static bool Is_Queue_Full(const RenderQueue& queue);
	
	static void Pop_From_Queue(RenderQueue& queue, OutputData& data);		// Retire un OutputData d'une queue 

	static void Push_To_Queue(Coord crd, char sym, Colors clr, RenderQueue& queue);// Ajoute un OutputData a la fin de la queue
	static void Render_Main_Queue();				// Affiche tout les éléments présent dans la main queue
	static void Render_Animation_Queue();				// Affiche tout les élément qui doivent l'être selon les timer
	//static void Add_To_Main_Queue(Coord crd, char sym, Colors clr);
	//static void Add_To_Animation_Queue(Coord crd, char sym, Colors clr);


public:
	static void Add_String_To_Render_List(std::string text, Coord crd,  Colors clr = WHITE, float speed = 0);
	static void Add_Char_To_Render_List(Coord crd, unsigned char sym, Colors clr = WHITE);	// Ajoute un charactère à afficher pour le prochain render
	static void Create_Queue(float speed, bool linear = true);			// Créer une nouvelle Queue, tout les char suivant seront ajouté à celle-ci
	static void Stop_Queue();											// Stop l'ajout d'élément dans la queue d'animation actuelle
	static void Render();	// Output tout les charactères dans la console, selon les listes, et les timers de ces listes
};	
