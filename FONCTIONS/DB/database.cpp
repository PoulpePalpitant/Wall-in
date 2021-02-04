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
		ConsoleRender::Add_String("Game saved", { gConWidth - 13 ,gConHeight });
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


		// DEBUG 
		// *****
		// ConsoleRender::Add_String("Is Level 2 Unlocked?", { 30,1 }); ConsoleRender::Add_String(line, { 52,1 });
		// ConsoleRender::Add_String("Is Level 3 Unlocked?", { 30,2 }); ConsoleRender::Add_String(std::to_string(gUnlockedLevels[2]), { 52,2 });
		// ConsoleRender::Add_String("Which puzzle on lvl 1", { 30,3 }); ConsoleRender::Add_String(std::to_string(gCurrentPuzzle[0]), { 52,3 });
		// ConsoleRender::Add_String("Which puzzle on lvl 2", { 30,4 }); ConsoleRender::Add_String(std::to_string(gCurrentPuzzle[1]), { 52,4 });
		// ConsoleRender::Add_String("Which puzzle on lvl 3", { 30,5 }); ConsoleRender::Add_String(std::to_string(gCurrentPuzzle[2]), { 52,5 });
		// ConsoleRender::Add_String("Was game completed?", { 30,6 }); ConsoleRender::Add_String(std::to_string(gameCompleted), { 52,6 });
		// ConsoleRender::Add_String("Game Loaded", { 0,5 });
		
		
		
		saveFile.close();
	}
}
