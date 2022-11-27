#define _CRT_SECURE_NO_WARNINGS 1
#include "game.h"
#pragma warning (disable:4996)

void game()
{
	HideCursor();
	InitInterface();
	InitSnake();
	RandFood();
	PrintSnake(1);
	Play();
}
int main()
{
	CursorJump(2 * (COL / 3), ROW / 2);
	menu();
	system("title Gluttonous Snack");
	game();
	return 0;
}