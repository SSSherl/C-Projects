#include<easyx.h>
#include<stdio.h>
#include<math.h>
#define PI 3.14

void point()
{
	int x;
	int y;
	for(int i = 0; i < 1000; i++)
	{
		x = rand() % (800 + 1) - 400;// % (800 + 1):0~800
		y = rand() % (600 + 1) - 300;
		putpixel(x, y, WHITE);
	}
}
void ConcentCircle()
{
	for (int r = 10; r <= 300; r += 10)
	{
		circle(0, 0, r);
	}

}
void triangle()
{
	POINT points[] = { {0, 200}, {200, -200},{-200, -200} };
	polygon(points, 3);

}
void trapezoid()
{
	POINT points[] = { {-100, 100}, {100, 100}, {-200, -100}, {200, -100}, {-200, -100} };
	polygon(points, 4);
}
void pentagon()
{
	/*typedef struct
	{
		LONG x;
		LONG y;
	}PIONT;*/
	double theta = PI / 2;
	double delta = 2 * PI / 5;
	POINT points[5];
	for (int r = 0; r < 5; r++)
	{
		points[r].x = cos(theta + r * delta) * 200;
		points[r].y = sin(theta + r * delta) * 200;
	}
	polygon(points, 5);

}
void printW()
{
	POINT points[] = { {-400, 200}, {-200, -200}, {0, 100}, {200, -200}, {400, 200} };
	polyline(points, 5);
}
int main()
{
	initgraph(800, 600);			//绘制窗口
	setorigin(400, 300);			//逻辑坐标原点置于中心
	setaspectratio(1, -1);			//反转y轴
	setlinecolor(YELLOW);
	ConcentCircle();				//画圆
	point();						//画点
	line(-200, 200, 200, -200);		//画直线
	line(200, 200, -200, -200);
	rectangle(-200, 100, 200, -100);//画矩形
	ellipse(-200, 100, 200, -100);	//画椭圆
	roundrect(-200, 100, 200,		//画圆角矩形
			  -100, 200, 100);
	pie(-200, 100, 200,				//画扇形
		- 100, 0, PI / 4);
	arc(-200, 100, 200,				//绘制圆弧
		-100, 0, PI / 4);
	triangle();						//绘制三角形
	trapezoid();					//绘制梯形
	pentagon();						//绘制五边形
	printW();						//绘制“W”（不封闭图形）
	getchar();
	closegraph();

	return 0;
}