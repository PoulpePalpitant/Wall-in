#include "polarisation.h"



// Donne la polarization oppos�
Polarization Get_Opp_Polar(Polarization plr)
{
	return (Polarization)(plr * NEG);
}