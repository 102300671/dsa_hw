#include <iostream>
#include "TripletMatrix.h"
#include "OrthogonalMatrix.h"
using namespace std;

// 显示主菜单
void showMainMenu() {
    cout << "请选择矩阵类型:" << endl;
    cout << "1. 三元组矩阵" << endl;
    cout << "2. 正交链表矩阵" << endl;
    cout << "3. 退出" << endl;
    cout << "输入选择: ";
}

// 显示矩阵操作菜单
void showOperationMenu() {
    cout << "请选择操作:" << endl;
    cout << "1. 插入元素" << endl;
    cout << "2. 显示矩阵" << endl;
    cout << "3. 矩阵加法" << endl;
    cout << "4. 矩阵转置" << endl;
    cout << "5. 矩阵乘法" << endl;
    cout << "6. 返回主菜单" << endl;
    cout << "输入选择: ";
}

// 处理三元组矩阵操作
void handleTripletMatrix() {
    TripletMatrix tA(3, 3), tB(3, 3);
    int choice;
    int row, col, value;
    while (true) {
        showOperationMenu();
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "请输入行、列和值 (用空格分隔): ";
                cin >> row >> col >> value;
                cout << "选择插入到矩阵 A 还是 B (1: A, 2: B): ";
                int matrixChoice;
                cin >> matrixChoice;
                if (matrixChoice == 1) {
                    tA.insert(row, col, value);
                } else if (matrixChoice == 2) {
                    tB.insert(row, col, value);
                }
                break;
            case 2:
                cout << "选择显示矩阵 A 还是 B (1: A, 2: B): ";
                cin >> matrixChoice;
                if (matrixChoice == 1) {
                    cout << "三元组矩阵A:" << endl;
                    tA.display();
                } else if (matrixChoice == 2) {
                    cout << "三元组矩阵B:" << endl;
                    tB.display();
                }
                break;
            case 3:
                cout << "A + B:" << endl;
                tA.add(tB).display();
                break;
            case 4:
                cout << "选择转置矩阵 A 还是 B (1: A, 2: B): ";
                cin >> matrixChoice;
                if (matrixChoice == 1) {
                    cout << "A 的转置:" << endl;
                    tA.transpose().display();
                } else if (matrixChoice == 2) {
                    cout << "B 的转置:" << endl;
                    tB.transpose().display();
                }
                break;
            case 5:
                cout << "A * B:" << endl;
                tA.multiply(tB).display();
                break;
            case 6:
                return;
            default:
                cout << "无效的选择，请重新输入。" << endl;
        }
    }
}

// 处理正交链表矩阵操作
void handleOrthogonalMatrix() {
    OrthogonalMatrix oA(3, 3), oB(3, 3);
    int choice;
    int row, col, value;
    while (true) {
        showOperationMenu();
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "请输入行、列和值 (用空格分隔): ";
                cin >> row >> col >> value;
                cout << "选择插入到矩阵 A 还是 B (1: A, 2: B): ";
                int matrixChoice;
                cin >> matrixChoice;
                if (matrixChoice == 1) {
                    oA.insert(row, col, value);
                } else if (matrixChoice == 2) {
                    oB.insert(row, col, value);
                }
                break;
            case 2:
                cout << "选择显示矩阵 A 还是 B (1: A, 2: B): ";
                cin >> matrixChoice;
                if (matrixChoice == 1) {
                    cout << "正交链表矩阵A:" << endl;
                    oA.display();
                } else if (matrixChoice == 2) {
                    cout << "正交链表矩阵B:" << endl;
                    oB.display();
                }
                break;
            case 3:
                cout << "A + B:" << endl;
                oA.add(oB).display();
                break;
            case 4:
                cout << "选择转置矩阵 A 还是 B (1: A, 2: B): ";
                cin >> matrixChoice;
                if (matrixChoice == 1) {
                    cout << "A 的转置:" << endl;
                    oA.transpose().display();
                } else if (matrixChoice == 2) {
                    cout << "B 的转置:" << endl;
                    oB.transpose().display();
                }
                break;
            case 5:
                cout << "A * B:" << endl;
                oA.multiply(oB).display();
                break;
            case 6:
                return;
            default:
                cout << "无效的选择，请重新输入。" << endl;
        }
    }
}

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