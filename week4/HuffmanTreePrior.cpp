#include <iostream>
#include <string>
#include <map>
#include <queue>

template <class T>
class TreeNode {
public:
    T value;
    int frequency;
    TreeNode* leftChild;
    TreeNode* rightChild;
    TreeNode() : frequency(0), leftChild(nullptr), rightChild(nullptr) {}
    TreeNode(T val, int fre) : value(val), frequency(fre), leftChild(nullptr), rightChild(nullptr) {}
};

template <class T>
struct Compare {
    bool operator()(const TreeNode<T>* x, const TreeNode<T>* y) const {
        return x->frequency > y->frequency;
    }
};

template <class T>
TreeNode<T>* buildHuffmanTree(std::map<T, int>& vis) {
    Compare<T> compare;
    std::priority_queue<TreeNode<T>*, std::vector<TreeNode<T>*>, Compare<T>> q;
    for (auto const& element : vis) {
        q.push(new TreeNode<T>(element.first, element.second));
    }
    while (q.size() > 1) {
        TreeNode<T>* fir = q.top();
        q.pop();
        TreeNode<T>* sec = q.top();
        q.pop();
        TreeNode<T>* curNode = new TreeNode<T>('\0', fir->frequency + sec->frequency);
        curNode->rightChild = sec;
        curNode->leftChild = fir;
        q.push(curNode);
    }
    return q.top();
}

template <class T>
void getHuffmanCode(TreeNode<T>* root, std::map<TreeNode<T>*, std::string>& encode, std::string code = "") {
    if (!root) return;
    if (root->value != '\0') {
        encode[root] = code;
        return;
    }
    getHuffmanCode(root->leftChild, encode, code + "0");
    getHuffmanCode(root->rightChild, encode, code + "1");
}

int main() {
    std::string str;
    std::cin >> str;
    std::map<char, int> vis;
    for (auto const& element : str) {
        ++vis[element];
    }
    TreeNode<char>* root = buildHuffmanTree(vis);
    std::map<TreeNode<char>*, std::string> encode;
    getHuffmanCode(root, encode, "");
    for (auto const& element : encode) {
        if (element.first->value != '\0')
            std::cout << element.first->value << " " << element.second << "\n";
    }
    return 0;
}