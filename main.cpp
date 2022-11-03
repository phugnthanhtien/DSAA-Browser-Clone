#include <iostream>
#include <string>
#include "mylib.h"
#define MAX 100
#define outlinecolor 11

using namespace std;

void box(int x, int y, int width, int height, int b_color, int t_color, string text, bool isCenter);
void n_box(int x, int y, int width, int height, int b_color, int t_color, string text, bool isCenter,int sl);
void highline(int x,int y,int w,int h,int b_color,int t_color, string text, bool isCenter);
void header();
void menu();

int main() {
	
	header();
	menu();

	_getch();
	return 0;
}


void menu() {
	
	ShowCur(0);
	int start_x = 20;
	int start_y = 10;
	int width = 12;
	int height = 2;
	int textColor = 15;
	int bgColor = 200;
	bool isCenter = false;
	int sl = 5;
	
	n_box(start_x, start_y, width, height, 1, textColor, "hello", isCenter, sl);
	highline(start_x, start_y, width, height, bgColor, textColor, "hello", isCenter);
	
	int xp = start_x;int yp = start_y;//t?a d? thanh s�ng
	int xcu = xp;int ycu = yp;
	bool kt = true;
	while (true)
	{
		//------ in ----
		if (kt == true)
		{
			//----- back space ----
			gotoXY(xcu, ycu);
			highline(xcu, ycu, width, height, bgColor, textColor, "hello", isCenter);//rs thanh sang cu
			xcu = xp;ycu = yp;
			//-------------
			highline(xp, yp, width, height, bgColor, textColor, "hello", isCenter);
			kt = false;
		}
		//----- dieu khien ---- //----- di chuyen ----
		if (_kbhit())
		{
			char c = _getch();
			if (c == -32)
			{
				kt = true; // flag 
				c = _getch();
				if (c == 72)
				{
					if(yp != start_y)yp -= 2;
					else
					{
						yp = start_y + height*(sl - 1);
					}
				}
				else if (c == 80 )
				{
					if(yp != start_y + height*(sl - 1))yp += 2;
					else
					{
						yp = start_y;
					}
				}
			}
		}
	}
}

void header() {
	int start_x = 1;
	int start_y = 1;
	int width = 8;
	int height = 2;
	int space = 2;
	int textColor = 15;
	int bgColor = 200;
	bool isCenter = true;

	
	box(start_x, start_y, width, height, 11, 15, "<", isCenter);
	box(start_x + width + space, start_y, width, height, 1, textColor, ">", isCenter);
	box((start_x + width)*2 + space, start_y, width + 1, height, 1, textColor, "Home", isCenter);
	box((start_x + width)*3 + 1 + space, start_y, width + 50, height , 1, textColor, "myhomepage.com", isCenter);
	box((start_x + width)*4 + 1 + 50 + space, start_y, width + 4, height , 1, textColor, "Search", isCenter);
	box((start_x + width)*5 + 4 + 1 + 50 + space, start_y, width + 4, height , 1, textColor, "Option", isCenter);
	
	highline(start_x, start_y, width, height, bgColor, textColor, "<", isCenter);
	
}

void box(int x, int y, int width, int height, int b_color, int t_color, string text, bool isCenter) {
	textcolor(b_color);
	for (int iy = y+1;iy <= y + height-1;iy++)
	{
		for (int ix = x+1;ix <= x + width-1;ix++)
		{
			gotoXY(ix, iy); cout << " ";
		}
	}
	if(isCenter)
		{
		int position = width/2 + x - text.length()/2;
		gotoXY( text.length() % 2 != 1 ? position + 1 : position, height/2 + y); SetColor(t_color); cout << text;}
	else
		{gotoXY(x + 1, y + 1); SetColor(t_color); cout << text;}
	
	textcolor(1);
	SetColor(outlinecolor);
	if(width < 1 || height < 1) return;
	
	for(int i = x; i< x + width; i++) {
		gotoXY(i, y);
		cout << char(196);
		gotoXY(i, y+height);
		cout << char(196);
	}
	for(int j = y; j <= y+height; j++) {
		gotoXY(x, j);
		cout << char(179);
		gotoXY(x + width, j);
		cout << char(179);
	}
	gotoXY(x, y); cout << char(218);
	gotoXY(x + width, y); cout << char(191);
	gotoXY(x , y + height); cout << char(192);
	gotoXY(x + width, y + height); cout << char(217);
	
}

void n_box(int x, int y, int width, int height, int b_color, int t_color, string text, bool isCenter, int sl)
{
	for (int i = 0;i < sl;i++)
	{
		box(x, y + (i * 2), width, height, b_color, t_color, text, isCenter);
		if (i != 0)
		{
			gotoXY(x, y + (i * 2));cout << char(195);
			gotoXY(x + width, y + (i * 2));cout << char(180);
		}
	}
}

void highline(int x,int y,int width,int height,int b_color, int t_color, string text, bool isCenter)
{
	textcolor(b_color);
	for (int iy = y + 1; iy <= y + height - 1; iy++)
	{
		for (int ix = x + 1; ix <= x + width - 1; ix++)
		{
			gotoXY(ix, iy); cout << " ";
		}
	}
	if(isCenter)
		{gotoXY(width/2 + x - text.length()/2 , height/2 + y); SetColor(t_color); cout << text;}
	else
		{gotoXY(x + 1, y + 1); SetColor(t_color); cout << text;}
}
