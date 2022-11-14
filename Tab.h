#pragma once
#include "node.h"

struct Tab {
    listUrl listUrl;
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

Tab *createTab(listUrl list) {
    Tab *newTab = new Tab;
    newTab->listUrl = list;
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

//int main() {
//    listUrl listLS;
//    listUrl listCehck;
//    listUrl listTest;
//    listUrl listTTTT;
//    createList(listCehck);
//    createList(listLS);
//    createList(listTest);
//    createList(listTTTT);
//
//    addTail(listLS, createNode("hehhe"));
//    addTail(listCehck, createNode("123564"));
//	addTail(listTest, createNode("test"));
//	addTail(listTTTT, createNode("just test"));
//
//    LTab myTabs;
//    initListTab(myTabs);
//
//    Tab *LS = createTab(listLS);
//    Tab *cehck = createTab(listCehck);
//    Tab * test = createTab(listTest);
//    Tab *t = createTab(listTTTT);
//
//    addTab(myTabs, LS);
//    addTab(myTabs, cehck);
//    addTab(myTabs, test);
//    addTab(myTabs, t);
//
//
//	printListTab(myTabs);
//	cout << endl;
//	deleteTab(myTabs, test);
//
//    printListTab(myTabs);
//
//    return 0;
//}


