#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <sstream>
#include <shlobj.h>


#include "database.h"
#include "../lvls/lvl_script.h"
#include "../UI/console_output/render_list.h"
#include "../console/sweet_cmd_console.h"

// How do i save to this path, on all pcs? 
// "C:/Users/Moi/AppData/Local/Wall IN/save.dat"	

// https://stackoverflow.com/questions/5920853/how-to-open-a-folder-in-appdata-with-c


using namespace std;

void Save()
{
	ofstream saveFile;
	saveFile.open("save.txt", ios::out | ios::trunc);	// Va toujours save dans le même fichier. keep it simple
	if (saveFile.is_open())
	{
		// write in it
		saveFile << gUnlockedLevels[1] << endl; // Le level [0] sera tjrs unlocked
		saveFile << gUnlockedLevels[2] << endl; 
		saveFile << gCurrentPuzzle[0] << endl;
		saveFile << gCurrentPuzzle[1] << endl;
		saveFile << gCurrentPuzzle[2] << endl;
		saveFile << gameCompleted << endl;
		saveFile.close();
		ConsoleRender::Add_String("Progress saved", { gConWidth - 17 ,gConHeight });
	}
}

void Load() {
	
	string line;
	
	ifstream saveFile("save.txt");

	if (saveFile.is_open())
	{
		// da fuck am I doing
		getline(saveFile, line);
		gUnlockedLevels[1] = stoi(line);

		getline(saveFile, line);
		gUnlockedLevels[2] = stoi(line);

		getline(saveFile, line);
		gCurrentPuzzle[0] = stoi(line); 

		getline(saveFile, line);
		gCurrentPuzzle[1] = stoi(line); 

		getline(saveFile, line);
		gCurrentPuzzle[2] = stoi(line); 

		getline(saveFile, line);
		gameCompleted = stoi(line);

		saveFile.close();
	}
}
