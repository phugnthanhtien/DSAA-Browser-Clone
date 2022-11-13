#pragma once
#include <bits/stdc++.h>
#include "node.h"
#include <fstream>

using namespace std;

void docFile(listUrl &list, string fileName, int x, int y, int w, int h) {  
    ifstream infile(fileName);
    string temp;
    int i = 0;
    while (infile >> temp) {
        Node *p = createNode(temp, x, y + (i * 2), w, h);
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

void ghiUrl(string fileName, string url) {
    ofstream outfile;
    outfile.open(fileName, std::ios_base::app);
    outfile << url << endl;
}