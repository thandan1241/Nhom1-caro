#include "View.h"



//Drawing
void CreateConsoleWindow(int a)
{
	HWND consoleWindow = GetConsoleWindow();
	RECT r;
	HANDLE hConsole;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, a);
	GetWindowRect(consoleWindow, &r);
	MoveWindow(consoleWindow, 50, 50, 1320, 700, 1);
	ShowScrollBar(consoleWindow, SB_BOTH, FALSE);
}
void FixConsoleWindow()
{
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}
void TextColor(int x)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, x);
}//chuyển màu văn bản không quan tâm màu nền 

void GotoXY(int x, int y) {
		COORD coord;
		coord.X = x;
		coord.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}void init_cursor()	//khởi tạo con trỏ
{
	hidecursor();
	TextColor(240);
	GotoXY(X1 - 2, Y1); std::cout << cursor_char_l;
}

void delete_cursor()
{
	hidecursor();
	TextColor(255);
	GotoXY(X1 - 2, Y1); std::cout << cursor_char_l;
	TextColor(240);
}

void hidecursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}
void showcursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = TRUE;
	SetConsoleCursorInfo(consoleHandle, &info);
}
void Draw_txt_noeffect(const char* file)//hiển thị file txt ra màn hình 
{
	FILE* h;
	int c;
	int printing = true;
	int running = true;
	GotoXY(0, 5);
	while (running)
	{
		fopen_s(&h, file, "r");
		if (h == NULL) return;
		hidecursor();
		while (printing)
		{
			TextColor(252);
			c = fgetc(h);
			std::cout << (char)c;
			if (feof(h))
				printing = false;
		}
		fclose(h);
		_COMMAND = toupper(_getch());
		if (_COMMAND == esc_char)
		{
			running = false;
		}
	}
	TextColor(240);
}
void DrawBoard(int size,COORD StartingCoord) {
	COORD currentpos = { StartingCoord.X,StartingCoord.Y };
	int totalborder = size + 1;
	for (int i = 0; i < totalborder; i++) {
		if(i!=0) currentpos.Y += 2;
		currentpos.X = StartingCoord.X;
		for (int h = 0; h < totalborder-1; h++) {
			GotoXY(currentpos.X, currentpos.Y);
			if ((i == 0) && (h == 0)) cout << TopLeft << Horizontal << Horizontal << Horizontal << UpCross;
			else if ((i == totalborder - 1) && (h == 0)) cout << BotLeft << Horizontal << Horizontal << Horizontal << DownCross;
			else if ((i == 0) && (h == totalborder - 2)) cout << UpCross << Horizontal << Horizontal << Horizontal << TopRight;
			else if ((i == totalborder - 1) && (h == totalborder - 2)) cout << DownCross << Horizontal << Horizontal << Horizontal << BotRight;
			else if (h == 0) cout << LeftCross << Horizontal << Horizontal << Horizontal << Cross;
			else if (h == totalborder-2) cout << Cross << Horizontal << Horizontal << Horizontal << RightCross;
			else if (i == 0) cout << UpCross << Horizontal << Horizontal << Horizontal << UpCross;
			else if (i == totalborder-1)  cout << DownCross << Horizontal << Horizontal << Horizontal << DownCross;
			else cout << Cross << Horizontal << Horizontal << Horizontal << Cross;
			currentpos.X += 4;
		}
		currentpos.X = StartingCoord.X;
		if (i != totalborder - 1) {
			for (int h = 0; h < totalborder - 1; h++) {
				GotoXY(currentpos.X, currentpos.Y + 1);
				cout << Vertical << "   " << Vertical;
				currentpos.X += 4;
			}
		}
	}
}
void vertical(int row, int height, int x, int y)//vẽ dọc 
{
	int max = row * height;
	for (int i = 1; i < max; i++)
	{
		GotoXY(x, y + i);
		std::cout << Vertical;
	}
}
void horizon(int column, int width, char middle, char out1, char out2)//vẽ ngang
{
	for (int i = 0; i < column; i++)
	{
		if (i == 0)
			std::cout << out1;
		else
			std::cout << middle;
		for (int j = 1; j <= width; j++)
			std::cout << Horizontal;
	}
	std::cout << out2;
}
void DrawBoard2(int row, int column, int x, int y, int width, int height)//vẽ bảng
{
	for (int i = 0; i <= column; i++)
	{
		vertical(row, height, x + i * (width + 1), y);
		Sleep(2);
	}
	for (int i = 0; i <= row; i++)
	{
		GotoXY(x, y + i * height);
		if (i == 0)
			horizon(column, width, UpCross, TopLeft, TopRight);
		else if (i == row)
			horizon(column, width, DownCross, BotLeft, BotRight);
		else
			horizon(column, width, Cross, LeftCross, RightCross);
		Sleep(2);
	}
}

void DrawInstruction() {
	int buf;
	GotoXY(30, 9);
	cout << TopLeft;
	for (int i = 0; i < 59; i++) {
		cout << Horizontal;
	}
	cout << TopRight;
	for (int i = 1; i < 10; i++) {
		GotoXY(30, 9 + i);
		cout << Vertical;
		for (int h = 0; h < 59; h++) { cout << " "; }
		cout << Vertical;
	}
	GotoXY(30, 19);
	cout << BotLeft;
	for (int i = 0; i < 59; i++) {
		cout << Horizontal;
	}
	cout << BotRight;
	GotoXY(55, 10);
	TextColor(241); //White BackGround and Dark Blue
	cout << " KEY LAYOUT";
	GotoXY(40, 11);
	cout << "W = GO UP";
	GotoXY(70, 12);
	cout << "ENTER = CHECK BOARD";
	GotoXY(40, 13);
	cout << "S = GO DOWN";

	GotoXY(40, 15);
	cout << "A = GO LEFT";
	GotoXY(70, 16);
	cout << "ESC = PAUSE";
	GotoXY(40, 17);
	cout << "D = GO RIGHT";
	GotoXY(35, 21);
	system("pause");
	TextColor(240); //return to default color
	return;
}
void DrawXO(bool TURN) {
	if (TURN == true) {
		TextColor(255);
		GotoXY(100, 0);
		cout << TopLeft << Horizontal << Horizontal << Horizontal << Horizontal << Horizontal << Horizontal << Horizontal << TopRight;
		GotoXY(100, 1);
		cout << Vertical << "       " << Vertical;
		GotoXY(100, 2);
		cout << Vertical << "       " << Vertical;
		GotoXY(100, 3);
		cout << Vertical << "       " << Vertical;
		GotoXY(100, 4);
		cout << BotLeft << Horizontal << Horizontal << Horizontal << Horizontal << Horizontal << Horizontal << Horizontal << BotRight;
		TextColor(252);
		GotoXY(100, 0);
		cout << TopLeft << Horizontal << Horizontal << Horizontal << UpCross << Horizontal << Horizontal << Horizontal << TopRight;
		GotoXY(100, 1);
		cout << "    " << Vertical << "    ";
		GotoXY(100, 2);
		cout << "    " << Vertical << "    ";
		GotoXY(100, 3);
		cout << "    " << Vertical << "    ";
		GotoXY(100, 4);
		cout << BotLeft << Horizontal << Horizontal << Horizontal << DownCross << Horizontal << Horizontal << Horizontal << BotRight;
		TextColor(240);
	}
	else {
		TextColor(255);
		GotoXY(100, 0);
		cout << TopLeft << Horizontal << Horizontal << Horizontal << UpCross << Horizontal << Horizontal << Horizontal << TopRight;
		GotoXY(100, 1);
		cout << "    " << Vertical << "    ";
		GotoXY(100, 2);
		cout << "    " << Vertical << "    ";
		GotoXY(100, 3);
		cout << "    " << Vertical << "    ";
		GotoXY(100, 4);
		cout << BotLeft << Horizontal << Horizontal << Horizontal << DownCross << Horizontal << Horizontal << Horizontal << BotRight;
		TextColor(241);
		GotoXY(100, 0);
		cout << TopLeft << Horizontal << Horizontal << Horizontal << Horizontal << Horizontal << Horizontal << Horizontal << TopRight;
		GotoXY(100, 1);
		cout << Vertical << "       " << Vertical;
		GotoXY(100, 2);
		cout << Vertical << "       " << Vertical;
		GotoXY(100, 3);
		cout << Vertical << "       " << Vertical;
		GotoXY(100, 4);
		cout << BotLeft << Horizontal << Horizontal << Horizontal << Horizontal << Horizontal << Horizontal << Horizontal << BotRight;
		TextColor(240);
	}
}
void DrawTurn(bool TURN) {
	if (TURN == true) TextColor(252);
	else TextColor(241);
	GotoXY(55, 0);
	cout << TopLeft << Horizontal << Horizontal << Horizontal << UpCross << Horizontal << Horizontal << Horizontal << TopRight << " " << TopLeft << "       " << TopRight << " " << TopLeft << Horizontal << Horizontal << Horizontal << Horizontal << Horizontal << Horizontal << Horizontal << TopRight << " " << TopLeft << Horizontal << Horizontal << Horizontal << Horizontal << Horizontal << Horizontal << Horizontal << TopRight;
	GotoXY(55, 1);
	cout << "    " << Vertical << "     " << Vertical << "       " << Vertical << " " << Vertical << "       " << Vertical << " " << Vertical << "       " << Vertical;
	GotoXY(55, 2);
	cout << "    " << Vertical << "     " << Vertical << "       " << Vertical << " " << LeftCross << Horizontal << Horizontal << Horizontal << UpCross << Horizontal << Horizontal << Horizontal << BotRight << " " << Vertical << "       " << Vertical;
	GotoXY(55, 3);
	cout << "    " << Vertical << "     " << Vertical << "       " << Vertical << " " << Vertical << "   " << Vertical << "     " << Vertical << "       " << Vertical;
	GotoXY(55, 4);
	cout << "    " << DownCross << "     " << BotLeft << Horizontal << Horizontal << Horizontal << Horizontal << Horizontal << Horizontal << Horizontal << BotRight << " " << DownCross << "   " << BotLeft << Horizontal << Horizontal << Horizontal << BotRight << " " << BotLeft << "       " << BotLeft;
	DrawXO(TURN);
}
void smallInstructionWin(int mode, bool turn) {
	GotoXY(55, 8);
	cout << TopLeft;
	for (int i = 0; i < 63; i++) {
		cout << Horizontal;
	}
	cout << TopRight;
	for (int i = 0; i < 7; i++) {
		GotoXY(55, 9 + i);
		cout << Vertical;
		for (int h = 0; h < 63; h++) {
			cout << " ";
		}
		cout << Vertical;
	}
	GotoXY(55, 16);
	cout << BotLeft;
	for (int i = 0; i < 63; i++) {
		cout << Horizontal;
	}
	cout << BotRight;
	if (mode == 1) {
		GotoXY(60, 10);
		cout << "A = LEFT";
		GotoXY(60, 11);
		cout << "D = RIGHT";
		GotoXY(60, 12);
		cout << "W = UP";
		GotoXY(60, 13);
		cout << "S = DOWN";
		GotoXY(80, 10);
		cout << "ENTER = PLACE MARK";
		GotoXY(80, 13);
		cout << "ESC = PAUSE";
	}
	else if(mode == 0){
		if (turn == true) {
			TextColor(252);
			GotoXY(60, 10);
			cout << "x    x        x       x       x   x x x x x x      xx    x";
			GotoXY(60, 11);
			cout << " x  x          x     x x     x         x           x x   x";
			GotoXY(60, 12);
			cout << "  xx            x   x   x   x          x           x  x  x";
			GotoXY(60, 13);
			cout << " x  x            x x     x x           x           x   x x ";
			GotoXY(60, 14);
			cout << "x    x            x       x       x x x x x x      x    xx";
			TextColor(240);
		}
		else {
			TextColor(241);
			GotoXY(60, 10);
			cout << "o o o o       o       o       o   o o o o o o      oo    o";
			GotoXY(60, 11);
			cout << "o     o        o     o o     o         o           o o   o";
			GotoXY(60, 12);
			cout << "o     o         o   o   o   o          o           o  o  o";
			GotoXY(60, 13);
			cout << "o     o          o o     o o           o           o   o o ";
			GotoXY(60, 14);
			cout << "o o o o           o       o       o o o o o o      o    oo";
			TextColor(240);
		}
	}
	else if(mode==2){
		TextColor(245);
		GotoXY(60, 10);
		cout << "o o o o   x x x x x        o        x        x        x";
		GotoXY(60, 11);
		cout << "o     o   x       x       o o        x      x x      x ";
		GotoXY(60, 12);
		cout << "o     o   x x x x x      o o o        x    x   x    x";
		GotoXY(60, 13);
		cout << "o     o   x   x         o     o        x  x     x  x";
		GotoXY(60, 14);
		cout << "o o o o   x   x x x    o       o        xx       xx";
		TextColor(240);
	}
}
void PauseAndRestartMenu(int mode, int activate) {
	//mode = 0: pause mode = 1 : restart
	TextColor(240);
	if (activate == 0) TextColor(255);
	GotoXY(75, 20);
	cout << TopLeft;
	for (int i = 0; i < 40; i++) {
		cout << Horizontal;
	}
	cout << TopRight;
	for (int i = 0; i < 7; i++) {
		GotoXY(75, 21 + i);
		cout << Vertical;
		for (int h = 0; h < 40; h++) {
			cout << " ";
		}
		cout << Vertical;
	}
	GotoXY(75, 27);
	cout << BotLeft;
	for (int i = 0; i < 40; i++) {
		cout << Horizontal;
	}
	cout << BotRight;
	if (mode == 0) {
		TextColor(240);
		if (activate == 0) TextColor(255);
		GotoXY(92, 21);
		cout << "PAUSE";
		GotoXY(80, 23);
		if (activate == 1) TextColor(241);
		cout << "RESUME (R)";
		if (activate == 1) TextColor(252);
		cout << "         SAVE & EXIT (S)";
		TextColor(240);
	}
	else {
		PauseAndRestartMenu(0, 0);
		TextColor(240);
		GotoXY(90, 21);
		cout << "PLAY AGAIN?";
		GotoXY(82, 23);
		TextColor(241);
		cout << "YES (R)";
		TextColor(252);
		cout << "             EXIT (S)";
		TextColor(240);
	}
}