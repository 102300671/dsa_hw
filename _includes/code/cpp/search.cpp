#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;

// （1）静态查找表：顺序查找、折半查找、分块查找

// 顺序查找
int sequentialSearch(const vector<int>& arr, int target) {
    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] == target) {
            return i; // 找到目标元素，返回其索引
        }
    }
    return -1; // 未找到目标元素
}

// 折半查找（二分查找）
int binarySearch(const vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2; // 防止整数溢出
        if (arr[mid] == target) {
            return mid; // 找到目标元素，返回其索引
        } else if (arr[mid] < target) {
            left = mid + 1; // 目标在右半部分
        } else {
            right = mid - 1; // 目标在左半部分
        }
    }
    return -1; // 未找到目标元素
}

// 分块查找的索引表结构
struct IndexBlock {
    int maxValue; // 块中的最大值
    int startIndex; // 块的起始索引
};

// 分块查找
int blockSearch(const vector<int>& arr, const vector<IndexBlock>& indexTable, int target) {
    // 先在索引表中确定目标可能所在的块
    int blockIndex = -1;
    for (int i = 0; i < indexTable.size(); ++i) {
        if (target <= indexTable[i].maxValue) {
            blockIndex = i;
            break;
        }
    }

    if (blockIndex == -1) {
        return -1; // 目标元素大于所有块的最大值
    }

    // 在确定的块中进行顺序查找
    int start = indexTable[blockIndex].startIndex;
    int end = (blockIndex == indexTable.size() - 1) ? arr.size() - 1 : indexTable[blockIndex + 1].startIndex - 1;

    for (int i = start; i <= end; ++i) {
        if (arr[i] == target) {
            return i;
        }
    }

    return -1; // 未找到目标元素
}

// （2）动态查找表：二叉排序树、平衡二叉树

// 二叉排序树的节点结构
struct BSTNode {
    int key;
    BSTNode* left;
    BSTNode* right;
    BSTNode(int k) : key(k), left(nullptr), right(nullptr) {}
};

// 二叉排序树插入操作
BSTNode* insertBST(BSTNode* root, int key) {
    if (root == nullptr) {
        return new BSTNode(key);
    }
    if (key < root->key) {
        root->left = insertBST(root->left, key);
    } else if (key > root->key) {
        root->right = insertBST(root->right, key);
    }
    return root;
}

// 二叉排序树查找操作
BSTNode* searchBST(BSTNode* root, int key) {
    if (root == nullptr || root->key == key) {
        return root;
    }
    if (key < root->key) {
        return searchBST(root->left, key);
    } else {
        return searchBST(root->right, key);
    }
}

// 平衡二叉树的节点结构（AVL树）
struct AVLNode {
    int key;
    int height;
    AVLNode* left;
    AVLNode* right;
    AVLNode(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
};

// 获取节点高度
int getHeight(AVLNode* node) {
    return node ? node->height : 0;
}

// 更新节点高度
void updateHeight(AVLNode* node) {
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
}

// 获取平衡因子
int getBalanceFactor(AVLNode* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

// 左旋操作
AVLNode* rotateLeft(AVLNode* z) {
    AVLNode* y = z->right;
    AVLNode* T2 = y->left;

    y->left = z;
    z->right = T2;

    updateHeight(z);
    updateHeight(y);

    return y;
}

// 右旋操作
AVLNode* rotateRight(AVLNode* z) {
    AVLNode* y = z->left;
    AVLNode* T3 = y->right;

    y->right = z;
    z->left = T3;

    updateHeight(z);
    updateHeight(y);

    return y;
}

// 平衡二叉树插入操作
AVLNode* insertAVL(AVLNode* root, int key) {
    if (root == nullptr) {
        return new AVLNode(key);
    }
    if (key < root->key) {
        root->left = insertAVL(root->left, key);
    } else if (key > root->key) {
        root->right = insertAVL(root->right, key);
    } else {
        return root; // 不允许重复键
    }

    // 更新节点高度
    updateHeight(root);

    // 获取平衡因子并调整平衡
    int balance = getBalanceFactor(root);

    // 左左情况
    if (balance > 1 && key < root->left->key) {
        return rotateRight(root);
    }

    // 右右情况
    if (balance < -1 && key > root->right->key) {
        return rotateLeft(root);
    }

    // 左右情况
    if (balance > 1 && key > root->left->key) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // 右左情况
    if (balance < -1 && key < root->right->key) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// 平衡二叉树查找操作（与BST相同）
AVLNode* searchAVL(AVLNode* root, int key) {
    if (root == nullptr || root->key == key) {
        return root;
    }
    if (key < root->key) {
        return searchAVL(root->left, key);
    } else {
        return searchAVL(root->right, key);
    }
}

// （3）哈希表

// 哈希表（使用链地址法处理冲突）
class HashTable {
private:
    vector<vector<int>> table;
    int capacity;

    // 哈希函数
    int hash(int key) const {
        return key % capacity;
    }

public:
    HashTable(int size) : capacity(size) {
        table.resize(capacity);
    }

    // 插入操作
    void insert(int key) {
        int index = hash(key);
        table[index].push_back(key);
    }

    // 查找操作
    bool search(int key) const {
        int index = hash(key);
        for (int value : table[index]) {
            if (value == key) {
                return true;
            }
        }
        return false;
    }

    // 删除操作
    void remove(int key) {
        int index = hash(key);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (*it == key) {
                table[index].erase(it);
                break;
            }
        }
    }
};

// 主函数菜单式选择查找方式
int main() {
    // 初始化测试数据
    vector<int> staticData = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    vector<IndexBlock> indexTable = {
        {5, 0},
        {11, 5},
        {19, 8}
    };

    // 初始化二叉排序树
    BSTNode* bstRoot = nullptr;
    vector<int> bstData = {5, 3, 7, 2, 4, 6, 8};
    for (int num : bstData) {
        bstRoot = insertBST(bstRoot, num);
    }

    // 初始化平衡二叉树
    AVLNode* avlRoot = nullptr;
    vector<int> avlData = {9, 5, 10, 0, 6, 11, -1, 1, 2};
    for (int num : avlData) {
        avlRoot = insertAVL(avlRoot, num);
    }

    // 初始化哈希表
    HashTable hashTable(10);
    vector<int> hashData = {1, 4, 7, 11, 14, 17};
    for (int num : hashData) {
        hashTable.insert(num);
    }

    int choice, target;
    do {
        // 显示菜单
        cout << "\n===== 查找表算法演示 =====" << endl;
        cout << "1. 顺序查找" << endl;
        cout << "2. 折半查找" << endl;
        cout << "3. 分块查找" << endl;
        cout << "4. 二叉排序树查找" << endl;
        cout << "5. 平衡二叉树查找" << endl;
        cout << "6. 哈希表查找" << endl;
        cout << "0. 退出" << endl;
        cout << "请选择查找方式: ";
        cin >> choice;

        if (choice == 0) {
            break;
        }

        cout << "请输入要查找的目标值: ";
        cin >> target;

        switch (choice) {
            case 1: {
                int result = sequentialSearch(staticData, target);
                cout << "顺序查找结果: ";
                if (result != -1) {
                    cout << "找到元素 " << target << "，位置为 " << result << endl;
                } else {
                    cout << "未找到元素 " << target << endl;
                }
                break;
            }
            case 2: {
                int result = binarySearch(staticData, target);
                cout << "折半查找结果: ";
                if (result != -1) {
                    cout << "找到元素 " << target << "，位置为 " << result << endl;
                } else {
                    cout << "未找到元素 " << target << endl;
                }
                break;
            }
            case 3: {
                int result = blockSearch(staticData, indexTable, target);
                cout << "分块查找结果: ";
                if (result != -1) {
                    cout << "找到元素 " << target << "，位置为 " << result << endl;
                } else {
                    cout << "未找到元素 " << target << endl;
                }
                break;
            }
            case 4: {
                BSTNode* result = searchBST(bstRoot, target);
                cout << "二叉排序树查找结果: ";
                if (result != nullptr) {
                    cout << "找到元素 " << target << endl;
                } else {
                    cout << "未找到元素 " << target << endl;
                }
                break;
            }
            case 5: {
                AVLNode* result = searchAVL(avlRoot, target);
                cout << "平衡二叉树查找结果: ";
                if (result != nullptr) {
                    cout << "找到元素 " << target << endl;
                } else {
                    cout << "未找到元素 " << target << endl;
                }
                break;
            }
            case 6: {
                bool result = hashTable.search(target);
                cout << "哈希表查找结果: ";
                if (result) {
                    cout << "找到元素 " << target << endl;
                } else {
                    cout << "未找到元素 " << target << endl;
                }
                break;
            }
            default:
                cout << "无效的选择，请重新输入！" << endl;
        }
    } while (true);

    return 0;
}    