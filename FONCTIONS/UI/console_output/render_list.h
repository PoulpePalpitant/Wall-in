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
	OutputData* first = NULL;	// Le premier �l�ment de la liste � afficher. Il sera le premier partie
	OutputData* last = NULL;	// Le dernier �l�ment de la liste � afficher. Il sera le dernier partie
	int size = 0;			// Nombre d'�l�mentsde la liste � afficher
};

struct AnimationQueue {
	SpeedTimer* timer;	// Entre chaque output dans cette liste
	RenderQueue queue;
	AnimationQueue* nxtQueue = NULL;
	bool isLinear;		// Linear veut dire que tout les �l�ments seront affich�s l'un apr�s l'autre avec du �lai entre chaque, � l'oppos� de tout en m�me temps

	~AnimationQueue()
	{
		delete timer;
	}
};

/*
OPTIMISATION:
	Ultimement, l'animation queue devrait plut�t �tre convertit en 1 event qui g�re des drawer queues! �a r�glerais le probl�me de framerate sur tout les affichages de string
*/

class ConsoleRender
{
	friend void Clear_All_Renders();
	static AnimationQueue* first, *last;// Listes contenants tout les output � faire sur une base de temps
	static AnimationQueue* animationQueue;	// Permet d'ajouter tout les prochains �l�ments dans la m�me queue. Ils seront affich�s 1 apr�s l'autre avec un certain d�lai
	static RenderQueue mainQueue;		// Liste principale. Elle est vid� � chaque render. C'est ta responsabilit� de ne pas la overfill et caus� du lags avec "cout"
	static bool addToNewQueue;			// D�termine quelle queue utiliser pour ajouter des charact�res � render			

	static bool Is_Empty(const RenderQueue& queue);
	static void Pop_From_Queue(RenderQueue& queue, OutputData& data);		// Retire un OutputData d'une queue 
	static void Push_To_Queue(Coord crd, char sym, Colors clr, RenderQueue& queue);// Ajoute un OutputData a la fin de la queue
	static void Render_Main_Queue();				// Affiche tout les �l�ments pr�sent dans la main queue
	static void Render_Animation_Queue();				// Affiche tout les �l�ment qui doivent l'�tre selon les timer
	static void Empty_All(); // dangerous stuff here
public:
	static void Set_Animation_Delay();					// Ceci est un fix b�tard et rapide pour conserver des m�thodes d�suettes. �a ralentie les animations legacy en mode release.
	static void Add_String(std::string text, Coord crd,  Colors clr = WHITE, float speed = 0, bool erase = false);
	static void Add_Char(Coord crd, unsigned char sym, Colors clr = WHITE);	// Ajoute un charact�re � afficher pour le prochain render
	static void Create_Animation_Queue(float speed, bool linear = true);			// Cr�er une nouvelle Queue, tout les char suivant seront ajout� � celle-ci
	static void Stop_Queue();											// Stop l'ajout d'�l�ment dans la queue d'animation actuelle
	static void Render();	// Output tout les charact�res dans la console, selon les listes, et les timers de ces listes
};	
