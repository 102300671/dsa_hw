#include <iostream>
using namespace std;
typedef struct Num {
  int data;
  struct Num *next;
} Num,*Nums;
typedef struct Node {
  Nums head;
  int length;
  int max;
} Node,*Nodes;
int init(Node &node,int max) {
  if(max<=0) {
    cout<<"请输入正整数"<<endl; 
    return 1;
  }
  node.head=new Num;
  node.head->next=nullptr;
  node.length=0;
  node.max=max;
  return 0;
}
int push(Node &node) {
  if(node.max==node.length) {
    cout<<"栈满"<<endl;
    return 1;
  }
  Nums t=new Num;
  cout<<"请输入一个整数:";
  int e;
  cin>>e;
  t->data=e;
  t->next=node.head->next;
  node.head->next=t;
  node.length++;
  return 0;
}
int pop(Node &node) {
  if(node.length==0) {
    cout<<"栈空"<<endl;
    return 1;
  }
  Nums current=node.head->next;
  cout<<current->data<<"已出栈"<<endl;
  node.head->next=current->next;
  delete current;
  node.length--;
  return 0;
}
int get(Node node) {
  if(node.length==0) {
    cout<<"栈空"<<endl;
    return 1;
  }
  cout<<"栈顶:"<<node.head->next->data<<endl;
  return 0;
}
int print(Node node) {
  if(node.length==0) {
    cout<<"栈空"<<endl;
    return 1;
  }
  Nums current=node.head->next;
  while(current) {
    cout<<current->data<<" ";
    current=current->next;
  }
  cout<<endl;
  return 0;
}
int clear(Node &node) {
  if(node.length==0) {
    cout<<"栈空"<<endl;
    return 1;
  }
  Nums current=node.head->next;
  while(current) {
    Nums next=current->next;
    delete current;
    current=next;
  }
  node.head->next=nullptr;
  node.length=0;
  return 0;
}
int des(Node &node) {
  Nums current=node.head->next;
  while(current) {
    Nums t=current;
    current=current->next;
    delete t;
  }
  delete node.head;
  return 0;
}
int main() {
  int max;
  Node node;
  while(1) {
    cout<<"请输入栈容量:";
    cin>>max;
    if(!(init(node,max))) {
      break;
    }  
  }
  while(1) {
    int op;
    cout<<"0:退出"<<endl;
    cout<<"1:入栈"<<endl;
    cout<<"2:出栈"<<endl;
    cout<<"3:仅获取栈顶元素(不出栈)"<<endl;
    cout<<"4:遍历栈"<<endl;
    cout<<"5:清空栈"<<endl;
    cout<<"请输入操作:";
    cin>>op;
    if(op==0) {
      break;
    }
    if(op==1) {
      push(node);
    }
    if(op==2) {
      pop(node);
    }
    if(op==3) {
      get(node);
    }
    if(op==4) {
      print(node);
    }
    if(op==5) {
      clear(node);
    }
  }
  des(node);
  return 0;
}