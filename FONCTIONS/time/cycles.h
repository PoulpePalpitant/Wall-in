#pragma once 

struct cycles{	// Template de cycles
	bool gThisCycle;
	int gCycleDuration;
	unsigned long long gCurrentCycle;
	unsigned long long gNextCycle;
	int gCycleTot;						// Le nombre total de cycle ayant u lieu
};

void UPD_Cycles();			// Update les cycles
void Do_Stuff_this_Cycle();