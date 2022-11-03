#include <bits/stdc++.h>

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
void removeList(List &list);
void removeNode(List &list, Node *x);

int main() {
    List li;
    createList(li);
    Node *x1 = createNode("Hello");
    Node *x2 = createNode("Hi");
    Node *x3 = createNode("A nhon");
    Node *x4 = createNode("Ni hao");
    Node *x5 = createNode("Xa quat ni kha");
    addTail(li, x1);
    addTail(li, x2);
    addTail(li, x3);
    addTail(li, x4);
    addTail(li, x5);
    browseNext(li);
    // cout << "Remove node x1: " << endl;
    // removeNode(li, x1);
    // cout << "Remove node x2: "<< endl;
    // removeNode(li, x2);
    cout << "Remove node x5: " << endl;
    removeNode(li, x5);
    browseNext(li);
    return 0;
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

void removeList(List &list) { // clear web browser
    Node *k;
    while (list.head) {
        k = list.head;
        list.head = list.head->next;
        delete k;
    }
}

void removeNode(List &list, Node *x) {
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