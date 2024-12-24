#pragma once
#include <iostream>
#include <Windows.h>
#include "View.h"
using namespace std;

struct filename {
	char name[30];
};
//Func
void LoadBoard(int matrix[BoardSize][BoardSize]);
void LoadSavedGame(char* name, int matrix[BoardSize][BoardSize], bool &turn);
filename* LoadFileList();
char* LoadGameMenu(FILE* buf, filename*& filelist, int matrix[BoardSize][BoardSize], bool& turn);
void SaveGame(FILE* output, int matrix[BoardSize][BoardSize], bool turn);
int CountFile();
void SaveNewGame(FILE* buf, filename*& filelist, int matrix[BoardSize][BoardSize], bool turn);
void SaveExistedGame(char* name, int matrix[BoardSize][BoardSize], bool turn);