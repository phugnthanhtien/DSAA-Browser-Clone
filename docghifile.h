#pragma once
#include <bits/stdc++.h>
#include "node.h"
#include <fstream>

using namespace std;

Node *createNode(string data, int x, int y, int w, int h);
void createList(listUrl &list);
void browseNext(listUrl list);
void removeList(listUrl &list);
void removeNode(listUrl &list, Node *x);
bool isEmpty(listUrl list);
void addTail(listUrl &list, Node*p);
void docFile(listUrl &list, string fileName, int x, int y, int w, int h);
void ghiFile(listUrl &list, string fileName);


void docFile(listUrl &list, string fileName, int x, int y, int w, int h) {  
    ifstream infile(fileName);
    string temp;
    int i = 0;
    while (infile >> temp) {
        Node *p = createNode(temp, 1, 6 + (i * 2), w, h);
        addTail(list, p);
        i++;
    }
}
void ghiFile(listUrl &list, string fileName) {
    ofstream MyFile(fileName);
    for (Node*i = list.head; i; i = i->next) {
        MyFile << i->url << endl;
    }
    MyFile.close();
}
