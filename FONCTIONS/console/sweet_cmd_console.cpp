
#include "sweet_cmd_console.h"
#include "../UI/map.h"


// Globales stuff

HWND GAME_WND = GetConsoleWindow();		// La fenêtre du jeu
RECT rect; // Dimension de la fenêtre
int gConWidth;
int gConHeight;
double charRatio;	// Le ratio pixel par character? Bref, utile pour redimensionner à partir d'un nombre de case!

// Local stuff

static HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
static CONSOLE_SCREEN_BUFFER_INFO csbi;				// Pour avoir accès au screen buffer de la console

void Upd_Console_Size()
{
	GetConsoleScreenBufferInfo(h, &csbi);
	gConWidth = csbi.srWindow.Right;					// Nouvelle Largeur
	gConHeight= csbi.srWindow.Bottom;					// Nouvelle Longueur
}

void Setup_Console_Window()
{
	// CHANGE LE CURSEUR
	// ********************************

	HANDLE hout; //handle to the console			// What is a handle? who knows!?
	CONSOLE_CURSOR_INFO cursor;						//cursor struct
	hout = GetStdHandle(STD_OUTPUT_HANDLE);			//set our handle for output			
	cursor.bVisible = false;						// rend le curseur unvisible
	cursor.dwSize = 1;								// et tr`s petits
	SetConsoleCursorInfo(hout, &cursor);			//pass the cursor info structure and our handle	to this function and we're done :)

	// LE TITRE DU JEU
	// ***************
	LPCTSTR GameName = "Wall In ";
	SetConsoleTitle(GameName);
}

void Set_Dflt_WND()
{
	SetWindowPos(GAME_WND, HWND_TOP, 0, 0, 1401, 1073, SWP_NOMOVE | SWP_NOZORDER);	// Bonne dimension par défaut de la fenêtre du jeu
	Upd_Console_Size();
	Center_WND();
}


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

void Resize_To_Game_Map()	// redimensionne la fenêtre de console. Faut faire ça AVANT DE REDIMENSIONNER LA MAP, SINON TOUT FOIRE
{
	charRatio = rect.right / (double)gConWidth;	
	  
	double right = charRatio * map.Get_Length();		// Longueur en pixel selon la longueur de la map + 1 espace de chaque côté
	double bot = charRatio * map.Get_Height();		// hauteur de de console selon la hauteur
	//double right = charRatio * (map.Get_Box_Limit(RIGHT) + (map.Get_Box_Limit(LEFT) * 2));		// Longueur en pixel selon la longueur de la map + 1 espace de chaque côté
	//double bot = charRatio * (map.Get_Height() + (map.Get_Box_Limit(UP) * 2));		// hauteur de de console selon la hauteur

	SetWindowPos(GAME_WND, HWND_TOP, 0, 0, (int)right, (int)bot, SWP_NOMOVE | SWP_NOZORDER);	// Bonne dimension par défaut de la fenêtre du jeu
	SetWindowPos(GAME_WND, HWND_TOP, 0, 0, (int)right, (int)bot, SWP_NOREDRAW | SWP_NOZORDER);	// Bonne dimension par défaut de la fenêtre du jeu
	Upd_Console_Size();
	Center_WND();
}

void Shake_That_Window()
{



}
void Change_Typography()
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


