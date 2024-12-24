#pragma once
#include <Windows.h>
#include <conio.h>
#include <iostream>

extern int _COMMAND;
extern int X1, Y1;

enum { BOARD_SIZE = 15 };
enum { COL = 2 };
enum { MAX_ROW = 7 };
enum { x_center_console = 58 }; //75
enum { y_center_console = 9 }; //17
//Const
const COORD CaroTopLeft = { 0,0 };
const COORD StartPoint = { CaroTopLeft.X + 2,CaroTopLeft.Y + 1 };
const int BoardSize = 12;
//ASCII characters for board-drawing
#define Vertical (char)186
#define Horizontal (char)205
#define Cross (char)206
#define UpCross (char)203
#define LeftCross (char)204
#define RightCross (char)185
#define DownCross (char)202
#define TopLeft (char)201
#define BotLeft (char)200
#define TopRight (char)187
#define BotRight (char)188

#define arrow_up (char) 72
#define arrow_down (char) 80
#define arrow_left (char) 75
#define arrow_right (char) 77
#define enter_char (char) 13
#define esc_char (char) 27
#define cursor_char_l ">>"
#define cursor_char "-"
using namespace std;

//Func
//Drawing
void CreateConsoleWindow(int a);
void FixConsoleWindow();
void GotoXY(int x, int y);
void TextColor(int x);
void Draw_txt_noeffect(const char* file);
void DrawBoard(int size,COORD StartingCoord);

void DrawBoard2(int row, int column, int x, int y, int width, int height);
void horizon(int column, int width, char middle, char out1, char out2);
void vertical(int row, int height, int x, int y);
void init_cursor();
void delete_cursor();
void hidecursor();
void showcursor();

void DrawInstruction();
void DrawXO(bool TURN);
void DrawTurn(bool TURN);
void smallInstructionWin(int mode, bool turn);
void PauseAndRestartMenu(int mode, int activate);



