#include <iostream>
#include <string>
#include <cstdlib>
#include "mylib.h"
#include "Tab.h"
#include "docghifile.h"
#include "content.h"
#include "vebackground.h"
#include "FNode.h"
#define MAX 100
#define outlinecolor 11

using namespace std;

// global variable
int positionX[7];
int textColor = 15;
int bgColor = 200;
int highlineColor = 143;
bool viewHistory = false, viewBookMark = false, viewFavorite = false;
string homeName = "myhomepage.com";
listUrl listLS;
listUrl listBookMark;
LTab listTab;
Tab *currentTab;
Node *temp_Delete = NULL;
Node *temp_Delete_url = NULL;
Node *tempNodeDele_FV = NULL;
int flag = 2;
FNode *tempListDele_FV = NULL;
FNode *tempFNodeDele_FV = NULL;
FNode *root = createFNode("ROOT");
FNode*currentFolder = root;
int xT = 40;
int yT = 10;
int t_color = 12;

// Node *currentBookMark;

// ASCII arrow
//  up: 72
//  down: 80
//  left: 75
//  right: 77
//  space: 32
//  enter: 13
//  ESC: 27

void initVariable();
void initHeader(listUrl &listHeader);
void initViewList(listUrl &list);
void initTab();

template <typename T>
void assignValue(T *node, int x, int y, int w, int h);

void Exit();

template <typename T>
void box(T *header, int b_color, int t_color, bool isCenter);
void n_box(listUrl list, int b_color, int t_color, bool isCenter);
template <typename T>
void highline(T *accumulator, int b_color, int t_color, bool isCenter);

void createSearchBar(listUrl &listSearch, listUrl &listHeader);
void Header(listUrl &listHeader);

void drawList(listUrl list);
void drawHeaderAndTab();
void drawBrowser();
void drawSquareTab(string content, int x, int y, bool isFocus);
void drawOption(listUrl &listHeader);
void drawListTab();
void drawDeleLS(listUrl &listLS, string key, int t);
void drawFolder(FNode *current);
void drawFavorite(FNode *current);

void movePointer(listUrl &list, listUrl &listHeader, bool isCenter);
template <typename T>
void moveHeader(T *accumulator, listUrl &listHeader);
void moveTab();
void moveLFUrl(FNode *current, bool isHead);
void moveLFNode(FNode *current);
void moveFavorite(FNode *current);
void drawInputButton(FNode *current);

int main()
{
	// khoi tao duy nhat 1 lan
	set_console_size(2000, 1000);
	initVariable();
	initTab();

	drawBrowser();
	//	viewFavorite = true;  -> debug cho de~
	//	drawFavorite(root);

	_getch();
	return 0;
}

void initVariable()
{
	createList(listBookMark);
	createList(listLS);
	docFile(listBookMark, "bookMark.txt");
	docFile(listLS, "url.txt");
	initListTab(listTab);
	initFolder(root);
}

void initTab()
{
	// Header
	listUrl listHeader;
	createList(listHeader);
	initHeader(listHeader);

	// listSearch
	listUrl listSearch;
	createList(listSearch);
	addTail(listSearch, createNode(homeName));

	// init new Tab with new listUrl
	addTab(listTab, createTab(listSearch, listHeader));
	currentTab = listTab.tail;
}

void drawListTab()
{
	Tab *accumulator = listTab.head;
	int x = 1, y = 0, space = 18;
	while (accumulator != NULL)
	{
		bool isCurrent = accumulator == currentTab ? true : false;
		accumulator->square.x = x;
		accumulator->square.y = y;
		drawSquareTab(accumulator->currentUrl->url, accumulator->square.x, accumulator->square.y, isCurrent);
		x += space;
		accumulator = accumulator->next;
	}
}

void moveTab()
{
	listTab.tail->next = listTab.head;
	listTab.head->prev = listTab.tail;
	drawSquareTab(currentTab->currentUrl->url, currentTab->square.x, currentTab->square.y, true);
	while (true)
	{
		if (_kbhit())
		{
			char c = _getch();
			if (c == -32)
			{
				c = _getch();
				if (c == 77)
				{
					drawSquareTab(currentTab->currentUrl->url, currentTab->square.x, currentTab->square.y, false);
					currentTab = currentTab->next;
					drawSquareTab(currentTab->currentUrl->url, currentTab->square.x, currentTab->square.y, true);
				}
				else if (c == 75)
				{
					drawSquareTab(currentTab->currentUrl->url, currentTab->square.x, currentTab->square.y, false);
					currentTab = currentTab->prev;
					drawSquareTab(currentTab->currentUrl->url, currentTab->square.x, currentTab->square.y, true);
				}
				else if (c == 80)
				{
					listTab.tail->next = NULL;
					listTab.head->prev = NULL;
					moveHeader(currentTab->listUrl.head, currentTab->listHeader);
				}
			}
			else if (c == 8)
			{
				listTab.tail->next = NULL;
				listTab.head->prev = NULL;
				Tab *temp;
				if (currentTab == listTab.tail)
					temp = currentTab->prev;
				else
					temp = currentTab->next;
				deleteTab(listTab, currentTab);
				currentTab = temp;
				if(!currentTab) Exit();
				drawSquareTab(currentTab->currentUrl->url, currentTab->square.x, currentTab->square.y, true);
				drawBrowser();
			}
			else if (c == 13)
			{
				listTab.tail->next = NULL;
				listTab.head->prev = NULL;
				drawBrowser();
			}
		}
	}
}

void drawHeaderAndTab()
{
	system("cls");
	drawListTab();
	Header(currentTab->listHeader);
}

void drawBrowser()
{
	drawHeaderAndTab();
	if (viewHistory)
	{
		drawList(listLS);
		movePointer(listLS, currentTab->listHeader, false);
	}
	else if (viewBookMark)
	{
		drawList(listBookMark);
		movePointer(listBookMark, currentTab->listHeader, false);
	}
	else if (viewFavorite)
	{
		drawFavorite(root);
	}
	if (currentTab->currentHeader->url == "Option")
	{
		drawOption(currentTab->listHeader);
	}
	else 
	{
		ascii_art(currentTab->currentUrl->url, xT, yT, t_color);
		if (currentTab->currentUrl->url == homeName)
		{
			//			drawBR();  -> debug cho de
		}
		if (currentTab->currentUrl->url == homeName || currentTab->currentHeader->x == positionX[3])
		{
			createSearchBar(currentTab->listUrl, currentTab->listHeader);
		}
		else
		{
			moveHeader(currentTab->listUrl.head, currentTab->listHeader);
		}
	}
}

void createSearchBar(listUrl &listSearch, listUrl &listHeader)
{
	box(createNode("", "", 42, 19, 50, 2), 0, 3, false);
	gotoXY(43, 20);
	ShowCur(1);
	string search;
	while (true)
	{
		if (_kbhit())
		{
			char c = _getch();
			if (c == -32)
			{
				c = _getch();
				if (c == 72)
				{
					moveHeader(currentTab->listUrl.head, listHeader);
				}
			}
			else
			{
				textcolor(15);
				getline(cin, search);
				if (search != "")
				{
					addAfter(listSearch, createNode(search), currentTab->currentUrl);
					addTail(listLS, createNode(search));
					currentTab->currentUrl = currentTab->currentUrl->next;
					drawBrowser();
				}
			}
		}
	}
}

void drawList(listUrl list)
{
	if (list.head != NULL)
	{
		textcolor(11);
		gotoXY(15, 6);
		cout << "XOA 1 DIA CHI LICH SU/BOOKMARK: NHAN PHIM BACKSPACE" << endl;
		gotoXY(15, 7);
		cout << "XOA TOAN BO LICH SU/BOOKMARK: NHAN PHIM DELETE" << endl;
		gotoXY(15, 8);
		cout << "XOA LICH SU TRONG MOT NGAY: NHAN PHIM SPACE" << endl;
		Node *accumulator = list.head;
		int i = 0;
		int x = 1, y = 10, w = 101, h = 2;
		gotoXY(0, 9);
		cout << list.head->dmy;
		string cur_dmy = list.head->dmy;
		while (accumulator != NULL)
		{
			if (accumulator->dmy != cur_dmy)
			{
				gotoXY(3, y + i * 2);
				cout << endl
					 << accumulator->dmy << endl
					 << endl;
				cur_dmy = accumulator->dmy;
				i += 1;
			}
			accumulator->x = x;
			accumulator->y = y + (i * 2);
			accumulator->w = w;
			accumulator->h = h;
			box(accumulator, 1, textColor, false);
			if (i != 0 && accumulator->prev->dmy == cur_dmy)
			{
				gotoXY(accumulator->x, accumulator->y);
				cout << char(195);
				gotoXY(accumulator->x + accumulator->w, accumulator->y);
				cout << char(180);
			}
			i++;
			accumulator = accumulator->next;
		}
	}
}

void movePointer(listUrl &list, listUrl &listHeader, bool isCenter)
{
	ShowCur(0);
	if (list.head != NULL)
	{
		list.tail->next = list.head;
		list.head->prev = list.tail;
		Node *accumulator = list.head;
		highline(accumulator, bgColor, textColor, isCenter);

		while (true)
		{
			if (_kbhit())
			{
				char c = _getch();
				if (c == -32)
				{
					c = _getch();
					if (c == 80)
					{
						highline(accumulator, 1, textColor, isCenter);
						accumulator = accumulator->next;
						highline(accumulator, bgColor, textColor, isCenter);
					}
					else if (c == 72)
					{
						highline(accumulator, 1, textColor, isCenter);
						if (accumulator == list.head)
						{
							list.tail->next = NULL;
							list.head->prev = NULL;
							moveHeader(currentTab->listUrl.head, listHeader);
						}
						else
						{
							accumulator = accumulator->prev;
							highline(accumulator, bgColor, textColor, isCenter);
						}
					}
					else if (c == 83)
					{
						list.tail->next = NULL;
						list.head->prev = NULL;
						if (viewHistory)
						{
							drawDeleLS(listLS, accumulator->url, 2);
						}
						else if (viewBookMark)
						{
							drawDeleLS(listBookMark, accumulator->url, 2);
						}
					}
				}
				else if (c == 8)
				{
					list.tail->next = NULL;
					list.head->prev = NULL;
					if (viewHistory)
					{
						temp_Delete_url = accumulator;
						drawDeleLS(listLS, accumulator->url, 0);
					}
					else if (viewBookMark)
					{
						temp_Delete_url = accumulator;
						drawDeleLS(listBookMark, accumulator->url, 0);
					}
				}
				else if (c == 13)
				{
					if (accumulator->url == "Yes")
					{
						if (viewHistory)
						{
							if (temp_Delete != NULL)
							{
								removeCondiNode(listLS, temp_Delete->dmy);
								temp_Delete = NULL;
								drawBrowser();
							}
							else if (temp_Delete_url != NULL)
							{
								removeNode(listLS, temp_Delete_url);
								temp_Delete_url = NULL;
								drawBrowser();
							}
							else
							{
								removeAllNode(listLS);
								drawBrowser();
							}
						}
						else if(viewBookMark)
						{
							if (temp_Delete_url != NULL)
							{
								removeNode(listBookMark, temp_Delete_url);
								temp_Delete_url = NULL;
								drawBrowser();
							}
							else
							{
								removeAllNode(listBookMark);
								drawBrowser();
							}
						}
						else if(viewFavorite)
						{
							if (flag == 1)
							{
								removeNode(tempListDele_FV->LUrl,tempNodeDele_FV);
							}
							else if (flag == 0)
							{
								findAndDeleteFN(tempListDele_FV,tempFNodeDele_FV);
							}
							drawHeaderAndTab();
							drawFavorite(tempListDele_FV);
						}
					}
					else if (accumulator->url == "No")
					{
						drawBrowser();
					}
					else if (accumulator->url == "View History")
					{
						viewHistory = true;
						viewBookMark = false;
						viewFavorite = false;
					}
					else if (accumulator->url == "View BookMark")
					{
						viewBookMark = true;
						viewHistory = false;
						viewFavorite = false;
					}
					else if (accumulator->url == "View your Favorite")
					{
						viewFavorite = true;
						viewHistory = false;
						viewBookMark = false;
					}
					else if (accumulator->url == "Open new tab")
					{
						initTab();
					}
					else
					{
						if(viewHistory || viewBookMark)
						{
							addAfter(currentTab->listUrl, createNode(accumulator->url), currentTab->currentUrl);
							addTail(listLS, createNode(accumulator->url));
							currentTab->currentUrl = currentTab->currentUrl->next;
							currentTab->currentHeader = currentTab->listHeader.head;
							if (viewHistory) 
								viewHistory = false;
							else viewBookMark = false;
							drawBrowser();
						}
					}
					drawBrowser();
				}
				else if (c == 32)
				{
					list.tail->next = NULL;
					list.head->prev = NULL;
					if (viewHistory)
					{
						temp_Delete = accumulator;
						drawDeleLS(listLS, accumulator->dmy, 1);
					}
				}
			}
		}
	}
}

void initHeader(listUrl &listHeader)
{
	ShowCur(0);
	int start_x = 1;
	int start_y = 2;
	int width = 8;
	int height = 2;
	int space = 1;
	bool isCenter = true;

	int widthElement[7] = {width, width, width + 1, width + 65, width + 4, width + 4, width};
	positionX[0] = start_x;
	for (int i = 1; i < 7; i++)
	{
		positionX[i] = positionX[i - 1] + widthElement[i - 1] + space;
	}
	createList(listHeader);
	addTail(listHeader, createNode("<", "", positionX[0], start_y, widthElement[0], height));
	addTail(listHeader, createNode(">", "", positionX[1], start_y, widthElement[1], height));
	addTail(listHeader, createNode("Home", "", positionX[2], start_y, widthElement[2], height));
	addTail(listHeader, createNode(homeName, "", positionX[3], start_y, widthElement[3], height));
	addTail(listHeader, createNode("|||\\", "", positionX[4], start_y, widthElement[4], height));
	addTail(listHeader, createNode("Option", "", positionX[5], start_y, widthElement[5], height));
	addTail(listHeader, createNode("X", "", positionX[6], start_y, widthElement[6], height));
}

void Header(listUrl &listHeader)
{
	Node *accumulator = listHeader.head;
	while (accumulator != NULL)
	{
		if (accumulator->x == positionX[3])
		{
			accumulator->url = currentTab->currentUrl->url;
		}
		box(accumulator, 1, textColor, true);
		if (accumulator->x == positionX[4] && currentTab->currentUrl->isBookMark)
		{
			highline(accumulator, highlineColor, textColor, true);
		}
		accumulator = accumulator->next;
	}
}

template <typename T>
void box(T *header, int b_color, int t_color, bool isCenter)
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

template <typename T>
void moveHeader(T *accumulator, listUrl &listHeader)
{
	ShowCur(0);
	listHeader.tail->next = listHeader.head;
	listHeader.head->prev = listHeader.tail;

	accumulator = currentTab->currentHeader;
	highline(accumulator, bgColor, textColor, true);

	while (true)
	{
		if (_kbhit())
		{
			char c = _getch();
			if (c == -32)
			{
				c = _getch();
				if (c == 77)
				{
					// neu la bookmark thi danh dau lai de luc sau highline ko bi ghi de`
					int bg = currentTab->currentHeader->url == "|||\\" && currentTab->currentUrl->isBookMark ? highlineColor : 1;
					highline(accumulator, bg, textColor, true);
					accumulator = accumulator->next;
					highline(accumulator, bgColor, textColor, true);
				}
				else if (c == 75)
				{
					int bg = currentTab->currentHeader->url == "|||\\" && currentTab->currentUrl->isBookMark ? highlineColor : 1;
					highline(accumulator, bg, textColor, true);
					accumulator = accumulator->prev;
					highline(accumulator, bgColor, textColor, true);
				}
				else if (c == 72)
				{
					listHeader.tail->next = NULL;
					listHeader.head->prev = NULL;
					highline(accumulator, 1, textColor, true);
					moveTab();
				}
				else if (c == 80)
				{
					if (viewFavorite)
					{
						listHeader.tail->next = NULL;
						listHeader.head->prev = NULL;
						drawHeaderAndTab();
						drawFavorite(currentFolder);
						moveFavorite(currentFolder);
					}
					else
					{
						listHeader.tail->next = NULL;
						listHeader.head->prev = NULL;
						drawBrowser();
					}
				}
				currentTab->currentHeader = accumulator;
			}
			else if (c == 13)
			{
				listHeader.tail->next = NULL;
				listHeader.head->prev = NULL;
				viewHistory = false;
				viewBookMark = false;
				viewFavorite = false;
				if (accumulator->url == "<")
				{
					if (currentTab->currentUrl != currentTab->listUrl.head)
					{
						currentTab->currentUrl = currentTab->currentUrl->prev;
					}
					else
						moveHeader(currentTab->listUrl.head, listHeader);
				}
				else if (accumulator->url == ">")
				{
					if (currentTab->currentUrl != currentTab->listUrl.tail)
					{
						currentTab->currentUrl = currentTab->currentUrl->next;
					}
					else
						moveHeader(currentTab->listUrl.head, listHeader);
				}
				else if (accumulator->url == "Home" && currentTab->currentUrl->url != homeName)
				{
					addTail(currentTab->listUrl, createNode(homeName));
					currentTab->currentUrl = currentTab->currentUrl->next;
				}
				else if (accumulator->url == "|||\\")
				{
					currentTab->currentUrl->isBookMark = !currentTab->currentUrl->isBookMark;
					if (currentTab->currentUrl->isBookMark)
						addTail(listBookMark, createNode(currentTab->currentUrl->url));
					else
						findAndDelete(listBookMark, currentTab->currentUrl->url);
				}
				else if (accumulator->url == "X")
				{
					ghiFile(listLS, "url.txt");
					ghiFile(listBookMark, "bookMark.txt");
					// khi exit thi cua so nao se hien len?
					system("cls");
					Exit();
				}
				currentTab->currentHeader = accumulator;
				drawBrowser();
			}
		}
	}
}

void drawOption(listUrl &listHeader)
{
	listUrl option;
	createList(option);
	int x = positionX[3] + 10, y = 10, w = 50, h = 2;
	addTail(option, createNode("View History", "", x, y, w, h));
	addTail(option, createNode("View BookMark", "", x, y += 2, w, h));
	addTail(option, createNode("View your Favorite", "", x, y += 2, w, h));
	addTail(option, createNode("Open new tab", "", x, y += 2, w, h));
	n_box(option, 1, textColor, false);
	movePointer(option, listHeader, false);
}
void drawDeleLS(listUrl &listLS, string key, int t)
{
	listUrl Answer;
	createList(Answer);
	int x = positionX[2] + 85, y = 10, w = 30, h = 2;
	textcolor(12);
	gotoXY(x, y - 1);
	if (t == 1)
		cout << "Xoa lich su ngay " << key << " ? " << endl;
	else if (t == 0)
		cout << "Ban co chac muon xoa dia chi nay khong?" << endl;
	else if (t == -1)
		cout << "Ban co muon xoa dia chi "<< key << " ? " << endl;
	else if (t == -2)
		cout << "Ban co muon xoa folder " << key << " ? " << endl;
	else
		cout << " Ban co muon xoa tat ca ? " << endl;
	addTail(Answer, createNode("Yes", "", x, y, w, h));
	addTail(Answer, createNode("No", "", x, y + 2, w, h));
	n_box(Answer, 1, textColor, false);
	movePointer(Answer, listLS, false);
}
void n_box(listUrl list, int b_color, int t_color, bool isCenter)
{
	Node *accumulator = list.head;
	int i = 0;
	while (accumulator != NULL)
	{
		box(accumulator, 1, textColor, false);
		if (i != 0)
		{
			gotoXY(accumulator->x, accumulator->y);
			cout << char(195);
			gotoXY(accumulator->x + accumulator->w, accumulator->y);
			cout << char(180);
		}
		i++;
		accumulator = accumulator->next;
	}
}

template <typename T>
void highline(T *accumulator, int b_color, int t_color, bool isCenter)
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
	textcolor(0);
	ShowCur(0);
}

void drawSquareTab(string content, int x = 0, int y = 0, bool isFocus = false)
{
	int sizeTab = 15;
	int text = isFocus ? 14 : textColor;
	for (int i = 0; i < sizeTab; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (j == 0)
			{
				textcolor(outlinecolor);
				gotoXY(x + i, y);
				i == sizeTab - 1 ? cout << " x" : cout << char(196);
			}
			else
			{
				gotoXY(x + 1, y + j);
				if (content.size() > sizeTab - 5)
				{
					textcolor(text);
					cout << content.substr(0, sizeTab - 5) + ".. ";
				}
				else
				{
					textcolor(text);
					cout << content << string(sizeTab - content.size() - 2, ' ');
				}
				textcolor(outlinecolor);
				cout << char(47);
			}
		}
	}
}

void drawFavorite(FNode *current)
{
	if (current != NULL)
	{
		gotoXY(105, 6);
		cout << " [!] XOA LINK/FOLDER : NHAN PHIM BACKSPACE" << endl;
	}
	if (current->url != "|/-/| ROOT")
	{
		gotoXY(positionX[2], 6);
		textcolor(9);
		cout << "Favorite Name: " << current->url;
	}
	drawFolder(current);
	moveFavorite(current);
}

void drawFolder(FNode *current)
{
	int x = 1, y = 7, w = 101, h = 2;
	bool isCenter = false;
	Node *accumulator = current->LUrl.head;
	int i = 0;
	while (accumulator != NULL)
	{
		assignValue(accumulator, x, y, w, h);
		isCenter = (accumulator == current->LUrl.head || accumulator == current->LUrl.head->next) ? true : false;
		box(accumulator, 1, textColor, isCenter);
		if (i != 0)
		{
			gotoXY(x, y);
			cout << char(195);
			gotoXY(x + w, y);
			cout << char(180);
		}
		i++;
		y += 2;
		accumulator = accumulator->next;
	}
	if (current->LFNode.head != NULL)
	{
		FNode *accumulator = current->LFNode.head;
		while (accumulator != NULL)
		{
			assignValue(accumulator, x, y, w, h);
			box(accumulator, 1, textColor, false);
			gotoXY(x, y);
			cout << char(195);
			gotoXY(x + w, y);
			cout << char(180);
			y += 2;
			accumulator = accumulator->next;
		}
	}
}

void moveFavorite(FNode *current)
{
	ShowCur(0);
	moveLFUrl(current, true);
}

void moveLFUrl(FNode *current, bool isHead)
{
	ShowCur(0);

	Node *accumulator = isHead ? current->LUrl.head : current->LUrl.tail;
	bool isCenter = (accumulator == current->LUrl.head || accumulator == current->LUrl.head->next) ? true : false;
	highline(accumulator, bgColor, textColor, isCenter);

	while (true)
	{
		if (_kbhit())
		{
			char c = _getch();
			if (c == -32)
			{
				isCenter = (accumulator == current->LUrl.head || accumulator == current->LUrl.head->next) ? true : false;
				c = _getch();
				if (c == 80)
				{
					highline(accumulator, 1, textColor, isCenter);
					if (accumulator == current->LUrl.tail)
						current->LFNode.head ? moveLFNode(current) : moveLFUrl(current, true);
					else
					{
						accumulator = accumulator->next;
						isCenter = (accumulator == current->LUrl.head || accumulator == current->LUrl.head->next) ? true : false;
						highline(accumulator, bgColor, textColor, isCenter);
					}
				}
				else if (c == 72)
				{
					highline(accumulator, 1, textColor, isCenter);
					if (accumulator == current->LUrl.head)
					{
						currentFolder = current;
						moveHeader(accumulator, currentTab->listHeader);
					}
					else
					{
						accumulator = accumulator->prev;
						isCenter = (accumulator == current->LUrl.head || accumulator == current->LUrl.head->next) ? true : false;
						highline(accumulator, bgColor, textColor, isCenter);
					}
				}
			}
			else if (c == 13)
			{
				if (accumulator == current->LUrl.head->next)
				{
					drawInputButton(current);
				}
				else if (accumulator == current->LUrl.head)
				{
					string temp = currentTab->currentUrl->url;
					if (current->LUrl.tail->url != temp)
					{
						addTail(current->LUrl, createNode(temp));
					}
					else
					{
						gotoXY(108, 8);
						textcolor(14);
						cout << "Url da duoc them vao";
						Sleep(1);
					}
					drawHeaderAndTab();
					drawFavorite(current);
				}
				else if(viewFavorite)
				{
					addAfter(currentTab->listUrl, createNode(accumulator->url), currentTab->currentUrl);
					addTail(listLS, createNode(accumulator->url));
					currentTab->currentUrl = currentTab->currentUrl->next;
					currentTab->currentHeader = currentTab->listHeader.head;
					viewFavorite = false;
					drawBrowser();
				}
			}
			else if (c==8)
			{
				flag = 1;
				tempListDele_FV = current;
				tempNodeDele_FV = accumulator;	
				if(current->LUrl.head != accumulator && current->LUrl.head->next != accumulator) 
					drawDeleLS(current->LUrl, accumulator->url,-1);
				drawHeaderAndTab();
				drawFavorite(current);
			}
		}
	}
}

void drawInputButton(FNode *current)
{
	string input;
	box(createNode("", "", 105, 9, 30, 2), 0, 3, false);
	gotoXY(108, 7);
	textcolor(14);
	cout << "Enter name of your folder"<< endl;
	gotoXY(111,8);
	cout << "[NHAN ESC DE THOAT]";
	gotoXY(108, 10);
	ShowCur(1);
	while (true)
	{
		if (_kbhit())
		{
			char c = _getch();
			if (c == 27) {
				drawBrowser();
			}
			else 
			{
				textcolor(15);
				getline(cin, input);
				if (input != "")
				{
					addTailFNode(current, createFNode(input));
					drawHeaderAndTab();
					drawFavorite(current);
				}
			}
		}
	}
}
void moveLFNode(FNode *current)
{
	ShowCur(0);
	bool isCenter = false;

	FNode *accumulator = current->LFNode.head;
	highline(accumulator, bgColor, textColor, isCenter);

	while (true)
	{
		if (_kbhit())
		{
			char c = _getch();
			if (c == -32)
			{
				c = _getch();
				if (c == 80)
				{
					highline(accumulator, 1, textColor, isCenter);
					if (accumulator == current->LFNode.tail)
						moveLFUrl(current, true);
					else
					{
						accumulator = accumulator->next;
						highline(accumulator, bgColor, textColor, isCenter);
					}
				}
				else if (c == 72)
				{
					highline(accumulator, 1, textColor, isCenter);
					if (accumulator == current->LFNode.head)
						moveLFUrl(current, false);
					else
					{
						accumulator = accumulator->prev;
						highline(accumulator, bgColor, textColor, isCenter);
					}
				}
			}
			else if (c == 13)
			{
				drawHeaderAndTab();
				drawFavorite(accumulator);
			}
			else if (c == 8)
			{
				flag =0;
				tempListDele_FV = current;
				tempFNodeDele_FV = accumulator;
				drawDeleLS(current->LUrl, accumulator->url,-2);
				drawHeaderAndTab();
				drawFavorite(current);
			}
		}
	}
}

template <typename T>
void assignValue(T *node, int x, int y, int w, int h)
{
	node->x = x;
	node->y = y;
	node->w = w;
	node->h = h;
}

void Exit() {
	system("cls");
	textcolor(4);
	cout << "Your application has been closed" << endl;
	exit(0);
}