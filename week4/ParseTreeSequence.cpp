#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <string.h>
#include <map>
#include "Stack.hpp"
#include "Queue.hpp"

template<class T>
class TreeNode {
    public:
        T value;
        TreeNode* leftChild;
        TreeNode* rightChild;
        TreeNode(T val): value(val), leftChild(nullptr), rightChild(nullptr) {}
        TreeNode(T val, TreeNode* lc, TreeNode* rc): value(val), leftChild(lc), rightChild(rc) {}
};

template<class T>
void addChild(TreeNode<T>* cur, T curNum) {
    if (!cur->leftChild) {
        cur->leftChild = new TreeNode<T>(curNum);
    } else {
        cur->rightChild = new TreeNode<T>(curNum);
    }
}

template<class T>
TreeNode<T>* parseTreeSequence(std::string str) {
    Stack<TreeNode<T>*> s;
    TreeNode<T>* root = new TreeNode<T>(0);  // 创建虚拟根节点
    s.push(root);
    int length = str.length();
    int curNum = 0;
    bool isParsingNumber = false;
    for (int i = 0; i < length; ++i) {
        if (isdigit(str[i])) {
            isParsingNumber = true;
            curNum = curNum * 10 + int(str[i] - '0');
        } else if (str[i] == '(') {
            TreeNode<T>* curNode = new TreeNode<T>(curNum);
            if (!s.top()->leftChild) {
                s.top()->leftChild = curNode;
            } else {
                s.top()->rightChild = curNode;
            }
            s.push(curNode);
            curNum = 0;
            isParsingNumber = false;
        } else if (str[i] == ')') {
            if (isParsingNumber) {
                TreeNode<T>* curNode = new TreeNode<T>(curNum);
                if (!s.top()->leftChild) {
                    s.top()->leftChild = curNode;
                } else {
                    s.top()->rightChild = curNode;
                }
                curNum = 0;
                isParsingNumber = false;
            }
            s.pop();
        } else if (str[i] == ',') {
            if (!isdigit(str[i - 1])) continue;
            TreeNode<T>* curNode = new TreeNode<T>(curNum);
            s.top()->leftChild = curNode;
            curNum = 0;
            isParsingNumber = false;
        }
    }
    TreeNode<T>* result = root->leftChild;
    delete root;
    return result;
}

template<class T>
void getPreOrder(TreeNode<T>* root) {
    TreeNode<T>* cur = root;
    Stack<TreeNode<T>*> s;
    while (!s.empty() || cur) {
        if (cur != nullptr) {
            std::cout << cur->value << " ";
            s.push(cur);
            cur = cur->leftChild;
        } else {
            cur = s.top();
            s.pop();
            cur = cur->rightChild;
        }
    }
}

template<class T>
void getPostOrder(TreeNode<T>* root) {
    TreeNode<T>* cur = root;
    Stack<TreeNode<T>*> s;
    std::map<TreeNode<T>*, char> tag;
    while (!s.empty() || cur) {
        if (cur) {
            s.push(cur);
            cur = cur->leftChild;
        } else {
            cur = s.top();
            if (tag[cur] == '1') {
                std::cout << cur->value << " ";
                s.pop();
                cur = nullptr;
            } else {
                tag[cur] = '1';
                cur = cur->rightChild;
            }
        }
    }
}

template<class T>
void getInOrder(TreeNode<T>* root) {
    Stack<TreeNode<T>*> s;
    TreeNode<T>* cur = root;
    while (!s.empty() || cur) {
        if (cur) {
            s.push(cur);
            cur = cur->leftChild;
        } else {
            cur = s.top()->rightChild;
            std::cout << s.top()->value << " ";
            s.pop();
        }
    }
}

template<class T>
void getLayerOrder(TreeNode<T>* root) {
    Queue<TreeNode<T>*> q;
    q.enqueue(root);
    while (!q.empty()) {
        TreeNode<T>* cur = q.first();
        q.dequeue();
        std::cout << cur->value << " ";
        if (cur->leftChild) q.enqueue(cur->leftChild);
        if (cur->rightChild) q.enqueue(cur->rightChild);
    }
    return ;
}

int main() {
    // Output:
    // preOrder: 52 3 2231 4 712424 6 8 
    // postOrder: 2231 4 3 6 8 712424 52 
    // inOrder: 2231 3 4 52 6 712424 8
    // layerOrder: 52 3 712424 2231 4 6 8
    std::string s = "52(3(2231,4),712424(6,8))";
    TreeNode<int>* root = parseTreeSequence<int>(s);
    std::cout << "preOrder: ";
    getPreOrder(root);
    std::cout << "\npostOrder: ";
    getPostOrder(root);
    std::cout << "\ninOrder: ";
    getInOrder(root);
    std::cout << "\nlayerOrder: ";
    getLayerOrder(root);
    return 0;
}