#pragma once

#include "spawn_bot.h"

extern bool jerryTime;	// It's Jerry Spawning time
extern int jerCount;		// Nombre de fois que le joueur doit stopper Jerry
extern int deadJerrys;		// Le nombre de Jerry qui sont dead pendant un Jerry time

void Ev_Spawn_Jerry();
void Ev_Stop_Spawn_Jerry();	// Stop l'event de spawn Jerry!

void Spawn_A_Jerry(Direction boxSide, int spwNum, int delay);	// Permet de spawn un Jerry
void Set_Jerry(Direction boxSide, int spwNum, int moveSpeed);
void Set_Jerry_Time(int JerryToStop);							// Nombre de Jerry à buter pendant un Jerry time
void Add_Jerrys_To_Stop(int toAdd);

void Update_Dead_Jerrys();							// Nombre de Jerry à buter pendant un Jerry time

// garbage
void Make_It_Vertical_Only();
