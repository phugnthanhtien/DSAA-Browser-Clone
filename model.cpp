// tim hieu cach bam qua lai 
struct Node {
    string url;
    Node*next;
    Node *prev;
}

struct listUrl {
    Node *Head = createNode("myhomepage.com");
    Node *Tail = null;
}
struct listBookMark {
    Node *Head ; // khoi tao home page
    Node *Tail;
}

Node *createNode(string url) {
    Node * p  = new Node;
    p->url = url;
    p->prev = NULL;
    p->next = NULL;
}

void clearHistory() {
    void xemLichSu();
}
int main() {
    listUrl listUrl;
    //tao home page
    header(listUrl.head, listUrl.head);
    homePage();
}

void veTrinhDuyet(Node *currentUrl) {
    header(currentUrl);
    content(currentUrl.url);
}

void header(Node*Head, Node *path) {
    listBookMark;
    Node *next = path->next;
    Node *prev = path->prev;
    Node *home = Head;
    string url = path->url;
    string search = "Nhap URL";
    book isbookMark = false;
    string option = "Tuy chon khac";

    //click next || prev || home -> veTrinhDuyet();

    // click search --> {
        Node currentURL = createNode(search);
        addTail(listUrl, currentURL);
        veTrinhDuyet(currentURL);
    }

}