#ifndef REDBLACKTREE_HPP
#define REDBLACKTREE_HPP
#define RED 0
#define BLACK 1

#include <iostream>
#include <algorithm>
#include <string>
#include <utility>

template<class K, class V>
class RBTreeNode {
    public:
        std::pair<K, V> value;
        RBTreeNode* parent;
        RBTreeNode* leftChild;
        RBTreeNode* rightChild;
        int frequency;
        int size;
        bool color;
        RBTreeNode(std::pair<K, V> val)
            : value(val)
            , parent(nullptr)
            , leftChild(nullptr)
            , rightChild(nullptr)
            , frequency(1)
            , size(1) 
            , color(RED) {}
        RBTreeNode()
            : parent(nullptr)
            , leftChild(nullptr)
            , rightChild(nullptr)
            , frequency(0)
            , size(0)
            , color(RED) {}
        int getSize() const {
            if (!this) return 0;
            else return this->size;
        }
};

template<class K, class V>
class RBTree {
    public:
        RBTreeNode<K, V>* root;
        RBTree() : root(nullptr) {}
        bool insert(std::pair<K, V>);
        bool remove(std::pair<K, V>);
        void inOrder();
        int getRank(std::pair<K, V>);
        int Rank(RBTreeNode<K, V>*, std::pair<K, V>);
        std::pair<K, V> getVal(int) const;
        std::pair<K, V> Val(RBTreeNode<K, V>*, int) const;
        std::pair<K, V> getPre(K) const;
        std::pair<K, V> Pre(K) const;
        std::pair<K, V> getSuf(K) const;
        std::pair<K, V> Suf(K) const;
        void leftRotate(RBTreeNode<K, V>*);
        void rightRotate(RBTreeNode<K, V>*);
        void leftRightRotate(RBTreeNode<K, V>*);
        void rightLeftRotate(RBTreeNode<K, V>*);
        void inOrder(RBTreeNode<K, V>*);
        void solveDoubleRed(RBTreeNode<K, V>*, RBTreeNode<K, V>*);
        void solveDoubleBlack(RBTreeNode<K, V>*, RBTreeNode<K, V>*);
        void update(RBTreeNode<K, V>*&);
};

template<class K, class V>
bool RBTree<K, V>::insert(std::pair<K, V> val) { // 先添加后修复
    if (!root) {
        root = new RBTreeNode<K, V>(val);
        root->color = BLACK;
        return true;
    }
    RBTreeNode<K, V>* cur = root;
    RBTreeNode<K, V>* parent = nullptr;
    int flg = 0;
    while (cur) {
        if (val.first < cur->value.first) {
            parent = cur;
            cur = cur->leftChild;
        } else if (val.first > cur->value.first) {
            parent = cur;
            cur = cur->rightChild;
        } else {
            cur->frequency++;
            flg = 1;
            break;
        }
    }
    if (!flg) {
        cur = new RBTreeNode<K, V>(val);
        if (cur->value.first < parent->value.first) {
            parent->leftChild = cur;
        } else {
            parent->rightChild = cur;
        }
        cur->parent = parent;
        solveDoubleRed(cur, parent);
    }
    RBTreeNode<K, V>* updateNode = cur->parent;
    while (updateNode) {
        update(updateNode);
        updateNode = updateNode->parent;
    }
    root->color = BLACK;
    return true;
}

template<class K, class V>
void RBTree<K, V>::solveDoubleRed(RBTreeNode<K, V>* cur, RBTreeNode<K, V>* parent) {
    while (parent && parent->color == RED) { // 我们的 cur 始终是红色的，只要 parent 不是红色的，就修复完毕了
        RBTreeNode<K, V>* grand = parent->parent;
        if (parent == grand->leftChild) {
            RBTreeNode<K, V>* uncle = grand->rightChild;
            if (uncle && uncle->color == RED) {
                uncle->color = BLACK;
                parent->color = BLACK;
                grand->color = RED;
                cur = grand;
                parent = grand->parent;
            } else {
                if (cur == parent->leftChild) {
                    rightRotate(grand);
                    grand->color = RED;
                    parent->color = BLACK;
                } else {
                    leftRightRotate(grand);
                    grand->color = RED;
                    cur->color = BLACK;
                }
                break;
            }
        } else {
            RBTreeNode<K, V>* uncle = grand->leftChild;
            if (uncle && uncle->color == RED) {
                uncle->color = BLACK;
                parent->color = BLACK;
                grand->color = RED;
                cur = grand;
                parent = grand->parent;
            } else {
                if (cur == parent->rightChild) {
                    leftRotate(grand);
                    grand->color = RED;
                    parent->color = BLACK;
                } else {
                    rightLeftRotate(grand);
                    grand->color = RED;
                    cur->color = BLACK;
                }
                break;
            }
        }
    }
}

template<class K, class V>
bool RBTree<K, V>::remove(std::pair<K, V> val) { // 先修复后删除
    RBTreeNode<K, V>* parent = nullptr;
    RBTreeNode<K, V>* cur = root;
    RBTreeNode<K, V>* delPos = nullptr;
    RBTreeNode<K, V>* delParentPos = nullptr;
    while (cur) {
        if (cur->value.first > val.first) {
            parent = cur;
            cur = cur->leftChild;
        } else if (cur->value.first < val.first) {
            parent = cur;
            cur = cur->rightChild;
        } else {
            if (cur->frequency == 1) {
                if (cur->leftChild == nullptr) {
                    if (cur == root) {
                        root = cur->rightChild;
                        if (root) {
                            root->parent = nullptr;
                            root->color = BLACK;
                        }
                        delete cur;
                        return true;
                    } else {
                        delParentPos = cur->parent;
                        delPos = cur;
                    }
                    break;
                } else if (cur->rightChild == nullptr) {
                    if (cur == root) {
                        root = cur->leftChild;
                        if (root) {
                            root->parent = nullptr;
                            root->color = BLACK;
                        }
                        delete cur;
                        return true;
                    } else {
                        delParentPos = cur->parent;
                        delPos = cur;
                    }
                    break;
                } else {
                    RBTreeNode<K, V>* minParent = cur;
                    RBTreeNode<K, V>* minRight = cur->rightChild;
                    while (minRight->leftChild) {
                        minParent = minRight;
                        minRight = minRight->leftChild;
                    }
                    cur->value = minRight->value;
                    delParentPos = minParent;
                    delPos = minRight;
                    break;
                }
            } else {
                cur->frequency = cur->frequency - 1;
                cur->size = cur->size - 1;
                cur = cur->parent;
                while (cur) {
                    update(cur);
                    cur = cur->parent;
                }
                return true;
            }
        }
    }
    if (delPos == nullptr) {
        return false;
    }
    solveDoubleBlack(delPos, delParentPos);
    RBTreeNode<K, V>* updateNode = delPos->parent;
    delPos->frequency = 0;
    delPos->size = 0;
    while (updateNode) {
        update(updateNode);
        updateNode = updateNode->parent;
    }
    if (delPos->leftChild == nullptr) {
        if (delPos == delParentPos->leftChild) {
            delParentPos->leftChild = delPos->rightChild;
            if (delPos->rightChild)
                delPos->rightChild->parent = delParentPos;
        } else {
            delParentPos->rightChild = delPos->rightChild;
            if (delPos->rightChild)
                delPos->rightChild->parent = delParentPos;
        }
    } else {
        if (delPos == delParentPos->leftChild) {
            delParentPos->leftChild = delPos->leftChild;
            if (delPos->leftChild)
                delPos->leftChild->parent = delParentPos;
        } else {
            delParentPos->rightChild = delPos->leftChild;
            if (delPos->leftChild) 
                delPos->leftChild->parent = delParentPos;
        }
    }
    delete delPos;
    return true;
}

template<class K, class V>
void RBTree<K, V>::solveDoubleBlack(RBTreeNode<K, V>* cur, RBTreeNode<K, V>* parent) {
    if (cur->color == BLACK) {
        if (cur->leftChild) {
            cur->leftChild->color = BLACK;
        } else if (cur->rightChild) {
            cur->rightChild->color = BLACK;
        } else {
            while (cur != root) {
                if (cur == parent->leftChild) {
                    RBTreeNode<K, V>* brother = parent->rightChild;
                    if (brother->color == RED) {
                        parent->color = RED;
                        brother->color = BLACK;
                        leftRotate(parent);
                        brother = parent->rightChild;
                    }
                    if (((brother->leftChild == nullptr) || (brother->leftChild->color == BLACK))
                    && ((brother->rightChild == nullptr) || (brother->rightChild->color == BLACK))) {
                        // 兄弟节点没有红色子节点
                        brother->color = RED;
                        if (parent->color == RED) {
                            parent->color = BLACK;
                            break;
                        }// 子节点没有红色的就看它父亲了
                        cur = parent;
                        parent = cur->parent;
                    } else {
                        // 兄弟节点有红色子节点
                        if ((brother->rightChild == nullptr) || (brother->rightChild->color == BLACK)) {
                            brother->leftChild->color = BLACK;
                            brother->color = RED;
                            rightRotate(brother);
                            brother = parent->rightChild;
                        }
                        brother->color = parent->color;
                        parent->color = BLACK;
                        brother->rightChild->color = BLACK;
                        leftRotate(parent);
                        break;
                    }
                } else {
                    RBTreeNode<K, V>* brother = parent->leftChild;
                    if (brother && brother->color == RED) {
                        brother->color = BLACK;
                        parent->color = RED;
                        rightRotate(parent);
                        brother = parent->leftChild;
                    }
                    if (((brother->leftChild == nullptr) || (brother->leftChild->color == BLACK))
                    && ((brother->rightChild == nullptr) || (brother->rightChild->color == BLACK))) {
                        brother->color = RED;
                        if (parent->color == RED) {
                            parent->color = BLACK;
                            break;
                        }
                        cur = parent;
                        parent = cur->parent;
                    } else {
                        if ((brother->leftChild == nullptr) || (brother->leftChild->color == BLACK)) {
                            brother->rightChild->color = BLACK;
                            brother->color = RED;
                            leftRotate(brother);
                            brother = parent->leftChild;
                        }
                        brother->color = parent->color;
                        parent->color = BLACK;
                        brother->leftChild->color = BLACK;
                        rightRotate(parent);
                        break;
                    }
                }
            }
        }
    }
}

template<class K, class V>
void RBTree<K, V>::inOrder() {
    inOrder(root);
    std::cout << "\n";
}

template<class K, class V>
void RBTree<K, V>::inOrder(RBTreeNode<K, V>* cur) {
    if (!cur)
        return ;
    inOrder(cur->leftChild);
    std::cout << cur->value.first << " ";
    inOrder(cur->rightChild);
}

template<class K, class V>
int RBTree<K, V>::getRank(std::pair<K, V> val) {
    return Rank(root, val);
}

template<class K, class V>
int RBTree<K, V>::Rank(RBTreeNode<K, V>* cur, std::pair<K, V> val) {
    if (!cur) return 1;
    if (cur->value.first < val.first) return cur->leftChild->getSize() + cur->frequency + Rank(cur->rightChild, val);
    else if (cur->value.first > val.first) return Rank(cur->leftChild, val);
    else return cur->leftChild->getSize() + 1;
}

template<class K, class V>
std::pair<K, V> RBTree<K, V>::getVal(int val) const {
    return Val(root, val);
}

template<class K, class V>
std::pair<K, V> RBTree<K, V>::Val(RBTreeNode<K, V>* cur, int val) const {
    if (cur->leftChild->getSize() >= val) return Val(cur->leftChild, val);
    else if (cur->leftChild->getSize() + cur->frequency >= val) return cur->value;
    else return Val(cur->rightChild, val - cur->leftChild->getSize() - cur->frequency);
}

template<class K, class V>
std::pair<K, V> RBTree<K, V>::getPre(K val) const {
    return Pre(val);
}

template<class K, class V>
std::pair<K, V> RBTree<K, V>::Pre(K val) const {
    RBTreeNode<K, V>* cur = root;
    std::pair<K, V> ans;
    int flg = 0;
    while (cur) {
        if (cur->value.first == val) {
            if (cur->leftChild) {
                cur = cur->leftChild;
                while (cur->rightChild)
                    cur = cur->rightChild;
                return cur->value;
            }
        }
        if (cur->value.first < val) {
            if (!flg) {
                flg = 1;
                ans = cur->value;
            } else if (cur->value.first > ans.first) {
                ans = cur->value;
            }
        }
        cur = cur->value.first > val ? cur->leftChild : cur->rightChild;
    }
    return ans;
}

template<class K, class V>
std::pair<K, V> RBTree<K, V>::getSuf(K val) const {
    return Suf(val);
}

template<class K, class V>
std::pair<K, V> RBTree<K, V>::Suf(K val) const {
    RBTreeNode<K, V>* cur = root;
    std::pair<K, V> ans;
    int flg = 0;
    while (cur) {
        if (cur->value.first == val) {
            if (cur->rightChild) {
                cur = cur->rightChild;
                while (cur->leftChild)
                    cur = cur->leftChild;
                return cur->value;
            }
        }
        if (cur->value.first > val) {
            if (!flg) {
                flg = 1;
                ans = cur->value;
            } else if (cur->value.first < ans.first) {
                ans = cur->value;
            }
        }
        cur = cur->value.first > val ? cur->leftChild : cur->rightChild;
    }
    return ans;
}

template<class K, class V>
void RBTree<K, V>::leftRotate(RBTreeNode<K, V>* cur) {
    RBTreeNode<K, V>* subR = cur->rightChild;
    RBTreeNode<K, V>* subRL = subR->leftChild;
    RBTreeNode<K, V>* grand = cur->parent;
    cur->rightChild = subRL;
    if (subRL)
        subRL->parent = cur;
    subR->leftChild = cur;
    cur->parent = subR;
    if (grand == nullptr) {
        root = subR;
        root->parent = nullptr;
    } else {
        if (cur == grand->leftChild) {
            grand->leftChild = subR;
        } else {
            grand->rightChild = subR;
        }
        subR->parent = grand;
    }
}

template<class K, class V>
void RBTree<K, V>::rightRotate(RBTreeNode<K, V>* cur) {
    RBTreeNode<K, V>* subL = cur->leftChild;
    RBTreeNode<K, V>* subLR = subL->rightChild;
    RBTreeNode<K, V>* grand = cur->parent;
    cur->leftChild = subLR;
    if (subLR)
        subLR->parent = cur;
    cur->parent = subL;
    subL->rightChild = cur;
    if (grand == nullptr) {
        root = subL;
        root->parent = nullptr;
    } else {
        if (cur == grand->leftChild) {
            grand->leftChild = subL;
        } else {
            grand->rightChild = subL;
        }
        subL->parent = grand;
    }
}

template<class K, class V>
void RBTree<K, V>::leftRightRotate(RBTreeNode<K, V>* cur) {
    leftRotate(cur->leftChild);
    rightRotate(cur);
}

template<class K, class V>
void RBTree<K, V>::rightLeftRotate(RBTreeNode<K, V>* cur) {
    rightRotate(cur->rightChild);
    leftRotate(cur);
}

template<class K, class V>
void RBTree<K, V>::update(RBTreeNode<K, V>*& cur) {
    cur->size = cur->leftChild->getSize() + cur->rightChild->getSize() + cur->frequency;
}

#endif