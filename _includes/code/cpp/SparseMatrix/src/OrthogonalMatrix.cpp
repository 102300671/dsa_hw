#include "OrthogonalMatrix.h"
#include <stdexcept>

// 构造函数
OrthogonalMatrix::OrthogonalMatrix(int r, int c) : rows(r), cols(c) {
    rowHeads = new OLNode*[rows];
    colHeads = new OLNode*[cols];
    for (int i = 0; i < rows; ++i) rowHeads[i] = nullptr;
    for (int j = 0; j < cols; ++j) colHeads[j] = nullptr;
}

// 析构函数
OrthogonalMatrix::~OrthogonalMatrix() {
    for (int i = 0; i < rows; ++i) {
        OLNode* p = rowHeads[i];
        while (p) {
            OLNode* tmp = p->right;
            delete p;
            p = tmp;
        }
    }
    delete[] rowHeads;
    delete[] colHeads;
}

// 扩容函数
void OrthogonalMatrix::ensureCapacity(int minRows, int minCols) {
    int newRows = (minRows > rows) ? minRows : rows;
    int newCols = (minCols > cols) ? minCols : cols;
    if (newRows == rows && newCols == cols) return;

    // 扩展行头
    OLNode** newRowHeads = new OLNode*[newRows];
    for (int i = 0; i < newRows; ++i)
        newRowHeads[i] = (i < rows) ? rowHeads[i] : nullptr;
    delete[] rowHeads;
    rowHeads = newRowHeads;

    // 扩展列头
    OLNode** newColHeads = new OLNode*[newCols];
    for (int j = 0; j < newCols; ++j)
        newColHeads[j] = (j < cols) ? colHeads[j] : nullptr;
    delete[] colHeads;
    colHeads = newColHeads;

    rows = newRows;
    cols = newCols;
}

// 插入元素
void OrthogonalMatrix::insert(int r, int c, int v) {
    if (v == 0) return;
    if (r < 0 || c < 0) throw std::out_of_range("插入位置越界");
    ensureCapacity(r + 1, c + 1); // 自动扩容
    OLNode* node = new OLNode(r, c, v);
    // 按行插入
    OLNode** pp = &rowHeads[r];
    while (*pp && (*pp)->col < c) pp = &((*pp)->right);
    node->right = *pp;
    *pp = node;
    // 按列插入
    pp = &colHeads[c];
    while (*pp && (*pp)->row < r) pp = &((*pp)->down);
    node->down = *pp;
    *pp = node;
}

// 转置
OrthogonalMatrix OrthogonalMatrix::transpose() const {
    OrthogonalMatrix result(cols, rows);
    for (int i = 0; i < rows; ++i) {
        for (OLNode* p = rowHeads[i]; p; p = p->right) {
            result.insert(p->col, p->row, p->val);
        }
    }
    return result;
}

// 加法
OrthogonalMatrix OrthogonalMatrix::add(const OrthogonalMatrix& other) const {
    if (rows != other.rows || cols != other.cols)
        throw std::invalid_argument("矩阵维度不一致，无法相加");
    OrthogonalMatrix result(rows, cols);
    // 先插入本矩阵所有元素
    for (int i = 0; i < rows; ++i)
        for (OLNode* p = rowHeads[i]; p; p = p->right)
            result.insert(p->row, p->col, p->val);
    // 再插入other，若有重复则累加
    for (int i = 0; i < rows; ++i) {
        for (OLNode* p = other.rowHeads[i]; p; p = p->right) {
            // 查找result中是否已有该位置
            OLNode* q = result.rowHeads[p->row];
            while (q && q->col < p->col) q = q->right;
            if (q && q->col == p->col) {
                q->val += p->val;
                if (q->val == 0) {
                    // 可选：删除为0的节点
                }
            } else {
                result.insert(p->row, p->col, p->val);
            }
        }
    }
    return result;
}

// 乘法
OrthogonalMatrix OrthogonalMatrix::multiply(const OrthogonalMatrix& other) const {
    if (cols != other.rows)
        throw std::invalid_argument("矩阵维度不匹配，无法相乘");
    OrthogonalMatrix result(rows, other.cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < other.cols; ++j) {
            int sum = 0;
            OLNode* pa = rowHeads[i];
            OLNode* pb = other.colHeads[j];
            while (pa && pb) {
                if (pa->col < pb->row) pa = pa->right;
                else if (pa->col > pb->row) pb = pb->down;
                else {
                    sum += pa->val * pb->val;
                    pa = pa->right;
                    pb = pb->down;
                }
            }
            if (sum != 0) result.insert(i, j, sum);
        }
    }
    return result;
}

// 显示
void OrthogonalMatrix::display() const {
    cout << "稀疏矩阵（" << rows << "x" << cols << "）:" << endl;
    for (int i = 0; i < rows; ++i) {
        OLNode* p = rowHeads[i];
        for (int j = 0; j < cols; ++j) {
            if (p && p->col == j) {
                cout << p->val << "\t";
                p = p->right;
            } else {
                cout << "0\t";
            }
        }
        cout << endl;
    }
}