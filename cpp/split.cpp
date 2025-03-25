#include <iostream>
using namespace std;
typedef struct Num {
    int num;
    Num* next;
} Num,*Nums;
typedef struct Node {
    Nums head;
    Nums tail;
} Node,*Nodes;
void init(Node &node) {
    node.head = NULL;
    node.tail = NULL;
}
void add(Node &node, int num) {
    Nums temp = new Num;
    temp->num = num;
    temp->next = NULL;
    if (node.head == NULL) {
        node.head = temp;
        node.tail = temp;
    } else {
        node.tail->next = temp;
        node.tail = temp;
    }
}
void split(Node &node, int n, Node &less, Node &greater) {
    Nums current = node.head;
    while (current != NULL) {
        if (current->num < n) {
            add(less, current->num);
        } else {
            add(greater, current->num);
        }
        current = current->next;
    }
}
void printList(Node &node) {
    Nums current = node.head;
    while (current != NULL) {
        cout << current->num << " ";
        current = current->next;
    }
}
void des(Node &node) {
  Nums current=node.head;
  while(current) {
    Nums t=current;
    current=current->next;
    delete t;
  }
}
int main() {
    Node node, less, greater;
    init(node);
    init(less);
    init(greater);
    int length;
    cin>>length;
    for (int i = 0; i < length; i++) {
        int num;
        cin>>num;
        add(node, num);
    }
    int n;
    cin>>n;
    split(node, n, less, greater);
    printList(less);
    printList(greater);
    des(node);
    des(less);
    des(greater);
    return 0;
}