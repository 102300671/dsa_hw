#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

int main() {
    vector<int> number;
    string line;
    getline(cin,line);
    stringstream ss(line);
    int num,sum=0;
    while (ss>>num) {
        number.push_back(num);
    }
    ofstream outfile;
    outfile.open("numbers.txt");
    for (int i=0;i<number.size();i++) {
        outfile<<number[i]<<endl;
    }
    outfile.close();
    ifstream infile;
    infile.open("numbers.txt");
    while (infile>>num) {
        sum+=num;
    }
    infile.close();
    cout<<sum<<endl;
    return 0;
}