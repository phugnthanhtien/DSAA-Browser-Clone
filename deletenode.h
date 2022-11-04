#include <iostream>
using namespace std;

struct Node {
    string url;
	int x, y, w, h;
    Node *prev, *next;
};

struct listUrl {
    Node *head, *tail;
};

Node *createNode(string data, int x, int y, int w, int h);
void createList(listUrl &list);
void addTail(listUrl &list, Node* node);
void browseNext(listUrl list);
void removeList(listUrl &list);
void removeNode(listUrl &list, Node *x);

Node *createNode(string data, int x, int y, int w, int h) {
    Node *p = new Node;
    if (p == NULL)
        return NULL;
    else {
        p->url = data;
        p->x = x;
		p->y = y;
		p->w = w;
		p->h = h;
        p->next = NULL;
        p->prev = NULL;
        return p;
    }
}
void createList(listUrl &list) {
    list.head = list.tail = NULL;
}

void addTail(listUrl &list, Node* node) {
   if (!list.head)
      list.head = list.tail = node;
   else {
      node->prev = list.tail;
      list.tail->next = node;
      list.tail = node;
   }
}

void browseNext(listUrl list) {
   for (Node*i = list.head; i; i = i->next) {
      cout << i->url << endl;
   }
}

void removeList(listUrl &list) { // clear web browser
    Node *k;
    while (list.head) {
        k = list.head;
        list.head = list.head->next;
        delete k;
    }
}

void removeNode(listUrl &list, Node *x) {
    if (x == list.head) {
        return;
    }
    else {
        if (x == list.tail) {
            x->prev->next = NULL;      
        }
        else {
            x->prev->next = x->next;
            x->next->prev = x->prev;
        }
        delete x;
    }
}