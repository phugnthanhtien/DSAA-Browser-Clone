#include <iostream>
#include <string>
#include "mylib.h"
#include  "node.h"
#include "docghifile.h"
#define MAX 100
#define outlinecolor 11

using namespace std;

// global variable 
int positionX[6];
int textColor = 15;
int bgColor = 200;
listUrl listHeader;
listUrl listLS;

//ASCII arrow
// up: 72
// down: 80
// left: 75
// right: 77
// space: 32
// enter: 13
// ESC: 27 

void box(Node *header, int b_color, int t_color, bool isCenter);
void n_box(listUrl list, int b_color, int t_color, bool isCenter);
void highline(Node *accumulator, int b_color, int t_color, bool isCenter);
void movePointer(int start_x, int start_y, int width, int height, bool isCenter);
void moveHeader();
void initHeader();
void listLichSu();
void veLichSu();
void LichSu();
void Header();

int main()
{
	set_console_size(1000, 600);
	
	initHeader();
	Header();
	// moveHeader();

	veLichSu();

	 _getch();
	return 0;
}

void LichSu() {
	Node *accumulator = listLS.head;
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
//not done
void veLichSu()
{

	// lichsu
	int xLichSu = 1;
	int yLichSu = 6;
	int widthLichSu = 110;
	int heightLichSu = 2;
	bool isCenterLichSu = false;

	listLichSu();
	// LichSu();
	n_box(listLS, bgColor, textColor, false);

	int start_x = xLichSu, start_y = yLichSu;
	int width = widthLichSu, height = heightLichSu;
	bool isCenter = isCenterLichSu;

	movePointer(start_x, start_y, width, height, isCenterLichSu);
}

// not done
void movePointer(int start_x, int start_y, int width, int height, bool isCenter) {
	ShowCur(0);
	listLS.tail->next = listLS.head;
	listLS.head->prev = listLS.tail;

	Node *accumulator = listLS.head;
	highline(accumulator, bgColor, textColor, true);

	while(true) {
		if(_kbhit()) {
			char c = _getch();
			if(c == -32) {
				c = _getch();
				if(c == 80){
					highline(accumulator, 1, textColor, true);
					accumulator = accumulator->next;
					highline(accumulator, bgColor, textColor, true);

				}
				else if(c == 72) {
					highline(accumulator, 1, textColor, true);
					accumulator = accumulator->prev;
					highline(accumulator, bgColor, textColor, true);
				}
			}
		}
	}
	listLS.tail->next = NULL;
	listLS.head->prev = NULL;
}


//not done
void listLichSu()
{
	ShowCur(0);
	int start_x = 1;
	int start_y = 6;
	int width = 101;
	int height = 2;
	bool isCenter = false;
	int sl = 5;

	docFile(listLS, "url.txt", start_x, start_y, width, height);   //note
	//n_box(start_x, start_y, width, height, 1, textColor, "Lich Su", isCenter, sl);
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

// done
void moveHeader() {
	ShowCur(0);
	// chuyển thành danh sách vòng để khi người dùng di chuyển con trỏ
	// tới cuối sẽ đi trở về đầu hoặc ngược lại
	listHeader.tail->next = listHeader.head;
	listHeader.head->prev = listHeader.tail;

	Node *accumulator = listHeader.head;
	highline(accumulator, bgColor, textColor, true);

	while(true) {
		if(_kbhit()) {
			char c = _getch();
			// kiểm tra xem người dùng nhấn phím mũi tên
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

// done
// làm giống header 
// hàm này dùng chung cho listLS vàlistBookMark
void n_box(listUrl list, int b_color, int t_color, bool isCenter)
{
	Node *accumulator = listLS.head;
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
