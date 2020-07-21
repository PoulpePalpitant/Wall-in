
#pragma once

#include "../blast/blast.h"


// Va créer l'animation du blast

class UI_MoveBlast {
private:
static SpeedTimer eraserTimer;

static void Move_Blast_Head_Forward(Blast* blast);
static bool Chk_Max_Blast_Length(Blast* blast);
static void Erase_Blast_Tail(Blast* blast);
static void Erase_Whole_Blast(Blast* blast);


protected:	
friend class Blast;
static void Animate_Blast(Blast* blast);

public:
static void Setup_Blast_Eraser(Blast* blast);
};