#include <iostream>
#include <vector>
using namespace std;
typedef struct Node {
  int x,y;
  struct Node *next;
} Node,*Nodes;
typedef struct Record {
  Nodes head;
} Record,*Records;
int init(Note &note) {
  record.head=new Node;
  record.head->next=nullptr;
  return 0;
}
int push(Record &record,int x,int y) {
  Nodes t=new Node;
  record.x=x;
  record.y=y;
  t.next=record.head->next;
  record.head->next=t;
  return 0;
}
int pop(Record &record) {
  Nodes t=record.head->next;
  record.head->next=t.next;
  delete t;
}
int createmaze(vector<vector<int>>& maze,int w,int h) {
  for(int i=1;i<w;i++) {
    for(int j=1;j<h;j++) {
      cin>>maze[w][h]
    }
  }
}
int try()