#ifndef LEFTISTHEAP_HPP
#define LEFTISTHEAP_HPP

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

template<class T>
class LeftistHeapNode {
    public:
        T value;
        int npl;
        LeftistHeapNode<T>* leftChild;
        LeftistHeapNode<T>* rightChild;
        LeftistHeapNode()
            : npl(-1)
            , leftChild(nullptr)
            , rightChild(nullptr) {}
        LeftistHeapNode(T val)
            : npl(0)
            , value(val)
            , leftChild(nullptr)
            , rightChild(nullptr) {}
};      

template<class T>
class LeftistHeap {
    public:
        LeftistHeapNode<T>* root;
        LeftistHeap()
            : root(nullptr) {}
        LeftistHeap(T val) {
            root = new LeftistHeapNode<T>(val);
        }
        void insert(T);
        void merge(LeftistHeap<T>);
        void pop();
        void preOrder();
        void inOrder();
        void postOrder();
    private:
        LeftistHeapNode<T>* merge(LeftistHeapNode<T>*, LeftistHeapNode<T>*);
        void insert(LeftistHeap<T>*);
        void preOrder(LeftistHeapNode<T>*);
        void inOrder(LeftistHeapNode<T>*);
        void postOrder(LeftistHeapNode<T>*);
};

template<class T>
void LeftistHeap<T>::postOrder() {
    postOrder(root);
    std::cout << "\n";
}

template<class T>
void LeftistHeap<T>::postOrder(LeftistHeapNode<T>* cur) {
    if (!cur) return ;
    postOrder(cur->leftChild);
    postOrder(cur->rightChild);
    std::cout << cur->value << " ";
}

template<class T>
void LeftistHeap<T>::inOrder() {
    inOrder(root);
    std::cout << "\n";
}

template<class T>
void LeftistHeap<T>::inOrder(LeftistHeapNode<T>* cur) {
    if (!cur) return ;
    inOrder(cur->leftChild);
    std::cout << cur->value << " ";
    inOrder(cur->rightChild);
}

template<class T>
void LeftistHeap<T>::preOrder() {
    preOrder(root);
    std::cout << "\n";
}

template<class T>
void LeftistHeap<T>::preOrder(LeftistHeapNode<T>* cur) {
    if (!cur) return ;
    std::cout << cur->value << " ";
    preOrder(cur->leftChild);
    preOrder(cur->rightChild);
}

template<class T>
void LeftistHeap<T>::insert(T value) {
    insert(new LeftistHeap<T>(value));
}

template<class T>
void LeftistHeap<T>::insert(LeftistHeap<T>* heap) {
    root = merge(root, heap->root);
}

template<class T>
void LeftistHeap<T>::merge(LeftistHeap<T> heap) {
    root = merge(root, heap.root);
}

template<class T>
LeftistHeapNode<T>* LeftistHeap<T>::merge(LeftistHeapNode<T>* x, LeftistHeapNode<T>* y) {
    if (x == nullptr) {
        return y;
    } else if (y == nullptr) {
        return x;
    }
    if (x->value > y->value) {
        LeftistHeapNode<T>* temp = x;
        x = y;
        y = temp;
    }
    x->rightChild = merge(x->rightChild, y);
    if (x->leftChild == nullptr || x->leftChild->npl < x->rightChild->npl) {
        LeftistHeapNode<T>* temp = x->leftChild;
        x->leftChild = x->rightChild;
        x->rightChild = temp;
    }
    if (x->rightChild == nullptr || x->leftChild == nullptr) {
        x->npl = 0;
    } else {
        // x->npl = (x->leftChild->npl > x->rightChild->npl) ? (x->rightChild->npl + 1) : (x->leftChild->npl + 1);
        x->npl = x->rightChild->npl + 1;
    }
    return x;
}

template<class T>
void LeftistHeap<T>::pop() {
    if (!root) {
        throw std::runtime_error("the heap is empty!");
        return ;
    }
    LeftistHeapNode<T>* l = root->leftChild;
    LeftistHeapNode<T>* r = root->rightChild;
    delete root;
    root = merge(l, r);
}

#endif