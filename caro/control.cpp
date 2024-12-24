#include "control.h"

//Actions on Checkboard
void MoveUp(COORD &x) {
	x.Y -= 2;
	GotoXY(x.X, x.Y);
}

void MoveDown(COORD& x) {
	x.Y += 2;
	GotoXY(x.X, x.Y);
}

void MoveLeft(COORD& x) {
	x.X -= 4;
	GotoXY(x.X, x.Y);
}

void MoveRight(COORD& x) {
	x.X += 4;
	GotoXY(x.X, x.Y);
}

void CheckBoard(const COORD& position, int matrix[BoardSize][BoardSize], bool turn) {
	matrix[(position.Y == StartPoint.Y) ? 0 : ((position.Y - StartPoint.Y)/2)][(position.X - StartPoint.X) / 4] = (turn == true) ? 1 : -1;
	if (turn == true) {
		TextColor(252);
		cout << "x";
		TextColor(240);
	}
	else {
		TextColor(241);
		cout << "o"; 
		TextColor(240);
	}
}

//Win Conditions
int dia1(COORD current, int matrix[BoardSize][BoardSize], bool turn) {
	int count = 0;
	int Col = (current.X - StartPoint.X) / 4;
	int Row = (current.Y == StartPoint.Y) ? 0 : ((current.Y - StartPoint.Y) / 2);
	while ((Row >= 0) && (Col <= BoardSize - 1) && (matrix[Row][Col] == ((turn == true) ? 1 : -1))) {
		count++;
		Row--;
		Col++;
	}
	Col = (current.X - StartPoint.X) / 4;
	Row = (current.Y == StartPoint.Y) ? 0 : ((current.Y - StartPoint.Y) / 2);
	while ((Col >= 0) && (Row <= BoardSize - 1) && (matrix[Row][Col] == ((turn == true) ? 1 : -1))) {
		count++;
		Row++;
		Col--;
	}
	count -= 1;
	if (count >= 5) {
		if (turn == true) return 1;
		else return -1;
	}
	else return 0;
}

int dia2(COORD current, int matrix[BoardSize][BoardSize], bool turn) {
	int count = 0;
	int Col = (current.X - StartPoint.X) / 4;
	int Row = (current.Y == StartPoint.Y) ? 0 : ((current.Y - StartPoint.Y) / 2);
	while ((Row >= 0) && (Col >= 0) && (matrix[Row][Col] == ((turn == true) ? 1 : -1))) {
		count++;
		Row--;
		Col--;
	}
	Col = (current.X - StartPoint.X) / 4;
	Row = (current.Y == StartPoint.Y) ? 0 : ((current.Y - StartPoint.Y) / 2);
	while ((Col <= BoardSize - 1) && (Row <= BoardSize - 1) && (matrix[Row][Col] == ((turn == true) ? 1 : -1))) {
		count++;
		Row++;
		Col++;
	}
	count -= 1;
	if (count >= 5) {
		if (turn == true) return 1;
		else return -1;
	}
	else return 0;
}

int vertical(COORD current, int matrix[BoardSize][BoardSize], bool turn) {
	int count = 0;
	int Col = (current.X - StartPoint.X) / 4;
	int Row = (current.Y == StartPoint.Y) ? 0 : ((current.Y - StartPoint.Y) / 2);
	while ((Row >= 0) && (matrix[Row][Col] == ((turn == true) ? 1 : -1))) {
		count++;
		Row--;
	}
	Row = (current.Y == StartPoint.Y) ? 0 : ((current.Y - StartPoint.Y) / 2);
	while ((Row <= BoardSize - 1) && (matrix[Row][Col] == ((turn == true) ? 1 : -1))) {
		count++;
		Row++;
	}
	count -= 1;
	if (count >= 5) {
		if (turn == true) return 1;
		else return -1;
	}
	else return 0;
}

int horizontal(COORD current, int matrix[BoardSize][BoardSize], bool turn) {
	int count = 0;
	int Col = (current.X - StartPoint.X) / 4;
	int Row = (current.Y == StartPoint.Y) ? 0 : ((current.Y - StartPoint.Y) / 2);
	while ((Col >= 0) && (matrix[Row][Col] == ((turn == true) ? 1 : -1))) {
		count++;
		Col--;
	}
	Col = (current.X - StartPoint.X) / 4;
	while ((Col <= BoardSize - 1) && (matrix[Row][Col] == ((turn == true) ? 1 : -1))) {
		count++;
		Col++;
	}
	count -= 1;
	if (count >= 5) {
		if (turn == true) return 1;
		else return -1;
	}
	else return 0;
}

//Win-Draw Check
int WinCheck(COORD current, int matrix[BoardSize][BoardSize], bool turn) {
	int result = 0;
	result = dia1(current, matrix, turn);
	if (result != 0) return result;
	result = dia2(current, matrix, turn);
	if (result != 0) return result;
	result = vertical(current, matrix, turn);
	if (result != 0) return result;
	result = horizontal(current, matrix, turn);
	if (result != 0) return result;
}

bool IsDraw(int matrix[BoardSize][BoardSize]) {
	int space = 0;
	for (int i = 0; i < BoardSize; i++) {
		for (int h = 0; h < BoardSize; h++) {
			if (matrix[i][h] == 0) space++;
		}
	}
	if (space == 0) return true;
	return false;
}

int Play(int option) {
	system("cls");
	showcursor();
	int returnvalue = 0; //0 = exit 10 = play again
	char* savedname = NULL;
	int result = 0;
	int array[BoardSize][BoardSize] = {};
	bool Turn = true; //true= X.turn false= O.turn
	char Input;
	filename* list = NULL;
	FILE* gamesave = NULL;
	COORD current = StartPoint;
	if (option == 2) {
		savedname = LoadGameMenu(gamesave, list, array, Turn);
		if (savedname == NULL) return 0;
		system("cls");
	}
	DrawBoard(BoardSize, CaroTopLeft);//newgame
	if (savedname !=NULL) LoadBoard(array);
	DrawTurn(Turn);
	smallInstructionWin(1, Turn);
	GotoXY(current.X, current.Y);
	while (1 == 1) {
		Input = toupper(_getch());
		if ((Input == 'W') && (current.Y != StartPoint.Y)) MoveUp(current);
		if ((Input == 'S') && (current.Y != StartPoint.Y + 2 * (BoardSize - 1))) MoveDown(current);
		if ((Input == 'A') && (current.X != StartPoint.X)) MoveLeft(current);
		if ((Input == 'D') && (current.X != StartPoint.X + 4 * (BoardSize - 1))) MoveRight(current);
		if ((Input == 13) && (array[(current.Y == StartPoint.Y) ? 0 : ((current.Y - StartPoint.Y) / 2)][(current.X - StartPoint.X) / 4] == 0)) {
			CheckBoard(current, array, Turn);
			result = WinCheck(current, array, Turn);
			if (result != 0) {
				smallInstructionWin(0, Turn);
				PauseAndRestartMenu(1, 1);
				Input = toupper(_getch());
				if (Input == 'R') {
					returnvalue=10;
				}
				if (Input == 'S'){
					returnvalue = 0;
				}
				break;
			}
			if (IsDraw(array) == true) {
				smallInstructionWin(2, Turn);
				PauseAndRestartMenu(1, 1);
				Input = toupper(_getch());
				if (Input == 'R') {
					returnvalue = 10;
				}
				if (Input == 'S') {
					returnvalue = 0;
				}
				break;
			}
			if (Turn == true) Turn = false;
			else Turn = true;
			DrawTurn(Turn);
			GotoXY(current.X, current.Y);
		}
		//pause
		if (Input == 27) {
			PauseAndRestartMenu(0, 1);
			GotoXY(current.X, current.Y);
			Input = toupper(_getch());
			if (Input == 'R') {
				PauseAndRestartMenu(0, 0);
			}
			if (Input == 'S') {
				if (savedname == NULL) {
					GotoXY(77, 25);
					SaveNewGame(gamesave, list, array, Turn);
				}
				else SaveExistedGame(savedname, array, Turn);
				returnvalue = 0;
				break;
			}
		}
	}
	free(list);
	return returnvalue; 
}