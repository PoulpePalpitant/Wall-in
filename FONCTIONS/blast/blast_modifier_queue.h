#pragma once


#include "blast.h"
#include "../global_types/global_types.h"
#include "../queue/queue.h"

/*
	Une queue qui contient tout les modifiers de blast accumulés par le joueur

*/

extern const int MAX_BLAST_MOD_Q;

class BlastModifierQueue 
{
public:
	static RingBufferQueue<int> queue;	// blurg public
	static void Add_Modifier(Modifier mod);
	static void Consume_Next_Modifier();
	static int What_Is_Size() { return queue.Get_Current_Size(); }
};





