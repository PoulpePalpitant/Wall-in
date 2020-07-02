#include "items.h"


#include "../player/player.h"


// Trouve une coord valide pour spawner un item

bool Items::Find_Spawn_Location()
{
	GrdCoord plyer = P1.Get_Grd_Coord();
	GrdCoord itemCrd = {};

	// THE RANDOM WAY

	// Génère 1 donnée au hasard
	// Vérifie si chacune des conditions sont présentes
	// Sinon recommence

	// Peut reprendre la même donnée.
	// Si les conditions augmentent, ça prend de plus en plus de temps
	// Si les conditions diminuent, ça prend de moins en moins de temps
	// Si aucune conditions sont valides, ça crash

	// TAKE NO CHANCES

	// Élimine tout de suite les données qui sont pas valides
	// Choisis une au hasard dans celle qui restes

	// Même vitesse, peut importe le nombre de conditions. 
	// Est très rapide quand les conditions sont grandes, mais bcp plus lentes quand aucune conditions sont présentes
	// Prend du temps valider chacunes des conditions
	// Si utilisé en rafale, peut gagner bcp de temps

	// PAR ÉLIMINATION

	// Génère 1 donnée au hasard
	// Vérifie si chacune des conditions sont présentes
	// Sinon, la donnée invalide est ajouté à une liste
	// Et recommence

	// Ne Peut pas reprendre la même donnée.
	// Plus les conditions augmentent, plus ça va prendre du temps, mais sera plus rapide que LA RANDOM WAY
	// Si les conditions diminuent, ça prend de moins en moins de temps
	// Ne crash pas si aucunes conditions sont valides

	// ÉLIMINATION ET REGROUPEMENT 
	
	// Élimine une certaine partie des données qui ne sont pas valides
	// Génère 1 donnée au hasard en excluant ces données
	// Vérifie si le reste des conditions sont présentes
	// Sinon, ajoute l'élément dans une listes
	// Recommence

	// Mix entre PAR ÉLIMINATION et TAKE NO CHANCES, cette façont est un peux plus flexible
	// Selon la quantité d'élément qui sont exclus, peut avoir une vitesse stable
	// Peut être rapide quand ya rien
	// Peut être un peu plus rapide que TAKE NO CHANCES quand on atteint 50% de conditions invalides?
	// Tout dépend de la capacité à regrouper des exclusions





	// CONDITION #1

	// Liste 1: Exclut la colonne
	// Liste 2 exclut la proximité
	// Liste 3 exlut les autres items

	// Liste 4 Exclut tout les autres invalidés par les Links

	// CONDITION #2
	// CONDITION #3
	// CONDITION #42
	// CONDITION #5
	// CONDITION #16

	return true;
}
