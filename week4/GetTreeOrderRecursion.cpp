#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>

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
void postOrder(TreeNode<T>* root) {
    if (root == nullptr) return ;
    postOrder(root->leftChild);
    postOrder(root->rightChild);
    std::cout << root->value << " ";
}

template<class T>
void bracketForm(TreeNode<T>* root) {
    if (root == nullptr) {
        std::cerr << "this sequence is illegal.";
        return ;
    }
    std::cout << root->value;
    int flg = 0;
    if (root->leftChild != nullptr) {
        flg = 1;
        std::cout << "(";
        bracketForm(root->leftChild);
    }
    if (root->rightChild != nullptr) {
        if (flg) {
            std::cout << ",";
        }
        flg = 1;
        bracketForm(root->rightChild);
    }
    if (flg) std::cout << ")";
}

int main() {
    // std::vector<int> preOrder = {52, 3, 2231, 4, 712424, 6, 8};
    // std::vector<int> inOrder = {2231, 3, 4, 52, 6, 712424, 8};
    std::vector<int> preOrder = {10, 5, 3, 7, 12};
    std::vector<int> inOrder = {3, 5, 7, 10, 12};
    TreeNode<int>* root = buildTree(preOrder, inOrder);
    postOrder(root);
    std::cout << "\n";
    bracketForm(root);
    std::cout << "\n";
    TreeNode<int>* newRoot;
    bracketForm(newRoot);
    return 0;
}