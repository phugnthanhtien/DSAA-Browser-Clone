#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <conio.h>
#include <vector>
#include "mylib.h"
using namespace std;


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
void drstar(vector <string> s)
{
for (int ii = 0; ii <30; ii++)
{
	for (int i = 0; i < s.size(); i++)
		{
			string st; 
			st = s[i].substr(0,50);
			textcolor(6);
			gotoXY(3, 15+i);
			cout << st;
			gotoXY(100,35+i);
			cout << st;
		}
	if (ii <29) 
		{
			Sleep(100);	
			system("cls"); 
		} 
	else 
		break;
}
}

void draw(int x, int y, int t_cl, vector <string> s1, vector <string> s2, vector <string> s3)
{
	for (int ii = 0; ii <20 ; ii++)
	{
		for (int i = 0; i < s1.size(); i++)
		{
			string st1; 
			st1 = s1[i].substr(0,70);
			textcolor(t_cl);
			gotoXY(x-ii,y+i);
			cout << st1;
		}
		for (int i = 0; i < s2.size(); i++)
		{
			string st2; 
			st2 = s2[i].substr(0,70);
			textcolor(t_cl);
			gotoXY(ii, y+i);
			cout << st2;
		} 
	    if (ii <19) 
		{
			Sleep(100);	
			system("cls"); 
		} 
	}
	drstar(s3);
}


int main()
{
	int x =80, y= 25;
	char dora[] = "./dora.txt";
	char nobi[] = "./nobi.txt";
	char star[] = "./star.txt";
	vector<string> s1 = input(dora);
	vector<string> s2 = input(nobi);	
	vector<string> s3 = input(star);
	draw(x,y,9,s1,s2,s3);
//	drstar(s3);
	_getch();
	return 0;
}
