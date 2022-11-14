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
<<<<<<< master
      node->next = NULL;
      after->next = node;
      list.tail = node;
=======
      node->next = after->next;
      after->next = node;
      if (list.tail != after)
         after->next->prev = node;
      if (list.tail == after) list.tail = after;
>>>>>>> update background - chỉnh addCurrent ở listSearch - findAndDelete
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
<<<<<<< master
}

=======
}
>>>>>>> update background - chỉnh addCurrent ở listSearch - findAndDelete
