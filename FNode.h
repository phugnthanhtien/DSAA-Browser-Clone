#pragma once
#include "node.h"
#include "mylib.h"

using namespace std;

struct FNode {
    string url;
    int x, y, w, h;
    FNode *prev;
    FNode *next;
    listUrl LUrl;
    struct listFNode
    {
        FNode *head;
        FNode *tail;
    }  LFNode;
};

FNode *createFNode(string url, int x = 0, int y = 0, int w = 0, int h = 0) {
    FNode *newFNode = new FNode;
    newFNode->url = "|/-/| " + url;
    newFNode->x = x;
    newFNode->y = y;
    newFNode->w = w;
    newFNode->h = h;
    newFNode->prev = NULL;
    newFNode->next = NULL;
    newFNode->LFNode.head = NULL;
    newFNode->LFNode.tail = NULL;
    createList(newFNode->LUrl);
    addTail(newFNode->LUrl, createNode("***Add Url to this favorite***"));
    addTail(newFNode->LUrl, createNode("***Create new Favorite***"));
    return newFNode;
}

//void printFNode(FNode *root) {
//	cout << "Folder: " << root->url << endl;
//	if(root->LUrl.head || root->LFNode.head) {	
//		cout << "Has: " << endl;
//	    for(Node *i = root->LUrl.head; i; i = i->next) {
//	    	cout << "url: " << i->url << endl;
//	    }
//	    int i = 1;
//	    for(FNode *j = root->LFNode.head; j; j = j->next) {
//			cout << "listF" << i << ": ";
//			printFNode(j);
//			i++;
//	    }         
//	}
//}

void printFNode(FNode *root, int x, int &y) {
	gotoXY(x, y);
	cout << "Folder: " << root->url;
	if(root->LUrl.head || root->LFNode.head) {
		gotoXY(x, ++y);
	    cout << "Has: ";
	    x+=2;
	    for(Node *i = root->LUrl.head; i; i = i->next) {
	    	gotoXY(x, ++y);
	        cout << "url: " << i->url;
	    }
	    int i = 1;
	    for(FNode *j = root->LFNode.head; j; j = j->next) {
	    	gotoXY(x , ++y);
	        cout << "listF" << i << ": ";
			printFNode(j, x, ++y);
			i++;
	    }
	}
}

void addTailFNode(FNode *root, FNode *newFNode) {
    if (root->LFNode.head == NULL)
		root->LFNode.head = root->LFNode.tail = newFNode;
	else
	{
		root->LFNode.tail->next = newFNode;
		newFNode->prev = root->LFNode.tail;
		root->LFNode.tail = newFNode;
	}
}

void removeFNode(FNode *p) {
	
}

void initFolder(FNode *root) {

  addTail(root->LUrl, createNode("facebook.com"));

   FNode *favorite = createFNode("favorite");
   
   FNode *animals = createFNode("animals");
   
   FNode *songs = createFNode("songs");
   addTail(songs->LUrl, createNode("EM la"));
   
   FNode *musiacals = createFNode("musicals");
   addTail(musiacals->LUrl, createNode("guitar"));
   addTail(musiacals->LUrl, createNode("piano"));
   
   FNode *hate = createFNode("hate");

   addTailFNode(favorite, animals);
   addTailFNode(favorite, songs);

  addTailFNode(root, favorite);
	addTailFNode(root, hate);
	addTailFNode(root, musiacals);
// 	int x= 0,y = 0;
//    printFNode(root, x, y);

}