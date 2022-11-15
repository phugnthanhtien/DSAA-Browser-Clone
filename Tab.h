#pragma once
#include "node.h"

struct Square {
	int x, y, w, h;
};

struct Tab {
    listUrl listUrl, listHeader;
    Node *currentUrl, *currentHeader;
    Square square;
    Tab *prev;
    Tab *next;
};

struct LTab {
    Tab *head;
    Tab *tail;
};

void initListTab(LTab &listTab) {
    listTab.head = NULL;
    listTab.tail = NULL;
}

Tab *createTab(listUrl list, listUrl listHeader, int x = 0, int y = 0, int w = 0, int h = 0) {
    Tab *newTab = new Tab;
    newTab->listUrl = list;
    newTab->listHeader = listHeader;
    newTab->square.x = x;
    newTab->square.y = y;
    newTab->square.w = w;
    newTab->square.h = h;
    newTab->currentUrl = list.head;
    newTab->currentHeader = listHeader.head;
    newTab->next = NULL;
    newTab->prev = NULL;
    return newTab;
}

void addTab(LTab &listTab, Tab *newTab){
    if(listTab.head == NULL) {
        listTab.head = newTab;
        listTab.tail = newTab;
    }
    else {
        listTab.tail->next = newTab;
        newTab->prev = listTab.tail;
        listTab.tail = newTab;
    }
}

void deleteTab(LTab &listTab, Tab *currentTab) {
	if(listTab.head == NULL) return;
	if(listTab.head == currentTab && listTab.tail == currentTab) {
		initListTab(listTab);
		delete currentTab;
	}
	else {
		if(listTab.head == currentTab) {
			listTab.head = listTab.head->next;
		}
		else {
			currentTab->prev->next = currentTab->next;
			if(currentTab == listTab.tail) 
				listTab.tail = currentTab->prev;
		}
		delete currentTab;
	}
}

void printListTab(LTab listTab) {
    Tab *accumulator = listTab.head;
    while(accumulator != NULL) {
        cout << accumulator->listUrl.head->url;
        accumulator = accumulator->next;
    }
}