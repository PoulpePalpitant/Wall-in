


#include "dsp_char.h"
#include "dsp_string.h"
#include "../../player/player.h"	// Uniquement pour emp�cher f'afficher par dessus le joueur
#include "../../time/timerOP.h"

#include "render_list.h"

 AnimationQueue* ConsoleRender::first, *ConsoleRender::last;			// Listes contenants tout les output � faire sur une base de temps
 RenderQueue ConsoleRender::mainQueue;					// Liste principale. Elle est vid� � chaque render. C'est ta responsabilit� de ne pas la overfill et caus� du lags avec "cout"
 AnimationQueue* ConsoleRender::animationQueue;		// Permet d'ajouter des �l�ments dans la m�me queue d'animation
 bool ConsoleRender::addToNewQueue;			// D�termine quelle queue utiliser pour ajouter des charact�res � render			

 // Ajoute une nouvelle queue d'animation
void ConsoleRender::Create_Queue(float speed, bool linear)
{
	if (last == NULL)	// Liste vide	
		first = last = new AnimationQueue;	// Nouvelle queue	
	else
		last = last->nxtQueue = new AnimationQueue;	// Nouvelle queue

	last->timer.Set_Cd_Duration(speed);	 // Set la dur�e du countdown, mais L'ACTIVE TOUT DE SUITE BRAH
	last->timer.Start_CountDown();	 // Set la dur�e du countdown, mais L'ACTIVE TOUT DE SUITE BRAH
	
	animationQueue = last;
	animationQueue->isLinear = linear;	// Si l'animation est lineaire, ou pas
	addToNewQueue = true;		// Les prochains output d'animation seront ajout� dans cette queue
}		

// On stop l'ajout de charact�res dans cette queue(ne s'applique pas � la mainqueue)
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
	static OutputData *toDelete;		// Le charact�re � draw

	toDelete = NULL;
	toDelete = queue.first;
	data = *toDelete;
	
	queue.first = queue.first->nxt;				// SI TU BUG ICI: TA ESSAYER D'AJOUTER UNE STRING VIDE "" OU NON-INITIALIS� DANS UN RENDER 
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

void ConsoleRender::Render_Main_Queue()				// Affiche tout les �l�ments pr�sent dans la main queue durant une frame
{
	static OutputData toDraw;		// Le charact�re � draw

	if (Is_Empty(mainQueue))
		return;	// rien � afficher pour cette frame
	else
	{
		while (mainQueue.size > 0)	// Tant que la liste est non vide
		{
			Pop_From_Queue(mainQueue, toDraw);					// Prend un nouvel �l�ment
			UI_Dsp_Char(toDraw.crd, toDraw.symbol, toDraw.clr);	// Affiche du symbole dans la console
		}

		mainQueue.first = mainQueue.last = NULL; // Good Practice!
	}
}

// Ajoute un charact�re � afficher dans une des render queues
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
		toPush = &animationQueue->queue; // Cr�er une nouvelle animation queue automatiquement
	}
	else
		if(addToNewQueue)
			toPush = &animationQueue->queue;	// Animation queue �tait d�j� l�
		else
			toPush = &mainQueue;	// Pas d'animation queue

	if (erase)
	{
		for (int loop = 0; loop < size; loop++)
		{
			Push_To_Queue(crd,TXT_CONST.SPACE, clr, *toPush);
			crd.x++;										// Incr�mente x pour le prochain charact�re	
		}
	}
	else
		for (int loop = 0; loop < size; loop++)
		{
			Push_To_Queue(crd, text[loop], clr, *toPush);
			crd.x++;										// Incr�mente x pour le prochain charact�re	
		}
}



// Affiche tout les �l�ment qui doivent l'�tre selon les timer
// ------------------------------------------------------------
void ConsoleRender::Render_Animation_Queue()
{
	AnimationQueue* toPop = first;		// Pourrait �tre null
	AnimationQueue* prev = NULL;		
	OutputData toDraw = {};				// � draw
	static Coord playerPos = {0,0}; // On veut pas afficher quoi que ce soit par dessus le joueur..... Le gros probl�me de ce syst�me de queue

	playerPos = P1.Get_XY();		
	
	while (toPop)	// tant que ta pas finis de traverser tout les listes
	{	
		if (toPop->timer.Get_Time_Left() <= 0)	// Le temps est �coul�, On affiche un �l�ment de la queue!
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
		else// Le temps n'est pas encore �coul�
		{
			toPop->timer.Tick_Timer();		// Avance le countdown
			prev = toPop;	// relink
			toPop = toPop->nxtQueue;	// pass au prochain
		}

	}
}


// Draw tout les �l�ments � draw dans les listes pour la frame actuelle
// ********************************************************************

void ConsoleRender::Render()	// Output tout les charact�res dans la console, selon les listes, et les timers de ces listes
{
	Render_Main_Queue();		// Affiche les �l�ments de la liste imm�diates
	
	//if (!GameLoopClock::pause)		// On render pas les animations si le jeu est en pause
		Render_Animation_Queue();	// Affiche les �l�ments des listes d'animation, solution tr�s simplistes pour cr�er de l'animation lin�aire. Beaucoup de bug et d'unforseen consequences. Ex: La d�tection de colision peut bien sortir par la fen�tre
	
	Stop_Queue();		/*Safety*/		// au cas o� tu oublis de stop la queue � la fin d'un update
}

