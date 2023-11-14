#ifndef SPLAY_HPP
#define SPLAY_HPP

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

template<class T>
class SplayNode {
    public:
        T value;
        int frequency;
        int size;
        SplayNode<T>* parent;
        SplayNode<T>* leftChild;
        SplayNode<T>* rightChild;
        int getFrequency() {
            if (!this) return 0;
            return frequency;
        }
        int getSize() {
            if (!this) return 0;
            return size;
        }
        SplayNode(T val) 
            : value(val)
            , parent(nullptr)
            , leftChild(nullptr)
            , rightChild(nullptr)
            , size(1)
            , frequency(1) {}
};

template<class T>
class Splay {
    public:
        void insert(T);
        void remove(T);
        bool search(T);
        T getPre(T);
        T getSuf(T);
        int getRank(T);
        T getKey(int);
        void inOrderTraversal();
        Splay()
            : root(nullptr) {}
    private:  
        SplayNode<T>* root;
        void Insert(T);
        void remove(SplayNode<T>*, T);
        SplayNode<T>* search(SplayNode<T>*, T); 
        SplayNode<T>* Pre(SplayNode<T>*, T);
        SplayNode<T>* Suf(SplayNode<T>*, T);
        int Rank(SplayNode<T>*, T);
        T Key(SplayNode<T>*, int);
        void update(SplayNode<T>*&);
        void inOrderTraversal(SplayNode<T>*);
        void leftRotate(SplayNode<T>*);
        void rightRotate(SplayNode<T>*);
        void splay(SplayNode<T>*&);
};

template<class T>
void Splay<T>::insert(T key) {
    Insert(key);
}

template<class T>
void Splay<T>::Insert(T key) {
    if (root == nullptr) {
        root = new SplayNode<T>(key);
        return ;
    }
    SplayNode<T>* current = root;
    while (current) {
        if (key < current->value) {
            if (current->leftChild == nullptr) {
                current->leftChild = new SplayNode<T>(key);
                current->leftChild->parent = current;
                current = current->leftChild;
                break;
            }
            current = current->leftChild;
        } else if (key > current->value) {
            if (current->rightChild == nullptr) {
                current->rightChild = new SplayNode<T>(key);
                current->rightChild->parent = current;
                current = current->rightChild;
                break;
            }
            current = current->rightChild;
        } else {
            current->frequency++;
            current->size++;
            break;
        }
    }
    splay(current);
}

template<class T>
void Splay<T>::remove(T key) {
    SplayNode<T>* cur = search(root, key);
    if (cur) {
        if (cur->frequency > 1) {
            cur->frequency--;
            cur->size--;
        } else {
            remove(root, key);
        }
    }
}

template<class T>
void Splay<T>::remove(SplayNode<T>* root, T key) {
    
}

template<class T>
bool Splay<T>::search(T key) {
    return search(root, key) != nullptr;
}

template<class T>
SplayNode<T>* Splay<T>::search(SplayNode<T>* cur, T key) {
    if (!root) {
        throw std::runtime_error("the tree is empty!");
    }
    SplayNode<T>* ans = nullptr;
    while (cur) {
        if (key < cur->value) cur = cur->leftChild;
        else if (key > cur->value) cur = cur->rightChild;
        else {
            ans = cur;
            break;
        }
    }
    if (!ans) return nullptr;
    splay(ans);
    return cur;
}

template<class T>
T Splay<T>::getPre(T key) {
    return Pre(root, key)->value;
}

template<class T>
SplayNode<T>* Splay<T>::Pre(SplayNode<T>* Root, T key) {
    SplayNode<T>* cur = Root;
    SplayNode<T>* ans = nullptr;
    while (cur) {
        if (key == cur->value) {
            SplayNode<T>* current = cur->leftChild;
            if (current) {
                while (current->rightChild)
                    current = current->rightChild;
                return current;
            }
        }
        if (cur->value < key) {
            if (!ans) ans = cur;
            else if (cur->value > ans->value) ans = cur;
        }
        cur = cur->value > key ? cur->leftChild : cur->rightChild;
    }
    splay(ans);
    return ans;
}

template<class T>
T Splay<T>::getSuf(T key) {
    return Suf(root, key)->value;
}

template<class T>
SplayNode<T>* Splay<T>::Suf(SplayNode<T>* Root, T key) {
    SplayNode<T>* cur = Root;
    SplayNode<T>* ans = nullptr;
    while (cur) {
        if (key == cur->value) {
            SplayNode<T>* current = cur->rightChild;
            if (current) {
                while (current->leftChild)
                    current = current->leftChild;
                return current;
            }
        }
        if (cur->value > key) {
            if (!ans) ans = cur;
            else if (cur->value < ans->value) ans = cur;
        }
        cur = cur->value > key ? cur->leftChild : cur->rightChild;
    }
    splay(ans);
    return ans;
}

template<class T>
int Splay<T>::getRank(T key) {
    return Rank(root, key);
}

template<class T>
int Splay<T>::Rank(SplayNode<T>* cur, T key) {
    if (!cur) return 1;
    if (cur->value > key) {
        return Rank(cur->leftChild, key);
    } else if (cur->value == key) {
        return cur->leftChild->getSize() + 1;
    } else {
        return cur->leftChild->getSize() + cur->getFrequency() + Rank(cur->rightChild, key);
    }
}

template<class T>
T Splay<T>::getKey(int rank) {
    return Key(root, rank);
}

template<class T>
T Splay<T>::Key(SplayNode<T>* cur, int rank) {
    if (cur->leftChild->getSize() >= rank) return Key(cur->leftChild, rank);
    else if (cur->leftChild->getSize() + cur->getFrequency() >= rank) return cur->value;
    else return Key(cur->rightChild, rank - cur->leftChild->getSize() - cur->getFrequency());
}

template<class T>
void Splay<T>::update(SplayNode<T>*& cur) {
    if (cur->leftChild) cur->leftChild->parent = cur;
    if (cur->rightChild) cur->rightChild->parent = cur;
}

template<class T>
void Splay<T>::inOrderTraversal() {
    inOrderTraversal(root);
    std::cout << "\n";
}

template<class T>
void Splay<T>::inOrderTraversal(SplayNode<T>* cur) {
    if (!cur) return ;
    inOrderTraversal(cur->leftChild);
    std::cout << cur->value << " ";
    inOrderTraversal(cur->rightChild);
}

template<class T>
void Splay<T>::leftRotate(SplayNode<T>* x) { // 三组双向更新，其中两组需要判断
    SplayNode<T>* y = x->rightChild;
    x->rightChild = y->leftChild;
    if (y->leftChild != nullptr) {
        y->leftChild->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y; 
    } else if (x == x->parent->leftChild) {
        x->parent->leftChild = y;
    } else {
        x->parent->rightChild = y;
    }
    y->leftChild = x;
    x->parent = y;
}

template<class T>
void Splay<T>::rightRotate(SplayNode<T>* x) {
    SplayNode<T>* y = x->leftChild;
    x->leftChild = y->rightChild;
    if (y->rightChild != nullptr) {
        y->rightChild->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y;
    } else if (x == x->parent->leftChild) {
        x->parent->leftChild = y;
    } else {
        x->parent->rightChild = y;
    }
    y->rightChild = x;
    x->parent = y;
}

template<class T>
void Splay<T>::splay(SplayNode<T>*& cur) {
    while (cur != root) {
        if (cur == root->leftChild) {
            rightRotate(root);
            break;
        } else if (cur == root->rightChild) {
            leftRotate(root);
            break;
        } else {
            SplayNode<T>* parent = cur->parent;
            SplayNode<T>* grandParent = parent->parent;
            if (cur == parent->leftChild && parent == grandParent->leftChild) {
                rightRotate(grandParent);
                rightRotate(parent);
            } else if (cur == parent->rightChild && parent == grandParent->rightChild) {
                leftRotate(grandParent);
                leftRotate(parent);
            } else if (cur == parent->leftChild && parent == grandParent->rightChild) {
                rightRotate(parent);
                leftRotate(grandParent);
            } else {
                leftRotate(parent);
                rightRotate(grandParent);
            }
            // 更新大小
            if (grandParent) {
                grandParent->size = (grandParent->leftChild ? grandParent->leftChild->getSize() : 0) +
                                    (grandParent->rightChild ? grandParent->rightChild->getSize() : 0) +
                                    grandParent->getFrequency();
            }
            if (parent) {
                parent->size = (parent->leftChild ? parent->leftChild->getSize() : 0) +
                               (parent->rightChild ? parent->rightChild->getSize() : 0) +
                               parent->getFrequency();
            }
            cur->size = (cur->leftChild ? cur->leftChild->getSize() : 0) +
                        (cur->rightChild ? cur->rightChild->getSize() : 0) +
                        cur->getFrequency();
        }
    }
}

#endif
