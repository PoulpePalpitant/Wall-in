#pragma once


#include "blast.h"
#include "../link/link.h"


LinkType Convert_Blast_Type_To_Link_Type(const BlastType &type);	// Quand tu tir, le blast � un type. Quand tu veux enregistrer le link apr�s, tu dois cr�er un Link avec le type qui correspond au blast

