#include <iostream>
#include "View.h"
#include <conio.h>
#include "control.h"
#include "model.h"
#include"Menu.h"
using namespace std;

int X1;//kh?i t?o ??a ch? con tr? ban ??u
int Y1;
int _COMMAND;//l?nh nh?p vào t? bàn phím 
bool _TURN;// l??t c?a ng??i ch?i 
int _X, _Y;
int S1, S2;
//int Color_X, Color_O;
//int CountMoveP1, CountMoveP2;
int main() {
	
	Menu menu[COL][MAX_ROW];
	int running = 1;
	X1 = x_center_console - 1;
	Y1 = y_center_console;
	while (running==running)
	{
		if (running == 10) { 
			running = Play(1);
			continue;
		}
		running = MAIN_Menu_Run(MAIN_menu(menu));
		if (running == 0) return 0;
		if ((running == 1) || (running == 2)) {
			running = Play(running);
		}
	}
	cout << "SEE U NEXT TIME";
	return 0;
}