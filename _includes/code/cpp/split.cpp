#include <iostream>
using namespace std;
typedef struct Num {
    int data;
    Num* next;
} Num,*Nums;
typedef struct Node {
    Nums head;
    Nums tail;
} Node,*Nodes;
void init(Node &node) {
    node.head=new Num;
    node.head->next=nullptr;
    node.tail=node.head;
  }
void TailInsert(Node &node,int num) {
    node.tail->next=new Num;
    node.tail=node.tail->next;
    node.tail->data=num;
    node.tail->next=nullptr;
  }
void split(Node &node, int n, Node &less, Node &greater) {
    Nums current = node.head->next;
    while (current != NULL) {
        if (current->data < n) {
            TailInsert(less, current->data);
        } else {
            TailInsert(greater, current->data);
        }
        current = current->next;
    }
}
void printList(Node &node) {
    Nums current = node.head->next;
    while (current != NULL) {
        cout << current->data << " ";
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
        TailInsert(node, num);
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