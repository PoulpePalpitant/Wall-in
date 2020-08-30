#include <string.h>
#include "sweet_cmd_console.h"
#include "../UI/map.h"


// Globales stuff

HWND GAME_WND = GetConsoleWindow();		// La fenêtre du jeu
RECT rect; // Dimension de la fenêtre
int gConWidth;
int gConHeight;
int gTotalRes;

double charRatio;	// Le ratio pixel par character? Bref, utile pour redimensionner à partir d'un nombre de case!

// Local stuff

static HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
static HANDLE outputHANDLE;					// pour le full screen?
static CONSOLE_SCREEN_BUFFER_INFO csbi;				// Pour avoir accès au screen buffer de la console

void Upd_Console_Size()
{
	GetConsoleScreenBufferInfo(h, &csbi);
	gConWidth = csbi.srWindow.Right;					// Nouvelle Largeur
	gConHeight= csbi.srWindow.Bottom;					// Nouvelle HauteurS
	gTotalRes = gConHeight * gConWidth;					// Nombre de charactères dans la console
}

void Set_Console_Name()
{
	// LE TITRE DU JEU
	// ***************
	LPCTSTR GameName = "Wall In ";
	SetConsoleTitle(GameName);
}

void Set_Dflt_WND()
{
	
	// Bon, ce que j'ai trouvé: Je met la font par défaut que j'apprécie sur mon écran, je met ensuite la console en fullscreen pour calculer c'est quoi la largeur et la longueur max
	// Par après je reset la console et je fais la même chose. Sauf que cette fois-ci, la dimension de la font est ralative au valeur max trouvé!!

	//À défaut de savoir comment retouvé la dimension d'un écran(pas juste la résolution), this fucking garbage works 
	Change_Font(true, 16); // dflt 16 pour référence
	//SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);	// set la console ben fat, mais somehow pas en fullscreen !
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);	// maximize la console!!!
	Upd_Console_Size();
	//SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_WINDOWED_MODE, 0);	// set la console ben fat, mais somehow pas en fullscreen !
	ShowWindow(GetConsoleWindow(), SW_SHOWDEFAULT);	// ...
	Change_Font(false); // the one you want
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);	// maximize la console!!!
	Upd_Console_Size();

	COORD saveme = { (short)gConWidth ,(short)gConHeight };	// i have been saved
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), saveme);
	Upd_Console_Size();



	// avec un unique handle
//	Change_Font(true, 16); // dflt 16 pour référence
////SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);	// set la console ben fat, mais somehow pas en fullscreen !
//	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);	// maximize la console!!!
//	Upd_Console_Size();
//	SetConsoleDisplayMode(h, CONSOLE_WINDOWED_MODE, 0);	// set la console ben fat, mais somehow pas en fullscreen !
//	//ShowWindow(GetConsoleWindow(), SW_SHOWDEFAULT);	// ...
//	Change_Font(true, 10); // the one you want
//	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);	// maximize la console!!!
//
//	COORD saveme = { gConWidth ,gConHeight };
//	SetConsoleScreenBufferSize(h, saveme);


	//Change_Font(false); // adaptative font
	Hide_Cursor(); 
}

static int Adapt_Font_To_Screen()	// permet de changer la font du jeu selon le gear du joueur
{
	// 236 de longueur, mon écran
	// 62 de largeur, mon écran

	if (gConHeight <= 46)
		return 10;
	else
		if (gConHeight > 46 && gConHeight <= 50)	// écran d'étienne, un écran de portable de gaming
			return 12;
		else
			if (gConHeight > 50 && gConHeight <= 60)
				return 14;
			else
				if (gConWidth < 236)
					return 14;	// square screen!
				else
					return 16;	// font size par défaut
}

void Change_Font(bool deflt, int size ) {
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	
	if (deflt)
		cfi.dwFontSize.Y = size;
	else
		cfi.dwFontSize.Y = Adapt_Font_To_Screen();                  // Height

	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void Hide_Cursor()			// rend le curseur invisible
{
	// CHANGE LE CURSEUR
	// ********************************

	HANDLE hout; //handle to the console			// What is a handle? who knows!?
	CONSOLE_CURSOR_INFO cursor;						//cursor struct
	hout = GetStdHandle(STD_OUTPUT_HANDLE);			//set our handle for output			
	cursor.bVisible = false;						// rend le curseur unvisible
	cursor.dwSize = 1;								// et tr`s petits
	SetConsoleCursorInfo(hout, &cursor);			//pass the cursor info structure and our handle	to this function and we're done :)
}

void Change_Typography()	// oldway
{
	_COORD con;	// Dimension de la console

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


}


void Shake_That_Window()
{



}

// OLDYS
// *****

// utilisé comme suis
	// old way d'afficher le jeu, pas fullscreen, en plein milieu de l'écran
	//SetWindowPos(GAME_WND, HWND_TOP, 0, 0, 1401, 1073, SWP_NOMOVE | SWP_NOZORDER);	// Bonne dimension par défaut de la fenêtre du jeu		/DÉSUET
	//Upd_Console_Size();
	//Center_WND(); // maintenant DÉSUET
void Change_Window_Position()	
{

	/*							    X	  Y    CX  cy   UINT			UINT							*/
	SetWindowPos(GAME_WND, HWND_TOP, 100, 100, 0, 0, SWP_NOSIZE | SWP_NOZORDER);		// UTILISE CETTE MAGNIFIQUE FONCTION
	// HWND_TOP : criss la fenêtre on top
	// HWND_TOPMOST	: Places the window above all non-topmost windows. The window maintains its topmost position even when it is deactivated.
	// X Type: int: The new position of the left side of the window, in client coordinates.
	// Y Type : int :The new position of the top of the window, in client coordinates.
	// cx Type : int : The new width of the window, in pixels.
	// cy Type : int : The new height of the window, in pixels. 
	// uFlags Type : UINT The window sizing and positioning flags. This parameter can be a combination of the following values.
}

// REPOSITIONNE LA WINDOW AU CENTRE
void Center_WND()
{
	int wndWidth, wndHeight;
	int scrWidth, scrHeight;
	int centerX, centerY;

	GetWindowRect(GAME_WND, &rect);	// get taht rectan	

	 /* Get Screen width and height */
	scrWidth = GetSystemMetrics(SM_CXSCREEN);
	scrHeight = GetSystemMetrics(SM_CYSCREEN);

	/* Calculate Window width and height */
	wndWidth = rect.right - rect.left;
	wndHeight = rect.bottom - rect.top;

	// Trouve la position du milieu

	centerX = (scrWidth - wndWidth) / 2;		// La position LEFT
	centerY = (scrHeight - wndHeight) / 2;		// La position TOP

	/* Reposition Window to the center of my screen */
	SetWindowPos(GAME_WND, HWND_TOP, centerX, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}
