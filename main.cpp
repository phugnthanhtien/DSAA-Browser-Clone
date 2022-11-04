#include <iostream>
#include <string>
#include "mylib.h"
#define MAX 100
#define outlinecolor 11

using namespace std;

// variable global
int positionX[6];
int textColor = 15;
int bgColor = 200;

void box(int x, int y, int width, int height, int b_color, int t_color, string text, bool isCenter);
void n_box(int x, int y, int width, int height, int b_color, int t_color, string text, bool isCenter, int sl);
void highline(int x, int y, int w, int h, int b_color, int t_color, string text, bool isCenter);
void movePointer(int start_x, int start_y, int width, int height, bool isCenter);
void header();
void listLichSu();
void veLichSu();

int main()
{

	set_console_size(1000, 600);

	veLichSu();

	_getch();
	return 0;
}

void veLichSu()
{
	// header
	int xHeader = 1;
	int yHeader = 1;
	int heightHeader = 2;
	bool isCenterHeader = true;

	// lichsu
	int xLichSu = 1;
	int yLichSu = 6;
	int widthLichSu = 100;
	int heightLichSu = 2;
	bool isCenterLichSu = false;
	int sl = 5;



	header();
	listLichSu();

	int start_x = xLichSu, start_y = yLichSu;
	int width = widthLichSu, height = heightLichSu;
	bool isCenter = isCenterLichSu;

	movePointer(start_x, start_y, width, height, isCenter);
}

void movePointer(int start_x, int start_y, int width, int height, bool isCenter)
{
	int sl = 5;
	int xp = start_x;
	int yp = start_y;
	int xcu = xp;
	int ycu = yp;
	bool check = true;
	while (true)
	{
		if (check == true)
		{
			gotoXY(xcu, ycu);
			highline(xcu, ycu, width, height, 1, textColor, "Lich Su", isCenter); // rs thanh sang cu
			xcu = xp;
			ycu = yp;
			highline(xp, yp, width, height, bgColor, textColor, "Lich Su", isCenter);
			check = false;
		}
		if (_kbhit())
		{
			char c = _getch();
			if (c == -32)
			{
				check = true; // flag
				c = _getch();
				if (c == 72)
				{
					if (yp != start_y)
						yp -= 2;
					else
					{
						yp = start_y + height * (sl - 1);
					}
				}
				else if (c == 80)
				{
					if (yp != start_y + height * (sl - 1))
						yp += 2;
					else
					{
						yp = start_y;
					}
				}
			}
		}
	}
}

void listLichSu()
{
	ShowCur(0);
	int start_x = 1;
	int start_y = 6;
	int width = 100;
	int height = 2;
	bool isCenter = false;
	int sl = 5;

	n_box(start_x, start_y, width, height, 1, textColor, "Lich Su", isCenter, sl);
	highline(start_x, start_y, width, height, bgColor, textColor, "Lich Su", isCenter);
}

void header()
{
	ShowCur(0);
	int start_x = 1;
	int start_y = 1;
	int width = 8;
	int height = 2;
	int space = 1;
	bool isCenter = true;

	int widthElement[6] = {width, width, width + 1, width + 55, width + 4, width + 4};
	positionX[0] = start_x;
	for (int i = 1; i < 6; i++)
	{
		positionX[i] = positionX[i - 1] + widthElement[i - 1] + space;
	}

	box(positionX[0], start_y, widthElement[0], height, 11, 15, "<", isCenter);
	box(positionX[1], start_y, widthElement[1], height, 1, textColor, ">", isCenter);
	box(positionX[2], start_y, widthElement[2], height, 1, textColor, "Home", isCenter);
	box(positionX[3], start_y, widthElement[3], height, 1, textColor, "myhomepage.com", isCenter);
	box(positionX[4], start_y, widthElement[4], height, 1, textColor, "Search", isCenter);
	box(positionX[5], start_y, widthElement[5], height, 1, textColor, "Option", isCenter);

	highline(start_x, start_y, width, height, bgColor, textColor, "<", isCenter);
}

void box(int x, int y, int width, int height, int b_color, int t_color, string text, bool isCenter)
{
	textcolor(b_color);
	for (int iy = y + 1; iy <= y + height - 1; iy++)
	{
		for (int ix = x + 1; ix <= x + width - 1; ix++)
		{
			gotoXY(ix, iy);
			cout << " ";
		}
	}
	if (isCenter)
	{
		int position = width / 2 + x - text.length() / 2;
		gotoXY(text.length() % 2 != 1 ? position + 1 : position, height / 2 + y);
		SetColor(t_color);
		cout << text;
	}
	else
	{
		gotoXY(x + 1, y + 1);
		SetColor(t_color);
		cout << text;
	}

	textcolor(1);
	SetColor(outlinecolor);
	if (width < 1 || height < 1)
		return;

	for (int i = x; i < x + width; i++)
	{
		gotoXY(i, y);
		cout << char(196);
		gotoXY(i, y + height);
		cout << char(196);
	}
	for (int j = y; j <= y + height; j++)
	{
		gotoXY(x, j);
		cout << char(179);
		gotoXY(x + width, j);
		cout << char(179);
	}
	gotoXY(x, y);
	cout << char(218);
	gotoXY(x + width, y);
	cout << char(191);
	gotoXY(x, y + height);
	cout << char(192);
	gotoXY(x + width, y + height);
	cout << char(217);
}

void n_box(int x, int y, int width, int height, int b_color, int t_color, string text, bool isCenter, int sl)
{
	for (int i = 0; i < sl; i++)
	{
		box(x, y + (i * 2), width, height, b_color, t_color, text, isCenter);
		if (i != 0)
		{
			gotoXY(x, y + (i * 2));
			cout << char(195);
			gotoXY(x + width, y + (i * 2));
			cout << char(180);
		}
	}
}

void highline(int x, int y, int width, int height, int b_color, int t_color, string text, bool isCenter)
{
	textcolor(b_color);
	for (int iy = y + 1; iy <= y + height - 1; iy++)
	{
		for (int ix = x + 1; ix <= x + width - 1; ix++)
		{
			gotoXY(ix, iy);
			cout << " ";
		}
	}
	if (isCenter)
	{
		gotoXY(width / 2 + x - text.length() / 2, height / 2 + y);
		SetColor(t_color);
		cout << text;
	}
	else
	{
		gotoXY(x + 1, y + 1);
		SetColor(t_color);
		cout << text;
	}
}
