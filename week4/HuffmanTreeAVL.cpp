#include <iostream>
#include <algorithm>
#include <utility>
#include <string>
#include <string.h>
#include "../Map.hpp"
#include "../AVLTree.hpp" // 假设你的 AVLTree 头文件是这个
#include "../Heap.hpp"

template<class T>
class TreeNode {    
    public:
        T value;
        int frequency;
        TreeNode* leftChild;
        TreeNode* rightChild;
        TreeNode() : frequency(0), leftChild(nullptr), rightChild(nullptr) {}
        TreeNode(T val, int fre) : value(val), frequency(fre), leftChild(nullptr), rightChild(nullptr) {}
};

template<class T>
struct Compare {
    bool operator()(const TreeNode<T>* x, const TreeNode<T>* y) const {
        return x->frequency < y->frequency;
    };
};

template<class T>
TreeNode<T>* buildHuffmanTree(Map<T, int>& vis) {
    Compare<T> compare;
    Heap<TreeNode<T>*> q(compare);
    MapIterator<T, int> it = vis.begin();
    // while (!it.isEnd()) {
    //     q.insert(new TreeNode(it.getCurrent().first, it.getCurrent().second));
    //     it.next();
    // }
    int flg = 1, end = vis.tree.root->getSize();
    for (it = vis.begin(); flg <= end; ++it, ++flg) {
        q.insert(new TreeNode(it.current->value.first, it.current->value.second));
        // std::cout << "ads";
    }
    while (q.size() != 1) {
        TreeNode<T>* fir = q.top();
        q.pop();
        TreeNode<T>* sec = q.top();
        q.pop();
        TreeNode<T>* curNode = new TreeNode('\0', fir->frequency + sec->frequency);
        curNode->rightChild = sec;
        curNode->leftChild = fir;
        q.insert(curNode);
    }
    return q.top();
}

template <class T>
void getHuffmanCode(TreeNode<T>* root, Map<TreeNode<T>*, std::string>& encode, std::string code) {
    if (!root) return;
    if (root->value != '\0') {
        encode.insert(std::pair<TreeNode<T>*, std::string>(root, code));
        return;
    }
    getHuffmanCode(root->leftChild, encode, code + "0");
    getHuffmanCode(root->rightChild, encode, code + "1");
}

template<class T>
void traversal(TreeNode<T>* cur) {
    if (!cur) return;
    std::cout << cur->value << " ";
    traversal(cur->leftChild);
    traversal(cur->rightChild);
}

int main() {
    //  AAABAACCD
    // A 1
    // C 00
    // B 010
    // D 011
    auto compare = [](const std::pair<char, int>& x, const std::pair<char, int>& y) {
        if (int(x.first) < int(y.first)) return -1;
        else if (int(x.first) == int(y.first)) return 0;
        else return 1;
    };
    std::string str;
    std::cin >> str;
    Map<char, int> vis(compare);
    for (auto const& element : str) {
        if (vis.contain(element)) {
            vis.insert(std::pair<char, int>(element, vis.find(element) + 1));
        } else {
            vis.insert(std::pair<char, int>(element, 1));
        }
    }
    // int flg = 1, end = vis.tree.root->getSize();
    // std::cout << "end: " << end << "\n";
    // for (MapIterator it = vis.begin(); flg <= end; ++it, ++flg) {
    //     std::cout << (*(it)).first << " " << (*(it)).second << "\n";
    // }
    TreeNode<char>* root = buildHuffmanTree(vis);
    auto compareEncode = [](const std::pair<TreeNode<char>*, std::string>& x, const std::pair<TreeNode<char>*, std::string>& y) {
        if (x.second < y.second) return -1;
        else if (x.second == y.second) return 0;
        else return 1;
    };
    Map<TreeNode<char>*, std::string> encode(compareEncode);
    encode.insert(std::pair<TreeNode<char>*, std::string>(root, ""));
    // traversal(root);
    // std::cout << "\n";
    getHuffmanCode(root, encode, "");
    MapIterator<TreeNode<char>*, std::string> it = encode.begin();
    int flg = 1, end = encode.tree.root->getSize();
    for (it = encode.begin(); flg <= end; ++it, ++flg) {
        if ((*(it)).second[0] != '\0') std::cout << (*(it)).first->value << " " << (*(it)).second << "\n";
    }
    return 0;
}
