#include "polarisation.h"



// Donne la polarization opposé
Polarization Get_Opp_Polar(Polarization plr)
{
	return (Polarization)(plr * NEG);
}