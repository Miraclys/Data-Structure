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
void threadTree(TreeNode<T>* root) {
    Stack<TreeNode<T>*> s;
    Stack<TreeNode<T>*> ans;
    TreeNode<T>* cur = root;
    while (!s.empty() || cur) {
        if (cur) {
            s.push(cur);
            cur = cur->leftChild;
        } else {
            cur = s.top();
            if (!ans.empty() && !ans.top()->rightChild) {
                ans.top()->rightThreaded = 1;
                ans.top()->rightChild = cur;
                // std::cout << ans.top()->value;
            }
            // std::cout << cur->value << " ";
            ans.push(cur);
            // std::cout << cur->value << " ";
            s.pop();
            cur = cur->rightChild;
        }
    } 
    // while (!ans.empty()) {
    //     if (ans.top()->rightChild) 
    //         std::cout << ans.top()->rightThreaded << " " << ans.top()->value << " " << ans.top()->rightChild->value << "\n";
    //     ans.pop();
    // }
}

template<class T>
void inOrderTraversal(TreeNode<T>* root) {
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
            while (current && current->leftChild) {
                current = current->leftChild;
            }
        }
    }
}

int main() {
    std::vector<int> preOrder = {52, 3, 2231, 4, 712424, 6, 8};
    std::vector<int> inOrder = {2231, 3, 4, 52, 6, 712424, 8};
    TreeNode<int>* root = buildTree(preOrder, inOrder);
    threadTree(root);
    inOrderTraversal(root);
    return 0; 
}