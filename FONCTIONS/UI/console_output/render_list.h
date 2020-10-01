#pragma once

#include "../coord.h"
#include "../txtstyle.h"
#include "../../time/countdown_clock.h"
#include "../../time/movement_timer.h"
#include "../../events/global_events/clear_all_states.h"

extern int gPlyerTimeoutDelay ;

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
	SpeedTimer* timer;	// Entre chaque output dans cette liste
	RenderQueue queue;
	AnimationQueue* nxtQueue = NULL;
	bool isLinear;		// Linear veut dire que tout les éléments seront affichés l'un après l'autre avec du élai entre chaque, à l'opposé de tout en même temps

	~AnimationQueue()
	{
		delete timer;
	}
};

/*
OPTIMISATION:
	Ultimement, l'animation queue devrait plutôt être convertit en 1 event qui gère des drawer queues! Ça règlerais le problème de framerate sur tout les affichages de string
*/

class ConsoleRender
{
	friend void Clear_All_Renders();
	static AnimationQueue* first, *last;// Listes contenants tout les output à faire sur une base de temps
	static AnimationQueue* animationQueue;	// Permet d'ajouter tout les prochains éléments dans la même queue. Ils seront affichés 1 après l'autre avec un certain délai
	static RenderQueue mainQueue;		// Liste principale. Elle est vidé à chaque render. C'est ta responsabilité de ne pas la overfill et causé du lags avec "cout"
	static bool addToNewQueue;			// Détermine quelle queue utiliser pour ajouter des charactères à render			

	static bool Is_Empty(const RenderQueue& queue);
	static void Pop_From_Queue(RenderQueue& queue, OutputData& data);		// Retire un OutputData d'une queue 
	static void Push_To_Queue(Coord crd, char sym, Colors clr, RenderQueue& queue);// Ajoute un OutputData a la fin de la queue
	static void Render_Main_Queue();				// Affiche tout les éléments présent dans la main queue
	static void Render_Animation_Queue();				// Affiche tout les élément qui doivent l'être selon les timer
	static void Empty_All(); // dangerous stuff here
public:
	static void Set_Animation_Delay();					// Ceci est un fix bâtard et rapide pour conserver des méthodes désuettes. Ça ralentie les animations legacy en mode release.
	static void Add_String(std::string text, Coord crd,  Colors clr = WHITE, float speed = 0, bool erase = false);
	static void Add_Char(Coord crd, unsigned char sym, Colors clr = WHITE);	// Ajoute un charactère à afficher pour le prochain render
	static void Create_Animation_Queue(float speed, bool linear = true);			// Créer une nouvelle Queue, tout les char suivant seront ajouté à celle-ci
	static void Stop_Queue();											// Stop l'ajout d'élément dans la queue d'animation actuelle
	static void Render();	// Output tout les charactères dans la console, selon les listes, et les timers de ces listes
};	
