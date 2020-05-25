
#include "convert_blast_type_to_wall.h"

// Convertit le type d'un blast en un type de link quand un tir est fait. EX :Un tir régulier va donc faire un 'Link' régulier
WallType Convert_Blast_Type_To_Wall_Type(const BlastType& type)
{
	static WallType convert;

	switch (type)
	{
	case BlastType::REGULAR:
		convert = WallType::REGULAR; break;	
		/*
		case BlastType::REGULAR
		case BlastType::REGULAR
		case BlastType::REGULAR
		case BlastType::REGULAR
		case BlastType::REGULAR
		*/





	}

	return convert;
}
