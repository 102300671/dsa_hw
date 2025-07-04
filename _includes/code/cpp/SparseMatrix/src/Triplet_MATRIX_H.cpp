#include "TripletMatrix.h"
#include <iostream>
#include <stdexcept>
using namespace std;

void TripletMatrix::ensureCapacity(int minCapacity) {
    if (capacity >= minCapacity) return;
    int newCap = capacity == 0 ? 8 : capacity * 2;
    if (newCap < minCapacity) newCap = minCapacity;
    Triple* newData = new Triple[newCap];
    for (int i = 0; i < size; ++i) newData[i] = data[i];
    delete[] data;
    data = newData;
    capacity = newCap;
}

TripletMatrix::TripletMatrix(int r, int c)
    : rows(r), cols(c), data(nullptr), size(0), capacity(0) {}

TripletMatrix::TripletMatrix(const TripletMatrix& other)
    : rows(other.rows), cols(other.cols), data(nullptr), size(other.size), capacity(other.capacity) {
    if (capacity > 0) {
        data = new Triple[capacity];
        for (int i = 0; i < size; ++i) data[i] = other.data[i];
    }
}

TripletMatrix& TripletMatrix::operator=(const TripletMatrix& other) {
    if (this == &other) return *this;
    delete[] data;
    rows = other.rows; cols = other.cols; size = other.size; capacity = other.capacity;
    data = nullptr;
    if (capacity > 0) {
        data = new Triple[capacity];
        for (int i = 0; i < size; ++i) data[i] = other.data[i];
    }
    return *this;
}

TripletMatrix::~TripletMatrix() {
    delete[] data;
}

void TripletMatrix::insert(int r, int c, int v) {
    if (v != 0) {
        ensureCapacity(size + 1);
        data[size++] = Triple(r, c, v);
    }
}

// 转置
TripletMatrix TripletMatrix::transpose() const {
    TripletMatrix result(cols, rows);
    for (int i = 0; i < size; ++i) {
        result.insert(data[i].col, data[i].row, data[i].val);
    }
    return result;
}

// 简单选择排序，按行优先、列次之
static void sortTriples(Triple* arr, int n) {
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j].row < arr[minIdx].row ||
                (arr[j].row == arr[minIdx].row && arr[j].col < arr[minIdx].col)) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            Triple tmp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = tmp;
        }
    }
}

// 加法
TripletMatrix TripletMatrix::add(const TripletMatrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("矩阵维度不一致，无法相加");
    }
    TripletMatrix result(rows, cols);
    // 拷贝并排序
    Triple* a = new Triple[size];
    Triple* b = new Triple[other.size];
    for (int i = 0; i < size; ++i) a[i] = data[i];
    for (int i = 0; i < other.size; ++i) b[i] = other.data[i];
    sortTriples(a, size);
    sortTriples(b, other.size);

    int i = 0, j = 0;
    while (i < size && j < other.size) {
        if (a[i].row == b[j].row && a[i].col == b[j].col) {
            int sum = a[i].val + b[j].val;
            if (sum != 0)
                result.insert(a[i].row, a[i].col, sum);
            ++i; ++j;
        } else if (a[i].row < b[j].row || (a[i].row == b[j].row && a[i].col < b[j].col)) {
            result.insert(a[i].row, a[i].col, a[i].val);
            ++i;
        } else {
            result.insert(b[j].row, b[j].col, b[j].val);
            ++j;
        }
    }
    while (i < size) {
        result.insert(a[i].row, a[i].col, a[i].val);
        ++i;
    }
    while (j < other.size) {
        result.insert(b[j].row, b[j].col, b[j].val);
        ++j;
    }
    delete[] a;
    delete[] b;
    return result;
}

// 乘法
TripletMatrix TripletMatrix::multiply(const TripletMatrix& other) const {
    if (cols != other.rows) {
        throw std::invalid_argument("矩阵维度不匹配，无法相乘");
    }
    TripletMatrix result(rows, other.cols);
    // 先将other按行列分组
    for (int i = 0; i < size; ++i) {
        int arow = data[i].row, acol = data[i].col, aval = data[i].val;
        for (int j = 0; j < other.size; ++j) {
            if (other.data[j].row == acol) {
                int bcol = other.data[j].col, bval = other.data[j].val;
                int r = arow, c = bcol, v = aval * bval;
                // 查找result中是否已有(r,c)
                bool found = false;
                for (int k = 0; k < result.size; ++k) {
                    if (result.data[k].row == r && result.data[k].col == c) {
                        result.data[k].val += v;
                        found = true;
                        break;
                    }
                }
                if (!found && v != 0) {
                    result.insert(r, c, v);
                }
            }
        }
    }
    // 移除乘积为0的项
    int idx = 0;
    for (int i = 0; i < result.size; ++i) {
        if (result.data[i].val != 0) {
            result.data[idx++] = result.data[i];
        }
    }
    result.size = idx;
    return result;
}

// 显示
void TripletMatrix::display() const {
    cout << "稀疏矩阵（" << rows << "x" << cols << "，非零元素" << size << "个）:" << endl;
    for (int i = 0; i < size; ++i) {
        cout << "(" << data[i].row << ", " << data[i].col << ") = " << data[i].val << endl;
    }
}