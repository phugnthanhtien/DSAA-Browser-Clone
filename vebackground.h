#pragma once
#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <conio.h>
#include <vector>
#include "mylib.h"
using namespace std;

int Time = 150;
vector <string> input(char *s){
	ifstream cin(s);
	vector <string> kq;
	if(!cin){
		cout << "Duong dan sai " << s ;
		return kq;
	}
	string x;
	while(1){
		if(!getline(cin, x))
			return kq;
		kq.push_back(x);
	} 
}
void MayTinh(int x, int y, vector<string> may_tinh){
	for(int i=0; i<may_tinh.size(); i++){
		string s;
		if(i == 8){
			s = may_tinh[i].substr(0, 20);
		}else
			s = may_tinh[i].substr(0, 25);
		gotoXY(x, y + i);
		cout << s;
	}
	for(int i=0; i<may_tinh.size(); i++){
		string s;
		if(i == 8){
			s = "  " + may_tinh[i].substr(45);
		}else
			s = may_tinh[i].substr(43);
		gotoXY(x + 44, y + i);
		cout << s;
	}
	
	for(int i=0; i<=12; i++){
		gotoXY(x + i + 21, y + 8);
		cout << may_tinh[8][i + 21];
		gotoXY(x + 45 - i, y + 8);
		cout << may_tinh[8][45 - i];
		Sleep(Time);
	}
	for(int i=0; i<8; i++){
		textcolor(12);
		gotoXY(x + 35 - i - 3, y + 8 - i);
		cout << may_tinh[8 - i].substr(35 - i - 3, i*2 + 3);
		if(i == 4){
			textcolor(7);
			gotoXY(x + 13, y + 5);
			cout << "___";
			Sleep(Time*1.5);
			gotoXY(x + 12, y + 5);
			cout << "\\";
			gotoXY(x + 16, y + 5);
			cout << "/";
		}
		Sleep(Time*1.5);
	}
}

void drawBR()
{
	textcolor(7);
	int x = 30, y = -5;
	char may_tinh[] = "./maytinh.txt";
	vector<string> s1 = input(may_tinh);
	MayTinh(x + 5, y + 30, s1);
	textcolor(12);
//	_getch();
}
