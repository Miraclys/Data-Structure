#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
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
    std::map<T, int> vis;
    for (int i = 0; i < inOrder.size(); ++i)
        vis[inOrder[i]] = i;
    Stack<TreeNode<T>*> s;
    TreeNode<T>* root = new TreeNode<T>(preOrder[0]);
    s.push(root);
    for (int i = 1; i < preOrder.size(); ++i) {
        TreeNode<T>* node = new TreeNode<T>(preOrder[i]);
        TreeNode<T>* parent = nullptr;
        while (!s.empty() && vis[node->value] > vis[s.top()->value]) {
            parent = s.top();
            s.pop();
        }
        if (parent) {
            parent->rightChild = node;
        } else {
            s.top()->leftChild = node;
        }
        s.push(node);
    }
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
            cur = s.top()->rightChild; // 在栈中的就是已经输出根了，所以我们再次回到 top 的时候，就是左子树已经输出完了，该输出右子树了。
            s.pop();
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
void getBracketForm(TreeNode<T>* root) {
    Stack<TreeNode<T>*> s;
    TreeNode<T>* cur = root;
    std::map<TreeNode<T>*, int> vis;
    std::map<TreeNode<T>*, int> tag; // 两个标记
    std::string bracketForm = "";
    while (!s.empty() || cur) {
        if (cur) {
            s.push(cur);
            bracketForm = bracketForm + std::to_string(cur->value);
            if (cur->leftChild || cur->rightChild) {
                bracketForm = bracketForm + "(";
                vis[cur] = 1;
            }
            cur = cur->leftChild;
        } else {
            cur = s.top();
            if (tag[cur] == 1) {
                if (vis[cur] == 1) bracketForm += ")";
                s.pop();
                cur = nullptr;
            } else {
                tag[cur] = 1;
                if (cur->leftChild && cur->rightChild) bracketForm += ",";
                cur = cur->rightChild;
            }
        }
    }
    std::cout << bracketForm;
}

int main() {
    // Input: preOrder and inOrder or postOrder and inOrder
    // Output: preOrder postOrder and bracketForm
    
    // std::vector<int> preOrder = {52, 3, 2231, 4, 712424, 6, 8};
    // std::vector<int> inOrder = {2231, 3, 4, 52, 6, 712424, 8};
    // std::vector<int> preOrder = {1, 2, 3, 4, 5};
    // std::vector<int> inOrder = {5, 4, 3, 2, 1};
    // std::vector<int> preOrder = {10, 5, 3, 7, 12};
    // std::vector<int> inOrder = {3, 5, 7, 10, 12};
    std::vector<int> preOrder = {123, 3, 4, 7, 8, 9};
    std::vector<int> inOrder = {3, 4, 123, 8, 9, 7};
    TreeNode<int>* root = buildTree(preOrder, inOrder);
    getPreOrder(root);
    std::cout << "\n";
    getPostOrder(root);
    std::cout << "\n";
    getBracketForm(root);
    return 0;
}