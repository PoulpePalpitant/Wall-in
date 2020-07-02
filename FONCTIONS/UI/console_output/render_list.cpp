


#include "dsp_char.h"
#include "dsp_string.h"
#include "../../player/player.h"	// Uniquement pour empêcher f'afficher par dessus le joueur
#include "../../time/timerOP.h"

#include "render_list.h"

 AnimationQueue* ConsoleRender::first, *ConsoleRender::last;			// Listes contenants tout les output à faire sur une base de temps
 RenderQueue ConsoleRender::mainQueue;					// Liste principale. Elle est vidé à chaque render. C'est ta responsabilité de ne pas la overfill et causé du lags avec "cout"
 AnimationQueue* ConsoleRender::animationQueue;		// Permet d'ajouter des éléments dans la même queue d'animation
 bool ConsoleRender::addToNewQueue;			// Détermine quelle queue utiliser pour ajouter des charactères à render			

 // Ajoute une nouvelle queue d'animation
void ConsoleRender::Create_Queue(float speed, bool linear)
{
	if (last == NULL)	// Liste vide	
		first = last = new AnimationQueue;	// Nouvelle queue	
	else
		last = last->nxtQueue = new AnimationQueue;	// Nouvelle queue

	last->timer.Set_Cd_Duration(speed);	 // Set la durée du countdown, mais L'ACTIVE TOUT DE SUITE BRAH
	last->timer.Start_CountDown();	 // Set la durée du countdown, mais L'ACTIVE TOUT DE SUITE BRAH
	
	animationQueue = last;
	animationQueue->isLinear = linear;	// Si l'animation est lineaire, ou pas
	addToNewQueue = true;		// Les prochains output d'animation seront ajouté dans cette queue
}		

// On stop l'ajout de charactères dans cette queue(ne s'applique pas à la mainqueue)
void ConsoleRender::Stop_Queue()
{
	addToNewQueue = false;	
	animationQueue = NULL;
}

void ConsoleRender::Push_To_Queue(Coord crd, char sym, Colors clr, RenderQueue& queue)// Ajoute un OutputData a la fin de la queue
{
	if (queue.first == NULL)
		queue.first = queue.last = new OutputData;
	else	
		queue.last = queue.last->nxt = new OutputData;

	queue.last->clr = clr;
	queue.last->crd = crd;
	queue.last->symbol = sym;
	queue.size++;
}

void ConsoleRender::Pop_From_Queue(RenderQueue& queue, OutputData& data)
{
	static OutputData *toDelete;		// Le charactère à draw

	toDelete = NULL;
	toDelete = queue.first;
	data = *toDelete;
	
	queue.first = queue.first->nxt;				// SI TU BUG ICI: TA ESSAYER D'AJOUTER UNE STRING VIDE "" OU NON-INITIALISÉ DANS UN RENDER 
	delete toDelete;
	queue.size--;	
}

bool ConsoleRender::Is_Empty(const RenderQueue& queue) {
	if (queue.size == 0)
		return true;
	else
		return false;
}

//bool ConsoleRender::Is_Queue_Full(const RenderQueue& queue) {
//	if (queue.size == 1000)	// insert max queue size here
//		return true;
//	else
//		return false;
//}

void ConsoleRender::Render_Main_Queue()				// Affiche tout les éléments présent dans la main queue durant une frame
{
	static OutputData toDraw;		// Le charactère à draw

	if (Is_Empty(mainQueue))
		return;	// rien à afficher pour cette frame
	else
	{
		while (mainQueue.size > 0)	// Tant que la liste est non vide
		{
			Pop_From_Queue(mainQueue, toDraw);					// Prend un nouvel élément
			UI_Dsp_Char(toDraw.crd, toDraw.symbol, toDraw.clr);	// Affiche du symbole dans la console
		}

		mainQueue.first = mainQueue.last = NULL; // Good Practice!
	}
}

// Ajoute un charactère à afficher dans une des render queues
// **********************************************************

void ConsoleRender::Add_Char(Coord crd, unsigned char sym, Colors clr)
{
	if (addToNewQueue)	// Ajout dans une queue d'animation
		Push_To_Queue(crd, sym, clr, animationQueue->queue); // Ajoute un OutputData a la fin de la queue
	else
		Push_To_Queue(crd, sym, clr, mainQueue); // Ajoute un OutputData a la fin de la queue

}
void ConsoleRender::Add_String(std::string text,Coord crd,  Colors clr , float speed, bool erase)
{
	if (text == "")
		throw "Pas de string vide dans mon salon";

	RenderQueue* toPush = NULL;
	int size = (int)text.length();	// Assignation de la longueur de la string 	

	if (speed > 0 )	// assignation de la queue
	{
		Stop_Queue();	// safety
		Create_Queue(speed);	
		toPush = &animationQueue->queue; // Créer une nouvelle animation queue automatiquement
	}
	else
		if(addToNewQueue)
			toPush = &animationQueue->queue;	// Animation queue était déjà là
		else
			toPush = &mainQueue;	// Pas d'animation queue

	if (erase)
	{
		for (int loop = 0; loop < size; loop++)
		{
			Push_To_Queue(crd,TXT_CONST.SPACE, clr, *toPush);
			crd.x++;										// Incrémente x pour le prochain charactère	
		}
	}
	else
		for (int loop = 0; loop < size; loop++)
		{
			Push_To_Queue(crd, text[loop], clr, *toPush);
			crd.x++;										// Incrémente x pour le prochain charactère	
		}
}



// Affiche tout les élément qui doivent l'être selon les timer
// ------------------------------------------------------------
void ConsoleRender::Render_Animation_Queue()
{
	AnimationQueue* toPop = first;		// Pourrait être null
	AnimationQueue* prev = NULL;		
	OutputData toDraw = {};				// À draw
	static Coord playerPos = {0,0}; // On veut pas afficher quoi que ce soit par dessus le joueur..... Le gros problème de ce système de queue

	playerPos = P1.Get_XY();		
	
	while (toPop)	// tant que ta pas finis de traverser tout les listes
	{	
		if (toPop->timer.Get_Time_Left() <= 0)	// Le temps est écoulé, On affiche un élément de la queue!
		{
			Pop_From_Queue(toPop->queue, toDraw);	

			if(!Are_Equal(toDraw.crd, playerPos))
				UI_Dsp_Char(toDraw.crd, toDraw.symbol, toDraw.clr);	// Affiche du symbole dans la console

			// Delete la queue si elle est vide				Garbo
			if (Is_Empty(toPop->queue))
			{

				if (toPop == first && toPop == last)
				{
					delete toPop;	// Delete la queue actuelle
					toPop = first = last = NULL;
				}
				else
					if (toPop == first)
					{
						toPop = toPop->nxtQueue;
						delete first;
						first = toPop;	// new first
						prev = NULL; /*safety*/
					}
					else
						if (toPop == last)
						{
							toPop = prev->nxtQueue = NULL;
							delete last;
							last = prev;	// new last
						}
						else
						{
							prev->nxtQueue = toPop->nxtQueue;	
							delete toPop;
							toPop = prev->nxtQueue;	// Passe au prochain
						}
			}
			else
			{
				if(toPop->isLinear)
					toPop->timer.Start_CountDown();	// Prochain countdown	// Pour l'animation d'une shot, en omet simplement de reset le countdown :)

				prev = toPop;				// please repeat yourself
				toPop = toPop->nxtQueue;	
			}
		}
		else// Le temps n'est pas encore écoulé
		{
			toPop->timer.Tick_Timer();		// Avance le countdown
			prev = toPop;	// relink
			toPop = toPop->nxtQueue;	// pass au prochain
		}

	}
}


// Draw tout les éléments à draw dans les listes pour la frame actuelle
// ********************************************************************

void ConsoleRender::Render()	// Output tout les charactères dans la console, selon les listes, et les timers de ces listes
{
	Render_Main_Queue();		// Affiche les éléments de la liste immédiates
	
	//if (!GameLoopClock::pause)		// On render pas les animations si le jeu est en pause
		Render_Animation_Queue();	// Affiche les éléments des listes d'animation, solution très simplistes pour créer de l'animation linéaire. Beaucoup de bug et d'unforseen consequences. Ex: La détection de colision peut bien sortir par la fenêtre
	
	Stop_Queue();		/*Safety*/		// au cas où tu oublis de stop la queue à la fin d'un update
}

