#include <iostream>
#include "../../Downloads/console/console.h"
#include <Windows.h>
#include <conio.h>
#include <time.h>
#define consoleWidth 108
#define consoleHeight 30

using namespace std;

enum trangthai {UP, DOWN, LEFT, RIGHT};

struct toado
{
	int x, y;
};

struct Snake
{
	toado dot[31];
	int n;
	trangthai tt;
};

struct Moi
{
	toado td;
};

void KhoiTao (Snake &snake , Moi &hq)
{
	snake.n = 1;
	snake.dot[0].x = 0;
	snake.dot[0].y = 0;
	snake.tt = RIGHT;

	hq.td.x = 10;
	hq.td.y = 10;
}

void HienThi(Snake snake, Moi hq) // khong co nhu cau thay doi con ran nen khong can dau &
{
	clrscr();

	for (int i = 0; i < consoleHeight; i++)
	{

		gotoXY(consoleWidth, i);
		cout << (char)178;
	}
			

	gotoXY(hq.td.x, hq.td.y);
    cout << "<3";
	for (int i = 0; i < snake.n; i++)
	{
		gotoXY(snake.dot[i].x, snake.dot[i].y);
		cout << "*";
	}
		
}

void DieuKhien(Snake &snake)
{
	for (int i = snake.n - 1; i > 0; i--)
		snake.dot[i] = snake.dot[i - 1];
	if (_kbhit())
	{
		int key = _getch();
		// dieu khien dau ran
		if (key == 'L' || key == 'l')
			snake.tt = LEFT;
		else if (key == 'R' || key == 'r')
			snake.tt = RIGHT;
		else if (key == 'U' || key == 'u')
			snake.tt = UP;
		else if (key == 'D' || key == 'd')
			snake.tt = DOWN;
		
		if (snake.tt == UP)
			snake.dot[0].y--;
		else if (snake.tt == DOWN)
			snake.dot[0].y++;
		else if (snake.tt == LEFT)
			snake.dot[0].x--;
		else if (snake.tt == RIGHT)
			snake.dot[0].x++;
	}
}

int XuLy(Snake& snake, Moi& hq)
{
	if (snake.dot[0].x == hq.td.x && snake.dot[0].y == hq.td.y)
	{
		for (int i = snake.n - 1; i > 0; i--)
			snake.dot[i] = snake.dot[i - 1];

		snake.n++;

		if (snake.tt == UP)
			snake.dot[0].y--;
		else if (snake.tt == DOWN)
			snake.dot[0].y++;
		else if (snake.tt == LEFT)
			snake.dot[0].x--;
		else if (snake.tt == RIGHT)
			snake.dot[0].x++;
		hq.td.x = rand() % consoleWidth;
		hq.td.y = rand() % consoleHeight;
	}

	if (snake.dot[0].x < 0 || snake.dot[0].x >= consoleWidth ||
		snake.dot[0].y < 0 || snake.dot[0].y >= consoleHeight)
		return 0;
	
	for (int i = 1; i < snake.n; i++)
		if (snake.dot[0].x == snake.dot[i].x &&
			snake.dot[0].y == snake.dot[i].y)
			return 0;

}

int main()
{
	srand(time(NULL));
	Snake snake;
	Moi hq;
	KhoiTao(snake,hq);

	int kt = 1;

	while (1)
	{
		// hien thi
		HienThi (snake,hq);

		// dieu khien
		DieuKhien (snake);

		// xu li
		kt = XuLy(snake, hq);


		// gameover
		if (kt == 0)
		{
			gotoXY(consoleWidth/2, 10);
			cout << "LOSE";
			_getch();
			break;
		}
		Sleep(200);
	}


	return 0;
}