#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "Stack.hpp"

template<class T>
class TreeNode {
    public:
        T value;
        TreeNode* leftChild;
        TreeNode* rightChild;
        bool leftThreaded;
        bool rightThreaded;
        TreeNode(T val) : value(val), leftChild(nullptr), rightChild(nullptr), 
            leftThreaded(false), rightThreaded(false) {}
};

template<class T>
TreeNode<T>* buildTree(std::vector<T> preOrder, std::vector<T> inOrder) {
    TreeNode<T>* root = new TreeNode(preOrder[0]);
    Stack<TreeNode<T>*> s;
    std::map<T, int> vis;
    for (int i = 0; i < inOrder.size(); ++i)
        vis[inOrder[i]] = i;
    s.push(root);
    for (int i = 1; i < preOrder.size(); ++i) {
        TreeNode<T>* curNode = new TreeNode(preOrder[i]);
        TreeNode<T>* parent = nullptr;
        while (!s.empty() && vis[curNode->value] > vis[s.top()->value]) {
            parent = s.top();
            s.pop();
        }
        if (parent) {
            parent->rightChild = curNode;
        } else {
            s.top()->leftChild = curNode;
        }
        s.push(curNode);
    }
    return root;
}

template<class T>
void threadBinaryTree(TreeNode<T>* root, TreeNode<T>*& prev) {
    if (!root) return ;
    threadBinaryTree(root->leftChild, prev);
    if (root->leftChild == nullptr && prev) {
        root->leftChild = prev;
        root->leftThreaded = true;
    }
    if (prev != nullptr && prev->rightChild == nullptr) {
        prev->rightChild = root;
        prev->rightThreaded = true;
    }
    prev = root;
    threadBinaryTree(root->rightChild, prev);
}

template<class T>
void inorderTraversal(TreeNode<T>* root) {
    if (!root) return;

    TreeNode<T>* current = root;

    while (current->leftChild) {
        current = current->leftChild;
    }

    while (current) {
        std::cout << current->value << " ";

        if (current->rightThreaded) {
            current = current->rightChild;
        } else {
            current = current->rightChild;
            while (current && !current->leftThreaded) {
                current = current->leftChild;
            }
        }
    }
}

// template<class T>
// void printPre(TreeNode<T>* root) {
//     if (!root) return ;
//     std::cout << root->value << " " << root->rightThreaded << " " << root->rightChild->value << "\n";
//     if (!root->leftThreaded) printPre(root->leftChild);
//     if (!root->rightThreaded) printPre(root->rightChild);
// }

int main() {
    // std::vector<int> preOrder = {52, 3, 2231, 4, 712424, 6, 8};
    // std::vector<int> inOrder = {2231, 3, 4, 52, 6, 712424, 8};
    // std::vector<int> preOrder = {10, 5, 3, 7, 12};
    // std::vector<int> inOrder = {3, 5, 7, 10, 12};
    // std::vector<int> preOrder = {1, 2, 3, 4, 5};
    // std::vector<int> inOrder = {5, 4, 3, 2, 1};
    std::vector<int> preOrder = {123, 3, 4, 7, 8, 9};
    std::vector<int> inOrder = {3, 4, 123, 8, 9, 7};
    TreeNode<int>* root = buildTree(preOrder, inOrder);
    TreeNode<int>* prev = nullptr;
    threadBinaryTree(root, prev);
    inorderTraversal(root);
    // printPre(root);
    return 0;
}