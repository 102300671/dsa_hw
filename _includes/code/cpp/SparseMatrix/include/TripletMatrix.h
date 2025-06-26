#ifndef TRIPLET_MATRIX_H
#define TRIPLET_MATRIX_H

#include <iostream>
using namespace std;

// 三元组结构体，表示稀疏矩阵的一个非零元素
struct Triple {
    int row, col;   // 元素所在的行和列
    int val;        // 元素的值
    Triple(int r = 0, int c = 0, int v = 0) : row(r), col(c), val(v) {}
};

// 三元组顺序表稀疏矩阵类
class TripletMatrix {
private:
    int rows, cols;             // 矩阵的行数和列数
    Triple* data;               // 存储所有非零元素的三元组数组
    int size;                   // 当前非零元素个数
    int capacity;               // 当前分配的容量
    void ensureCapacity(int minCapacity); // 扩容函数
public:
    TripletMatrix(int r = 0, int c = 0);           // 构造函数
    TripletMatrix(const TripletMatrix& other);      // 拷贝构造
    TripletMatrix& operator=(const TripletMatrix& other); // 赋值运算符
    ~TripletMatrix();                              // 析构函数
    void insert(int r, int c, int v);              // 插入一个非零元素
    TripletMatrix transpose() const;                // 转置矩阵
    TripletMatrix add(const TripletMatrix& other) const;      // 矩阵加法
    TripletMatrix multiply(const TripletMatrix& other) const; // 矩阵乘法
    void display() const;                           // 显示矩阵
    int getRowCount() const { return rows; }        // 获取行数
    int getColCount() const { return cols; }        // 获取列数
    int getNonZeroCount() const { return size; }    // 获取非零元素个数
};

#endif // TRIPLET_MATRIX_H