#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
#include<conio.h>
#pragma warning (disable:4996)
#define ROW 22
#define COL 42
#define EMPTY 0
#define WALL 1
#define FOOD 2
#define HEAD 3
#define BODY 4
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
void menu();
void HideCursor();
void CursorJump(int x, int y);
void InitInterface();
void InitSnake();
void RandFood();
void PrintSnake(int flag);
void MoveSnake(int x, int y);
void JudgeFunc(int x, int y);
void run(int x, int y);
void Play();
