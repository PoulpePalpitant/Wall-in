
#include "Header.h"



void SpawnBOT()
{
	if (Spawn_this_Cycle)
	{
		int BOT_Ind = 0;

		// G�n�ration d'une nouvelle COORD de spawnBOT
		do
		{
			if (Random_Boxside || !Spawn_Valide)
			{
				// On D�cide sur quel Bordure le Spawn aura lieu 			
				if (HorizontalSpawn)
					rand() % 2 == 0 ? BoxSide = LEFT : BoxSide = RIGHT;	// Spawn Horizontal
				else
					if (VerticalSpawn)
						rand() % 2 == 0 ? BoxSide = UP : BoxSide = DOWN;	// Spawn Vertical
					else
						BoxSide = rand() % 4;	//	Bordure random

				// Si on a SpawnMultiple de script�, de nature �same side� , on spawn les prochains Bots sur la m�me bordure
				//	en skipant la cr�ation de Boxside pour la prochaine boucle
				if (Same_Side)
					Random_Boxside = false;
			}

			if (Random_Spawn_COORD || !Spawn_Valide)	// Si le scripted spawn est pas valide, on fait une nouvelle coord
			{
				//	On d�cide quel sera la coordonn�e ou le Spawn aura lieu

				if (BoxSide % 2 == 0)
					Indice_Spawn_COORD = rand() % MaxSpawn_CoordinatesX;
				else
					Indice_Spawn_COORD = rand() % MaxSpawn_CoordinatesY;
			}

			NextSpawnXY = SpawnXY[BoxSide][Indice_Spawn_COORD];

			// VALIDATION SPAWN!	
			for (Blockthisshit = 0; Blockthisshit <= MaxNumBOTS - 1; ++Blockthisshit)	//	On check si le spawn actuel est block�
			{
				// V�rification: si un block �quivaut au cycle actuel de Bot_move. On ne peut pas cr�er de BOTS sur cette COORD.
				//
				//	NOTE IMPORTANTE:
				//

				// Faudra v�rifier si ta pas d�ja fait bouger tes BOTS durant ce cycle!

				if (Spawn_Block[BoxSide][Indice_Spawn_COORD][Blockthisshit] >= Current_BOT_MOVE_Cycle &&
					Spawn_Block[BoxSide][Indice_Spawn_COORD][Blockthisshit] < Next_BOT_MOVE_Cycle)
				{
					Spawn_Valide = false;
					break;
				}
			}

			if (Blockthisshit == MaxNumBOTS)
				Spawn_Valide = true;


		} while (!Spawn_Valide);


		// Cr�ation d'un BOT
		for (BOT_Ind = 0; BOT_Ind < MaxNumBOTS; ++BOT_Ind)	// Si on arrive au Nombre MAx de Bot????? Faudrait jamais utiliser la fonction 
		{
			if (BOTXY[BOT_Ind] == 0)
			{



				switch (BoxSide)
				{
				case 0: BOT_Direction[BOT_Ind] = DOWN;
				case 1:	BOT_Direction[BOT_Ind] = RIGHT;
				case 2:	BOT_Direction[BOT_Ind] = UP;
				case 3:	BOT_Direction[BOT_Ind] = LEFT;
				}

				BOTXY[BOT_Ind] = NextSpawnXY;

				// Faut bannir la Coordonn�e de Spawn pour le cycle pr�sent, si tu veux faire des double spawn sameside
				for (int temps = 0; temps <= MaxNumBOTS - 1; ++temps)
					if (Spawn_Block[BoxSide][Indice_Spawn_COORD][temps] == 0)
					{
						Spawn_Block[BoxSide][Indice_Spawn_COORD][temps] = Current_Spawn_Cycle;
						break;
					}
				break;
			}
		}

		Goto_Coordinnates(CoordX, CoordY, BOTXY[BOT_Ind]);

		cout << 'B';// BOT_Sym[BoxSide][0]; // on cout le reste apres quand ta trouv� comment. Apr�es une version jouable?


		//CR�ATION SPAWN BLOCK 				
		// Ces trucs suivent la m�me logiques que les SpawnCoord.  Haut/Bas - Gauche/Droite
		int First_Spawn_Intersection[2] = {};// from bot to side
		int Static_Coord_First_Block[2] = {};	// Distance du BOT actuel au coin de la bordure perpendiculaire.
		int Block_Side_StaticAxis[2] = {};//nowere
		int Block_Side[2] = {};//perp_Sp_Blck.spwns_Side[A] = UP;		// Bordure ou il faut blocker les spawns :side 0 =  Gauche ou Haut.   Side 1 = Droite ou bas
		int Block_SideXY[2] = {};//				
		int Next_Closest_Spawn[2] = {};//
		Time Min_Time_Impact[2] = {};//
		bool NO_Block[2] = {};//
		int COORD_Ind[2] = {};//
		int Intersection;// nowere
		int Cycles_Before_Impact[2] = {};//
		int Bot_Move_Axis;//
		int Side;//
		bool Direction_Negatif_Ou_Positif = false;
		bool Spawn_Found = false;//

		// Permet de passer soit de haut en bas, ou de bas en haut de le tableau de spawn suivant pour inscrire les bonnes valeurs.
		//	Permet aussi de d�terminer dans quel direction le spawn le plus proche est.
		if (BoxSide == DOWN || BoxSide == RIGHT)
			Direction_Negatif_Ou_Positif = true;	//	Si n�gatif, la direction sera vers la gauche, ou vers le haut





		//////////////////////////////////////////////////////JE DOIS CLEANER TOUTE CETTE MERDE
		if (BoxSide % 2 == 0)
		{
			MaxSpawnBlocks = MaxSpawn_CoordinatesY;
			Bot_Move_Axis = ShipMoveY;

			// Donne la premi�re COORD perpendiculaire de spawn qui pourrait cr�� une colision si un bot apparaissait
			for (Side = 0; Side < 2; ++Side)
			{
				if (Side == 0)
				{
					Block_Side[Side] = LEFT;

					First_Spawn_Intersection[Side] = CoordX - spawn.limit[LEFT];

					if (BoxSide == 0)
						Static_Coord_First_Block[Side] = First_Spawn_Intersection[Side] + spawn.limit[UP];
					else
						Static_Coord_First_Block[Side] = spawn.limit[DOWN] - First_Spawn_Intersection[Side];

					Block_SideXY[Side] = (spawn.limit[LEFT] * CompresseurXY) + Static_Coord_First_Block[Side]; //ex: x= SpawnLeft y= Min_Dist_Side
				}
				else
				{
					Block_Side[Side] = RIGHT;
					First_Spawn_Intersection[Side] = spawn.limit[RIGHT] - CoordX;

					if (BoxSide == 0) // fix this shit.....
						Static_Coord_First_Block[Side] = First_Spawn_Intersection[Side] + spawn.limit[UP];	// CoordX de l'endroit ou viens de spawner le bot
					else
						Static_Coord_First_Block[Side] = spawn.limit[DOWN] - First_Spawn_Intersection[Side];

					Block_SideXY[Side] = (spawn.limit[RIGHT] * CompresseurXY) + Static_Coord_First_Block[Side];
				}

				// Faudrait pas mettre Spawndown?
				if (Static_Coord_First_Block[Side] > box.limit[DOWN] || Static_Coord_First_Block[Side] < box.limit[UP])	// si la distance minimal d�passe la distance max des spawn sur le boxside
				{
					NO_Block[Side] = true;				// on ne block rien du tout
					continue;
				}


				// Si le BlockSideXY n'est finalement pas une spawn Coord, On utilise ClosestSpawn pour trouver le prochain
				// Si le spawn le plus proche n'est pas � droite, vers le positif, mais bien � gauche, vers le n�gatif...
				if (Direction_Negatif_Ou_Positif)
					Next_Closest_Spawn[Side] = Block_SideXY[Side] - Bot_Move_Axis;
				else
					Next_Closest_Spawn[Side] = Block_SideXY[Side] + Bot_Move_Axis;
			}

		}
		else
		{
			MaxSpawnBlocks = MaxSpawn_CoordinatesX;
			Bot_Move_Axis = ShipMoveX;

			for (Side = 0; Side < 2; ++Side)
			{

				// Donne la premi�re COORDXY  sur les deux bordure de spawn qui peut cr�er un bot qui ferait une colision, 
				//et qu'on doit blocker
				if (Side == 0)	// quand c,est = � 0: on suit la logique Up or left
				{
					Block_Side[Side] = UP;
					First_Spawn_Intersection[Side] = CoordY - spawn.limit[UP];	// Nombre de Botmovecycle avant un impact

					if (BoxSide == 3)
						Static_Coord_First_Block[Side] = spawn.limit[RIGHT] - First_Spawn_Intersection[Side];
					else
						Static_Coord_First_Block[Side] = First_Spawn_Intersection[Side] + spawn.limit[LEFT];	// La distance possible de spawn qui causerait un impact. Sur l'axe l'at�ral au bot 

					Block_SideXY[Side] = (Static_Coord_First_Block[Side] * CompresseurXY) + spawn.limit[UP];	//  y = SpawnUP X= l'autre affaire

				}
				else
				{
					Block_Side[Side] = DOWN;
					First_Spawn_Intersection[Side] = spawn.limit[DOWN] - CoordY;

					if (BoxSide == 3)
						Static_Coord_First_Block[Side] = spawn.limit[RIGHT] - First_Spawn_Intersection[Side];// CoordY =ou le bot viens de spawner. On assigne maintenant �a � une valeure de X
					else
						Static_Coord_First_Block[Side] = First_Spawn_Intersection[Side] + spawn.limit[LEFT];

					Block_SideXY[Side] = (Static_Coord_First_Block[Side] * CompresseurXY) + spawn.limit[DOWN];
				}


				if (Static_Coord_First_Block[Side] > box.limit[RIGHT])	// SIDENOTE: �a se peut que just 1 bordure soit block�. Ou m�me aucune. On le note ici
				{
					Block_Side[Side] = false;
					continue;
				}
				//  On utilise ClosestSpawn pour v�rifier si la COORD est une COORD de SPawn
				// Si le spawn le plus proche n'est pas � droite, vers le positif, mais bien � gauche, vers le n�gatif...
				// Le closest spawn se trouvera � gauche
				if (Direction_Negatif_Ou_Positif)
					Next_Closest_Spawn[Side] = (Block_SideXY[Side] - Bot_Move_Axis * CompresseurXY);
				else
					Next_Closest_Spawn[Side] = (Block_SideXY[Side] + Bot_Move_Axis * CompresseurXY);


			}
		}




		// Ceci ajuste la distance minimale et la coordonn�e du premier spawn � blocker

		for (Side = 0; Side < 2; ++Side)
		{
			if (NO_Block[Side] == true)
				continue;

			for (int COORD = 0; COORD < MaxSpawnBlocks; ++COORD)
			{
				// Ceci ne marche pas. Il faut comparer uniquement l'axe de d�placement du BOT!!!
				// Ceci ne marche pas. Si on descend dans le tableau, il faut comparer alors dans lautre sens!!!!

				// Voici les deux conditions qui permettent de trouver la COORDXY du premier Spawn a bloquer
				// C'est though � catcher alors voici une illustration: 
				//  SpawnXY = 1	(Le premier spawn  � blocker, les S sont d'autres SPawnXY)							
				//	Block_Side = B	(La Coord de Bordure � ajuster)			
				//	Closest_Spawn = C	(La Coord de Bordure a ajuster, + l'intervalle qui s�pare 1 spawn)



				//	Si on va Blocker de droite � gauche (Direction_Negatif_Ou_Positif = true)

				//	1:			S---C-----1------B--S
				//  			(1 > C)		(1 <= B)


				// Si on va blocker de gauche � droite	(Direction_Negatif_Ou_Positif = false)

				//	2:			S---B-----1------C--S
				//				 (1 >= B)		(1 < C)


				if (Direction_Negatif_Ou_Positif)
					if (SpawnXY[Block_Side[Side]][COORD] <= Block_SideXY[Side]
						&& SpawnXY[Block_Side[Side]][COORD] > Next_Closest_Spawn[Side])
						Spawn_Found = true;

				if (!Direction_Negatif_Ou_Positif)
					if (SpawnXY[Block_Side[Side]][COORD] < Next_Closest_Spawn[Side]
						&& SpawnXY[Block_Side[Side]][COORD] >= Block_SideXY[Side])
						Spawn_Found = true;

				if (Spawn_Found)
				{

					// Min DistSide est useless bien franchement
					if (Block_SideXY[Side] != SpawnXY[Block_Side[Side]][COORD])
					{
						//Le first spawn intersection correspond au X ou Y du SpawnXY qu'on va block
						// Cette merde on l'utilise plsu apr�es
						/*// On ajuste �galement la Distance minimale
						Static_Coord_First_Block[Side] = SpawnXY[Block_Side[Side]][COORD] / CompresseurXY;	// Si la Min_Dist_side est sur l'axe des X

						if (Bot_Move_Axis == ShipMoveY)// Si la Min_Dist_side est sur l'axe des Y
							Static_Coord_First_Block[Side] = Block_SideXY[Side] - Static_Coord_First_Block[Side] * CompresseurXY;*/
							/*

							First_Spawn_Intersection[Side] = CoordX - spawn.limit[LEFT];
							Static_Coord_First_Block[Side] = spawn.limit[DOWN] - First_Spawn_Intersection[Side];
							Block_SideXY[Side] = (spawn.limit[LEFT] * CompresseurXY) + Static_Coord_First_Block[Side];*/

							// pas besoin de �a si tu set tes affaires comme il faut :P
							//			motherfucker....
							// je me parle � moi m�me. Send Help!     and nudes.


						switch (BoxSide)
						{
							// juste pour l'exemple : ex boxside 2

							// Faut isoler le Y qu'on veut
							CoordX = SpawnXY[Block_Side[Side]][COORD] / CompresseurXY;
							Static_Coord_First_Block[Side] = SpawnXY[Block_Side[Side]][COORD] - CoordX * CompresseurXY;
							// Voil�. Ensuite on fait le calcul pour trouver la DISTANCE minimale � parcourir pour l'intersection
							Cycles_Before_Impact[Side] = spawn.limit[DOWN] - Static_Coord_First_Block[Side];





						}





					}

					// On enregistre l'indice de cette Coordonn�e
					COORD_Ind[Side] = COORD;

					// On change le BlockSide pour la COORD SPawnXY #1
					Block_SideXY[Side] = SpawnXY[Block_Side[Side]][COORD];


					Spawn_Found = false;
					break;
				}

			}

		}




		// BOT SPAWN DELAI BEFORE MOVING TO OUR DOOM

		// Si tu veux ajouter un D�lai avec un Q visuel.	T'ajuste � ajouter : int DELAY = 3 * BOT_Move_Cycle;
		// Apres dans la section BotMove: EX:  BotDelay[i] = 3;		if( BotDelay[i] >0) 
																		//BotDelay[i]--; cout << un Symbole de Square genre!!!!
		//esle -------> On bouge le BOT!!!!


		// On Calcul le temps minimal que �a prend pour un impact
		for (int Side = 0; Side < 2; ++Side)	//	Min_Dist_side[Side]( * 1) ( 1= Vitesse du Bot) * BOT_Move_Cycle
		{
			if (NO_Block[Side] == false)
				Min_Time_Impact[Side] = Current_BOT_MOVE_Cycle + Cycles_Before_Impact[Side] * BOT_Move_Cycle;
		}

		//	Enregistrement de chacun des Cycles lors duquel les SPawnCoord seront Block�s!

		for (Side = 0; Side < 2; ++Side)	// side = Left; Side < Right;
		{
			if (NO_Block[Side] == false)
				for (In COORD = COORD_Ind[Side]; COORD < MaxSpawnBlocks; ++COORD)
				{
					//if (SpawnXY[Block_Side[Side]][COORD])

					for (Time Block = 0; Block < MaxNumBOTS; ++Block)
					{
						// On cherche dans le tableau si un block ( une intervalle de temps) est vide

						if (Spawn_Block[Block_Side[Side]][COORD][Block] == 0)
						{
							// On test le spawn block!
							Goto_Coordinnates(CoordX, CoordXY, SpawnXY[Block_Side[Side]][COORD]);
							cout << Min_Time_Impact[Side];


							Spawn_Block[Block_Side[Side]][COORD][Block] = Min_Time_Impact[Side];
							Spawn_Block_Indice[BOT_Ind][Block_Side[Side]][COORD] = Block;
							break;
						}

						// le prochain spawn qui sera block� correspond	au temps que �a va prendre pour le bot � s'y rendre


					}

					Min_Time_Impact[Side] += BOT_Move_Cycle * Bot_Move_Axis;	// l� il se d�place de un
						// Sinon tu peux changer �a pour genre BOTSpeed = Bot_Move_Axis ou 1
						// Min_Time_Impact[Side] +=  Bot_Move_Cycle * (Bot_Move_Axis / BotSpeed)
						// VOila!!			
						// Pour l'instant, change pas la vitesse d'un bot pour qu'un d�placement permettrait de skip un spawn
						// �a viendrais tout fucker!!!

					// On descend le tableau si le Bot se dirige vers des spawns de valeurs d�croissantes
					if (Direction_Negatif_Ou_Positif)
						COORD -= 2;

					if (COORD <= -2)
						break;
				}
		}


		// Si le spawn est script�, on check si on en fait plus qu'un spawn d'une shot.

		if (Scripted_Spawn)
		{
			Num_Of_Spawns--;

			if (Num_Of_Spawns > 0)
				SpawnBOT();	// fuck je devrais r�inisialiser mes shit non?
			else
				Scripted_Spawn = false;
		}

		Spawn_Valide = false;
		Spawn_this_Cycle = false;
		Total_BOTS_Spawned++;

		// Variables � r�initialiser 

		for (int boogie = 0; boogie < 1; ++boogie)
		{

		}




		/*int Min_Dist_side[2] = {};
		int Block_Side[2] = {};
		int Block_Side_StaticAxis[2] = {};
		int Block_SideXY[2] = {};
		int Min_Time_Impact[2] = {};
		bool NO_Block[2] = {};
		int Closest_Spawn[2] = {};
		int COORD_Ind[2] = {};

		int Bot_Move_Axis, Bot_Static_Axis;
		double Ajustement;
		int Side;
		bool Indice_Decroissant = false;*/



		HorizontalSpawn = false;
		VerticalSpawn = false;
		Random_Spawn_COORD = false;
		Random_Boxside = false;
		NextSpawnXY = 0;

	}		// FIN SPAWN BLOCK et Cr�ation de BOTS
}	//	fin spawn fonction
