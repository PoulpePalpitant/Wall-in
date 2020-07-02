#include "items.h"


#include "../player/player.h"


// Trouve une coord valide pour spawner un item

bool Items::Find_Spawn_Location()
{
	GrdCoord plyer = P1.Get_Grd_Coord();
	GrdCoord itemCrd = {};

	// THE RANDOM WAY

	// G�n�re 1 donn�e au hasard
	// V�rifie si chacune des conditions sont pr�sentes
	// Sinon recommence

	// Peut reprendre la m�me donn�e.
	// Si les conditions augmentent, �a prend de plus en plus de temps
	// Si les conditions diminuent, �a prend de moins en moins de temps
	// Si aucune conditions sont valides, �a crash

	// TAKE NO CHANCES

	// �limine tout de suite les donn�es qui sont pas valides
	// Choisis une au hasard dans celle qui restes

	// M�me vitesse, peut importe le nombre de conditions. 
	// Est tr�s rapide quand les conditions sont grandes, mais bcp plus lentes quand aucune conditions sont pr�sentes
	// Prend du temps valider chacunes des conditions
	// Si utilis� en rafale, peut gagner bcp de temps

	// PAR �LIMINATION

	// G�n�re 1 donn�e au hasard
	// V�rifie si chacune des conditions sont pr�sentes
	// Sinon, la donn�e invalide est ajout� � une liste
	// Et recommence

	// Ne Peut pas reprendre la m�me donn�e.
	// Plus les conditions augmentent, plus �a va prendre du temps, mais sera plus rapide que LA RANDOM WAY
	// Si les conditions diminuent, �a prend de moins en moins de temps
	// Ne crash pas si aucunes conditions sont valides

	// �LIMINATION ET REGROUPEMENT 
	
	// �limine une certaine partie des donn�es qui ne sont pas valides
	// G�n�re 1 donn�e au hasard en excluant ces donn�es
	// V�rifie si le reste des conditions sont pr�sentes
	// Sinon, ajoute l'�l�ment dans une listes
	// Recommence

	// Mix entre PAR �LIMINATION et TAKE NO CHANCES, cette fa�ont est un peux plus flexible
	// Selon la quantit� d'�l�ment qui sont exclus, peut avoir une vitesse stable
	// Peut �tre rapide quand ya rien
	// Peut �tre un peu plus rapide que TAKE NO CHANCES quand on atteint 50% de conditions invalides?
	// Tout d�pend de la capacit� � regrouper des exclusions





	// CONDITION #1

	// Liste 1: Exclut la colonne
	// Liste 2 exclut la proximit�
	// Liste 3 exlut les autres items

	// Liste 4 Exclut tout les autres invalid�s par les Links

	// CONDITION #2
	// CONDITION #3
	// CONDITION #42
	// CONDITION #5
	// CONDITION #16

	return true;
}
