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
        SplayNode<T>* parent;
        SplayNode<T>* leftChild;
        SplayNode<T>* rightChild;
        SplayNode(T val) 
            : value(val)
            , parent(nullptr)
            , leftChild(nullptr)
            , rightChild(nullptr) {}
};

template<class T>
class Splay {
    public:
        void insert(T);
        void remove(T);
        bool search(T);
        T getMin();
        T getPre(T);
        T getSuf(T);
        void inOrderTraversal();
        Splay()
            : root(nullptr) {}
    private:  
        SplayNode<T>* root;
        SplayNode<T>* Min();
        void Insert(T);
        void Remove(T);
        SplayNode<T>* search(SplayNode<T>*, T); 
        SplayNode<T>* Pre(SplayNode<T>*, T);
        SplayNode<T>* Suf(SplayNode<T>*, T);
        void update(SplayNode<T>*&);
        void inOrderTraversal(SplayNode<T>*);
        void leftRotate(SplayNode<T>*);
        void rightRotate(SplayNode<T>*);
        void splay(SplayNode<T>*&, SplayNode<T>*&);
};

template<class T>
T Splay<T>::getMin() {
    return Min()->value;
}

template<class T>
SplayNode<T>* Splay<T>::Min() {
    SplayNode<T>* cur = root;
    if (!cur->leftChild) {
        return cur;
    }
    cur = cur->leftChild;
    while (cur->rightChild)
        cur = cur->rightChild;
    return cur;
}

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
        }
    }
    splay(current, root);
}

template<class T>
void Splay<T>::remove(T key) {
    Remove(key);
}

template<class T>
void Splay<T>::Remove(T key) {
    SplayNode<T>* curNode = search(root, key);
    splay(curNode, root);
    SplayNode<T>* cur = root;
    SplayNode<T>* ans = nullptr;
    SplayNode<T>* current = nullptr;
    if (!cur->leftChild) {
        root = cur->rightChild;
        if (cur->rightChild) cur->rightChild->parent = nullptr;
        return ;
    }
    cur = cur->leftChild;
    if (cur->rightChild) {
        while (cur->rightChild)
            cur = cur->rightChild;
        ans = cur;
    } else ans = cur;
    // std::cout << "ans : " << ans->value;/
    // std::cout << "ans: " << ans->value << "\n";
    // std::cout << root->leftChild->value << "\n";
    // std::cout << "equal: " << (ans == root->leftChild);
    splay(ans, root->leftChild);
    root->leftChild->rightChild = root->rightChild;
    root = root->leftChild;
    if (root->rightChild) root->rightChild->parent = root;
    root->parent = nullptr;
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
    splay(ans, root);
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
    splay(ans, root);
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
    splay(ans, root);
    return ans;
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
void Splay<T>::splay(SplayNode<T>*& cur, SplayNode<T>*& target) {
    // std::cout << "Splay equal: " << (cur == target) << "\n";
    if (cur == target) return ;
    // std::cout << "this is a test";
    while (cur != target) {
        if (cur == target->leftChild) {
            rightRotate(target);
            break;
        } else if (cur == target->rightChild) {
            leftRotate(target);
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
        }
    }
}

#endif