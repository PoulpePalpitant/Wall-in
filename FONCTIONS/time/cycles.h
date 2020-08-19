#pragma once 

struct cycles{	// Template de cycles
	bool gThisCycle;
	int gCycleDuration;
	unsigned long long gCurrentCycle;
	unsigned long long gNextCycle;
	int gCycleTot;						// Le nombre total de cycle ayant u lieu
};

extern bool stopSpwCycle; 
extern bool stopMoveCycle;

void Reset_Spw_Cycle();				// Reset le nombre de spw cycle � 0
void UPD_Cycles_Stuff();			// Update les cycles des bots
void Do_Stuff_this_Cycle();