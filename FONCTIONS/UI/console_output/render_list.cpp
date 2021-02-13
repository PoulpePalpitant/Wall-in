

#include "render_list.h"

#include "dsp_char.h"
#include "dsp_string.h"
#include "../../player/player.h"	
#include "../../time/timerOP.h"



StringAnimationList ConsoleRender::strList;
RenderQueue ConsoleRender::mainQueue;					

void ConsoleRender::Push_To_Queue(Coord crd, char sym, Colors clr, RenderQueue& queue)
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
	static OutputData *toDelete;		

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

void ConsoleRender::Add_Char(Coord crd, unsigned char sym, Colors clr)
{
	Push_To_Queue(crd, sym, clr, mainQueue); // Ajoute un OutputData a la fin de la queue
}

void ConsoleRender::Add_String(std::string text,Coord crd,  Colors clr , int speed, bool erase)
{
	if (text == "")
		throw "Pas de string vide dans mon salon";
	
	if (speed == 0)	// tu suite à la render queue, y'aura pas d'animation
	{
		if (erase)
			for (int i = 0; i < text.size(); i++)
			{
				Push_To_Queue(crd, TXT_CONST.SPACE, WHITE, mainQueue);
				crd.x++;
			}
		else
			for (unsigned char c : text)
			{
				Push_To_Queue(crd, c, clr, mainQueue);
				crd.x++;
			}
		
		return;
	}
	
	// Création d'une nouvelle queue pour la string
	if (strList.last == NULL)	// Liste vide	
		strList.first = strList.last = new StringQueue((int)text.length(), speed);	
	else
		strList.last = strList.last->nxt = new StringQueue((int)text.length(), speed);

	strList.last->Add_String(crd, text, clr,erase);
}



// Affiche tout les élément qui doivent l'être selon les timer
// ------------------------------------------------------------
void ConsoleRender::Render_String_Animation()
{
	StringQueue* queueToPop = strList.first;		// Pourrait être null
	StringQueue* prev = NULL;
	CharData charToDraw = {};							

	while (queueToPop)	// tant que ta pas finis de traverser tout les listes
	{
		while (queueToPop->timer->Tick())	// Le temps est écoulé, On affiche un élément de la queue!
		{
			charToDraw = queueToPop->Pop_First();
			Push_To_Queue(charToDraw.crd, charToDraw.symbol, charToDraw.clr, mainQueue);	// Ajoute le symbole à la renderqueue

			// Delete la queue si elle est vide		
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
		prev = queueToPop;	
		queueToPop = queueToPop->nxt;	
	}
}

// LAZY COPY-PASTE
// ***************

void ConsoleRender::Empty_All()
{
	OutputData toDraw;

	while (mainQueue.size > 0)	
		Pop_From_Queue(mainQueue, toDraw);	

	mainQueue.first = mainQueue.last = NULL; 

	StringQueue* queueToPop = strList.first;	
	StringQueue* prev = NULL;
	CharData charToDraw = {};							

	while (queueToPop)
	{
			charToDraw = queueToPop->Pop_First();

			if (queueToPop->Is_Empty())
			{
				if (queueToPop == strList.first && queueToPop == strList.last)
				{
					delete queueToPop;	
					queueToPop = strList.first = strList.last = NULL;
					continue;
				}
				else
					if (queueToPop == strList.first)
					{
						queueToPop = queueToPop->nxt;
						delete strList.first;
						strList.first = queueToPop;	
						prev = NULL;
					}
					else
						if (queueToPop == strList.last)
						{
							queueToPop = prev->nxt = NULL;
							delete strList.last;
							strList.last = prev;	
							continue;
						}
						else
						{
							prev->nxt = queueToPop->nxt;
							delete queueToPop;
							queueToPop = prev->nxt;	
						}
			}

		prev = queueToPop;	
		queueToPop = queueToPop->nxt;	
	}

	strList.first = strList.last = NULL; 

}

void ConsoleRender::Render()				
{
	static OutputData toDraw;		

	if (Is_Empty(mainQueue))
		return;	
	else
	{
		while (mainQueue.size > 0)	
		{
			Pop_From_Queue(mainQueue, toDraw);					
			UI_Dsp_Char(toDraw.crd, toDraw.symbol, toDraw.clr);	
		}

		mainQueue.first = mainQueue.last = NULL; 
	}
}
