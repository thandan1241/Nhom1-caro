#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "View.h"
#include "model.h"
using namespace std;

//Func
//Actions on Chessboard
void MoveUp(COORD &x);

void MoveDown(COORD& x);

void MoveLeft(COORD& x);

void MoveRight(COORD& x);

void CheckBoard(const COORD& position, int matrix[BoardSize][BoardSize], bool turn);

//Win Conditions
int dia1(COORD current, int matrix[BoardSize][BoardSize], bool turn);

int dia2(COORD current, int matrix[BoardSize][BoardSize], bool turn);

int vertical(COORD current, int matrix[BoardSize][BoardSize], bool turn);

int horizontal(COORD current, int matrix[BoardSize][BoardSize], bool turn);
//Win-Draw Check
int WinCheck(COORD current, int matrix[BoardSize][BoardSize], bool turn);

bool IsDraw(int matrix[BoardSize][BoardSize]);

int Play(int option);