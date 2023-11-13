
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

int getVal() {
    return rand();
}

template<class T>
class TreapNode {
    public:
        T key;
        int value;
        int frequency;
        int size;
        TreapNode<T>* leftChild;
        TreapNode<T>* rightChild;
        int getSize() {
            if (!this) return 0;
            return size;
        }
        int getFrequency() {
            if (!this) return 0;
            return frequency;
        }
        TreapNode(T k)
            : value(getVal())
            , key(k)
            , leftChild(nullptr)
            , rightChild(nullptr)
            , frequency(1)
            , size(1) {}
};

template<class T>
class Treap {
    public:
        void insert(T);
        void remove(T);
        int getRank(T);
        T getKey(int);
        T getPre(T);
        T getSuf(T);
        void inOrderTraverse();
        Treap() {
            root = nullptr;
        }
    private:
        TreapNode<T>* root;
        void insert(TreapNode<T>*&, T);
        void remove(TreapNode<T>*&, T);
        int Rank(TreapNode<T>*, T);
        T Key(TreapNode<T>*, int);
        T Pre(TreapNode<T>*, T);
        T Suf(TreapNode<T>*, T);
        void leftRotate(TreapNode<T>*&);
        void rightRotate(TreapNode<T>*&);
        void inOrderTraverse(TreapNode<T>*);
        void update(TreapNode<T>*&);
};

template<class T>
void Treap<T>::insert(T key) {
    insert(root, key);
}

template<class T>
void Treap<T>::insert(TreapNode<T>*& cur, T key) {
    if (!cur) {
        cur = new TreapNode<T>(key);
        return ;
    } else if (cur->key > key) {
        insert(cur->leftChild, key);
        if (cur->leftChild->value < cur->value) rightRotate(cur);
        update(cur);
    } else if (cur->key < key) {
        insert(cur->rightChild, key);
        if (cur->rightChild->value < cur->value) leftRotate(cur);
        update(cur); // 如果没有 rotate 的话，不写这一句话就没有办法 update 了
    } else {
        ++cur->frequency;
        ++cur->size;
    }
    // update(cur);
}

template<class T>
void Treap<T>::remove(T key) {
    remove(root, key);
}

template<class T>
void Treap<T>::remove(TreapNode<T>*& cur, T key) {
    if (!cur) return ;
    if (cur->key > key) {
        remove(cur->leftChild, key);
        update(cur);
    } else if (cur->key < key) {    
        remove(cur->rightChild, key);
        update(cur);
    } else {
        if (cur->frequency > 1) {
            --cur->frequency;
            --cur->size;
            return ;
        }
        else {
            if (!cur->leftChild && !cur->rightChild) {
                delete cur;
                cur = nullptr;
                return ;
            }
            if (cur->leftChild == nullptr) {
                delete cur;
                cur = cur->rightChild;
            } else if (cur->rightChild == nullptr) {
                delete cur;
                cur = cur->leftChild;
            } else {
                if (cur->leftChild->value > cur->rightChild->value) {
                    leftRotate(cur);
                    remove(cur->leftChild, key);
                    update(cur);
                } else {
                    rightRotate(cur);
                    remove(cur->rightChild, key);
                    update(cur);
                }
            }
        }
    }
    // update(cur);
}

template<class T>
int Treap<T>::getRank(T key) {
    return Rank(root, key);
}

template<class T>
int Treap<T>::Rank(TreapNode<T>* cur, T key) {
    if (!cur) return 1;
    if (cur->key > key) {
        return Rank(cur->leftChild, key);
    } else if (cur->key == key) {
        return cur->leftChild->getSize() + 1;
    } else {
        return cur->leftChild->getSize() + cur->getFrequency() + Rank(cur->rightChild, key);
    }
}

template<class T>
T Treap<T>::getKey(int rank) {
    return Key(root, rank);
}

template<class T>
T Treap<T>::Key(TreapNode<T>* cur, int rank) {
    if (cur->leftChild->getSize() >= rank) return Key(cur->leftChild, rank);
    else if (cur->leftChild->getSize() + cur->getFrequency() >= rank) return cur->key;
    else return Key(cur->rightChild, rank - cur->leftChild->getSize() - cur->getFrequency());
}

template<class T>
T Treap<T>::getPre(T key) {
    return Pre(root, key);
}

template<class T>
T Treap<T>::Pre(TreapNode<T>* cur, T key) {
    TreapNode<T>* ans = nullptr;
    while (cur) {
        if (cur->key == key) {
            TreapNode<T>* pre = cur->leftChild;
            if (pre) {
                while (pre->rightChild)
                    pre = pre->rightChild;
                return pre->key;
            }
        }
        if (cur->key < key) {
            if (!ans) ans = cur;
            else if (cur->key > ans->key) ans = cur;
        }
        cur = cur->key > key ? cur->leftChild : cur->rightChild;
    }
    return ans->key;
}

template<class T>
T Treap<T>::getSuf(T key) {
    return Suf(root, key);
}

template<class T>
T Treap<T>::Suf(TreapNode<T>* cur, T key) {
    TreapNode<T>* ans = nullptr;
    while (cur) {
        if (cur->key == key) {
            TreapNode<T>* pre = cur->rightChild;
            if (pre) {
                while (pre->leftChild)
                    pre = pre->leftChild;
                return pre->key;
            }
        }
        if (cur->key > key) {
            if (!ans) ans = cur;
            else if (cur->key < ans->key) ans = cur;
        }
        cur = cur->key > key ? cur->leftChild : cur->rightChild;
    }
    return ans->key;
}

template<class T>
void Treap<T>::leftRotate(TreapNode<T>*& cur) {
    TreapNode<T>* subR = cur->rightChild;
    cur->rightChild = subR->leftChild;
    subR->leftChild = cur;
    update(cur);
    update(subR);
    cur = subR;
}

template<class T>
void Treap<T>::rightRotate(TreapNode<T>*& cur) {
    TreapNode<T>* subL = cur->leftChild;
    cur->leftChild = subL->rightChild;
    subL->rightChild = cur;
    update(cur);
    update(subL);
    cur = subL;
}

template<class T>
void Treap<T>::inOrderTraverse() {
    inOrderTraverse(root);
    std::cout << "\n";
}

template<class T>
void Treap<T>::inOrderTraverse(TreapNode<T>* cur) {
    if (!cur) return ;
    inOrderTraverse(cur->leftChild);
    std::cout << cur->key << " ";
    inOrderTraverse(cur->rightChild);
}

template<class T>
void Treap<T>::update(TreapNode<T>*& cur) {
    cur->size = cur->leftChild->getSize() + cur->rightChild->getSize() + cur->getFrequency();
}


int main() {
    srand(time(0));
    Treap<int> t;
    int opt, x;
    int n;
    std::cin >> n;
    while (n--) {
        std::cin >> opt >> x;
        if (opt == 1) {
            t.insert(x);
        } else if (opt == 2) {
            t.remove(x);
        } else if (opt == 3) {
            std::cout << t.getRank(x) << "\n";
        } else if (opt == 4) {
            std::cout << t.getKey(x) << "\n";
        } else if (opt == 5) {
            std::cout << t.getPre(x) << "\n";
        } else {
            std::cout << t.getSuf(x) << "\n";
        }
    }
    // int x;
    // std::cin >> x;
    // t.insert(x);
    // t.inOrderTraverse();
    // std::cin >> x;
    // std::cout << t.getKey(x) << "\n";
    return 0;
}