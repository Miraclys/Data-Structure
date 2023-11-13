#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "../Stack.hpp"

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
void createInorderThreadedBinaryTree(TreeNode<T>* root) {
    if (!root) return;

    Stack<TreeNode<T>*> stack;
    TreeNode<T>* current = root;
    TreeNode<T>* prev = nullptr;

    while (current || !stack.empty()) {
        while (current) {
            stack.push(current);
            current = current->leftChild;
        }

        current = stack.top();
        stack.pop();

        if (prev && !current->leftChild) {
            current->leftChild = prev;
            current->leftThreaded = true;
        }

        if (prev && !prev->rightChild) {
            prev->rightChild = current;
            prev->rightThreaded = true;
        }

        prev = current;
        current = current->rightChild;
    }
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
            while (current && !current->leftThreaded) {
                current = current->leftChild;
            }
        }
    }
}

template<class T>
void transInOrderTraversal(TreeNode<T>* root) {
    TreeNode<T>* curNode = root;
    TreeNode<T>* target = nullptr;
    while (curNode) {
        target = curNode;
        if (curNode->rightThreaded) {
            curNode = curNode->rightChild;
        } else {
            curNode = curNode->rightChild;
            while (curNode && !curNode->leftThreaded) {
                curNode = curNode->leftChild;
            }
        }
    }
    curNode = target;
    while (curNode) {
        std::cout << curNode->value << " ";
        if (curNode->leftThreaded) {
            curNode = curNode->leftChild;
        } else {
            curNode = curNode->leftChild;
            while (curNode && !curNode->rightThreaded) {
                curNode = curNode->rightChild;
            }
        }
    }
}

int main() {
    std::vector<int> preOrder = {52, 3, 2231, 4, 712424, 6, 8};
    std::vector<int> inOrder = {2231, 3, 4, 52, 6, 712424, 8};
    TreeNode<int>* root = buildTree(preOrder, inOrder);
    createInorderThreadedBinaryTree(root);
    inOrderTraversal(root);
    // threadTree(root);
    // printPre(root);
    std::cout << "\n";
    transInOrderTraversal(root);
    return 0; 
}