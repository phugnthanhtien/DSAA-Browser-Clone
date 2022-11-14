#pragma once
#include <iostream>

using namespace std;

struct Node {
    string url;
	int x, y, w, h;
	bool isBookMark = false;
    Node *prev, *next;
};

struct listUrl {
    Node *head, *tail;
};

Node *createNode(string data, int x = 0, int y = 0, int w = 0, int h = 0) {
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

void browseNext(listUrl list) {
   for (Node*i = list.head; i; i = i->next) {
      cout << i->url << endl;
   }
}

void removeList(listUrl &list) { 
    Node *k;
    while (list.head) {
        k = list.head;
        list.head = list.head->next;
        delete k;
    }
}

void removeNode(listUrl &list, Node *x) {
    if (list.head == NULL) return;
    else {
        if (list.head == list.tail && x == list.head) {
            list.head = NULL;
            list.tail = NULL;
        }
        else if (x == list.head) {
            list.head = list.head->next;
            x->next->prev = NULL;
        }
        else if (x == list.tail) {
            list.tail = list.tail->prev;
            x->prev->next = NULL;      
        }
        else {
            x->prev->next = x->next;
            x->next->prev = x->prev;
        }
        delete x;
    }
}

bool isEmpty(listUrl list)
{
	if(list.head == NULL)
		return 1;
	return 0;
}

void addTail(listUrl &list, Node*p )
{
	if (isEmpty(list))
		list.head =  list.tail = p;
	else
	{
		list.tail->next = p;
		p->prev = list.tail;
		list.tail = p;
	}
}

