#include <iostream>
#include <string>
#include "mylib.h"
#include  "deletenode.h"
#define MAX 100
#define outlinecolor 11

using namespace std;

// global variable 
int positionX[6];
int textColor = 15;
int bgColor = 200;
listUrl listHeader;

//ASCII arrow
// up: 72
// down: 80
// left: 75
// right: 77
// space: 32
// enter: 13
// ESC: 27 

void box(Node *header, int b_color, int t_color, bool isCenter);
void n_box(int x, int y, int width, int height, int b_color, int t_color, string text, bool isCenter, int sl);
void highline(Node *accumulator, int b_color, int t_color, bool isCenter);
void movePointer(int start_x, int start_y, int width, int height, bool isCenter);
void moveHeader();
void initHeader();
void listLichSu();
void veLichSu();
void Header();

int main()
{
	set_console_size(1000, 600);
	
	initHeader();
	Header();
	moveHeader();
	//  veLichSu();

	 _getch();
	return 0;
}

//not done
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



	initHeader();
	Header();
	listLichSu();

	int start_x = xLichSu, start_y = yLichSu;
	int width = widthLichSu, height = heightLichSu;
	bool isCenter = isCenterLichSu;

//	movePointer(start_x, start_y, width, height, isCenter);
}

// not done
// void movePointer(int start_x, int start_y, int width, int height, bool isCenter)
// {
// 	ShowCur(0);
// 	int sl = 5;
// 	int xp = start_x;
// 	int yp = start_y;
// 	int xcu = xp;
// 	int ycu = yp;
// 	bool check = true;
// 	while (true)
// 	{
// 		if (check == true)
// 		{
// 			gotoXY(xcu, ycu);
// 			highline(xcu, ycu, width, height, 1, textColor, "Lich Su", isCenter); // rs thanh sang cu
// 			xcu = xp;
// 			ycu = yp;
// 			highline(xp, yp, width, height, bgColor, textColor, "Lich Su", isCenter);
// 			check = false;
// 		}
// 		if (_kbhit())
// 		{
// 			char c = _getch();
// 			if (c == -32)
// 			{
// 				check = true; // flag
// 				c = _getch();
// 				if (c == 75)
// 				{
// 					if (yp != start_y)
// 						yp -= 2;
// 					else
// 					{
// 						yp = start_y + height * (sl - 1);
// 					}
// 				}
// 				else if (c == 77)
// 				{
// 					if (yp != start_y + height * (sl - 1))
// 						yp += 2;
// 					else
// 					{
// 						yp = start_y;
// 					}
// 				}
// 			}
// 		}
// 	}
// }


//not done
void listLichSu()
{
	int start_x = 1;
	int start_y = 6;
	int width = 100;
	int height = 2;
	bool isCenter = false;
	int sl = 5;

//	n_box(start_x, start_y, width, height, 1, textColor, "Lich Su", isCenter, sl);
//	highline(start_x, start_y, width, height, bgColor, textColor, "Lich Su", isCenter);
}

//done
void initHeader()
{
	ShowCur(0);
	int start_x = 1;
	int start_y = 1;
	int width = 8;
	int height = 2;
	int space = 1;
	bool isCenter = true;

	int widthElement[6] = {width, width, width + 1, width + 65, width + 4, width + 4};
	positionX[0] = start_x;
	for (int i = 1; i < 6; i++)
	{
		positionX[i] = positionX[i - 1] + widthElement[i - 1] + space;
	}
	createList(listHeader);
	addTail(listHeader, createNode("<", positionX[0], start_y, widthElement[0], height));
	addTail(listHeader, createNode(">", positionX[1], start_y, widthElement[1], height));
	addTail(listHeader, createNode("Home", positionX[2], start_y, widthElement[2], height));
	addTail(listHeader, createNode("myhomepage.com", positionX[3], start_y, widthElement[3], height));
	addTail(listHeader, createNode("Search", positionX[4], start_y, widthElement[4], height));
	addTail(listHeader, createNode("Option", positionX[5], start_y, widthElement[5], height));
}

//done
void Header() {
	Node *accumulator = listHeader.head;
	while(accumulator != NULL) {
		box(accumulator, 1, textColor, true);
		accumulator = accumulator->next;
	}	
}

void box(Node *header, int b_color, int t_color, bool isCenter)
{
	textcolor(b_color);
	for (int iy = header->y + 1; iy <= header->y + header->h - 1; iy++)
	{
		for (int ix = header->x + 1; ix <= header->x + header->w - 1; ix++)
		{
			gotoXY(ix, iy);
			cout << " ";
		}
	}
	if (isCenter)
	{
		int position = header->w / 2 + header->x - header->url.length() / 2;
		gotoXY(header->url.length() % 2 != 1 ? position + 1 : position, header->h / 2 + header->y);
		SetColor(t_color);
		cout << header->url;
	}
	else
	{
		gotoXY(header->x + 1, header->y + 1);
		SetColor(t_color);
		cout << header->url;
	}

	textcolor(1);
	SetColor(outlinecolor);
	if (header->w < 1 || header->h < 1)
		return;

	for (int i = header->x; i < header->x + header->w; i++)
	{
		gotoXY(i, header->y);
		cout << char(196);
		gotoXY(i, header->y + header->h);
		cout << char(196);
	}
	for (int j = header->y; j <= header->y + header->h; j++)
	{
		gotoXY(header->x, j);
		cout << char(179);
		gotoXY(header->x + header->w, j);
		cout << char(179);
	}
	gotoXY(header->x, header->y);
	cout << char(218);
	gotoXY(header->x + header->w, header->y);
	cout << char(191);
	gotoXY(header->x, header->y + header->h);
	cout << char(192);
	gotoXY(header->x + header->w, header->y + header->h);
	cout << char(217);
}

// done
void moveHeader() {
	ShowCur(0);
	listHeader.tail->next = listHeader.head;
	listHeader.head->prev = listHeader.tail;

	Node *accumulator = listHeader.head;
	highline(accumulator, bgColor, textColor, true);

	while(true) {
		if(_kbhit()) {
			char c = _getch();
			if(c == -32) {
				c = _getch();
				if(c == 77){
					highline(accumulator, 1, textColor, true);
					accumulator = accumulator->next;
					highline(accumulator, bgColor, textColor, true);

				}
				else if(c == 75) {
					highline(accumulator, 1, textColor, true);
					accumulator = accumulator->prev;
					highline(accumulator, bgColor, textColor, true);
				}
			}
		}
	}
	listHeader.tail->next = NULL;
	listHeader.head->prev = NULL;
}

// not done
void n_box(listUrl list, int b_color, int t_color, bool isCenter)
{
	Node * accumulator = list.head;
	int i = 0;
	while(accumulator != NULL)
	{
		box(accumulator, 1, t_color, false);
		if (i != 0)
		{
			gotoXY(accumulator->x, accumulator->y + (i * 2));
			cout << char(195);
			gotoXY(accumulator->x + accumulator->w, accumulator->y + (i * 2));
			cout << char(180);
		}
	}
}

//done
void highline(Node *accumulator, int b_color, int t_color, bool isCenter)
{
	textcolor(b_color);
	for (int iy = accumulator->y + 1; iy <= accumulator->y + accumulator->h - 1; iy++)
	{
		for (int ix = accumulator->x + 1; ix <= accumulator->x + accumulator->w - 1; ix++)
		{
			gotoXY(ix, iy);
			cout << " ";
		}
	}
	if (isCenter)
	{
		int position = accumulator->w / 2 + accumulator->x - accumulator->url.length() / 2;
		gotoXY(accumulator->url.length() % 2 != 1 ? position + 1 : position, accumulator->h / 2 + accumulator->y);
		SetColor(t_color);
		cout << accumulator->url;
	}
	else
	{
		gotoXY(accumulator->x + 1, accumulator->y + 1);
		SetColor(t_color);
		cout << accumulator->url;
	}
}
