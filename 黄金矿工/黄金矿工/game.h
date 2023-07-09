#define _CRT_SECURE_NO_WARNINGS
#define _stprintf
#include<stdio.h>
#include<easyx.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

#undef UNICODE
#undef _UNICODE

#define MAX_ITERM 6
#define PI 3.14159265358979323846
#define distance(hook) (sqrt(pow(hook.x - hook.endx, 2) + pow(hook.y - hook.endy, 2)))
//º”‘ÿÀ˘”–Õº∆¨
IMAGE img[MAX_ITERM];
struct SCORE
{
	int coin;
}score;
enum Index
{
	i_gold1 = 0,
	i_gold2 = 1,
	i_gold3 = 2,
	i_stone1 = 3,
	i_stone2 = 4,
	i_money = 5
}index;
struct Iterm
{
	int coin;
	int x;
	int y;
	int height;
	int width;
	bool flag;
	int type;
	int gold;

}iterm[MAX_ITERM];
enum Dir
{
	LEFT,
	RIGHT
};
enum State
{
	S_ORIGIN,
	S_LONG,
	S_SHORT
	
};
struct Hook
{
	int x;
	int y;
	int endx;
	int endy;
	int len;
	double ang;
	Dir dir;
	int vx;
	int vy;
	State state;
	int index;
}hook;

enum TYPE
{
	GOLD1,
	GOLD2,
	GOLD3,
	STONE1,
	STONE2,
	MONEY
	
	
};
