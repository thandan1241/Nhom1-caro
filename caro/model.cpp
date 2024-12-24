#include "model.h"

//func
void LoadBoard(int matrix[BoardSize][BoardSize]) {
	for (int i=0; i < BoardSize; i++) {
		for (int h=0; h < BoardSize; h++) {
			GotoXY(StartPoint.X + h * 4, StartPoint.Y + i * 2);
			if (matrix[i][h] == 1) { 
				TextColor(252);
				cout << "x";
				TextColor(240);
			}
			if (matrix[i][h] == -1) {
				TextColor(241);
				cout << "o";
				TextColor(240);
			}
		}
	}
}

void LoadSavedGame(char* name, int matrix[BoardSize][BoardSize], bool &turn) {
	FILE* input = NULL;
	char path[27] = { 0 };
	strncpy_s(path, name, strlen(name)-1);
	strcat_s(path, 27, ".txt");
	fopen_s(&input, path, "r");
	if (input != NULL) {
		int a = 0;
		fscanf_s(input, "%d", &a);
		if (a == 1) turn = true;
		else turn = false;
		for (int i = 0; i < BoardSize; i++) {
			for (int h = 0; h < BoardSize; h++) {
				fscanf_s(input, "%d", &matrix[i][h]);
			}
		}
		fclose(input);
		return;
	}
}

filename* LoadFileList() {
	FILE* buf;
	fopen_s(&buf, "GameList.txt", "r");
	if (buf) {
		char holder[20] = { 0 };
		int count= CountFile();
		if (count == 0) return NULL;
		filename* list = (filename*)malloc(sizeof(filename) * count);
		if (list == NULL) {
			cout << "failed";
			return NULL;
		}
		for (int i = 0; i < count; i++) {
			fgets(holder, 20, buf);
			strncpy_s(list[i].name, 20, holder,20);
		}
		fclose(buf);
		return list;
	}
	return NULL;
}

char* LoadGameMenu(FILE* buf, filename*& filelist, int matrix[BoardSize][BoardSize], bool& turn) {
	system("cls");
	filelist = LoadFileList();
	if (filelist == NULL) {
		GotoXY(50, 6);
		cout << TopLeft;
		for (int i = 0; i < 20; i++) {
			cout << Horizontal;
		}
		cout << TopRight;
		for (int i = 1; i < 2; i++) {
			GotoXY(50, 6 + i);
			cout << Vertical;
			for (int h = 0; h < 20; h++) { cout << " "; }
			cout << Vertical;
		}
		GotoXY(50, 8);
		cout << BotLeft;
		for (int i = 0; i < 20; i++) {
			cout << Horizontal;
		}
		cout << BotRight;
		GotoXY(51, 7);
		TextColor(252);
		cout << "No game to be loaded";
		TextColor(240);
		Sleep(2000);
		return NULL;
	}
	fopen_s(&buf, "GameList.txt", "r");
	if (buf) {
		GotoXY(30, 4);
		cout << TopLeft;
		for (int i = 0; i < 59; i++) {
			cout << Horizontal;
		}
		cout << TopRight;
		for (int i = 1; i < 25; i++) {
			GotoXY(30, 4 + i);
			cout << Vertical;
			for (int h = 0; h < 59; h++) { cout << " "; }
			cout << Vertical;
		}
		GotoXY(30, 29);
		cout << BotLeft;
		for (int i = 0; i < 59; i++) {
			cout << Horizontal;
		}
		cout << BotRight;
		GotoXY(53, 6);
		TextColor(252);
		cout << "Saved Game List";
		TextColor(245);
		int count = CountFile();
		int input;
		for (int i = 0; i < count; i++) {
			GotoXY(45, 8 + 2 * i);
			cout << i + 1 << ". " << filelist[i].name<<"\n";
		}
		GotoXY(40, 8 + 2 * count);
		TextColor(240);
		cout << "Choose game to load (Input number) ";
		cin >> input;
		cin.ignore();
		LoadSavedGame(filelist[input - 1].name, matrix, turn);
		fclose(buf);
		return filelist[input - 1].name;
	}
	return NULL;
}

void SaveGame(FILE* output, int matrix[BoardSize][BoardSize], bool turn) {
	if (output != NULL) {
		fprintf_s(output, "%d", turn==true?1:0);
		fprintf_s(output, "%c", 13);
		for (int i = 0; i < BoardSize; i++) {
			for (int h = 0; h < BoardSize; h++) {
				fprintf_s(output, "%d", matrix[i][h]);
				fprintf_s(output, "%c", 32);
			}
			fprintf_s(output, "%c", 13);
		}
	}
}

int CountFile() {
	int count = 0;
	FILE* file;
	char buf[30] = { 0 };
	fopen_s(&file, "GameList.txt", "r");
	if (file) {
		while (fgets(buf, 30, file) != NULL) {
			count++;
		}
		fclose(file);
	}
	return count;
}

void SaveNewGame(FILE* buf, filename*& filelist, int matrix[BoardSize][BoardSize], bool turn) {
	int count = CountFile()+1;
	filelist = (filename*)realloc(filelist, sizeof(filename) * (count));
	if (filelist != NULL) {
		char nam[27] = { 0 };
		cout << "Name (No more than 15): ";
		cin.getline(nam, 20);
		strncpy_s(filelist[count - 1].name, nam, 21);
		fopen_s(&buf, "GameList.txt", "a");
		if (buf) {
			fprintf_s(buf, "%s", filelist[count - 1].name);
			fprintf_s(buf, "%c", 10);
			fclose(buf);
		}
		strcat_s(nam, 27, ".txt");
		fopen_s(&buf, nam, "w+");
		if (buf) {
			SaveGame(buf,matrix,turn);
			fclose(buf);
		}
	}
}

void SaveExistedGame(char* name, int matrix[BoardSize][BoardSize], bool turn) {
	FILE* file=NULL;
	char path[27] = { 0 };
	strncpy_s(path, name, strlen(name) - 1);
	strcat_s(path, 27, ".txt");
	fopen_s(&file, path, "w+");
	if (file) {
		SaveGame(file, matrix, turn);
		fclose(file);
	}
}