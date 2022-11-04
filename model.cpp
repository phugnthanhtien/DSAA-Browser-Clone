// tim hieu cach bam qua lai 
struct Node {
    string url;
    int x, y, w, h;
    Node*next;
    Node *prev;
}

struct listUrl {
    Node *Head = createNode("myhomepage.com");
    Node *Tail = null;
}

Node *createNode(string url) {
    Node * p  = new Node;
    p->url = url;
    p->prev = NULL;
    p->next = NULL;
}

void inittializeListUrl(listUrl listUrl, filename) {
    //doc tung dong
    createNode();
    addTail(listUrl listUrl, Node *add);
}

void ghiFile(string fileName, listUrl listCanGhi)

int main() {
    listUrl listUrl;
    listUrl bookMark;
    //tao home page

    //
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
    bool isbookMark = false;
    string option = "Tuy chon khac";

    //click next || prev || home -> veTrinhDuyet();

    // click search --> {
        Node currentURL = createNode(search);
        addTail(listUrl, currentURL);
        veTrinhDuyet(currentURL);
    }

    //click option
    // 1. List History
    // 2. List book Mark

    listLichSu(listUrl listUrl);

}

void listLichSu(listUrl) {
    // loop element in listUrl
    veLichSu(element);

    clearAll(); // mo rong
}

void listBookMark(listBookMark) {
    // loop element in listBookMark
    veLichSuBookMark(element);
    
    clearAll(); // mo rong
}

void veLichSu(Node *lichSu) {
    string url = lichSu.url;
    string xoa = "Delete";

    //click Xoa
    xoaNode(listUrl listUrl, Node *lichSu);
    if(lichSu.bookMark) xoaNode(listUrl listBookMark, Node *lichSu);
}

void veLichSuBookMark(Node *lichSu) {
    string url = lichSu.url;
    string xoa = "Delete";

    //click Xoa
    xoaNode(listUrl listBookMark, Node *lichSu);
}