


#include "dsp_char.h"
#include "dsp_string.h"
#include "../../player/player.h"	// Uniquement pour empêcher f'afficher par dessus le joueur
#include "../../time/timerOP.h"

#include "render_list.h"


StringAnimationList ConsoleRender::strList;
RenderQueue ConsoleRender::mainQueue;					// Liste principale. Elle est vidé à chaque render. C'est ta responsabilité de ne pas la overfill et causé du lags avec "cout"

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

// Ajoute un charactère à afficher dans une des render queues
// **********************************************************

void ConsoleRender::Add_Char(Coord crd, unsigned char sym, Colors clr)
{
	Push_To_Queue(crd, sym, clr, mainQueue); // Ajoute un OutputData a la fin de la queue
}
void ConsoleRender::Add_String(std::string text,Coord crd,  Colors clr , int speed, bool erase)
{
	if (text == "")
		throw "Pas de string vide dans mon salon";
	
	// Création d'une nouvelle queue pour la string
	if (strList.last == NULL)	// Liste vide	
		strList.first = strList.last = new StringQueue((int)text.length(), speed);	// Nouvelle queue	
	else
		strList.last = strList.last->nxt = new StringQueue((int)text.length(), speed);	// Nouvelle queue

	strList.last->Add_String(crd, text, clr,erase);
}



// Affiche tout les élément qui doivent l'être selon les timer
// ------------------------------------------------------------
void ConsoleRender::Render_String_Animation()
{
	StringQueue* queueToPop = strList.first;		// Pourrait être null
	StringQueue* prev = NULL;
	CharData charToDraw = {};							// À draw

	while (queueToPop)	// tant que ta pas finis de traverser tout les listes
	{
		while (queueToPop->timer->Tick())	// Le temps est écoulé, On affiche un élément de la queue!
		{
			charToDraw = queueToPop->Pop_First();
			Push_To_Queue(charToDraw.crd, charToDraw.symbol, charToDraw.clr, mainQueue);	// Ajoute le symbole à la renderqueue

			// Delete la queue si elle est vide				Garbo
			if (queueToPop->Is_Empty())
			{
				if (queueToPop == strList.first && queueToPop == strList.last)
				{
					delete queueToPop;	// Delete la queue actuelle»
					queueToPop = strList.first = strList.last = NULL;
					return;			// tu dois sortir car le timer n'existe plus :O et on a plus rien à updater aussi»
				}
				else
					if (queueToPop == strList.first)
					{
						queueToPop = queueToPop->nxt;
						delete strList.first;
						strList.first = queueToPop;	// new first
						prev = NULL; /*safety*/
					}
					else
						if (queueToPop == strList.last)
						{
							queueToPop = prev->nxt = NULL;
							delete strList.last;
							strList.last = prev;	// new last
							return;			// tu dois sortir car le timer n'existe plus :O et on a plus rien à updater aussi»
						}
						else
						{
							prev->nxt = queueToPop->nxt;
							delete queueToPop;
							queueToPop = prev->nxt;	// Passe au prochain
						}
			}
		}

		// Le temps n'est pas encore écoulé pour updater l'affichage ici. On passe donc à la prochaine queue
		prev = queueToPop;	// relink
		queueToPop = queueToPop->nxt;	// pass au prochain
	}
}

// LAZY COPY-PASTE
// ***************

void ConsoleRender::Empty_All()
{
	// Vide la main queue
	OutputData toDraw;

	while (mainQueue.size > 0)	// Tant que la liste est non vide
		Pop_From_Queue(mainQueue, toDraw);	 // Prend un nouvel élément

	mainQueue.first = mainQueue.last = NULL; // Good Practice!

	// Vide animation queue
	StringQueue* queueToPop = strList.first;		// Pourrait être null
	StringQueue* prev = NULL;
	CharData charToDraw = {};							// À draw

	while (queueToPop)	// tant que ta pas finis de traverser tout les listes
	{
			charToDraw = queueToPop->Pop_First();

			// Delete la queue si elle est vide				Garbo
			if (queueToPop->Is_Empty())
			{
				if (queueToPop == strList.first && queueToPop == strList.last)
				{
					delete queueToPop;	// Delete la queue actuelle»
					queueToPop = strList.first = strList.last = NULL;
					continue;
				}
				else
					if (queueToPop == strList.first)
					{
						queueToPop = queueToPop->nxt;
						delete strList.first;
						strList.first = queueToPop;	// new first
						prev = NULL; /*safety*/
					}
					else
						if (queueToPop == strList.last)
						{
							queueToPop = prev->nxt = NULL;
							delete strList.last;
							strList.last = prev;	// new last
							continue;
						}
						else
						{
							prev->nxt = queueToPop->nxt;
							delete queueToPop;
							queueToPop = prev->nxt;	// Passe au prochain
						}
			}

		// Le temps n'est pas encore écoulé pour updater l'affichage ici. On passe donc à la prochaine queue
		prev = queueToPop;	// relink
		queueToPop = queueToPop->nxt;	// pass au prochain
	}

	strList.first = strList.last = NULL; // safety

}


// Draw tout les éléments à draw dans les listes pour la frame actuelle
// ********************************************************************

void ConsoleRender::Render()				// Affiche tout les éléments présent dans la main queue durant une frame
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
