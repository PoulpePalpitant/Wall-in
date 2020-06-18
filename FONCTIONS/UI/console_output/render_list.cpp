


#include "dsp_char.h"

#include "render_list.h"

 TimerQueue* first, * last;	// Listes contenants tout les output à faire sur une base de temps
 RenderQueue mainQueue;		// Liste principale. Elle est vidé à chaque render. C'est ta responsabilité de ne pas la overfill et causé du lags avec "cout"
 int leftToAdd;				// Ce truc va servir de compteur pour  déterminer quelle queue utiliser pour ajouter des charactères à render			


void ConsoleRender::Add_New_Timer_Queue()
{
	last = last->nxtQueue = new TimerQueue;	// Nouvelle queue
}		// Ajoute une nouvelle queue

void Push_To_Queue(Coord crd, char sym, Colors clr)// Ajoute un OutputData a la fin de la queue
{



}


OutputData* ConsoleRender::Pop_From_Queue(RenderQueue& queue)
{
	static OutputData* toPop, *toDelete;		// Le charactère à draw

	toPop = toDelete = NULL;
	toPop = toDelete = queue.first;
	
	queue.first = queue.first->nxt;				// not sure here...
	
	delete toDelete;
	queue.size--;	

	// delete si liste vide?

	return toPop;
}



bool ConsoleRender::Is_Queue_Empty(const RenderQueue& queue) {
	if (queue.first == NULL)
		return true;
	else
		return false;
}

bool ConsoleRender::Is_Queue_Full(const RenderQueue& queue) {
	if (queue.size == 1000)	// insert max queue size here
		return true;
	else
		return false;
}

void ConsoleRender::Render_Main_Queue()				// Affiche tout les éléments présent dans la main queue durant une frame
{
	static OutputData *toDraw;		// Le charactère à draw

	if (Is_Queue_Empty(mainQueue))
		return;	// rien à afficher pour cette frame
	else
	{
		while (toDraw = Pop_From_Queue(mainQueue))	// Tant que la liste est non vide
		{
			UI_Dsp_Char(toDraw->crd, toDraw->symbol, toDraw->clr);	// Affiche du symbole dans la console

		}

	}
}

void ConsoleRender::Add_To_Timer_Queue(Coord crd, char sym, Colors clr , float speed)
{
	if (leftToAdd == 0)
	{
		Add_New_Timer_Queue();	// Nouvelle queue
		last->delay.Set_Cd_Duration = speed;	// set_ le contdown
		last->queue.
	}
	// Comment adder un charactère dans le timer queue????
	// Il se peut que j'ajoute une dizaine de charactère successivement.
	// Ceucx-ci doivent se trouver tous dans la même queue

	leftToAdd--;		// Réduit de 1 le nombre de char à ajouter dans la même liste de timer
}

void ConsoleRender::Add_To_Main_Queue(Coord crd, char sym, Colors clr) 
{


}


// Ajoute un charactère à afficher dans une des render queues
// **********************************************************

void ConsoleRender::Add_To_Render_List(Coord crd, char sym, Colors clr, float speed)
{
	if (speed == 0)
		Add_To_Main_Queue(crd, sym, clr);			// ajouter dans le main render queue
	else
		Add_To_Timer_Queue(crd, sym, clr, speed);	
}

// Affiche tout les élément qui doivent l'être selon les timer
// ------------------------------------------------------------
void ConsoleRender::Render_Timer_Queue() 
{
	// Check la première liste
	// -> Vérifie si ya du temps sur le timer
	// Si countdown yé done, on refreshle timer
	// Pop l'élément, passe au suivant
}


// Draw tout les éléments à draw dans les listes pour la frame actuelle
// ********************************************************************

void ConsoleRender::Render()	// Output tout les charactères dans la console, selon les listes, et les timers de ces listes
{
	Render_Main_Queue();// Affiche l'élément de la liste
	Render_Timer_Queue();
}

