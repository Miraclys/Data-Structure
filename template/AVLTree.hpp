#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <iostream>
#include <vector>
#include <functional>

template<class K, class V>
class TreeNode {
    public:
        std::pair<K, V> value;
        int frequency, size, height;
        TreeNode<K, V>* leftChild;
        TreeNode<K, V>* rightChild;
        int getSize() const;
        int getHeight() const;
        TreeNode(std::pair<K, V> val) 
            : value(val)
            , frequency(1)
            , size(1)
            , height(1)
            , leftChild(nullptr)
            , rightChild(nullptr) {}
};

template<class K, class V>
int TreeNode<K, V>::getSize() const {
    if (!this) return 0;
    return this->size;
}

template<class K, class V>
int TreeNode<K, V>::getHeight() const {
    if (!this) return 0;
    return this->height;
}

template<class K, class V>
class Tree {
    public:
        std::function<int(const std::pair<K, V>&, const std::pair<K, V>&)> compare;
        TreeNode<K, V>* root;
        void insert(std::pair<K, V> val);
        void insertNode(TreeNode<K, V>*& cur, std::pair<K, V> val);
        void removeNode(TreeNode<K, V>*& cur, std::pair<K, V> val);
        void remove(std::pair<K, V> val);
        int getRank(std::pair<K, V> val) const;
        int Rank(TreeNode<K, V>* cur, std::pair<K, V> val) const;
        std::pair<K, V> getPre(std::pair<K, V> val) const ;
        std::pair<K, V> Pre(TreeNode<K, V>* cur, std::pair<K, V> val) const;
        std::pair<K, V> getSuf(std::pair<K, V> val) const;
        std::pair<K, V> Suf(TreeNode<K, V>* cur, std::pair<K, V> val) const;
        std::pair<K, V> getVal(int val) const;
        std::pair<K, V> Val(TreeNode<K, V>* cur, int val) const;
        void leftRight(TreeNode<K, V>*& cur);
        void rightLeft(TreeNode<K, V>*& cur);
        void leftPlus(TreeNode<K, V>*& cur);
        void rightPlus(TreeNode<K, V>*& cur);
        void update(TreeNode<K, V>*& cur);
        Tree() : root(nullptr) {}
        Tree(std::function<int(const std::pair<K, V>&, const std::pair<K, V>&)> comp) : compare(comp), root(nullptr) {}
};

template<class K, class V>
void Tree<K, V>::insert(std::pair<K, V> val) {
    insertNode(root, val);
}

template<class K, class V>
void Tree<K, V>::insertNode(TreeNode<K, V>*& cur, std::pair<K, V> val) {
    if (!cur) {
        cur = new TreeNode<K, V>(val);
        return ;
    }
    if (compare(val, cur->value) == -1) {
        insertNode(cur->leftChild, val);
        update(cur);
        if (cur->leftChild->getHeight() - cur->rightChild->getHeight() == 2) {
            if (compare(val, cur->leftChild->value) == -1) {
                leftPlus(cur);
            } else {
                leftRight(cur);
            }
        }
    } else if (compare(val, cur->value) == 1) {
        insertNode(cur->rightChild, val);
        update(cur);
        if (cur->rightChild->getHeight() - cur->leftChild->getHeight() == 2) {
            if (compare(val, cur->rightChild->value) == -1) {
                rightLeft(cur);
            } else {
                rightPlus(cur);
            }
        }
    } else {
        cur->frequency = cur->frequency + 1;
        cur->size = cur->size + 1;
        update(cur);
        return ;
    }
    update(cur);
}

template<class K, class V>
void Tree<K, V>::remove(std::pair<K, V> val) {
    removeNode(root, val);
}

template<class K, class V>
void Tree<K, V>::removeNode(TreeNode<K, V>*& cur, std::pair<K, V> val) {
    if (!cur) return ;  
    if (compare(cur->value, val) == 0) {
        if (cur->frequency > 1) {
            cur->frequency = cur->frequency - 1;
            update(cur);
            return ;
        } else {
            if (cur->leftChild && cur->rightChild) {
                TreeNode<K, V>* q = cur->rightChild;
                while (q->leftChild)
                    q = q->leftChild;
                cur->frequency = q->frequency;
                cur->value = q->value;
                q->frequency = 1;
                removeNode(cur->rightChild, q->value);
                update(cur);
                if (cur->leftChild->getHeight() - cur->rightChild->getHeight() == 2) {
                    if (cur->leftChild->leftChild->getHeight() >= cur->leftChild->rightChild->getHeight()) {
                        leftPlus(cur);
                    } else {
                        leftRight(cur);
                    }
                }
            } else {
                TreeNode<K, V>* q = cur;
                if (cur->leftChild) cur = cur->leftChild;
                else if (cur->rightChild) cur = cur->rightChild;
                else cur = nullptr;
                delete q;
                q = nullptr;
                return ;
            }
        }
    } else if (compare(val, cur->value) == -1) {
        removeNode(cur->leftChild, val);
        update(cur);
        if (cur->rightChild->getHeight() - cur->leftChild->getHeight() == 2) {
            if (cur->rightChild->rightChild->getHeight() >= cur->rightChild->leftChild->getHeight()) {
                rightPlus(cur);
            } else {
                rightLeft(cur);
            }
        }
    } else {
        removeNode(cur->rightChild, val);
        update(cur);
        if (cur->leftChild->getHeight() - cur->rightChild->getHeight() == 2) {
            if (cur->leftChild->leftChild->getHeight() >= cur->leftChild->rightChild->getHeight()) {
                leftPlus(cur);
            } else {
                leftRight(cur);
            }
        }
    }
    // if (cur == nullptr) return ;
    update(cur);
}

template<class K, class V>
int Tree<K, V>::getRank(std::pair<K, V> val) const {
    return Rank(root, val);
}

template<class K, class V>
int Tree<K, V>::Rank(TreeNode<K, V>* cur, std::pair<K, V> val) const {
    if (!cur) return 1;
    if (compare(val, cur->value) == -1) return Rank(cur->leftChild, val);
    else if (compare(val, cur->value) == 1) return cur->leftChild->getSize() + cur->frequency + Rank(cur->rightChild, val);
    else return cur->leftChild->getSize() + 1;
}

template<class K, class V>
std::pair<K, V> Tree<K, V>::getPre(std::pair<K, V> val) const {
    return Pre(root, val);
}

template<class K, class V>
std::pair<K, V> Tree<K, V>::Pre(TreeNode<K, V>* cur, std::pair<K, V> val) const {
    std::pair<K, V> ans;
    int flg = 0;
    while (cur) {
        if (compare(cur->value, val) == 0) {
            if (cur->leftChild) {
                cur = cur->leftChild;
                while (cur->rightChild)
                    cur = cur->rightChild;
                return cur->value;
            }
        }
        if (compare(cur->value, val) == -1) {
            if (!flg) {
                flg = 1;
                ans = cur->value;
            } else if (compare(cur->value, ans) == 1) {
                ans = cur->value;
            }
        }
        cur = compare(cur->value, val) == -1 ? cur->rightChild : cur->leftChild;
    }
    return ans;
}

template<class K, class V>
std::pair<K, V> Tree<K, V>::getSuf(std::pair<K, V> val) const {
    return Suf(root, val);
}

template<class K, class V>
std::pair<K, V> Tree<K, V>::Suf(TreeNode<K, V>* cur, std::pair<K, V> val) const {
    std::pair<K, V> ans;
    int flg = 0;
    while (cur) {
        if (compare(cur->value, val) == 0) {
            if (cur->rightChild) {
                cur = cur->rightChild;
                while (cur->leftChild)
                    cur = cur->leftChild;
                return cur->value;
            }
        }
        if (compare(val, cur->value) == -1) {
            if (!flg) {
                flg = 1;
                ans = cur->value;
            } else if (compare(cur->value, ans) == -1) {
                ans = cur->value;
            }
        }
        cur = compare(cur->value, val) == 1 ? cur->leftChild : cur->rightChild;
    }
    return ans;
}

template<class K, class V>
std::pair<K, V> Tree<K, V>::getVal(int val) const {
    return Val(root, val);
}

template<class K, class V>
std::pair<K, V> Tree<K, V>::Val(TreeNode<K, V>* cur, int val) const {
    if (cur->leftChild->getSize() >= val) return Val(cur->leftChild, val);
    else if (cur->leftChild->getSize() + cur->frequency >= val) return cur->value;
    else return Val(cur->rightChild, val - cur->leftChild->getSize() - cur->frequency);
}

template<class K, class V>
void Tree<K, V>::leftRight(TreeNode<K, V>*& cur) {
    rightPlus(cur->leftChild);
    leftPlus(cur);
}

template<class K, class V>
void Tree<K, V>::rightLeft(TreeNode<K, V>*& cur) {
    leftPlus(cur->rightChild);
    rightPlus(cur);
}

template<class K, class V>
void Tree<K, V>::leftPlus(TreeNode<K, V>*& cur) {
    TreeNode<K, V>* q = cur->leftChild;
    cur->leftChild = q->rightChild;
    q->rightChild = cur;
    update(cur);
    update(q);
    cur = q;
}

template<class K, class V>
void Tree<K, V>::rightPlus(TreeNode<K, V>*& cur) {
    TreeNode<K, V>* q = cur->rightChild;
    cur->rightChild = q->leftChild;
    q->leftChild = cur;
    update(cur);
    update(q);
    cur = q;
}

template<class K, class V>
void Tree<K, V>::update(TreeNode<K, V>*& cur) {
    cur->size = cur->leftChild->getSize() + cur->rightChild->getSize() + cur->frequency;
    cur->height = std::max(cur->rightChild->getHeight(), cur->leftChild->getHeight()) + 1;
}

#endif