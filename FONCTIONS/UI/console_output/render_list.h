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
	OutputData* first = NULL;	// Le premier élément de la liste à afficher. Il sera le premier partie
	OutputData* last = NULL;	// Le dernier élément de la liste à afficher. Il sera le dernier partie
	int size = 0;			// Nombre d'élémentsde la liste à afficher
};


// Console Render permet de centralisé tout les affichages dans la console. Cette class gère tout la liste des outputs de charactères et les vide la liste à chaque tick de la gameloop (indépendamment du framerate)
// Cette classe contient également une idotie de ma parte, c'est à dire une queue de charactères à animer dans le temps nommé StringAnimationList. Cette queue utilise les même fonctionnalité que la render queue, sauf que
// chaque liste de charactères sont associés à un timer. J'ai appris à mes dépend qu'il était stupide d'updater cette liste en même temps que la liste principale, car l'animation devient complètement désynchroniser avec
// la limite de framerate que j'ai implanté, oops! Je ne vais pas delete ou séparer l'animation queue car elle est trop omniprésente dans le code. C'est pourquoi elle reste ici. Je l'ai néanmoins modifié pour qu'elle
// s'occupe uniquement des affichages de String dans le temps

class ConsoleRender
{
	friend void Clear_All_Renders();
	static StringAnimationList strList;	// la liste de tous les animations de string
	static RenderQueue mainQueue;		// Liste principale. Elle est vidé à chaque render. C'est ta responsabilité de ne pas la overfill et causé du lags avec "cout"

	static bool Is_Empty(const RenderQueue& queue);
	static void Pop_From_Queue(RenderQueue& queue, OutputData& data);		// Retire un OutputData d'une queue 
	static void Push_To_Queue(Coord crd, char sym, Colors clr, RenderQueue& queue);// Ajoute un OutputData a la fin de la queue
	static void Empty_All(); // dangerous stuff here

public:
	static void Render_String_Animation();			// Affiche tout les strings selon des timers
	static void Add_String(std::string text, Coord crd,  Colors clr = WHITE, float speed = 0, bool erase = false);
	static void Add_Char(Coord crd, unsigned char sym, Colors clr = WHITE);	// Ajoute un charactère à afficher pour le prochain render
	static void Render();	// Output tout les charactères dans la console, selon les listes, et les timers de ces listes
};	



