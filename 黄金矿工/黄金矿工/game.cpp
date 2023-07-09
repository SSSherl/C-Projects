#include"game.h"
//透明贴图
void drawAlpha(IMAGE* picture, int  picture_x, int picture_y) //x为载入图片的X坐标，y为Y坐标
{

	// 变量初始化
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //获取picture的显存指针
	int picture_width = picture->getwidth(); //获取picture的宽度，EASYX自带
	int picture_height = picture->getheight(); //获取picture的高度，EASYX自带
	int graphWidth = getwidth();       //获取绘图区的宽度，EASYX自带
	int graphHeight = getheight();     //获取绘图区的高度，EASYX自带
	int dstX = 0;    //在显存里像素的角标

	// 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //在显存里像素的角标
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度
			int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //在显存里像素的角标
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //αp=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //αp=sa/255 , FP=sb , BP=db
			}
		}
	}
}
//初始化数据
void initData()
{
	srand(time(NULL));
	hook.x = 475;
	hook.y = 70;
	hook.len = 50;
	hook.endx = hook.x;
	hook.endy = hook.y + hook.len;
	hook.ang = 0.0;
	hook.dir = RIGHT;
	hook.vx = 0;
	hook.vy = 0;
	hook.state = S_ORIGIN;
	hook.index = -1;

	iterm[i_gold1].height = 112;
	iterm[i_gold1].width = 124;
	iterm[i_gold2].height = 43;
	iterm[i_gold2].width = 47;
	iterm[i_gold3].height = 23;
	iterm[i_gold3].width = 25;
	iterm[i_stone1].height = 68;
	iterm[i_stone1].width = 76;
	iterm[i_stone2].height = 54;
	iterm[i_stone2].width = 45;
	iterm[i_money].height = 61;
	iterm[i_money].width = 54;
	iterm[i_money].gold = rand() % 301;
	iterm[i_gold1].gold = 100;
	iterm[i_gold2].gold = 60;
	iterm[i_gold3].gold = 30;
	iterm[i_stone1].gold = 16;
	iterm[i_stone2].gold = 2;
	for (int i = 0; i < MAX_ITERM; i++)
	{
		iterm[i].x = rand() % 805;
		iterm[i].y = rand() % 185 + 200;
		iterm[i].flag = 1;
		iterm[i].type = rand() % 6;
		CHAR fileName[20] = { 0 };
		wsprintf(fileName, _T("./images/%d.jpg"), i);
		loadimage(&img[i], fileName);

	}
	
}
void SetBackground()
{

	//背景图片 ./images/bg.jpg
	//定义图片变量
	//加载图片到变量中
	IMAGE bg;
	loadimage(&bg, _T("./images/bg.jpg"), getwidth(), getheight());
	putimage(0, 0, &bg);

	
}
void gameDraw()
{
	//绘制分数
	settextstyle(48, 0, TEXT(" "));
	setbkmode(TRANSPARENT);
	char str[100] = { 0 };
	sprintf(str, "%d", score.coin);
	outtextxy(100, 10, TEXT(str));
	

	
	
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 3);
	line(hook.x, hook.y, hook.endx, hook.endy);
	for (int i = 0; i < MAX_ITERM; i++)
	{
		if(iterm[i].flag == 1)
		{
			if (iterm[i].flag == 1)
			{
				if (iterm[i].type == GOLD1 || iterm[i].type == GOLD2 || iterm[i].type == GOLD3)

				{
					drawAlpha(&img[i], iterm[i].x, iterm[i].y);

				}
				if (iterm[i].type == MONEY)

				{
					drawAlpha(&img[i], iterm[i].x, iterm[i].y);

				}
				if (iterm[i].type == STONE1 || iterm[i].type == STONE2)

				{
					drawAlpha(&img[i], iterm[i].x, iterm[i].y);
				}

			}
		}

	}
}
//摇摆钩子
void hookRock(double inc)
{
	if (hook.state != S_ORIGIN)
	{
		return;
	}
	if (hook.dir == RIGHT)
	{
		hook.ang += inc;

	}
	else
	{
		hook.ang -= inc;

	}
	if (hook.ang >= 71)
	{
		hook.dir = LEFT;
	}
	else if(hook.ang <= -71)
	{
		hook.dir = RIGHT;
	}
	//求当前endx, endy的位置
	hook.endx = hook.x + sin(PI / 180 * hook.ang) * hook.len;
	hook.endy = hook.y + cos(PI / 180 * hook.ang) * hook.len;
	

}
void HookLength(int speed)
{
	if (GetAsyncKeyState(VK_SPACE) && hook.state == S_ORIGIN)
	{
		hook.state = S_LONG;
		hook.vx = sin(PI / 180 * hook.ang) * speed;
		hook.vy = cos(PI / 180 * hook.ang) * speed;
	}
	if(hook.state == S_LONG)
	{
		hook.endx += hook.vx;
		hook.endy += hook.vy;
	}
	else if (hook.state == S_SHORT)
	{
		hook.endx -= hook.vx;
		hook.endy -= hook.vy;
	}
	if (hook.endx <= 0 || hook.endx >= getwidth() || hook.endy >= getheight())
	{
		hook.state = S_SHORT;
	}
	if (distance(hook) <= hook.len && hook.index == -1)
	{
		hook.state = S_ORIGIN;
	}
}
void Grap()
{
	if (hook.state == S_ORIGIN)
	{
		return;
	}

	for (int i = 0; i < MAX_ITERM; i++)
	{
		if (iterm[i].flag == 1 && hook.endx > iterm[i].x && hook.endx < iterm[i].x + iterm[i].width &&
			hook.endy > iterm[i].y && hook.endy < iterm[i].y + iterm[i].height)
		{
			hook.index = i;
		}
	}
	if (hook.index != -1)
	{
		hook.state = S_SHORT;
		iterm[hook.index].x = hook.endx;
		iterm[hook.index].y = hook.endy;
		if (distance(hook) <= hook.len )
		{
			hook.state = S_ORIGIN;
			iterm[hook.index].flag = 0;
			score.coin += iterm[hook.index].gold;
			hook.index = -1;
		}
	}
}
int main()
{
	initgraph(960, 540);
	cleardevice();
	initData();
	
	BeginBatchDraw();
	while (true)
	{
		cleardevice();
		SetBackground();
		gameDraw();
		hookRock(0.3);
		HookLength(5);
		Grap();
		FlushBatchDraw();

	}
	EndBatchDraw();
	getchar();
	return 0;
}