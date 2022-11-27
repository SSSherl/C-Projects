#include "game.h"
#pragma warning (disable:4996)
int face[ROW][COL];
int count = 0;
char C = '0';
struct Snake
{
	int length;//蛇身长度
	int x;//蛇头横坐标
	int y;//蛇头纵坐标
}snake;
struct Body
{
	int x;//蛇身横坐标
	int y;//蛇身纵坐标
}body[ROW * COL];
void HideCursor()
{
	CONSOLE_CURSOR_INFO curInfo;
	curInfo.dwSize = 1;
	curInfo.bVisible = FALSE;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(handle, &curInfo);
}
void CursorJump(int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, pos);
}
void menu()
{
	CursorJump(2 * (COL / 3), ROW / 2);
	printf("Easy.A or Difficult.B or Very Difficult.C \n");
	scanf("%c", &C);
	system("cls");
	if (C == '0')
	{
		exit(0);
	}
	

}
void InitInterface()
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (j == 0 || j == COL - 1)
			{
				face[i][j] = WALL; 
				CursorJump(2 * j, i);
				printf("■");
			}
			else if (i == 0 || i == ROW - 1)
			{
				face[i][j] = WALL; 
				printf("■");
			}
			else
			{
				face[i][j] = EMPTY; 
			}
		}
	}
	
}
void InitSnake()
{
	

	snake.length = 2;
	snake.x = COL / 2;
	snake.y = ROW / 2;

	body[0].x = COL / 2 - 1;
	body[0].y = ROW / 2;
	body[1].x = COL / 2 - 2;
	body[1].y = ROW / 2;

	face[snake.x][snake.y] = HEAD;
	face[body[0].x][body[0].y] = BODY;
	face[body[1].x][body[1].y] = BODY;

}


void RandFood()
{
	int i, j;
	do
	{
		srand((unsigned int)time(NULL));
		i = rand() % ROW;
		j = rand() % COL;
	} while (face[i][j] != EMPTY);
	face[i][j] = FOOD;
	CursorJump(2*j, i);
	printf("●");
}

void PrintSnake(int flag)
{
	if (flag == 1)
	{
		CursorJump(2 * snake.x, snake.y);
		printf("■");
		for (int i = 0; i < snake.length; i++)
		{
			CursorJump(2 * body[i].x, body[i].y);
			printf("□");
		}
	}
	else 
	{
		if (body[snake.length - 1].x != 0) 
		{
			CursorJump(2 * body[snake.length - 1].x, body[snake.length - 1].y);
			printf("  ");
		}
	}
}

void MoveSnake(int x, int y)
{
	PrintSnake(0);
	face[body[snake.length - 1].y][body[snake.length - 1].x] = EMPTY;
	face[snake.y][snake.x] = BODY;
	for (int i = snake.length - 1; i > 0; i--)
	{
		body[i].x = body[i - 1].x;
		body[i].y = body[i - 1].y;
		
	}
	body[0].y = snake.y;
	body[0].x = snake.x;
	snake.x = snake.x + x;
	snake.y = snake.y + y;
	PrintSnake(1);

}

void JudgeFunc(int x, int y)
{
	if (face[snake.y + y][snake.x + x] == FOOD)
	{
		snake.length++;
		count++;
		RandFood();
		

	}
	else if(face[snake.y + y][snake.x + x] == BODY || face[snake.y + y][snake.x + x] == WALL)
	{
		Sleep(500);
		system("cls");
		CursorJump(2 * (COL / 3), ROW / 2);
		printf("Game Over.Your score is %d.",count);
	}
}
void run(int x, int y)
{
	int t = 0;
	while (1)
	{	
		if(t ==0)
		{
			if (C == 'A')
			{
				t = 10000;
			}
			else if (C == 'B')
			{
				t = 7000;
			}
			else
			{
				t = 3000;
			}
		}
		while (--t)
		{
			if (kbhit() != 0) 
			{
				break;
			}
		}
		if (t == 0) 
		{
			JudgeFunc(x, y); 
			MoveSnake(x, y); 
		}
		else 
		{
			break; 
		}
	}
}

void Play()
{
	int n = RIGHT;
	int tmp = 0;
	goto first;
	while (1)
	{
		n = getch();
		switch (n)
		{
		case UP:
		case DOWN:
			if (tmp != LEFT && tmp != RIGHT)
			{
				n = tmp;
			}
			break;
		case LEFT:
		case RIGHT:
			if (tmp != UP && tmp != DOWN)
			{
				n = tmp;
			}
			break;
		}

	first:
		switch (n)
		{
		case UP:
			run(0, -1);
			tmp = UP;
			break;
		case DOWN:
			run(0, 1);
			tmp = DOWN;
			break;
		case LEFT:
			run(-1, 0);
			tmp = LEFT;
			break;
		case RIGHT:
			run(1, 0);
			tmp = RIGHT;
			break;
		}

	}
	
}

