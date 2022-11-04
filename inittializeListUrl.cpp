#include <bits/stdc++.h>
#include <fstream>

using namespace std;

struct Node {
    string url;
    Node *prev, *next;
};

struct List {
    Node *head, *tail;
};

Node *createNode(string data);
void createList(List &list);
void addTail(List &list, Node* node);
void browseNext(List list);
void inittializeListUrl(List &listUrl, string fileName);
void writeHistoryFile(List &listUrl, string fileName);

int main() {
    List li;
    createList(li);
    inittializeListUrl(li, "url.txt");
    //browseNext(li);
    writeHistoryFile(li, "url_history.txt");
    return 0;
}

void inittializeListUrl(List &listUrl, string fileName) {
    ifstream infile(fileName);
    string temp;
    while (infile >> temp) {
        Node *p = createNode(temp);
        addTail(listUrl, p);
    }
}

void writeHistoryFile(List &listUrl, string fileName) {
    ofstream MyFile(fileName);
    for (Node*i = listUrl.head; i; i = i->next) {
        MyFile << i->url << endl;
    }
    MyFile.close();
}

Node *createNode(string data) {
    Node *p = new Node;
    if (p == NULL)
        return NULL;
    else {
        p->url = data;
        p->next = NULL;
        p->prev = NULL;
        return p;
    }
}
void createList(List &list) {
    list.head = list.tail = NULL;
}

void addTail(List &list, Node* node) {
   if (!list.head)
      list.head = list.tail = node;
   else {
      node->prev = list.tail;
      list.tail->next = node;
      list.tail = node;
   }
}

void browseNext(List list) {
   for (Node*i = list.head; i; i = i->next) {
      cout << i->url << endl;
   }
}

