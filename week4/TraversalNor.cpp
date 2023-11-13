#include <iostream>
#include <vector>
#include <algorithm>
#include "Stack.hpp"

template<class T>
class TreeNode {
    public:
        T value;
        TreeNode* leftChild;
        TreeNode* rightChild;
        TreeNode(T val): value(val), leftChild(nullptr), rightChild(nullptr) {}
        TreeNode(T val, TreeNode* lc, TreeNode rc): value(val), leftChild(lc), rightChild(rc) {}
};

template<class T>
TreeNode<T>* buildTree(std::vector<T>& preOrder, std::vector<T>& inOrder) {
    if (preOrder.empty() || inOrder.empty()) {
        return nullptr;
    }
    T rootValue = preOrder[0];
    TreeNode<T>* root = new TreeNode<T>(rootValue);

    auto rootIndex = std::find(inOrder.begin(), inOrder.end(), rootValue);
    if (rootIndex == inOrder.end()) {
        throw std::runtime_error("The traversal result is not valid.");
    }
    std::vector<T> leftInOrder(inOrder.begin(), rootIndex);
    std::vector<T> rightInOrder(rootIndex + 1, inOrder.end());
    std::vector<T> leftPreOrder(preOrder.begin() + 1, preOrder.begin() + 1 + leftInOrder.size());
    std::vector<T> rightPreOrder(preOrder.begin() + 1 + leftInOrder.size(), preOrder.end());

    root->leftChild = buildTree(leftPreOrder, leftInOrder);
    root->rightChild = buildTree(rightPreOrder, rightInOrder);

    return root;
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
    char tag[1005] = {'0'};
    while (!s.empty() || cur) {
        if (cur) {
            s.push(cur);
            cur = cur->leftChild;
        } else {
            cur = s.top();
            if (tag[cur->value] == '1') {
                std::cout << cur->value << " ";
                s.pop();
                cur = nullptr;
            } else {
                tag[cur->value] = '1';
                cur = cur->rightChild;
            }
        }
    }
}

int main() {
    // 5, 3, 2, 4, 7, 6, 8
    // 2, 3, 4, 5, 6, 7, 8

    // 10, 5, 3, 7, 12
    // 3, 5, 7, 10, 12

    // 1, 2, 3, 4, 5
    // 5, 4, 3, 2, 1

    // 52, 3, 2231, 4, 712424, 6, 8
    // 2231, 3, 4, 52, 6, 712424, 8
    std::vector<int> preOrder = {52, 3, 2231, 4, 712424, 6, 8};
    std::vector<int> inOrder = {2231, 3, 4, 52, 6, 712424, 8};
    TreeNode<int>* root = buildTree(preOrder, inOrder);
    getPreOrder(root);
    std::cout << "\n";
    getPostOrder(root);
    return 0;
}