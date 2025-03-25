#include <iostream>
using namespace std;
typedef struct Num {
  int data;
  struct Num* next;
} Num,*Nums;
typedef struct Node {
  Nums head;
  Nums tail;
  int length;
} Node,*Nodes;
void init(Node &node) {
  node.head=new Num;
  node.head->next=node.head;
  node.tail=node.head;
  node.length=0;
}
void TailInsert(Node &node,int num) {
  Nums newNode=new Num;
  newNode->data=num;
  newNode->next=node.head;
  node.tail->next=newNode;
  node.tail=newNode;
  node.length++;
}
void move(Node &node,int k) {
  k=k%node.length;
  Nums newTail=node.head->next;
  for(int i=0;i<node.length-k-1;++i) {
    newTail=newTail->next;
  }
  node.tail->next=node.head->next;
  node.head->next=newTail->next;
  newTail->next=node.head;
  node.tail=newTail;
}
void print(Node &node) {
  Nums current=node.head->next;
  for(int i=0;i<node.length;i++) {
    cout<<current->data<<" ";
    current=current->next;
  }
}
void des(Node &node) {
  Nums current=node.head;
  for(int i=0;i<node.length;i++) {
    Nums t=current;
    current=current->next;
    delete t;
  }
}
int main() {
  Node node;
  init(node);
  int n,num,k;
  cin>>n;
  for(int i=0;i<n;i++) {
	  cin>>num;
    TailInsert(node,num);
  }
  cin>>k;
  move(node,k);
  print(node);
  des(node);
  return 0;
}