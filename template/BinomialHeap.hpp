#ifndef  BINOMIAL_HEAP
#define BINOMIAL_HEAP

#include <iostream>
#include <algorithm>
#include <algorithm>
#include <string>
#include <vector>

template<class T>
class BinomialHeapNode {
    public:
        T value;
        int degree;
        BinomialHeapNode<T>* sibling;
        BinomialHeapNode<T>* child;
        BinomialHeapNode<T>* parent;
        BinomialHeapNode(T val)
            : value(val)
            , degree(0)
            , sibling(nullptr)
            , child(nullptr)
            , parent(nullptr) {}
};

template<class T>
class BinomialHeap {
    public:
        void insert(T);
        T top();
        void pop();
        BinomialHeapNode<T>* topNode() {
            return top(head);
        }
        void unionHeap(BinomialHeapNode<T>*);
        void decrease(BinomialHeapNode<T>*, int);
        BinomialHeapNode<T>* getHead() {
            return head;
        }
        BinomialHeap() {
            head = nullptr;
        }
    private:
        void extractMin();  
        BinomialHeapNode<T>* head;
        void Insert(T);
        BinomialHeapNode<T>* top(BinomialHeapNode<T>*);
        void linkNode(BinomialHeapNode<T>*&, BinomialHeapNode<T>*&);
        BinomialHeapNode<T>* mergeTopLink(BinomialHeapNode<T>*);
        BinomialHeapNode<T>* getTopLink(BinomialHeapNode<T>*, BinomialHeapNode<T>*);
};

template<class T>
void BinomialHeap<T>::insert(T val) {
    Insert(val);
}

template<class T>
void BinomialHeap<T>::Insert(T val) {
    if (!head) {
        head = new BinomialHeapNode<T>(val);
        return ;
    }
    BinomialHeapNode<T>* newNode = new BinomialHeapNode<T>(val);
    // BinomialHeapNode<T>* newHead = getTopLink(head, newNode);
    newNode->sibling = head;
    head = newNode;
    head = mergeTopLink(head);
}

template<class T>
T BinomialHeap<T>::top() {
    return top(head)->value;
}

template<class T>
BinomialHeapNode<T>* BinomialHeap<T>::top(BinomialHeapNode<T>* cur) {
    BinomialHeapNode<T>* ans = nullptr;
    while (cur) {
        if (!ans) ans = cur;
        else if (cur->value < ans->value) ans = cur;
        cur = cur->sibling;
    }
    return ans;
}

template<class T>
void BinomialHeap<T>::pop() {
    extractMin();
}

template<class T>
void BinomialHeap<T>::extractMin() {
    BinomialHeapNode<T>* minNode = top(head);
    BinomialHeapNode<T>* cur = head;
    if (cur == minNode) {
        if (head->sibling) {
            head = head->sibling;
        } else {
            head = nullptr;
            // return ;
        }
    } else {
        while (cur->sibling != minNode)
            cur = cur->sibling;
        cur->sibling = cur->sibling->sibling;
    }
    std::vector<BinomialHeapNode<T>*> v;
    BinomialHeapNode<T>* curNode = minNode->child;
    if (curNode) {
        while (curNode) {
            v.push_back(curNode);
            curNode = curNode->sibling;
        }
        for (BinomialHeapNode<T>* element : v)
            element->sibling = nullptr;
        if (v.size() > 1) {
            std::reverse(v.begin(), v.end());
            // 获取 minNode 的 pre，和 后面连接
            // 取反 v 然后再合并两个根链 
            for (int i = 0; i < v.size() - 1; ++i)
                v[i]->sibling = v[i + 1];
        }
        // BinomialHeapNode<T>* newHead = getTopLink(head, v[0]);
        // head = mergeTopLink(newHead);
        head = getTopLink(head, v[0]);
        head = mergeTopLink(head);
    }
}

template<class T>
void BinomialHeap<T>::unionHeap(BinomialHeapNode<T>* h2) {
    head = getTopLink(head, h2);
    head = mergeTopLink(head);
}

template<class T>
void BinomialHeap<T>::decrease(BinomialHeapNode<T>* cur, int key) {
    if (!cur || !head) {
        throw std::runtime_error("illegal decreasing!");
    }
    cur->value -= key;
    BinomialHeapNode<T>* parent = cur->parent;
    while (parent && cur->value < parent->value) {
        T temp = cur->value;
        cur->value = parent->value;
        parent->value = temp;
        cur = parent;
        parent = cur->parent;
    }
}

template<class T>
void BinomialHeap<T>::linkNode(BinomialHeapNode<T>*& cur, BinomialHeapNode<T>*& newNode) {
    newNode->parent = cur;
    newNode->sibling = cur->child;
    cur->child = newNode;
    ++cur->degree;
}

template<class T>
BinomialHeapNode<T>* BinomialHeap<T>::getTopLink(BinomialHeapNode<T>* p1, BinomialHeapNode<T>* p2) {
    if (p1 == nullptr) {
        return p2;
    } else if (p2 == nullptr) {
        return p1;
    }
    BinomialHeapNode<T>* newHead = nullptr;
    BinomialHeapNode<T>* p = nullptr;
    if (p1->degree <= p2->degree) {
        newHead = p1;
        p = p1;
        p1 = p1->sibling;
    } else {
        newHead = p2;
        p = p2;
        p2 = p2->sibling;
    }
    while (p1 && p2) {
        if (p1->degree <= p2->degree) {
            p->sibling = p1;
            p1 = p1->sibling;
            p = p->sibling;
        } else {
            p->sibling = p2;
            p2 = p2->sibling;
            p = p->sibling;
        }
    }
    if (p1) p->sibling = p1;
    else p->sibling = p2;
    return newHead;
}

template<class T>
BinomialHeapNode<T>* BinomialHeap<T>::mergeTopLink(BinomialHeapNode<T>* cur) {
    if (!cur) return nullptr;
    BinomialHeapNode<T>* prev = nullptr;
    BinomialHeapNode<T>* x = cur;
    BinomialHeapNode<T>* nxt = x->sibling;
    while (nxt) {
        // std::cout << "a";
        if (x->degree != nxt->degree || (nxt->sibling && nxt->sibling->degree == x->degree)) {
            prev = x;
            x = nxt; // 连续三个一样的，并且现在的 x 指向了第一个位置 或者 当前不一样和下一个
        } else if (x->value <= nxt->value) {
            x->sibling = nxt->sibling;
            linkNode(x, nxt);
        } else {
            if (prev == nullptr) {
                cur = nxt;
            } else {
                prev->sibling = nxt;
            }
            linkNode(nxt, x);
            x = nxt;
        }
        nxt = x->sibling;
    }
    return cur;
}

#endif