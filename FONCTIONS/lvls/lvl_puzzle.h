#pragma once
#include "../grid/grid.h"


class LvlPuzzle {
	int lvl;
	int id;

	int step;
	int maxStep;
	int numberShots;
	GrdCoord playerStartPos;


	void Reset() {
		step = 0;
	}

	LvlPuzzle(int lvl, int id, int maxStep) {
		this->lvl = lvl;
		this->id = id;
		this->maxStep = maxStep;
	}

	void Script_Patch();
	//{
	//	int currPuzzle = gCurrentCheckPoints[gCurrentLevel - 1];
	//	int puzzleStep = 5;

	//	switch (step)
	//	{
	//	default:
	//		break;
	//	}

	//}
};
