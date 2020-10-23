#pragma once

#include "../coord.h"
#include "../txtstyle.h"
#include "../../time/countdown_clock.h"
#include "../../time/movement_timer.h"
#include "../../events/global_events/clear_all_states.h"
#include "string_animation.h"

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


// Console Render permet de centralis� tout les affichages dans la console. Cette class g�re tout la liste des outputs de charact�res et les vide la liste � chaque tick de la gameloop (ind�pendamment du framerate)
// Cette classe contient �galement une idotie de ma parte, c'est � dire une queue de charact�res � animer dans le temps nomm� StringAnimationList. Cette queue utilise les m�me fonctionnalit� que la render queue, sauf que
// chaque liste de charact�res sont associ�s � un timer. J'ai appris � mes d�pend qu'il �tait stupide d'updater cette liste en m�me temps que la liste principale, car l'animation devient compl�tement d�synchroniser avec
// la limite de framerate que j'ai implant�, oops! Je ne vais pas delete ou s�parer l'animation queue car elle est trop omnipr�sente dans le code. C'est pourquoi elle reste ici. Je l'ai n�anmoins modifi� pour qu'elle
// s'occupe uniquement des affichages de String dans le temps

class ConsoleRender
{
	friend void Clear_All_Renders();
	static StringAnimationList strList;	// la liste de tous les animations de string
	static RenderQueue mainQueue;		// Liste principale. Elle est vid� � chaque render. C'est ta responsabilit� de ne pas la overfill et caus� du lags avec "cout"

	static bool Is_Empty(const RenderQueue& queue);
	static void Pop_From_Queue(RenderQueue& queue, OutputData& data);		// Retire un OutputData d'une queue 
	static void Push_To_Queue(Coord crd, char sym, Colors clr, RenderQueue& queue);// Ajoute un OutputData a la fin de la queue
	static void Empty_All(); // dangerous stuff here

public:
	static void Render_String_Animation();			// Affiche tout les strings selon des timers
	static void Add_String(std::string text, Coord crd,  Colors clr = WHITE, float speed = 0, bool erase = false);
	static void Add_Char(Coord crd, unsigned char sym, Colors clr = WHITE);	// Ajoute un charact�re � afficher pour le prochain render
	static void Render();	// Output tout les charact�res dans la console, selon les listes, et les timers de ces listes
};	



