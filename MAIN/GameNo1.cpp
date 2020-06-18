/*

Auteur		: Laurent
Description	:	Cette version du Wall Game fonctionne avec l'utilisation d,une variable supplémentaire de Link
				Nommé ALPHA. Ces ALPHALink désigne le premier VitalLink d'une Structure. Il ne servent virtuellement à rien
				et c'est pourquoi je vais les purger
Version		: 1.0

*/



#include "global.h"
//#include "GameNo1_Spawn_BOT.cpp"

using namespace std;


//	* ******************** *
//	* DECLARATION FONCTION *
//	* ******************** *


void Swag_Animation(Colors col1, Colors col2, Colors col3);	// So pretty...
void Swag_Animation2(Colors col0, Colors col1, Colors col2, Colors col3, Colors col4, Colors col5);	// So pretty...
void UnSwagidy_Animation();	// So Unpretty... :(

void Change_Color(int c) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
// Initialisation des coordonnées d'où vont spawner les bots
void Create_New_Spawn_Coord(int ShipMoveX, int ShipMoveY, int SpawnXY[][MaxNumBOTS]);
int Search_Coordinnates(int Link[], int Y, int XY);
void Goto_Coordinnates(int& X, int& Y, int XY);
void Get_Coordinnates(int& X, int& Y, int XY);	
int Compress_Cursor_XY();					// Compresse la valeur en x et en y du curseur en une seule valeur entière (x * 10000 + y)
int Compress_XY(int CoordX, int CoordY);	// Compresse une valeur en x et en y en une seule valeur entière (x * 10000 + y)
int Find_a_Links_VitalLink(int CoordXY);	// Trouve le VL d'un Link	


// Basic shit
Axe Axe_Entre_Deux_Coord(int Coord1, int Coord2);							// Donne l'axe de distance séparant deux coordonnées
Polarisation Polarisation_Selon_Direction(Direction direction);				// Donne la polarisation de déplacement positif(+1) ou négatif(-1) dans la console selon une direction
Polarisation Polarisation_Selon_Deux_Coord(int CoordDepart, int CoordFin); // Donne la polarisation d'une direction(celle que sous-tend la distance entre depart et fin)
Direction Direction_Entre_Deux_Coord_Selon_Axe(int CoordDepart, int CoordFin, Axe axe);// Donne la direction d'une coordonnée par rapport à une autre, selon l'axe des X ou l'axe des Y
void Reset_Tableau_Unidimensionelle_A_Une_Valeur_confortable_pour_les_gens_qui_regardent_leHockey_le_dimanche_avec_une_tit_bier(int Tableau[], int MAX);
void Reset_Tableau_Tridimensionelle_avec_une_tite_sauce_brune_a_coté_pis_des_patates(int Tableau[4][MaxSpawn_COORD][MaxNumBOTS]);
void Reset_Everything___or_almost();										// reset plein de valeurs pour restart une game		

// MATH STUFF
int Intervalle(int min, int max); // Retourne la différence d'un minimum à un maximum

// WALLS AND SHITS
void Create_Wall(int CoordX, int CoordY, char WallSym);				// Création et affichage d'1 mur
void Creation_1_mur(int CoordXY);									// Creation d'un unique mur selon sa coordonnée compressé
void Destroy_WALL(int CoordX, int CoordY);							//	DESTRUCTION ET EFFACEMENT D'UN MUR
void Destruction_1_mur(int CoordXY);								// Efface un mur dans le tableau de WAlls
void Creation_or_Destruction_Walls_Btwn_Links(int CoordDepart, int CoordFin, Time Delay = 4, bool Creation = false);	// Créer ou détruit les murs entre deux Coords

// TEMP WALL LOGIC
int Search_For_Available_Link(int in);
int Search_For_Available_VitalLink(int in);


// SPAWNS & BOTS
void Block_Front_Spawn(int FrontBoxside, int coord, int Nb_Bot);	// Permet de Blocker le spawn en vis-à-vis de spawner d'autres BOTS
void Front_BOT_Boxside(int & Boxside);								// Donne la bordure en face d'un bot
void Affi_ou_Effa_BOT_Esc_Door(int Boxside, int& CoordX, int& CoordY, bool Effacer = false);	// Affiche la porte de sortie d'un BOT
void MAX_BOTS_Steps_for_each_border(int LimitUP, int LimitLEFT, int LimitDOWN, int LimitRIGHT, int Box_to_Spawn);	// Donne la quantité de déplacement Max pour chacune des bordures de spawn de BOTS
int Total_BOT_Steps_Before_Exit(int Boxside);									// Donne la quantité de déplacement qu'un bot doit parcourir avant de sortir de la BOX
void BOT_Progression_Color(Colors & Color, int NumStepsLeft, int Max_Steps);	// Changela couleur d'un BOT selon son avancé
void Design_BOT(BOT_Design &BOT_design, int BOT_Ind, int BoxSide);				// Assignation des characters d'affichage du BOT. son apparence sera différente selon sa direction 
void Design_BOT_Warning(char& wrngDesign, int BoxSide);							// Le design du Warning qui apparaît avant un bot
void UI_AF_BOT_Warning(int Ind);												// Affiche le symbole du warning !
int UPD_BOT_Warning_Cycles(int Ind);											// Update le nombre de cycle restant avant pour warner le player qu'un bot va spawner
void Afficher_ou_Effacer_BOT(int BOT_In, bool Effacer);							// Affiche un BOT
void Afficher_BOT_Design_2(int BOT_In, char Sym);								// Affiche bot selon son nb de char
void Spawn_Crd_Interv(int min, int max, Sp_CoordIn &coordIn);// ACTIVE L'INTERVAL DE SPAWN COORD POUR LE PROCHAIN SPAWN

// HERO 
bool HeroTakeDamage(HERO& hero);		// Quand le player reçoit du dégât (un bot atteint la bordure ou autre)
void UPD_Hero_Color(int Health);		// change la couleur du joueur selon sa vie
void UPD_Hero_Damage_Animation(int health);		// Animation de dégât
void Hero_Damage_Animation3hp();	// ANIMATION de dégât quand le héro possède maintenant 3 de vie(il en avait 4 avant )
void Hero_Damage_Animation2hp();	// ANIMATION de dégât quand le héro possède maintenant 2 de vie(il en avait 3 avant )
void Hero_Damage_Animation1hp();	// ANIMATION de dégât quand le héro possède maintenant 1 de vie(il en avait 2 avant )
void Hero_Damage_Animation0hp();	// ANIMATION de dégât quand le héro possède maintenant 0 de vie(il en avait 1 avant )
void UPD_Hero_Heart(HERO& hero);	// Affiche la vie du joueur 
void UI_AF_Hero_Heart(Coord crd, string Layer[], Colors clr);	// Affiche la vie du joueur sous la forme d'un coeur

// DESTRUCTION
void Destroy_BOT_and_Spawn_Blocks(int In_Bot, int Front_Coord);
bool Find_Parent_Btwn_Links(int CoordLeft, int CoordRight, int& VL_Left, int& VL_Right, bool& isVital); // Trouve lequel de deux Link est Vital pour l'autre
void Find_CoordLeft_AND_Right_of_BOT_Impact(int DirectionBOT, int& CoordLeft, int& CoordRight);			// Trouve les deux coord de link à gauche et à droite du bot qui à impacté un mur
void Structure_Destruction_n_Stuff(int Destruction, int VL, int VL_Origin, bool DestroyLeft_Right, bool One_Link_Destruction);	// Permet de détruire les structures
void PreDestruction_par_Wall_Transfer();																// La destruction de murs et de liens par le joueur. Si le joueur fait un tir quand il se trouve sur un '.' boute
void PreDestruction_par_BOT_Impact(int DirectionBOT, int CoordXY);										// Trouve deux Coord, et détermine de quel côté on brise la chaine de murs

// AFFICHAGES ET INTERFACE

void Clean_Char(int CoordX, int CoordY);						// Affiche un charactère vide ' ' à sune coordonnée
void UI_Delete_String(int CoordX, int CoordY, int Length);		// Efface une suite de charactère dans la console
void UI_DE_Texte_Area(int CoordX, int  CoordY, int col, int lig);		// Delete une superficie de la box(Start en haut a gauche)
void UI_Eff_Texte_Area_And_nothing_else(int CoordX, int  CoordY, int col, int lig);
void UI_Aff_String(int CoordX, int CoordY, string txt, Time time = 0, Colors color = WHITE);
void UI_Aff_Char(int CoordX, int CoordY, char Sym, Time time= 0, Colors color = WHITE);
void UI_Afficher_Box(int CoordX, int CoordY, int NBLIG = 3, int NBCOL = 3, Colors Couleur = BRIGHT_WHITE, bool Effacer = false, Time time = 0); // L' affichage D'une BOX de 3x3(par défaut) autours d'un point central
void UI_Aff_ET_Del_Char(int CoordX, int CoordY, char Sym, Time time, Colors color = WHITE);	// Affiche un char et l'efface ensuite
void UI_Display_StatsName();			// Affiche les titres des stats
void UI_Update_TimerAndStats();			// Affiche les stats
void UI_Msg_Animation_1(int CoordX, int CoordY, string titre, Time time = 10, Colors color = LIGHT_RED );			// Affiche un msg insistant
void UI_Aff_Keyboard(int CoordX, int CoordY);					// Affiche un sweet Keyboard
void UI_Msg_Stop_it(int CoordX, int CoordY, string Message);	// Affiche un msg, plutôt insistant
void EV_MsgAf_Stop_Bot(int CoordX, int CoordY, bool Effacer);	// Affiche ce le joeur doit faire pour survivre
void EV_MsAF_Got_Out();					// knowledge is power


// EVENTS																													// SPECIAL EVENTS
void EV_Box_Trap();				/// Le player est pris dans une boite et doit utiliser WASD pour sortir
void EV_Create_Vertical_Structure(int GridXY, int L, int V, int NbWalls);			// Création d'une tit structure pour le début de la game
void EV_Create_Horizontal_Structure();			// Création d'une tit structure pour le début de la game
void EV_Create_Tutorial_Structure();
void EV_Change_BOT_Speed(int speed);			// Change la vitesse des bots


// EVENT DE MESSAGE
void EV_MsgAF_WillHurt();				// THIS WILL HURT
void EV_MsgAF_You();					//		YOU
void EV_MsgAF_Must();					//		MUST
void EV_MsgAF_STOPIT();					//	  STOP IT
//--
void EV_Msg_AF_WasdTuto();
void EV_Msg_DE_WasdTuto();
void EV_MsgAf_Del_Touche_Tir(int CoordX, int CoordY, bool Effacer = false);	// Affiche les touches de tir
void EV_MsgAf_Touche_Mouvement(int CoordX, int CoordY);		// Affiche les touches de mouvements WASD
//--

//Fonctions Levels!!!
void Move_BOTS();	// On bouge les BOTs
void SpawnBOT();	//	Permet de Spawner des bots et blocker certains spawn pour éviter des colisions
void Chck_Event_trigger(Time Current_Time, int BOTSpwnedTOT);			// Vérifie si un event est triggered
void LVL1_Events(Time Current_Time, int BOTSpwnedTOT);					// Les évènements du lvl 1
void LVL1_Msg_Events(Time Current_Time, int BOTSpwnedTOT);


// GESTION DU TEMPS
const unsigned int Time_Based_Spawn(const int Time); // Mon cheat pour utiliser une switch conditionnelle
void Check_Level_Script(int LVL_Script);
void Check_Spawn_Cycle();	//On vérifie on est sur quel cycle de spawn
void Check_BOT_Cycle();		// On vérifie on est sur quel cycle de bot move


void Level_1_Script(); void Level_1_Spawn_Script(int Spwn_cycleTOT);
void Level_2_Script(); void Level_2_Spawn_Script();
void Level_3_Script(); void Level_3_Spawn_Script();
void Level_4_Script(); void Level_4_Spawn_Script();
void Level_5_Script(); void Level_5_Spawn_Script();
void Level_6_Script(); void Level_6_Spawn_Script();
void Level_7_Script(); void Level_7_Spawn_Script();
void Level_8_Script(); void Level_8_Spawn_Script();

// Condition de Victoire de niveau : Tuer tout les bots Restants1	
void Finish_Them_to_Win(int BOTXY[], int& EndLevel);

bool restart = false;
char reset = 0;

// J'pense que je vais crisser toute les variables en dehors du main....
// J'pense que je vais devoir tout restructurer et pu rien mettre en dehors du main
int main()
{
	do
	{
		//Reset tout les variables pour un restart

		//On revient à la couleur blanc pâle
		Change_Color(7); clrscr();	Reset_Everything___or_almost();
	
		restart = reset = BOT_Escape = 0;		// si tu veux vraiment mettre un piton retry. tu dois TOUT réinitisialiser les tableaux: 45min environ
		hero.health = 2; hero.clr = LIGHT_GREEN;
		Spwn_cycleTOT = 0;
		Initialize_Level = true;

		// Ré-Initialisation du temps
		Current_time = Current_Spawn_Cycle = Current_BOT_MOVE_Cycle = 0;

		// CRÉATION DES SPAWN COORD, selon les dimensions de la BOX et des distances de mouvement du ship	
		// Inititialisation à false des fronts spawn block
	
		int cul = 0;
		for (size_t i = 0; i < 4; i++)
			for (size_t j = 0; j < MaxSpawn_COORD; ++j)
				for (size_t k = 0; k < MaxNumBOTS; ++k)
					front_Spawn_Block[i][j][k] = {};

		// Initialize spawn block à -1
		Reset_Tableau_Tridimensionelle_avec_une_tite_sauce_brune_a_coté_pis_des_patates(Spawn_Block);

		// Section tests!/////////////////////////////////////////////////////Section tests!///////////////////////////////////////////////////

	
		




		_getch();

		
		//Section tests!/////////////////////////////////////////////////////Section tests!///////////////////////////////////////////////////*/




		// CHANGE LA DIMENSION DE LA SCREEN
		// ********************************
		HWND console = GetConsoleWindow();
		RECT ConsoleRect;
		GetWindowRect(console, &ConsoleRect);		// 817x 911  ou 713x807		// 85 par 53
		MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 713, 807, TRUE);
		MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 713, 983, TRUE);
		
		
		

		//short conWidth = get_wColumn();

		// CHANGE LE CURSEUR
		// ********************************
		HANDLE hout; //handle to the console			// What is a handle? who knows!?
		CONSOLE_CURSOR_INFO cursor;						//cursor struct
		hout = GetStdHandle(STD_OUTPUT_HANDLE);			//set our handle for output			
		cursor.bVisible= false;							// rend le curseur unvisible
		cursor.dwSize = 1;								// et tr`s petit
		SetConsoleCursorInfo(hout, &cursor);			//pass the cursor info structure and our handle
														//to this function and we're done :)
		
		// LE TITRE DU JEU
		// ***************
		LPCTSTR GameName = "Stop? Stop! ";
		SetConsoleTitle(GameName);

		// LA FONT DES CHARACTÈRES DE LA CONSOLE
		// **************************************
		HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
		PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX();
		lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);

		GetCurrentConsoleFontEx(out, 0, lpConsoleCurrentFontEx);	// Font actuel

		// FONT STUFF										// SETTINGS ACTUELS APOUR LA CONSOLE
		lpConsoleCurrentFontEx->cbSize = 84;				//cbSize = 84 
		lpConsoleCurrentFontEx->nFont = 0;					//nFont = 0 
		lpConsoleCurrentFontEx->dwFontSize = { 8 , 16 };	//dwFontSize = { X = 8 Y = 16 }	y = la bonne size
		lpConsoleCurrentFontEx->FontFamily = 54;			//FontFamily = 54
		lpConsoleCurrentFontEx->FontWeight = 400;			//FontWeight = 400
		
		// FONT NAME										
		lpConsoleCurrentFontEx->FaceName[0] = 'C';			//FaceName = 0x00000196bcd8caa4 L"Consolas"
		lpConsoleCurrentFontEx->FaceName[1] = 'o';
		lpConsoleCurrentFontEx->FaceName[2] = 'n';
		lpConsoleCurrentFontEx->FaceName[3] = 's';
		lpConsoleCurrentFontEx->FaceName[4] = 'o';
		lpConsoleCurrentFontEx->FaceName[5] = 'l';
		lpConsoleCurrentFontEx->FaceName[6] = 'a';
		lpConsoleCurrentFontEx->FaceName[7] = 's'; 
		
		for (size_t i = 8; i < 32; i++)	
			lpConsoleCurrentFontEx->FaceName[i] = '\0';			// Dumbshit. Je sais pas comment reset ce type :(
		

		SetCurrentConsoleFontEx(out, 0, lpConsoleCurrentFontEx);
		delete lpConsoleCurrentFontEx;
		

		// La dimension de la console en CASE de charactère
		// ************************************************

		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		con = GetLargestConsoleWindowSize(h);


		//Section tests////////////////////////////////////////////////////

		// RNG 
		unsigned long long t = time(0);
		srand(t); int position = rand();


		//DÉCOMPTE! 
		countdown = 0;	//Ceci annule le countdown , pour arrêter de me faire perdre du temps
		if (countdown > 0)
		{
			HeroX = 30;
			HeroY = 12;

			gotoxy(HeroX, HeroY);
			cout << "Ready?";
			_getch();

			gotoxy(HeroX, HeroY);
			clreol();


			for (int i = 5; i >= 1; i--)
			{
				gotoxy(HeroX, HeroY);
				cout << i << "...";
				Sleep(countdown);

				countdown -= countdown / 2;
			}

			Change_Color(12);

			while (countdown > 5)
			{
				gotoxy(HeroX, HeroY);
				cout << "GO!";
				Sleep(countdown);

				gotoxy(HeroX, HeroY);
				clreol();
				Sleep(countdown);

				countdown -= (countdown / 5);
			}

			Change_Color(7);
		}


		cout << fixed << setprecision(2);
		Level_1_Script(); // On initialise le niveau 1!
		UI_Display_StatsName();	// Affiche les stats le gros

		//GAME START! /*/*/*/*/*/*/*/*/*/*/*/*/*/*//*/*/*/*/*/*/

		string Tutorial = "Normal Start?";
		UI_Aff_String(15, 15, Tutorial, 15);
		UI_Aff_String(12, 17, "Yes/no : (Y/N)", 15);
		char c;
		while (_kbhit())
			_getch();

		do
		{
			c = (toupper(_getch()));

		} while (c != 'Y' && c != 'N');

		clrscr();

		if (c == 'N') FastStart = true;

		
		//	AFFICHE JOUEUR
		HeroX = box.limit[RIGHT] / 2;	HeroY = box.limit[DOWN] / 2; gotoxy(HeroX, HeroY);	cout << AllPlyrSym[4]; 
		//UI_Aff_String(HeroX - 1, HeroY - 4, "YOU", 100, LIGHT_GREEN);
		//UI_Aff_Char(HeroX, HeroY - 3, '|', 100, BRIGHT_WHITE);
		//UI_Aff_Char(HeroX - 1, HeroY - 2, '\\', 100, BRIGHT_WHITE);
		//UI_Aff_Char(HeroX + 1, HeroY - 2, '/', 100, BRIGHT_WHITE);Sleep(1000);
		Sleep(1000); UI_Aff_String(HeroX - 1, HeroY - 4, "   ");

		while (loop)
		{
			// Autre réinitialisation de variables de merde
			mouvement = action = ii = i = input = 0;
			Hero_Move = true;
			




			//Créer un ghost qui suit le Ship a chaque mouvements! Just for show!
			// J'ai disable le ghost pour pas me faire chier avec mes tests
			/*
			do
			{
				if ((_kbhit()))
					input++;

				i = 0;


				if (x < GhostX)
					GhostX--;

				if (x > GhostX)
					GhostX++;

				if (y < GhostY)
				{
					GhostY--;
					UpDown = 1;
				}

				if (y > GhostY)
				{
					GhostY++;
					UpDown = -1;
				}

				if (y == GhostY)
					UpDown = 0;

				gotoxy(GhostX, GhostY);
				cout << Ship;


				Sleep(20);

				//Clear
				cout << "\b ";
				gotoxy(botX[i], botY[i] + UpDown);
				cout << " ";

			} while (input < 1);
			*/

			Check_Level_Script(LVL_Script);
			Check_Level_Script(LVL_Script);		// Ça débug le temps somehow
			UPD_Hero_Heart(hero);

			while (_kbhit())
				_getch();


			// Quand le Player est idle on reste ici
			do
			{
				// INITIALISATION DU TEMPS
				Timer_Start = clock();

				Check_Level_Script(LVL_Script);

				if ((_kbhit()))
					input++;

				// Incrémentation du temps
				Timer_End = clock();
				Time_Passed = Timer_End - Timer_Start;
				Current_time += Time_Passed;


				UI_Update_TimerAndStats();

				// LA GAME FINIS MAINTENANT
				if (BOT_Escape)
					break;

			} while (input < 1);

			// LA GAME FINIS MAINTENANT
			if (BOT_Escape)
				break;




			//Enregistre une touche de mouvement
			mouvement = toupper(_getch());

			// Press Spacebar to pause
			if (mouvement == ' ')
			{
				_getch();
				mouvement = 0;
			}
			if (mouvement == 'r')
				BOT_Escape = true;
			
			
			//Enregistre une touche d'action(tirer)

			if (GetKeyState(VK_LEFT) & 0x8000)
			{
				action = VK_LEFT;	 BlastFin = box.limit[LEFT];	X_ou_Y = x;
			}

			if (GetKeyState(VK_RIGHT) & 0x8000)
			{
				action = VK_RIGHT;	 BlastFin = box.limit[RIGHT];	X_ou_Y = x;
			}

			if (GetKeyState(VK_UP) & 0x8000)
			{
				action = VK_UP;		BlastFin = box.limit[UP];		X_ou_Y = y;
			}

			if (GetKeyState(VK_DOWN) & 0x8000)
			{
				action = VK_DOWN;	BlastFin = box.limit[DOWN];		X_ou_Y = y;	//Le Blast sera vertical Si LeftRightB = false
			}

			//		Si le joueur se trouve sur un boute et tir dans une autre direction que les murs qui y sont relié
			//		alors le link sera détruit, mais un tir aura tout de même lieu. Sinon un simple backstep aura lieu?					pew
			
			if (Le_Boute)						//	ex					O----O----@			tir a droite	=	O---O    @           ----------												
				Wall_Transfer = true;			//		'@' = joueur			
			else
				Wall_Transfer = false;
			

			if (action != 0)
			{
				if (X_ou_Y)		//Si le tir est horizontal
				{
					NSWE = HeroX;									//Déplacement des Blasts sur l'axe des X
					BlastSym = BlastSymX;							//Symbole de blast Horizontal
					TailleBlast = TailleBlastX;						//Taille de Blast Horizontal
					MaxBlastLink = NbBlastLink = NbBlastLinkX;		//Nombre de Link de Blast Horizontal
					CleanBlastY = BlastY = HeroY;					//La Position Y ne Changera pas
					HeroMoveXY = HeroMoveX;						//LXaxe de direction ou le Ship va BackStep, si celui-ci tir de trop près

				}
				else
				{
					NSWE = HeroY;										//Déplacement des Blasts sur l'axe des Y
					BlastSym = BlastSymY;							//Symbole de blast Vertical
					TailleBlast = TailleBlastY;						//Taille de Blast Vertical
					MaxBlastLink = NbBlastLink = NbBlastLinkY;		//Nombre de Link de Blast Vertical
					CleanBlastX = BlastX = HeroX;					//La Position X ne Changera pas
					HeroMoveXY = HeroMoveY;
				}

				//Si DirectionB est Positif, le blast se dirigera dans une valeur positive de X ou Y, dans la console
				switch (action)
				{
				case VK_DOWN:
				case VK_RIGHT: DirectionB = 1; break;
				case VK_LEFT:
				case VK_UP:    DirectionB = -1; break;	//Sinon, bah le contraire.
				}
			}

			//On efface l'ancienne position du Ship... pour ne pas laisser de traces!
			//Fait aussi partie de l'animation du blast. Je l'ai mis en double, watchout buddy
			gotoxy(HeroX, HeroY); cout << " \b";

			//Créer une action selon la touche du clavier enfoncé  
			switch (action)
			{
				/////////////////////////////////////////////////////		Tire du Blast!!!								PEW. PEW.
			
			//Blast à gauche|			Blast à droite|			|Blast en haut|			|Blast en bas|
			case VK_LEFT:				case VK_RIGHT:			case VK_UP:				case VK_DOWN:	
		
				// Le link rattaché au boute sera détruit!!!! 
				if (Wall_Transfer)
				{
					PreDestruction_par_Wall_Transfer();
					Le_Boute = false;					// On suppose que le joueur ne se trouve plus sur un "boute"
				}


				BackStep = false;
				Hero_Move = false;					//Le joueur ne se déplacera pas, il tir un blast à la place!
				gotoxy(HeroX, HeroY); cout << " ";	//On efface l'ancienne position du Ship...Temporairement... Fait partie de l'animation du blast!

				for (i = 0; NSWE + i != BlastFin; i += DirectionB)	//Watchout, Le i Devient négatif
				{
					// INSERT TIME TRACKING START HERE
					Timer_Start = clock();

					//Considérer interchanger Blastzisloop++ aux lieux de i += DirectionB

					//DirectionB détermine la direction pour afficher le prochain blast symbole.
					//Ex: si NSWE = 'ShipY' DirectionB est '+', le Blast se dirigera vers le 'Sud'  
					//Si DirectionB est Négatif, les blasts se dirigeront vers le 'Nord'


					if (X_ou_Y)		//Le blast sera latéral, Gauche ou droite
					{
						BlastX = NSWE + i;
						CleanBlastX = BlastX - TailleBlast * DirectionB;
					}
					else					//Le blast sera vertical, haut ou Bas, sur l'axe des Y
					{
						BlastY = NSWE + i;
						CleanBlastY = BlastY - TailleBlast * DirectionB;
					}

					gotoxy(BlastX, BlastY);


					//Transforme la position actuelle du curseur en une variable pour checker les tableaux
					GridX = wherex();		//Si tu sort de la loupe, Grid x , y XY , ne doivent pas changer
					GridY = wherey();
					GridXY = GridX * CompresseurXY + GridY;

					//Check si la position actuelle est un Link, ou un VITALLINK. Si c'est la cas on stop le blast
					for (int j = 0; j < ML; j++)
					{
						//// Si le joueur tir sur un BOT, le BOT sera détruit!
						//if(GridXY == BOTXY[j])
						//	Destroy_BOT_and_Spawn_Blocks(j, front_Spawn_COORD[j]);

							if (GridXY == LinkXY[j] || GridXY == VitalLinkXY[j])
							{
								BlastStop = true;

								// On continue de chercher dans le Tableau de VitalLink pour voir si on en créer un nouveau ou pas
								for (j = j; j < ML; j++)
									if (GridXY == VitalLinkXY[j])
									{
										Skip_FirstVL = true;
										VL = j;
										break;
									}

								break;
							}
					}

					if (BlastStop)
						break;

					// On affiche le symbole du Blast
					gotoxy(BlastX, BlastY);	cout << BlastSym;				

					if (BlastSizeLoop >= TailleBlast)		//Limite la longueur du Blast selon la Taille maximum désiré
					{
						gotoxy(CleanBlastX, CleanBlastY);	//Réduit la longueur du blast 
						cout << " ";
					}

					BlastSizeLoop++;
					Sleep(12);

					//Le temps continue d'avancer durant le blast
					Timer_End = clock();
					Time_Passed = Timer_End - Timer_Start;
					Current_time += Time_Passed;

					UI_Update_TimerAndStats();


					Check_Level_Script(LVL_Script);

				}//FIN DU BLAST ;)



				 //	PRÉPARATION À L'ENREGISTREMENT DU BLAST DANS LES VALEURS  LinkXY, VITAL , WallXY, WALLboute


				// NOTE : Le BLast s'arrête seulement quand il rencontre  un côté de la Box, ou un quelconque Link/Vital
				// On fait un BackStep si le Blast n'a pas atteint ça taille Max
 				if (BlastSizeLoop < TailleBlast)
				{
					BackStep = true;

					//Aucun Wall n'est créé si le blast est plus petit que la taille minimale pour la création d'un Link
					if (BlastSizeLoop < HeroMoveXY)
						Create_Walls = false;

					//Si le Ship est trop près d'un côté de la BOX et tire dessus, on fait un BackStep*  "DELETE"
					if (NSWE + i == BlastFin)
					{
						//On efface un tit résidu du blast, Pour l'instant ça marche, mais sert à rien
						// SI Un BackSTep à lieux et un Alpha est créé....
						gotoxy(BlastX, BlastY);
						cout << ' ';

						/*		SIDENOTE:
										//iCI, SI JE fais un backstep, qui me ferait sortir de la console, je pourrais faire une animation
										//pour montrer qu'il y a un mur invisible, comme des tites lignes qui apparaissent  ex: __@_ _   @   _ _
										//si j'ai du temps :(																						*/
					}
				}

				// Aucun enregistrement ne sera fais, si Create_Walls est faux
				if (Create_Walls)
				{

					//	 SIDENOTE: 
					//				Le Nombre de Walls a enregistrer Dépend du TailleBLast, et de la distance 
					//				qui sépare le Ship du point d'impact. Pour l'instant j'ai setté ça manuellement....
					//				Si tu veux augmenter la quantité de walls par Blast dans le futur utlisie ça:
					//						BlastSizeLoop / ShipMove(Xy) * NBWalls_PerLink


					//	ENREGISTREMENT DES WALLS


					if (X_ou_Y)
					{
						if (BackStep)
							CmbDeWalls = NbWallX;
						else
							CmbDeWalls = (TailleBlastX / HeroMoveX) * NbWallX;		//Deux fois NbWallx
					}
					else
						CmbDeWalls = NbWallY;

					WallX = GridX;		//Rappel: GRIDXY est égal à la coordonnée XY ou le Blast s'est arrêté
					WallY = GridY;

					//La direction que vas prendre l'enregsitrement
					//Illustration:		o	est égal à la position de départ, ou le blast c'est arrêté 			
					//	+----o			+	EST ÉGAL À CleanBlast.		- EST égal au Walls enregistré

					for (int j = 0; j < CmbDeWalls; ++j)
					{
						if (X_ou_Y)
						{
							WallX -= DirectionB;

							if (WallX % HeroMoveXY == 0)	// Ceci est égal aux intersections des LINK
								WallX -= DirectionB;			// Aucun mur ne sera enregistré à une Coordonnée de LINK
						}
						else
						{
							WallY -= DirectionB;

							if (WallY / HeroMoveXY == 0)
								WallY -= DirectionB;
						}

						gotoxy(WallX, WallY); // Just pour débugger :)

						WallXY = CompresseurXY * WallX + WallY;

						for (int k = 0; k < ML; ++k)
							if (Wall[k] == 0)
							{
								Wall[k] = WallXY;
								break;
							}
					}

					//	Cette Section permet de faire un tit boute
					if (BackStep)
						gotoxy(HeroX, HeroY);
					else
						gotoxy(CleanBlastX, CleanBlastY);

					WallX = wherex();
					WallY = wherey();


					// Si la coordonnée actuelle( celle d'un «Boute») est la même que celle du Ship.  «Le_Boute» est activé et on peut faire un wall_transfert.
					if (HeroX == WallX && HeroY == WallY)	// Si le boute reste activé, le prochain mouv du joueur fera apparaître un boute à sa position
						Le_Boute = true;
					else
							cout << BlastSymBoute;

					//NOTE:		Ici je change les valeur de NbBlastLink et MaxBlastLink uniquement afin de me 
					//		faufiler dans la suite du code «Inscription du Blast dans les tableau pour inscrire un Link 

				// Préparation pour inscription si un BACKSTEP à lieu(Quand le blast n'a pas atteint ça taille max)

					if (BackStep)
					{
						//Permet de Valider Combien de Links sont enregistrés
						NbBlastLink = BlastSizeLoop / HeroMoveXY;

						//On Enregistre 1 Link et un vital 
						if (NbBlastLink > 0)
						{
							//sert virtuellement à rien pour l'instant
							if (TailleBlast >= 2 * HeroMoveXY) //si la taille du Blast peut contenir plus qu'un ShipMoveXY, mais //si tu augmente plus que 2*ShipMove la tailleBlast,<--CECI MARCHERA PLUSs

								if (!Skip_FirstVL)
									NbBlastLink = 3;	//On Enregistre 1 Link et 1 vital même si NBlastLink vaut 3, i know its weird
						}

						if (NbBlastLink == 1)
							MaxBlastLink = NbBlastLink = 3;

					}

					//LES ALPHAS ET VITAL LINK NE SAURONT PAS LIÉS
					//Si le blast est le prmier à s'arrêter à la console, on créer le Symbole ALPHA
					if (NSWE + i == BlastFin && !Skip_FirstVL)		//Sauf si on fait un BackStep, au walls ne sont créés dans ce cas
					{
						gotoxy(GridX, GridY); cout << ALPHASym; //Sleep(15);	//Watchout ta mis des Sleep icitte pour rendre l'animation cool
						NoVLSym = true;
					}


					// ENREGISTREMENT du Blast dans les Tableaux de Link, VitalLink et Walls

					//On loop la procédure selon le nombre de links qui devraient être créés pour un blast.
					while (NbBlastLink > 0)
					{
						if (NbBlastLink != MaxBlastLink)	//Permet de skipper la création du premier Link, puisqu'il devrait déjà être dans la base de donnée(Les boutes sont des Links)
						{									//sauf si c'est le premier Link(Alpha)
							for (int j = 0; j < ML; ++j)	//Cherche le première variable du tableau qui est setté à 0.00
								if (LinkXY[j] == 0)
								{
									LinkXY[j] = GridXY;		//Place la coordonnée actuelle dans la variable de LinkXY du tableau
									LinkIndice[j] = VL;		//Relie l'indice du Premier VitalLink au deuxieme Linkdd
									VitalCompteur[VL]++;	//On augmente de 1 le nombre de liens qui dépende du VitalLink
									LinkDirection[j] = action;	//La direction qu'avait le Blast					
									break;
								}
						}

						if (NbBlastLink != 1)	//Le Dernier Link ne sera pas enregister comme Vital, puisqu'il n'est pas encore relié avec quoi que ce soit
						{
							if (!Skip_FirstVL)	 // On enregistre pas de VitaLink si le Ship_move est vrai:, donc Si Le blast est trop court.
							{	//NOTE!: On EnrEgistre un Link une Case plus loin que le blast, même si aucun BlastSym n'est affiché.
								for (int i = 0; i < ML; i++)		//Trouver les première variable setté à 0.00 dans les Tableaux
									if (VitalLinkXY[i] == 0)
									{
										VitalLinkXY[i] = GridXY;	//Place la coordonnée actuelle dans la valeure de VitalLink,
										VL = i;

										break;
									}

								//Afficher le symbole VitalLink
								if (!NoVLSym)
								{
									gotoxy(GridX, GridY);

									if (NbBlastLink >= 2)	//Empêche la création du Symbole de vital Link s'il ne reste plus de vital link a afficher,
										cout << VitalLinkSym;		// ou que Le blast créer un seul VitalLink, qui s'avère aussi être un AlphaLink

									//Sleep(20);		//(l'icône du AlphaLink est pas pareil que celle du VitalLink)
								}
								else
									NoVLSym = false;
							}
							else
								Skip_FirstVL = false;

							//DÉPLACEMENT VERS LE PROCHAIN LINK DU BLAST
							//Illustration pour un blast, allant de gauche à droite.		3----2----1		1= La coord du Blast stop
							//On fait donc un mouvement par en arrière, pour retracer nos pas en gros


							switch (action)
							{
							case VK_RIGHT: gotoxy(GridX - HeroMoveX, GridY);   break;
							case VK_LEFT: gotoxy(GridX + HeroMoveX, GridY);   break;
							case VK_UP: gotoxy(GridX, GridY + HeroMoveY);	 break;
							case VK_DOWN: gotoxy(GridX, GridY - HeroMoveY);
							}

							//Transforme la position actuelle du curseur en une variable pour checker les tableaux
							GridX = wherex();
							GridY = wherey();
							GridXY = GridX * CompresseurXY + GridY;
							gotoxy(GridX, GridY);

							if (BackStep)
								NbBlastLink--;	//On arrête d'inscrire des VItalLink, après une fois, en cas de BackStep
						}

						NbBlastLink--;			//Le nombre de Link/VitalLink à encrypter est réduit de 1!
					}
				}

				//Reset toute les variables pour que tout fonctionne comme sur des roullettes :)
				BlastSizeLoop = BlastStop = BlastX = BlastY = CleanBlastX = CleanBlastY = TailleBlast =
					Skip_FirstVL = VL = HeroMoveXY = Wall_Transfer = 0;
				Create_Walls = Create_Boute = true;


				//	Fin Bloc d'instruction
				//Timer_End = clock();
				//Time_Passed = (Timer_End - Timer_Start) ;
				//Current_time += Time_Passed;
				//cout << clock();
				//cout << (clock() / CLOCKS_PER_SEC);

			}//Fin de la fonction Action ;P


			//	Début Fonction
			Timer_Start = clock();

			//BACKSTEP
			if (BackStep)
			{
				switch (action)
				{
				case VK_RIGHT:	mouvement = 'A';	break;			//gotoxy(ShipX - ShipMoveX, ShipY);   
				case VK_LEFT:	mouvement = 'D';	 break;			// gotoxy(ShipX + ShipMoveX, ShipY);  
				case VK_UP:		mouvement = 'S';		break;		//	gotoxy(ShipX, ShipY + ShipMoveY);
				case VK_DOWN:	mouvement = 'W';					// gotoxy(ShipX, ShipY - ShipMoveY);
				}

				Hero_Move = true;
			}

			//Le mouvement Du Joueur!!!

			MouvementValide = true;

			if (Hero_Move)	//Si Ship_Move est false, le ship bouge pas. Par défaut, il est à ON, Sauf quand le joueur pèse sur une touche action
			{

				//On vérifie si le déplacement est Valide, Donc a l'intérieur de la box fixé par Blast_Fin
				switch (mouvement)
				{
				//case ' ': SpawnBot = true; break; spawn un ti bot. officially useless
				case 'A':
					if (!(HeroX - HeroMoveX < box.limit[LEFT])) //x -= ShipMoveX;	//Le joueur veut se déplacer en dehors de la box,... DENIED!
						GridX = HeroX - HeroMoveX;
					GridY = HeroY; HeroSym = AllPlyrSym[LEFT];	break;

				case 'D':
					if (!(HeroX + HeroMoveX > box.limit[RIGHT])) //x += ShipMoveX;
						GridX = HeroX + HeroMoveX;
					GridY = HeroY; HeroSym = AllPlyrSym[RIGHT];	break;

				case 'W':
					if (!(HeroY - HeroMoveY < box.limit[UP]))	//y -= ShipMoveY;
						GridY = HeroY - HeroMoveY;
					GridX = HeroX; HeroSym = AllPlyrSym[UP];	break;

				case 'S':
					if (!(HeroY + HeroMoveY > box.limit[DOWN])) //y += ShipMoveY;
						GridY = HeroY + HeroMoveY;
					GridX = HeroX; HeroSym = AllPlyrSym[DOWN];
				}


				//Transforme la position du futur mouvement pour checker les tableaux, pour vérifier si la case est libre
				gotoxy(GridX, GridY);
				GridXY = GridX * CompresseurXY + GridY;

				//Validation du mouvement!
				for (int i = 0; i < ML; i++)
					if (GridXY == VitalLinkXY[i]) // Si BackStep == true; On Enclanche la Destruction!!!!
						MouvementValide = false;

				//La nouvelle position du Ship!
				if (MouvementValide)
				{
					if (Le_Boute)
					{
						gotoxy(HeroX, HeroY); cout << BlastSymBoute;
						Le_Boute = false;
					}

					// Sert principalement à corriger des bugs visuels
					HeroXY = GridXY;	HeroX = GridX;	HeroY = GridY;

					// Le joueur se trouve sur un Boute à sa nouvelle position
					for (int i = 0; i < ML; ++i)
						if (HeroXY == LinkXY[i])
						{
							Le_Boute = true;
							break;
						}

				}
				else	//Si le Mouvement est invalide, une animation est créer pour que le joueur comprenne
				{
					gotoxy(HeroX, HeroY);
					Change_Color(LIGHT_PURPLE);
					cout << HeroSym;
					Sleep(90);			//Le ship y flash pendant .90 secondes
				}
			}

			//Afficher la nouvelle position du Ship, DU MOOUVEMENT!!
			gotoxy(HeroX, HeroY);


			if (Le_Boute)
				Change_Color(LIGHT_YELLOW);
			else
				Change_Color(hero.clr);		//Couleur 15 = très blanc
			cout << HeroSym;
















			while ((_kbhit()))
				_getch();


			gotoxy(0, 0);		//Le curseur qui flash, on le place dans un coin pour qui fasse pas chier

			//On revient à la couleur blanc pâle
			Change_Color(7);
			Sleep(50);


			// Si le joueur est DEAD, la partie est terminé 
			if (hero.statut == DEAD)
				break;

			if (BOT_Escape)
				break;

			//Incrémentation du temps

			Timer_End = clock();
			Time_Passed = Timer_End - Timer_Start;
			Current_time += Time_Passed;

			UI_Update_TimerAndStats();

		}//fin loop jeu


		clrscr();
		if (!EndLevel)
			cout << " gg brah.";
		

		//gotoxy(60, 15); cout << "Retry?  (R)";
		
		Sleep(1000);

		while ((_kbhit()))	//	Clear tampon
			_getch();

		_getch();//reset = _getch();

	} while (reset == 'r');

	return 0;





	// Failure
	gotoxy(box.limit[RIGHT] / 2, 15);
	string Lost = "L O S T";
	Sleep(1000);
	
	for (int i = 0; i < 8; ++i)
	{
		Sleep(500); cout << Lost[i];
	}

	string Nothing = "Nothing could be saved...";
	gotoxy(box.limit[RIGHT] / 2, 15);

	for (int i = 0; i < 26; ++i)
	{
		Sleep(50); cout << Nothing[i];
	}
	
	Sleep(3000);


	
	
	




	
}//fin projet main

































//	Les Fonctions Contenant le scénario pour chaque niveaux!!


void Level_1_Script()
{
	if (Initialize_Level)
	{
		UI_Display_StatsName();	// Display les trackers

		FinalChallengeTIME = 60000;
		
		// Les dimensions du Terrain de Jeu pour *DEFAULT  		
		box.limit[UP] = 2;								   
		box.limit[DOWN] = 28;							   
		box.limit[LEFT] = 4;							   
		box.limit[RIGHT] = 116;

		// test de redimension:


		//**** WIN SIZE: 85/48			ou 713x807
		
		// DONT TOUCH	***********************************************************************************
		
		box.limit[UP] = 2;
		box.limit[DOWN] = 43;		// Bond de ShipmoveY * 2!!
		box.limit[LEFT] = 4;		// on dirait que le calcul c'est (Right - Left) / shipmoveX ... et -1 ou valeur plancher...
		box.limit[RIGHT] = 81;		// pour l'instant je gosse pour redimensionner, anyway je vais juste faire ça une ou deux fois
		
		// DONT TOUCH	************************************************************************************


		// Test : Laisser un espace en haut			JE GOSSE ENCORE!
		box.limit[UP] = 8;
		box.limit[DOWN] = 49;// était 43
		box.limit[LEFT] = 4;	
		box.limit[RIGHT] = 81;

		spawn.limit[UP] = box.limit[UP] - Box_to_Spawn;
		spawn.limit[LEFT] = box.limit[LEFT] - Box_to_Spawn;
		spawn.limit[DOWN] = box.limit[DOWN] + Box_to_Spawn;
		spawn.limit[RIGHT] = box.limit[RIGHT] + Box_to_Spawn;
		
		MaxSpawn_CoordinatesX = (box.limit[RIGHT] - box.limit[LEFT]) / HeroMoveX;	//now its 22
		MaxSpawn_CoordinatesY = (box.limit[DOWN] - box.limit[UP]) / HeroMoveY;		// 8?

		Create_New_Spawn_Coord(HeroMoveX, HeroMoveY, SpawnXY);	// Création des Spawns de BOTS!
		MAX_BOTS_Steps_for_each_border(box.limit[UP], box.limit[LEFT], box.limit[DOWN], box.limit[RIGHT], Box_to_Spawn); // lis le nom
		
		// Vitesse des BOTS
		//BOT_Move_Cycle = 400;	// pas touché!
		// Vitesse des spawns
		//Current_Spawn_Cycle = (Spawn_Cycle = 1500);	//*OFFICIEL* pas touché!

		// Vitesse des bots		// 200 = good speed pour les autres niveaux, ici 225-250 devrait être bon, check ton event qui rétablit la vitesse dans ce niv: ce sera la vrai bonne valeur 
		BOT_Move_Cycle = 300;	
		
		/**//* RAPPEL *//**/

		// On Spawn un BOT, et ensuite on fait bouger tout les BOTS.
		// Pour l'initialisation d'un niveau, il faut mettre les cycles de spawn et de BOTmove en même temps
		// et Activer le spawn et le bot move pour le cycle courant
		Spawn_Cycle = 1000;	//test
		Current_Spawn_Cycle = 4500;		// Premier Spawn!!!
		Spawn_this_Cycle = false;
		Next_Spawn_Cycle = Current_Spawn_Cycle + Spawn_Cycle;
		//test
		Current_BOT_MOVE_Cycle = Current_Spawn_Cycle; Move_BOTS_this_Cycle = true;
		Next_BOT_MOVE_Cycle = Current_BOT_MOVE_Cycle + BOT_Move_Cycle;
		
		
		hero.health = 3;

		Initialize_Level = false;
	}
	else
	{
		if(Spawn_this_Cycle)
			Level_1_Spawn_Script(Spwn_cycleTOT);
		
		// Vérification de si y'a un event qui est trigger
		Chck_Event_trigger(Current_time, BOT.TOT_Spawned);

		if (EndLevel)
		{
			LVL_Script = 2;
			gotoxy(HeroX, HeroY);

			// Célébration :)
			//cout << "I Made it!";
			//Sleep(5000);
			clrscr();
			UI_Aff_String(15, 15, "Good Job brah, you are a nice person! :) ", 75, LIGHT_AQUA); BOT_Escape = true;

			_getch();
		}
	}
}







//	Les spawns pour chaque niveaux!!
void Level_1_Spawn_Script(int Spwn_cycleTOT)
{
	// Spawn continuellement à la même place
	//Random_Boxside = Random_Spawn_COORD = false; BoxSide = LEFT; Indice_Spawn_COORD = 1;
	
	/*if (BOT_tracker.Total_BOT_Spawned % 2 == 0)
		Indice_Spawn_COORD = 1;*/
	
	/*if (BOT_tracker.Total_BOT_Spawned >= 20 && BOT_tracker.Total_BOT_Spawned < 30)
		BoxSide = UP; Indice_Spawn_COORD = 6;
	
	if (BOT_tracker.Total_BOT_Spawned >= 20 && BOT_tracker.Total_BOT_Spawned < 30)
		BoxSide = UP; Indice_Spawn_COORD = 6;*/


	int Scripted_spawn = Spwn_cycleTOT;	// Pour aller dans la switch et déterminé quel va être le spawn
	int Skip = 0;						// Représente le nombre de fois qu'on va Skip un cycle de spawn selon l'indice de temps: Delay * Spawn_Cycle

	NumSpawnTOT = 1;					// Reset le nb de spawn max ce cycle-ci
	CoordIntv = {};						// Reset l'interval
	Multi_Spawn = Same_Side =  false;	// Reset la fonctionnalité multispawn
	BoxSide = Indice_Spawn_COORD = -1;	// Si ces valeurs restent à -1, elles seront assignés de manière Random dans la fonction spawnbot

	// RAPPEL IMPORTANT: Le nombre Maximum de Spawn Coord pour chacune des bordures sont les suivantes
						// Bordure : LEFT RIGHT		-> MaxSpawn_CoordinatesY - 1
						// Bordure : UP DOWN		-> MaxSpawn_CoordinatesX - 1
	// NOTICE: Les spawns sont numéroter de [0 à MAX -1]!!	
	// LE NOMBRE DE SPAWN MAX PAR CYCLE CORRESPOND MaxSpawn_Coordinates - 1 : 

	// Par défaut, pour le niveau, tous les spawns seront verticaux
	HorizontalSpawn = true;

	// Script selon le nombre de BOTS spawné durant le niveau	// Flexibilité si je change la vitesse des spawns
	switch (Scripted_spawn)
	{
	case 0:	BoxSide = LEFT; Indice_Spawn_COORD = 0; Skip = 12; break;	//Skip = 8; break;
	case 1:	BoxSide = LEFT; Indice_Spawn_COORD = 0;	Skip = 19; break;	// donne un intervalle de 0 à 1 pour la  prochaine spawn coord	
	case 2:	BoxSide = LEFT; Indice_Spawn_COORD = MaxSpawn_CoordinatesY - 1;	Skip = 4; break;
	case 3:	BoxSide = LEFT; Indice_Spawn_COORD = MaxSpawn_CoordinatesY - 2;	Skip = 2; break;
	case 4: BoxSide = RIGHT; Indice_Spawn_COORD = 0;	Skip = 3; break;
	case 6:	Skip = 2; break;
	case 7:	Skip = 2; break;
	case 5:Indice_Spawn_COORD = MaxSpawn_CoordinatesY / 2;	Skip = 2; break;

	// Triple spawn à droite 
	case 8:	BoxSide = RIGHT; Indice_Spawn_COORD = MaxSpawn_CoordinatesY - 1;Skip = 1; break;
	case 9:	BoxSide = LEFT; Indice_Spawn_COORD = MaxSpawn_CoordinatesY - 2; Skip = 1;  break;
	case 10:BoxSide = RIGHT; Indice_Spawn_COORD = MaxSpawn_CoordinatesY - 3;Skip = 1;  break;
	case 11:Skip = 1; break;
	case 12:Skip = 1; break;
	case 13:BoxSide = RIGHT; Indice_Spawn_COORD = 0; break;
	case 14: break;
	case 15: break;
	case 16:Indice_Spawn_COORD = MaxSpawn_CoordinatesY / 2 - 1; break;
	case 17:Indice_Spawn_COORD = MaxSpawn_CoordinatesY / 2 ;break;
	case 18:Indice_Spawn_COORD = MaxSpawn_CoordinatesY / 2;  break;
	case 19:Indice_Spawn_COORD = MaxSpawn_CoordinatesY / 2 + 1; break;
	case 20:BoxSide = RIGHT;  Indice_Spawn_COORD = 0; 	break;							
	case 21:BoxSide = LEFT; Indice_Spawn_COORD = MaxSpawn_CoordinatesY - 1;  break;		
	case 22:BoxSide = LEFT; Indice_Spawn_COORD = 0 ;  break;
	case 23: Spawn_Crd_Interv(0, 5, CoordIntv);	break;
	case 24: Spawn_Crd_Interv(0, 10, CoordIntv);break;
	case 25: Spawn_Crd_Interv(0, 5, CoordIntv);break;
	case 26: Spawn_Crd_Interv(10, MaxSpawn_CoordinatesY - 1, CoordIntv); NumSpawnTOT = 2; break;
	case 27:break;
	case 28:break;
	case 29:Skip = 5;break;
	// Start les doubles spawns
	case 30:BoxSide = RIGHT; (5, 6, CoordIntv); NumSpawnTOT = 2; break;
	case 31:BoxSide = RIGHT; Spawn_Crd_Interv(5, 6, CoordIntv); NumSpawnTOT = 2; break;
	case 32:BoxSide = RIGHT; Spawn_Crd_Interv(5, 6, CoordIntv); NumSpawnTOT = 2; break;
	case 33:BoxSide = RIGHT; Spawn_Crd_Interv(5, 6, CoordIntv); NumSpawnTOT = 2; break;
	case 34:BoxSide = RIGHT; Spawn_Crd_Interv(5, 6, CoordIntv); NumSpawnTOT = 2;  Skip = 8; break;
	case 35:BoxSide = LEFT; Spawn_Crd_Interv(9, 10, CoordIntv); NumSpawnTOT = 2; break;
	case 36:BoxSide = LEFT; Spawn_Crd_Interv(9, 10, CoordIntv); NumSpawnTOT = 2; break;
	case 37:BoxSide = LEFT; Spawn_Crd_Interv(9, 10, CoordIntv); NumSpawnTOT = 2; break;
	case 38:BoxSide = LEFT; Spawn_Crd_Interv(9, 10, CoordIntv); NumSpawnTOT = 2; break;
	case 39:BoxSide = LEFT; Spawn_Crd_Interv(9, 10, CoordIntv); NumSpawnTOT = 2;  Skip = 8; break;
	case 40:BoxSide = LEFT; Spawn_Crd_Interv(2, 3, CoordIntv); NumSpawnTOT = 2; break;
	case 41:BoxSide = LEFT; Spawn_Crd_Interv(2, 3, CoordIntv); NumSpawnTOT = 2; break;
	case 42:BoxSide = LEFT; Spawn_Crd_Interv(2, 3, CoordIntv); NumSpawnTOT = 2; break;
	case 43:BoxSide = LEFT; Spawn_Crd_Interv(2, 3, CoordIntv); NumSpawnTOT = 2; break;
	case 44:BoxSide = LEFT; Spawn_Crd_Interv(2, 3, CoordIntv); NumSpawnTOT = 2;  Skip = 5; break;
	case 45:BoxSide = RIGHT; Spawn_Crd_Interv(11, 12, CoordIntv); NumSpawnTOT = 2; break;
	case 46:BoxSide = RIGHT; Spawn_Crd_Interv(11, 12, CoordIntv); NumSpawnTOT = 2; break;
	case 47:BoxSide = RIGHT; Spawn_Crd_Interv(11, 12, CoordIntv); NumSpawnTOT = 2; break;
	case 48:BoxSide = RIGHT; Spawn_Crd_Interv(11, 12, CoordIntv); NumSpawnTOT = 2; break;
	case 49:BoxSide = RIGHT; Spawn_Crd_Interv(11, 12, CoordIntv); NumSpawnTOT = 2;  Skip = 5; break;
	// Start les triples spawns!!
	case 50:break;
	case 51:NumSpawnTOT = 3; Skip = 2; break;
	case 52:break;
	case 53:NumSpawnTOT = 3; Skip = 2;break;
	case 54:break;
	case 55: NumSpawnTOT = 3;Skip = 3; break;
	case 56: 
	case 57: NumSpawnTOT = 3;Skip = 4; break;
	case 58:break;
	case 59:NumSpawnTOT = 3; break;
	case 60:break;
	case 61:NumSpawnTOT = 3;Skip = 4; break;
	case 62:NumSpawnTOT = 3;Skip = 1; break;
	case 63:Skip = 1;		 break;
	case 64:Skip = 1;		 break;
	case 65:Skip = 1;		 break;
	case 66:Skip = 1;		 break;
	case 67:NumSpawnTOT = 3; break;
	case 80: Spawn_Crd_Interv(0, 1, CoordIntv); NumSpawnTOT = 3; Skip = 2; break;
	case 81: Spawn_Crd_Interv(MaxSpawn_CoordinatesY - 2, MaxSpawn_CoordinatesY - 1, CoordIntv); NumSpawnTOT = 3; break;
	case 83: Spawn_Crd_Interv(0, 1, CoordIntv); NumSpawnTOT = 3; break;
	case 84: Spawn_Crd_Interv(MaxSpawn_CoordinatesY - 2, MaxSpawn_CoordinatesY - 1, CoordIntv); NumSpawnTOT = 3; break;
	case 87: Spawn_Crd_Interv(0, MaxSpawn_CoordinatesY / 2, CoordIntv); NumSpawnTOT = 3; break;
	case 88: Spawn_Crd_Interv(MaxSpawn_CoordinatesY / 2, MaxSpawn_CoordinatesY - 1, CoordIntv); NumSpawnTOT = 3; break;
	case 99: Skip = 7; break;					// GROSSE WAVE INCOMING
	case 100:BoxSide = LEFT; NumSpawnTOT = 5; break; 
	case 101:BoxSide = LEFT; NumSpawnTOT = 5; Skip = 1; break;
	case 102:BoxSide = LEFT; NumSpawnTOT = 5;break;
	case 103:BoxSide = LEFT; NumSpawnTOT = 5; Skip = 5;break;
	case 104:BoxSide = RIGHT; NumSpawnTOT = 5;break;
	case 105:BoxSide = RIGHT; NumSpawnTOT = 5;break;
	case 106:BoxSide = RIGHT; NumSpawnTOT = 5;break;
	case 107:BoxSide = RIGHT; NumSpawnTOT = 5;Skip = 5;break;
	case 108: NumSpawnTOT = 10; Skip = 2; break;
	case 109: NumSpawnTOT = 10; Skip = 20; break;
	}

	// Ceci ajoute du temps entre le spawn actuel et le prochain
	Next_Spawn_Cycle += Skip * Spawn_Cycle;

	// traitement du random
	if(BoxSide != -1)
		Random_Boxside = false;
	if (Indice_Spawn_COORD != -1 || CoordIntv.active)
		Random_Spawn_COORD = false;
	if (NumSpawnTOT > 1)
		Multi_Spawn = true;

	// Assignation du nombre de spawn durant ce cycle
	//NumSpawn = NumSpawnTOT;

	// Quoi faire si je ne peux pas faire un spawn multiple à cause que j'ai atteint la limite de bots?
	// Pour l'instant: spawn le min possible, soit entre 0 et 4....

	//if (Total_BOTS_Spawned < MaxNumBOTS - 2)	// Double Spawn
	//if (Total_BOTS_Spawned < MaxNumBOTS - 3)	// Triple Spawn
	//if (Total_BOTS_Spawned < MaxNumBOTS - 4)	// Quad Spawn
}

// CHECK LES ÉVÈNEMENTS SPÉCIAUX
void Chck_Event_trigger(Time Current_Time, int BOTSpwnedTOT)
{
	LVL1_Events(Current_Time, BOTSpwnedTOT);
	LVL1_Msg_Events(Current_Time, BOTSpwnedTOT);
}

// VÉRIFIE SI DES CONDITIONS S'APPLIQUENT POUR STARTER UN EVENT
//***********************************************************
void LVL1_Events(Time Current_Time, int BOTSpwnedTOT)
{
	int Ev = LVLNb[0].EvTOT;						// Nombre d'event fait 
	bool EventisDone = false;
	switch (Ev)
	{
	case 0:
		// Le tutorial de mouvement en quelque sorte
		if (!FastStart)
		{
			enum LVL1Requierment{FirstKill, FirstSpawn};

			LVL1Requierment LVL1REQ;
			LVL1REQ = FirstKill;


			EV_Box_Trap();		// Créer une trap pour montrer au joueur comment bouger
			UI_Aff_Char(box.limit[RIGHT] / 2, box.limit[DOWN] / 2, AllPlyrSym[4], 0, LIGHT_GREEN);	// Affiche joueur
			EventisDone = true; 
		}break;
		
	case 1:	 // Au premier bot qui spawn, on augmente ça vitesse à 1000% après qu'il est fait 1 pas!
		if (!FastStart && BOTSpwnedTOT == 1 && BOT.TotalSteps[0] == 1)
		{
			EV_Change_BOT_Speed(50);			// Vitesse élevé
			EventisDone = true; 
		}break;
	case 2:	// RÉTABLIT LA VITESSE NORMALE
		if (!FastStart && BOTSpwnedTOT == 1 && !BOT.TOT_Alive)
		{
			EV_Change_BOT_Speed(225);			// Vitesse du niveau
			EventisDone = true;  
		}break;
	case 3:	//EV_Create_Tutorial_Structure();

		EventisDone = true;  break;
	case 4:	 
EventisDone = true;  break;
	case 5:	 
EventisDone = true;  break;
	case 6:	 
EventisDone = true;  break;
	case 7:	 
EventisDone = true;  break;
	case 8:	 
EventisDone = true;  break;
	case 9:	 
EventisDone = true;  break;
	case 10: 
EventisDone = true;  break;
	case 11: 
		EventisDone = true;  break;




	}

	if(EventisDone)
	{
		// 0 C'est le lvl 1
		LVLNb[0].EvDone[Ev] = true;	// Evenement num TOT est fait
		LVLNb[0].EvTOT++;			// Nombre d'event fait 
	}

	if (Current_Time >= 175000 && Current_Time <= 176000)
		EndLevel = true;
}


// CHECK TOUS LES ÉVENEMENTS QUI CONSISTENT À AFFICHER DU TEXTE DANS LA CONSOLE		(si un Msgevent fait plus que ça, il sera simplement un "EV" normal)
//	----------------------------------------------------------------------------------------- 

void LVL1_Msg_Events(Time Current_Time, int BOTSpwnedTOT)
{
	// Cette structure d'event me permet uniquement d'enchaîner une suite d'évènement linéaire selon chaque event qui l'a précédé
	//	 CONS: -Ne peut pas répéter un event sans duppliquer code
	//			- Ne peut pas se fier à aucun timer pour faire une event
	int& Ev = lvlMsgEv[0].EvTOT;						// Nombre d'event fait 
	bool EventisDone = false;
	if (!lvlMsgEv[0].EvDone[Ev])		// Si l'évènement n'a jamais eu lieu
	{		
		if (!FastStart)
			switch (Ev)
			{
			case 0:	// AFFICHE : "ENJOY FREEDOM"
				if (Current_Time >= 250)
				{
					EV_Msg_AF_WasdTuto();
					EventisDone = true;
				}	break;
			case 1:	// Efface msg précédent
				if (Current_Time >= 5000)
				{
					EV_Msg_DE_WasdTuto();
					EventisDone = true;
				}	break;
			case 2: //		 THIS WILL HURT
				if (Current_Time >= 5500)
				{
					EV_MsgAF_WillHurt();	EventisDone = true;
				}	break;
			case 3://			YOU
				if (Current_Time >= 9000)
				{
					EV_MsgAF_You(); EventisDone = true;
				}	break;
			case 4://			MUST
				if (Current_Time >= 9500)
				{
					EV_MsgAF_Must();EventisDone = true;
				}break;

			case 5://			STOP IT
				if (Current_Time >= 10000)
				{
					EV_MsgAF_STOPIT();EventisDone = true;
				}break;
			case 6:// Efface les mess précédents!
				if (BOTSpwnedTOT == 1 && !BOT.TOT_Alive)
				{
					gotoxy(0, box.limit[DOWN] / 2); clreol();
					Hero_Damage_Animation0hp(); UPD_Hero_Heart(hero);					
					EventisDone = true;
				}break;
			case 7: // Affiche les autres touches claviers	
				if (Current_Time >= 20000)
				{
					EV_MsAF_Got_Out();
					EV_MsgAf_Del_Touche_Tir(38, 11);	EventisDone = true;
				}	break;
			case 8: // Affiche les autres touches claviers	
				if (Current_Time >= 25000)
				{
					UI_DE_Texte_Area(38, 11, 15, 5);
					EV_MsgAf_Stop_Bot(38, 11, false); EventisDone = true;
				}	break;
			case 9: // Informe le joueur sur comment jouer le jeu
				if	(Current_Time >= 28000)
				{
					EV_MsgAf_Stop_Bot(38, 11, true); EventisDone = true;
					
				}break;

			case 10:	// Eff Ms précédent
				if (Current_Time >= 18000)
				{
					
				
				}break;
			}
		else
			Ev += 10;	// yuck, compense le fait qu'un faststart commence plus tard dans les event

	
		switch (Ev)
		{
		case 10: 	EventisDone = true; break;
		case 12:	 	EventisDone = true; break;
		case 13:	 	EventisDone = true; break;
		case 20:
			if (Spwn_cycleTOT == 60)
			{
				UI_Aff_String(box.limit[RIGHT] / 2, box.limit[DOWN] + 2, " noice ", 0, LIGHT_GREEN);
				EventisDone = true;
			}
			break;
		case 21:
			if (Spwn_cycleTOT == 65)
			{
				UI_Aff_String(box.limit[RIGHT] / 2, box.limit[DOWN] + 2, "       ");
				EventisDone = true;
			}
			break;
		}

		if (EventisDone)					// NE DOIT PAS DÉPASSÉ 20 EVENT MAX
		{
			lvlMsgEv[0].EvDone[Ev] = true;	// L'évènement est fait
			lvlMsgEv[0].EvTOT++;			// Le nombre d'event fait au total
		}

	}
}

// Tous les processus(Animation et health update) enclanché par le fait que un Bot sort de la box(le hero prend un de dégât)
bool HeroTakeDamage(HERO &hero)
{
	// 1 de dégât
	hero.health--;

	UPD_Hero_Color(hero.health);			// change la couleur du joueur selon sa vie
	UPD_Hero_Damage_Animation(hero.health);	// Provoque l'animation quand tu reçoît des dégâts- elle est poche for now
	UPD_Hero_Heart(hero);					// Update la vie du joueur!

	// Screen Clear( détruit tout dans l'écran )	// si la vie descend à -1

	// Le joueur est mort, et la partie se termine 
	if (hero.health == 0)	// Si tu décide de faire un op screen clear, met ça à -1
		hero.statut = DEAD;
	
	return hero.statut;
}

void UPD_Hero_Heart(HERO& hero)
{
	string Layer[3] = {};			// Chacune des lignes possibles représentant le coeur
	Coord crd;					// Coordonnée de départ pour afficher le coeur
	crd.Y = box.limit[DOWN] + 2;
	switch (hero.health)
	{
	case 4:
		Layer[0] = "	 \     /";
		Layer[1] = "    - (*Y*)	-";
		Layer[2] = ". + / _`v'_ \ + .";
		break;
	case 3:
		Layer[0] = "        ";
		Layer[1] = "     ( Y*)  ";
		Layer[2] = "      `v'   ";
		crd.X =  39;
		   break;
	case 2:
		Layer[1] = "     ( Y    ";
		Layer[2] = "      `v    ";
		crd.X = 39;
		break;
	case 1:
		Layer[1]=   "  . ,";
		Layer[2]=   "__ v'  ";
		crd.X = 38;
		break;
	case 0:
		break;
	}

	UI_AF_Hero_Heart(crd, Layer, hero.clr);		// Affiche le coeur!
}
// Affiche la vie du joueur sous la forme d'un coeur
// -------------------------------------------------


void UI_AF_Hero_Heart(Coord crd, string Layer[], Colors clr)	
{
	// con.X / 2 Mettre des choses centré!!! >:(
	for (size_t i = 0; i < 3; i++)
	{
		UI_Aff_String(crd.X, crd.Y + i, Layer[i], 0, clr);
	}
}

// ----------------------------------------// ----------------------------------------// ----------------------------------------

// CHANGE LA COULEUR DU JOUEUR SELON SA VIE
// ----------------------------------------

void UPD_Hero_Color(int health)
{
	switch (hero.health)
	{
	case 4: hero.clr = LIGHT_AQUA; break;		// LE MAX, TU COMMENCE PAS UNE GAME AVEC ÇA
	case 3: hero.clr = LIGHT_GREEN; break;		// Standard: Commence chaque lvl avec ça
	case 2: hero.clr = LIGHT_YELLOW; break;
	case 1: hero.clr = LIGHT_RED; break;		// Dernière chance
	}
}

void UPD_Hero_Damage_Animation(int health)
{
	// if(hero.statut == INVINCIBLE)
	gotoxy(84,53); cout << "   ";		// Fait shaker l'écran si tu cout à l'extérieur du screen
	gotoxy(0,0); cout << "   ";		// Fait shaker l'écran si tu cout à l'extérieur du screen
	gotoxy(84, 54);
	//switch (health)
	//{
	//case 3: Hero_Damage_Animation3hp(); break;		// Standard: Commence chaque lvl avec ça
	//case 2: Hero_Damage_Animation2hp(); break;
	//case 1: Hero_Damage_Animation1hp(); break;		// Dernière chance
	//case 0: Hero_Damage_Animation0hp(); break;		// Dernière chance
	//}
}

void Hero_Damage_Animation3hp()	// ANIMATION de dégât quand le héro possède maintenant 3 de vie(il en avait 4 avant )
{
	Swag_Animation(BRIGHT_WHITE, AQUA, LIGHT_AQUA);	// plus de teinte aqua
	UnSwagidy_Animation();	// Effacement
}

void Hero_Damage_Animation2hp()	// ANIMATION de dégât quand le héro possède maintenant 2 de vie
{
	Swag_Animation2(WHITE, LIGHT_YELLOW, GRAY, LIGHT_RED, YELLOW, YELLOW);	// plus de teinte YELLOW
	UnSwagidy_Animation();	// Effacement
}
void Hero_Damage_Animation1hp()	// ANIMATION de dégât quand le héro possède maintenant 1 de vie
{
	Swag_Animation2(BRIGHT_WHITE, LIGHT_RED, BLACK, LIGHT_RED, BLACK, GRAY);	// plus de teinte de rouge
	UnSwagidy_Animation();	// Effacement

}
void Hero_Damage_Animation0hp()	// ANIMATION de dégât quand le héro possède maintenant 3 de vie
{
	Swag_Animation2(BRIGHT_WHITE, GRAY, BLACK, BLACK, BLACK, BRIGHT_WHITE);	// plus de teinte de rouge
	UnSwagidy_Animation();	// Effacement
}
////--------------------------------------------------------------------------------------------------------------

void Finish_Them_to_Win(int BOTXY[], int& EndLevel)
{
	int F;
	for (F = 0; F < MaxNumBOTS; ++F)
		if (BOTXY[F] > 0)
			break;

	if (F == MaxNumBOTS)
		EndLevel = true;
}

//-------------------------------------------------------//-------------------------------------------------------


// ACTIVE L'INTERVAL DE SPAWN COORD POUR LE PROCHAIN SPAWN
//-------------------------------------------------------
void Spawn_Crd_Interv(int min, int max, Sp_CoordIn &coordIn)
{
	coordIn.min = min;
	coordIn.max = max;
	coordIn.active = true;
}

void Create_New_Spawn_Coord(int ShipMoveX, int ShipMoveY, int SpawnXY[][MaxNumBOTS])
{

	//	VARIABLES de création des coordonnées pour la création des Spawns
	int First_CoordX, Last_CoordX, Distance_entre_Spawns, BoxSide;
	int First_CoordY, Last_CoordY, FirstSpawn_COORD, LastSpawn_COORD;
	

	for (BoxSide = 0; BoxSide <= 4 - 1; ++BoxSide)
	{
		//	Pour chaque Boxside on établit la Coordonnée correspondant au premier et au dernier Spawn selon la logique suivante: 
		//	Les Spawns se retrouvent UNE CASE en dessous ou a droite du GRID. De Haut vers le Bas ou de Gauche à droite.   
		// 	ex: premier spawn sur le côté RIGHT se trouve en haut et le dernier se trouve en bas. Les Spawns à droites reflètent donc ceux à gauche
		//  Même chose pour Up et Down

		if (BoxSide % 2 == 0)	//Top-Down, 0-2  et Left-Right 1-3 sont associés.
		{
			Distance_entre_Spawns = ShipMoveX * CompresseurXY;	//Je multiplie par 1000 pour éviter
			First_CoordX = (box.limit[LEFT] + 2) * CompresseurXY;	// les Floating point error à la comparaison
			Last_CoordX = box.limit[RIGHT] * CompresseurXY;		// plus bas
		}
		else
		{
			Distance_entre_Spawns = ShipMoveY;
			First_CoordY = box.limit[UP] + 2;	//what is + 2?			+2 semble être la distance entre le spawn et le 
			Last_CoordY = box.limit[DOWN];							//début du grid...	ça devrait juste être spawn.down...

		}

		switch (BoxSide)
		{
		case 0: First_CoordY = Last_CoordY = box.limit[UP] - Box_to_Spawn;	break;	//	le +/- 1 sert placer le Spawn une case en dehors de la Box. 
		case 1: First_CoordX = Last_CoordX = (box.limit[LEFT] - Box_to_Spawn) * CompresseurXY; break;		//	Setté à 1 for now...
		case 2: First_CoordY = Last_CoordY = box.limit[DOWN] + Box_to_Spawn; break;
		case 3: First_CoordX = Last_CoordX = (box.limit[RIGHT] + Box_to_Spawn) * CompresseurXY;
		}

		
		

		FirstSpawn_COORD = First_CoordY + First_CoordX;
		LastSpawn_COORD = Last_CoordY + Last_CoordX;

		//ON ÉCRIT chaque COORdonnées des Spawn dans le tableau qui servira de référence pour faire apparaître les BOTS.
		for (int i = 0; FirstSpawn_COORD != LastSpawn_COORD; i++)
		{
			SpawnXY[BoxSide][i] = FirstSpawn_COORD;

			Goto_Coordinnates(CoordX, CoordY, FirstSpawn_COORD );
			//cout << i;			//Affiche le numéro de chaque spawns
			FirstSpawn_COORD += Distance_entre_Spawns;
		}
	}
}


// Destruction d'un bot si celui-ci rencontre un mur ou réussis à sortir de la map
void Destroy_BOT_and_Spawn_Blocks(int In_Bot, int Front_Coord)
{
	int CoordX, CoordY;
	int _PerpBoxSide[2] = {};						// Les deux bordures perpendiculaires de spawn a débloquer 
	int FrontBoxSide = BOT_Direction[In_Bot];	// Permet de retracer la bordure en face du bot. Pour enlever le blockage
	int MaxSpawn;							// Donne le nombre de spawn a débloqué sur les deux bordures perpendiculaire au bot

	// Attribution des valeurs de Boxside pour la vérification des deux bordures perpendiculaires à débloquer
	for (size_t i = 0; i < 2; i++)
	{
		if (i == 0)
			switch (FrontBoxSide)
			{										//
			case UP: case DOWN:_PerpBoxSide[i] = LEFT; MaxSpawn = MaxSpawn_CoordinatesY; break;
			case LEFT:case RIGHT:_PerpBoxSide[i] = UP; MaxSpawn = MaxSpawn_CoordinatesX; 
			}
		else
			switch (FrontBoxSide)
			{
			case UP:case DOWN: _PerpBoxSide[i] = RIGHT; break;
			case LEFT:case RIGHT:_PerpBoxSide[i] = DOWN;
			}
	}

	//Unblock all Spawns linked to that bot
	for (size_t Side = 0; Side < 2; Side++)
		for (int COORD = 0; COORD < MaxSpawn; ++COORD)
		{
			if (Spawn_Block[_PerpBoxSide[Side]][COORD][In_Bot] != -1)			
			{	// Ceci va reset tous les block qui ont l'indice du BOT. Même ceux qui sont pas affecté....
				// C'est pourquoi il serait mieux d'avoir une liste chaîné
				
				//Get_Coordinnates(CoordX, CoordY, SpawnXY[_PerpBoxSide[Side]][COORD]);	// POUR DEBUG
				//gotoxy(CoordX, CoordY); changeColor(GREEN);
				//cout << ' ';
				//changeColor(7);
			}
			Spawn_Block[_PerpBoxSide[Side]][COORD][In_Bot] = -1;
		}
	// Unblock Front Spawn
	front_Spawn_Block[FrontBoxSide][front_Spawn_COORD[In_Bot]][In_Bot] = false;
	front_Spawn_COORD[In_Bot] = -1;		// La coordonnée du spawn à blocker est invalidé


	// Effacement de la porte de sortie si aucun bot ne s'y dirige(sorte de queue visuelle qui montre ou le bot se dirige
	size_t allBots;	// indice du tableau de front spawn block

	for (allBots = 0; allBots < MaxNumBOTS; allBots++)
		if(front_Spawn_Block[FrontBoxSide][Front_Coord][allBots] == true)
			break;

	// Si plus aucun bot n'est présent face au spawn, on efface la porte
	if (allBots == MaxNumBOTS)
	{
		// Coordonnée du spawn(malheuresuement, la porte est une coche plus loin)
		Get_Coordinnates(CoordX, CoordY, SpawnXY[FrontBoxSide][Front_Coord]);
		Affi_ou_Effa_BOT_Esc_Door(FrontBoxSide, CoordX, CoordY, true);	// Efface la porte
	}

	BOTXY[In_Bot] = BOT_Direction[In_Bot] = 0;	// BOT = DESTROYED
	BOT.TotalSteps[In_Bot] = BOT.MaxSteps[In_Bot] = BOT.StepsToEscape[In_Bot] = 0;	// Reset son nombre de déplacements
	BOT.TOT_Alive--; // réduit de 1 le total de Bots Spawné
}


// Find distance between wall impact and left and right intersection(link/Vitalink) coord
void Find_CoordLeft_AND_Right_of_BOT_Impact(int DirectionBOT, int & CoordLeft, int & CoordRight)
{
	// Ce qui suit sert à déterminer la position des 2 LINK se trouvant à gauche et à droite du BOT ayant percuté un mur.

	// Distance entre le point d'impact du bot et les deux COORD des premier LINK à gauche et à droite
	struct Distance_Entre_Impact_Et_Intersections { int LeftX, LeftY, RightX, RightY; };
	Distance_Entre_Impact_Et_Intersections Dist;

	// L'axe ou ne se trouve pas les walls			// Donc si un bot se dirigeant vers RIGHT et frappe un walls, les murs et les links adjacent seront à la vertical
	if (DirectionBOT == LEFT || DirectionBOT == RIGHT)
	{
		DirectionX = Dist.LeftX = Dist.RightX = 0; 
	}	// L'axe des walls est donc sur les Y
	else
	{
		DirectionY = Dist.LeftY = Dist.RightY = 0; 
	}	 // L'axe des walls est donc sur les X

	// Distance à gauche et à droite, sur les deux axes, séparant le BOT des deux LINK 

	// -1 * Distance entre bot et intersection gauche + NbWall + Distance entre bot et intersection gauche
	switch (DirectionBOT)
	{
	case UP:	Dist.LeftX = -1;		Dist.RightX = NbWallX; break;
	case LEFT:	Dist.LeftY = NbWallY;	Dist.RightY = -1;	 break;
	case DOWN:	Dist.LeftX = NbWallX;	Dist.RightX = -1;	 break;
	case RIGHT:	Dist.LeftY = -1;		Dist.RightY = NbWallY;
	}

	//// CoordLeft et CoordRight = au premier Link à gauche et à droite du BOT
	CoordLeft = ((CoordX + Dist.LeftX) * CompresseurXY + CoordY + Dist.LeftY);
	CoordRight = ((CoordX + Dist.RightX) * CompresseurXY + CoordY + Dist.RightY);

}

// Trouve le VitalLink d'un Link selon une coordonnée
int Find_a_Links_VitalLink(int CoordXY) 
{
	size_t Index = Search_Coordinnates(LinkXY, ML, CoordXY);	// Trouve l'indice du LinkXY à la position actuelle
	return VitalLinkXY[LinkIndice[Index]];						// Retourn la Coordonnée du parent immédiat du Link

}

// Donne l'axe des walls(x ou y) se trouvant entre deux CoordonnéesXY, (l'axe de la distance entre les deux points)
Axe Axe_Entre_Deux_Coord(int Coord1, int Coord2)
{
	Axe axe;	// l'axe que l'on cherche
	int CoordX1 =	Coord1 / CompresseurXY;	// Décompression de la COORD
	int CoordX2 =	Coord2 / CompresseurXY;

	// Si ça donne faux, cela veut dire que la valeur en X des deux coordonnée est identique. 
	if (CoordX1 > CoordX2 || CoordX1 < CoordX2)
		axe = x;
	else
		axe = y;		//	La distance séparant les deux Coordonnée se fait donc sur l'axe des Y

	return axe;
}

Polarisation Polarisation_Selon_Deux_Coord(int CoordDepart, int CoordFin)
{
	Polarisation polar; // Donne la polarisation d'une direction(celle que sous-tend la distance entre depart et fin)

	if (CoordDepart < CoordFin)	polar = Pos; else polar = Neg;	return polar;
}

// Donne la polarisation de déplacement positif(+1) ou négatif(-1) dans la console selon une direction
Polarisation Polarisation_Selon_Direction(Direction direction)
{
	Polarisation polarisation;

	switch (direction)
	{
	case DOWN:	polarisation = Pos; break;
	case RIGHT:	polarisation = Pos;	break;			//	L'axe des et X et Y s'incrémenteront positivement	
	case UP:	polarisation = Neg; break;			// RAPPEL: Si on se dirige vers la droite ou vers le bas dans la console 
	case LEFT:	polarisation = Neg; break;
	}

	return polarisation;
}



// Donne la direction d'une coordonnée par rapport à une autre, selon l'axe des X ou l'axe des Y
Direction Direction_Entre_Deux_Coord_Selon_Axe(int CoordDepart, int CoordFin, Axe axe)
{
	Direction direction;	// La direction que l'on recherche

	switch (axe)	// peut fail si axe == NUL
	{
	case x:	if (CoordDepart < CoordFin)	direction = RIGHT; else direction = LEFT;
	case y: if (CoordDepart < CoordFin)	direction = UP; else direction = DOWN;
	}


	return direction;
}

// Compress une valeur en x et en y ensemble
int Compress_XY(int CoordX, int CoordY)	{	int CoordXY = CoordX * CompresseurXY + CoordY; return CoordXY;	}



//*/*/*/*/FONCTION QUI PERMETTRAIT DE SETUP DES VARIABLES POUR NAVIGUER LES MURS ENTRE DEUX COORD. FOR NOW, USELESS. CAR JE NAVIGUE UNIQUEMENT POUR CRÉEER OU DÉTRUIRE
//void Walls_Btwn_2_Coord(int CoordDepart, int CoordFin)
//{
//	int NbdeWalls;		// Le nombre de walls entre 2 coord
//	Axe axe;			// L'axe des murs entre la CoordDepart et la Coord de fin
//	Polarisation polar;	// La polarisation entre la Coordonnée de départ et la coord de fin
//	char Sym;			// Le symbole pour l'affichage du Wall
//
//	axe = Axe_Entre_Deux_Coord(CoordDepart, CoordFin);				// Donne l'axe
//	polar = Polarisation_Selon_Deux_Coord(CoordDepart, CoordFin);	// Trouve la polarisation entre là coordonnée de départ et de fin															
//
//	//// Le nombre de walls et le symbol du wall
//	if (axe == x){NbdeWalls = NbWallX; Sym = BlastSymX;}	else	{ NbdeWalls = NbWallY; Sym = BlastSymY;}	
//}


//	DESTRUCTION ET EFFACEMENT D'UN MUR
void Destroy_WALL(int CoordX, int CoordY)
{
	int CoordXY = Compress_XY( CoordX, CoordY);				// Valeur compressé pour chercher dans le tableau
	Destruction_1_mur(CoordXY);								//On détruit le Wall à l'emplacement
	Clean_Char(CoordX, CoordY);							// Efface le symbole présent sur la coordonnée
}

// Destruction d'un unique mur selon sa coordonnée compressé
void Destruction_1_mur(int CoordXY)
{
	//On détruit le Wall à l'emplacement
	for (int m = 0; m < C; ++m)
		if (CoordXY == Wall[m])
		{
			Wall[m] = 0;
			break;
		}
}

// Création ou Destruction de tous les murs possibles se situant entre deux coord (côte-à-côte sur le grid)
void Creation_or_Destruction_Walls_Btwn_Links(int CoordDepart, int CoordFin, Time Delay, bool Creation)
{
	int NbdeWalls;		// Le nombre de walls entre 2 coord
	Axe axe;			// L'axe des murs entre la CoordDepart et la Coord de fin
	Polarisation polar;	// La polarisation entre la Coordonnée de départ et la coord de fin
	char Sym;			// Le symbole pour l'affichage du Wall

	axe = Axe_Entre_Deux_Coord(CoordDepart, CoordFin);				// Donne l'axe
	polar = Polarisation_Selon_Deux_Coord(CoordDepart, CoordFin);	// Trouve la polarisation entre là coordonnée 

	//// Le nombre de walls et le symbol du wall
	if (axe == x) { NbdeWalls = NbWallX; Sym = BlastSymX; }
	else		  { NbdeWalls = NbWallY; Sym = BlastSymY; }

	// On va commencer la destruction/Création à partir de la coordonnée de départ
	Goto_Coordinnates(CoordX, CoordY, CoordDepart);

	for (int l = 0; l < NbdeWalls; ++l)	// Destruction de chacun des murs entre les deux Links
	{
		// La coordonnée de chacun des murs à détruire est déterminée par l'incrémentation de x ou y de +1 ou -1 case selon l'axe ou se trouve les walls
		axe == y ? CoordY += polar : CoordX += polar;
		if (Creation)
			Create_Wall(CoordX, CoordY, Sym);	// Création d'un mur
		else
			Destroy_WALL(CoordX, CoordY);		// Destruction du mur et effacement du symbole
		Sleep(Delay);
	}
}

void Create_Wall(int CoordX, int CoordY, char WallSym)
{
	int CoordXY = Compress_XY(CoordX, CoordY);				// Valeur compressé pour chercher dans le tableau
	Creation_1_mur(CoordXY);								// Création du mur
	gotoxy(CoordX, CoordY);	cout << WallSym;				// Affichage du mur
}


// Creation d'un unique mur selon sa coordonnée compressé
void Creation_1_mur(int CoordXY)
{
	//On créé le Wall à l'emplacement
	for (int m = 0; m < C; ++m)
		if (Wall[m] == 0)
		{
			Wall[m] = CoordXY;
			break;
		}
}

void Afficher_Char(int CoordXY, char Sym)
{
	int CoordX, CoordY;	Goto_Coordinnates(CoordX, CoordY, CoordXY);	cout << Sym;
}


// Création d'une tit structure pour le début de la game
void EV_Create_Vertical_Structure(int GridXy, int L, int V, int NbWalls)
{
	Change_Color(BRIGHT_WHITE);

	int Delay = 40;
	V = Search_For_Available_VitalLink(V);
	L = Search_For_Available_Link(L);


	int somethinghere = Search_Coordinnates(VitalLinkXY, ML, GridXY);	// Si retourne -1, il na rien trouvé


	if (Search_Coordinnates(LinkXY, ML, GridXY) != -1 && somethinghere != -1)	// Si ya quekchose icitte, on affiche rien pentoute
	{
		VitalLinkXY[L] = GridXY;		VitalCompteur[L]++;
		LinkXY[V] = GridXY += HeroMoveY;	LinkIndice[V] = L;
		LinkDirection[V] = VK_UP;

		// Manque plus qu'à afficher
		Afficher_Char(VitalLinkXY[L], ALPHASym); Sleep(Delay);
		Creation_or_Destruction_Walls_Btwn_Links(VitalLinkXY[L], LinkXY[V], Delay, true);
		Afficher_Char(LinkXY[V], VitalLinkSym);	// Link en bas

		for (L = 1; L < NbWalls; L++)
		{
			V++;

			// Et on recommence
			VitalLinkXY[L] = LinkXY[V - 1];

			LinkXY[V] = GridXY += HeroMoveY; // Link en bas
			LinkIndice[V] = L;
			LinkDirection[V] = VK_UP;

			Creation_or_Destruction_Walls_Btwn_Links(VitalLinkXY[L], LinkXY[V], Delay, true);
			Afficher_Char(LinkXY[V], VitalLinkSym);

			VitalCompteur[L]++;

		}
		Afficher_Char(LinkXY[V], BlastSymBoute);
		Change_Color(WHITE);
	}
}

// Création d'une tit structure pour le début de la game
void EV_Create_Horizontal_Structure(int GridXy, int L, int V, int NbWalls)			
{
	Change_Color(BRIGHT_WHITE);
	int Delay = 40;

	int somethinghere = Search_Coordinnates(VitalLinkXY, ML, GridXY);	// Si retourne -1, il na rien trouvé

	if (Search_Coordinnates(LinkXY, ML, GridXY) != -1 && somethinghere != -1)	// Si ya quekchose icitte, on affiche rien pentoute
	{
		VitalLinkXY[L] = GridXY;			VitalCompteur[L]++;
		LinkXY[V] = GridXY -= HeroMoveX * CompresseurXY;	LinkIndice[V] = L;
		LinkDirection[V] = VK_RIGHT;

		// Manque plus qu'à afficher
		Afficher_Char(VitalLinkXY[L], ALPHASym); Sleep(Delay);
		Creation_or_Destruction_Walls_Btwn_Links(VitalLinkXY[L], LinkXY[V], Delay, true);
		Afficher_Char(LinkXY[V], BlastSymBoute);	// Link en bas	
	}
}


// Créé des murs pour montrer qu'on peut faire ça pour stopper les bots and shit
void EV_Create_Tutorial_Structure() 
{
	EV_Create_Vertical_Structure(box.limit[UP] + Box_to_Spawn + 50000, 10, 10, 2);	// Créé un mur au début de la game qui va servir à montrer que le joueur peut stopper les ennemis en faisant des murs
	EV_Create_Horizontal_Structure(80024, 100, 100, 1);	// ... Et un autre pour montrer qu'il peut tirer dans ce sens aussi
}



// Détermine laquelle de deux Coordonnée qui dépend de l'autre. Du même coup, détermine aussi si celle dépendante est un VL ou non
bool Find_Parent_Btwn_Links(int CoordLeft, int CoordRight,int &VL_Left, int & VL_Right, bool & isVital)
{
	//fONCTION QUE J'ai  fais FONCTIONNER!(Bravo!)						//Check d'abord si la coordonnée lEFT ou RIGHT est un VitalLink
	VL_Left = Search_Coordinnates(VitalLinkXY, ML, CoordLeft);			//VL_ left correspond a l'indice du VitalLinkXY se trouvant à la CoordLeft
	VL_Right = Search_Coordinnates(VitalLinkXY, ML, CoordRight);		//VL_right correspond a l'indice du VitalLinkXY se trouvant à la CoordRIGHT

	//On détruit à Gauche si DestroyLeft_Right est True. On détruit à droite si DestroyLeft_Right est false. 
	DestroyLeft_Right = false;

	// Vérifie si un des deux côtés n'est pas un vitalink 
	//Si il n'y a pas de VitalLink à gauche
	if (VL_Left == -1)				// L'indice du VL à gauche et à droite. Si = à -1, alors il n'y a pas de VLink à gauche OU à droite
	{
		isVital = true;		//	Nous aurons qu'à détruire qu'un seul Link
		DestroyLeft_Right = true;			// et il sera à gauche
	}
	//Si la Coordonnée à droite n'est pas un VitalLink
	if (VL_Right == -1)
		isVital = true;		//Nous détruisons à droite (DestroyLeft_Right est faux par défaut)

	if (!isVital)
	{
		//Nous devons vérifier lequel des deux Coord dépend de l'autre
		for (int i = 0; i < ML; i++)			//On trouve la CoordLeft dans le Tableau de LINKXY	
		{
			if (CoordLeft == LinkXY[i])
			{
				if (LinkIndice[i] == VL_Right)	// Check si le LinkXY(CoordLeft) est l'enfant de CoordRight.
					DestroyLeft_Right = true;	//  Si c'est le cas, On détruit la CoordLeft 
												// Sinon par défaut on détruit à droite(false)
				break;
			}
		}
	}

	return DestroyLeft_Right;
}


//	// Wall transfer est une destruction de mur causée par le joueur. La destruction standard de mur se fait par l'impact d'un bot sur un mur
void PreDestruction_par_Wall_Transfer()
{
	int CoordVLink, CoordLink;
	bool One_Link_Destruction = true;	// On détruit assuérment qu'un seul Link
	int Destruction;					// La coordonnée ou on va tout détruire
	int VL = -1;						// Ta fonction de destruction est boboche. Alors on est obligé de mettre un valeur bidon dans VL. Mais on sait qu'il n'y a pas de VL à cette coord
	int VL_Origin;						// VL Origin, est le VitalLink de l'ature côté de la chaîne de destruction. Son parent.
	int IndexLink;

	// On devrait être positionné sur le shipXy en ce moment mais je prendrais pas de chance
	CoordLink = Compress_XY(HeroX, HeroY);							// La position immédiate du curseur dans la console, le LINK, LE boute!
	IndexLink = Search_Coordinnates(LinkXY, ML, CoordLink);			// Trouve l'indice du LinkXY à la position actuelle
	VL_Origin = LinkIndice[IndexLink];								// L'indice du VitalLink de notre Link à détruire
	CoordVLink = VitalLinkXY[VL_Origin];							// Trouve le VL du Link

	// Destruction des murs entre les deux link. On part du VitalLink, vers le Link
	Creation_or_Destruction_Walls_Btwn_Links(CoordVLink, CoordLink);

	// Destruction de la chaîne de murs suivante
	Structure_Destruction_n_Stuff(CoordLink, VL, VL_Origin, DestroyLeft_Right, One_Link_Destruction);
}


// Bouette qui setup les variables pour la destruction des murs
void PreDestruction_par_BOT_Impact(int DirectionBOT, int CoordXY)
{
	int CoordLeft, CoordRight;
	bool DestroyLeft_Right = false;			// Dicte de quel côté on va détruire une chaîne de liens(True = left et false = right)
	bool One_Link_Destruction = false;
	int	VL_Left, VL_Right;			// L'indice du VL se trouvant sur les deux coordonnées
	int Destruction;			// La coordonnée ou on va tout détruire
	int VL, VL_Origin;		// VL Origin, est le VitalLink de l'ature côté de la chaîne de destruction. Son parent.

	// Ce qui suit sert à déterminer la position des 2 LINK se trouvant à gauche et à droite du BOT ayant percuté un mur.
	Find_CoordLeft_AND_Right_of_BOT_Impact(DirectionBOT, CoordLeft, CoordRight);

	// Détruire à partir de quel COordonnée(left ou right).			Et un seul link si l'une des Coord n'est pas vital
	DestroyLeft_Right = Find_Parent_Btwn_Links(CoordLeft, CoordRight, VL_Left, VL_Right, One_Link_Destruction);
	
	//On détruit à gauche ou a droite?
	if (DestroyLeft_Right)				// On détruit les link à gauche 
	{
		Destruction = CoordLeft;
		VL = VL_Left;
		VL_Origin = VL_Right;

		// Et la coordonnée à droite est nécessairement le Vital du Link à gauche
	}
	else								// On détruit les link relié au Link à droite
	{
		Destruction = CoordRight;
		VL = VL_Right;
		VL_Origin = VL_Left;
	}

	// Destruction des murs entre les deux link, commence par la gauche. Pour l'instant
	Creation_or_Destruction_Walls_Btwn_Links(CoordLeft, CoordRight);

	// Destruction de la chaîne de murs suivante
	Structure_Destruction_n_Stuff(Destruction, VL, VL_Origin, DestroyLeft_Right, One_Link_Destruction);

}



//Destruction v3.0 : Permet la destruction de pleins de murs
void Structure_Destruction_n_Stuff(int Destruction, int VL, int VL_Origin, bool DestroyLeft_Right, bool One_Link_Destruction)
{
	// Préparation des coordonnés
	CoordX = Destruction / CompresseurXY;
	CoordY = Destruction - CoordX * CompresseurXY;

	// On efface pas le premier Link si le Ship s'y trouve!!
	if (HeroXY == Destruction)
		Le_Boute = false;
	else 					//On positionne le curseur sur le premier Link et on efface le symbole( pour l'animation)
		gotoxy(CoordX, CoordY); cout << ' ';
	
	//Pour ton animation de Destruction Post-Mortem		
	Counter_Walls = 0;

	///////////////////////////////////////////////////////////////////La Destruction!!!!\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\	

	// Si l'on ne détruit pas une chaine de link, mais une extrêmité(un seul link) on skip cette étape pour détruire uniquement ce lien après 
	if (!One_Link_Destruction)
	{
		NumVLtoDestroy = 1;							// Initialisation. On débute avec la coord d'un VitalLink à détruire. D
		VitalLink_Destruction[NumVLtoDestroy] = VL;

		do
		{
			VL = VitalLink_Destruction[NumVLtoDestroy];

			if (VitalCompteur[VL] > 0)
			{
				for (int k = 0; k < ML; ++k)
				{
					//On cherche quels sont les Links qui sont dépendants du VitalLink
					if (LinkIndice[k] == VL)
					{

						//On se positionne sur le Link
						Goto_Coordinnates(CoordX, CoordY, VitalLinkXY[VL]);

						DirectionX = DirectionY = 0;

						//On check dans quel direction le Link se trouve par rapport au VitalLink
						switch (LinkDirection[k])
						{
						case VK_RIGHT:	NbdeWalls = NbWallX;	DirectionX = -1; break;
						case VK_LEFT: 	NbdeWalls = NbWallX;  	DirectionX = 1; break;
						case VK_UP:   	NbdeWalls = NbWallY;	DirectionY = 1; break;
						case VK_DOWN: 	NbdeWalls = NbWallY;	DirectionY = -1;
						}

						//On visite chaque mur, du VitalLink jusqu'au Link, et on les DESTROY!
						for (int l = 0; l < NbdeWalls; ++l)
						{
							CoordX += DirectionX;CoordY += DirectionY;
							gotoxy(CoordX, CoordY); cout << ' '; Sleep(15);	// Pour Débugger ajoute un x

							/*//Si tu veux animer la destruction en changeant la couleur du Background , voilà...
							changeColor(20); CoordX = wherex(); CoordY = wherey(); CoordXY = CoordY * 100 - CoordX;
							Destruction_Animation[Counter_Destruction][Counter_Walls] = CoordXY; Counter_Walls++;*/

							// Coord du wall
							CoordXY = CoordX * CompresseurXY + CoordY;

							//On détruit le Wall à l'emplacement
							for (int m = 0; m < C; ++m)
								if (CoordXY == Wall[m])
								{
									Wall[m] = 0;
									break;
								}
						}

						//J'additionne de 0 à chaque fois, m'essemble que c'est useless


						//	Si le joueur se trouve sur un "Boute", c'est à dire un Link se trouvant sur l'extremité d'une chaîne
						//	Nous n'effaçons pas cette extremité, car sinon, le joueur serait effacé aussi D?:

						if (HeroXY == LinkXY[k])					
							Le_Boute = false;
						else 
						{	//On Delete le symbole du Link se trouvant au bout
							CoordX += DirectionX;CoordY += DirectionY;
							CoordXY = CoordX * CompresseurXY + CoordY;
							gotoxy(CoordX, CoordY); cout << ' ';
						}
						
						//On check si un VitalLink se trouve sur la coordonnée du Link qu'on va détruire
						for (int l = 0; l < ML; ++l)
							if (VitalLinkXY[l] == LinkXY[k])
							{
								NumVLtoDestroy++;							//Augmente l'indice du numbre de Vital à détruire de 1
								VitalLink_Destruction[NumVLtoDestroy] = l;	//On met la valeur de l'indice du nouveau Vital trouvé dans le Tableau pour le delete après
								break;
							}
						//Si c'est le cas, on ajoute le VL qu'on utilisiat live et on l'ajoute dans le tableaux des shit à détruire later
						//LE VL du NouveauVitalLink devrait prendre la place de l'ancien pour la prochaine loop de destruction de walls

						//On Delete tout ce qui se trouvait sur la coordonnée 
						//Goto_Coordinnates(CoordX, CoordY, LinkXY[k]); changeColor(12); cout << 'L'; changeColor(7); // Pour Débugger

						LinkIndice[k] = 0;
						LinkXY[k] = 0;
						LinkDirection[k] = 0;

						//Réduit de 1 le nombre de Link étant relié au VitalLink
						VitalCompteur[VL]--;

						//Pour ton animation de destruction post-Mortem
						Counter_Destruction++;

						break;
					}
				}
			}
			else//Si le compteur de Links dépendant du VitalLink tombe à Zéro, plus aucun Link n'est associé, et on peut delete le VitalLink definitivement  
			{
				CoordX = VitalLinkXY[VL] / CompresseurXY;
				CoordY = VitalLinkXY[VL] - CoordX * CompresseurXY;
				gotoxy(CoordX, CoordY);
				cout << ' ';

				VitalLinkXY[VL] = 0;
				VitalLink_Destruction[NumVLtoDestroy] = 0;
				NumVLtoDestroy--;
			}

		} while (NumVLtoDestroy >= 1);
	}

	//// Le Compteur du Parent de la chaine de vitallink qu'on vient de détruire est réduit de 1
	VitalCompteur[VL_Origin]--;
	
	// On doit maintenant effacer le vitaLink parent de la chaîne de destruction
	if (VitalCompteur[VL_Origin] == 0)
	{
		//On va au premier VitalLink  et on le pète!
		Goto_Coordinnates(CoordX, CoordY, VitalLinkXY[VL_Origin]);

		if(Search_Coordinnates(LinkXY, ML, VitalLinkXY[VL_Origin]) == -1)	
			cout << ' ';											//	Vérification de si un link est présent sur la coordonnée du Vital d'origine
		else														//	Si aucun link n'est présent, cela veut dire que c'était un alpha!
			cout << BlastSymBoute;									//	-----------------------------------------------------------------			

		// Il faut donc supprimer le vital Link)
		VitalLinkXY[VL_Origin] = 0;
	}

	//On détruit le LINK Originelle, c'est à dire celui se trouvant sur
	//la Coordonnée de départ de la chaîne de destruction gauche ou droite (CoordLeft ou CoordRight)
	//*-*-*-*-*-*-*-*-*-*-*-***-*-*-*-*-**-*-*-*-*-*-*-*-*-*-*-***-*-*-*-*-**-*-*-*-*-*-*-*-*-*-*-***-*-*-*-*-*

	{
		In Final_Link;
		Final_Link = Search_Coordinnates(LinkXY, ML, Destruction);	// On trouve le dernier Link à delete

		LinkXY[Final_Link] = 0;				// Et on le liquide
		LinkDirection[Final_Link] = 0;
		LinkIndice[Final_Link] = 0;
	}

	//Reset tes variables pour pas te faire chier
	DESTROY_STRUCTURE  = Destruction = One_Link_Destruction = 0;

}//Fin fonction destroy

 


// Affiche un charactère vide à une coordonnée
void Clean_Char(int CoordX, int CoordY)
{
	gotoxy(CoordX, CoordY); cout << ' ';
}




//On cherche dans le tableaux des Links/ou VitalLink
int Search_Coordinnates(int Link[], int Max, int XY)
{
	int Indice = -1;	// Si la fonction trouve rien, elle retourne -1
	int i;

	for (i = 0; i < Max; i++)
		if (XY == Link[i])
		{
			Indice = i;
			break;
		}
			
	return Indice;
}

// On se déplace à une coordonnée
void Goto_Coordinnates(int& X, int& Y, int XY)
{
	X = XY / CompresseurXY;
	Y = XY - X * CompresseurXY;
	gotoxy(X, Y);
}

//Transforme la position actuelle du curseur en une variable pour checker les tableaux
int Compress_Cursor_XY() 
{
	 int CoordXY = wherex() * CompresseurXY + wherey();		return CoordXY;
}

// On retire la compression
void Get_Coordinnates(int& X, int& Y, int XY)
{
	X = XY / CompresseurXY;
	Y = XY - X * CompresseurXY;
}

//	Permet de mettre en branle les scénarios des Levelss
void Check_Level_Script(int LVL_Script)
{
	
	// On check tout les Cycles	// faut mettre ça avant le lvl script. car le script se fit au temps actuel 
	// pour trigger des affaires. La fonction spawnbot par exemple peut stopper un spawn pour ce cycle. 

	Check_Spawn_Cycle();	// Refresh Timer des spawns
	Check_BOT_Cycle();		// Refresh Timer des Bots
	UI_Update_TimerAndStats();		// Affiche les différents Timer


	switch (LVL_Script)
	{
		case 1:	Level_1_Script(); break;
		/*case 2: Level_2_Script(); break;
		case 3: Level_3_Script(); break;
		case 4: Level_4_Script(); break;
		case 5: Level_5_Script(); break;
		case 6: Level_6_Script(); break;
		case 7: Level_7_Script(); break;
		case 8: Level_8_Script();*/
	}

	


	// On fait Spawner un BOT, et ensuite on le bouge. Dans cette ordre
	if (Spawn_this_Cycle)
	{
		if (BOT.TOT_Alive < MaxNumBOTS)	// Max de bots
		{
			SpawnBOT();
			Spawn_this_Cycle = false;
		}
		else
		{
			bool THEREISTOOMANYBOTSDUDE = true;
			if (THEREISTOOMANYBOTSDUDE)
				bool yourefucked = true;
		}
	}

	// On bouge tous les BOTS
	if (Move_BOTS_this_Cycle)
	{
		if (BOT.TOT_Alive > 0)			// Aucun BOT ne peut être bougés
		{
			Move_BOTS();
			Move_BOTS_this_Cycle = false;
		}
	}
}

void Check_Spawn_Cycle()
{
	if (Current_time >= Next_Spawn_Cycle)
	{
		Spawn_this_Cycle = true;
		Current_Spawn_Cycle = Next_Spawn_Cycle;	// j'ai pt pas besoin de Current_Spawn_Cycle
		Next_Spawn_Cycle = Current_Spawn_Cycle + Spawn_Cycle;
		Spwn_cycleTOT++;						// Le nombre de cycle de spawn depuis le début de la game
	}
}


void Check_BOT_Cycle()
{
	// Check Bot_Move_Cycle
	if (Current_time >= Next_BOT_MOVE_Cycle)
	{
		Current_BOT_MOVE_Cycle = Next_BOT_MOVE_Cycle;
		Next_BOT_MOVE_Cycle += BOT_Move_Cycle;
		Move_BOTS_this_Cycle = true;
	}
}

// Donne la bordure en face d'un bot
void Front_BOT_Boxside(int & Boxside)				// Boxside devient Frontboxside			
{													// Si Boxside = LEFT(1) alors FrontBoxside RIGHT(3)
	Boxside <= LEFT ? Boxside += 2 : Boxside -= 2;	// Si Boxside = Down(2) alors FrontBoxside UP(0)
}


// Donne la quantité de déplacement Max des bots pour chacune des bordures de spawn de BOTS
void MAX_BOTS_Steps_for_each_border(int LimitUP, int LimitLEFT, int LimitDOWN, int LimitRIGHT, int Box_to_Spawn)
{
	// Le nombre déplacement Max qu'un Bot peut parcourir selon son axe
	BOT.MaxBotDistanceX = LimitRIGHT - LimitLEFT + 1; // + Box_to_Spawn
	BOT.MaxBotDistanceY = LimitDOWN - LimitUP + 1;
	//int HalfwayX = BOT_tracker.MaxBotDistanceX / 2;
	//int HalfwayY = BOT_tracker.MaxBotDistanceY / 2;

}

// Donne la quantité de déplacement qu'un bot doit parcourir avant de sortir de la BOX
int Total_BOT_Steps_Before_Exit(int Boxside)
{
	int NumberOfSteps = 0;	// Le nombre steps max que le BOT devras faire avant de sortir
	
	switch (Boxside)
	{
	case UP:case DOWN:		NumberOfSteps = BOT.MaxBotDistanceY;	break;
	case LEFT:case RIGHT:	NumberOfSteps = BOT.MaxBotDistanceX;
	}
	
	return NumberOfSteps;

}

// Change la couleur du BOT selon sa progression
void BOT_Progression_Color(Colors & Color, int NumStepsLeft, int Max_Steps)
{
	int Halfway = Max_Steps / 2;	// Le bot est à moitié chemin >:| 
	int HURRY = 10;					// Il reste 10 bot moves!!
	
		if (NumStepsLeft > Halfway)
			Color = WHITE;
		else if (NumStepsLeft == Halfway)
			Color = LIGHT_YELLOW;
		else if (NumStepsLeft == HURRY)
			Color = LIGHT_RED;
}

// Pour vérifier si tu block un spawn and stuff
bool Check_Front_Spawn_If_Blocked(In boxside, In coord)
{
	bool Prevent_Spawn = false;
	for (size_t i = 0; i < MaxNumBOTS; i++)
	{
		if (front_Spawn_Block[boxside][coord][i] == true)
		{
			Prevent_Spawn = true; break;
		}
	}
		return Prevent_Spawn;
}

// Ceci permet d'empêcher la création d'un BOT directement en face d'un BOT déjà existants
void Block_Front_Spawn(int FrontBoxside, int coord, int Nb_Bot)
{
	Front_BOT_Boxside(FrontBoxside);	// Détermine la bordure droit devant le bot
	
	front_Spawn_Block[FrontBoxside][coord][Nb_Bot] = true;	// On Block le spawn 
	front_Spawn_COORD[Nb_Bot] = coord;						// Tableau pointer vers la coordonnée du Frontspawn `bloquer

	// On affiche la porte de sortie du bot!!!
	Get_Coordinnates(CoordX, CoordY, SpawnXY[FrontBoxside][coord]);	// Donne la coordonnée xy du spawn
	Affi_ou_Effa_BOT_Esc_Door(FrontBoxside, CoordX, CoordY);				// Fait apparaître la porte juste à côté
	
}

// Affiche la case ou le bot essaie d'atteindre pour s'enfuir(celle juste en dehors du terrain de jeu)
void Affi_ou_Effa_BOT_Esc_Door(int BoxSide, int& CoordX, int& CoordY, bool Effacer) 
{
	Polarisation Direction;
	char Sym = 178;

	// On va effacer à la place
	if (Effacer)
		Sym = ' ';


	/*void Destruction_Walls_Betwn_Links(int CoordLeft, Polarisation polarisation, Axe axe)
	{
		int CoordX, CoordY;
		int NbdeWalls;	// Le nombre de walls à saccager!

		// On va commencer la destruction à partir de la coordonnée de gauche vers la droite
		Goto_Coordinnates(CoordX, CoordY, CoordLeft);
		*/

	switch (BoxSide)
	{
	case UP:	CoordY = box.limit[UP];		break;
	case LEFT:	CoordX = box.limit[LEFT];	break;
	case DOWN:	CoordY = box.limit[DOWN];	break;
	case RIGHT:	CoordX = box.limit[RIGHT];
	}

	// On affiche la porte de sortie du bot!!!
	gotoxy(CoordX, CoordY); Change_Color(GRAY); cout << Sym;
	Change_Color(7);

}

// Le design du BOT, selon la bordure d'ou il provient(et non de sa direction!!!
void Design_BOT(BOT_Design &BOT_design,int BOT_Ind, int BoxSide)
{
	switch (BoxSide)
	{
	case UP:	BOT_design.BOT_Sym[BOT_Ind] = BOT_temp_Design[DOWN];		break;
	case LEFT:	BOT_design.BOT_Sym[BOT_Ind] = BOT_temp_Design[RIGHT];	break;
	case DOWN:	BOT_design.BOT_Sym[BOT_Ind] = BOT_temp_Design[UP];	break;
	case RIGHT:	BOT_design.BOT_Sym[BOT_Ind] = BOT_temp_Design[LEFT];
	}
}

// Le design du BOT, selon la bordure d'ou il provient(et non de sa direction!!!
void Design_BOT_Warning(char& wrngDesign, int BoxSide)
{
	switch (BoxSide)
	{
	case UP:	wrngDesign = BOT_Wrng_Design[UP];		break;
	case LEFT:	wrngDesign = BOT_Wrng_Design[LEFT];	break;
	case DOWN:	wrngDesign = BOT_Wrng_Design[DOWN];		break;
	case RIGHT:	wrngDesign = BOT_Wrng_Design[RIGHT];
	}
}

int Find_Next_SpawnBOT_Location();
void Validate_Next_SpawnBOT_Location();
void Check_Invalid_SpawnXY(Inv_SpCrd* deb, int  NumSpawnTOT);				// Vérifie la liste des coordxY des bots qui ont spawné durance ce cycle
void Check_Invalid_Spwn_Coord_Ind(Inv_Coord_ind* deb, Inv_Coord_ind* fin);	// Vérifie la liste des coord Indice des spawns qui ont déjà été invalidé durant ce cycle
// donc empêche de revenir sur la même coord invalidé si on s'est qu'elle n'est pas bonne

void CheckNextSpawnBlock();


void SpawnBOT()
{
	// Si on spawn plus qu'un bot, on veut empêcher que ceux-ci spawns au même endroit
	static Inv_SpCrd* debXY = NULL, * finXY = NULL, * itXY = NULL;		//	Pointe vers le début et la fin de la liste de spwns invalides

	// Création des pointeurs pour la liste d'indice de coord de spawns invalide
	static Inv_Coord_ind* deb = NULL, * fin = NULL, * it = NULL;		//	Pointe vers le début et la fin de la liste de Coord
	static int cptr = 0;												// Le nombre spawns Coord Indice qu'on a vérifié comme étant invalide
	static int cptrInv = 0;												// Le nombre de spawn invalidé (ceux qui sont réservé pour un bot uniquement durant ce cycle)
	static bool ValidCoord;
																		
	// Fonction pour trouver un spawn valide
	// int Find_Valide_Spawn(deb, fin, struct des contraintes)
	for (size_t NumSpawn = NumSpawnTOT; NumSpawn > 0; --NumSpawn)	// redéfinition de num spawn, considère dlete la variable globale!!
	{
		// SI ON SPAWN DURANT CE CYCLE
		if (Spawn_this_Cycle)
		{
			int BOT_Ind = 0;												// Indice du BOT qu'on spawn
			int CrdInterv = Intervalle(CoordIntv.min, CoordIntv.max);		// Donne une interval possible entre deux coord(// le min et le max doivent toujours être différents)

			// Génération d'une nouvelle COORD de spawnBOT
			do
			{
				ValidCoord = true;	// La coord Commence par être valide

				if (Random_Boxside)	// Si le spawn est invalidé, par la présence d'un block. On va trouver une autre COORD, Mais pas un nouveau côté de BoxSide
				{
					// On Décide sur quel Bordure le Spawn aura lieu 			
					if (HorizontalSpawn)
						rand() % 2 == 0 ? BoxSide = LEFT : BoxSide = RIGHT;	// Spawn Horizontal
					else
						if (VerticalSpawn)
							rand() % 2 == 0 ? BoxSide = UP : BoxSide = DOWN;	// Spawn Vertical
						else
							BoxSide = rand() % 4;	//	Bordure random

					// Si on a SpawnMultiple de scripté, de nature «same side» , on spawn les prochains Bots sur la même bordure
					//	en skipant la création de Boxside pour la prochaine boucle
					if (Same_Side)
						Random_Boxside = false;
				}


				if (Random_Spawn_COORD || !Spawn_Valide)	// Si le scripted spawn random, on invente une nouvelle coord random
				{
					if (BoxSide % 2 == 0)
						Indice_Spawn_COORD = rand() % MaxSpawn_CoordinatesX;
					else
						Indice_Spawn_COORD = rand() % MaxSpawn_CoordinatesY;
				}
				else
					if (CrdInterv && !Random_Spawn_COORD) // Si l'intervalle est autre chose que Zéro 					
						Indice_Spawn_COORD = rand() % (CrdInterv + 1) + CoordIntv.min;// Création d'une coord à l'int. de l'interval
																					// NOTE: ya du random, mais il est limité à l'intervalle

				NextSpawnXY = SpawnXY[BoxSide][Indice_Spawn_COORD]; // Le Spawn à valider

				// VALIDATION SPAWN!	

				// VÉRIFICATION DES ÉLÉMENTS DANS LA LISTE des indices déjà vérifiés
				it = deb;

				while (it) // ou tout simplement while (it)
				{
					if (Indice_Spawn_COORD == it->Ind)
					{
						ValidCoord = Spawn_Valide = false;				// La coordonnée est invalide
						break;
					}
					else
						it = it->nxt;					// passe au prochain élément
				}

				if (!ValidCoord)		// On recommence!
					continue;

				// Vérification de la coordonnée des bots déjà spawné durant ce cycle
				itXY = debXY;

				// YO SI CETTE LISTE EST AUSSI GRANDE QUE LE NOMBRE DE SPAWN COORD SUR UNE BORDURE, TU DEVRAIS CANCELLER LE 
				// RESTE DES SPAWNS
				// EN FAISANT BREAK; ET EN SETTANT LE NUMSPAWN À 0!

				while (itXY) // ou tout simplement while (it)
				{
					if (NextSpawnXY == itXY->spwnXY)
					{
						ValidCoord = Spawn_Valide = false;				// La coordonnée est invalide
						break;
					}
					else
						itXY = itXY->nxt;					// passe au prochain élément
				}

				if (!ValidCoord)		// On recommence!
					continue;

				for (Blockthisshit = 0; Blockthisshit <= MaxNumBOTS - 1; ++Blockthisshit)	//	On check si le spawn actuel est blocké
				{
					// Vérification: si un block équivaut au cycle actuel de Bot_move. On ne peut pas créer de BOTS sur cette COORD.
					if (Spawn_Block[BoxSide][Indice_Spawn_COORD][Blockthisshit] >= Current_BOT_MOVE_Cycle &&
						Spawn_Block[BoxSide][Indice_Spawn_COORD][Blockthisshit] < Next_BOT_MOVE_Cycle)
					{
						//Goto_Coordinnates(CoordX, CoordY, NextSpawnXY);	// Pour voir ou était le spawn invalide


						 // FIX THIS:
						// SI LA BOXSIDE À CHANGE, TA LISTE NE VAUT PLUS RIEN
						// Faudrait que tu fasse une liste "spécifiquement " pour une seule boxside
						// genre if cptr + cptrInv == MaxSpawnCoordX; RandomBoxside == true;


						// Ajoute l'indice de coord dans la liste des coord invalide
						if (!Random_Boxside)
						{
							if (!fin)	// Liste vide						Ce lis: si False: donc 0, donc NULL, donc Liste vide												
								deb = fin = new Inv_Coord_ind;	// Le premier de la liste						
							else
							{
								fin->Ind = Indice_Spawn_COORD;
								fin = fin->nxt = new Inv_Coord_ind;
							}

							cptr++;							// Augmententation du nombre de Coord invalidé

							if (cptr == CrdInterv)			// Chacunes des Coords sont invalides? Ceci active le random pour qu'on spawn ailleurs à la place
								Random_Spawn_COORD = true;
						}
						Spawn_Valide = false;
						break;
					}
				}
				// Si on atteint la maximum de coord spawn sans trouver de block;
				if (Blockthisshit == MaxNumBOTS)
					Spawn_Valide = true;

				// Ceci vérifie la présence d'un front spawn block 
				if (Check_Front_Spawn_If_Blocked(BoxSide, Indice_Spawn_COORD))
				{
					Spawn_Valide = false;
					Random_Spawn_COORD = true;
				}

			} while (!Spawn_Valide);



			// Création d'un BOT
			for (BOT_Ind = 0; BOT_Ind < MaxNumBOTS; ++BOT_Ind)	// Si on arrive au Nombre MAx de Bot????? Faudrait jamais utiliser la fonction 
			{
				if (BOT_Ind == MaxNumBOTS - 1)
					BOT_Ind = MaxNumBOTS - 1;

				if (BOTXY[BOT_Ind] == 0)
				{
					switch (BoxSide)
					{
					case 0: BOT_Direction[BOT_Ind] = DOWN; break;
					case 1:	BOT_Direction[BOT_Ind] = RIGHT;break;
					case 2:	BOT_Direction[BOT_Ind] = UP;break;
					case 3:	BOT_Direction[BOT_Ind] = LEFT;
					}

					BOTXY[BOT_Ind] = NextSpawnXY;

					// La coord compressé du bot qu'on spawn est listé dans les coordXY invalide de spw de ce cycle
					if (NumSpawn > 1)	// sI ON SPAWN PLUS QU'UNE FOIS	// Faut aussi la débloquer à la fin de la fonction???
					{
						if (finXY == NULL)	// Liste vide			
							debXY = finXY = new Inv_SpCrd;	// Le premier de la liste

						finXY->spwnXY = NextSpawnXY;
						finXY = finXY->nxt = new Inv_SpCrd;
						cptrInv++;							// Le nombre de bots qui invalide des coord durant le spawn multiple

						if(cptrInv == CrdInterv)			
							Random_Spawn_COORD = true;
					}
					break;
				}
			}

			// Donne la distance que doit franchir le BOT pour sortir de la box
			BOT.warCountdown[BOT_Ind] = SPWN_DLAY;				// Le nombre de cycle avant que le bot ne commence son avancé!
			BOT.MaxSteps[BOT_Ind] = Total_BOT_Steps_Before_Exit(BoxSide);
			BOT.StepsToEscape[BOT_Ind] = BOT.MaxSteps[BOT_Ind];

			// Le coordonnée du spawn directement en face du bot qu'on vient de créer sera blocké jusqu'à la destruction de notre BOT
			Block_Front_Spawn(BoxSide, Indice_Spawn_COORD, BOT_Ind);

			// Initialisation du Design du Bot
			Design_BOT(BOT_design, BOT_Ind, BoxSide);
			Design_BOT_Warning(BOT.warSym[BOT_Ind], BoxSide);
			BOT.nbSym[BOT_Ind] = 1;		// Le design sera à deux symboles

			//// Affichage du BOT
			//
			//Goto_Coordinnates(CoordX, CoordY, BOTXY[BOT_Ind]);
			//cout << BOT_design.BOT_Sym[BOT_Ind];
			
			BOT.TOT_Alive++;				// Incrémente le nombre de bots!
			BOT.TOT_Spawned++;

			//CRÉATION SPAWN BLOCK 				
			int Side;	// side 0 ou 1 . J'ai pas appliqué de changement pour celui-là

			Direction spwn_Side[2] = {};					// Désigne quels sont les deux Bordures de Spawns à blocker
			Distance from_BOT_To_Side[2] = {};				// Représente la distance séparant le BOT à la Bordure perpendiculaire. Sert à trouver le premier point d'intersection
			Distance from_SBLCK_To_Intersection[Bi];//AJOUTÉ	// Représente la distance séparant le BOT au point d'intersection. Sert à trouver le nombre de cycles de mouvement des bots avantler premier impact
			int cycles_Before_Impact[2] = {};				// Le nombre de Cycle de mouvements des BOTS avant le premier impact. On le trouve par cette équation(la distance entre le bot et l'intersection - la distance entre Block et l'intersection): from_BOT_To_Side - from_BOT_To_Intersection 

			CoordinatesXY frst_Spwn_Intersection[2] = {};	// La coordonnée perpendiculaire au spawn, X OU Y(selon la direction du mouvement du BOT tout juste spawné) de la première colision perpendiculaire possible. Sert à trouver la première COORDXY du premier Block Possible
			CoordinatesXY next_Closest_Spwn[2] = {};		// Cette coordonnée se retrouve à une distance de Spawn plus loin que first_BlockXY. Entre ces deux coordonnées se trouve forcément le premier Spawn à blocker
			CoordinatesXY first_BlockXY[2] = {};			// Sert d'outil de comparaison pour trouver la première COORDXY de spawn à blocker . À noter que cette coordonnée peut se trouver entre deux spawns. On utilise donc une deuxième COORD pour la trouver.

			In first_Block_Coord[2] = {};					// La coordonnée du premier Spawn à blocker. Ceci est égal à son indice dans le tableau des spawns
			Time min_Time_Impact[2] = {};					// Désigne quel est le premier Cycle de Mouvement des Bots ou un spawn provoquerait une colision

			Distance betwn_Spwn = 0;							// La distance séparant chaque spawn perpendiculaire. Soit ShipMoveX ou ShipMoveY
			bool no_Need_To_Block[2] = {};					// Désigne le fait que le BOT actuel est trop loin pour qu'un spawn perpendiculaire créer une colision
			Polarisation polar_BOT = Pos;					// La polarisation positive ou négative du mouvement du BOT qu'on vient de créer. Si négatif, on va inversé la direction dans lequel on va passer dans le tableau de spawn à blocker
			bool spwn_Found = false;						// Le premier Spawn à blocker est trouvé!


			 // On dirais qu'il n'y en aura pas de transition, je vais garder tout ça dans la fonction
			 // Je sais pas comment structué ça. On dirait que je devrait faire des mini-structures dans ma structure
			 // et que ça devrait pas être globale aussi
			 // dans le fond tout reste dans cette fonction anyway
			 // je vais juste changer les noms pour que ça fit parfaitement. Les noms de types aussi

			// Permet de passer soit de haut en bas, ou de bas en haut de le tableau de spawn suivant pour inscrire les bonnes valeurs.
			//	Permet aussi de déterminer dans quel direction le spawn le plus proche est.
			if (BoxSide == DOWN || BoxSide == RIGHT)
				polar_BOT = Neg;



			// Pour déterminer quelles sont les deux bordures perpendiculaires à blocker. ET LA DISTANCE entre chaque spawn sur ces bordures	(FONCTION 1)
			switch (BoxSide)
			{
			case UP:	case DOWN:	spwn_Side[0] = LEFT; spwn_Side[1] = RIGHT; betwn_Spwn = HeroMoveY; MaxSpawnBlocks = MaxSpawn_CoordinatesY; break;
			case LEFT:	case RIGHT:	spwn_Side[0] = UP; spwn_Side[1] = DOWN; betwn_Spwn = HeroMoveX; MaxSpawnBlocks = MaxSpawn_CoordinatesX;
			}

			// Pour déterminer la distance entre le Le bot qu'on vient de spawn et la bordure perpendiculaire (FONCTION 2)
			switch (BoxSide)
			{
			case UP:	case DOWN:	from_BOT_To_Side[0] = CoordX - spawn.limit[LEFT];			//SideA
				from_BOT_To_Side[1] = spawn.limit[RIGHT] - CoordX; break;	//SideB

			case LEFT:	case RIGHT:	from_BOT_To_Side[0] = CoordY - spawn.limit[UP];				//SideA
				from_BOT_To_Side[1] = spawn.limit[DOWN] - CoordY;	break;	//SideB
			}
			// Jai ajouté la valeur du delay ici même si ça fait aucun sens dans la structure. Je crois que ce cheat va marcher doe
			from_BOT_To_Side[0] += SPWN_DLAY;
			from_BOT_To_Side[1] += SPWN_DLAY;

			// Pour déterminer la coordonnée(x ou y) du point d'intersection du premier Spawn a blocker (FONCTION 3)
			for (Side = 0; Side < 2; ++Side)
			{
				switch (BoxSide)			
				{
				case UP:	frst_Spwn_Intersection[Side] = from_BOT_To_Side[Side] + spawn.limit[UP];	break;
				case DOWN:	frst_Spwn_Intersection[Side] = spawn.limit[DOWN] - from_BOT_To_Side[Side];	break;
				case LEFT:	frst_Spwn_Intersection[Side] = from_BOT_To_Side[Side] + spawn.limit[LEFT];	break;
				case RIGHT:	frst_Spwn_Intersection[Side] = spawn.limit[RIGHT] - from_BOT_To_Side[Side];
				}
			}

			// Pour Déterminer la première COORDXY  sur les deux bordure de spawn qui peut créer un bot qui ferait une colision,(FONCTION 4)
			switch (BoxSide)
			{
			case UP:	case DOWN:	first_BlockXY[0] = (spawn.limit[LEFT] * CompresseurXY) + frst_Spwn_Intersection[0]; 			//SideA
				first_BlockXY[1] = (spawn.limit[RIGHT] * CompresseurXY) + frst_Spwn_Intersection[1]; break;		//SideB

			case LEFT:	case RIGHT:	first_BlockXY[0] = (frst_Spwn_Intersection[0] * CompresseurXY) + spawn.limit[UP];			//SideA
				first_BlockXY[1] = (frst_Spwn_Intersection[1] * CompresseurXY) + spawn.limit[DOWN];break;														//SideB
			}
			// Optimize
			// for (Side = 0; Side < 2; ++Side)
			//	case up: case Down: 	if(Side == 0) limit = Left
			//								else	limit = right;
			//								first_BlockXY[Side] = (spawn.limit[limit] * CompresseurXY) + frst_Spwn_Intersection[Side]; 



			// Pour empêcher de créer un block si le spawn est trop loin de la bordure perpendiculaire	(FONCTION 5)
			for (int Side = 0; Side < 2; ++Side)
				switch (BoxSide)
				{
				case UP:	case DOWN:
					if (frst_Spwn_Intersection[Side] > box.limit[DOWN] || frst_Spwn_Intersection[Side] < box.limit[UP])
						no_Need_To_Block[Side] = true;  break;

				case LEFT:	case RIGHT:
					if (frst_Spwn_Intersection[Side] > box.limit[RIGHT] || frst_Spwn_Intersection[Side] < box.limit[LEFT])
						no_Need_To_Block[Side] = true;  break;


				}			// Optimize: remplacer down up, right left, par Limit[Side)


			// Pour déterminer quel est le closest Spawn	(FONCTION 6)
			// On utilise ClosestSpawn pour trouver spawn suivant si le BlockSideXY n'est finalement pas une spawn Coord
			for (Side = 0; Side < 2; ++Side)	//Optimize: void FindClosestSPawn(Side side)	 Side = au type Side
			{									// Tu met le côté de la bordure (A ou B) en paramètre d'entrée
				switch (BoxSide)
				{
				case UP:	case DOWN:	next_Closest_Spwn[Side] = first_BlockXY[Side] + betwn_Spwn * polar_BOT; break;
				case LEFT:	case RIGHT:	next_Closest_Spwn[Side] = (first_BlockXY[Side] + betwn_Spwn * CompresseurXY * polar_BOT);
				}
			}

			// Ceci ajuste la distance minimale et la coordonnée du premier spawn à blocker

			for (Side = 0; Side < 2; ++Side)
			{
				if (no_Need_To_Block[Side] == true)
					continue;

				for (int COORD = 0; COORD < MaxSpawnBlocks; ++COORD)
				{
					// Voici les deux conditions qui permettent de trouver la COORDXY du premier Spawn a bloquer
					// C'est though à catcher alors voici une illustration: 
					//  SpawnXY = 1	(Le premier spawn  à blocker, les S sont d'autres SPawnXY)							
					//	Block_Side = B	(La Coord de Bordure à ajuster)			
					//	Closest_Spawn = C	(La Coord de Bordure a ajuster, + l'intervalle qui sépare 1 spawn)

					if (polar_BOT == Neg)													//	Si on va Blocker de droite à gauche (polar_BOT = Neg)	
						if (SpawnXY[spwn_Side[Side]][COORD] <= first_BlockXY[Side])
							if (SpawnXY[spwn_Side[Side]][COORD] > next_Closest_Spwn[Side])	//	1:			S---C-----1------B--S
								spwn_Found = true;											//  			(1 > C)		(1 <= B)

					if (polar_BOT == Pos)													// Si on va blocker de gauche à droite	(polar_BOT = Pos)
						if (SpawnXY[spwn_Side[Side]][COORD] < next_Closest_Spwn[Side])
							if (SpawnXY[spwn_Side[Side]][COORD] >= first_BlockXY[Side])		//	2:			S---B-----1------C--S
								spwn_Found = true;											//				 (1 >= B)		(1 < C)

					if (spwn_Found)
					{
						/* not important?*/
						// Min DistSide est useless bien franchement
						if (first_BlockXY[Side] != SpawnXY[spwn_Side[Side]][COORD])
						{
							//Le first spawn intersection correspond au X ou Y du SpawnXY qu'on va block
							// Cette merde on l'utilise plsu aprèes
							/*// On ajuste également la Distance minimale
							Static_Coord_First_Block[Side] = SpawnXY[Block_Side[Side]][COORD] / CompresseurXY;	// Si la Min_Dist_side est sur l'axe des X

							if (Bot_Move_Axis == ShipMoveY)// Si la Min_Dist_side est sur l'axe des Y
								Static_Coord_First_Block[Side] = Block_SideXY[Side] - Static_Coord_First_Block[Side] * CompresseurXY;*/
								/*

								First_Spawn_Intersection[Side] = CoordX - spawn.limit[LEFT];
								Static_Coord_First_Block[Side] = spawn.limit[DOWN] - First_Spawn_Intersection[Side];
								Block_SideXY[Side] = (spawn.limit[LEFT] * CompresseurXY) + Static_Coord_First_Block[Side];*/

								// pas besoin de ça si tu set tes affaires comme il faut :P
								//			motherfucker....
								// je me parle à moi même. Send Help!     and nudes
						}




						// On enregistre l'indice de cette Coordonnée
						first_Block_Coord[Side] = COORD;

						// On change le BlockSide pour la COORD SPawnXY #1
						first_BlockXY[Side] = SpawnXY[spwn_Side[Side]][COORD];

						// Pour déterminer la distance qui sépare le spawn actuel et le point d'intersection (FONCTION 8)
						// (cette distance sera toujours supérieur ou égal a la distance entre le block et le point d'intersection :from_BOT_To_intersection[Side])

						switch (BoxSide)
						{
						case UP:;
							// Faut isoler le Y de la coordonnée du spawn actuelle, en enlevant le x du nombre compressé 
							CoordX = SpawnXY[spwn_Side[Side]][COORD] / CompresseurXY;
							frst_Spwn_Intersection[Side] = SpawnXY[spwn_Side[Side]][COORD] - CoordX * CompresseurXY;

							// Voilà. Ensuite on fait le calcul pour trouver la DISTANCE minimale à parcourir pour l'intersection
							from_SBLCK_To_Intersection[Side] = frst_Spwn_Intersection[Side] - spawn.limit[UP];break;
						case DOWN:
							// Faut isoler le Y en enlevant le x du nombre compressé 
							CoordX = SpawnXY[spwn_Side[Side]][COORD] / CompresseurXY;
							frst_Spwn_Intersection[Side] = SpawnXY[spwn_Side[Side]][COORD] - CoordX * CompresseurXY;

							// Voilà. Ensuite on fait le calcul pour trouver la DISTANCE minimale à parcourir pour l'intersection
							from_SBLCK_To_Intersection[Side] = spawn.limit[DOWN] - frst_Spwn_Intersection[Side];	break;

						case LEFT:;
							//ICI il faut isoler le x à la place en enlevant le y du nombre compressé  
							frst_Spwn_Intersection[Side] = SpawnXY[spwn_Side[Side]][COORD] / CompresseurXY;

							// Voilà. Ensuite on fait le calcul pour trouver la DISTANCE minimale à parcourir pour l'intersection
							from_SBLCK_To_Intersection[Side] = frst_Spwn_Intersection[Side] - spawn.limit[LEFT];	break;
						case RIGHT:
							//ICI il faut isoler le x à la place en enlevant le y du nombre compressé  
							frst_Spwn_Intersection[Side] = SpawnXY[spwn_Side[Side]][COORD] / CompresseurXY;

							// Voilà. Ensuite on fait le calcul pour trouver la DISTANCE minimale à parcourir pour l'intersection
							from_SBLCK_To_Intersection[Side] = spawn.limit[RIGHT] - frst_Spwn_Intersection[Side];	break;
						}

						// Pour trouver le nombre de cycle de difference entre le spawn, et le block (FONCTION 9)
						cycles_Before_Impact[Side] = from_SBLCK_To_Intersection[Side] - from_BOT_To_Side[Side];

						spwn_Found = false;
						break;
					}

				}

			}

			// BOT SPAWN DELAI BEFORE MOVING TO OUR DOOM

			// Si tu veux ajouter un Délai avec un Q visuel.	T'ajuste à ajouter : int DELAY = 3 * BOT_Move_Cycle;
			// Apres dans la section BotMove: EX:  BotDelay[i] = 3;		if( BotDelay[i] >0) 
																			//BotDelay[i]--; cout << un Symbole de Square genre!!!!
			//esle -------> On bouge le BOT!!!!


			// On Calcul le temps minimal que ça prend pour un impact
			for (int Side = 0; Side < 2; ++Side)	//	Min_Dist_side[Side]( * 1) ( 1= Vitesse du Bot) * BOT_Move_Cycle
			{
				if (no_Need_To_Block[Side] == false)
					min_Time_Impact[Side] = Current_BOT_MOVE_Cycle + cycles_Before_Impact[Side] * BOT_Move_Cycle;
			}

			//	Enregistrement de chacun des Cycles lors duquel les SPawnCoord seront Blockés!

			for (Side = 0; Side < 2; ++Side)	// side = Left; Side < Right;
			{
				if (no_Need_To_Block[Side] == false)
				{
					for (In COORD = first_Block_Coord[Side]; COORD < MaxSpawnBlocks; ++COORD)
					{
						//// On test le spawn block!
						//if (COORD == first_Block_Coord[Side])	// Affiche seulement le premier block 
						//{
						//	Goto_Coordinnates(CoordX, CoordXY, SpawnXY[spwn_Side[Side]][COORD]);
						//	cout << min_Time_Impact[Side]; // /(double)CLOCKS_PER_SEC; // Le cycle ou on va bloqué un spawn.
						//}
						Spawn_Block[spwn_Side[Side]][COORD][BOT_Ind] = min_Time_Impact[Side];

						// le prochain spawn qui sera blocké correspond	au temps que ça va prendre pour le bot à s'y rendre
						min_Time_Impact[Side] += BOT_Move_Cycle * betwn_Spwn;	// là il se déplace de un
							// Sinon tu peux changer ça pour genre BOTSpeed = Bot_Move_Axis ou 1
							// Min_Time_Impact[Side] +=  Bot_Move_Cycle * (Bot_Move_Axis / BotSpeed)
							// VOila!!			
							// Pour l'instant, change pas la vitesse d'un bot pour qu'un déplacement permettrait de skip un spawn
							// Ça viendrais tout fucker!!!

						// On descend le tableau si le Bot se dirige vers des spawns de valeurs décroissantes
						if (polar_BOT == Neg) {
							COORD -= 2;
							if (COORD <= -2) break;
						}
					}
				}
			}


		}

	}	//	fin spawn fonction

		// Variables à réinitialiser 
		// tu dois réinisialiser la liste conentant tout les adresses invalides des spawn multiples

		// Recyclage de la liste des coord Indice
		while (it = deb) // affectation (it = deb) suivi du test sur la valeur de it != NULL
		{
			deb = deb->nxt;
			delete it;
		}
		fin = NULL;

		// Recyclage de la liste des spawns invalidé
		while (itXY = debXY) // affectation (it = deb) suivi du test sur la valeur de it != NULL
		{
			debXY = debXY->nxt;
			delete itXY;
		}
		finXY = NULL;

		Spawn_this_Cycle = false;	
		HorizontalSpawn = false;
		VerticalSpawn = false;
		Random_Spawn_COORD = true;
		Random_Boxside = true;
		NextSpawnXY = 0;
				
	
}// FIN SPAWN BLOCK et Création de BOTS

void Move_BOTS()
{
	int BOT_IS_OUT;		// Donne la limit qui défini si un BOT est sortie de la box ou non
	int Coord_OUT;		// Donne l'axe de déplacement qu'on va comprarer pour savoir sir le bot est sortie
	bool EffacerBOT = true;	// Permet d'effacer les BOTS

	for (int bot = 0; bot < MaxNumBOTS; ++bot)
	{
		if (BOTXY[bot] != 0)
			if(BOT.warCountdown[bot]== 0)			
			{
				// On efface le bot
				Afficher_ou_Effacer_BOT(bot, EffacerBOT);

				switch (BOT_Direction[bot])
				{
				case UP:	CoordY--; BOT_IS_OUT = box.limit[UP];		Coord_OUT = CoordY; break;	//On cout les différentes parties du BOT aussi, selon sa direction
				case LEFT:	CoordX--; BOT_IS_OUT = box.limit[LEFT];		Coord_OUT = CoordX; break;
				case DOWN:	CoordY++; BOT_IS_OUT = box.limit[DOWN];		Coord_OUT = CoordY; break;	// remplacer ++ -- par BotSpeed[m]; o.5, 2, Shipmove
				case RIGHT:	CoordX++; BOT_IS_OUT = box.limit[RIGHT];	Coord_OUT = CoordX;
				}

				// On incremente la COORd du BOT
				gotoxy(CoordX, CoordY);
				BOTXY[bot] = CoordX * CompresseurXY + CoordY;

				//**********Ceci Test si deux BOTS peuvent se percuter ***************//////
				for (size_t i = 0; i < MaxNumBOTS; i++)
				{
					if (BOTXY[bot] == BOTXY[i] && bot > i)
					{
						cvmSetColor(JAUNE);
						cout << 'X'; Beep(400, 100);
						_getch();
					}
				}

				// Incrémentation du mouvement
				BOT.TotalSteps[bot]++;
				BOT.StepsToEscape[bot]--;

				// On check quelle couleur aura le BOT, selon la distance qu'il à parcouru
				BOT_Progression_Color(BOT.color[bot], BOT.StepsToEscape[bot], BOT.MaxSteps[bot]);

				//// Affiche le Bot!"!!! selon sa couleur....	/*Disabled for now*/
				//changeColor(BOT_tracker.color[bot]); 
				//cout << BOT_design.BOT_Sym[bot];	
				//changeColor(WHITE);	// Remet la couleur normal.	// avant destruction	// À vérifier si je le fait en double

				// Si un BOT sort de la BOX
				if (BOT.StepsToEscape[bot] == 0 && BOT.TotalSteps[bot] != 0)											//if (Coord_OUT == BOT_IS_OUT)
				{
					HeroTakeDamage(hero);	// Le hero prend du dégât!

					if (!hero.health)
						BOT_Escape = true;				// Pour FINIR LA GAME SI UN BOT SORT

					// On Détruit(enfin) un BOT et tout les blockages de spawn qu'il a engendré
					Destroy_BOT_and_Spawn_Blocks(bot, front_Spawn_COORD[bot]);

					BOTXY[bot] = 0;
					BOT_Direction[bot] = 0;
				}

				// Si un BOT rencontre un mur
				for (int w = 0; w < C; w++)
					if (BOTXY[bot] == Wall[w] && BOTXY[bot] != 0)		// Ma manière lazy de pas tout reset à -1....
					{
						//Destruction des MURS, et Structures de liens
						PreDestruction_par_BOT_Impact(BOT_Direction[bot], CoordXY);

						// On Détruit(enfin) un BOT et tout les blockages de spawn qu'il a engendré
						Destroy_BOT_and_Spawn_Blocks(bot, front_Spawn_COORD[bot]);	break;
					}
			}
	}
	//Swag_Animation();
	
	EffacerBOT = false;

	// Ceci réaffiche les bots pour éviter leur disparition quand il sont proche 
	for (int bot = 0; bot < MaxNumBOTS; ++bot)
	{
		if (BOTXY[bot] != 0)
		{
			if (UPD_BOT_Warning_Cycles(bot))
				UI_AF_BOT_Warning(bot);
			else
				Afficher_ou_Effacer_BOT(bot, EffacerBOT);
		}
	}


}

// Sert à updater on est au combientième cycle de warning du bot
int UPD_BOT_Warning_Cycles(int Ind)
{
	if (!BOT.warCountdown[Ind])
		return 0;
	else
		return BOT.warCountdown[Ind]--;		// Décrémente le cycle de warning
}

// Affiche le warning que le bot s'en vient ( clignotement, alterne entre effacement et symbole : >, ' ', >, ' ' 
void UI_AF_BOT_Warning(int Ind)
{
	Goto_Coordinnates(CoordX, CoordY, BOTXY[Ind]);		// position du Bot actuel

	if (BOT.warCountdown[Ind] % 2 == 0)	// Je pourrais mettre de la couleur si on se rapproche
	{
		if (BOT.warCountdown[Ind] < 6)
		{
			if (BOT.warCountdown[Ind] < 3)
				Change_Color(LIGHT_RED);			// 3 cycle left
			else
				Change_Color(LIGHT_YELLOW);		// 6 cycle left

			cout << BOT.warSym[Ind];
		
			Change_Color(WHITE);
		}
	}
	else
		cout << ' ';
}

// Affiche un BOT selon son design(le nombre de charactères qu'il prend dans la console
void Afficher_ou_Effacer_BOT(int BOT_In, bool Effacer)
{
	char Sym;

	if (Effacer)
		Sym = ' ';		// On efface le Bot au lieu de l'afficher
	else {
		Change_Color(BOT.color[BOT_In]);	// La couleur du BOT
		Sym = BOT_design.BOT_Sym[BOT_In];		// Le symbole du Bot
	}

	switch (BOT.nbSym[BOT_In])
	{
	case 1: Goto_Coordinnates(CoordX, CoordY, BOTXY[BOT_In]); cout << Sym; break;
	case 2:	Afficher_BOT_Design_2(BOT_In, Sym); break;
	}

	Change_Color(WHITE);		// On reviens à la couleur normale
}

// Affiche un BOT avec le desing à deux charactères
void Afficher_BOT_Design_2(int BOT_In, char Sym)
{

	Goto_Coordinnates(CoordX, CoordY, BOTXY[BOT_In]); cout << Sym;		// Le premier Sym

	switch (BOT_Direction[BOT_In])	// Le deuxième Symbole
	{
	case UP:	case DOWN:	 cout << Sym;	break;
	case LEFT:	case RIGHT:	gotoxy(CoordX, CoordY + 1); cout << Sym;
	}


}
							
// reset pleins de valeur pour restart une game							
void Reset_Everything___or_almost()
{
	Reset_Tableau_Unidimensionelle_A_Une_Valeur_confortable_pour_les_gens_qui_regardent_leHockey_le_dimanche_avec_une_tit_bier(LinkXY, ML);
	Reset_Tableau_Unidimensionelle_A_Une_Valeur_confortable_pour_les_gens_qui_regardent_leHockey_le_dimanche_avec_une_tit_bier(VitalLinkXY, ML);
	Reset_Tableau_Unidimensionelle_A_Une_Valeur_confortable_pour_les_gens_qui_regardent_leHockey_le_dimanche_avec_une_tit_bier(VitalCompteur, ML);
	Reset_Tableau_Unidimensionelle_A_Une_Valeur_confortable_pour_les_gens_qui_regardent_leHockey_le_dimanche_avec_une_tit_bier(LinkIndice, ML);
	Reset_Tableau_Unidimensionelle_A_Une_Valeur_confortable_pour_les_gens_qui_regardent_leHockey_le_dimanche_avec_une_tit_bier(LinkDirection, ML);
	Reset_Tableau_Unidimensionelle_A_Une_Valeur_confortable_pour_les_gens_qui_regardent_leHockey_le_dimanche_avec_une_tit_bier(BOT_Direction, MaxNumBOTS);
	Reset_Tableau_Unidimensionelle_A_Une_Valeur_confortable_pour_les_gens_qui_regardent_leHockey_le_dimanche_avec_une_tit_bier(BOTXY, MaxNumBOTS);
	BOT = {};
	// fuck a you			front_Spawn_COORD[i] = -1;
	for (size_t i = 0; i < MaxNumBOTS; i++)
		front_Spawn_COORD[i] = -1;
	// fuck a you	front_Spawn_Block
	for (size_t i = 0; i < 4; i++)
		for (size_t j = 0; j < MaxSpawn_COORD; j++)
			for (size_t k = 0; k < MaxNumBOTS; k++)
				front_Spawn_Block[i][j][k] = 0;
	Reset_Tableau_Tridimensionelle_avec_une_tite_sauce_brune_a_coté_pis_des_patates(Spawn_Block);
	Le_Boute = false;

}

// Reset un tableau
void Reset_Tableau_Unidimensionelle_A_Une_Valeur_confortable_pour_les_gens_qui_regardent_leHockey_le_dimanche_avec_une_tit_bier(int Tableau[], int MAX)
{
	for (size_t i = 0; i < MAX; i++)
		Tableau[i] = 0;
}

// Reset un Tableau tri-dimensionelle
void Reset_Tableau_Tridimensionelle_avec_une_tite_sauce_brune_a_coté_pis_des_patates(int Tableau[4][MaxSpawn_COORD][MaxNumBOTS])
{
	for (size_t i = 0; i < 4; i++)
		for (size_t j = 0; j < MaxSpawn_COORD; j++)
			for (size_t k = 0; k < MaxNumBOTS; k++)
				Tableau[i][j][k] = -1;

}

//***********  //***********  //***********	 //***********	//***********  //***********  //***********	 //***********	//***********
// LES EVENT*  // LES EVENT*  // LES EVENT*	 // LES EVENT*	// LES EVENT*  // LES EVENT*  // LES EVENT*	 // LES EVENT*	// LES EVENT*
//***********  //***********  //***********	 //***********	//***********  //***********  //***********	 //***********	//***********


// Le joueur est prit dans une sorte de box et doit utiliser les touchent de déplacmeent pour sortir!
void EV_Box_Trap()
{
	char mouvement;
	Coord coord;									// Cooronnées pour affichage
	Coord depart = { coord.X, coord.Y };			// Position de départ
	Polarisation PoX, PoY;							// Polarisation dans la console

	C_D Wallhit = 0;								// Compte le nombre d'input du joueur
	int MaxHits = 18;								// nombre de hit pour sortir de la box
	int lig = 3, col = 3;							// nombre de lignes et de colonnes sur la box
	Colors color = BRIGHT_WHITE;					// Couleur de la box
	bool Effacer = true;							// Efface la Box

	UI_Afficher_Box(depart.X, depart.Y, lig, col, color, false, 160);				// L' affichage D'une BOX autours d'un point central
	EV_MsgAf_Touche_Mouvement(depart.X, depart.Y - 13);	// Affiche les touches de mouvements
	UI_Aff_String(10, 1, "You want to get out? Why? It's pointless anyway.", 50, LIGHT_RED); Sleep(200);
	UI_Aff_String(10, 50,  "Try faster maybe? I think you can do it", 50, LIGHT_YELLOW); Sleep(200);

	while (Wallhit <= MaxHits)
	{
		UI_Afficher_Box(depart.X, depart.Y, lig, col, color);				// L' affichage D'une BOX autours d'un point central
		Change_Color(LIGHT_GREEN);	gotoxy(depart.X, depart.Y); cout << AllPlyrSym[4];		// Coord de départ

		while (_kbhit())
			_getch();

		//Enregistre une touche de mouvement
		mouvement = toupper(_getch());

		PoX = PoY = NUL;		// reset la polarisation

		switch (mouvement)
		{
		case 'A':PoX = Neg;Wallhit++;	break;
		case 'D':PoX = Pos;Wallhit++;	break;
		case 'W':PoY = Neg;Wallhit++;	break;
		case 'S':PoY = Pos;Wallhit++;	break;
		}

		gotoxy(depart.X, depart.Y); cout << ' ';						// Coord de départ

		coord.X = depart.X + PoX; coord.Y = depart.Y + PoY;			//Saute sur le mur
		UI_Aff_ET_Del_Char(coord.X, coord.Y, AllPlyrSym[4], 10, GREEN);

		coord.X += PoX * 2; coord.Y += PoY * 2;			//Saute sur le mur
		UI_Aff_ET_Del_Char(coord.X, coord.Y, AllPlyrSym[4], 8, LIGHT_PURPLE);
		//Afficher_Box(depart.X, depart.Y, 5, 5, LIGHT_AQUA);

		coord.X += PoX * 2; coord.Y += PoY * 2;			//Saute sur le mur
		UI_Aff_ET_Del_Char(coord.X, coord.Y, AllPlyrSym[4], 8, LIGHT_RED);
		//Afficher_Box(depart.X, depart.Y, 5, 5, LIGHT_BLUE);

		coord.X += PoX * 8; coord.Y += PoY * 8;			//Saute sur le mur
		UI_Aff_ET_Del_Char(coord.X, coord.Y, AllPlyrSym[4], 8, YELLOW);
		//Afficher_Box(depart.X, depart.Y, 5, 5, LIGHT_PURPLE);

		coord.X -= PoX * 4; coord.Y -= PoY * 4;			//Saute sur le mur
		UI_Aff_ET_Del_Char(coord.X, coord.Y, AllPlyrSym[4], 8, WHITE);
		//Afficher_Box(depart.X, depart.Y, 5, 5, LIGHT_YELLOW);

		coord.X -= PoX; coord.Y -= PoY;				//Saute sur le mur
		UI_Aff_ET_Del_Char(coord.X, coord.Y, AllPlyrSym[4], 15, LIGHT_AQUA);

		//if ((Wallhit >= 13))
		//	color = LIGHT_RED;
		//else if ((Wallhit >= 8))
		//	color = LIGHT_GREEN;
		///*else if ((Wallhit >= 8))
		//	color = LIGHT_RED;*/
		//else if (Wallhit >= 4)
		//	color = LIGHT_YELLOW;
		//else
		//	color = BRIGHT_WHITE;

		switch (Wallhit)
		{
		case 1:		case 8:		case 15:	color = LIGHT_RED;	break;
		case 2:		case 9:		case 16:	color = LIGHT_BLUE;		break;
		case 4:		case 10:	case 17:	color = LIGHT_GREEN;	break;
		case 3:		case 11:	case 18:	color = LIGHT_AQUA;		break;
		case 5:		case 12:	case 19:	color = LIGHT_PURPLE;	break;
		case 6:		case 13:	case 20:	color = BRIGHT_WHITE;		break;
		case 7:		case 14:	case 21:	color = LIGHT_YELLOW;	break;

		}
		switch (Wallhit)
		{
		case 3:
		case 9:
		case 12:
		case 15:
		case 18:lig = col += 2;
		}


	}

	UI_Afficher_Box(depart.X, depart.Y, lig, col, color, Effacer);				// L' affichage D'une BOX autours d'un point central

	int v = 0;
	lig = col = 6; color = LIGHT_RED;
	UI_Afficher_Box(depart.X, depart.Y, lig, col, color);	Sleep(0);			// L' affichage D'une BOX plus grosse
	lig = col = 8;	color = RED;
	UI_Afficher_Box(depart.X, depart.Y, lig, col, color);	Sleep(v);			// L' affichage D'une BOX plus grosse
	lig = col = 10; color = LIGHT_YELLOW;
	UI_Afficher_Box(depart.X, depart.Y, lig, col, color);	Sleep(v);			// L' affichage D'une BOX plus grosse
	lig = col = 12; color = YELLOW;
	UI_Afficher_Box(depart.X, depart.Y, lig, col, color);	Sleep(v);			// L' affichage D'une BOX plus grosse
	lig = col = 15; color = BRIGHT_WHITE;
	UI_Afficher_Box(depart.X, depart.Y, lig, col, color);	Sleep(v);			// L' affichage D'une BOX plus grosse
	lig = col = 17; color = GREEN;
	UI_Afficher_Box(depart.X, depart.Y, lig, col, color);	Sleep(v);			// L' affichage D'une BOX plus grosse
	lig = col = 19; color = LIGHT_PURPLE;
	UI_Afficher_Box(depart.X, depart.Y, lig, col, color);	Sleep(v);			// L' affichage D'une BOX plus grosse
	lig = col = 21; color = PURPLE;
	UI_Afficher_Box(depart.X, depart.Y, lig, col, color);	Sleep(v);			// L' affichage D'une BOX plus grosse
	lig = col = 23; color = LIGHT_AQUA;
	UI_Afficher_Box(depart.X, depart.Y, lig, col, color);	Sleep(v);			// L' affichage D'une BOX plus grosse
	lig = col = 25; color = LIGHT_BLUE;
	UI_Afficher_Box(depart.X, depart.Y, lig, col, color);	Sleep(v);			// L' affichage D'une BOX plus grosse
	lig = col = 29; color = LIGHT_YELLOW;
	UI_Afficher_Box(depart.X, depart.Y, lig, col, color);	Sleep(v);			// L' affichage D'une BOX plus grosse
	lig = col = 33; color = LIGHT_RED;
	UI_Afficher_Box(depart.X, depart.Y, lig, col, color);	Sleep(0);			// L' affichage D'une BOX plus grosse
	lig = col = 37; color = LIGHT_AQUA;
	UI_Afficher_Box(depart.X, depart.Y, lig, col, color);	Sleep(0);			// L' affichage D'une BOX plus grosse
	lig = col = 41; color = LIGHT_GREEN;
	UI_Afficher_Box(depart.X, depart.Y, lig, col, color);	Sleep(20);			// L' affichage D'une BOX plus grosse
	gotoxy(0, 0); clrscr();
}


// CHANGE LA VITESSE DE DÉPLACEMENT DES BOTS 
void EV_Change_BOT_Speed(int speed)
{
	BOT_Move_Cycle = speed;		// Change la variable global du speed
}



// ***************
// LES MSG EVENTS*
// --------------*


// REWARD POUR AVOIR SORTIE DE LA BOX
void EV_Msg_AF_WasdTuto()
{
	UI_Aff_String(22, 26, "ENJOY", 20, LIGHT_RED);
	UI_Aff_String(52, 26, "FREEDOM", 20, LIGHT_RED);
}

void EV_Msg_DE_WasdTuto()
{
	string se = "freedom";
	UI_Delete_String(22, 26, 5);
	UI_Delete_String(52, 26, se.size());
}
//--------------*--------------*--------------*--------------*

// TUTORIAL: Message après qu'un bot est sortie de la box pendant le tuto
void EV_MsAF_Got_Out()
{
	UI_Aff_String(45, 20, " KNOWLEDGE", 40, LIGHT_RED); Sleep(1000);
	UI_Aff_String(65, 20, " IS POWER ", 40, LIGHT_RED); Sleep(2000);

}
// TUTORIAL: Message après que le joueur est empêché le bot de sortir pendant le tuto
void EV_MsAF_Not_Got_Out()
{
	UI_Aff_String(30, 30, " This did not hurt...", 40, LIGHT_RED); Sleep(1000);
	UI_Delete_String(30, 30, 21);
}

//--------------*--------------*--------------*--------------*

// Affichages des touches de mouvements
//-------------------------------------

void EV_MsgAf_Touche_Mouvement(int CoordX, int CoordY)
{
	string titre = "GET OUT";
	Change_Color(LIGHT_RED); gotoxy(CoordX - titre.size() / 2, CoordY); cout << titre;
	Change_Color(LIGHT_YELLOW);

	CoordY += 27, CoordX--; 
	//gotoxy(CoordX, CoordY);Afficher_Box(CoordX, CoordY, 3, 3, YELLOW);
	gotoxy(CoordX, CoordY); cout << "[W]";
	
	CoordX -= 3; CoordY += 1;
	//gotoxy(CoordX, CoordY);Afficher_Box(CoordX, CoordY, 3, 3, YELLOW);
	gotoxy(CoordX, CoordY); cout << "[A]";
	
	CoordX += 3;
	//gotoxy(CoordX, CoordY);Afficher_Box(CoordX, CoordY, 3, 3, YELLOW);
	gotoxy(CoordX, CoordY); cout << "[S]";
	
	CoordX += 3;
	//gotoxy(CoordX , CoordY );Afficher_Box(CoordX, CoordY, 3, 3, YELLOW);
	gotoxy(CoordX , CoordY); cout << "[D]";
	Change_Color(BRIGHT_WHITE);
}

// Afficher les touches de tirs
// ----------------------------

void EV_MsgAf_Del_Touche_Tir(int CoordX, int CoordY, bool Effacer)
{

	string titre = "CREATE WALL"; 
	string titre2 = "O----\333";
	string titre3 = "\333----O";

	char Sym;		
	//
	//O
	//|
	//|
	//.
	//gotoxy(CoordX, CoordY);Afficher_Box(CoordX, CoordY, 3, 3, YELLOW);
	//if (Effacer)
	//{
	//	UI_Delete_String(CoordX, CoordY, titre.size());
	//	gotoxy(CoordX - 7, CoordY + 3); cout << "                                    ";
	//	FastStart = true;
	//}
	//else
	{
		UI_Aff_String(CoordX - 3, CoordY, titre, 100, LIGHT_RED); Sleep(300);
		UI_Aff_String(CoordX - 8, CoordY + 2, "(Arrows on Keyboard)", 50, LIGHT_YELLOW);
		UI_Aff_String(CoordX + 1, CoordY + 4, "[^] ", 50, LIGHT_YELLOW);
		UI_Aff_String(CoordX - 3, CoordY + 5, "[<] [V] [>]", 50, LIGHT_YELLOW);
		
		// Affiche les mini walls horizontales

		//changeColor(LIGHT_YELLOW); // Change couleur des walls
		//CoordX -= 3; CoordY--;	// replace le curseur
		//CoordX -=  (titre3.size() + 2); 
		//UI_Aff_String(CoordX, CoordY, titre2, 20, LIGHT_YELLOW);
		//CoordX = CoordX + 4 + titre3.size() + titre.size();
		//UI_Aff_String(CoordX, CoordY, titre3, 20, LIGHT_YELLOW);
		//CoordX -= (titre3.size() + titre.size() + 2);

		//for (size_t i = 0; i < 2; i++)
		//{
		//	if (!i)
		//		CoordX -= 2;
		//	else
		//		CoordX += titre.size() + titre2.size() * 2 + 3;

		//	for (size_t i = 0; i < 2; i++)			
		//		UI_Aff_Char(CoordX, ++CoordY, '\263',0, LIGHT_YELLOW);
		//	UI_Aff_Char(CoordX, ++CoordY, '\372', 0, LIGHT_YELLOW);
		//	
		//	CoordY -= 3;
		//}


	}


	//										^			(Arrows/Flèches)			Design #2
	//				STOP THEM.				|										
	//									<--	- -->
	////									|
	//										v	
//											

}


//DONNE L'INSTRUCTION AU JOUEUR D'ARRÊTER UN ENNEMIE
// --------------------------------------------------

void EV_MsgAf_Stop_Bot(int CoordX, int CoordY, bool Effacer)
{

	string titre = "STOP THEM."; //"SHOOT";
	char Sym;

	//gotoxy(CoordX, CoordY);Afficher_Box(CoordX, CoordY, 3, 3, YELLOW);
	if (Effacer)
	{
		UI_Delete_String(CoordX, CoordY, titre.size());
		gotoxy(CoordX - 7, CoordY + 3); cout << "                                    ";
	}
	else
	{
		UI_Eff_Texte_Area_And_nothing_else(CoordX - 11, CoordY - 1, 27, 7);
		
		UI_Aff_String(CoordX - 2, CoordY+3, titre, 100, LIGHT_RED); Sleep(10);
		UI_Aff_Char(CoordX + 2, CoordY + 7, 204, 400, LIGHT_YELLOW);
		UI_Aff_String(CoordX - 10, CoordY + 2, "", 30, LIGHT_YELLOW);
		UI_Aff_String(CoordX - 6, CoordY + 11, "MORE INCOMING", 30, LIGHT_RED);
		UI_Aff_String(CoordX - 3, CoordY + 9, "", 30, LIGHT_RED);

		/*UI_Delete_String(60, 10, MsgSize); Sleep(100);
		UI_Msg_Stop_it(60, 10, Message);*/
	}
}

// TOUS LES PARTIES DE L'ANIMATIONS DES TITRES sont enboîté par des tites lignes --------------------------------
void EV_MsgAF_WillHurt()			
{
	UI_Aff_String(box.limit[RIGHT] / 2 - 23, 10, "THIS			WILL			HURT", 0, LIGHT_RED);
}
void EV_MsgAF_You()
{
	UI_Aff_String(box.limit[RIGHT] / 2 - 25, box.limit[DOWN] / 2, "YOU", 0, LIGHT_RED);
	UI_Aff_String(box.limit[RIGHT] / 2 - 25, box.limit[DOWN] / 2, "YOU", 10, WHITE);
	UI_Aff_String(box.limit[RIGHT] / 2 - 25, box.limit[DOWN] / 2, "YOU", 5, LIGHT_RED);
	UI_Aff_String(box.limit[RIGHT] / 2 - 25, box.limit[DOWN] / 2, "YOU", 10, WHITE);
	UI_Aff_String(box.limit[RIGHT] / 2 - 25, box.limit[DOWN] / 2, "YOU", 5, LIGHT_RED);
}
void EV_MsgAF_Must()			
{
	UI_Aff_String(box.limit[RIGHT] / 2 - 10, box.limit[DOWN] / 2, "must", 10, LIGHT_RED);
	UI_Aff_String(box.limit[RIGHT] / 2 - 10, box.limit[DOWN] / 2, "must", 0, WHITE);
	UI_Aff_String(box.limit[RIGHT] / 2 - 10, box.limit[DOWN] / 2, "must", 10, LIGHT_RED);
	UI_Aff_String(box.limit[RIGHT] / 2 - 10, box.limit[DOWN] / 2, "must", 5, WHITE);
	UI_Aff_String(box.limit[RIGHT] / 2 - 10, box.limit[DOWN] / 2, "must", 0, LIGHT_RED);
}
void EV_MsgAF_STOPIT()
{
	UI_Aff_String(box.limit[RIGHT] / 2 + 15, box.limit[DOWN] / 2, "STOP IT", 5, LIGHT_RED);
	UI_Aff_String(box.limit[RIGHT] / 2 + 15, box.limit[DOWN] / 2, "STOP IT", 5, WHITE);
	UI_Aff_String(box.limit[RIGHT] / 2 + 15, box.limit[DOWN] / 2, "STOP IT", 5, LIGHT_RED);
	UI_Aff_String(box.limit[RIGHT] / 2 + 15, box.limit[DOWN] / 2, "STOP IT", 5, WHITE);
	UI_Aff_String(box.limit[RIGHT] / 2 + 15, box.limit[DOWN] / 2, "STOP IT", 5, LIGHT_RED);
}

// --------------------------------------------------------------------------------------------------------------------------------
// AFFICHE UN MSG, PLUTÔT INSISTANT, À RÉPÉPTION, quand le premier bot meurt 
void UI_Msg_Stop_it(int CoordX, int CoordY, string Msg)
{
	for (size_t i = 0; i < 1; i++)
	{
		UI_Msg_Animation_1(CoordX, CoordY, Msg, 0);		// pour débugger, avant le multithread: jai mis le temps à 0
		CoordY++;
	}
}



//*********************************************
// AUTRES FONCTIONS INTERFACE, MENU, AFFICHAGE*
// -------------------------------------------*-
//**********************************************

//Affiche un keyboard, en highlightant les flèches de clavier
void UI_Aff_Keyboard(int CoordX, int CoordY)
{
	for (size_t Lignes = 0; Lignes < 10; Lignes++)
	{
		switch (Lignes)
		{
		case 1:UI_Aff_String(CoordX, CoordY, ".--------------------------------------------------------------------."); break;
		case 2:UI_Aff_String(CoordX, CoordY, "| [Esc][F1][F2][F3][F4][F5][F6][F7][F8][F9][F0][F10][F11][F12] o o o |"); break;
		case 3:UI_Aff_String(CoordX, CoordY, "|                                                                    |"); break;
		case 4:UI_Aff_String(CoordX, CoordY, "|[`][1][2][3][4][5][6][7][8][9][0][-][=][_<_] [I][H][U]  [N][/][*][-]|"); break;
		case 5:UI_Aff_String(CoordX, CoordY, "|[| -][Q][W][E][R][T][Y][U][I][O][P][{][}]| | [D][E][D]  [7][8][9]|+||"); break;
		case 6:UI_Aff_String(CoordX, CoordY, "|[CAP][A][S][D][F][G][H][J][K][L][;]['][#]|_|            [4][5][6]|_||"); break;
		case 7:UI_Aff_String(CoordX, CoordY, "| [^][\][Z][X][C][V][B][N][M][, ][.][/ ][ ^ ]     ");Change_Color(LIGHT_YELLOW); cout << "[^]";	Change_Color(WHITE);	 cout << "     [1][2][3]| ||"; break;
		case 8:UI_Aff_String(CoordX, CoordY, "|[c][a][________________________][a]      [c] ");Change_Color(LIGHT_YELLOW); cout << "[<][V][>]";Change_Color(WHITE); cout << "	 [0][.]|_|| "; break;
		case 9:UI_Aff_String(CoordX, CoordY, "`--------------------------------------------------------------------'"); break;
		}

		CoordY++;
	}

	//.--------------------------------------------------------------------.
	//| [Esc][F1][F2][F3][F4][F5][F6][F7][F8][F9][F0][F10][F11][F12] o o o |
	//|                                                                    |
	//|[`][1][2][3][4][5][6][7][8][9][0][-][=][_<_] [I][H][U]  [N][/][*][-]|
	//|[| -][Q][W][E][R][T][Y][U][I][O][P][{][}]| | [D][E][D]  [7][8][9]|+||
	//|[CAP][A][S][D][F][G][H][J][K][L][;]['][#]|_|            [4][5][6]|_||        
	//| [^][\][Z][X][C][V][B][N][M][, ][.][/ ][ ^ ]    [^]     [1][2][3]| ||
	//|[c][a][________________________][a]      [c] [<][V][>]	  [0][.]|_||
	//`--------------------------------------------------------------------' 
}

// AFFICHE UN MSG : D'un coup, et ensuite, Lettre par lettre 
//--------------------------------------------------------------------

void UI_Msg_Animation_1(int CoordX, int CoordY, string titre, Time time, Colors color)
{

	gotoxy(CoordX, CoordY); Change_Color(BRIGHT_WHITE); cout << titre; Sleep(time * 2 + 5);
	gotoxy(CoordX, CoordY);	Change_Color(color);

	for (size_t i = 0; i < titre.size(); i++)		// Réaffiche le titre lettre dans une couleur différente, lettres par lettres
	{
		cout << titre[i]; Sleep(time);
	}

	Change_Color(WHITE);
}



// AFFICHE UNE STRING SELON UN RYTHME ET UNE COULEUR
///*************************************************

void UI_Aff_String(int CoordX, int CoordY, string txt, Time time, Colors color)
{
	int length = txt.size();

	gotoxy(CoordX, CoordY);		// Positionnement du curseur
	Change_Color(color);			// Changement de couleur

	for (size_t i = 0; i < length; i++)
	{
		cout << txt[i]; Sleep(time);
	}

	Change_Color(WHITE);
}

// AFFICHE UN char! SELON UN RYTHME ET UNE COULEUR
///*************************************************
void UI_Aff_Char(int CoordX, int CoordY, char Sym, Time time, Colors color)
{
	gotoxy(CoordX, CoordY);		// Positionnement du curseur
	Change_Color(color);			// Changement de couleur
	cout << Sym; Sleep(time);
	Change_Color(WHITE);
}

// EFFACEMENT DE TOUS LES CHARACTÈRES PRÉSENT DANS UN RECTANGLE DE LA CONSOLE
void UI_DE_Texte_Area(int CoordX, int  CoordY, int col, int lig)
{
	int c, l;			// Nombre de lignes et colonnes relatif

	for (l = 0; l < lig; l++)
	{
		for (c = 0; c < col; c++)
		{
			gotoxy(CoordX + c, CoordY); cout << ' ';
		}

		CoordY++;
	}


}

// EFFACEMENT DE TOUS LES CHARACTÈRES PRÉSENT DANS UN RECTANGLE DE LA CONSOLE
void UI_Eff_Texte_Area_And_nothing_else(int CoordX, int  CoordY, int col, int lig)
{
	int c, l;			// Nombre de lignes et colonnes relatif
	int XY;
	int dont = 0;

	for (l = 0; l < lig; l++)
	{
		for (c = 0; c < col; c++)
		{
			dont = 0;
			XY = Compress_XY(CoordX + c, CoordY);

			// Vérifie tout mes tableaux de merde lol
			if(Search_Coordinnates(LinkXY, ML, XY) == -1)							
				if(Search_Coordinnates(VitalLinkXY, ML, XY) == -1)
					if(Search_Coordinnates(Wall, C, XY) == -1)
						if (Search_Coordinnates(BOTXY, MaxNumBOTS, XY) == -1)
						{
							gotoxy(CoordX + c, CoordY); cout << ' ';
						}
		}

		CoordY++;
	}


}


// L' affichage D'une BOX de XparX autours d'un point central
// --------------------------

void UI_Afficher_Box(int CoordX, int CoordY, int NBLIG, int NBCOL,  Colors Couleur, bool Effacer, Time time )		// Valeur^par défaut, ne doit être placé que dans la déclaration
{
	// Position logique en haut à gauche pour faciliter l'affichage
	Coord cor = { CoordX - NBLIG / 2, CoordY - NBCOL / 2 };		// Le centre!!!

	// Pour représenter une position logique du curseur dans une case du jeu
	struct Affichage_Case
	{
		int l;		// ligne d'un charactère d'une case	[ 0 .. NB_LIG_CASE ]
		int c;		// colonne d'un charactère d'une case[ 0 .. NB_COL_CASE ]
		int Sym;	// pour afficher le symbole dans une case
	};

	Affichage_Case Ca;

	// La position logique en colonne et en ligne relatif à chaque cases			
	Ca.c = 0;
	Ca.l = 0;

	Change_Color(Couleur);		// Le couleur du curseur 

	while (Ca.l < NBLIG)					//	Permet d'afficher le bon symbole de la BOX jeu selon la position du curseur de la console windows dans la case 
	{											//	Les dimensions de la case sont régit par le NB_LIG_CASE ET NB_COL_CASE
		if (Ca.l < NBLIG)
		{
			if (Ca.l == 0)
			{
				if (Ca.c == 0)							// Left TOp corner
					Ca.Sym = 218;

				if (Ca.c > 0 && Ca.c < NBCOL - 1)		// Symbole top et Bottom
					Ca.Sym = 196;

				if (Ca.c == NBCOL - 1)					// Right TOp corner
					Ca.Sym = 191;
			}
			else				// On affiche un symbole différent selon la ligne 
				if (Ca.l > 0 && Ca.l < NBLIG - 1)
				{
					if (Ca.c == 0)						// Symbole Left et Right
						Ca.Sym = 179;

					if (Ca.c > 0 && Ca.c < NBCOL - 1)
						Ca.Sym = ' ';

					if (Ca.c == NBCOL - 1)				// Symbole Left et Right
						Ca.Sym = 179;
				}
				else if (Ca.l == NBLIG - 1)
				{
					if (Ca.c == 0)						// BOt Left corner
						Ca.Sym = 192;

					if (Ca.c > 0 && Ca.c < NBCOL - 1)	// Symbole top et Bottom
						Ca.Sym = 196;

					if (Ca.c == NBCOL - 1)				// BOt Right corner
						Ca.Sym = 217;
				}
			if (Ca.Sym != ' ')
			{
				gotoxy(Ca.c + cor.X, cor.Y + Ca.l);
				cout << (char)Ca.Sym; Sleep(time);
			}
		}

		// Si le nombre de colonnes dans la case est dépassé. On doit changer de ligne 
		if (Ca.c + cor.X >= cor.X + NBCOL - 1)
		{
			++Ca.l;						// On change de ligne et on revient à la première colonne 
			Ca.c = 0;
		}
		else
			Ca.c++;	// On avance d'une colonne tant qu'on ne dépasse pas la limite de colonne pour une case
	}

	cvmSetColor(BLANC);	// On revient à la couleure de base

}

// Affiche un char et l'efface ensuite
void UI_Aff_ET_Del_Char(int CoordX, int CoordY, char Sym, Time time, Colors color)
{
	Change_Color(color);									// Couleur désiré
	gotoxy(CoordX, CoordY); cout << Sym; Sleep(time);	// Affiche le char, selon une durée de temps
	gotoxy(CoordX, CoordY); cout << " ";				// Efface le char après la durée de temps
}

// Efface un nombre de charactères consécutif 
//********************************************
void UI_Delete_String(int CoordX, int CoordY, int Length) 
{
	gotoxy(CoordX, CoordY); 

	for (size_t i = 0; i < Length; i++)
			cout << ' ';
}

void UI_Display_StatsName()
{
	// On affiche le temps pour les tests
	/*gotoxy(0, 0); cout << "Current time: ";
	gotoxy(box.limit[LEFT], box.limit[DOWN] + 3); cout << "Current BOT Cycle: " ;
	gotoxy(box.limit[RIGHT] - 20, box.limit[DOWN] + 3); cout << "Next BOT Move : " ;

	gotoxy((box.limit[RIGHT] / 2) - 15, 0); cout << "Current Spawn Cycle: " ;
	gotoxy(box.limit[RIGHT] - 22, 0); cout << "Next Spawn : ";*/

	//gotoxy((box.limit[RIGHT] / 2), box.limit[DOWN] + 3); cout << "TOT Spw Cyc: ";
}

void UI_Update_TimerAndStats() 
{
	//// On affiche le temps pour les tests
	//gotoxy(0 + StatsT[0].size(), 0); cout << Current_time;

	///*if (Move_BOTS_this_Cycle)	changeColor(GREEN);
	//else	changeColor(LIGHT_RED);*/
	//gotoxy((box.limit[LEFT]  + StatsT[1].size()) , box.limit[DOWN] + 3); cout << Current_BOT_MOVE_Cycle;//changeColor(WHITE);
	//gotoxy(box.limit[RIGHT] - 20 + StatsT[2].size(), box.limit[DOWN] + 3); cout <<  Next_BOT_MOVE_Cycle;

	///*if (Spawn_this_Cycle)changeColor(GREEN);
	//else	changeColor(LIGHT_RED);*/
	//gotoxy((box.limit[RIGHT] / 2) - 15 + StatsT[3].size(), 0); cout << Current_Spawn_Cycle;//changeColor(WHITE);
	//gotoxy(box.limit[RIGHT] - 22 + StatsT[4].size(), 0); cout << Next_Spawn_Cycle;
	//gotoxy((box.limit[RIGHT] / 2) + StatsT[5].size(), box.limit[DOWN] + 3); cout << Spwn_cycleTOT;
}

void UI_Damage_Animation();
void UI_Display_Health();


void Swag_Animation(Colors col1, Colors col2, Colors col3)	// So pretty...
{
	// 7- 6 -8 

	int x = 0, y = 1;	
	gotoxy(x, y);	// Start en haut à gauche
	int xMax = 84;	// Longueur de console
	int yMax = 53;	// hauteur de console
	char Sym = 178;		// Symbole


	for (int i = 0; y < yMax; ++i)
	{
		if (x == xMax)
		{
			x = 0; y++;
		}
		else
			x++;

		if (y >= box.limit[UP] && y <= box.limit[DOWN])
			if (x >= box.limit[LEFT] && x <= box.limit[RIGHT])
			{
				x = box.limit[RIGHT];	continue;
			}
		
		gotoxy(x, y); 
		
			if (i % 3 == 0)	
				Change_Color(col1);	
			else 
				Change_Color(col2);

			if (i % 7 == 0)	Change_Color(col3);
			if (i % 10 == 0) Change_Color(0);						
		 
			if(y != yMax )
				cout << Sym;
	
	}

}

void Swag_Animation2(Colors col0 , Colors col1, Colors col2, Colors col3, Colors col4, Colors col5)	// So pretty...
{
	int x = 0, y = 0;	gotoxy(x, y);	// Start en haut à gauche
	int xMax = 84;	// Longueur de console
	int yMax = 52;	// Largeur de console
	char Sym;		// Symbole
	Sym = 178;

	for (int i = 0; y < yMax; ++i)
	{
		if (x == xMax)
		{
			x = 0; y++;
		}
		else
			x++;

		if (y >= box.limit[UP] && y <= box.limit[DOWN])		
			if (x >= box.limit[LEFT] && x <= box.limit[RIGHT])		// Skip le dedans de la box
			{
				x = box.limit[RIGHT];	continue;
			}

		gotoxy(x, y); Change_Color(col0);	
		if (i % 3 == 0)	Change_Color(col1);
		if (i % 5 == 0) Change_Color(col2);
		if (i % 7 == 0)	Change_Color(col3);
		if (i % 8 == 0) Change_Color(col4);
		if (i % 11 == 0) Change_Color(col5);


		cout << Sym;
	}
}

void UnSwagidy_Animation()	// So Unpretty... :(
{
	int x = 0, y = 0;	gotoxy(x, y);	// Start en haut à gauche
	int xMax = 84;	// Longueur de console
	int yMax = 53;	// Largeur de console
	char Sym;		// Symbole
	Sym = ' ';

	for (int i = 0; y < yMax; ++i)
	{
		if (x == xMax)
		{
			x = 0; y++;
		}
		else
			x++;

		if (y >= box.limit[UP] && y <= box.limit[DOWN])
			if (x >= box.limit[LEFT] && x <= box.limit[RIGHT])		// Skip le dedans de la box
			{
				x = box.limit[RIGHT];	continue;
			}
		gotoxy(x, y);
		cout << Sym; // Effacement du contours du terrain de jeu
	}
}

////////////////////////////////*****************************************
////////////////////////////////*****************************************
////////////////////////////////*****************************************
////////////////////////////////*****************************************
////////////////////////////////*****************************************
////////////////////////////////*****************************************
////////////////////////////////*****************************************
////////////////////////////////*****************************************
////////////////////////////////*****************************************
//TEMPORARY CRAP STUFF!!!!!
////////////////////////////////*****************************************////////////////////////////////*****************************************
////////////////////////////////*****************************************
////////////////////////////////*****************************************
////////////////////////////////*****************************************
////////////////////////////////*****************************************
////////////////////////////////*****************************************
////////////////////////////////*****************************************
////////////////////////////////*****************************************
////////////////////////////////*****************************************
////////////////////////////////*****************************************

// CHERCHE UN LINK DE LIBRE				sera uselessssss

int Search_For_Available_Link(int in) 
{
	do		//Trouver les première variable setté à 0.00 dans les Tableaux de Link
	{
		if (LinkXY[in] == 0)
			break;
		else
			in++;
	} while (in < ML);

	return in;
}

int Search_For_Available_VitalLink(int in)
{
	do		//Trouver les première variable setté à 0.00 dans les Tableaux de Vital
	{
		if (VitalLinkXY[in] == 0)
			break;
		else
			in++;
	} while (in < ML);

	return in;
}


// MATH STUFF
//***********


// Retourne la différence d'un minimum à un maximum
int Intervalle(int min, int max)
{
	int intervalle = max - min;
	return intervalle;
}






//Ici j'pourrais design du code qui arrête de chercher dans le tableau quand ya juste une shitload de variables a 0; pour l'instant
//Je crois pas que t'es équiper de suffisament de connaissance pour justifier de faire ça: Qu'est ce qui prend le plus de CPU?

//Empêche de chercher plus loin dans un tableau si t'atteint la troller de Zéros
void Stop_Search(int Wall[])
{
	int i = 0;
	int IfFiftyZeros = 0;

	while (i < 300)
	{
		if (Wall[i] == 0)
			IfFiftyZeros++;
		else
			IfFiftyZeros = 0;

		if (IfFiftyZeros == 500)
			break;
		i++;
	}
}
//genre ça