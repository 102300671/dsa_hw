# 稀疏矩阵实验（C++）

本项目实现了两种稀疏矩阵存储结构及其基本运算：
- 三元组顺序表（TripletMatrix）
- 正交链表（OrthogonalMatrix）

## 目录结构

```
.
├── main.cpp                # 程序入口，交互式菜单
├── Makefile                # 构建脚本
├── include/
│   ├── TripletMatrix.h     # 三元组类声明
│   └── OrthogonalMatrix.h  # 正交链表类声明
├── src/
│   ├── Triplet_MATRIX_H.cpp # 三元组类实现
│   └── OrthogonalMatrix.cpp # 正交链表类实现
```

## 编译与运行

```bash
make
./sparse_matrix_demo
```

## 功能

- 支持三元组和正交链表两种稀疏矩阵的插入、显示、加法、转置、乘法
- 交互式菜单操作

## 示例

运行后可选择矩阵类型和操作，按提示输入即可。

## 清理

```bash
make clean
```

## 依赖

- C++11 或更高
- g++ 编译器

---

如有问题请联系作