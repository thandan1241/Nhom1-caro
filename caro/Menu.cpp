#include"Menu.h"
void MoveDown1(Menu menu[COL][MAX_ROW], int option)
{
	hidecursor();
	TextColor(255);
	GotoXY(X1 - 2, Y1); std::cout << cursor_char_l;
	if (Y1 < menu[0][option - 1].y)
	{
		GotoXY(X1, Y1);
		Y1 += 2;
		GotoXY(X1, Y1);
	}
}
void MoveUp1(Menu menu[COL][MAX_ROW], int option)
{
	hidecursor();
	TextColor(255);
	GotoXY(X1 - 2, Y1); std::cout << cursor_char_l;
	if (Y1 > menu[0][0].y)
	{
		GotoXY(X1, Y1);
		Y1 -= 2;
		GotoXY(X1, Y1);
	}
}

int MAIN_menu(Menu menu[COL][MAX_ROW]) {
	CreateConsoleWindow(240);
	FixConsoleWindow();
	system("cls");
	DrawBoard2(1, 1, x_center_console - 10, y_center_console - 1, 25, 12); //x_center_console-10, y_center_console-1
	menu[0][0].content = "New Game";
	menu[0][1].content = "Load Game";
	menu[0][2].content = "About Us";
	menu[0][3].content = "Instruction";
	menu[0][4].content = "Exit";
	for (int i = 0; i < 6; i++)
	{
		menu[0][i].y = 2 * i + menu[0][0].y;
		GotoXY(menu[0][i].x, menu[0][i].y);
		std::cout << menu[0][i].content << std::endl;
	}

	GotoXY(X1, Y1);

	while (true)
	{
		init_cursor();
		_COMMAND = toupper(_getch());
		if (_COMMAND == arrow_down)
			MoveDown1(menu, 6);
		else if (_COMMAND == arrow_up)
			MoveUp1(menu, 6);
		else if (_COMMAND == enter_char)
		{
			delete_cursor();
			if (X1 == (menu[0][0].x - 1) && (Y1 == menu[0][0].y))
				return 1;
			else if (X1 == menu[0][1].x - 1 && Y1 == menu[0][1].y)
				return 2;
			else if (X1 == menu[0][2].x - 1 && Y1 == menu[0][2].y)
				return 3;
			else if (X1 == menu[0][3].x - 1 && Y1 == menu[0][3].y)
				return 4;
			else if (X1 == menu[0][4].x - 1 && Y1 == menu[0][4].y)
				return 5;
			else if (X1 == menu[0][5].x - 1 && Y1 == menu[0][5].y)
				return 6;
		}
	}
}

int MAIN_Menu_Run(int option) {
	string file_select;
	hidecursor();
	switch (option) {
	case 1: 
		return 1;
	case 2:
		return 2;
	case 3:
		system("cls");
		Draw_txt_noeffect("AboutUs.txt");
		return 3;
	case 4:
		system("cls");
		DrawInstruction();
		return 4;
	case 5:
		system("cls");
		return 0;
	}
}