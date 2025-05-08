#include <iostream>
#include <string>
#include <fstream>
using namespace std;
int file_create(const string& filename) {
  ofstream file(filename);
  if(!file.is_open()) {
    cerr<<创建文件失败<<endl;
    return 1;
  }
  file.close();
  return 0;
}
int file_read(const string& filename) {
  string line;
  ifstream file(filename);
  if(!file.is_open()) {
    cerr<<"无法打开文件"<<endl;
    return 1;
  }
  while(getline(file,line)) {
    cout<<line<<endl;
  }
  file.close();
  return 0;
}
int file_add_write(const string& filename) {
  ofstream file(filename,ios::app);
  if(!file.is_open()) {
    cerr<<"无法打开文件"<<endl;
    return 1;
  }
  string line;
  while(true) {
    getline(cin,line);
    if(line.empty()) {
      break;
    }
    file<<line<<endl;
  }
  file.close();
  return 0;
}
int file_re_write(const string& filename) {
  ofstream file(filename);
  if(!file.is_open()) {
    cerr<<"无法打开文件"<<endl;
    return 1;
  }
  string line;
  while(true) {
    getline(cin,line);
    if(line.empty()) {
      break;
    }
    file<<line<<endl;
  }
  file.close();
  return 0;
}
int main() {
  cout<<"请选择操作:";
  int os;
  cin>>os;
  cout<<"1:创建文件"<<endl
      <<"2:读取文件内容"<<endl
      <<"3:文件追加内容"<<endl
      <<"4:覆写文件"<<endl;
  string filename;
  cout<<"请输入文件名"<<endl;
  getline(cin,filename);
  if(os==1) {
    file_create(filename);
  }
  else if(os==2) {
    file_read(filename);
  }
  else if(os==3) {
    file_add_write(filename);
  }
  else if(os==4) {
    file_re_write(filename);
  }
  return 0;
}