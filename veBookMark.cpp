#include <iostream>
#include <string>
#include "mylib.h"
#include "node.h"
#include "docghifile.h"
#define outlinecolor 11
#define MAX 100
using namespace std;
listUrl listBookMark;
Node *currentBookMark;
int textColor = 15;
int bgColor = 200;
void initBookMark();
void box(Node *header, int b_color, int t_color, bool isCenter);
void n_box(listUrl list, int b_color, int t_color, bool isCenter);
void highline(Node *accumulator, int b_color, int t_color, bool isCenter);
void movePointer(listUrl list, bool isCenter);
int main()
{
    initBookMark();
    n_box(listBookMark, bgColor, textColor, false);
	movePointer(listBookMark, false);
    _getch();
    return 0;
}

void box(Node *header, int b_color, int t_color, bool isCenter)
{
    	// set background
	textcolor(b_color);
	for (int iy = header->y + 1; iy <= header->y + header->h - 1; iy++)
	{
		for (int ix = header->x + 1; ix <= header->x + header->w - 1; ix++)
		{
			gotoXY(ix, iy);
			cout << " ";
		}
	}

	// kiểm tra xem có muốn để chữ ở giữa khung không
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

	textcolor(1); // bỏ tô màu viền
	
	// tô màu khung
	SetColor(outlinecolor);

	// nếu chiều rộng hoặc chiều dài ko tồn tại -> ko vẽ
	if (header->w < 1 || header->h < 1)
		return;

	// vẽ khung
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

void n_box(listUrl list, int b_color, int t_color, bool isCenter)
{
	Node *accumulator = list.head;
	int i = 0;
	while(accumulator != NULL) {
		box(accumulator, 1, textColor, false);
		if (i != 0)
		{
			gotoXY(accumulator->x, accumulator->y);cout << char(195);
			gotoXY(accumulator->x +accumulator-> w, accumulator->y);cout << char(180);
		}
		i++;
		accumulator = accumulator->next;
	}
}
// file bookMark.text không khởi tạo giá trị sẵn
// xử lí ở main rồi ghi gtri vào file bookMark.text
void initBookMark()
{
	ShowCur(0);
	int start_x = 1;
	int start_y = 6;
	int width = 101;
	int height = 2;

	docFile(listBookMark, "bookMark.txt", start_x, start_y, width, height);
	currentBookMark = listBookMark.head;
}

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
void movePointer(listUrl list, bool isCenter) {
	ShowCur(0);
	list.tail->next = list.head;
	list.head->prev = list.tail;

	Node *accumulator = list.head;
	highline(accumulator, bgColor, textColor, isCenter);

	while(true) {
		if(_kbhit()) {
			char c = _getch();
			if(c == -32) {
				c = _getch();
				if(c == 80){
					highline(accumulator, 1, textColor, isCenter);
					accumulator = accumulator->next;
					highline(accumulator, bgColor, textColor, isCenter);

				}
				else if(c == 72) {
					highline(accumulator, 1, textColor, isCenter);
					if(accumulator == list.head) moveHeader();
					else {
						accumulator = accumulator->prev;
						highline(accumulator, bgColor, textColor, isCenter);
					}
				}
			}
		}
	}
	list.tail->next = NULL;
	list.head->prev = NULL;
}
