#include"game.h"
//͸����ͼ
void drawAlpha(IMAGE* picture, int  picture_x, int picture_y) //xΪ����ͼƬ��X���꣬yΪY����
{

	// ������ʼ��
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬EASYX�Դ�
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //��ȡpicture���Դ�ָ��
	int picture_width = picture->getwidth(); //��ȡpicture�Ŀ�ȣ�EASYX�Դ�
	int picture_height = picture->getheight(); //��ȡpicture�ĸ߶ȣ�EASYX�Դ�
	int graphWidth = getwidth();       //��ȡ��ͼ���Ŀ�ȣ�EASYX�Դ�
	int graphHeight = getheight();     //��ȡ��ͼ���ĸ߶ȣ�EASYX�Դ�
	int dstX = 0;    //���Դ������صĽǱ�

	// ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //���Դ������صĽǱ�
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA��͸����
			int sr = ((src[srcX] & 0xff0000) >> 16); //��ȡRGB���R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //���Դ������صĽǱ�
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //��ʽ�� Cp=��p*FP+(1-��p)*BP  �� ��p=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //��p=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //��p=sa/255 , FP=sb , BP=db
			}
		}
	}
}
//��ʼ������
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

	//����ͼƬ ./images/bg.jpg
	//����ͼƬ����
	//����ͼƬ��������
	IMAGE bg;
	loadimage(&bg, _T("./images/bg.jpg"), getwidth(), getheight());
	putimage(0, 0, &bg);

	
}
void gameDraw()
{
	//���Ʒ���
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
//ҡ�ڹ���
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
	//��ǰendx, endy��λ��
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