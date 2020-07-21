
#include "../events/msg_dispatcher.h"
#include "blast_modifier_queue.h"
#include "mod_queue_animator.h"
#include "mod_queue_animator_add.h"
#include "mod_queue_animator_consume.h"
#include "../player/player.h"


const int MAX_BLAST_MOD_Q = 10;

RingBufferQueue<int> BlastModifierQueue::queue(MAX_BLAST_MOD_Q);


void BlastModifierQueue::Add_Modifier(Modifier mod)
{
	int currentSize = 0;

	queue.Register(mod);	// ajoute l'item si queue non pleine
	currentSize = queue.Get_Current_Size();
	
	// Trigger l'animator. Va se charger de créer une tit animation
	if (currentSize <= 5)
	{
		DrawModifierQueue::addNew.Add_To_Index(mod, currentSize - 1);
	
		if(currentSize == 1)	// la couleur du joueur va changé selon son modifier
			P1.Upd_Color();

	}

	// Si ya plus que 5 encore dans la queue
	if (currentSize == 6)		// quand la limite viens d'être dépassé
		DrawModifierQueue::Show_Excess();

	if (!DrawModifierQueue::isShown)	// we show it!
		MsgQueue::Register(SHOW_MOD_QUEUE);
}
void BlastModifierQueue::Consume_Next_Modifier()
{
	static Modifier mod;

	if (queue.Get_Current_Size() == 0)
	{
		blastP1.Setup_Modifier(REGULAR);	// Aucun modifier
		return;
	}
	else
	{
		mod = (Modifier)queue.Extract();
		blastP1.Setup_Modifier(mod);	// Assigne le modifier de la queue au tir du blast actuel
		DrawModifierQueue::Reorder_Rest_Of_Queue();	// Réagence la queue affiché
		DrawModifierQueue::consume.Add_To_Next_Available(mod);		// pour l'animation
		DrawModifierQueue::addNew.Cancel();
		
		P1.Upd_Color();	// couleur du joueur change selon son prochain modifier

		if (BlastModifierQueue::What_Is_Size() == 5)		// quand on redescend en dessous de 6
			DrawModifierQueue::Hide_Excess();
	}
}