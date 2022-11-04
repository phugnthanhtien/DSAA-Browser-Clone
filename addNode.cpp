#include <iostream>
using namespace std;
struct Node
{
	string url;
	Node*next;
	Node*prev;
};

struct listUrl 
{
    Node *Head;
    Node *Tail;
};

bool Empty(listUrl L);
Node *createNode(string url);
void AddTail(listUrl &L, Node*p );
void inList(listUrl &L);
int main()
{
	listUrl list;
	inList(list);
	AddTail(list, createNode("gg.com"));
	cout << list.Head->url;
	return 0;
}
Node *createNode(string url) {
    Node * p  = new Node;
    if (p == NULL)
    	return NULL;
    else
    {
	    p->url = url;
	    p->prev = NULL;
	    p->next = NULL;
	    return p;
	}
}
bool Empty(listUrl L)
{
	if(L.Head == NULL)
		return 1;
	return 0;
}
void inList(listUrl &L)
{
	L.Head = L.Tail = NULL;
}
void AddTail(listUrl &L, Node*p )
{
	if (Empty(L))
		L.Head =  L.Tail = p;
	else
	{
		L.Tail->next = p;
		p->prev = L.Tail;
		L.Tail = p;
	}
}



