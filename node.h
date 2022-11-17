#pragma once
#include <iostream>

using namespace std;

struct Node {
    string url, dmy;
	int x, y, w, h;
	bool isBookMark = false;
    Node *prev, *next;
};

struct listUrl {
    Node *head, *tail;
};

Node *createNode(string data, string dmy = "", int x = 0, int y = 0, int w = 0, int h = 0) {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int year = 1900 + ltm->tm_year;
    int month = 1 + ltm->tm_mon;
    int day = ltm->tm_mday;
    if (dmy == "") 
        dmy = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
    Node *p = new Node;
    if (p == NULL)
        return NULL;
    else {
        p->url = data;
        p->dmy = dmy;
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
      cout << i->url  << " " << i->dmy << endl;
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

void addAfter(listUrl &list, Node* node, Node* after)
{
   if (after)
   {
      node->prev = after;
      node->next = NULL;
      after->next = node;
      list.tail = node;
   }
   else
      addTail(list, node);
}
Node* SearchNode(listUrl list, string key)
{
   Node *i = list.head;
   while (i && i->url != key)
      i = i->next;
   return i;
}
void findAndDelete(listUrl &list, string key)
{
   Node* result = SearchNode(list, key);
   removeNode(list, result);
}

