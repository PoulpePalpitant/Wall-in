#pragma once

// Polarisation dans la console : Positif = Vers le bas ou la droite
//								  Negatif = Vers la gauche ou le haut

enum Polarization { POS = 1, NEG = -1, NUL = 0 };

Polarization Get_Opp_Polar(Polarization plr);	// Donne la polarisation opposé
