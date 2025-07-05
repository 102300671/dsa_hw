#ifndef ORTHOGONAL_MATRIX_H
#define ORTHOGONAL_MATRIX_H

#include <iostream>
using namespace std;

// 稀疏矩阵的十字链表结点结构体
struct OLNode {
    int row, col, val;         // 行号、列号、元素值
    OLNode *right, *down;      // 指向右侧和下方结点的指针
    OLNode(int r = 0, int c = 0, int v = 0)
        : row(r), col(c), val(v), right(nullptr), down(nullptr) {}
};

// 十字链表稀疏矩阵类
class OrthogonalMatrix {
private:
    int rows, cols;                    // 矩阵的行数和列数
    OLNode** rowHeads;                 // 每一行的头结点指针数组
    OLNode** colHeads;                 // 每一列的头结点指针数组
    void ensureCapacity(int minRows, int minCols);
public:
    OrthogonalMatrix(int r = 0, int c = 0);   // 构造函数
    ~OrthogonalMatrix();                      // 析构函数，释放内存
    void insert(int r, int c, int v);         // 插入元素
    OrthogonalMatrix transpose() const;        // 转置矩阵
    OrthogonalMatrix add(const OrthogonalMatrix& other) const;      // 矩阵加法
    OrthogonalMatrix multiply(const OrthogonalMatrix& other) const; // 矩阵乘法
    void display() const;                      // 显示矩阵
    int getRowCount() const { return rows; }   // 获取行数
    int getColCount() const { return cols; }   // 获取列数
};

#endif // ORTHOGONAL_MATRIX_H