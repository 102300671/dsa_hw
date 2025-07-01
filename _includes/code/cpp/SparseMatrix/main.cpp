#include <iostream>
#include "TripletMatrix.h"
#include "OrthogonalMatrix.h"
#include "MatrixOperations.h"
using namespace std;



int main() {
    int choice;
    while (true) {
        showMainMenu();
        cin >> choice;
        switch (choice) {
            case 1:
                handleTripletMatrix();
                break;
            case 2:
                handleOrthogonalMatrix();
                break;
            case 3:
                return 0;
            default:
                cout << "无效的选择，请重新输入。" << endl;
        }
    }
    return 0;
}