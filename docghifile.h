#pragma once
#include <bits/stdc++.h>
#include "node.h"
#include <fstream>

using namespace std;

void docFile(listUrl &list, string fileName, string dmy = "", int x = 0, int y = 0, int w = 0, int h = 0)
{
    ifstream infile(fileName);
    string temp;
    int i = 0;
    while (infile >> temp)
    {
        string::difference_type n = std::count(temp.begin(), temp.end(), '/');
        if (n == 2)
        {
            dmy = temp;
        }
        if (n != 2)
        {
            Node *p = createNode(temp, dmy, x, y + (i * 2), w, h);
            addTail(list, p);
            i++;
        }
    }
}
/*
facebook 12/11
youtube 12/11
instagram 11/11
messenger 11/11
linkedin 10/11
*/
void ghiFile(listUrl &list, string fileName)
{
    ofstream MyFile(fileName);
    MyFile << list.head->dmy << endl;
    string cur_dmy = list.head->dmy;
    for (Node *i = list.head; i; i = i->next)
    {
        if (i->dmy != cur_dmy)
        {
            MyFile << i->dmy << endl;
            cur_dmy = i->dmy;
        }
        MyFile << i->url << endl;
    }
    MyFile.close();
}
void ghiUrl(string fileName, string url)
{
    ofstream outfile;
    outfile.open(fileName, std::ios_base::app);
    outfile << url << endl;
}
