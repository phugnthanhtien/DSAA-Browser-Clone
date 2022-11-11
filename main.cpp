#include <iostream>
#include <string>
#include "mylib.h"
#include  "node.h"
#include "docghifile.h"
#include "content.h"
#define MAX 100
#define outlinecolor 11

using namespace std;

// global variable
int positionX[6];
int textColor = 15;
int bgColor = 200;
int highlineColor = 143;
string homeName = "myhomepage.com";
listUrl listHeader;
listUrl listLS;
listUrl listBookMark;
listUrl listSearch;
Node *currentUrl;
Node *currentHeader;

int xT = 30;
int yT = 10;
int t_color = 12;

//Node *currentBookMark;

//ASCII arrow
// up: 72
// down: 80
// left: 75
// right: 77
// space: 32
// enter: 13
// ESC: 27

void initVariable();
void box(Node *header, int b_color, int t_color, bool isCenter);
void n_box(listUrl list, int b_color, int t_color, bool isCenter);
void highline(Node *accumulator, int b_color, int t_color, bool isCenter);
void movePointer(listUrl list, bool isCenter);
void initTab();
void moveHeader();
void initHeader();
void initLichSu();
void initBookMark();
void veLichSu();
void LichSu();
void Header(Node *currentUrl);
void drawBrowser();
void createSearchBar();
void drawTab(string content, int x, int y, bool isFocus);

int main() {
// khoi tao duy nhat 1 lan
	set_console_size(1200, 600);
	initVariable();
	initHeader();

	drawBrowser();
	_getch();
	return 0;
}

void initVariable() {
	createList(listSearch);
	currentUrl = createNode(homeName);
	addTail(listSearch, currentUrl);
}

void drawBrowser() {
	system("cls");
	drawTab(currentUrl->url, 1, 0,true);
	Header(currentUrl);
	ascii_art(currentUrl->url, xT, yT, t_color);
	if(currentUrl->url == homeName) {
		createSearchBar();
	} else {
		moveHeader();
	}
}

void createSearchBar() {
	box(createNode("", 30, 19, 70, 2), 0, 3, false);
	gotoXY(31, 20);
	ShowCur(1);
	string search;
	while(true) {
		if(_kbhit()) {
			char c = _getch();
			if(c == -32) {
				c = _getch();
				if(c == 72) {
					moveHeader();
				}
			} else {
				textcolor(15);
				getline(cin, search);
				if(search != "") {
					addTail(listSearch, createNode(search));
					currentUrl = currentUrl->next;
					drawBrowser();
				}
			}
		}
	}
}

void LichSu() {
	Node *accumulator = listLS.head;
	int i = 0;
	while(accumulator != NULL) {
		box(accumulator, 1, textColor, false);
		if (i != 0) {
			gotoXY(accumulator->x, accumulator->y);
			cout << char(195);
			gotoXY(accumulator->x +accumulator-> w, accumulator->y);
			cout << char(180);
		}
		i++;
		accumulator = accumulator->next;
	}
}

// void veLichSu()
// {
// 	int xLichSu = 1;
// 	int yLichSu = 6;
// 	int widthLichSu = 110;
// 	int heightLichSu = 2;
// 	bool isCenterLichSu = false;

// 	initLichSu();
// 	n_box(listLS, bgColor, textColor, false);
// 	movePointer(listLS, isCenterLichSu);
// }

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
				if(c == 80) {
					highline(accumulator, 1, textColor, isCenter);
					accumulator = accumulator->next;
					highline(accumulator, bgColor, textColor, isCenter);

				} else if(c == 72) {
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

void initLichSu() {
	ShowCur(0);
	int start_x = 1;
	int start_y = 6;
	int width = 101;
	int height = 2;
	docFile(listLS, "url.txt", start_x, start_y, width, height);
	currentUrl = listLS.tail;
}

void initBookMark() {
	ShowCur(0);
	int start_x = 1;
	int start_y = 6;
	int width = 101;
	int height = 2;

	docFile(listBookMark, "bookMark.txt", start_x, start_y, width, height);
}
void initHeader() {
	ShowCur(0);
	int start_x = 1;
	int start_y = 2;
	int width = 8;
	int height = 2;
	int space = 1;
	bool isCenter = true;

	int widthElement[6] = {width, width, width + 1, width + 65, width + 4, width + 4};
	positionX[0] = start_x;
	for (int i = 1; i < 6; i++) {
		positionX[i] = positionX[i - 1] + widthElement[i - 1] + space;
	}
	createList(listHeader);
	addTail(listHeader, createNode("<", positionX[0], start_y, widthElement[0], height));
	addTail(listHeader, createNode(">", positionX[1], start_y, widthElement[1], height));
	addTail(listHeader, createNode("Home", positionX[2], start_y, widthElement[2], height));
	addTail(listHeader, createNode(homeName, positionX[3], start_y, widthElement[3], height));
	addTail(listHeader, createNode("|||\\", positionX[4], start_y, widthElement[4], height));
	addTail(listHeader, createNode("Option", positionX[5], start_y, widthElement[5], height));
	currentHeader = listHeader.head;
}

void Header(Node *currentUrl) {
	Node *accumulator = listHeader.head;
	while(accumulator != NULL) {
		if(accumulator->x == positionX[3]) {
			accumulator->url = currentUrl->url;
		}
		box(accumulator, 1, textColor, true);
		if(accumulator->x == positionX[4] && currentUrl->isBookMark) {
			highline(accumulator, highlineColor, textColor, true);
		}
		accumulator = accumulator->next;
	}
}

void box(Node *header, int b_color, int t_color, bool isCenter) {
	textcolor(b_color);
	for (int iy = header->y + 1; iy <= header->y + header->h - 1; iy++) {
		for (int ix = header->x + 1; ix <= header->x + header->w - 1; ix++) {
			gotoXY(ix, iy);
			cout << " ";
		}
	}

	if (isCenter) {
		int position = header->w / 2 + header->x - header->url.length() / 2;
		gotoXY(header->url.length() % 2 != 1 ? position + 1 : position, header->h / 2 + header->y);
		SetColor(t_color);
		cout << header->url;
	} else {
		gotoXY(header->x + 1, header->y + 1);
		SetColor(t_color);
		cout << header->url;
	}

	textcolor(1);

	SetColor(outlinecolor);

	if (header->w < 1 || header->h < 1)
		return;

	for (int i = header->x; i < header->x + header->w; i++) {
		gotoXY(i, header->y);
		cout << char(196);
		gotoXY(i, header->y + header->h);
		cout << char(196);
	}
	for (int j = header->y; j <= header->y + header->h; j++) {
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

void moveHeader() {
	ShowCur(0);
	listHeader.tail->next = listHeader.head;
	listHeader.head->prev = listHeader.tail;

	Node *accumulator = currentHeader;
	highline(accumulator, bgColor, textColor, true);

	while(true) {
		if(_kbhit()) {
			char c = _getch();
			if(c == -32) {
				c = _getch();
				if(c == 77) {
					// neu la bookmark thi danh dau lai de luc sau highline ko bi ghi de`
					int bg = currentHeader->url == "|||\\" && currentUrl->isBookMark ? highlineColor : 1;
					highline(accumulator, bg, textColor, true);
					accumulator = accumulator->next;
					highline(accumulator, bgColor, textColor, true);
				} else if(c == 75) {
					int bg = currentHeader->url == "|||\\" && currentUrl->isBookMark ? highlineColor : 1; 
					highline(accumulator, bg, textColor, true);
					accumulator = accumulator->prev;
					highline(accumulator, bgColor, textColor, true);
				}
			} else if (c == 13) {
				listHeader.tail->next = NULL;
				listHeader.head->prev = NULL;
				if (accumulator->url == "<") {
					if (currentUrl != listSearch.head) {
						currentUrl = currentUrl->prev;
					} else moveHeader();
				} 
				else if (accumulator->url == ">") {
					if (currentUrl != listSearch.tail) {
						currentUrl = currentUrl->next;
					} else moveHeader();
				} 
				else if (accumulator->url == "Home" && currentUrl->url != homeName) {
					addTail(listSearch, createNode(homeName));
					currentUrl = currentUrl->next;
					ghiUrl("url.txt", currentUrl->url);
				} 
				else if (accumulator->url == currentUrl->url) {
					createSearchBar();
				}
				else if(accumulator->url == "|||\\") {
					currentUrl->isBookMark = !currentUrl->isBookMark;
				}
				drawBrowser();
			}
			currentHeader = accumulator;
		}
	}
}

void n_box(listUrl list, int b_color, int t_color, bool isCenter) {
	Node *accumulator = list.head;
	int i = 0;
	while(accumulator != NULL) {
		box(accumulator, 1, textColor, false);
		if (i != 0) {
			gotoXY(accumulator->x, accumulator->y);
			cout << char(195);
			gotoXY(accumulator->x +accumulator-> w, accumulator->y);
			cout << char(180);
		}
		i++;
		accumulator = accumulator->next;
	}
}

void highline(Node *accumulator, int b_color, int t_color, bool isCenter) {
	textcolor(b_color);
	for (int iy = accumulator->y + 1; iy <= accumulator->y + accumulator->h - 1; iy++) {
		for (int ix = accumulator->x + 1; ix <= accumulator->x + accumulator->w - 1; ix++) {
			gotoXY(ix, iy);
			cout << " ";
		}
	}
	if (isCenter) {
		int position = accumulator->w / 2 + accumulator->x - accumulator->url.length() / 2;
		gotoXY(accumulator->url.length() % 2 != 1 ? position + 1 : position, accumulator->h / 2 + accumulator->y);
		SetColor(t_color);
		cout << accumulator->url;
	} else {
		gotoXY(accumulator->x + 1, accumulator->y + 1);
		SetColor(t_color);
		cout << accumulator->url;
	}
	textcolor(0);
	ShowCur(0);
}

void drawTab(string content, int x = 0, int y = 0, bool isFocus = false) {
	int sizeTab = 15;
	int text = isFocus ? 14 : textColor;
	for(int i=0; i< sizeTab; i++) {
		for(int j = 0; j<2; j++) {
			if(j == 0) {
				textcolor(outlinecolor);
				gotoXY(x + i, y);
				i == sizeTab - 1 ?  cout << " x" : cout << char(196);
			}
			else {
				gotoXY(x + 1, y + j);
				if(content.size() > sizeTab - 5) {
					textcolor(text);
					cout << content.substr(0, sizeTab - 5) + ".. ";
				}
				else {
					textcolor(text);
					cout << content << string(sizeTab - content.size() - 2, ' ');
				}
				textcolor(outlinecolor);
				cout << char(47);
			}
		}
	}
}
