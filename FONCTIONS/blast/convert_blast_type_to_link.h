#pragma once


#include "blast.h"
#include "../link/link.h"


LinkType Convert_Blast_Type_To_Link_Type(const BlastType &type);	// Quand tu tir, le blast à un type. Quand tu veux enregistrer le link après, tu dois créer un Link avec le type qui correspond au blast

