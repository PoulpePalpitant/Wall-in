


#include "dsp_char.h"
#include "dsp_string.h"
#include "../../player/player.h"	// Uniquement pour emp�cher f'afficher par dessus le joueur
#include "../../time/timerOP.h"

#include "render_list.h"


StringAnimationList ConsoleRender::strList;
RenderQueue ConsoleRender::mainQueue;					// Liste principale. Elle est vid� � chaque render. C'est ta responsabilit� de ne pas la overfill et caus� du lags avec "cout"

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

// Ajoute un charact�re � afficher dans une des render queues
// **********************************************************

void ConsoleRender::Add_Char(Coord crd, unsigned char sym, Colors clr)
{
	Push_To_Queue(crd, sym, clr, mainQueue); // Ajoute un OutputData a la fin de la queue
}
void ConsoleRender::Add_String(std::string text,Coord crd,  Colors clr , int speed, bool erase)
{
	if (text == "")
		throw "Pas de string vide dans mon salon";
	
	// Cr�ation d'une nouvelle queue pour la string
	if (strList.last == NULL)	// Liste vide	
		strList.first = strList.last = new StringQueue((int)text.length(), speed);	// Nouvelle queue	
	else
		strList.last = strList.last->nxt = new StringQueue((int)text.length(), speed);	// Nouvelle queue

	strList.last->Add_String(crd, text, clr,erase);
}



// Affiche tout les �l�ment qui doivent l'�tre selon les timer
// ------------------------------------------------------------
void ConsoleRender::Render_String_Animation()
{
	StringQueue* queueToPop = strList.first;		// Pourrait �tre null
	StringQueue* prev = NULL;
	CharData charToDraw = {};							// � draw

	while (queueToPop)	// tant que ta pas finis de traverser tout les listes
	{
		while (queueToPop->timer->Tick())	// Le temps est �coul�, On affiche un �l�ment de la queue!
		{
			charToDraw = queueToPop->Pop_First();
			Push_To_Queue(charToDraw.crd, charToDraw.symbol, charToDraw.clr, mainQueue);	// Ajoute le symbole � la renderqueue

			// Delete la queue si elle est vide				Garbo
			if (queueToPop->Is_Empty())
			{
				if (queueToPop == strList.first && queueToPop == strList.last)
				{
					delete queueToPop;	// Delete la queue actuelle�
					queueToPop = strList.first = strList.last = NULL;
					return;			// tu dois sortir car le timer n'existe plus :O et on a plus rien � updater aussi�
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
							return;			// tu dois sortir car le timer n'existe plus :O et on a plus rien � updater aussi�
						}
						else
						{
							prev->nxt = queueToPop->nxt;
							delete queueToPop;
							queueToPop = prev->nxt;	// Passe au prochain
						}
			}
		}

		// Le temps n'est pas encore �coul� pour updater l'affichage ici. On passe donc � la prochaine queue
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
		Pop_From_Queue(mainQueue, toDraw);	 // Prend un nouvel �l�ment

	mainQueue.first = mainQueue.last = NULL; // Good Practice!

	// Vide animation queue
	StringQueue* queueToPop = strList.first;		// Pourrait �tre null
	StringQueue* prev = NULL;
	CharData charToDraw = {};							// � draw

	while (queueToPop)	// tant que ta pas finis de traverser tout les listes
	{
			charToDraw = queueToPop->Pop_First();

			// Delete la queue si elle est vide				Garbo
			if (queueToPop->Is_Empty())
			{
				if (queueToPop == strList.first && queueToPop == strList.last)
				{
					delete queueToPop;	// Delete la queue actuelle�
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

		// Le temps n'est pas encore �coul� pour updater l'affichage ici. On passe donc � la prochaine queue
		prev = queueToPop;	// relink
		queueToPop = queueToPop->nxt;	// pass au prochain
	}

	strList.first = strList.last = NULL; // safety

}


// Draw tout les �l�ments � draw dans les listes pour la frame actuelle
// ********************************************************************

void ConsoleRender::Render()				// Affiche tout les �l�ments pr�sent dans la main queue durant une frame
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
